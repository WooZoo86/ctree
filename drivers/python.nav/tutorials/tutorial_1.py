# -*- coding: Latin-1 -*-

if False:
  print("Debugging information:")
  import struct
  print("  Python bit depth based on 'pointer' size: "+ str(struct.calcsize("P") * 8))
  import platform
  print ("  Python 'architecture' information: " + str(platform.architecture()))
  import os
  if 'PYTHONPATH' in os.environ:
    print("  PYTHONPATH=[%s]." % os.environ['PYTHONPATH'].split(os.pathsep))
    print("  This should point at the 'drivers/python.nav' folder.")
  else:
    print("  Note!!! PYTHONPATH is not set.  Should point at the 'drivers/python.nav' folder.")

  # Show information about the sizes of the various integer types.
  # c_long / c_ulong are 4 bytes long on Windows.  On Centos 8, they are 8 bytes.
  from _ctypes import *
  import ctypes
  print("sizeof(): ")
  print(" c_byte=%d, c_int8=%d, c_ubyte=%d, c_uint8=%d" % (sizeof(ctypes.c_byte), sizeof(ctypes.c_int8), sizeof(ctypes.c_ubyte), sizeof(ctypes.c_uint8)))
  print(" c_short=%d, c_int=%d, c_long=%d, c_longlong=%d" % (sizeof(ctypes.c_short), sizeof(ctypes.c_int), sizeof(ctypes.c_long), sizeof(ctypes.c_longlong)))
  print(" c_ushort=%d, c_uint=%d, c_ulong=%d, c_ulonglong=%d" % (sizeof(ctypes.c_ushort), sizeof(ctypes.c_uint), sizeof(ctypes.c_ulong), sizeof(ctypes.c_ulonglong)))
  print(" c_int16=%d, c_int32=%d, c_int64=%d" % (sizeof(ctypes.c_int16), sizeof(ctypes.c_int32), sizeof(ctypes.c_int64)))
  print(" c_uint16=%d, c_uint32=%d, c_uint64=%d" % (sizeof(ctypes.c_uint16), sizeof(ctypes.c_uint32), sizeof(ctypes.c_uint64)))
  print("")


import faircom_nav as nav
from decimal import Decimal
from datetime import *
import sys


# ================================================================================
#
# Log into the FairCom Server and connect to one of its databases.
#

def connect():
  nav.Logger.log("CONNECT")

  # Connect to the FairCom server.
  try:
    my_server.connect()
    nav.Logger.log("\tLogged onto Faircom Server Instance " + my_server.server_name + ".")
  
  except nav.DatabaseError as e:
    nav.Logger.log("\tFaircom Server Instance is not running.")
    nav.Logger.log("\tNOTE: The evaluation edition automatically shuts down periodically.")
    nav.Logger.exit_with_faircom_error(e)
  
  # Try to connect to the database.
  # If the database does not exist, create it and then connect to it.
  try:
    my_database.connect(my_server) # try to connect to the database.
    nav.Logger.log("\tConnected to FairCom Database " + my_database.database_name + ".")

  except nav.DatabaseError as e:
      # The 'connect' call failed.
      if e.error_code == 101:
        nav.Logger.log("\tDatabase " + my_database.database_name + " does not exist.")
        try:
          my_database.create() # create the database
          nav.Logger.log("\tCreated FairCom Database " + my_database.database_name + " in Faircom Server " + my_server.server_name + ".")
        except nav.DatabaseError as e:
          nav.Logger.log("\tCould not create Faircom Database " + my_database.database_name + " with path " + my_database.database_path + ".")
          nav.Logger.exit_with_faircom_error(e)
        try:
          my_database.connect(my_server)
          nav.Logger.log("\tConnected to FairCom Database " + my_database.database_name + ".")
        except nav.DatabaseError as e:
          nav.Logger.log("\tCould not connect to Faircom Database " + my_database.database_name + ".")
          nav.Logger.exit_with_faircom_error(e)
      else:
        nav.Logger.log("\tCould not connect to Faircom Database " + my_database.database_name + ".")
        nav.Logger.exit_with_faircom_error(e)


# ================================================================================
#
# Open the table. If it doesn't exist, create it. 
#

