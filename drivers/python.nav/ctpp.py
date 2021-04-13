# -*- coding: Latin-1 -*-

import ctypes
import sys
import ctdb
import ctdb_const
import enum

from datetime import *
from decimal import *






from datetime import date

def PyStringToCTDate(theString, DateType):
  value = ctypes.c_uint32()
  retval = ctdb.StringToDate(theString, DateType, ctypes.byref(value))
  if retval == 0:
    return value.value 

def PyDateToCTDate(theDate):
  return date.toordinal(theDate)-620606

def IntsToCTDate(year, month, day):
  value = ctypes.c_uint32()
  retval = ctdb.DatePack(ctypes.byref(value), year, month, day)
  if retval == 0:
    return value.value 

def CTDateToPyString(theDate, DateType):
  return ctdb.DateToString(theDate, DateType)

def CTDateToPyDate(theDate):
  return date.fromordinal(theDate+620606)





def create_string_buffer(length):
    return ctypes.create_string_buffer(length)

def missing_(length):
    pass

class CTSession:

    def __init__(self, sessionType=ctdb_const.SessionTypeEnum.NAV_SQL): 
        if type(sessionType)!=ctdb_const.SessionTypeEnum:
            raise ctdb.DatabaseError( "The sessionType parameter must be of type 'SessionTypeEnum'.  You provided a "+str(type(sessionType))+".", 1) 
        self.handle = ctdb.AllocSession(sessionType.value) 

    def Logon(self, dbEngine, user, password): 
        return ctdb.Logon(self.handle, dbEngine, user, password)

    def Logout(self):
        return ctdb.Logout(self.handle)

    def GetError(self):
        return ctdb.GetError(self.handle)

    def ClearError(self):
        return ctdb.ClearError(self.handle)

    def IsTransActive(self):
        return ctdb.IsTransActive(self.handle)

    def Begin(self):
        return ctdb.Begin(self.handle)

    def Commit(self):
        return ctdb.Commit(self.handle)

    def Abort(self):
        return ctdb.Abort(self.handle)

    def IsLockActive(self):
        return ctdb.IsLockActive(self.handle)

    def GetLockMode(self):
        return ctdb.GetLockMode(self.handle)

    def Lock(self, lockMode):
        if type(lockMode)!=ctdb_const.LockModeEnum:
            raise ctdb.DatabaseError( "The lockMode parameter must be of type 'LockModeEnum'.  You provided a "+str(type(lockMode))+".", 1) 
        return ctdb.Lock(self.handle, lockMode.value)

    def Unlock(self):
        return ctdb.Unlock(self.handle)

    def GetTransactionMode(self):
        return ctdb.GetTransactionMode(self.handle)

    def SetTransactionMode(self, mode):
        return ctdb.SetTransactionMode(self.handle, mode)

    def GetAutoCommit(self, mode):
        return ctdb.GetAutoCommit(self.handle)

    def SetAutoCommit(self, flag=True):
        return ctdb.SetAutoCommit(self.handle, flag)

    def Create(self, dbEngine, user, password):
        return ctdb.CreateSession(self.handle, dbEngine, user, password)

    def GetServerName(self):
        return ctdb.GetServerName(self.handle)

    def GetUserLogonName(self):
        return ctdb.GetUserLogonName(self.handle)

    def GetPassword(self):
        return ctdb.GetUserPassword(self.handle)

    def GetParam(self, ParamType):
        return ctdb.GetSessionParams(self.handle, ParamType)

    def SetParam(self, ParamType, value):
        return ctdb.SetSessionParams(self.handle, ParamType, value)

    def IsActive(self):
        return ctdb.IsActiveSession(self.handle)

    def GetPath(self):
        buf = create_string_buffer(256)
        ctdb.GetSessionPath(self.handle, buf, 256)
        return buf.value

    def SetPath(self, Path):
        return ctdb.SetSessionPath(self.handle, Path)

    def FirstDatabase(self):
        Name = create_string_buffer(256)
        Path = create_string_buffer(256)
        ctdb.FirstDatabase(self.handle, Name, 256, Path, 256)
        return (Name.value.decode(ctdb_const.CTREE_CHAR_ENCODING), Path.value.decode(ctdb_const.CTREE_CHAR_ENCODING))

    def NextDatabase(self):
        Name = create_string_buffer(256)
        Path = create_string_buffer(256)
        ctdb.NextDatabase(self.handle, Name, 256, Path, 256)
        return (Name.value.decode(ctdb_const.CTREE_CHAR_ENCODING), Path.value.decode(ctdb_const.CTREE_CHAR_ENCODING))

    def FindDatabase(self, Name, Path_=None):
        Path = create_string_buffer(256)
        if type(Path_) == str:
            Path.value = Path_.encode(ctdb_const.CTREE_CHAR_ENCODING)
        retval = ctdb.FindDatabase(self.handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), Path, 256)
        if retval == 0:
            return Path.value.decode(ctdb_const.CTREE_CHAR_ENCODING)
        else:
            return None

    def DisconnectAll(self):
        return ctdb.DisconnectAll(self.handle)

    def CreateDatabase(self, Name, Path=""):
        return ctdb.CreateDatabase(self.handle, Name, Path)

    def AddDatabase(self, Name, Path=""):
        return ctdb.AddDatabase(self.handle, Name, Path)

    def DeleteDatabase(self, Name):
        return ctdb.DeleteDatabase(self.handle, Name)

    def DropDatabase(self, Name):
        return ctdb.DropDatabase(self.handle, Name)

    def GetDatabaseUID(self, Name, uid):
        return ctdb.GetDatabaseUID(self.handle, Name, uid)


    def SetLogonOnly(self, flag):
        return ctdb.SetLogonOnly(self.handle, flag)

    def GetLogonOnly(self):
        return ctdb.GetLogonOnly(self.handle)

    def GetDatabaseCount(self):
        return ctdb.GetDatabaseCount(self.handle)

    def SetSessionType(self, SessionType):
        if type(SessionType)!=ctdb_const.SessionTypeEnum:
            raise ctdb.DatabaseError( "The SessionType parameter must be of type 'SessionTypeEnum'.  You provided a "+str(type(SessionType))+".", 1) 
        return ctdb.SetSessionType(self.handle, SessionType)

    def GetSessionType(self):
        return ctdb.GetSessionType(self.handle)

    def SetCurrentNodeName(self, NodeName):
        return ctdb.SetCurrentNodeName(self.handle, NodeName)


    def IsSQLServer(self):
        return ctdb.IsSQLServer(self.handle)

    def SetExclusive(self, flag):
        return ctdb.SetSessionExclusive(self.handle, flag)

    def IsExclusive(self):
        return ctdb.IsSessionExclusive(self.handle)


    def BeginImpersonation(self, taskId):
        return ctdb.BeginImpersonation(self.handle, taskId)

    def EndImpersonation(self):
        return ctdb.EndImpersonation(self.handle)

    def ServerDateTime(self):
        return ctdb.ServerDateTime(self.handle)

    def SetLogPath(self, path):
        return ctdb.SetLogPath(self.handle, path)

    def SetStatusLogPath(self, path):
        return ctdb.SetStatusLogPath(self.handle, path)

    def SetTempPath(self, path):
        return ctdb.SetTempPath(self.handle, path)

    def __del__(self):
        ctdb.FreeSession(self.handle)

