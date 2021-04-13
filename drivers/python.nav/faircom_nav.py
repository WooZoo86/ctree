# -*- coding: Latin-1 -*-

import sys
if sys.version_info < (3,4,0):
    raise Exception("Python version 3.4 and later is required by this module.  You are running version %s.%s.%s." % (str(sys.version_info.major),str(sys.version_info.minor),str(sys.version_info.micro)))

from ctdb_const import *

import ctypes, math
from ctpp import * 
from ctdb import *

from decimal import Decimal

from datetime import * 


# ************************************************************************************
# ************************************************************************************
#
#  Table Class
#
# Encapsulates the table created in the FairCom database
# - The table must be opened before it can be used.
# - First call .open() to open the table.
# - If the table cannot be opened, call .create() to create it, and then call .Open().
# - Once the table is open, all methods work -- except .create().
#
# - An application can instantiate many of these objects 
#   to simultaneously open the table on the same database 
#   or on different databases on different Faircom Servers.
#
# Contains the following
#   - FairCom Objects for managing database session, table, and last exception
#   - Methods to open, close, create, and delete the table
#   - Method to get a new record buffer object to work with table data
#   - Methods to begin, commit, and rollback transactions on the table
#
# Special features
#  - Each instance of table represents a connection to the table in the database. 
#  - This makes it is easy to open multiple, simultaneous connection sessions 
#    to the same table in the same FairCom Server and Database.
#  - It also makes it easy to simultaneously open or create different tables 
#    in different databases or on different Servers.