def open_or_create_table():
  nav.Logger.log("OPEN")
 
  # Try to open the table.  If it does not open, try to create it and then open it.
  try:
    my_table.open(my_database)
    nav.Logger.log("\tOpened " + my_table.table.table_name + " table in " + str(my_table.table.get_open_mode()) + " mode.")

  except nav.DatabaseError as e:
    if e.error_code == 4023:
      nav.Logger.log("\tTable " + my_table.table.table_name + " does not exist.")
      try:
        my_table.create(my_database) # create the table
        nav.Logger.log("\tCreated table " + my_table.table.table_name + ".")
      except nav.DatabaseError as e:
        nav.Logger.log("\tCould not create " + my_table.table.table_name + " table.")
        nav.Logger.exit_with_faircom_error(e)
      try:
        my_table.open(my_database)
        nav.Logger.log("\tOpened " + my_table.table.table_name + " table in " + str(my_table.table.get_open_mode()) + " mode.")
      except nav.DatabaseError as e:
        nav.Logger.log("\tCould not open " + my_table.table.table_name + " table.")
        nav.Logger.exit_with_faircom_error(e)
    else:
      nav.Logger.log("\tCould not open " + my_table.table.table_name + " table.")
      nav.Logger.exit_with_faircom_error(e)
 

# ================================================================================
#
# Delete all records under locking control in the Athlete table
#

def delete_records():

  nav.Logger.log("PROCESS")

  try:
    rec = my_table.table.new_record_buffer()  # type = CTRecord
    count = rec.get_record_count()

    # Enable session-wide locking - blocking WRITE locks
    my_server.lock(nav.LockModeEnum.BLOCKING_WRITE)
    my_server.tran_begin()

    found = rec.first()   # read first record
    while found is True:
      rec.delete()
      found = rec.next()

    my_server.tran_commit() # commit the transaction, release all locks, and disable session-wide locking
    nav.Logger.log("\tDeleted all " + str(count) + " existing records.")

  except nav.DatabaseError as e:
    my_server.tran_rollback() # roll the transaction back, release all locks, and disable session-wide locking
    nav.Logger.exit_with_faircom_error(e)


# ================================================================================
#
# Insert records into the Athlete table 
#

def add_records():
  try:
    rec = my_table.table.new_record_buffer()

    my_server.tran_begin()

    for athlete in my_table.test_data:
      rec.clear()

      rec.set_field_value( my_table.NAME_FIELD,             athlete["Name"])
      rec.set_field_value( my_table.RANKING_FIELD,          athlete["Ranking"])
      rec.set_field_value( my_table.BIRTH_DATE_FIELD,       athlete["BirthDate"])
      rec.set_field_value( my_table.PLAYER_NUMBER_FIELD,    athlete["PlayerNumber"])
      rec.set_field_value( my_table.LIVED_PAST_2000_FIELD,  athlete["LivedPast2000"])
      rec.set_field_value( my_table.EARNINGS_FIELD,         athlete["Earnings"])
      rec.set_field_value( my_table.FAVORITE_SAYING_FIELD,  athlete["FavoriteSaying"])

      rec.write()    # add record

    my_server.tran_commit()

    nav.Logger.log("\tAdded " + str(rec.get_record_count()) + " new athlete records.")

  except nav.DatabaseError as e:
    my_server.tran_rollback()
    nav.Logger.exit_with_faircom_error(e)


# ================================================================================
#
# Update a filtered subset of records under locking control in the Athlete table. 
#

def update_records():
  earningsField = my_table.EARNINGS_FIELD # type = int, a field number

  try:
    rec = my_table.table.new_record_buffer()  # type = CTRecord

    # Define subset of records to update
    rec.set_filter("month(birthDate) == 1 AND playerNumber >= 23")
    filter_expression=rec.get_filter()

    # Enable session-wide locking - blocking WRITE locks
    my_server.lock(nav.LockModeEnum.BLOCKING_WRITE)

    my_server.tran_begin()

    found = rec.first()       # Read first record in subset
    while found is True:
      earnings=rec.get_field_value(earningsField)
      rec.set_field_value(earningsField, earnings * Decimal(2.0))
      rec.write()
      found = rec.next()    # Read next record

    my_server.tran_commit() # commit the transaction, release all locks, and disable session-wide locking

    rec.set_filter("")         # Clear the filter

    nav.Logger.log("\tUpdated athlete earnings by 2x \n\tWHERE " + filter_expression )

  except nav.DatabaseError as e:
    my_server.tran_rollback() # roll the transaction back, release all locks, and disable session-wide locking
    nav.Logger.exit_with_faircom_error(e)
  

# ================================================================================
#
# Display all records in the Athlete table. 
#