class CTDatabase:
    def __init__(self, ctSession):
        self.session = ctSession
        self.handle = ctdb.AllocDatabase(ctSession.handle) 

    def IsActive(self):
        return ctdb.IsActiveDatabase(self.handle)

    def Connect(self, Name):
        return ctdb.Connect(self.handle, Name)

    def Create(self, Name, Path):
        return ctdb.CreateDatabase(self.handle, Name, Path)

    def Disconnect(self):
        return ctdb.Disconnect(self.handle)

    def FirstTable(self):
        Name = create_string_buffer(256)
        Path = create_string_buffer(256)
        retval = ctdb.FirstTable(self.handle, Name, 256, Path, 256)
        if retval == 0:
            return (Name.value.decode(ctdb_const.CTREE_CHAR_ENCODING), Path.value.decode(ctdb_const.CTREE_CHAR_ENCODING))
        elif retval == 101:
            return None

    def NextTable(self):
        Name = create_string_buffer(256)
        Path = create_string_buffer(256)
        retval = ctdb.NextTable(self.handle, Name, 256, Path, 256)
        if retval == 0:
            return (Name.value.decode(ctdb_const.CTREE_CHAR_ENCODING), Path.value.decode(ctdb_const.CTREE_CHAR_ENCODING))
        elif retval == 101:
            return None

    def FindTable(self, Name):
        Path = create_string_buffer(256)
        retval = ctdb.FindTable(self.handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), Path, 256)
        if retval == 0:
            return Path.value.decode(ctdb_const.CTREE_CHAR_ENCODING)
        elif retval == 101:
            return None

    def AddTable(self, Name, Path):
        return ctdb.AddTable(self.handle, Name, Path)

    def DeleteTable(self, Name, Password):
        return ctdb.DeleteTable(self.handle, Name, Password)

    def DropTable(self, Name):
        return ctdb.DropTable(self.handle, Name)

    def GetTableUID(self, Name):
        uid = ctypes.c_uint32()
        retval = ctdb.GetTableUID(self.handle, Name, ctypes.byref(uid))
        if retval == 0:
            return uid.value
        elif retval == 101:
            return None


    def GetPath(self):
        return ctdb.GetDatabasePath(self.handle)

    def GetName(self):
        return ctdb.GetDatabaseName(self.handle)

    def CloseAll(self):
        return ctdb.CloseAll(self.handle)

    def GetTableCount(self):
        return ctdb.GetTableCount(self.handle)

    def GetDefaultSqlTableOwner(self):
        return ctdb.GetDefaultSqlTableOwner(self.handle)

    def SetDefaultSqlTableOwner(self, owner):
        return ctdb.SetDefaultSqlTableOwner(self.handle, owner)

    def IsSQL(self):
        return ctdb.IsSQLDatabase(self.handle)

    def SetExclusive(self, flag):
        return ctdb.SetDatabaseExclusive(self.handle, flag)

    def IsExclusive(self):
        return ctdb.IsDatabaseExclusive(self.handle)

    def RenameTable(self, OldName, NewName):
        return ctdb.RenameTable(self.handle, OldName, NewName)