class Table(): 
  __table_name = "" 
  __table_password = "" 
  @property
  def table_name(self):
    return self.__table_name
  @property
  def table_password(self):
    return self.__table_password

  __isOpen = False
  __faircomDatabase = None 
  __ctTable = None 
  __disposing = False

  def __init__(self, table_name="athlete", table_password=""): 
    self.__table_name = table_name
    self.__table_password = table_password

  def __del__(self):
    self.__disposing = True
    self.close()

  # ================================================================================
  # 
  # Table Properties
  #

  @property
  def is_open(self): 
    return self.__isOpen

  @property
  def faircom_database(self): 
    return self.__faircomDatabase

  @property
  def myCTTable(self): 
    return self.__ctTable

  # ================================================================================
  # 
  # Open or Create Table
  #


  def open_or_create(self, faircom_database, open_mode=OpenModeEnum.NORMAL, field_defs=None, index_information=None, identity_field_information=None):
    try:
      self.open(faircom_database, open_mode) 
    except ctdb.DatabaseError as e:
      if e.error_code == 4023:
        try:
          self.create(faircom_database, field_defs, index_information, identity_field_information)
          self.open(faircom_database, open_mode)
        except ctdb.DatabaseError as e:
            raise e
      else:
        raise e


  # ================================================================================
  # 
  # Open Table
  # 

  def open(self, faircomDatabase, openMode=OpenModeEnum.NORMAL):
    if self.__isOpen:
      return

    self.__faircomDatabase = faircomDatabase
    try:
      self.__ctTable = CTTable(self.__faircomDatabase.CTDatabase)
      self.__ctTable.Open(self.__table_name, openMode)

      self.__isOpen = True

    except ctdb.DatabaseError as e:
      raise e 


  # ================================================================================
  # 
  # Close Table
  # 

  def close(self):
    if not self.__isOpen:
      return
      
    try:
      self.__ctTable.Close()
    except ctdb.DatabaseError as e:
      if not self.__disposing:
        raise e
    self.__isOpen = False



  # ================================================================================
  # 
  # Validate field definition list for adding columns to a table
  # A good list throws no errors.
  # A bad list throws an error with a text description of the problem.
  # 
  # INTERNAL USE ONLY!!!!  NOT FOR CUSTOMER USE!!!
  #

  def int_validate_field_definitions(self, field_defs=None):
    if type(field_defs) is not list:
      raise ctdb.DatabaseError("Error! The 'field_defs' parameter must be a list.", 1) 
    if len(field_defs)==0:
      raise ctdb.DatabaseError("Error! There needs to be at least one user-added field.", 1) 
    for index1, fieldDef in enumerate(field_defs):
      if type(fieldDef) is not dict:
        raise ctdb.DatabaseError("Error! Each item in the 'field_defs' list item must be a dictionary.  Item #%d is not." % (index1), 1) 
      if ("Name" not in fieldDef) or ("Type" not in fieldDef):
        raise ctdb.DatabaseError("Error! Each dict item in the table 'field_defs' list must contain at least a 'Name' and 'Type' item.  Please check item %d in the 'field_defs' list." % (index1), 1) 
      for index2, key in enumerate(fieldDef.keys()):
        if (key!="Name") and (key!="Type") and (key!="Length") and (key!="Scale") and (key!="NotNull"):
          raise ctdb.DatabaseError("Error! Unrecognized key [%s] in position %d of table 'field_defs' list item #%d." % (key,index2,index1), 1) 

    seen=set() 
    for index1, fieldDef in enumerate(field_defs):
      fieldName = fieldDef["Name"]
      if fieldName.isspace():
        raise ctdb.DatabaseError("Error! Field number %d's name is blank / pure white space." % (index1))
      fieldName=fieldName.strip().lower() 
      if not fieldName[0].isalpha():
        raise ctdb.DatabaseError("Error! Field number %d's name (%s) does not start with a letter." % (index1, fieldName))
      if fieldName in seen:
        raise ctdb.DatabaseError("Error! Field name '%s' occurs more than once in field_defs (case-insensitive)." % (fieldName))
      else:
        seen.add(fieldName)


  # ================================================================================
  # 
  # Add fields / columns to a table.  Used by table creation and adding / inserting new columns later.
  # 
  # INTERNAL USE ONLY!!!!  NOT FOR CUSTOMER USE!!!
  # Success throws no errors.  Failure throws an error with a text description of the problem.
  #

  def int_add_fields(self, field_defs=None):

    try:

      for fieldDef in field_defs:

        if "Length" in fieldDef:
          length=fieldDef["Length"]
        else:
          length=0
        colType=fieldDef["Type"]
        if length <= 0:
          if colType!=FieldTypeEnum.BOOLEAN and colType!=FieldTypeEnum.INT8_SIGNED and colType!=FieldTypeEnum.INT8_UNSIGNED and colType!=FieldTypeEnum.INT16_SIGNED and colType!=FieldTypeEnum.INT16_UNSIGNED and colType!=FieldTypeEnum.INT32_SIGNED and colType!=FieldTypeEnum.INT32_UNSIGNED and \
            colType!=FieldTypeEnum.MONEY and colType!=FieldTypeEnum.DATE and colType!=FieldTypeEnum.TIME and colType!=FieldTypeEnum.FLOAT32 and colType!=FieldTypeEnum.FLOAT64 and colType!=FieldTypeEnum.TIMESTAMP and \
            colType!=FieldTypeEnum.INT64_SIGNED and colType!=FieldTypeEnum.INT64_UNSIGNED and colType!=FieldTypeEnum.CURRENCY and colType!=FieldTypeEnum.DECIMAL:
            if length==0 and colType==FieldTypeEnum.STRING:
              pass 
            else:
              raise ctdb.DatabaseError("The column type used by the '"+fieldDef["Name"]+"' column requires a length that is greater than zero.", 1) 
        

        field = self.__ctTable.AddField(fieldDef["Name"].strip(), colType, length) 

        if "Scale" in fieldDef: 
          field.SetScale(fieldDef["Scale"])

        if "NotNull" in fieldDef:
          field.SetNullFlag(fieldDef["NotNull"])

        

      for field_number, fieldDef in enumerate(field_defs):
        if fieldDef["Type"] == FieldTypeEnum.STRING: 
          ctdb.SetBinaryFlag(self.__ctTable.handle, field_number, 4) 

    except ctdb.DatabaseError as e:
      raise e 



  # ================================================================================
  # 
  # Add field(s) / column(s) to an existing table
  # 
  # field_defs is a list of fields to add to the end of the table.  Same format as used by create().  Required.
  # alter_table_mode is an optional mode to pass to the ctdbAlterTable() function.
  #

  def add_fields(self, field_defs, alter_table_mode=ctdb_const.CTDB_ALTER_NORMAL):

    try:
      self.int_validate_field_definitions(field_defs)
    except ctdb.DatabaseError as e:
      raise e 

    try:
      self.__faircomDatabase.faircom_server.tran_begin()

      self.int_add_fields(field_defs)

      self.__ctTable.Alter(alter_table_mode)

      self.__faircomDatabase.faircom_server.tran_commit()

    except ctdb.DatabaseError as e:
      self.__faircomDatabase.faircom_server.tran_rollback()
      raise e 


  # ================================================================================
  # 
  # Create Table with indexes
  # 

  def create(self, faircomDatabase, field_defs=None, index_information=None, identity_field_information=None):

    if field_defs is None:
      raise ctdb.DatabaseError("Error! Table create requires a 'field_defs' list.", 1) 
  
    try:
      self.int_validate_field_definitions(field_defs)
    except ctdb.DatabaseError as e:
      raise e 

    if identity_field_information is not None:
      if type(identity_field_information) is not dict:
        raise ctdb.DatabaseError("Error! The 'identity_field_information' parameter must be a dictionary.", 1) 
      for index, key in enumerate(identity_field_information):
        if (key!="FieldName") and (key!="Seed") and (key!="Increment"):
          raise ctdb.DatabaseError("Error! Unrecognized key [%s] in position %d of the 'identity_field_information' dict." % (key,index), 1) 
      if ("FieldName" not in identity_field_information) or ("Seed" not in identity_field_information) or ("Increment" not in identity_field_information):
        raise ctdb.DatabaseError("Error! The 'identity_field_information' dict must contain a 'FieldName', 'Seed', and 'Increment' item.", 1) 

    if index_information is not None:
      if type(index_information) is not list:
        raise ctdb.DatabaseError("Error! The 'index_information' parameter must be a list.", 1) 
      for index1, indexDict in enumerate(index_information):
        if type(indexDict) is not dict:
          raise ctdb.DatabaseError("Error! Each item in the 'index_information' list item must be a dictionary.  Item #%d is `." % (index1), 1) 
        for index2, key in enumerate(indexDict):
          if (key!="IndexName") and (key!="IndexType") and (key!="AllowDuplicates") and (key!="AllowNullKeys") and (key!="SegmentList"):
            raise ctdb.DatabaseError("Error! Unrecognized key [%s] in position %d of 'index_information' dict number %d." % (key,index2,index1), 1) 
        if ("IndexName" not in indexDict) or ("IndexType" not in indexDict) or ("AllowDuplicates" not in indexDict) or ("AllowNullKeys" not in indexDict) or ("SegmentList" not in indexDict):
          raise ctdb.DatabaseError("Error! Each 'index_information' dict must contain a 'IndexName', 'IndexType', 'AllowDuplicates', 'AllowNullKeys', and 'SegmentList' item.  Index dict #%d is missing one of them." % (index1), 1) 
        segments=indexDict['SegmentList']
        if type(segments) is not list:
          raise ctdb.DatabaseError("Error! Index #%d's 'SegmentList' must be a list.  It's not." % (index1), 1) 
        if len(segments)==0:
          raise ctdb.DatabaseError("Error! Each index needs to have at least one segment.  Index #%d has none." % (index1), 1) 
        for index3, segmentDict in enumerate(segments):
          if type(segmentDict) is not dict:
            raise ctdb.DatabaseError("Error! All of the items in a 'SegmentList' must be a dictionaries.  Item #%d in index #%d's 'SegmentList' is not." % (index3,index1), 1) 
          for index4, key in enumerate(segmentDict):
            if (key!="FieldName") and (key!="Flags"):
              raise ctdb.DatabaseError("Error! Unrecognized key [%s] in position %d of index #%d's 'SegmentList' dict number %d." % (key,index4,index1,index3), 1) 
          if ("FieldName" not in segmentDict) or ("Flags" not in segmentDict):
            raise ctdb.DatabaseError("Error! Each 'SegmentList' dict must contain a 'FieldName' and 'Flags' item.  Index #%d's SegmentList dict #%d is missing one of them." % (index1,index3), 1) 


    try:
      if self.__ctTable is None:
        self.__faircomDatabase = faircomDatabase
        self.__ctTable = CTTable(self.__faircomDatabase.CTDatabase)

      self.__faircomDatabase.faircom_server.tran_begin()

      self.int_add_fields(field_defs)

      if identity_field_information is not None:
        self.__ctTable.SetIdentityField(identity_field_information['FieldName'], identity_field_information['Seed'], identity_field_information['Increment'])

      if index_information is not None:
        for indexDict in index_information:
          idx=self.__ctTable.AddIndex(indexDict['IndexName'], indexDict['IndexType'], indexDict['AllowDuplicates'], indexDict['AllowNullKeys'])
          segments=indexDict['SegmentList']
          for segmentDict in segments:
            self.__ctTable.AddSegment(idx, segmentDict['FieldName'], segmentDict['Flags'])


      self.__ctTable.Create(self.__table_name, ctdb_const.CTCREATE_HUGEFILE | ctdb_const.CTCREATE_TRNLOG)

      self.__faircomDatabase.faircom_server.tran_commit()


    except ctdb.DatabaseError as e:
      self.__faircomDatabase.faircom_server.tran_rollback()
      self.__ctTable.Close();  
      raise e 


  # ================================================================================
  # 
  # Remove fields from an existing table
  # 
  # Pass me a list of strings that give the field names I want removed.
  #
  def remove_fields(self, field_names_to_remove, alter_table_mode=ctdb_const.CTDB_ALTER_NORMAL):
    if not self.__isOpen:
      raise ctdb.DatabaseError("Need to call Table.open() method before calling remove_fields().", 1) 

    if type(field_names_to_remove) is not list:
      raise ctdb.DatabaseError("Error! The 'field_names_to_remove' parameter must be a list.", 1) 
    if len(field_names_to_remove)==0:
      raise ctdb.DatabaseError("Error! There needs to be at least one field listed in field_names_to_remove.", 1) 

    seen=set() 
    for index1, fieldName in enumerate(field_names_to_remove):
      if type(fieldName) is not str:
        raise ctdb.DatabaseError("Error! Each item in the 'field_names_to_remove' list item must be a string.  Item #%d is not." % (index1), 1) 
      if fieldName.isspace():
        raise ctdb.DatabaseError("Error! Field number %d's name is blank / pure white space." % (index1))
      fieldName=fieldName.strip().lower() 
      if fieldName in seen:
        raise ctdb.DatabaseError("Error! Field name '%s' occurs more than once in field_defs (case-insensitive)." % (fieldName))
      else:
        seen.add(fieldName)

    try:
      self.__faircomDatabase.faircom_server.tran_begin()

      for fieldName in field_names_to_remove:
        fieldName=fieldName.strip() 
        self.__ctTable.DeleteField(fieldName)

      self.__ctTable.Alter(alter_table_mode)

      self.__faircomDatabase.faircom_server.tran_commit()

    except ctdb.DatabaseError as e:
      self.__faircomDatabase.faircom_server.tran_rollback()
      raise e 


  # ================================================================================
  # 
  # Move one field in the table.
  #
  # 'the_field' param is the field name or number of the field to be moved.
  # 'new_position' param is the new field number you want that field to have.

  def move_field(self, the_field, new_position, alter_table_mode=ctdb_const.CTDB_ALTER_NORMAL):
    if not self.__isOpen:
      raise ctdb.DatabaseError("Need to call Table.open() method before calling move_field().", 1) 

    if (type(the_field) is not str) and (type(the_field) is not int):
      raise ctdb.DatabaseError("Error! The 'the_field' parameter must be a string or integer.", 1) 
    if (type(new_position) is not int):
      raise ctdb.DatabaseError("Error! The 'new_position' parameter must be an integer.", 1) 

    if type(the_field) is str:
      the_field=the_field.strip()

    try:
      self.__faircomDatabase.faircom_server.tran_begin()

      self.__ctTable.MoveField(the_field, new_position)

      self.__ctTable.Alter(alter_table_mode)

      self.__faircomDatabase.faircom_server.tran_commit()

    except ctdb.DatabaseError as e:
      self.__faircomDatabase.faircom_server.tran_rollback()
      raise e 



  # ================================================================================
  # 
  # Delete Table
  # 

  def delete(self):
    if not self.__isOpen:
      raise ctdb.DatabaseError("Need to call Table.open() method before calling delete().", 1) 
    try:
      self.close()
      self.__faircomDatabase.CTDatabase.DeleteTable(self.__table_name, self.__table_password)
    except ctdb.DatabaseError as e:
      raise e

  # ================================================================================
  # 
  # Return a new record buffer object for working with Table Records
  # 

  def new_record_buffer(self):
    if not self.__isOpen:
      raise ctdb.DatabaseError("Need to call Table.open() method before calling new_record_buffer().", 1) 
    return CTRecord(self.__ctTable)

  def get_open_mode(self):
        return self.__ctTable.GetOpenMode()