def display_records():

  nav.Logger.log("REPORT")

  try:
    rec = my_table.table.new_record_buffer()  # type = CTRecord

    # Set the collation / sort order of the record read-out by selecting the index on the "name" field
    rec.set_default_index(my_table.NAME_INDEX_NAME)

    found = rec.first()     # read first record

    while found is True:
      name = rec.get_field_value(my_table.NAME_FIELD)
      earnings = rec.get_field_value(my_table.EARNINGS_FIELD)

      nav.Logger.log("\t\t" + name.ljust(20) + str(earnings).rjust(20)) 

      found = rec.next()    # read next record

  except nav.DatabaseError as e:
    nav.Logger.exit_with_faircom_error(e)


# ================================================================================
#
# Delete Athlete table (records, definition, data and index files)
#

def delete_table():
  try:
    my_table.table.delete()
    nav.Logger.log("\tDeleted table '%s'." % (my_table.table.table_name))
  except nav.DatabaseError as e:
    nav.Logger.exit_with_faircom_error(e)

# ================================================================================
#
# Delete Database (all tables, records, etc.)
#

def delete_database():
  try:
    my_database.delete()
    nav.Logger.log("\tDeleted FairCom Database " + my_database.database_name + " from Faircom Server " + my_database.faircom_server.server_name + ".")
  except nav.DatabaseError as e:
    nav.Logger.log("\tCould not delete FairCom Database " + my_database.database_name + " from Faircom Server " + my_database.faircom_server.server_name + ".")
    nav.Logger.exit_with_faircom_error(e)

# ================================================================================
#
# Disconnect from database
#

def disconnect():
  nav.Logger.log("DISCONNECT")

  try:
    my_table.table.close()
    nav.Logger.log("\tClosed table " + my_table.table.table_name + ".")
    my_database.disconnect()
    nav.Logger.log("\tDisconnected from FairCom Database " + my_database.database_name + ".")
    my_server.disconnect()
    nav.Logger.log("\tLogged out of FairCom Server Instance " + my_server.server_name + ".")
  except nav.DatabaseError as e:
    nav.Logger.log("\tCould not close/disconnect.")
    nav.Logger.exit_with_faircom_error(e)


# ************************************************************************************
# ************************************************************************************
#
#  Athlete Table Class
#
# Encapsulates the Athlete Table created in the FairCom database
# - The table must be opened before it can be used.
# - First call .open() to open the table.
# - If the table cannot be opened, call .create() to create it, and then call .Open().
# - Once the table is open, all methods work -- except .create().
#
# - An application can instantiate many of these objects 
#   to simultaneously open the Athlete table on the same database 
#   or on different databases on different Faircom Servers.
#
# Contains the following
#   - FairCom Objects for managing database session, table, and last exception
#   - Methods to open, close, create, and delete the Athlete table
#   - Method to get a new record buffer object to work with Athlete table data
#   - Methods to begin, commit, and rollback transactions on the table
#
# Special features
#  - Each instance of AthleteTable represents a connection to the Athlete table. 
#  - This makes it is easy to open multiple, simultaneous connection sessions 
#    to the same Athlete table in the same FairCom Server and Database.
#  - It also makes it easy to simultaneously open or create different Athlete tables 
#    in different databases or on different Servers.