class CTTable:

    def __init__(self, parentObject):
        self.parent = parentObject
        self.parentHandle = parentObject.handle
        self.handle = ctdb.AllocTable(parentObject.handle)

    def IsActive(self):
        return ctdb.IsActiveTable(self.handle)

    def GetName(self):
        return ctdb.GetTableName(self.handle).decode(ctdb_const.CTREE_CHAR_ENCODING)

    def GetPath(self):
        return ctdb.GetTablePath(self.handle).decode(ctdb_const.CTREE_CHAR_ENCODING)

    def GetDataExtension(self):
        return ctdb.GetTableExtension(self.handle).decode(ctdb_const.CTREE_CHAR_ENCODING)

    def GetIndexExtension(self):
        return ctdb.GetIndexExtension(self.handle).decode(ctdb_const.CTREE_CHAR_ENCODING)

    def GetOpenMode(self):
        return ctdb.GetTableOpenMode(self.handle)

    def GetCreateMode(self):
        return ctdb.GetTableCreateMode(self.handle)

    def GetDataDefaultExtentSize(self):
        return ctdb.GetTableDefaultDataExtentSize(self.handle)

    def GetIndexDefaultExtentSize(self):
        return ctdb.GetTableDefaultIndexExtentSize(self.handle)

    def GetPassword(self):
        return ctdb.GetTablePassword(self.handle)

    def GetGroupid(self):
        return ctdb.GetTableGroupid(self.handle)

    def GetPermission(self):
        return ctdb.GetTablePermission(self.handle)

    def SetPath(self, Path):
        return ctdb.SetTablePath(self.handle, Path)

    def SetDataExtension(self, Ext):
        return ctdb.SetTableExtension(self.handle, Ext)

    def SetIndexExtension(self, Ext):
        return ctdb.SetIndexExtension(self.handle, Ext)

    def SetDataDefaultExtentSize(self, size):
        return ctdb.SetTableDefaultDataExtentSize(self.handle, size)

    def SetIndexDefaultExtentSize(self, size):
        return ctdb.SetTableDefaultIndexExtentSize(self.handle, size)

    def SetPassword(self, Password):
        return ctdb.SetTablePassword(self.handle, Password)

    def SetGroupid(self, Groupid):
        return ctdb.SetTableGroupid(self.handle, Groupid)

    def SetPermission(self, Permmask):
        return ctdb.SetTablePermission(self.handle, Permmask)

    def Create(self, Name, CreateMode):
        return ctdb.CreateTable(self.handle, Name, CreateMode)

    def Open(self, Name, OpenMode):
        if type(OpenMode)!=ctdb_const.OpenModeEnum:
            raise ctdb.DatabaseError( "The OpenMode parameter must be of type 'OpenModeEnum'.  You provided a "+str(type(OpenMode))+".", 1) 
        return ctdb.OpenTable(self.handle, Name, OpenMode.value)

    def Close(self):
        return ctdb.CloseTable(self.handle)

    def Remove(self):
        return ctdb.RemoveTable(self.handle)

    def GetFieldCount(self):
        return ctdb.GetTableFieldCount(self.handle)

    def AddField(self, Name, FieldType, Length):
        if type(FieldType)!=ctdb_const.FieldTypeEnum:
            raise ctdb.DatabaseError( "The FieldType parameter must be of type 'FieldTypeEnum'.  You provided a "+str(type(FieldType))+".", 1) 
        fieldHandle = ctdb.AddField(self.handle, Name, FieldType.value, Length)
        return CTField(fieldHandle)

    def InsertField(self, BeforeFieldNumberOrName, Name, FieldType, Length):
        if type(FieldType)!=ctdb_const.FieldTypeEnum:
            raise ctdb.DatabaseError( "The FieldType parameter must be of type 'FieldTypeEnum'.  You provided a "+str(type(FieldType))+".", 1) 
        if type(BeforeFieldNumberOrName) == str:
            return ctdb.InsFieldByName(self.handle, BeforeFieldNumberOrName, Name, FieldType.value, Length)
        if type(BeforeFieldNumberOrName) == int:
            return ctdb.InsField(self.handle, BeforeFieldNumberOrName, Name, FieldType.value, Length)
        if type(BeforeFieldNumberOrName) == CTField:
            return ctdb.InsFieldByName(self.handle, BeforeFieldNumberOrName.GetName(), Name, FieldType.value, Length)

    def DelField(self, FieldNumberOrName):
        self.DeleteField(FieldNumberOrName)

    def DeleteField(self, FieldNumberOrName):
        if type(FieldNumberOrName) == str:
            return ctdb.DelFieldByName(self.handle, FieldNumberOrName)
        if type(FieldNumberOrName) == int:
            return ctdb.DelField(self.handle, FieldNumberOrName)
        if type(FieldNumberOrName) == CTField:
            return ctdb.DelFieldByName(self.handle, FieldNumberOrName.GetName())

    def MoveField(self, FieldNumberOrName, newNumber):
        if type(FieldNumberOrName) == str:
            fieldHandle = ctdb.GetFieldByName(self.handle, FieldNumberOrName)
        elif type(FieldNumberOrName) == int:
            fieldHandle = ctdb.GetField(self.handle, FieldNumberOrName)
        elif type(FieldNumberOrName) == CTField:
            fieldHandle = FieldNumberOrName.handle
        return ctdb.MoveField(fieldHandle, newNumber)

    def FieldExists(self, FieldName):
        if type(FieldName) == str:
            fieldHandle = ctdb.GetFieldByName(self.handle, FieldName, False)
        return fieldHandle != None

    def GetField(self, FieldNumberOrName):
        if type(FieldNumberOrName) == str:
            fieldHandle = ctdb.GetFieldByName(self.handle, FieldNumberOrName)
        elif type(FieldNumberOrName) == int:
            fieldHandle = ctdb.GetField(self.handle, FieldNumberOrName)
        if fieldHandle == None:
            raise Exception( "GetField failed for " + FieldNumberOrName)
        return CTField(fieldHandle)

    def GetFieldNumber(self, FieldName):
        return ctdb.GetFieldNumber(self.handle, FieldName)

    def GetIndexCount(self):
        return ctdb.GetTableIndexCount(self.handle)

    def AddIndex(self, name, KeyType, AllowDuplicates, NullFlag):
        indexHandle = ctdb.AddIndex(self.handle, name, KeyType, AllowDuplicates, NullFlag)
        return CTIndex(indexHandle)

    def DelIndex(self, IndexNumber):
        return ctdb.DelIndex(self.handle, IndexNumber)

    def GetIndex(self, IndexNumberOrName):
        if type(IndexNumberOrName) == str:
            indexHandle = ctdb.GetIndexByName(self.handle, IndexNumberOrName)
        if type(IndexNumberOrName) == int:
            indexHandle = ctdb.GetIndex(self.handle, IndexNumberOrName)
        return CTIndex(indexHandle)

    def GetIndexNbrByName(self, IndexName):
        return ctdb.GetIndexNbrByName(self.handle, IndexName)

    def GetSegment(self, pIndex, SegNumber):
        return ctdb.GetSegment(self.handle, pIndex, SegNumber)


    def AddSegment(self, Index, Field, SegMode):
        if type(Index) == str or type(Index) == int:
            indexHandle = self.GetIndex(Index).handle
        elif type(Index) == CTIndex:
            indexHandle = Index.handle

        if type(Field) == str or type(Field) == int:
            fieldHandle = self.GetField(Field).handle
        elif type(Field) == CTField:
            fieldHandle = Field.handle

        return ctdb.AddSegment(indexHandle, fieldHandle, SegMode)



    def InsertSegment(self, pIndex, BeforeSegment, Field, SegMode):
        return ctdb.InsertSegment(self.handle, pIndex, BeforeSegment, Field, SegMode)

    def DelSegment(self, IndexNUmber, SegNumber):
        return ctdb.DelSegment(self.handle, IndexNUmber, SegNumber)

    def DelSegment(self, IndexName, SegNumber):
        return ctdb.DelSegment(self.handle, IndexName, SegNumber)

    def Alter(self, Action):
        return ctdb.AlterTable(self.handle, Action)

    def ResetAll(self):
        return ctdb.ResetAll(self.handle)

    def HasNullFieldSupport(self):
        return ctdb.HasNullFieldSupport(self.handle)

    def GetIndexByUID(self, uid):
        indexHandle = ctdb.GetIndexByUID(self.handle, uid)
        return CTIndex(indexHandle)

    def HasRecbyt(self):
        return ctdb.HasRecbyt(self.handle)

    def HasRowid(self):
        return ctdb.HasRowid(self.handle)

    def UnlockTable(self):
        return ctdb.UnlockTable(self.handle)

    def UpdateCndxIndex(self, indexnbr, cndexpr):
        return ctdb.UpdateCndxIndex(self.handle, indexnbr, cndexpr)

    def UpdateCndxIndex(self, indexname, cndexpr):
        return ctdb.UpdateCndxIndex(self.handle, indexname, cndexpr)

    def GetCndxIndex(self, indexnbr, cndexpr):
        return ctdb.GetCndxIndex(self.handle, indexnbr, cndexpr)

    def GetCndxIndex(self, indexname, cndexpr):
        return ctdb.GetCndxIndex(self.handle, indexname, cndexpr)




    def GetPadChar(self):
        Padchar = ctypes.c_int()
        Dmlchar = ctypes.c_int()
        retval = ctdb.GetPadChar(self.handle, ctypes.byref(Padchar), ctypes.byref(Dmlchar))
        return [Padchar.value, Dmlchar.value]

    def SetPadChar(self, padchar, dmlchar):
        return ctdb.SetPadChar(self.handle, padchar, dmlchar)

    def UpdatePadChar(self, padchar, dmlchar, rebuild=False):
        return ctdb.UpdatePadChar(self.handle, padchar, dmlchar, rebuild)

    def UpdateCreateMode(self, mode):
        return ctdb.UpdateCreateMode(self.handle, mode)

    def HasDelField(self):
        return ctdb.HasDelField(self.handle)

    def SetIndexFilename(self, IndexOrNumberOrName, path, filename):
        if type(IndexOrNumberOrName) == str or type(IndexOrNumberOrName) == int:
            indexHandle = self.GetIndex(IndexOrNumberOrName).handle
        if type(IndexOrNumberOrName) == CTIndex:
            indexHandle = IndexOrNumberOrName.handle
        return ctdb.SetIndexFilename(indexHandle, path, filename)

    def GetIndexFilename(self, IndexOrNumberOrName):
        if type(IndexOrNumberOrName) == str or type(IndexOrNumberOrName) == int:
            indexHandle = self.GetIndex(IndexOrNumberOrName).handle
        if type(IndexOrNumberOrName) == CTIndex:
            indexHandle = IndexOrNumberOrName.handle
        return ctdb.GetIndexFilename(indexHandle)

    def GetDatno(self):
        return ctdb.GetDatno(self.handle)


    def GetIdxno(self, IndexOrNumberOrName):
        if type(IndexOrNumberOrName) == str or type(IndexOrNumberOrName) == int:
            indexHandle = self.GetIndex(IndexOrNumberOrName).handle
        if type(IndexOrNumberOrName) == CTIndex:
            indexHandle = IndexOrNumberOrName.handle
        return ctdb.GetIdxno(indexHandle)



    def ClearAllFieldDefaultValue(self):
        return ctdb.ClearAllFieldDefaultValue(self.handle)




    def GetStatus(self):
        return ctdb.GetTableStatus(self.handle)



    def GetOwner(self):
        return ctdb.GetTableOwner(self.handle)

    def SetOwner(self, owner):
        return ctdb.SetTableOwner(self.handle, owner)

    def Rebuild(self, mode):
        return ctdb.RebuildTable(self.handle, mode)












    def Clone(self, Name):
        clone_table = CTTable(self.parentHandle)
        ctdb.CloneTable(clone_table.handle, Name, self.handle)
        return clone_table










    def GetFullTextIndexCount(self):
        return ctdb.GetTableFTICount(self.handle)

    def AddFullTextIndex(self, name):
        fti_handle = ctdb.AddFTI(self.handle, name)
        return CTFullTextIndex(fti_handle)

    def DelFullTextIndex(self, IndexNumberOrName):
        return ctdb.DelFTI(self.handle, Number)

    def GetFullTextIndex(self, IndexNumberOrName=0):
        fti_handle = ctdb.GetFTI(self.handle, IndexNumberOrName)
        return CTFullTextIndex(fti_handle)


    def NumberOfKeyEntries(self, IndexNumber):
        return ctdb.NumberOfKeyEntries(self.handle, IndexNumber)

    def SetIdentityField(self, FieldName, Seed, Increment):
        return ctdb.SetIdentityField(self.handle, FieldName, Seed, Increment)