# ************************************************************************************
# 
# FaircomServer Class
#
# Manage a Faircom Server.
# - A Faircom Server contains zero or more databases.
# - You must connect to a server before you can access its databases.
# - An application can instantiate many of these objects 
#   to create simultaneous connections to different Faircom Servers.
#

class FaircomServer:
  __ServerName = "" 
  __UserName = "" 
  @property
  def server_name(self):
    return self.__ServerName
  @property
  def user_name(self):
    return self.__UserName

  __connected = False
  __ctSession = None 

  __password = ""  
  __disposing = False

  def __init__(self, faircomServerName, userName, password): 
    self.__ServerName = faircomServerName
    self.__UserName = userName
    self.__password = password

  def __del__(self):
    self.__disposing = True
    self.disconnect()

  @property
  def connected(self):
    return self.__connected

  @property
  def CTSession(self): 
    if self.__ctSession is None:
      self.connect()
    return self.__ctSession

  def connect(self):
    try:
      self.__ctSession = CTSession(SessionTypeEnum.NAV_SQL)
      self.__ctSession.Logon(self.__ServerName, self.__UserName, self.__password)
    except ctdb.DatabaseError as e:
      raise e 
    self.__connected = True

  def disconnect(self):
    if not self.__connected:
      return
    try:
      self.__ctSession.Logout()
      self.__connected = False
    except ctdb.DatabaseError as e:
      if not self.__disposing:
        raise e

  def lock(self, lockMode):
    if type(lockMode) is not LockModeEnum:
      raise ctdb.DatabaseError("Error!  FaircomServer.lock() must be given a 'LockModeEnum' parameter.", 1) 
    if not self.__connected:
      raise ctdb.DatabaseError("Error!  Please do not call FaircomServer.lock() while disconnected from the server.", 1) 
            
    try:
      self.__ctSession.Lock(lockMode)
    except ctdb.DatabaseError as e:
      raise e

  # ================================================================================
  # 
  # Begin, Commit, and Rollback Database Transactions
  # 

  def tran_begin(self): 
    try:
      self.__ctSession.Begin()
    except ctdb.DatabaseError as e:
      raise e

  def tran_commit(self):
    try:
      self.__ctSession.Commit()
    except ctdb.DatabaseError as e:
      raise e

  def tran_rollback(self):
    try:
      self.__ctSession.Abort()
    except ctdb.DatabaseError as e:
      if e.error_code != 71: #Ignore the error: "No Active Transaction"
        raise e