class AthleteTable(): 
  __table = None # I will be an instance of the FairCom nav Table class.
  
  def __init__(self, table_name="athlete", table_password=""): # Give me strings
    self.__table=nav.Table(table_name, table_password)

  @property
  def table(self):
    return self.__table

  # Identity Field Info
  identity_field_information = { "FieldName": "id", "Seed": 100, "Increment": 2 }
  # This optional item is a single {dictionary} which MUST have all three items shown above, if it is used.


  # Index Info - we will have an index for the "name" and the "ranking" fields.  Each one gets one key segment.
  NAME_INDEX_NAME = "athlete_name_idx"
  RANK_INDEX_NAME = "athlete_rank_idx"
  index_information = [
    { "IndexName": NAME_INDEX_NAME, "IndexType": nav.FIXED_LENGTH_KEY, "AllowDuplicates": True, "AllowNullKeys": True, \
      "SegmentList": [{"FieldName": "name", "Flags": nav.FIELD_NUMBER}] },
    { "IndexName": RANK_INDEX_NAME, "IndexType": nav.FIXED_LENGTH_KEY, "AllowDuplicates": True, "AllowNullKeys": False, \
      "SegmentList": [{"FieldName": "ranking", "Flags": nav.FIELD_NUMBER}] }
  ]
  # This optional item is a [list] of {dictionaries}, where each dictionary defines one index.
  #   Each index dict contains the index name, type, two flags, and a LIST of one or more segment-defining dicts.
  #     Each segment-defining dict contains the name of the field and a Flags integer.


  # Athlete Table Field/Column Definition
  field_defs =  [
    {  "Name": "id",              "Type": nav.FieldTypeEnum.INT64_SIGNED,     "NotNull": True  }, 
    {  "Name": "name",            "Type": nav.FieldTypeEnum.STRING_FIXED_LENGTH,    "Length": 30     },  
    {  "Name": "ranking",         "Type": nav.FieldTypeEnum.INT16_SIGNED,       "NotNull": True  },  
    {  "Name": "birthDate",       "Type": nav.FieldTypeEnum.DATE,                        },  
    {  "Name": "playerNumber",    "Type": nav.FieldTypeEnum.DECIMAL,     "Scale": 6       },  
    {  "Name": "livedPast2000",   "Type": nav.FieldTypeEnum.BOOLEAN,                        },  
    {  "Name": "earnings",        "Type": nav.FieldTypeEnum.CURRENCY,                    },  
    {  "Name": "favoriteSaying",  "Type": nav.FieldTypeEnum.STRING,                  }, 
  ]
  # This REQUIRED item is a [list] of {dictionaries}, where each dictionary defines one column / field in the table.
  #   Each field dict must have a name and type, and can have other optional items.
  # You must specify at least one field/column when creating a table.


  # Athlete Field Numbers
  ID_FIELD = 0
  NAME_FIELD = 1
  RANKING_FIELD = 2
  BIRTH_DATE_FIELD = 3
  PLAYER_NUMBER_FIELD = 4
  LIVED_PAST_2000_FIELD = 5
  EARNINGS_FIELD = 6
  FAVORITE_SAYING_FIELD = 7
  

  # Test data to store in the table.  add_records() uses this.
  test_data = [
    { "Name": "Michael Jordan",     "Ranking": 1,              "BirthDate": date(1963, 2, 17),
      "PlayerNumber": 23,           "LivedPast2000": True,     "Earnings": 1700000000,
      "FavoriteSaying": "There is no 'i' in team but there is in win.",  },

    { "Name": "Babe Ruth",          "Ranking": 2,              "BirthDate": date(1895, 2, 6),
      "PlayerNumber": 3,            "LivedPast2000": False,    "Earnings": 800000,
      "FavoriteSaying": "Every strike brings me closer to the next home run.",    },
    
    { "Name": "Muhammad Ali",       "Ranking": 3,              "BirthDate": date(1942, 1, 17),
      "PlayerNumber": 1,            "LivedPast2000": True,     "Earnings": 60000000,
      "FavoriteSaying": "Float like a butterfly, sting like a bee.",    },
    
    { "Name": "Pelé",               "Ranking": 4,              "BirthDate": date(1940, 10, 23),
      "PlayerNumber": 10,           "LivedPast2000": True,     "Earnings": 115000000,
      "FavoriteSaying": "Everything is practice.",    },
    
    { "Name": "Wayne Gretzky",      "Ranking": 5,              "BirthDate": date(1961, 1, 26),
      "PlayerNumber": 99,           "LivedPast2000": True,     "Earnings": 1720000,
      "FavoriteSaying": "You miss 100 percent of the shots you never take.",    },
    
    { "Name": "Michael Schumacher", "Ranking": 6,              "BirthDate": date(1969, 1, 3),
      "PlayerNumber": 1,            "LivedPast2000": True,     "Earnings": 990000000,
      "FavoriteSaying": "Once something is a passion, the motivation is there.",    },
  ]


  def create(self, database):
    # 'field_defs' is required, 'index_information' and 'identity_field_information' are optional.
    self.__table.create(database, field_defs=self.field_defs, index_information=self.index_information, identity_field_information=self.identity_field_information)
 
  def open(self, database):
    self.__table.open(database)


# ************************************************************************************
# ************************************************************************************


# Login information
faircom_server_name = "FAIRCOMS"
database_name = "ctreeSQL"
user_name = "ADMIN"
password = "ADMIN"
athlete_table_name = "athlete"

# Tutorial Objects
my_server = nav.FaircomServer(faircom_server_name, user_name, password)
my_database = nav.FaircomDatabase(database_name)
my_table = AthleteTable(athlete_table_name)

nav.Logger.log("\tTUTORIAL 1 for python.nav")

connect()

open_or_create_table()

delete_records()

add_records()

update_records()

display_records()

if "-cleanup" in sys.argv:  # Do the command-line arguments contain the "-cleanup" flag?
  nav.Logger.log("CLEANUP")
  delete_table()
  delete_database()

disconnect()

input("\nPress <ENTER> key to exit . . .")