class CTResource:
    def __init__(self, ctTable, type_=0, number=0, name=None):
        self.table = ctTable
        self.tableHandle = ctTable.handle
        self.handle = ctdb.AllocResource(ctTable.handle, type_, number, name)
        self.allocated = True

    def __del__(self):
        if self.allocated:
            self.allocated = False
            ctdb.FreeRecord(self.handle)

    def Close(self):
        if self.allocated:
            self.allocated = False
            ctdb.FreeRecord(self.handle)

    def Unlock(self):
        return ctdb.UnlockResource(self.handle)

    def Add(self, data, size):
        return ctdb.AddResource(self.handle, data, size)

    def Delete(self):
        return ctdb.DeleteResource(self.handle)

    def Update(self, data, size):
        return ctdb.UpdateResource(self.handle, data, size)

    def First(self, lock=False):
        return ctdb.FirstResource(self.handle, lock)

    def Next(self, lock=False):
        return ctdb.NextResource(self.handle, lock)

    def Find(self, type, number, lock=False):
        return ctdb.FindResourceByName(self.handle, name, lock)

    def Find(self, name, lock=False):
        return ctdb.FindResourceByName(self.handle, name, lock)

    def IsLocked(self):
        return ctdb.IsResourceLocked(self.handle)

    def GetType(self):
        return ctdb.GetResourceType(self.handle)

    def SetType(self, type_):
        return ctdb.SetResourceType(self.handle, type_)

    def GetNumber(self):
        return ctdb.GetResourceNumber(self.handle)

    def SetNumber(self, number):
        return ctdb.SetResourceNumber(self.handle, number)

    def GetName(self):
        return ctdb.GetResourceName(self.handle)

    def SetName(self, name):
        return ctdb.SetResourceName(self.handle, name)

    def GetDataLength(self):
        return ctdb.GetResourceDataLength(self.handle)

    def GetData(self):
        return ctdb.GetResourceData(self.handle)

    def SetData(self, data, size):
        return ctdb.SetResourceData(self.handle, data, size)