# ************************************************************************************
# 
# FaircomDatabase Class
#
# Manage a FairCom Database
# - You must connect to a database before you can access its objects (tables, indexes, etc.).
# - An application can instantiate many of these objects 
#   to create simultaneous connections to different databases on many Faircom Servers.
# 
# - First create the object with the database name and optional path.
# - Second call .connect() or .connect_or_create() to connect to a database in a Faircom Server.
# - .create() creates a database in a Faircom Server.
# - .delete() deletes a database in a Faircom Server.
# - When done, call .disconnect() to disconnect from the Database.
#


class FaircomDatabase:
  __DatabaseName = "" 
  __DatabasePath = "" 
  @property
  def database_name(self):
    return self.__DatabaseName
  @property
  def database_path(self):
    return self.__DatabasePath

  __connected = False
  __faircomServer = None 
  __ctDatabase = None 

  __disposing = False

  def __init__(self, databaseName, databasePath = ""):  
    self.__DatabaseName = databaseName
    self.__DatabasePath = databasePath

  def __del__(self):
    self.__disposing = True
    self.disconnect()
    
  @property
  def connected(self):
    return self.__connected

  @property
  def faircom_server(self):
    return self.__faircomServer

  @property
  def CTDatabase(self):
    return self.__ctDatabase

  def connect_or_create(self, faircomServer): 
    try:
      self.connect(faircomServer) 
    except ctdb.DatabaseError as e:
        if e.error_code == 101:
          try:
            self.create()
            self.connect(faircomServer)
          except ctdb.DatabaseError as e:
            raise e 
        else:
          raise e 
      

  def connect(self, server): 
    self.__faircomServer = server

    try:
      self.__ctDatabase = CTDatabase(self.__faircomServer.CTSession)
      self.__ctDatabase.Connect(self.__DatabaseName)
      self.__connected = True

    except ctdb.DatabaseError as e:
      raise e


  def disconnect(self):
      if not self.__connected:
        return
      try:
        self.__ctDatabase.Disconnect()
        self.__connected = False
      except ctdb.DatabaseError as e:
        if not self.__disposing:
          raise e


  def create(self):
    if not self.__faircomServer.connected:
      raise ctdb.DatabaseError("FaircomDatabase.create() cannot create database " + self.__DatabaseName + ". You must first connect FaircomDatabase object to a Faircom Server.", 1) 
    try:
      self.__ctDatabase.Create(self.__DatabaseName, self.__DatabasePath)
    except ctdb.DatabaseError as e:
      raise e


  def delete(self):
    if not self.__faircomServer.connected:
      raise ctdb.DatabaseError("FaircomDatabase.delete() cannot delete database " + self.__DatabaseName + ". You must first connect FaircomDatabase object to a Faircom Server.", 1) 

    try:
      self.disconnect()
      self.__faircomServer.CTSession.DeleteDatabase(self.__DatabaseName)
    except ctdb.DatabaseError as e:
      raise e



# ************************************************************************************
# 
# Logger Class
#
# Encapsulates logging messages to the console.
# - exit_with_faircom_error() writes out a faircom error
# - Log() writes out a string

class Logger:
  @staticmethod
  def log(message):
    print(message)

  @classmethod 
  def exit_with_faircom_error(self,err):  
    print("\nERROR: "+str(err)) 
    self.terminate_app()

  @classmethod 
  def exit_with_app_error(self,message):
    print(message)
    self.terminate_app()

  @staticmethod
  def terminate_app():
    print("*** Execution aborted *** ")
    input("\nPress <ENTER> key to exit . . .") 
    sys.exit(0)