class CTRecord:
    def __init__(self, ctTable):
        self.table = ctTable
        self.tableHandle = ctTable.handle
        self.handle = ctdb.AllocRecord(ctTable.handle)
        self.allocated = True

    def __del__(self):
        if self.allocated:
            self.allocated = False
            ctdb.FreeRecord(self.handle)

    def Close(self):
        if self.allocated:
            self.allocated = False
            ctdb.FreeRecord(self.handle)

    def GetFieldNumber(self, FieldNumberOrName):
        FieldNumber = FieldNumberOrName
        if type(FieldNumberOrName) == str:
            FieldNumber = ctdb.GetFieldNumber(self.tableHandle, FieldNumberOrName)
        return FieldNumber

    def first(self):
        retval = ctdb.FirstRecord(self.handle)
        if retval == ctdb_const.CTDBRET_OK:
            return True
        else:
            return False

    def last(self):
        retval = ctdb.LastRecord(self.handle)
        if retval == ctdb_const.CTDBRET_OK:
            return True
        else:
            return False

    def next(self):
        retval = ctdb.NextRecord(self.handle)
        if retval == ctdb_const.CTDBRET_OK:
            return True
        else:
            return False

    def prev(self):
        retval = ctdb.PrevRecord(self.handle)
        if retval == ctdb_const.CTDBRET_OK:
            return True
        else:
            return False

    def find(self, FindMode):
        retval = ctdb.FindRecord(self.handle, FindMode)
        if retval == ctdb_const.CTDBRET_OK:
            return True
        else:
            return False


    def clear(self):
        return ctdb.ClearRecord(self.handle)

    def read(self):
        return ctdb.ReadRecord(self.handle)

    def write(self):
        return ctdb.WriteRecord(self.handle)

    def delete(self):
        return ctdb.DeleteRecord(self.handle)

    def Reset(self):
        return ctdb.ResetRecord(self.handle)

    def CopyBuffer(self, source):
        if type(source) == CTRecord:
            source = source.handle
        return ctdb.CopyRecordBuffer(source, self.handle)

    def IsNew(self):
        return ctdb.IsNewRecord(self.handle)

    def IsEdited(self):
        return ctdb.IsEditedRecord(self.handle)

    def SetNew(self, flag):
        return ctdb.SetNewRecord(self.handle, flag)

    def SetEdited(self, flag):
        return ctdb.SetEditedRecord(self.handle, flag)


    def GetRecordPos(self):
        uid = ctypes.c_uint32()
        retval = ctdb.GetRecordPos(self.handle, ctypes.byref(uid))
        if retval == 0:
            return uid.value
        elif retval == 101:
            return None

    def GetRecordNbr(self):
        return ctdb.GetRecordNbr(self.handle)

    def SetRecordPos(self, offset):
        return ctdb.SetRecordPos(self.handle, offset)


    def SeekRecord(self, offset):
        return ctdb.SeekRecord(self.handle, offset)

    def GetLength(self):
        return ctdb.GetRecordLength(self.handle)

    def GetRecordLength(self):
        return ctdb.GetRecordLength(self.handle)

    def GetSize(self):
        return ctdb.GetRecordSize(self.handle)

    def GetRecordSize(self):
        return ctdb.GetRecordSize(self.handle)

    def IsNullField(self, FieldNumberOrName):
        return ctdb.IsNullField(self.handle, self.GetFieldNumber(FieldNumberOrName))

    def GetDefaultIndex(self):
        return ctdb.GetDefaultIndex(self.handle)

    def GetDefaultIndexName(self):
        return ctdb.GetDefaultIndexName(self.handle)

    def set_default_index(self, indexNumberOrName):
        if type(indexNumberOrName) == str:
            indexNumberOrName = ctdb.GetIndexNbrByName(self.tableHandle, indexNumberOrName)
        return ctdb.SetDefaultIndex(self.handle, indexNumberOrName)

    def GetFieldName(self, FieldNumber):
        fieldHandle = ctdb.GetField(self.tableHandle, FieldNumber)
        return ctdb.GetFieldName(fieldHandle)

    def GetFieldType(self, FieldNumber):
        fieldHandle = ctdb.GetField(self.tableHandle, FieldNumber)
        return ctdb.GetFieldType(fieldHandle)

    def GetFieldAsBool(self, FieldNumber):
        value = ctypes.c_int()
        retval = ctdb.GetFieldAsBool(self.handle, FieldNumber, ctypes.byref(value))
        if retval == 0:
            if value.value != 0:
                return True
            else:
                return False

    def GetFieldAsSigned(self, FieldNumberOrName): 
        value = ctypes.c_int()
        retval = ctdb.GetFieldAsSigned(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsUnsigned(self, FieldNumberOrName): 
        value = ctypes.c_uint()
        retval = ctdb.GetFieldAsUnsigned(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsDate(self, FieldNumberOrName):
        value = ctypes.c_uint32()
        retval = ctdb.GetFieldAsDate(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsTime(self, FieldNumberOrName):
        value = ctypes.c_uint32()
        retval = ctdb.GetFieldAsTime(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsDateTime(self, FieldNumberOrName):
        value = ctypes.c_double()
        retval = ctdb.GetFieldAsDateTime(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsMoney(self, FieldNumberOrName):
        value = ctypes.c_int32()
        retval = ctdb.GetFieldAsMoney(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsFloat(self, FieldNumberOrName):
        value = ctypes.c_double()
        retval = ctdb.GetFieldAsFloat(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsString(self, FieldNumberOrName, BufferLength=None):
        FieldNumber = self.GetFieldNumber(FieldNumberOrName)
        if BufferLength is None:
          l = ctdb.GetFieldDataLength(self.handle, FieldNumber)+50
        else:
          l = BufferLength+50
        buf = create_string_buffer(l)
        ctdb.GetFieldAsString(self.handle, FieldNumber, buf, l)
        return buf.value.decode(ctdb_const.CTREE_CHAR_ENCODING)

    def GetFieldAsJSON(self, FieldNumber):
        return ctdb.GetFieldAsJSON(self.handle, FieldNumber)

    def GetFieldAsBlob(self, FieldNumber, value):
        return ctdb.GetFieldAsBlob(self.handle, FieldNumber, value)





    def set_field_value(self, FieldNumberOrName, value):
        if value is None:
            return self.ClearField(FieldNumberOrName)

        FieldNumber = FieldNumberOrName
        if type(FieldNumberOrName) == str:
            FieldNumber = ctdb.GetFieldNumber(self.tableHandle, FieldNumberOrName)
        FieldHandle = ctdb.GetField(self.tableHandle, FieldNumber) 
        FieldType = ctdb.GetFieldType(FieldHandle)
        if FieldType == ctdb_const.FieldTypeEnum.BOOLEAN.value:
            if type(value) == str:
                if value.lower() == 'true':
                    value=True
                elif value.lower() == 'false':
                    value=False
                else:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to boolean.", 1) 
            return ctdb.SetFieldAsBool(self.handle, FieldNumber, value)

        if FieldType == ctdb_const.FieldTypeEnum.INT8_SIGNED.value:
            if type(value) == str:
                try:
                  value=int(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to integer [%s]" % str(e), 1) 
            if type(value) == int:
                if value<-128:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>127:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsSigned(self.handle, FieldNumber, value) 
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 
        if FieldType == ctdb_const.FieldTypeEnum.INT16_SIGNED.value:
            if type(value) == str:
                try:
                  value=int(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to integer [%s]" % str(e), 1) 
            if type(value) == int:
                if value<-32768:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>32767:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsSigned(self.handle, FieldNumber, value) 
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 
        if FieldType == ctdb_const.FieldTypeEnum.INT32_SIGNED.value:
            if type(value) == str:
                try:
                  value=int(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to integer [%s]" % str(e), 1) 
            if type(value) == int:
                if value<-2147483648:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>2147483647:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsSigned(self.handle, FieldNumber, value) 
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 
        if FieldType == ctdb_const.FieldTypeEnum.INT64_SIGNED.value: 
            if type(value) == str:
                a = ctypes.c_int64()
                ctdb.StringToBigInt(value,ctypes.byref(a))
                return ctdb.SetFieldAsBigint(self.handle, FieldNumber, a)
            if type(value) == int:
                if value<-9223372036854775807:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>9223372036854775807:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsBigint(self.handle, FieldNumber, value)
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 


        if FieldType == ctdb_const.FieldTypeEnum.INT8_UNSIGNED.value:
            if type(value) == str:
                try:
                  value=int(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to integer [%s]" % str(e), 1) 
            if type(value) == int:
                if value<0:
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>255:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsUnsigned(self.handle, FieldNumber, value)
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 
        if FieldType == ctdb_const.FieldTypeEnum.INT16_UNSIGNED.value:
            if type(value) == str:
                try:
                  value=int(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to integer [%s]" % str(e), 1) 
            if type(value) == int:
                if value<0:
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>65535:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsUnsigned(self.handle, FieldNumber, value)
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 
        if FieldType == ctdb_const.FieldTypeEnum.INT32_UNSIGNED.value:
            if type(value) == str:
                try:
                  value=int(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to integer [%s]" % str(e), 1) 
            if type(value) == int:
                if value<0:
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>4294967295:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsUnsigned(self.handle, FieldNumber, value)
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 

        if FieldType == ctdb_const.FieldTypeEnum.MONEY.value:
            if type(value) == int: 
                if value<-2147483648:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>2147483647:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                a = ctypes.c_int32()
                try:
                  retval = ctdb.LongToMoney(value,ctypes.byref(a))
                except ctdb.DatabaseError as e:
                  raise ctdb.DatabaseError( "set_field_value failed - problem with money value.", e.errorCode) 
                return ctdb.SetFieldAsMoney(self.handle, FieldNumber, a)
            elif type(value) == float: 
                a = ctypes.c_int32()
                try:
                  ctdb.FloatToMoney(value,ctypes.byref(a))
                except ctdb.DatabaseError as e:
                  raise ctdb.DatabaseError( "set_field_value failed - problem with money value.", e.errorCode) 
                return ctdb.SetFieldAsMoney(self.handle, FieldNumber, a)

            elif type(value) == str:
                a = ctypes.c_int32()
                try:
                  ctdb.StringToMoney(value,ctypes.byref(a))
                except ctdb.DatabaseError as e:
                  raise ctdb.DatabaseError( "set_field_value failed - problem with money value.", e.errorCode) 
                return ctdb.SetFieldAsMoney(self.handle, FieldNumber, a)

            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 


        if FieldType == ctdb_const.FieldTypeEnum.DATE.value:
            if type(value) != date:
                raise ctdb.DatabaseError( "set_field_value failed - expected a date and got a "+str(type(value))+".", 1) 
            a = ctypes.c_uint32()
            try:
              retval = ctdb.DatePack(ctypes.byref(a),value.year,value.month,value.day)
            except ctdb.DatabaseError as e:
              raise ctdb.DatabaseError( "set_field_value failed - problem with the date.", e.errorCode) 
            return ctdb.SetFieldAsDate(self.handle, FieldNumber, a)
        if FieldType == ctdb_const.FieldTypeEnum.TIME.value:
            if type(value) != time:
                raise ctdb.DatabaseError( "set_field_value failed - expected a time and got a "+str(type(value))+".", 1) 
            a = ctypes.c_uint32()
            retval = ctdb.TimePack(ctypes.byref(a),value.hour,value.minute,value.second)
            return ctdb.SetFieldAsTime(self.handle, FieldNumber, a)
        if FieldType == ctdb_const.FieldTypeEnum.FLOAT32.value or FieldType == ctdb_const.FieldTypeEnum.FLOAT64.value: 
            if type(value) == str:
                try:
                  value=float(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to float [%s]" % str(e), 1) 
            return ctdb.SetFieldAsFloat(self.handle, FieldNumber, value)


        if FieldType == ctdb_const.FieldTypeEnum.DECIMAL.value:

            if type(value) == str:
                buf = ctypes.create_string_buffer(40) 
                r=ctdb.StringToNumber(value,ctypes.byref(buf))
                if r!=0:
                    raise ctdb.DatabaseError( "set_field_value failed - could not convert string value to a CTNUMBER.", r) 
                return ctdb.SetFieldAsNumber(self.handle, FieldNumber, ctypes.byref(buf))

            if type (value) == int:
                buf = ctypes.create_string_buffer(40) 
                v=str(value) 
                r=ctdb.StringToNumber(v,ctypes.byref(buf))
                if r!=0:
                    raise ctdb.DatabaseError( "set_field_value failed - could not convert int value to a CTNUMBER.", r) 
                return ctdb.SetFieldAsNumber(self.handle, FieldNumber, ctypes.byref(buf))

            if type(value) == float:
                buf = ctypes.create_string_buffer(40) 
                r=ctdb.FloatToNumber(value,ctypes.byref(buf)) 
                if r!=0:
                    raise ctdb.DatabaseError( "set_field_value failed - could not convert float value to a CTNUMBER.", r) 
                return ctdb.SetFieldAsNumber(self.handle, FieldNumber, ctypes.byref(buf))

            if type(value) == Decimal:
                buf = ctypes.create_string_buffer(40) 
                v=str(value) 
                r=ctdb.StringToNumber(v,ctypes.byref(buf))
                if r!=0:
                    raise ctdb.DatabaseError( "set_field_value failed - could not convert Decimal value to a CTNUMBER.", r) 
                return ctdb.SetFieldAsNumber(self.handle, FieldNumber, ctypes.byref(buf))

            raise ctdb.DatabaseError( "set_field_value failed - expected a str, int, float, or Decimal and got a "+str(type(value))+".", 1) 


        if FieldType == ctdb_const.FieldTypeEnum.TIMESTAMP.value: 
            if type(value) != datetime:
                raise ctdb.DatabaseError( "set_field_value failed - expected a datetime and got a "+str(type(value))+".", 1) 
            a = ctypes.c_double()
            retval = ctdb.DateTimePack(ctypes.byref(a),value.year,value.month,value.day,value.hour,value.minute,value.second)
            return ctdb.SetFieldAsDateTime(self.handle, FieldNumber, a)


        if FieldType == ctdb_const.FieldTypeEnum.CURRENCY.value:
            if type(value) == int: 
                if value<-9223372036854775808:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>9223372036854775807:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                a = ctypes.c_int64()
                try:
                  retval = ctdb.BigIntToCurrency(value,ctypes.byref(a))
                except ctdb.DatabaseError as e:
                  raise ctdb.DatabaseError( "set_field_value failed - problem with currency value.", e.errorCode) 
                return ctdb.SetFieldAsCurrency(self.handle, FieldNumber, a)
            elif type(value) == float: 
                a = ctypes.c_int64()
                try:
                  ctdb.FloatToCurrency(value,ctypes.byref(a))
                except ctdb.DatabaseError as e:
                  raise ctdb.DatabaseError( "set_field_value failed - problem with currency value.", e.errorCode) 
                return ctdb.SetFieldAsCurrency(self.handle, FieldNumber, a)
            elif type(value) == str:
                a = ctypes.c_int64()
                try:
                  ctdb.StringToCurrency(value,ctypes.byref(a))
                except ctdb.DatabaseError as e:
                  raise ctdb.DatabaseError( "set_field_value failed - problem with currency value.", e.errorCode) 
                return ctdb.SetFieldAsCurrency(self.handle, FieldNumber, a)

            if type(value) == Decimal:
                v=str(value) 
                a = ctypes.c_int64() 
                r=ctdb.StringToCurrency(v,ctypes.byref(a))
                if r!=0:
                    raise ctdb.DatabaseError( "set_field_value failed - could not convert Decimal value to a CTCURRENCY.", r) 
                return ctdb.SetFieldAsCurrency(self.handle, FieldNumber, a)

            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 



        if FieldType == ctdb_const.FieldTypeEnum.STRING_FIXED_LENGTH.value or FieldType == ctdb_const.FieldTypeEnum.STRING.value:
            if value is None:
                pass 
                return 0
            if type(value) != str:
                raise ctdb.DatabaseError( "set_field_value failed - expected a string and got a "+str(type(value))+".", 1) 
            return ctdb.SetFieldAsString(self.handle, FieldNumber, value)


        if FieldType == ctdb_const.FieldTypeEnum.BINARY_FIXED_LENGTH.value:
            if value is None:
                pass 
                return 0
            if type(value) != str:
                raise ctdb.DatabaseError( "set_field_value failed - expected a string and got a "+str(type(value))+".", 1) 
            return ctdb.SetFieldAsBinary(self.handle, FieldNumber, value.encode('Latin-1'), len(value))

        if FieldType == ctdb_const.FieldTypeEnum.INT64_UNSIGNED.value: 
            if type(value) == str:
                try:
                  value=int(value)
                except Exception as e:
                  raise ctdb.DatabaseError( "set_field_value failed - could not convert string to integer [%s]" % str(e), 1) 
            if type(value) == int:
                if value<0:
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too low.", 4039) 
                elif value>18446744073709551615:  
                  raise ctdb.DatabaseError( "set_field_value failed - int is out of range - too high.", 4038) 
                return ctdb.SetFieldAsUnsignedBigint(self.handle, FieldNumber, value)
            else:
                raise ctdb.DatabaseError( "set_field_value failed - expected an int and got a "+str(type(value))+".", 1) 
  
        raise ctdb.DatabaseError( "set_field_value failed - unrecognized field type.", 4019)



    def get_field_value(self, FieldNumberOrName):
        IsNull=self.IsNullField(FieldNumberOrName)
        if IsNull:
            return None
        
        FieldNumber = FieldNumberOrName
        if type(FieldNumberOrName) == str:
            FieldNumber = ctdb.GetFieldNumber(self.tableHandle, FieldNumberOrName)
        FieldHandle = ctdb.GetField(self.tableHandle, FieldNumber) 
        FieldType = ctdb.GetFieldType(FieldHandle)
        if FieldType == ctdb_const.FieldTypeEnum.BOOLEAN.value:
            return self.GetFieldAsBool(FieldNumber)
        if FieldType == ctdb_const.FieldTypeEnum.INT8_SIGNED.value or FieldType == ctdb_const.FieldTypeEnum.INT16_SIGNED.value or FieldType == ctdb_const.FieldTypeEnum.INT32_SIGNED.value:
            return self.GetFieldAsSigned(FieldNumber)  

        if FieldType == ctdb_const.FieldTypeEnum.INT8_UNSIGNED.value or FieldType == ctdb_const.FieldTypeEnum.INT16_UNSIGNED.value or FieldType == ctdb_const.FieldTypeEnum.INT32_UNSIGNED.value:
            return self.GetFieldAsUnsigned(FieldNumber) 

        if FieldType == ctdb_const.FieldTypeEnum.MONEY.value:
            a = self.GetFieldAsMoney(FieldNumber) 
            d = ctypes.c_double()
            ctdb.MoneyToFloat(a, ctypes.byref(d))
            return d

        if FieldType == ctdb_const.FieldTypeEnum.DATE.value:
            a = self.GetFieldAsDate(FieldNumber) 
            return date.fromordinal(a+620606)

        if FieldType == ctdb_const.FieldTypeEnum.TIME.value:
            a = self.GetFieldAsTime(FieldNumber) 
            hour=ctypes.c_int()
            min=ctypes.c_int()
            sec=ctypes.c_int()
            ctdb.TimeUnpack(a,ctypes.byref(hour),ctypes.byref(min),ctypes.byref(sec))
            return time(hour=hour.value, minute=min.value, second=sec.value)

        if FieldType == ctdb_const.FieldTypeEnum.FLOAT32.value or FieldType == ctdb_const.FieldTypeEnum.FLOAT64.value: 
            return self.GetFieldAsFloat(FieldNumber)

        if FieldType == ctdb_const.FieldTypeEnum.DECIMAL.value:
            buf = ctypes.create_string_buffer(40) 
            ctdb.GetFieldAsNumber(self.handle, FieldNumber, ctypes.byref(buf))
            s = ctdb.NumberToString(ctypes.byref(buf))
            return Decimal(s)

        if FieldType == ctdb_const.FieldTypeEnum.TIMESTAMP.value: 
            a = self.GetFieldAsDateTime(FieldNumber) 


        if FieldType == ctdb_const.FieldTypeEnum.CURRENCY.value:
            a = ctypes.c_int64()
            ctdb.GetFieldAsCurrency(self.handle, FieldNumber, ctypes.byref(a))
            s = ctdb.CurrencyToString(a.value, BufferSize=100)
            return Decimal(s)

        if FieldType == ctdb_const.FieldTypeEnum.STRING_FIXED_LENGTH.value or FieldType == ctdb_const.FieldTypeEnum.STRING.value:
            return self.GetFieldAsString(FieldNumber)

        if FieldType == ctdb_const.FieldTypeEnum.BINARY_FIXED_LENGTH.value:
            length = ctdb.GetFieldDataLength(self.handle, FieldNumber)
            buf = create_string_buffer(length)
            ctdb.GetFieldAsBinary(self.handle,FieldNumber,buf,length)
            s = buf.raw.decode('Latin-1')
            return s

        if FieldType == ctdb_const.FieldTypeEnum.INT64_SIGNED.value: 
            a = ctypes.c_int64()
            ctdb.GetFieldAsBigint(self.handle, FieldNumber, ctypes.byref(a))
            return a.value

        if FieldType == ctdb_const.FieldTypeEnum.INT64_UNSIGNED.value: 
            a = ctypes.c_int64()
            ctdb.GetFieldAsUnsignedBigint(self.handle, FieldNumber, ctypes.byref(a))
            return a.value
 
        raise ctdb.DatabaseError( "get_field_value failed - unrecognized field type (%d)." % (FieldType), 4019)




    def SetFieldAsBool(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsBool(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsSigned(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsSigned(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsUnsigned(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsUnsigned(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsDate(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsDate(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsTime(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsTime(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsDateTime(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsDateTime(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsMoney(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsMoney(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsFloat(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsFloat(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsString(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsString(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsJSON(self, FieldNumber, value):
        return ctdb.SetFieldAsJSON(self.handle, FieldNumber, value.encode(ctdb_const.CTREE_CHAR_ENCODING))

    def SetFieldAsJSON(self, FieldNumber, value):
        return ctdb.SetFieldAsJSON(self.handle, FieldNumber, value)

    def SetFieldAsBlob(self, FieldNumber, value):
        return ctdb.SetFieldAsBlob(self.handle, FieldNumber, value)

    def GetFieldAsBigint(self, FieldNumber):
        return ctdb.GetFieldAsBigint(self.handle, FieldNumber)

    def GetFieldAsCurrency(self, FieldNumberOrName):
        value = ctypes.c_int64()
        retval = ctdb.GetFieldAsCurrency(self.handle, self.GetFieldNumber(FieldNumberOrName), ctypes.byref(value))
        if retval == 0:
            return value.value

    def GetFieldAsNumber(self, FieldNumber):
        return ctdb.GetFieldAsNumber(self.handle, FieldNumber)

    def SetFieldAsBigint(self, FieldNumber, value):
        return ctdb.SetFieldAsBigint(self.handle, FieldNumber, value)

    def SetFieldAsCurrency(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsCurrency(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def SetFieldAsNumber(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsNumber(self.handle, self.GetFieldNumber(FieldNumberOrName), value)

    def IsNullField(self, FieldNumberOrName):
        return ctdb.IsNullField(self.handle, self.GetFieldNumber(FieldNumberOrName))













    def get_record_count(self):
        return ctdb.GetRecordCount(self.handle)

    def RecordSetOn(self, siglen):
        return ctdb.RecordSetOn(self.handle, siglen)

    def IsRecordSetOn(self):
        return ctdb.IsRecordSetOn(self.handle)

    def RecordSetOff(self):
        return ctdb.RecordSetOff(self.handle)

    def IsVariableField(self, FieldNumberOrName):
        return ctdb.IsVariableField(self.handle, self.GetFieldNumber(FieldNumberOrName))

    def GetFieldLength(self, FieldNumberOrName):
        if type(FieldNumberOrName) == str:
            fieldHandle = ctdb.GetFieldByName(FieldNumberOrName).handle
        if type(FieldNumberOrName) == int:
            fieldHandle = ctdb.GetField(self.tableHandle, FieldNumberOrName)
        return ctdb.GetFieldLength(fieldHandle)

    def GetFieldSize(self, FieldNumberOrName):
        return ctdb.GetFieldSize(self.handle, self.GetFieldNumber(FieldNumberOrName))

    def GetFieldOffset(self, FieldNumberOrName):
        return ctdb.GetFieldOffset(self.handle, self.GetFieldNumber(FieldNumberOrName))

    def GetFieldAddress(self, FieldNumberOrName):
        return ctdb.GetFieldAddress(self.handle, self.GetFieldNumber(FieldNumberOrName))

    def GetFieldByName(self, FieldName):
        fieldHandle = ctdb.GetFieldByName(self.handle, FieldName)
        return CTField(fieldHandle)

    def ClearField(self, FieldNumberOrName):
        return ctdb.ClearField(self.handle, self.GetFieldNumber(FieldNumberOrName))

    def Lock(self, lockMode):
        if type(lockMode)!=ctdb_const.LockModeEnum:
            raise ctdb.DatabaseError( "The lockMode parameter must be of type 'LockModeEnum'.  You provided a "+str(type(lockMode))+".", 1) 
        return ctdb.LockRecord(self.handle, lockMode.value)

    def LockRecord(self, lockMode):
        if type(lockMode)!=ctdb_const.LockModeEnum:
            raise ctdb.DatabaseError( "The lockMode parameter must be of type 'LockModeEnum'.  You provided a "+str(type(lockMode))+".", 1) 
        return ctdb.LockRecord(self.handle, lockMode.value)

    def Unlock(self):
        return ctdb.UnlockRecord(self.handle)

    def UnlockRecord(self):
        return ctdb.UnlockRecord(self.handle)

    def GetLock(self):
        return ctdb.GetRecordLock(self.handle)

    def GetRecordLock(self):
        return ctdb.GetRecordLock(self.handle)

    def GetRowid(self):
        return ctdb.GetRowid(self.handle)

    def FindRowid(self, rowid, FindMode):
        return ctdb.FindRowid(self.handle, rowid, FindMode)





    def Compare(self, *record):
        return ctdb.Compare(self.handle, *record)

    def BuildTargetKey(self, FindMode, targetkey, targetlen):
        return ctdb.BuildTargetKey(self.handle, FindMode, targetkey, targetlen)

    def AtPercentile(self, percent):
        return ctdb.RecordAtPercentile(self.handle, percent)


    def NumberOfKeyEntries(self, IndexNumber):
        return ctdb.NumberOfKeyEntries(self.handle, IndexNumber)


    def SwitchContext(self):
        return ctdb.SwitchContext(self.handle)

    def set_filter(self, cndexpr):
        return ctdb.FilterRecord(self.handle, cndexpr)

    def IsFiltered(self):
        return ctdb.IsFilteredRecord(self.handle)

    def get_filter(self):
        return ctdb.GetFilter(self.handle)

    def SetFieldAsUTF16(self, FieldNumberOrName, value):
        return ctdb.SetFieldAsUTF16(self.handle, FieldNumber, value)

    def GetFieldAsUTF16(self, FieldNumberOrName, value, size):
        return ctdb.GetFieldAsUTF16(self.handle, FieldNumber, value, size)

    def BatchLoaded(self):
        return ctdb.BatchLoaded(self.handle)

    def BatchLocked(self):
        return ctdb.BatchLocked(self.handle)

    def BatchTotal(self):
        return ctdb.BatchTotal(self.handle)

    def BatchMode(self):
        return ctdb.BatchMode(self.handle)

    def IsBatchActive(self):
        return ctdb.IsBatchActive(self.handle)

    def EndBatch(self):
        return ctdb.EndBatch(self.handle)

    def InsertBatch(self):
        return ctdb.InsertBatch(self.handle)

    def NextBatch(self):
        return ctdb.NextBatch(self.handle)

    def NextInBatch(self):
        return ctdb.NextInBatch(self.handle)

    def SetBatch(self, mode, targetLen, bufferLen):
        return ctdb.SetBatch(self.handle, mode, targetLen, bufferLen)

    def GetErrorIndex(self):
        return ctdb.GetErrorIndex(self.handle)

    def JumpTo(self, offset):
        return ctdb.JumpToRecord(self.handle, offset)

    def GetRecordKeyPos(self):
        kp = ctypes.c_uint32()
        retval = ctdb.GetRecordKeyPos(self.handle, ctypes.byref(kp))
        if retval == 0:
            return kp.value
        else:
            return None

    def SetDefaultFullTextIndex(self, indexno):
        return ctdb.SetDefaultFTI(self.handle, indexno)

    def FullTextSearchOn(self, query, mode):
        return ctdb.FTSearchOn(self.handle, query, mode)

    def IsFullTextSearchOn(self):
        return ctdb.IsFTSearchOn(self.handle)

    def FullTextSearchOff(self):
        return ctdb.FTSearchOff(self.handle)

    def GetFullTextSearchErrorDetails(self, error, position):
        return ctdb.GetFTSErrorDetails(self.handle, error, position)


class CTField:
    def __init__(self, handle):
        self.handle = handle

    def GetName(self):
        return ctdb.GetFieldName(self.handle)

    def GetType(self):
        return ctdb.GetFieldType(self.handle)

    def GetLength(self):
        return ctdb.GetFieldLength(self.handle)

    def SetName(self, FieldName):
        return ctdb.SetFieldName(self.handle, FieldName)

    def SetType(self, FieldType, Length):
        if type(FieldType)!=ctdb_const.FieldTypeEnum:
            raise ctdb.DatabaseError( "The FieldType parameter must be of type 'FieldTypeEnum'.  You provided a "+str(type(FieldType))+".", 1) 
        return ctdb.SetFieldType(self.handle, FieldType.value, Length)

    def SetLength(self, Length):
        return ctdb.SetFieldLength(self.handle, Length)

    def GetNumber(self):
        return ctdb.GetFieldNbr(self.handle)

    def GetNullFlag(self):
        return ctdb.GetFieldNullFlag(self.handle)

    def GetPrecision(self):
        return ctdb.GetFieldPrecision(self.handle)

    def GetScale(self):
        return ctdb.GetFieldScale(self.handle)

    def SetNullFlag(self, flag):
        return ctdb.SetFieldNullFlag(self.handle, flag)

    def SetPrecision(self, precision):
        return ctdb.SetFieldPrecision(self.handle, precision)

    def SetScale(self, scale):
        return ctdb.SetFieldScale(self.handle, scale)

    def IsNumeric(self):
        return ctdb.IsFieldNumeric(self.handle)

    def SetFieldDefaultValue(self, value, length):
        return ctdb.SetFieldDefaultValue(self.handle, value, length)

    def GetFieldDefaultValue(self):
        return ctdb.GetFieldDefaultValue(self.handle)

    def ClearFieldDefaultValue(self):
        return ctdb.ClearFieldDefaultValue(self.handle)

    def SetFieldDefaultDateTimeType(self, dateType, timeType):
        return ctdb.SetFieldDefaultDateTimeType(self.handle, dateType, timeType)

    def IsFieldDefaultValueSet(self):
        return ctdb.IsFieldDefaultValueSet(self.handle)

    def GetFieldDefaultDateType(self):
        return ctdb.GetFieldDefaultDateType(self.handle)

    def GetFieldDefaultTimeType(self):
        return ctdb.GetFieldDefaultTimeType(self.handle)

    def GetStatus(self):
        return ctdb.GetFieldStatus(self.handle)

    def SetFieldStringEncoding(self, encoding):
        return ctdb.SetFieldStringEncoding(self.handle, encoding)

    def GetFieldStringEncoding(self):
        return ctdb.GetFieldStringEncoding(self.handle)

class CTIndex:
    def __init__(self, handle):
        self.handle = handle

    def GetKeyLength(self):
        return ctdb.GetIndexKeyLength(self.handle)

    def GetKeyType(self):
        return ctdb.GetIndexKeyType(self.handle)

    def GetEmptyChar(self):
        return ctdb.GetIndexEmptyChar(self.handle)

    def GetDuplicateFlag(self):
        return ctdb.GetIndexDuplicateFlag(self.handle)

    def GetNullFlag(self):
        return ctdb.GetIndexNullFlag(self.handle)

    def GetTemporaryFlag(self):
        return ctdb.GetIndexTemporaryFlag(self.handle)

    def SetEmptyChar(self, EmptyChar):
        return ctdb.SetIndexEmptyChar(self.handle, EmptyChar)

    def SetDuplicateFlag(self, DupFlag):
        return ctdb.SetIndexDuplicateFlag(self.handle, DupFlag)

    def SetNullFlag(self, NullFlag):
        return ctdb.SetIndexNullFlag(self.handle, NullFlag)

    def SetTemporaryFlag(self, TempFlag):
        return ctdb.SetIndexTemporaryFlag(self.handle, TempFlag)

    def GetSegmentCount(self):
        return ctdb.GetIndexSegmentCount(self.handle)

    def AddSegment(self, pField, SegMode):
        return ctdb.AddSegment(self.handle, pField.handle, SegMode)


    def InsertSegment(self, BeforeSegment, Field, SegMode):
        return ctdb.InsertSegment(self.handle, BeforeSegment, Field, SegMode)

    def InsertSegment(self, BeforeSegment, offset, length, SegMode):
        return ctdb.InsertSegment(self.handle, BeforeSegment, offset, length, SegMode)

    def DelSegment(self, SegmentNumber):
        return ctdb.DelSegment(self.handle, SegmentNumber)

    def GetSegment(self, SegmentNumber):
        sHandle = ctdb.GetSegment(self.handle, SegmentNumber)
        return CTSegment(sHandle)

    def GetNumber(self):
        inr = ctypes.c_int32()
        ctdb.GetIndexNbr(self.handle, ctypes.byref(inr))
        return inr.value

    def GetName(self):
        return ctdb.GetIndexName(self.handle).decode(ctdb_const.CTREE_CHAR_ENCODING)

    def GetUID(self):
        uid = ctypes.c_uint32()
        ctdb.GetIndexUID(self.handle, self.GetName(), ctypes.byref(uid))
        return uid.value

    def SetName(self, IndexName):
        return ctdb.SetIndexName(self.handle, IndexName)

    def SetKeyType(self, keytype):
        return ctdb.SetKeyType(self.handle, keytype)

    def SetFilename(self, path, name):
        return ctdb.SetFilename(self.handle, path, name)

    def GetFilename(self):
        return ctdb.GetIndexFilename(self.handle)

    def GetIdxno(self):
        return ctdb.GetIdxno(self.handle)

    def GetStatus(self):
        return ctdb.GetIndexStatus(self.handle)


    def AddJSONSegment(self, pField, key, Type, Length):
        return ctdb.AddJSONSegment(self.handle, pField, key, Type, Length)


class CTSegment:
    def __init__(self, handle):
        self.handle = handle

    def GetField(self):
        fieldHandle = ctdb.GetSegmentField(self.handle)
        return CTField(fieldHandle)

    def GetFieldName(self):
        fieldHandle = ctdb.GetSegmentField(self.handle)
        return CTField(fieldHandle).GetName()

    def GetPartialField(self):
        fieldHandle = ctdb.GetSegmentPartialField(self.handle)
        return CTField(fieldHandle)

    def GetPartialFieldName(self):
        fieldHandle = ctdb.GetSegmentPartialField(self.handle)
        return CTField(fieldHandle).GetName()

    def GetMode(self):
        return ctdb.GetSegmentMode(self.handle)

    def SetMode(self, SegMode):
        return ctdb.SetSegmentMode(self.handle, SegMode)

    def GetNumber(self):
        nr = ctypes.c_int32()
        ctdb.GetSegmentNbr(self.handle, ctypes.byref(nr))
        return nr.value

    def GetStatus(self):
        return ctdb.GetSegmentStatus(self.handle)

    def MoveSegment(self, newIndex):
        return ctdb.MoveSegment(self.handle, newIndex) 

    def SetField(self, field):
        return ctdb.SetSegmentField(self.handle, field)

    def SetJSONField(self, field, key, type, size):
        return ctdb.SetJSONSegmentField(self.handle, field, key, type, size)


class CTFullTextIndex:
    def __init__(self, ctSession_or_FTIHandle):
        if type(ctSession_or_FTIHandle) == CTSession:
            self.handle = ctdb.AllocFTI(ctSession.handle)
        else:
            self.handle = ctSession_or_FTIHandle

    def AddField(self, ctField, mode):
        return ctdb.AddFTIField(self.handle, ctField.handle, mode)

    def GetFieldCount(self):
        return ctdb.GetFTIFieldCount (self.handle)

    def GetField(self, FieldNumber):
        return ctdb.GetFTIField(self.handle, FieldNumber)

    def GetFieldMode(self, FieldNumber):
        return ctdb.GetFTIFieldMode(self.handle, FieldNumber)

    def GetStatus(self):
        return ctdb.GetFTIStatus(self.handle)

    def SetOption(self, option, pvalue, lvalue):
        return ctdb.SetFTIOption(self.handle, option, pvalue, lvalue)

    def GetNumber(self, pNumber):
        return ctdb.GetFTINbr(self.handle, pNumber)

    def GetName(self):
        return ctdb.GetFTIName(self.handle)


class CTFullTextIndexDictionary:
    def __init__(self, ctSession):
        self.handle = ctdb.AllocFTIDict(ctSession.handle)

    def SetOption(self, option, pvalue, lvalue):
        return ctdb.SetFTIDictOption(self.handle, option, pvalue, lvalue)

    def __del__(self):
        ctdb.FreeFTIDict(self.handle)
