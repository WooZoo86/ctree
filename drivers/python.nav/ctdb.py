# -*- coding: Latin-1 -*-

import ctypes, sys
from pyctdbsdk import _ctdbsdk
import inspect
import ctdb_const


OK = 0

class DatabaseError(Exception):
  def __init__(self, error_message=None, error_code=None, source_file=None, line_number=None):
    self.__errorMsg = error_message 
    self.__errorCode = error_code
    self.__sourceFile = source_file
    self.__lineNbr = line_number

  @property
  def error_message(self):
    return self.__errorMsg

  @property
  def error_code(self):
    return self.__errorCode

  @property
  def source_file(self):
    return self.__sourceFile

  @property
  def line_number(self):
    return self.__lineNbr

  def __str__(self):
    return self.__errorMsg+" ErrorCode="+str(self.__errorCode)
    
  def __repr__(self):
    return "DatabaseError('"+self.__errorMsg+"', "+str(self.__errorCode)+")"


def AllocSession(SessionType, ):
  retval = _ctdbsdk.ctdbAllocSession(SessionType, ) 
  if retval is None: 
    raise DatabaseError( "AllocSession failed.") 
  return retval

def FreeSession(Handle, ):
  retval = _ctdbsdk.ctdbFreeSession(Handle, )

def Logon(Handle, dbengine, userid, password, ): 
  retval = _ctdbsdk.ctdbLogon(Handle, dbengine.encode(ctdb_const.CTREE_CHAR_ENCODING), userid.encode(ctdb_const.CTREE_CHAR_ENCODING), password.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "Session logon failed.", retval)
  return retval

def Logout(Handle, ):
  retval = _ctdbsdk.ctdbLogout(Handle, )
  if retval != 0:
    raise DatabaseError( "Session logout failed.", retval)
  return retval

def GetServerName(Handle, ):
  retval = _ctdbsdk.ctdbGetServerName(Handle, )
  if retval == 0:
    raise DatabaseError( "GetServerName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetUserLogonName(Handle, ):
  retval = _ctdbsdk.ctdbGetUserLogonName(Handle, )
  if retval == 0:
    raise DatabaseError( "GetUserLogonName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetUserPassword(Handle, ):
  retval = _ctdbsdk.ctdbGetUserPassword(Handle, )
  if retval == 0:
    raise DatabaseError( "GetUserPassword failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetSessionParams(Handle, ParamType, ):
  retval = _ctdbsdk.ctdbGetSessionParams(Handle, ParamType, )
  if retval == 0:
    raise DatabaseError( "GetSessionParams failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetSessionParams(Handle, ParamType, value, ):
  retval = _ctdbsdk.ctdbSetSessionParams(Handle, ParamType, value, )
  if retval != 0:
    raise DatabaseError( "SetSessionParams failed.", retval)
  return retval

def SetSessionSSLParams(Handle, ParamType, value, ):
  retval = _ctdbsdk.ctdbSetSessionSSLParams(Handle, ParamType, value.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetSessionSSLParams failed.", retval)
  return retval

def IsSSLActive(Handle, ):
  retval = _ctdbsdk.ctdbIsSSLActive(Handle, )
  return retval

def SetSSL(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetSSL(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetSSL failed.", retval)
  return retval

def IsActiveSession(Handle, ):
  retval = _ctdbsdk.ctdbIsActiveSession(Handle, )
  return retval

def GetSessionHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetSessionHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetSessionHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetError(Handle, ):
  retval = _ctdbsdk.ctdbGetError(Handle, ) 
  if retval == 0:
    raise DatabaseError( "GetError failed.") 
  return retval

def SetError(Handle, ErrorCode, ):
  retval = _ctdbsdk.ctdbSetError(Handle, ErrorCode, )
  if retval != 0:
    raise DatabaseError( "SetError failed.", retval)
  return retval

def ClearError(Handle, ):
  retval = _ctdbsdk.ctdbClearError(Handle, )

def IsTransActive(Handle, ):
  retval = _ctdbsdk.ctdbIsTransActive(Handle, )
  if retval == 0:
    raise DatabaseError( "IsTransActive failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SyncTransactionState(Handle, ):
  retval = _ctdbsdk.ctdbSyncTransactionState(Handle, )
  if retval != 0:
    raise DatabaseError( "SyncTransactionState failed.", retval)
  return retval

def Begin(Handle, ):
  retval = _ctdbsdk.ctdbBegin(Handle, )
  if retval != 0:
    raise DatabaseError( "Begin Transaction failed.", retval)
  return retval

def PrepareCommit(Handle, ):
  retval = _ctdbsdk.ctdbPrepareCommit(Handle, )
  if retval != 0:
    raise DatabaseError( "PrepareCommit failed.", retval)
  return retval

def Commit(Handle, ):
  retval = _ctdbsdk.ctdbCommit(Handle, )
  if retval != 0:
    raise DatabaseError( "Commit Transaction failed.", retval)
  return retval

def Abort(Handle, ):
  retval = _ctdbsdk.ctdbAbort(Handle, )
  if retval != 0:
    raise DatabaseError( "Abort Transaction failed.", retval)
  return retval

def SetSavePoint(Handle, ):
  retval = _ctdbsdk.ctdbSetSavePoint(Handle, )
  if retval == 0:
    raise DatabaseError( "SetSavePoint failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetSingleSavePoint(Handle, ):
  retval = _ctdbsdk.ctdbSetSingleSavePoint(Handle, )
  if retval == 0:
    raise DatabaseError( "SetSingleSavePoint failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def RestoreSavePoint(Handle, SavePoint, ):
  retval = _ctdbsdk.ctdbRestoreSavePoint(Handle, SavePoint, )
  if retval != 0:
    raise DatabaseError( "RestoreSavePoint failed.", retval)
  return retval

def ClearSavePoint(Handle, ):
  retval = _ctdbsdk.ctdbClearSavePoint(Handle, )
  if retval != 0:
    raise DatabaseError( "ClearSavePoint failed.", retval)
  return retval

def GetSessionPath(Handle, Path, PathSize ):
  retval = _ctdbsdk.ctdbGetSessionPath(Handle, Path, PathSize )
  if retval != 0:
    raise DatabaseError( "GetSessionPath failed.", retval)
  return Path

def SetSessionPath(Handle, Path, ):
  retval = _ctdbsdk.ctdbSetSessionPath(Handle, Path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetSessionPath failed.", retval)
  return retval

def FirstDatabase(Handle, Name, NameSize, Path, PathSize, ):
  retval = _ctdbsdk.ctdbFirstDatabase(Handle, Name, NameSize, Path, PathSize, )
  if retval != 0:
    raise DatabaseError( "FirstDatabase failed.", retval)
  return retval

def NextDatabase(Handle, Name, NameSize, Path, PathSize, ):
  retval = _ctdbsdk.ctdbNextDatabase(Handle, Name, NameSize, Path, PathSize, )
  if retval != 0:
    raise DatabaseError( "NextDatabase failed.", retval)
  return retval

def FindDatabase(Handle, Name, Path, PathSize, ):
  retval = _ctdbsdk.ctdbFindDatabase(Handle, Name, Path, PathSize, )
  return retval

def FindDatabaseByUID(Handle, uid, Name, NameSize, Path, PathSize, ):
  retval = _ctdbsdk.ctdbFindDatabaseByUID(Handle, uid, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), NameSize, Path.encode(ctdb_const.CTREE_CHAR_ENCODING), PathSize, )
  if retval != 0:
    raise DatabaseError( "FindDatabaseByUID failed.", retval)
  return retval

def CreateSession(Handle, dbengine, userid, password, ):
  retval = _ctdbsdk.ctdbCreateSession(Handle, dbengine.encode(ctdb_const.CTREE_CHAR_ENCODING), userid.encode(ctdb_const.CTREE_CHAR_ENCODING), password.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "CreateSession failed.", retval)
  return retval

def GetFirstActiveDatabase(Handle, pScanIndex, ):
  retval = _ctdbsdk.ctdbGetFirstActiveDatabase(Handle, pScanIndex, )
  if retval is None: 
    raise DatabaseError( "GetFirstActiveDatabase failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetNextActiveDatabase(Handle, pScanIndex, ):
  retval = _ctdbsdk.ctdbGetNextActiveDatabase(Handle, pScanIndex, )
  if retval is None: 
    raise DatabaseError( "GetNextActiveDatabase failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FindActiveDatabase(Handle, Name, ):
  retval = _ctdbsdk.ctdbFindActiveDatabase(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval is None: 
    raise DatabaseError( "FindActiveDatabase failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FindActiveDatabaseByUID(Handle, uid, ):
  retval = _ctdbsdk.ctdbFindActiveDatabaseByUID(Handle, uid, )
  if retval is None: 
    raise DatabaseError( "FindActiveDatabaseByUID failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetDefFloatFormat(Handle, format, ):
  retval = _ctdbsdk.ctdbSetDefFloatFormat(Handle, format.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetDefFloatFormat failed.", retval)
  return retval

def GetDefFloatFormat(Handle, ):
  retval = _ctdbsdk.ctdbGetDefFloatFormat(Handle, )
  if retval == 0:
    raise DatabaseError( "GetDefFloatFormat failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetLogonOnly(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetLogonOnly(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetLogonOnly failed.", retval)
  return retval

def GetLogonOnly(Handle, ):
  retval = _ctdbsdk.ctdbGetLogonOnly(Handle, )
  return retval

def GetDatabaseCount(Handle, ):
  retval = _ctdbsdk.ctdbGetDatabaseCount(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetDatabaseCount failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetUserTag(Handle, tagptr, ):
  retval = _ctdbsdk.ctdbGetUserTag(Handle, tagptr, )
  if retval != 0:
    raise DatabaseError( "GetUserTag failed.", retval)
  return retval

def SetUserTag(Handle, tagptr, ):
  retval = _ctdbsdk.ctdbSetUserTag(Handle, tagptr, )
  if retval != 0:
    raise DatabaseError( "SetUserTag failed.", retval)
  return retval

def IsLockActive(Handle, ):
  retval = _ctdbsdk.ctdbIsLockActive(Handle, )
  if retval == 0:
    raise DatabaseError( "IsLockActive failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def Lock(Handle, mode, ):
  retval = _ctdbsdk.ctdbLock(Handle, mode, )
  if retval != 0:
    raise DatabaseError( "Lock failed.", retval)
  return retval

def Unlock(Handle, ):
  retval = _ctdbsdk.ctdbUnlock(Handle, )
  if retval != 0:
    raise DatabaseError( "Unlock failed.", retval)
  return retval

def GetLockMode(Handle, ):
  retval = _ctdbsdk.ctdbGetLockMode(Handle, )
  if retval == 0:
    raise DatabaseError( "GetLockMode failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetTransactionIsolation(Handle, isolevel, ):
  retval = _ctdbsdk.ctdbSetTransactionIsolation(Handle, isolevel, )
  if retval != 0:
    raise DatabaseError( "SetTransactionIsolation failed.", retval)
  return retval

def GetTransactionIsolation(Handle, ):
  retval = _ctdbsdk.ctdbGetTransactionIsolation(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTransactionIsolation failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetSessionType(Handle, SessionType, ):
  retval = _ctdbsdk.ctdbSetSessionType(Handle, SessionType, )
  if retval != 0:
    raise DatabaseError( "SetSessionType failed.", retval)
  return retval

def GetSessionType(Handle, ):
  retval = _ctdbsdk.ctdbGetSessionType(Handle, )
  return retval

def GetLibType(Handle, ):
  retval = _ctdbsdk.ctdbGetLibType(Handle, )
  return retval

def SetKeepLock(Handle, mode, ):
  retval = _ctdbsdk.ctdbSetKeepLock(Handle, mode, )
  if retval != 0:
    raise DatabaseError( "SetKeepLock failed.", retval)
  return retval

def GetKeepLock(Handle, ):
  retval = _ctdbsdk.ctdbGetKeepLock(Handle, )
  return retval

def SetCurrentNodeName(Handle, NodeName, ):
  retval = _ctdbsdk.ctdbSetCurrentNodeName(Handle, NodeName.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetCurrentNodeName failed.", retval)
  return retval

def SwitchInstance(Handle, ):
  retval = _ctdbsdk.ctdbSwitchInstance(Handle, )
  if retval != 0:
    raise DatabaseError( "SwitchInstance failed.", retval)
  return retval

def SetPathPrefix(Handle, path, ):
  retval = _ctdbsdk.ctdbSetPathPrefix(Handle, path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetPathPrefix failed.", retval)
  return retval

def ClearPathPrefix(Handle, ):
  retval = _ctdbsdk.ctdbClearPathPrefix(Handle, )
  if retval != 0:
    raise DatabaseError( "ClearPathPrefix failed.", retval)
  return retval

def GetPathPrefix(Handle, ):
  retval = _ctdbsdk.ctdbGetPathPrefix(Handle, )
  if retval == 0:
    raise DatabaseError( "GetPathPrefix failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetHandleType(Handle, ):
  retval = _ctdbsdk.ctdbGetHandleType(Handle, )
  if retval == 0:
    raise DatabaseError( "GetHandleType failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetCallback(Handle, CallBackType, CallBackFunc, ):
  retval = _ctdbsdk.ctdbSetCallback(Handle, CallBackType, CallBackFunc, )
  if retval != 0:
    raise DatabaseError( "SetCallback failed.", retval)
  return retval

def GetCallback(Handle, CallBackType, ):
  retval = _ctdbsdk.ctdbGetCallback(Handle, CallBackType, )
  if retval is None: 
    raise DatabaseError( "GetCallback failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def ClearCallback(Handle, CallBackType, ):
  retval = _ctdbsdk.ctdbClearCallback(Handle, CallBackType, )
  if retval != 0:
    raise DatabaseError( "ClearCallback failed.", retval)
  return retval

def ClearAllCallback(Handle, ):
  retval = _ctdbsdk.ctdbClearAllCallback(Handle, )
  if retval != 0:
    raise DatabaseError( "ClearAllCallback failed.", retval)
  return retval

def SetLocalTag(Handle, pTag, ):
  retval = _ctdbsdk.ctdbSetLocalTag(Handle, pTag, )
  if retval != 0:
    raise DatabaseError( "SetLocalTag failed.", retval)
  return retval

def GetLocalTag(Handle, ):
  retval = _ctdbsdk.ctdbGetLocalTag(Handle, )
  if retval is None: 
    raise DatabaseError( "GetLocalTag failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetFieldCallback(Handle, CallBackType, CallBackFunc, ):
  retval = _ctdbsdk.ctdbSetFieldCallback(Handle, CallBackType, CallBackFunc, )
  if retval != 0:
    raise DatabaseError( "SetFieldCallback failed.", retval)
  return retval

def IsSQLServer(Handle, ):
  retval = _ctdbsdk.ctdbIsSQLServer(Handle, )
  return retval

def GetSystemConfig(index, ):
  retval = _ctdbsdk.ctdbGetSystemConfig(index, )
  if retval == 0:
    raise DatabaseError( "GetSystemConfig failed.") 
  return retval

def SetSessionExclusive(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetSessionExclusive(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetSessionExclusive failed.", retval)
  return retval

def IsSessionExclusive(Handle, ):
  retval = _ctdbsdk.ctdbIsSessionExclusive(Handle, )
  if retval == 0:
    raise DatabaseError( "IsSessionExclusive failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetAttachMode(Handle, ):
  retval = _ctdbsdk.ctdbGetAttachMode(Handle, )
  if retval == 0:
    raise DatabaseError( "GetAttachMode failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AttachSession(Handle, Session, mode, isTransactionActive, ):
  retval = _ctdbsdk.ctdbAttachSession(Handle, Session, mode, isTransactionActive, )
  if retval != 0:
    raise DatabaseError( "AttachSession failed.", retval)
  return retval

def DetachSession(Handle, ):
  retval = _ctdbsdk.ctdbDetachSession(Handle, )
  if retval != 0:
    raise DatabaseError( "DetachSession failed.", retval)
  return retval

def SetConfigurationFile(cfgfil, ):
  retval = _ctdbsdk.ctdbSetConfigurationFile(cfgfil.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetConfigurationFile failed.", retval)
  return retval

def SetLicenseFile(licfil, ):
  retval = _ctdbsdk.ctdbSetLicenseFile(licfil.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetLicenseFile failed.", retval)
  return retval

def StartDatabaseEngine():
  retval = _ctdbsdk.ctdbStartDatabaseEngine()
  if retval != 0:
    raise DatabaseError( "StartDatabaseEngine failed.", retval)
  return retval

def StopDatabaseEngine():
  retval = _ctdbsdk.ctdbStopDatabaseEngine()

def AcquireSessionId():
  retval = _ctdbsdk.ctdbAcquireSessionId()
  if retval == 0:
    raise DatabaseError( "AcquireSessionId failed.") 
  return retval

def ReleaseSessionId(sessid, ):
  retval = _ctdbsdk.ctdbReleaseSessionId(sessid, )

def GetSessionId(Handle, ):
  retval = _ctdbsdk.ctdbGetSessionId(Handle, )
  if retval == 0:
    raise DatabaseError( "GetSessionId failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetSessionId(Handle, sessid, ):
  retval = _ctdbsdk.ctdbSetSessionId(Handle, sessid, )

def GetTransactionMode(Handle, ):
  retval = _ctdbsdk.ctdbGetTransactionMode(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTransactionMode failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetTransactionMode(Handle, mode, ):
  retval = _ctdbsdk.ctdbSetTransactionMode(Handle, mode, )
  if retval != 0:
    raise DatabaseError( "SetTransactionMode failed.", retval)
  return retval

def GetOperationState(Handle, ):
  retval = _ctdbsdk.ctdbGetOperationState(Handle, )
  if retval == 0:
    raise DatabaseError( "GetOperationState failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetOperationState(Handle, mode, state, ):
  retval = _ctdbsdk.ctdbSetOperationState(Handle, mode, state, )
  if retval != 0:
    raise DatabaseError( "SetOperationState failed.", retval)
  return retval

def GetAutoCommit(Handle, ):
  retval = _ctdbsdk.ctdbGetAutoCommit(Handle, )
  if retval == 0:
    raise DatabaseError( "GetAutoCommit failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetAutoCommit(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetAutoCommit(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetAutoCommit failed.", retval)
  return retval

def SetSqlCallBack(Handle, SQLcallback, ):
  retval = _ctdbsdk.ctdbSetSqlCallBack(Handle, SQLcallback, )

def GetCtreeOWNER():
  retval = _ctdbsdk.ctdbGetCtreeOWNER()
  if retval == 0:
    raise DatabaseError( "GetCtreeOWNER failed.") 
  return retval

def SetCtreeOWNER(owner, ):
  retval = _ctdbsdk.ctdbSetCtreeOWNER(owner, )

def LoadCallbackLib(Handle, libname, inifile, registercallbacks, ):
  retval = _ctdbsdk.ctdbLoadCallbackLib(Handle, libname.encode(ctdb_const.CTREE_CHAR_ENCODING), inifile.encode(ctdb_const.CTREE_CHAR_ENCODING), registercallbacks, )
  if retval != 0:
    raise DatabaseError( "LoadCallbackLib failed.", retval)
  return retval

def UnLoadCallbackLib(Handle, unregonly, ):
  retval = _ctdbsdk.ctdbUnLoadCallbackLib(Handle, unregonly, )
  if retval != 0:
    raise DatabaseError( "UnLoadCallbackLib failed.", retval)
  return retval

def BeginImpersonation(Handle, taskId, ):
  retval = _ctdbsdk.ctdbBeginImpersonation(Handle, taskId, )
  if retval != 0:
    raise DatabaseError( "BeginImpersonation failed.", retval)
  return retval

def EndImpersonation(Handle, ):
  retval = _ctdbsdk.ctdbEndImpersonation(Handle, )
  if retval != 0:
    raise DatabaseError( "EndImpersonation failed.", retval)
  return retval

def GetProductName(Handle, prodName, bufLen, ):
  retval = _ctdbsdk.ctdbGetProductName(Handle, prodName, bufLen, )
  if retval != 0:
    raise DatabaseError( "GetProductName failed.", retval)
  return retval

def GetProductVersion(Handle, prodVersion, bufLen, ):
  retval = _ctdbsdk.ctdbGetProductVersion(Handle, prodVersion, bufLen, )
  if retval != 0:
    raise DatabaseError( "GetProductVersion failed.", retval)
  return retval

def GetMaxConnections(Handle, maxConn, ):
  retval = _ctdbsdk.ctdbGetMaxConnections(Handle, maxConn, )
  if retval != 0:
    raise DatabaseError( "GetMaxConnections failed.", retval)
  return retval

def ServerDateTime(hSession, ):
  retval = _ctdbsdk.ctdbServerDateTime(hSession, )
  if retval == 0:
    raise DatabaseError( "ServerDateTime failed.", _ctdbsdk.ctdbGetError(hSession))
  return retval

def SetLocalDirectory(localdir, ):
  retval = _ctdbsdk.ctdbSetLocalDirectory(localdir.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetLocalDirectory failed.", retval)
  return retval

def SetLogPath(hSession, path, ):
  retval = _ctdbsdk.ctdbSetLogPath(hSession, path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetLogPath failed.", retval)
  return retval

def SetStatusLogPath(hSession, path, ):
  retval = _ctdbsdk.ctdbSetStatusLogPath(hSession, path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetStatusLogPath failed.", retval)
  return retval

def SetTempPath(hSession, path, ):
  retval = _ctdbsdk.ctdbSetTempPath(hSession, path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetTempPath failed.", retval)
  return retval

def GetDatabaseHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetDatabaseHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetDatabaseHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AllocDatabase(Handle, ): 
  retval = _ctdbsdk.ctdbAllocDatabase(Handle, )
  if retval is None: 
    raise DatabaseError( "AllocDatabase failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeDatabase(Handle, ):
  retval = _ctdbsdk.ctdbFreeDatabase(Handle, )

def Connect(Handle, Name, ): 
  retval = _ctdbsdk.ctdbConnect(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError("Database connect failed.", retval)
  return retval

def Disconnect(Handle, ):
  retval = _ctdbsdk.ctdbDisconnect(Handle, )
  if retval != 0:
    raise DatabaseError( "Database disconnect failed.", retval)
  return retval

def DisconnectAll(Handle, ):
  retval = _ctdbsdk.ctdbDisconnectAll(Handle, )
  if retval != 0:
    raise DatabaseError( "Database disconnect all failed.", retval)
  return retval

def CreateDatabase(Handle, Name, Path, ):
  retval = _ctdbsdk.ctdbCreateDatabase(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), Path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "Create database failed.", retval)
  return retval

def AddDatabase(Handle, Name, Path, ):
  retval = _ctdbsdk.ctdbAddDatabase(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), Path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "Add database failed.", retval)
  return retval

def DeleteDatabase(Handle, Name, ):
  retval = _ctdbsdk.ctdbDeleteDatabase(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "Delete database failed.", retval)
  return retval

def DropDatabase(Handle, Name, ):
  retval = _ctdbsdk.ctdbDropDatabase(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "Drop database failed.", retval)
  return retval

def FirstTable(Handle, Name, NameSize, Path, PathSize, ):
  retval = _ctdbsdk.ctdbFirstTable(Handle, Name, NameSize, Path, PathSize, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "FirstTable failed.", retval)
  return retval

def NextTable(Handle, Name, NameSize, Path, PathSize, ):
  retval = _ctdbsdk.ctdbNextTable(Handle, Name, NameSize, Path, PathSize, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "NextTable failed.", retval)
  return retval

def FindTable(Handle, Name, Path, PathSize ):
  if type(Name) == str:
    Name = Name.encode(ctdb_const.CTREE_CHAR_ENCODING)
  retval = _ctdbsdk.ctdbFindTable(Handle, Name, Path, PathSize )
  if retval != 0 and retval != 101:
    raise DatabaseError( "FindTable failed.", retval)
  return retval

def FindTableByUID(Handle, uid, Name, NameSize, Path, PathSize, ):
  retval = _ctdbsdk.ctdbFindTableByUID(Handle, uid, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), NameSize, Path.encode(ctdb_const.CTREE_CHAR_ENCODING), PathSize, )
  if retval != 0:
    raise DatabaseError( "FindTableByUID failed.", retval)
  return retval

def AddTable(Handle, Name, Path, ):
  retval = _ctdbsdk.ctdbAddTable(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), Path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "AddTable failed.", retval)
  return retval

def AddTableXtd(Handle, Name, PhysicName, Path, ):
  retval = _ctdbsdk.ctdbAddTableXtd(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), PhysicName.encode(ctdb_const.CTREE_CHAR_ENCODING), Path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "AddTableXtd failed.", retval)
  return retval


def DeleteTable(Handle, TableName, Password, ):
  retval = _ctdbsdk.ctdbDeleteTable(Handle, TableName.encode(ctdb_const.CTREE_CHAR_ENCODING), Password.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "DeleteTable failed.", retval)
  return retval

def DropTable(Handle, TableName, ):
  retval = _ctdbsdk.ctdbDropTable(Handle, TableName.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "DropTable failed.", retval)
  return retval

def GetDatabaseUID(Handle, Name, puid, ):
  retval = _ctdbsdk.ctdbGetDatabaseUID(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), puid, )
  if retval != 0:
    raise DatabaseError( "GetDatabaseUID failed.", retval)
  return retval

def GetTableUID(Handle, Name, puid, ):
  retval = _ctdbsdk.ctdbGetTableUID(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), puid, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "GetTableUID failed.", retval)
  return retval

def GetDatabaseObjptr(Handle, ):
  retval = _ctdbsdk.ctdbGetDatabaseObjptr(Handle, )
  if retval is None: 
    raise DatabaseError( "GetDatabaseObjptr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetDatabaseObjptr(Handle, ptr, ):
  retval = _ctdbsdk.ctdbSetDatabaseObjptr(Handle, ptr, )
  if retval != 0:
    raise DatabaseError( "SetDatabaseObjptr failed.", retval)
  return retval

def GetFirstActiveTable(Handle, pScanRec, ):
  retval = _ctdbsdk.ctdbGetFirstActiveTable(Handle, pScanRec, )
  if retval is None: 
    raise DatabaseError( "GetFirstActiveTable failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetNextActiveTable(Handle, pScanRec, ):
  retval = _ctdbsdk.ctdbGetNextActiveTable(Handle, pScanRec, )
  if retval is None: 
    raise DatabaseError( "GetNextActiveTable failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FindActiveTable(Handle, Name, ):
  retval = _ctdbsdk.ctdbFindActiveTable(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval is None: 
    raise DatabaseError( "FindActiveTable failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FindActiveTableByUID(Handle, uid, ):
  retval = _ctdbsdk.ctdbFindActiveTableByUID(Handle, uid, )
  if retval is None: 
    raise DatabaseError( "FindActiveTableByUID failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetActiveDatabaseUID(Handle, puid, ):
  retval = _ctdbsdk.ctdbGetActiveDatabaseUID(Handle, puid, )
  if retval != 0:
    raise DatabaseError( "GetActiveDatabaseUID failed.", retval)
  return retval

def IsActiveDatabase(Handle, ):
  retval = _ctdbsdk.ctdbIsActiveDatabase(Handle, )
  return retval

def GetDatabasePath(Handle):
  retval = _ctdbsdk.ctdbGetDatabasePath(Handle)
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING) if retval else retval

def GetDatabaseName(Handle):
  retval = _ctdbsdk.ctdbGetDatabaseName(Handle)
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING) if retval else retval

def GetTableCount(Handle, ):
  retval = _ctdbsdk.ctdbGetTableCount(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetTableCount failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetActiveTableByUID(Handle, uid, ):
  retval = _ctdbsdk.ctdbGetActiveTableByUID(Handle, uid, )
  if retval is None: 
    raise DatabaseError( "GetActiveTableByUID failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetDefaultSqlTableOwner(Handle):
  retval = _ctdbsdk.ctdbGetDefaultSqlTableOwner(Handle)
  if retval == 0:
    raise DatabaseError( "GetDefaultSqlTableOwner failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING) if retval else retval

def SetDefaultSqlTableOwner(Handle, sqlowner, ):
  retval = _ctdbsdk.ctdbSetDefaultSqlTableOwner(Handle, sqlowner.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetDefaultSqlTableOwner failed.", retval)
  return retval

def IsSQLDatabase(Handle, ):
  retval = _ctdbsdk.ctdbIsSQLDatabase(Handle, )
  if retval == 0:
    raise DatabaseError( "IsSQLDatabase failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetDatabaseExclusive(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetDatabaseExclusive(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetDatabaseExclusive failed.", retval)
  return retval

def IsDatabaseExclusive(Handle, ):
  retval = _ctdbsdk.ctdbIsDatabaseExclusive(Handle, )
  return retval

def CheckSysTablesSQLInfo(pDatabase, Error, ErrorCount, ):
  retval = _ctdbsdk.ctdbCheckSysTablesSQLInfo(pDatabase, Error, ErrorCount, )
  if retval != 0:
    raise DatabaseError( "CheckSysTablesSQLInfo failed.", retval)
  return retval

def GetTableHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetTableHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetTableHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AllocTable(Handle, ):
  retval = _ctdbsdk.ctdbAllocTable(Handle, )
  if retval is None: 
    raise DatabaseError( "AllocTable failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeTable(Handle, ):
  retval = _ctdbsdk.ctdbFreeTable(Handle, )

def IsActiveTable(Handle, ):
  retval = _ctdbsdk.ctdbIsActiveTable(Handle, )
  return retval

def GetTablePath(Handle, ):
  retval = _ctdbsdk.ctdbGetTablePath(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTablePath failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTableName(Handle, ):
  retval = _ctdbsdk.ctdbGetTableName(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTableName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTableExtension(Handle, ):
  retval = _ctdbsdk.ctdbGetTableExtension(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTableExtension failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTableIndexCount(Handle):
  retval = _ctdbsdk.ctdbGetTableIndexCount(Handle)
  if retval == -1: 
    raise DatabaseError( "GetTableIndexCount failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTableFieldCount(Handle, ):
  retval = _ctdbsdk.ctdbGetTableFieldCount(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetTableFieldCount failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTableOpenMode(Handle, ):
  retval = _ctdbsdk.ctdbGetTableOpenMode(Handle, )
  return retval

def GetTableCreateMode(Handle, ):
  retval = _ctdbsdk.ctdbGetTableCreateMode(Handle, )
  return retval

def GetTableDefaultDataExtentSize(Handle, ):
  retval = _ctdbsdk.ctdbGetTableDefaultDataExtentSize(Handle, )
  return retval

def GetTableDefaultIndexExtentSize(Handle, ):
  retval = _ctdbsdk.ctdbGetTableDefaultIndexExtentSize(Handle, )
  return retval

def SetTablePath(Handle, Path, ):
  retval = _ctdbsdk.ctdbSetTablePath(Handle, Path.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetTablePath failed.", retval)
  return retval

def SetTableExtension(Handle, fExt, ):
  retval = _ctdbsdk.ctdbSetTableExtension(Handle, fExt.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetTableExtension failed.", retval)
  return retval

def SetTableDefaultDataExtentSize(Handle, size, ):
  retval = _ctdbsdk.ctdbSetTableDefaultDataExtentSize(Handle, size, )
  if retval != 0:
    raise DatabaseError( "SetTableDefaultDataExtentSize failed.", retval)
  return retval

def SetTableDefaultIndexExtentSize(Handle, size, ):
  retval = _ctdbsdk.ctdbSetTableDefaultIndexExtentSize(Handle, size, )
  if retval != 0:
    raise DatabaseError( "SetTableDefaultIndexExtentSize failed.", retval)
  return retval

def CreateTable(Handle, TableName, CreateMode, ):
  retval = _ctdbsdk.ctdbCreateTable(Handle, TableName.encode(ctdb_const.CTREE_CHAR_ENCODING), CreateMode, )
  if retval != 0:
    raise DatabaseError( "CreateTable failed.", retval)
  return retval

def CreateMRTTable(Handle, VTableName, ParentName, CreateMode, filter, ):
  retval = _ctdbsdk.ctdbCreateMRTTable(Handle, VTableName.encode(ctdb_const.CTREE_CHAR_ENCODING), ParentName.encode(ctdb_const.CTREE_CHAR_ENCODING), CreateMode, filter.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "CreateMRTTable failed.", retval)
  return retval

def GetVTableInfoFromTable(VTableRes, ):
  retval = _ctdbsdk.ctdbGetVTableInfoFromTable(VTableRes, )
  if retval != 0:
    raise DatabaseError( "GetVTableInfoFromTable failed.", retval)
  return retval

def AllocVTableInfo(pTable, size, ):
  retval = _ctdbsdk.ctdbAllocVTableInfo(pTable, size, )
  if retval is None: 
    raise DatabaseError( "AllocVTableInfo failed.") 
  return retval

def FreeVTableInfo(Info, ):
  retval = _ctdbsdk.ctdbFreeVTableInfo(Info, )

def RenameTable(Handle, oldname, newname, ):
  retval = _ctdbsdk.ctdbRenameTable(Handle, oldname.encode(ctdb_const.CTREE_CHAR_ENCODING), newname.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "RenameTable failed.", retval)
  return retval

def MoveTable(Handle, oldname, newpath, newname, ):
  retval = _ctdbsdk.ctdbMoveTable(Handle, oldname.encode(ctdb_const.CTREE_CHAR_ENCODING), newpath.encode(ctdb_const.CTREE_CHAR_ENCODING), newname.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "MoveTable failed.", retval)
  return retval

def OpenTable(Handle, TableName, OpenMode, ):
  retval = _ctdbsdk.ctdbOpenTable(Handle, TableName.encode(ctdb_const.CTREE_CHAR_ENCODING), OpenMode, )
  if retval != 0:
    raise DatabaseError( "OpenTable failed.", retval)
  return retval

def OpenTableByUID(Handle, uid, OpenMode, ):
  retval = _ctdbsdk.ctdbOpenTableByUID(Handle, uid, OpenMode, )
  if retval != 0:
    raise DatabaseError( "OpenTableByUID failed.", retval)
  return retval

def CloseTable(Handle, ):
  retval = _ctdbsdk.ctdbCloseTable(Handle, )
  if retval != 0:
    raise DatabaseError( "CloseTable failed.", retval)
  return retval

def CloseAll(Handle, ):
  retval = _ctdbsdk.ctdbCloseAll(Handle, )
  if retval != 0:
    raise DatabaseError( "CloseAll failed.", retval)
  return retval

def GetTablePassword(Handle, ):
  retval = _ctdbsdk.ctdbGetTablePassword(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTablePassword failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTableGroupid(Handle, ):
  retval = _ctdbsdk.ctdbGetTableGroupid(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTableGroupid failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexExtension(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexExtension(Handle, )
  if retval == 0:
    raise DatabaseError( "GetIndexExtension failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTablePermission(Handle, ):
  retval = _ctdbsdk.ctdbGetTablePermission(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTablePermission failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetTablePassword(Handle, password, ):
  retval = _ctdbsdk.ctdbSetTablePassword(Handle, password.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetTablePassword failed.", retval)
  return retval

def SetTableGroupid(Handle, groupid, ):
  retval = _ctdbsdk.ctdbSetTableGroupid(Handle, groupid.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetTableGroupid failed.", retval)
  return retval

def SetIndexExtension(Handle, ext, ):
  retval = _ctdbsdk.ctdbSetIndexExtension(Handle, ext.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetIndexExtension failed.", retval)
  return retval

def SetTablePermission(Handle, permmask, ):
  retval = _ctdbsdk.ctdbSetTablePermission(Handle, permmask, )
  if retval != 0:
    raise DatabaseError( "SetTablePermission failed.", retval)
  return retval

def GetTableObjptr(Handle, ):
  retval = _ctdbsdk.ctdbGetTableObjptr(Handle, )
  if retval is None: 
    raise DatabaseError( "GetTableObjptr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetTableObjptr(Handle, ptr, ):
  retval = _ctdbsdk.ctdbSetTableObjptr(Handle, ptr, )
  if retval != 0:
    raise DatabaseError( "SetTableObjptr failed.", retval)
  return retval

def GetActiveTableUID(Handle, puid, ):
  retval = _ctdbsdk.ctdbGetActiveTableUID(Handle, puid, )
  if retval != 0:
    raise DatabaseError( "GetActiveTableUID failed.", retval)
  return retval

def AlterTable(Handle, Action):
  retval = _ctdbsdk.ctdbAlterTable(Handle, Action)
  if retval != 0:
    raise DatabaseError( "AlterTable failed.", retval)
  return retval

def ResetAll(Handle, ):
  retval = _ctdbsdk.ctdbResetAll(Handle, )
  if retval != 0:
    raise DatabaseError( "ResetAll failed.", retval)
  return retval

def HasNullFieldSupport(Handle, ):
  retval = _ctdbsdk.ctdbHasNullFieldSupport(Handle, )
  if retval == 0:
    raise DatabaseError( "HasNullFieldSupport failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTableSuperFile(Handle, ):
  retval = _ctdbsdk.ctdbGetTableSuperFile(Handle, )
  if retval is None: 
    raise DatabaseError( "GetTableSuperFile failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetTableSuperFile(Handle, pSuper, ):
  retval = _ctdbsdk.ctdbSetTableSuperFile(Handle, pSuper, )
  if retval != 0:
    raise DatabaseError( "SetTableSuperFile failed.", retval)
  return retval

def UnlockTable(Handle, ):
  retval = _ctdbsdk.ctdbUnlockTable(Handle, )
  if retval != 0:
    raise DatabaseError( "UnlockTable failed.", retval)
  return retval

def GetTableNbr(Handle, ):
  retval = _ctdbsdk.ctdbGetTableNbr(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetTableNbr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetTable(Handle, index, ):
  retval = _ctdbsdk.ctdbGetTable(Handle, index, )
  if retval is None: 
    raise DatabaseError( "GetTable failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def HasRecbyt(Handle):
  retval = _ctdbsdk.ctdbHasRecbyt(Handle)
  return retval

def HasRowid(Handle):
  retval = _ctdbsdk.ctdbHasRowid(Handle)
  return retval

def IsVTable(Handle, ):
  retval = _ctdbsdk.ctdbIsVTable(Handle, )
  if retval == 0:
    raise DatabaseError( "IsVTable failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetVTableNumber(Handle, ):
  retval = _ctdbsdk.ctdbGetVTableNumber(Handle, )
  if retval == 0:
    raise DatabaseError( "GetVTableNumber failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetMRTTableFilter(Handle, condition, ):
  retval = _ctdbsdk.ctdbSetMRTTableFilter(Handle, condition.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetMRTTableFilter failed.", retval)
  return retval

def GetTablePartitionIndexNbr(Handle, ):
  retval = _ctdbsdk.ctdbGetTablePartitionIndexNbr(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTablePartitionIndexNbr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetTablePartitionIndexNbr(Handle, idxno, ):
  retval = _ctdbsdk.ctdbSetTablePartitionIndexNbr(Handle, idxno, )
  if retval != 0:
    raise DatabaseError( "SetTablePartitionIndexNbr failed.", retval)
  return retval

def SetTablePartitionRule(Handle, expr, ):
  retval = _ctdbsdk.ctdbSetTablePartitionRule(Handle, expr.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetTablePartitionRule failed.", retval)
  return retval

def SetMRTTableDefaultIndex(Handle, idxno, min, minlen, max, maxlen, method, ):
  retval = _ctdbsdk.ctdbSetMRTTableDefaultIndex(Handle, idxno, min, minlen, max, maxlen, method, )
  if retval != 0:
    raise DatabaseError( "SetMRTTableDefaultIndex failed.", retval)
  return retval

def PartAdminByName(handle, partname, partmode, partstatus, ):
  retval = _ctdbsdk.ctdbPartAdminByName(handle, partname.encode(ctdb_const.CTREE_CHAR_ENCODING), partmode, partstatus, )
  if retval != 0:
    raise DatabaseError( "PartAdminByName failed.", retval)
  return retval

def PartAdminByKey(handle, keyval, partmode, partstatus, ):
  retval = _ctdbsdk.ctdbPartAdminByKey(handle, keyval, partmode, partstatus, )
  if retval != 0:
    raise DatabaseError( "PartAdminByKey failed.", retval)
  return retval

def PartAdminByNumber(handle, partno, partmode, partstatus, ):
  retval = _ctdbsdk.ctdbPartAdminByNumber(handle, partno, partmode, partstatus, )
  if retval != 0:
    raise DatabaseError( "PartAdminByNumber failed.", retval)
  return retval

def SetIdentityField(Handle, FieldName, seed, increment, ):
  retval = _ctdbsdk.ctdbSetIdentityField(Handle, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), seed, increment, )
  if retval != 0:
    raise DatabaseError( "SetIdentityField failed.", retval)
  return retval

def GetIdentityField(Handle, ):
  retval = _ctdbsdk.ctdbGetIdentityField(Handle, )
  if retval == 0:
    raise DatabaseError( "GetIdentityField failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIdentityFieldDetails(Handle, seed, increment, ):
  retval = _ctdbsdk.ctdbGetIdentityFieldDetails(Handle, seed, increment, )
  if retval == 0:
    raise DatabaseError( "GetIdentityFieldDetails failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFirstPartition(Handle, ):
  retval = _ctdbsdk.ctdbGetFirstPartition(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetFirstPartition failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetLastPartition(Handle, ):
  retval = _ctdbsdk.ctdbGetLastPartition(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetLastPartition failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetPadChar(Handle, pPadchar, pDmlchar):
  retval = _ctdbsdk.ctdbGetPadChar(Handle, pPadchar, pDmlchar)
  if retval != 0:
    raise DatabaseError( "GetPadChar failed.", retval)
  return retval

def SetPadChar(Handle, padchar, dmlchar):
  if type(padchar) == str:
    padchar = ord(padchar[0])
  if type(dmlchar) == str:
    dmlchar = ord(dmlchar[0])
  retval = _ctdbsdk.ctdbSetPadChar(Handle, padchar, dmlchar)
  if retval != 0:
    raise DatabaseError( "SetPadChar failed.", retval)
  return retval

def UpdatePadChar(Handle, padchar, dmlchar, rebuild):
  if type(padchar) == str:
    padchar = ord(padchar[0])
  if type(dmlchar) == str:
    dmlchar = ord(dmlchar[0])
  retval = _ctdbsdk.ctdbUpdatePadChar(Handle, padchar, dmlchar, rebuild)
  if retval != 0:
    raise DatabaseError( "UpdatePadChar failed.", retval)
  return retval

def UpdateCreateMode(Handle, mode, ):
  retval = _ctdbsdk.ctdbUpdateCreateMode(Handle, mode, )
  if retval != 0:
    raise DatabaseError( "UpdateCreateMode failed.", retval)
  return retval

def HasDelField(Handle):
  retval = _ctdbsdk.ctdbHasDelField(Handle)
  return retval

def GetDatno(Handle):
  retval = _ctdbsdk.ctdbGetDatno(Handle)
  if retval == -1: 
    raise DatabaseError( "GetDatno failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIdxnoByNumber(Handle, index, ):
  retval = _ctdbsdk.ctdbGetIdxnoByNumber(Handle, index, )
  if retval == -1: 
    raise DatabaseError( "GetIdxnoByNumber failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIdxnoByName(Handle, indexname, ):
  retval = _ctdbsdk.ctdbGetIdxnoByName(Handle, indexname.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval == -1: 
    raise DatabaseError( "GetIdxnoByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def RemoveTable(Handle, ):
  retval = _ctdbsdk.ctdbRemoveTable(Handle, )
  if retval != 0:
    raise DatabaseError( "RemoveTable failed.", retval)
  return retval

def GetTableType(Handle, ):
  retval = _ctdbsdk.ctdbGetTableType(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTableType failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetRebuildProgress(Handle, ):
  retval = _ctdbsdk.ctdbGetRebuildProgress(Handle, )
  if retval == 0:
    raise DatabaseError( "GetRebuildProgress failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SystemFilterOn(Handle, mode, ):
  retval = _ctdbsdk.ctdbSystemFilterOn(Handle, mode, )
  if retval != 0:
    raise DatabaseError( "SystemFilterOn failed.", retval)
  return retval

def SystemFilterOff(Handle, mode, ):
  retval = _ctdbsdk.ctdbSystemFilterOff(Handle, mode, )
  if retval != 0:
    raise DatabaseError( "SystemFilterOff failed.", retval)
  return retval

def SetTableKSeg(Handle, pKSeg, ):
  retval = _ctdbsdk.ctdbSetTableKSeg(Handle, pKSeg, )
  if retval != 0:
    raise DatabaseError( "SetTableKSeg failed.", retval)
  return retval

def GetTableKSeg(Handle, pKSeg, ):
  retval = _ctdbsdk.ctdbGetTableKSeg(Handle, pKSeg, )
  if retval != 0:
    raise DatabaseError( "GetTableKSeg failed.", retval)
  return retval

def GetTableStatus(Handle, ):
  retval = _ctdbsdk.ctdbGetTableStatus(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTableStatus failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AttachTable(Handle, datno, ):
  retval = _ctdbsdk.ctdbAttachTable(Handle, datno, )
  if retval != 0:
    raise DatabaseError( "AttachTable failed.", retval)
  return retval

def AttachTableXtd(Handle, datno, nbrfields, dodaptr, ifilptr, ):
  retval = _ctdbsdk.ctdbAttachTableXtd(Handle, datno, nbrfields, dodaptr, ifilptr, )
  if retval != 0:
    raise DatabaseError( "AttachTableXtd failed.", retval)
  return retval

def DetachTable(Handle, ):
  retval = _ctdbsdk.ctdbDetachTable(Handle, )
  if retval != 0:
    raise DatabaseError( "DetachTable failed.", retval)
  return retval

def GetTableOwner(Handle, ):
  retval = _ctdbsdk.ctdbGetTableOwner(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTableOwner failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval if retval is None else retval.decode(ctdb_const.CTREE_CHAR_ENCODING)

def SetTableOwner(Handle, owner):
  retval = _ctdbsdk.ctdbSetTableOwner(Handle, owner.encode(ctdb_const.CTREE_CHAR_ENCODING))
  if retval != 0:
    raise DatabaseError( "SetTableOwner failed.", retval)
  return retval

def RebuildTable(Handle, mode):
  retval = _ctdbsdk.ctdbRebuildTable(Handle, mode)
  if retval != 0 and retval != 650: 
    raise DatabaseError( "RebuildTable failed.", retval)
  return retval

def SetCallbackOnRebuild(funcptr, step, ):
  retval = _ctdbsdk.ctdbSetCallbackOnRebuild(funcptr, step, )
  if retval == 0:
    raise DatabaseError( "SetCallbackOnRebuild failed.") 
  return retval

def AllocResource(Handle, type, number, name):
  retval = _ctdbsdk.ctdbAllocResource(Handle, type, number, name if name is None else name.encode(ctdb_const.CTREE_CHAR_ENCODING))
  if retval is None: 
    raise DatabaseError( "AllocResource failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeResource(resource, ):
  retval = _ctdbsdk.ctdbFreeResource(resource, )
  if retval != 0:
    raise DatabaseError( "FreeResource failed.", retval)
  return retval

def UnlockResource(resource, ):
  retval = _ctdbsdk.ctdbUnlockResource(resource, )
  if retval != 0:
    raise DatabaseError( "UnlockResource failed.", retval)
  return retval

def AddResource(resource, data, size, ):
  retval = _ctdbsdk.ctdbAddResource(resource, data, size, )
  if retval != 0:
    raise DatabaseError( "AddResource failed.", retval)
  return retval

def DeleteResource(resource, ):
  retval = _ctdbsdk.ctdbDeleteResource(resource, )
  if retval != 0:
    raise DatabaseError( "DeleteResource failed.", retval)
  return retval

def UpdateResource(resource, data, size, ):
  retval = _ctdbsdk.ctdbUpdateResource(resource, data, size, )
  if retval != 0:
    raise DatabaseError( "UpdateResource failed.", retval)
  return retval

def FirstResource(resource, lock, ):
  retval = _ctdbsdk.ctdbFirstResource(resource, lock, )
  if retval != 0 and retval != 408:
    raise DatabaseError( "FirstResource failed.", retval)
  return retval

def NextResource(resource, lock, ):
  retval = _ctdbsdk.ctdbNextResource(resource, lock, )
  if retval != 0 and retval != 408:
    raise DatabaseError( "NextResource failed.", retval)
  return retval

def FindResource(resource, type, number, lock, ):
  retval = _ctdbsdk.ctdbFindResource(resource, type, number, lock, )
  if retval != 0:
    raise DatabaseError( "FindResource failed.", retval)
  return retval

def FindResourceByName(resource, name, lock, ):
  retval = _ctdbsdk.ctdbFindResourceByName(resource, name.encode(ctdb_const.CTREE_CHAR_ENCODING), lock, )
  if retval != 0:
    raise DatabaseError( "FindResourceByName failed.", retval)
  return retval

def IsResourceLocked(resource, ):
  retval = _ctdbsdk.ctdbIsResourceLocked(resource, )
  return retval

def GetResourceType(resource, ):
  retval = _ctdbsdk.ctdbGetResourceType(resource, )
  if retval == 0:
    raise DatabaseError( "GetResourceType failed.") 
  return retval

def SetResourceType(resource, type, ):
  retval = _ctdbsdk.ctdbSetResourceType(resource, type, )
  if retval != 0:
    raise DatabaseError( "SetResourceType failed.", retval)
  return retval

def GetResourceNumber(resource, ):
  retval = _ctdbsdk.ctdbGetResourceNumber(resource, )
  return retval

def SetResourceNumber(resource, number, ):
  retval = _ctdbsdk.ctdbSetResourceNumber(resource, number, )
  if retval != 0:
    raise DatabaseError( "SetResourceNumber failed.", retval)
  return retval

def GetResourceName(resource, ):
  retval = _ctdbsdk.ctdbGetResourceName(resource, )
  if retval == 0:
    raise DatabaseError( "GetResourceName failed.") 
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING)

def SetResourceName(resource, name, ):
  retval = _ctdbsdk.ctdbSetResourceName(resource, name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetResourceName failed.", retval)
  return retval

def GetResourceDataLength(resource, ):
  retval = _ctdbsdk.ctdbGetResourceDataLength(resource, )
  if retval == 0:
    raise DatabaseError( "GetResourceDataLength failed.") 
  return retval

def GetResourceData(resource, ):
  retval = _ctdbsdk.ctdbGetResourceData(resource, )
  if retval is None: 
    raise DatabaseError( "GetResourceData failed.") 
  return retval

def SetResourceData(resource, data, size, ):
  retval = _ctdbsdk.ctdbSetResourceData(resource, data, size, )
  if retval != 0:
    raise DatabaseError( "SetResourceData failed.", retval)
  return retval

def GetBinaryFlag(Handle, fldno, ):
  retval = _ctdbsdk.ctdbGetBinaryFlag(Handle, fldno, )
  if retval == 0:
    raise DatabaseError( "GetBinaryFlag failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetBinaryFlag(Handle, fldno, flag, ): 
  retval = _ctdbsdk.ctdbSetBinaryFlag(Handle, fldno, flag, )
  if retval != 0:
    raise DatabaseError( "SetBinaryFlag failed.", retval)
  return retval

def CloneTable(tarHandle, tarTableName, srcHandle, ):
  retval = _ctdbsdk.ctdbCloneTable(tarHandle, tarTableName.encode(ctdb_const.CTREE_CHAR_ENCODING), srcHandle, )
  if retval != 0:
    raise DatabaseError( "CloneTable failed.", retval)
  return retval

def SetExtensionHint(Handle, ExtHint, ):
  retval = _ctdbsdk.ctdbSetExtensionHint(Handle, ExtHint, )
  if retval != 0:
    raise DatabaseError( "SetExtensionHint failed.", retval)
  return retval

def GetExtensionHint(Handle, ):
  retval = _ctdbsdk.ctdbGetExtensionHint(Handle, )
  if retval == 0:
    raise DatabaseError( "GetExtensionHint failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def CheckRecordSchemaConversion(Handle, status, ):
  retval = _ctdbsdk.ctdbCheckRecordSchemaConversion(Handle, status, )
  if retval != 0:
    raise DatabaseError( "CheckRecordSchemaConversion failed.", retval)
  return retval

def StartRecordSchemaConversion(Handle, ):
  retval = _ctdbsdk.ctdbStartRecordSchemaConversion(Handle, )
  if retval != 0:
    raise DatabaseError( "StartRecordSchemaConversion failed.", retval)
  return retval

def TableHasCallback(Handle, ):
  retval = _ctdbsdk.ctdbTableHasCallback(Handle, )
  if retval == 0:
    raise DatabaseError( "TableHasCallback failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetRecordHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetRecordHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetRecordHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AllocRecord(Handle, ):
  retval = _ctdbsdk.ctdbAllocRecord(Handle, )
  if retval is None: 
    raise DatabaseError( "AllocRecord failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def DuplicateRecord(Handle, ):
  retval = _ctdbsdk.ctdbDuplicateRecord(Handle, )
  if retval is None: 
    raise DatabaseError( "DuplicateRecord failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def CopyRecordBuffer(Source, Dest, ):
  retval = _ctdbsdk.ctdbCopyRecordBuffer(Source, Dest, )
  if retval != 0:
    raise DatabaseError( "CopyRecordBuffer failed.", retval)
  return retval

def AssignRecordBuffer(Handle, pBuffer, reclen, ):
  retval = _ctdbsdk.ctdbAssignRecordBuffer(Handle, pBuffer, reclen, )
  if retval != 0:
    raise DatabaseError( "AssignRecordBuffer failed.", retval)
  return retval

def FreeRecord(Handle, ):
  retval = _ctdbsdk.ctdbFreeRecord(Handle, )

def ResetRecord(Handle, ):
  retval = _ctdbsdk.ctdbResetRecord(Handle, )
  if retval != 0:
    raise DatabaseError( "ResetRecord failed.", retval)
  return retval

def FirstRecord(Handle, ):
  retval = _ctdbsdk.ctdbFirstRecord(Handle, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "FirstRecord failed.", retval)
  return retval

def LastRecord(Handle, ):
  retval = _ctdbsdk.ctdbLastRecord(Handle, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "LastRecord failed.", retval)
  return retval

def NextRecord(Handle, ):
  retval = _ctdbsdk.ctdbNextRecord(Handle, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "NextRecord failed.", retval)
  return retval

def PrevRecord(Handle, ):
  retval = _ctdbsdk.ctdbPrevRecord(Handle, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "PrevRecord failed.", retval)
  return retval

def FindTarget(Handle, target, FindMode, ):
  retval = _ctdbsdk.ctdbFindTarget(Handle, target, FindMode, )
  if retval != 0:
    raise DatabaseError( "FindTarget failed.", retval)
  return retval

def FindRecord(Handle, FindMode, ):
  retval = _ctdbsdk.ctdbFindRecord(Handle, FindMode, )
  if retval != 0 and retval != 101:
    raise DatabaseError( "FindRecord failed.", retval)
  return retval

def LocateRecord(Handle, LocateMode, ):
  retval = _ctdbsdk.ctdbLocateRecord(Handle, LocateMode, )
  if retval == 0:
    raise DatabaseError( "LocateRecord failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetRecordCriteria(Handle, LocateMode, ):
  retval = _ctdbsdk.ctdbSetRecordCriteria(Handle, LocateMode, )
  if retval != 0:
    raise DatabaseError( "SetRecordCriteria failed.", retval)
  return retval

def UpdateRecordCriteria(Handle, LocateMode, ):
  retval = _ctdbsdk.ctdbUpdateRecordCriteria(Handle, LocateMode, )
  if retval != 0:
    raise DatabaseError( "UpdateRecordCriteria failed.", retval)
  return retval

def GetBestIndex(Handle, fieldNameList, LocateMode, ):
  retval = _ctdbsdk.ctdbGetBestIndex(Handle, fieldNameList, LocateMode, )
  if retval is None: 
    raise DatabaseError( "GetBestIndex failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AddLocateCriteria(Handle, LocateFieldName, LocateFieldValue, ):
  retval = _ctdbsdk.ctdbAddLocateCriteria(Handle, LocateFieldName, LocateFieldValue, )
  if retval != 0:
    raise DatabaseError( "AddLocateCriteria failed.", retval)
  return retval

def ClearRecord(Handle, ):
  retval = _ctdbsdk.ctdbClearRecord(Handle, )
  if retval != 0:
    raise DatabaseError( "ClearRecord failed.", retval)
  return retval

def ReadRecord(Handle, ):
  retval = _ctdbsdk.ctdbReadRecord(Handle, )
  if retval != 0:
    raise DatabaseError( "ReadRecord failed.", retval)
  return retval

def WriteRecord(Handle, ):
  retval = _ctdbsdk.ctdbWriteRecord(Handle, )
  if retval != 0:
    raise DatabaseError( "WriteRecord failed.", retval)
  return retval

def DeleteRecord(Handle, ):
  retval = _ctdbsdk.ctdbDeleteRecord(Handle, )
  if retval != 0:
    raise DatabaseError( "DeleteRecord failed.", retval)
  return retval

def GetRecordBuffer(Handle, ):
  retval = _ctdbsdk.ctdbGetRecordBuffer(Handle, )
  if retval is None: 
    raise DatabaseError( "GetRecordBuffer failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetRecordLength(Handle, ):
  retval = _ctdbsdk.ctdbGetRecordLength(Handle, )
  if retval == 0:
    raise DatabaseError( "GetRecordLength failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetRecordSize(Handle, ):
  retval = _ctdbsdk.ctdbGetRecordSize(Handle, )
  if retval == 0:
    raise DatabaseError( "GetRecordSize failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def IsNewRecord(Handle, ):
  retval = _ctdbsdk.ctdbIsNewRecord(Handle, )
  return retval

def IsEditedRecord(Handle, ):
  retval = _ctdbsdk.ctdbIsEditedRecord(Handle, )
  return retval

def SetNewRecord(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetNewRecord(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetNewRecord failed.", retval)
  return retval

def SetEditedRecord(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetEditedRecord(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetEditedRecord failed.", retval)
  return retval

def SetRecordBuffer(Handle, pBuffer, reclen, mode, ):
  retval = _ctdbsdk.ctdbSetRecordBuffer(Handle, pBuffer, reclen, mode, )
  if retval != 0:
    raise DatabaseError( "SetRecordBuffer failed.", retval)
  return retval

def IsNullField(Handle, FieldNbr): 
  retval = _ctdbsdk.ctdbIsNullField(Handle, FieldNbr)
  return retval

def GetRecordPos(Handle, pOffset, ):
  retval = _ctdbsdk.ctdbGetRecordPos(Handle, pOffset, )
  if retval != 0:
    raise DatabaseError( "GetRecordPos failed.", retval)
  return retval

def GetRecordKeyPos(Handle, pPosition, ):
  retval = _ctdbsdk.ctdbGetRecordKeyPos(Handle, pPosition, )
  if retval != 0:
    raise DatabaseError( "GetRecordKeyPos failed.", retval)
  return retval

def SetRecordPos(Handle, offset, ):
  retval = _ctdbsdk.ctdbSetRecordPos(Handle, offset, )
  if retval != 0:
    raise DatabaseError( "SetRecordPos failed.", retval)
  return retval

def SetRecordOffset(Handle, offset, ):
  retval = _ctdbsdk.ctdbSetRecordOffset(Handle, offset, )
  if retval != 0:
    raise DatabaseError( "SetRecordOffset failed.", retval)
  return retval

def SeekRecord(Handle, offset, ):
  retval = _ctdbsdk.ctdbSeekRecord(Handle, offset, )
  if retval != 0:
    raise DatabaseError( "SeekRecord failed.", retval)
  return retval

def GetDefaultIndex(Handle, ):
  retval = _ctdbsdk.ctdbGetDefaultIndex(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetDefaultIndex failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetDefaultIndexName(Handle, ):
  retval = _ctdbsdk.ctdbGetDefaultIndexName(Handle, )
  if retval == 0:
    raise DatabaseError( "GetDefaultIndexName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING)

def SetDefaultIndex(Handle, indexno, ):
  retval = _ctdbsdk.ctdbSetDefaultIndex(Handle, indexno, )
  if retval != 0:
    raise DatabaseError( "SetDefaultIndex failed.", retval)
  return retval

def SetDefaultIndexByName(Handle, name, ):
  retval = _ctdbsdk.ctdbSetDefaultIndexByName(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetDefaultIndexByName failed.", retval)
  return retval

def GetFieldNumberByName(Handle, FieldName, ):
  retval = _ctdbsdk.ctdbGetFieldNumberByName(Handle, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval == -1: 
    raise DatabaseError( "GetFieldNumberByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFieldAsBool(Handle, FieldNumber, pValue):
  retval = _ctdbsdk.ctdbGetFieldAsBool(Handle, FieldNumber, pValue)
  if retval != 0:
    raise DatabaseError( "GetFieldAsBool failed.", retval)
  return retval

def GetFieldAsSigned(Handle, FieldNbr, pValue, ): 
  retval = _ctdbsdk.ctdbGetFieldAsSigned(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsSigned failed.", retval)
  return retval

def GetFieldAsUnsigned(Handle, FieldNbr, pValue, ): 
  retval = _ctdbsdk.ctdbGetFieldAsUnsigned(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsUnsigned failed.", retval)
  return retval

def GetFieldAsDate(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsDate(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsDate failed.", retval)
  return retval

def GetFieldAsTime(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsTime(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsTime failed.", retval)
  return retval

def GetFieldAsTimeMsec(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsTimeMsec(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsTimeMsec failed.", retval)
  return retval

def GetFieldAsMoney(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsMoney(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsMoney failed.", retval)
  return retval

def GetFieldAsFloat(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsFloat(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsFloat failed.", retval)
  return retval

def GetFieldAsDateTime(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsDateTime(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsDateTime failed.", retval)
  return retval

def GetFieldAsString(Handle, FieldNbr, pValue, size, ):
  retval = _ctdbsdk.ctdbIsNullField(Handle, FieldNbr)
  if retval==1:
    pValue.raw=str.encode("None",ctdb_const.CTREE_CHAR_ENCODING)
    return True
  retval = _ctdbsdk.ctdbGetFieldAsString(Handle, FieldNbr, pValue, size, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsString failed.", retval)
  return retval

def GetFieldAsJSON(Handle, FieldNbr, pValue, size, ):
  retval = _ctdbsdk.ctdbGetFieldAsJSON(Handle, FieldNbr, pValue, size, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsJSON failed.", retval)
  return retval

def GetFieldAsBinary(Handle, FieldNbr, pValue, size, ):
  retval = _ctdbsdk.ctdbGetFieldAsBinary(Handle, FieldNbr, pValue, size, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsBinary failed.", retval)
  return retval

def GetFieldAsBlob(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsBlob(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsBlob failed.", retval)
  return retval

def GetFieldAsBigint(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsBigint(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsBigint failed.", retval)
  return retval

def GetFieldAsUnsignedBigint(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsUnsignedBigint(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsUnsignedBigint failed.", retval)
  return retval

def GetFieldAsCurrency(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsCurrency(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsCurrency failed.", retval)
  return retval

def GetFieldAsNumber(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbGetFieldAsNumber(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "GetFieldAsNumber failed.", retval)
  return retval

def SetFieldAsBool(Handle, FieldNbr, Value, ):
  retval = _ctdbsdk.ctdbSetFieldAsBool(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsBool failed.", retval)
  return retval

def SetFieldAsSigned(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsSigned(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsSigned failed.", retval)
  return retval

def SetFieldAsUnsigned(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsUnsigned(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsUnsigned failed.", retval)
  return retval

def SetFieldAsDate(Handle, FieldNbr, Value, ):
  retval = _ctdbsdk.ctdbSetFieldAsDate(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsDate failed.", retval)
  return retval

def SetFieldAsTime(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsTime(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsTime failed.", retval)
  return retval

def SetFieldAsTimeMsec(Handle, FieldNbr, value, ):
  retval = _ctdbsdk.ctdbSetFieldAsTimeMsec(Handle, FieldNbr, value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsTimeMsec failed.", retval)
  return retval

def SetFieldAsMoney(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsMoney(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsMoney failed.", retval)
  return retval

def SetFieldAsFloat(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsFloat(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsFloat failed.", retval)
  return retval

def SetFieldAsDateTime(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsDateTime(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsDateTime failed.", retval)
  return retval

def SetFieldAsString(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsString(Handle, FieldNbr, Value.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetFieldAsString failed.", retval)
  return retval

def SetFieldAsJSON(Handle, FieldNbr, Value, ):
  retval = _ctdbsdk.ctdbSetFieldAsJSON(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsJSON failed.", retval)
  return retval

def SetFieldAsBinary(Handle, FieldNbr, pValue, size, ):
  retval = _ctdbsdk.ctdbSetFieldAsBinary(Handle, FieldNbr, pValue, size, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsBinary failed.", retval)
  return retval

def SetFieldAsBlob(Handle, FieldNbr, pValue, ):
  retval = _ctdbsdk.ctdbSetFieldAsBlob(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsBlob failed.", retval)
  return retval

def SetFieldAsBigint(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsBigint(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsBigint failed.", retval)
  return retval

def SetFieldAsUnsignedBigint(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsUnsignedBigint(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsUnsignedBigint failed.", retval)
  return retval

def SetFieldAsCurrency(Handle, FieldNbr, Value, ): 
  retval = _ctdbsdk.ctdbSetFieldAsCurrency(Handle, FieldNbr, Value, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsCurrency failed.", retval)
  return retval

def SetFieldAsNumber(Handle, FieldNbr, pValue, ): 
  retval = _ctdbsdk.ctdbSetFieldAsNumber(Handle, FieldNbr, pValue, )
  if retval != 0:
    raise DatabaseError( "SetFieldAsNumber failed.", retval)
  return retval

def GetRecordCount(Handle):
  value = ctypes.c_uint64()
  retval = _ctdbsdk.ctdbGetRecordCount(Handle, ctypes.byref(value))
  if retval != 0:
    raise DatabaseError( "GetRecordCount failed.", retval)
  return value.value

def RecordSetOn(Handle, siglen):
  retval = _ctdbsdk.ctdbRecordSetOn(Handle, siglen)
  if retval != 0:
    raise DatabaseError( "RecordSetOn failed.", retval)
  return retval

def RecordSetOff(Handle, ):
  retval = _ctdbsdk.ctdbRecordSetOff(Handle, )
  if retval != 0:
    raise DatabaseError( "RecordSetOff failed.", retval)
  return retval

def IsRecordSetOn(Handle, ):
  retval = _ctdbsdk.ctdbIsRecordSetOn(Handle, )
  return retval

def IsVariableField(Handle, FieldNbr, ):
  retval = _ctdbsdk.ctdbIsVariableField(Handle, FieldNbr, )
  return retval

def GetFieldDataLength(Handle, FieldNbr, ):
  retval = _ctdbsdk.ctdbGetFieldDataLength(Handle, FieldNbr, )
  return retval

def GetFieldSize(Handle, FieldNbr):
  retval = _ctdbsdk.ctdbGetFieldSize(Handle, FieldNbr)
  return retval

def GetFieldOffset(Handle, FieldNbr, ):
  retval = _ctdbsdk.ctdbGetFieldOffset(Handle, FieldNbr, )
  return retval

def GetFieldAddress(Handle, FieldNbr):
  retval = _ctdbsdk.ctdbGetFieldAddress(Handle, FieldNbr)
  if retval is None: 
    raise DatabaseError( "GetFieldAddress failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def ClearField(Handle, FieldNbr, ): 
  retval = _ctdbsdk.ctdbClearField(Handle, FieldNbr, )
  if retval != 0:
    raise DatabaseError( "ClearField failed.", retval)
  return retval

def LockRecord(Handle, mode, ):
  retval = _ctdbsdk.ctdbLockRecord(Handle, mode, )
  if retval != 0:
    raise DatabaseError( "LockRecord failed.", retval)
  return retval

def UnlockRecord(Handle, ):
  retval = _ctdbsdk.ctdbUnlockRecord(Handle, )
  if retval != 0:
    raise DatabaseError( "UnlockRecord failed.", retval)
  return retval

def BuildTargetKey(Handle, FindMode, targetkey, targetlen, ):
  retval = _ctdbsdk.ctdbBuildTargetKey(Handle, FindMode, targetkey, targetlen, )
  if retval != 0:
    raise DatabaseError( "BuildTargetKey failed.", retval)
  return retval

def GetFieldData(pRecord, FieldNbr, ):
  retval = _ctdbsdk.ctdbGetFieldData(pRecord, FieldNbr, )
  if retval is None: 
    raise DatabaseError( "GetFieldData failed.") 
  return retval

def GetRecordNbr(Handle, ):
  retval = _ctdbsdk.ctdbGetRecordNbr(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetRecordNbr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetRecord(Handle, index, ):
  retval = _ctdbsdk.ctdbGetRecord(Handle, index, )
  if retval is None: 
    raise DatabaseError( "GetRecord failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetRowid(Handle):
  value = ctypes.c_uint64()
  retval = _ctdbsdk.ctdbGetRowid(Handle, ctypes.byref(value) )
  if retval != 0:
    raise DatabaseError( "GetRowid failed.", retval)
  return value.value

def FindRowid(Handle, rowid, FindMode, ):
  retval = _ctdbsdk.ctdbFindRowid(Handle, rowid, FindMode, )
  if retval != 0:
    raise DatabaseError( "FindRowid failed.", retval)
  return retval

def FindKey(Handle, pOffset, FindMode, ):
  retval = _ctdbsdk.ctdbFindKey(Handle, pOffset, FindMode, )
  if retval != 0:
    raise DatabaseError( "FindKey failed.", retval)
  return retval

def RecordBlockingReadOn(Handle, timeoutsec, condition, ):
  retval = _ctdbsdk.ctdbRecordBlockingReadOn(Handle, timeoutsec, condition.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "RecordBlockingReadOn failed.", retval)
  return retval

def IsRecordBlockingReadOn(Handle, ):
  retval = _ctdbsdk.ctdbIsRecordBlockingReadOn(Handle, )
  if retval == 0:
    raise DatabaseError( "IsRecordBlockingReadOn failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def RecordBlockingReadOff(Handle, ):
  retval = _ctdbsdk.ctdbRecordBlockingReadOff(Handle, )
  if retval != 0:
    raise DatabaseError( "RecordBlockingReadOff failed.", retval)
  return retval

def FilterRecord(Handle, cndexpr, ):
  retval = _ctdbsdk.ctdbFilterRecord(Handle, cndexpr.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "FilterRecord failed.", retval)
  return retval

def IsFilteredRecord(Handle, ):
  retval = _ctdbsdk.ctdbIsFilteredRecord(Handle, )
  return retval

def GetFilter(Handle):
  retval = _ctdbsdk.ctdbGetFilter(Handle)
  if retval == 0:
    raise DatabaseError( "GetFilter failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING) if retval else reval


def GetRecordLock(Handle, ):
  retval = _ctdbsdk.ctdbGetRecordLock(Handle, )
  if retval == 0:
    raise DatabaseError( "GetRecordLock failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def CompareRecords(Handle1, Handle2, ):
  retval = _ctdbsdk.ctdbCompareRecords(Handle1, Handle2, )
  if retval != 0:
    raise DatabaseError( "CompareRecords failed.", retval)
  return retval

def RecordAtPercentile(Handle, percent):
  retval = _ctdbsdk.ctdbRecordAtPercentile(Handle, percent)
  if retval != 0:
    raise DatabaseError( "RecordAtPercentile failed.", retval)
  return retval

def RecordPosAtOffset(Handle, offset, ):
  retval = _ctdbsdk.ctdbRecordPosAtOffset(Handle, offset, )
  if retval != 0:
    raise DatabaseError( "RecordPosAtOffset failed.", retval)
  return retval

def EstimateSpan(Handle, key1, key2, ): 
  retval = _ctdbsdk.ctdbEstimateSpan(Handle, key1, key2, )
  if retval == 0:
    raise DatabaseError( "EstimateSpan failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def RecordRangeOn(Handle, SegCount, lRange, uRange, operators, ):
  retval = _ctdbsdk.ctdbRecordRangeOn(Handle, SegCount, lRange, uRange, operators, )
  if retval != 0:
    raise DatabaseError( "RecordRangeOn failed.", retval)
  return retval

def RecordRangeXtdOn(Handle, SegCount, lRange, uRange, operators, rangeFlag, ):
  retval = _ctdbsdk.ctdbRecordRangeXtdOn(Handle, SegCount, lRange, uRange, operators, rangeFlag, )
  if retval != 0:
    raise DatabaseError( "RecordRangeXtdOn failed.", retval)
  return retval

def RecordRangeOff(Handle, ):
  retval = _ctdbsdk.ctdbRecordRangeOff(Handle, )
  if retval != 0:
    raise DatabaseError( "RecordRangeOff failed.", retval)
  return retval

def IsRecordRangeOn(Handle, ):
  retval = _ctdbsdk.ctdbIsRecordRangeOn(Handle, )
  if retval == 0:
    raise DatabaseError( "IsRecordRangeOn failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SwitchContext(Handle):
  retval = _ctdbsdk.ctdbSwitchContext(Handle)
  if retval != 0:
    raise DatabaseError( "SwitchContext failed.", retval)
  return retval

def BatchLoaded(Handle, ):
  retval = _ctdbsdk.ctdbBatchLoaded(Handle, )
  if retval == 0:
    raise DatabaseError( "BatchLoaded failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def BatchLocked(Handle, ):
  retval = _ctdbsdk.ctdbBatchLocked(Handle, )
  if retval == 0:
    raise DatabaseError( "BatchLocked failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def BatchTotal(Handle, ):
  retval = _ctdbsdk.ctdbBatchTotal(Handle, )
  if retval == 0:
    raise DatabaseError( "BatchTotal failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def BatchMode(Handle, ):
  retval = _ctdbsdk.ctdbBatchMode(Handle, )
  if retval == 0:
    raise DatabaseError( "BatchMode failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def EndBatch(Handle, ):
  retval = _ctdbsdk.ctdbEndBatch(Handle, )
  if retval != 0:
    raise DatabaseError( "EndBatch failed.", retval)
  return retval

def InsertBatch(Handle, ):
  retval = _ctdbsdk.ctdbInsertBatch(Handle, )
  if retval != 0:
    raise DatabaseError( "InsertBatch failed.", retval)
  return retval

def IsBatchActive(Handle, ):
  retval = _ctdbsdk.ctdbIsBatchActive(Handle, )
  return retval

def NextBatch(Handle, ):
  retval = _ctdbsdk.ctdbNextBatch(Handle, )
  if retval != 0:
    raise DatabaseError( "NextBatch failed.", retval)
  return retval

def SetBatch(Handle, mode, targetLen, bufferLen, ):
  retval = _ctdbsdk.ctdbSetBatch(Handle, mode, targetLen, bufferLen, )
  if retval != 0:
    raise DatabaseError( "SetBatch failed.", retval)
  return retval

def SetBatchFilter(Handle, expr, ):
  retval = _ctdbsdk.ctdbSetBatchFilter(Handle, expr.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetBatchFilter failed.", retval)
  return retval

def SetBatchRangeOn(Handle, SegCount, lRange, uRange, operators, ):
  retval = _ctdbsdk.ctdbSetBatchRangeOn(Handle, SegCount, lRange, uRange, operators, )
  if retval != 0:
    raise DatabaseError( "SetBatchRangeOn failed.", retval)
  return retval

def SetBatchRangeOff(Handle, ):
  retval = _ctdbsdk.ctdbSetBatchRangeOff(Handle, )
  if retval != 0:
    raise DatabaseError( "SetBatchRangeOff failed.", retval)
  return retval

def GetErrorIndex(Handle):
  retval = _ctdbsdk.ctdbGetErrorIndex(Handle)
  if retval == -1: 
    raise DatabaseError( "GetErrorIndex failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def NumberOfKeyEntries(Handle, IndexNumber ):
  retval = _ctdbsdk.ctdbNumberOfKeyEntries(Handle, IndexNumber)
  if retval == -1: 
    raise DatabaseError( "NumberOfKeyEntries failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def JumpToRecord(Handle, offset):
  retval = _ctdbsdk.ctdbJumpToRecord(Handle, offset)
  if retval != 0:
    raise DatabaseError( "JumpToRecord failed.", retval)
  return retval

def GetLastIdentity(Handle, value, ):
  retval = _ctdbsdk.ctdbGetLastIdentity(Handle, value, )
  if retval != 0:
    raise DatabaseError( "GetLastIdentity failed.", retval)
  return retval

def ParseRecordExpr(Handle, expr, exprType, exprIdx, ):
  retval = _ctdbsdk.ctdbParseRecordExpr(Handle, expr.encode(ctdb_const.CTREE_CHAR_ENCODING), exprType, exprIdx, )
  if retval != 0:
    raise DatabaseError( "ParseRecordExpr failed.", retval)
  return retval

def EvalExprAsSigned(Handle, exprIdx, exprValue, ):
  retval = _ctdbsdk.ctdbEvalExprAsSigned(Handle, exprIdx, exprValue, )
  if retval != 0:
    raise DatabaseError( "EvalExprAsSigned failed.", retval)
  return retval

def EvalExprAsDate(Handle, exprIdx, exprValue, ):
  retval = _ctdbsdk.ctdbEvalExprAsDate(Handle, exprIdx, exprValue, )
  if retval != 0:
    raise DatabaseError( "EvalExprAsDate failed.", retval)
  return retval

def EvalExprAsTime(Handle, exprIdx, exprValue, ):
  retval = _ctdbsdk.ctdbEvalExprAsTime(Handle, exprIdx, exprValue, )
  if retval != 0:
    raise DatabaseError( "EvalExprAsTime failed.", retval)
  return retval

def EvalExprAsDateTime(Handle, exprIdx, exprValue, ):
  retval = _ctdbsdk.ctdbEvalExprAsDateTime(Handle, exprIdx, exprValue, )
  if retval != 0:
    raise DatabaseError( "EvalExprAsDateTime failed.", retval)
  return retval

def EvalExprAsNumber(Handle, exprIdx, exprValue, ):
  retval = _ctdbsdk.ctdbEvalExprAsNumber(Handle, exprIdx, exprValue, )
  if retval != 0:
    raise DatabaseError( "EvalExprAsNumber failed.", retval)
  return retval

def EvalExprAsString(Handle, exprIdx, exprValue, exprValueLen, ):
  retval = _ctdbsdk.ctdbEvalExprAsString(Handle, exprIdx, exprValue.encode(ctdb_const.CTREE_CHAR_ENCODING), exprValueLen, )
  if retval != 0:
    raise DatabaseError( "EvalExprAsString failed.", retval)
  return retval

def AddUserDefFunc(Handle, funcName, funcPointer, funcRetType, funcArgTypes, funcArgCount, ):
  retval = _ctdbsdk.ctdbAddUserDefFunc(Handle, funcName.encode(ctdb_const.CTREE_CHAR_ENCODING), funcPointer, funcRetType, funcArgTypes, funcArgCount, )
  if retval != 0:
    raise DatabaseError( "AddUserDefFunc failed.", retval)
  return retval

def GetActiveResultSet(Handle, ):
  retval = _ctdbsdk.ctdbGetActiveResultSet(Handle, )
  if retval is None: 
    raise DatabaseError( "GetActiveResultSet failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FTSearchOn(Handle, query, mode):
  retval = _ctdbsdk.ctdbFTSearchOn(Handle, query.encode(ctdb_const.CTREE_CHAR_ENCODING), mode)
  if retval != 0:
    raise DatabaseError( "FTSearchOn failed.", retval)
  return retval

def IsFTSearchOn(Handle, ):
  retval = _ctdbsdk.ctdbIsFTSearchOn(Handle, )
  if retval == 0:
    raise DatabaseError( "IsFTSearchOn failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FTSearchOff(Handle, ):
  retval = _ctdbsdk.ctdbFTSearchOff(Handle, )
  if retval != 0:
    raise DatabaseError( "FTSearchOff failed.", retval)
  return retval

def GetFTSErrorDetails(Handle, error, position, ):
  retval = _ctdbsdk.ctdbGetFTSErrorDetails(Handle, error, position, )
  if retval != 0:
    raise DatabaseError( "GetFTSErrorDetails failed.", retval)
  return retval

def AddToFieldMask(Handle, FieldNbr, ):
  retval = _ctdbsdk.ctdbAddToFieldMask(Handle, FieldNbr, )
  if retval != 0:
    raise DatabaseError( "AddToFieldMask failed.", retval)
  return retval

def RemoveFieldMask(Handle, ):
  retval = _ctdbsdk.ctdbRemoveFieldMask(Handle, )
  if retval != 0:
    raise DatabaseError( "RemoveFieldMask failed.", retval)
  return retval

def IsFieldMaskOn(Handle, ):
  retval = _ctdbsdk.ctdbIsFieldMaskOn(Handle, )
  if retval == 0:
    raise DatabaseError( "IsFieldMaskOn failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetIndexHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AllocIndex(Handle, ):
  retval = _ctdbsdk.ctdbAllocIndex(Handle, )
  if retval is None: 
    raise DatabaseError( "AllocIndex failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeIndex(Handle, ):
  retval = _ctdbsdk.ctdbFreeIndex(Handle, )

def AddIndex(Handle, name, key_type, AllowDuplicates, NullFlag, ):
  retval = _ctdbsdk.ctdbAddIndex(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING), key_type, AllowDuplicates, NullFlag, )
  if retval is None: 
    raise DatabaseError( "AddIndex failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def DelIndex(Handle, IndexNumber, ):
  retval = _ctdbsdk.ctdbDelIndex(Handle, IndexNumber, )
  if retval != 0:
    raise DatabaseError( "DelIndex failed.", retval)
  return retval

def GetIndex(Handle, IndexNumber):
  retval = _ctdbsdk.ctdbGetIndex(Handle, IndexNumber)
  if retval is None: 
    raise DatabaseError( "GetIndex failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexNbrByName(Handle, name):
  retval = _ctdbsdk.ctdbGetIndexNbrByName(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING))
  if retval == -1: 
    raise DatabaseError( "GetIndexNbrByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexByName(Handle, name, ):
  retval = _ctdbsdk.ctdbGetIndexByName(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval is None: 
    raise DatabaseError( "GetIndexByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexByUID(Handle, uid, ):
  retval = _ctdbsdk.ctdbGetIndexByUID(Handle, uid, )
  if retval is None: 
    raise DatabaseError( "GetIndexByUID failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexSegmentCount(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexSegmentCount(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetIndexSegmentCount failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexKeyLength(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexKeyLength(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetIndexKeyLength failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexKeyType(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexKeyType(Handle, )
  return retval

def GetIndexEmptyChar(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexEmptyChar(Handle, )
  return retval

def GetIndexDuplicateFlag(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexDuplicateFlag(Handle, )
  if retval == 0:
    raise DatabaseError( "GetIndexDuplicateFlag failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetIndexNullFlag(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexNullFlag(Handle, )
  return retval

def GetIndexTemporaryFlag(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexTemporaryFlag(Handle, )
  return retval

def SetIndexKeyType(Handle, KeyType, ):
  retval = _ctdbsdk.ctdbSetIndexKeyType(Handle, KeyType, )
  if retval != 0:
    raise DatabaseError( "SetIndexKeyType failed.", retval)
  return retval

def SetIndexEmptyChar(Handle, EmptyChar):
  if type(EmptyChar) == str:
    EmptyChar = ord(EmptyChar[0])
  retval = _ctdbsdk.ctdbSetIndexEmptyChar(Handle, EmptyChar)
  if retval != 0:
    raise DatabaseError( "SetIndexEmptyChar failed.", retval)
  return retval

def SetIndexDuplicateFlag(Handle, DupFlag, ):
  retval = _ctdbsdk.ctdbSetIndexDuplicateFlag(Handle, DupFlag, )
  if retval != 0:
    raise DatabaseError( "SetIndexDuplicateFlag failed.", retval)
  return retval

def SetIndexNullFlag(Handle, NullFlag):
  retval = _ctdbsdk.ctdbSetIndexNullFlag(Handle, NullFlag)
  if retval != 0:
    raise DatabaseError( "SetIndexNullFlag failed.", retval)
  return retval

def SetIndexTemporaryFlag(Handle, TempFlag, ):
  retval = _ctdbsdk.ctdbSetIndexTemporaryFlag(Handle, TempFlag, )
  if retval != 0:
    raise DatabaseError( "SetIndexTemporaryFlag failed.", retval)
  return retval

def SetIndexCndxExpr(Handle, conditionExpr, ):
  retval = _ctdbsdk.ctdbSetIndexCndxExpr(Handle, conditionExpr.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetIndexCndxExpr failed.", retval)
  return retval

def GetIndexNbr(Handle, pNumber, ):
  retval = _ctdbsdk.ctdbGetIndexNbr(Handle, pNumber, )
  if retval != 0:
    raise DatabaseError( "GetIndexNbr failed.", retval)
  return retval

def GetIndexUID(Handle, Name, puid, ):
  retval = _ctdbsdk.ctdbGetIndexUID(Handle, Name.encode(ctdb_const.CTREE_CHAR_ENCODING), puid, )
  if retval != 0:
    raise DatabaseError( "GetIndexUID failed.", retval)
  return retval

def SetIndexFilename(Handle, path, filename):
  retval = _ctdbsdk.ctdbSetIndexFilename(Handle, path if path is None else path.encode(ctdb_const.CTREE_CHAR_ENCODING), filename if filename is None else filename.encode(ctdb_const.CTREE_CHAR_ENCODING))
  if retval != 0:
    raise DatabaseError( "SetIndexFilename failed.", retval)
  return retval

def GetIndexFilename(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexFilename(Handle, )
  if retval == 0:
    raise DatabaseError( "GetIndexFilename failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING) if retval else retval

def GetIdxno(Handle, ):
  retval = _ctdbsdk.ctdbGetIdxno(Handle, )
  if retval == -1: 
    raise DatabaseError( "GetIdxno failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetIndexDistinctKeyCountFlag(Handle, Flag, ):
  retval = _ctdbsdk.ctdbSetIndexDistinctKeyCountFlag(Handle, Flag, )
  if retval != 0:
    raise DatabaseError( "SetIndexDistinctKeyCountFlag failed.", retval)
  return retval

def GetIndexDistinctKeyCountFlag(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexDistinctKeyCountFlag(Handle, )
  if retval == 0:
    raise DatabaseError( "GetIndexDistinctKeyCountFlag failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetIndexKSeg(Handle, pKSeg, ):
  retval = _ctdbsdk.ctdbSetIndexKSeg(Handle, pKSeg, )
  if retval != 0:
    raise DatabaseError( "SetIndexKSeg failed.", retval)
  return retval

def GetIndexKSeg(Handle, pKSeg, ):
  retval = _ctdbsdk.ctdbGetIndexKSeg(Handle, pKSeg, )
  if retval != 0:
    raise DatabaseError( "GetIndexKSeg failed.", retval)
  return retval

def GetIndexStatus(Handle, ):
  retval = _ctdbsdk.ctdbGetIndexStatus(Handle, )
  return retval

def GetIndexName(Handle):
  retval = _ctdbsdk.ctdbGetIndexName(Handle)
  return retval

def SetIndexName(Handle, IndexName, ):
  retval = _ctdbsdk.ctdbSetIndexName(Handle, IndexName.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetIndexName failed.", retval)
  return retval

def CheckIndexBackgroundLoad(Handle, status, ):
  retval = _ctdbsdk.ctdbCheckIndexBackgroundLoad(Handle, status, )
  if retval != 0:
    raise DatabaseError( "CheckIndexBackgroundLoad failed.", retval)
  return retval

def AllocFTIDict(Handle, ):
  retval = _ctdbsdk.ctdbAllocFTIDict(Handle, )
  if retval is None: 
    raise DatabaseError( "AllocFTIDict failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeFTIDict(Handle, ):
  retval = _ctdbsdk.ctdbFreeFTIDict(Handle, )

def GetFTIDictHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetFTIDictHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetFTIDictHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetFTIDictOption(Handle, option, pvalue, lvalue, ):
  retval = _ctdbsdk.ctdbSetFTIDictOption(Handle, option, pvalue.encode(ctdb_const.CTREE_CHAR_ENCODING), lvalue, )
  if retval != 0:
    raise DatabaseError( "SetFTIDictOption failed.", retval)
  return retval

def AllocFTI(Handle, ):
  retval = _ctdbsdk.ctdbAllocFTI(Handle, )
  if retval is None: 
    raise DatabaseError( "AllocFTI failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeFTI(Handle, ):
  retval = _ctdbsdk.ctdbFreeFTI(Handle, )

def GetFTIHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetFTIHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetFTIHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AddFTI(Handle, name ):
  retval = _ctdbsdk.ctdbAddFTI(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING) )
  if retval is None: 
    raise DatabaseError( "AddFTI failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AddFTIField(Handle, FieldHandle, mode, ):
  retval = _ctdbsdk.ctdbAddFTIField(Handle, FieldHandle, mode, )
  if retval != 0:
    raise DatabaseError( "AddFTIField failed.", retval)
  return retval

def AddFTIFieldByName(Handle, Number, FieldName, mode, ):
  retval = _ctdbsdk.ctdbAddFTIFieldByName(Handle, Number, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), mode, )
  if retval != 0:
    raise DatabaseError( "AddFTIFieldByName failed.", retval)
  return retval

def GetFTI(Handle, Number=0):
  retval = _ctdbsdk.ctdbGetFTI(Handle, Number)
  if retval is None: 
    raise DatabaseError( "GetFTI failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def DelFTI(Handle, Number, ):
  retval = _ctdbsdk.ctdbDelFTI(Handle, Number, )
  if retval != 0:
    raise DatabaseError( "DelFTI failed.", retval)
  return retval

def GetTableFTICount(Handle, ):
  retval = _ctdbsdk.ctdbGetTableFTICount(Handle, )
  if retval == 0:
    raise DatabaseError( "GetTableFTICount failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFTIStatus(Handle, ):
  retval = _ctdbsdk.ctdbGetFTIStatus(Handle, )
  if retval == 0:
    raise DatabaseError( "GetFTIStatus failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFTIFieldCount(Handle, ):
  retval = _ctdbsdk.ctdbGetFTIFieldCount(Handle, )
  if retval == 0:
    raise DatabaseError( "GetFTIFieldCount failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFTIField(Handle, FieldNumber, ):
  retval = _ctdbsdk.ctdbGetFTIField(Handle, FieldNumber, )
  if retval is None: 
    raise DatabaseError( "GetFTIField failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFTIFieldMode(Handle, FieldNumber, ):
  retval = _ctdbsdk.ctdbGetFTIFieldMode(Handle, FieldNumber, )
  if retval == 0:
    raise DatabaseError( "GetFTIFieldMode failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFTINbrByName(Handle, name, ):
  retval = _ctdbsdk.ctdbGetFTINbrByName(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval == 0:
    raise DatabaseError( "GetFTINbrByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFTIByName(Handle, name, ):
  retval = _ctdbsdk.ctdbGetFTIByName(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval is None: 
    raise DatabaseError( "GetFTIByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetDefaultFTI(Handle, Number, ):
  retval = _ctdbsdk.ctdbSetDefaultFTI(Handle, Number, )
  if retval != 0:
    raise DatabaseError( "SetDefaultFTI failed.", retval)
  return retval

def SetFTIOption(Handle, option, pvalue, lvalue, ):
  retval = _ctdbsdk.ctdbSetFTIOption(Handle, option, pvalue.encode(ctdb_const.CTREE_CHAR_ENCODING), lvalue, )
  if retval != 0:
    raise DatabaseError( "SetFTIOption failed.", retval)
  return retval

def GetFTIByUID(Handle, uid, ):
  retval = _ctdbsdk.ctdbGetFTIByUID(Handle, uid, )
  if retval is None: 
    raise DatabaseError( "GetFTIByUID failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFTINbr(Handle, pNumber, ):
  retval = _ctdbsdk.ctdbGetFTINbr(Handle, pNumber, )
  if retval != 0:
    raise DatabaseError( "GetFTINbr failed.", retval)
  return retval

def GetFTIName(Handle, ):
  retval = _ctdbsdk.ctdbGetFTIName(Handle, )
  if retval == 0:
    raise DatabaseError( "GetFTIName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval if retval is None else retval.decode(ctdb_const.CTREE_CHAR_ENCODING)

def SetFTICndxExpr(Handle, conditionExpr, ):
  retval = _ctdbsdk.ctdbSetFTICndxExpr(Handle, conditionExpr.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetFTICndxExpr failed.", retval)
  return retval

def CheckFTIBackgroundLoad(pFTI, status, ):
  retval = _ctdbsdk.ctdbCheckFTIBackgroundLoad(pFTI, status, )
  if retval != 0:
    raise DatabaseError( "CheckFTIBackgroundLoad failed.", retval)
  return retval

def StartFTIBackgroundLoad(pFTI, ):
  retval = _ctdbsdk.ctdbStartFTIBackgroundLoad(pFTI, )
  if retval != 0:
    raise DatabaseError( "StartFTIBackgroundLoad failed.", retval)
  return retval

def GetSegmentHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetSegmentHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetSegmentHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AllocSegment(Handle, ):
  retval = _ctdbsdk.ctdbAllocSegment(Handle, )
  if retval is None: 
    raise DatabaseError( "AllocSegment failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeSegment(Handle, ):
  retval = _ctdbsdk.ctdbFreeSegment(Handle, )

def IsExtSegment(SegMode, ):
  retval = _ctdbsdk.ctdbIsExtSegment(SegMode, )
  if retval == 0:
    raise DatabaseError( "IsExtSegment failed.") 
  return retval

def GetSegment(Handle, SegNumber, ):
  retval = _ctdbsdk.ctdbGetSegment(Handle, SegNumber, )
  if retval is None: 
    raise DatabaseError( "GetSegment failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetSegmentField(Handle, ):
  retval = _ctdbsdk.ctdbGetSegmentField(Handle, )
  if retval is None: 
    raise DatabaseError( "GetSegmentField failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetSegmentPartialField(Handle, ):
  retval = _ctdbsdk.ctdbGetSegmentPartialField(Handle, )
  if retval is None: 
    raise DatabaseError( "GetSegmentPartialField failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetSegmentFieldName(Handle, ):
  retval = _ctdbsdk.ctdbGetSegmentFieldName(Handle, )
  if retval == 0:
    raise DatabaseError( "GetSegmentFieldName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetSegmentMode(Handle, ):
  retval = _ctdbsdk.ctdbGetSegmentMode(Handle, )
  if retval == 0:
    raise DatabaseError( "GetSegmentMode failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetSegmentLength(Handle, ):
  retval = _ctdbsdk.ctdbGetSegmentLength(Handle, )
  if retval == 0:
    raise DatabaseError( "GetSegmentLength failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetSegmentMode(Handle, SegMode, ):
  retval = _ctdbsdk.ctdbSetSegmentMode(Handle, SegMode, )
  if retval != 0:
    raise DatabaseError( "SetSegmentMode failed.", retval)
  return retval

def GetSegmentNbr(Handle, pNumber):
  retval = _ctdbsdk.ctdbGetSegmentNbr(Handle, pNumber)
  if retval != 0:
    raise DatabaseError( "GetSegmentNbr failed.", retval)
  return retval

def AddSegment(IndexHandle, FieldHandle, SegMode):
  retval = _ctdbsdk.ctdbAddSegment(IndexHandle, FieldHandle, SegMode)
  if retval is None: 
    raise DatabaseError( "AddSegment failed.", _ctdbsdk.ctdbGetError(IndexHandle))
  return retval


def AddSegmentByNbr(Handle, IndexNbr, FieldNbr, SegMode, ):
  retval = _ctdbsdk.ctdbAddSegmentByNbr(Handle, IndexNbr, FieldNbr, SegMode, )
  if retval is None: 
    raise DatabaseError( "AddSegmentByNbr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AddSegmentByName(Handle, IndexNbr, FieldName, SegMode, ):
  retval = _ctdbsdk.ctdbAddSegmentByName(Handle, IndexNbr, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), SegMode, )
  if retval is None: 
    raise DatabaseError( "AddSegmentByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def InsSegment(Handle, SegNumber, FieldHandle, SegMode, ):
  retval = _ctdbsdk.ctdbInsSegment(Handle, SegNumber, FieldHandle, SegMode, )
  if retval is None: 
    raise DatabaseError( "InsSegment failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def InsSegmentByNbr(Handle, IndexNbr, SegNumber, FieldNbr, SegMode, ):
  retval = _ctdbsdk.ctdbInsSegmentByNbr(Handle, IndexNbr, SegNumber, FieldNbr, SegMode, )
  if retval is None: 
    raise DatabaseError( "InsSegmentByNbr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def InsSegmentByName(Handle, IndexNbr, SegNumber, FieldName, SegMode, ):
  retval = _ctdbsdk.ctdbInsSegmentByName(Handle, IndexNbr, SegNumber, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), SegMode, )
  if retval is None: 
    raise DatabaseError( "InsSegmentByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def InsSegmentEx(Handle, SegNumber, offset, length, SegMode, ):
  retval = _ctdbsdk.ctdbInsSegmentEx(Handle, SegNumber, offset, length, SegMode, )
  if retval is None: 
    raise DatabaseError( "InsSegmentEx failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def DelSegment(Handle, SegNumber, ):
  retval = _ctdbsdk.ctdbDelSegment(Handle, SegNumber, )
  if retval != 0:
    raise DatabaseError( "DelSegment failed.", retval)
  return retval

def DelSegmentEx(Handle, ):
  retval = _ctdbsdk.ctdbDelSegmentEx(Handle, )
  if retval != 0:
    raise DatabaseError( "DelSegmentEx failed.", retval)
  return retval

def AddRowIdSegment(Handle, ):
  retval = _ctdbsdk.ctdbAddRowIdSegment(Handle, )
  if retval is None: 
    raise DatabaseError( "AddRowIdSegment failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AddJSONSegment(Handle, FieldHandle, key, type, size, ):
  retval = _ctdbsdk.ctdbAddJSONSegment(Handle, FieldHandle, key.encode(ctdb_const.CTREE_CHAR_ENCODING), type, size, )
  if retval is None: 
    raise DatabaseError( "AddJSONSegment failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetKSegDefaults(pKSeg, ):
  retval = _ctdbsdk.ctdbSetKSegDefaults(pKSeg, )
  if retval != 0:
    raise DatabaseError( "SetKSegDefaults failed.", retval)
  return retval

def SetSegmentKSeg(Handle, pKSeg, ):
  retval = _ctdbsdk.ctdbSetSegmentKSeg(Handle, pKSeg, )
  if retval != 0:
    raise DatabaseError( "SetSegmentKSeg failed.", retval)
  return retval

def GetSegmentKSeg(Handle, pKSeg, ):
  retval = _ctdbsdk.ctdbGetSegmentKSeg(Handle, pKSeg, )
  if retval != 0:
    raise DatabaseError( "GetSegmentKSeg failed.", retval)
  return retval

def GetJSONSegmentProperties(Handle, pKey, pType, size, ):
  retval = _ctdbsdk.ctdbGetJSONSegmentProperties(Handle, pKey, pType, size, )
  if retval != 0:
    raise DatabaseError( "GetJSONSegmentProperties failed.", retval)
  return retval

def GetSegmentStatus(Handle):
  retval = _ctdbsdk.ctdbGetSegmentStatus(Handle)
  return retval

def MoveSegment(Handle, newIndex, ):
  retval = _ctdbsdk.ctdbMoveSegment(Handle, newIndex, )
  if retval != 0:
    raise DatabaseError( "MoveSegment failed.", retval)
  return retval

def SetSegmentField(Handle, field, ):
  retval = _ctdbsdk.ctdbSetSegmentField(Handle, field, )
  if retval != 0:
    raise DatabaseError( "SetSegmentField failed.", retval)
  return retval

def SetJSONSegmentField(Handle, field, key, type, size, ):
  retval = _ctdbsdk.ctdbSetJSONSegmentField(Handle, field, key.encode(ctdb_const.CTREE_CHAR_ENCODING), type, size, )
  if retval != 0:
    raise DatabaseError( "SetJSONSegmentField failed.", retval)
  return retval

def GetFieldHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetFieldHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AllocField(pTable, FieldName, FieldType, FieldLength, ):
  retval = _ctdbsdk.ctdbAllocField(pTable, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), FieldType, FieldLength, )
  if retval is None: 
    raise DatabaseError( "AllocField failed.") 
  return retval

def FreeField(Handle, ):
  retval = _ctdbsdk.ctdbFreeField(Handle, )

def AddField(Handle, FieldName, FieldType, FieldLength, ):
  retval = _ctdbsdk.ctdbAddField(Handle, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), FieldType, FieldLength, )
  if retval is None: 
    raise DatabaseError( "AddField failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval 

def InsField(Handle, BeforeFieldNumber, FieldName, FieldType, FieldLength):
  retval = _ctdbsdk.ctdbInsField(Handle, BeforeFieldNumber, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), FieldType, FieldLength)
  if retval is None: 
    raise DatabaseError( "InsField failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def InsFieldByName(Handle, BeforeFieldName, FieldName, FieldType, FieldLength):
  retval = _ctdbsdk.ctdbInsFieldByName(Handle, BeforeFieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), FieldType, FieldLength)
  if retval is None: 
    raise DatabaseError( "InsFieldByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def DelField(Handle, Index, ):
  retval = _ctdbsdk.ctdbDelField(Handle, Index, )
  if retval != 0:
    raise DatabaseError( "DelField failed.", retval)
  return retval

def DelFieldByName(Handle, FieldName, ):
  retval = _ctdbsdk.ctdbDelFieldByName(Handle, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "DelFieldByName failed.", retval)
  return retval

def MoveField(FieldHandle, newIndex, ):
  retval = _ctdbsdk.ctdbMoveField(FieldHandle, newIndex, )
  if retval != 0:
    raise DatabaseError( "MoveField failed.", retval)
  return retval

def GetField(TableHandle, FieldNumber ):
  retval = _ctdbsdk.ctdbGetField(TableHandle, FieldNumber)
  if retval is None: 
    raise DatabaseError( "GetField failed.", _ctdbsdk.ctdbGetError(TableHandle))
  return retval 

def GetFieldByName(Handle, FieldName, RaiseExceptionIfMissing=True):
  retval = _ctdbsdk.ctdbGetFieldByName(Handle, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING))
  if retval is None and RaiseExceptionIfMissing: 
    raise DatabaseError( "GetFieldByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval 

def GetFieldNumber(TableHandle, FieldName):
  if type(FieldName) == str:
    FieldName = FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING)
  retval = _ctdbsdk.ctdbGetFieldNumber(TableHandle, FieldName)
  if retval == -1: 
    raise DatabaseError( "GetFieldNumber failed.", _ctdbsdk.ctdbGetError(TableHandle))
  return retval

def GetFieldProperties(Handle, FieldName, pType, pLength, ):
  retval = _ctdbsdk.ctdbGetFieldProperties(Handle, FieldName, pType, pLength, )
  if retval != 0:
    raise DatabaseError( "GetFieldProperties failed.", retval)
  return retval

def SetFieldProperties(Handle, FieldName, Type, Length, ):
  retval = _ctdbsdk.ctdbSetFieldProperties(Handle, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), Type, Length, )
  if retval != 0:
    raise DatabaseError( "SetFieldProperties failed.", retval)
  return retval

def GetFieldNbr(Handle):
  retval = _ctdbsdk.ctdbGetFieldNbr(Handle)
  if retval == -1: 
    raise DatabaseError( "GetFieldNbr failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFieldName(Handle):
  retval = _ctdbsdk.ctdbGetFieldName(Handle)
  if retval == 0:
    raise DatabaseError( "GetFieldName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval.decode(ctdb_const.CTREE_CHAR_ENCODING)

def GetFieldLength(FieldHandle):
  retval = _ctdbsdk.ctdbGetFieldLength(FieldHandle)
  if retval == -1: 
    raise DatabaseError( "GetFieldLength failed.", _ctdbsdk.ctdbGetError(FieldHandle))
  return retval

def GetFieldType(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldType(Handle, )
  if retval == 0:
    raise DatabaseError( "GetFieldType failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFieldNullFlag(Handle):
  retval = _ctdbsdk.ctdbGetFieldNullFlag(Handle)
  return retval

def GetFieldPrecision(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldPrecision(Handle, )
  return retval

def GetFieldScale(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldScale(Handle, )
  return retval

def SetFieldNullFlag(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetFieldNullFlag(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetFieldNullFlag failed.", retval)
  return retval

def SetFieldPrecision(Handle, fprec, ):
  retval = _ctdbsdk.ctdbSetFieldPrecision(Handle, fprec, )
  if retval != 0:
    raise DatabaseError( "SetFieldPrecision failed.", retval)
  return retval

def SetFieldScale(Handle, fscale, ):
  retval = _ctdbsdk.ctdbSetFieldScale(Handle, fscale, )
  if retval != 0:
    raise DatabaseError( "SetFieldScale failed.", retval)
  return retval

def SetFieldName(Handle, name, ):
  retval = _ctdbsdk.ctdbSetFieldName(Handle, name.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "SetFieldName failed.", retval)
  return retval

def SetFieldLength(Handle, len, ):
  retval = _ctdbsdk.ctdbSetFieldLength(Handle, len, )
  if retval != 0:
    raise DatabaseError( "SetFieldLength failed.", retval)
  return retval

def SetFieldType(Handle, type, ):
  retval = _ctdbsdk.ctdbSetFieldType(Handle, type, )
  if retval != 0:
    raise DatabaseError( "SetFieldType failed.", retval)
  return retval

def IsFieldNumeric(Handle, ):
  retval = _ctdbsdk.ctdbIsFieldNumeric(Handle, )
  return retval

def SetFieldDefaultValue(Handle, value, length, ):
  retval = _ctdbsdk.ctdbSetFieldDefaultValue(Handle, value.encode(ctdb_const.CTREE_CHAR_ENCODING), length, )
  if retval != 0:
    raise DatabaseError( "SetFieldDefaultValue failed.", retval)
  return retval

def GetFieldDefaultValue(Handle):
  pLength = ctypes.c_int32()
  retval = _ctdbsdk.ctdbGetFieldDefaultValue(Handle, ctypes.byref(pLength))
  if retval == 0:
    raise DatabaseError( "GetFieldDefaultValue failed.", _ctdbsdk.ctdbGetError(Handle))
  return (retval.decode(ctdb_const.CTREE_CHAR_ENCODING) if retval else None, pLength.value)

def ClearFieldDefaultValue(Handle, ):
  retval = _ctdbsdk.ctdbClearFieldDefaultValue(Handle, )
  if retval != 0:
    raise DatabaseError( "ClearFieldDefaultValue failed.", retval)
  return retval

def ClearAllFieldDefaultValue(Handle):
  retval = _ctdbsdk.ctdbClearAllFieldDefaultValue(Handle)
  if retval != 0:
    raise DatabaseError( "ClearAllFieldDefaultValue failed.", retval)
  return retval

def SetFieldDefaultDateTimeType(Handle, dateType, timeType, ):
  retval = _ctdbsdk.ctdbSetFieldDefaultDateTimeType(Handle, dateType, timeType, )
  if retval != 0:
    raise DatabaseError( "SetFieldDefaultDateTimeType failed.", retval)
  return retval

def IsFieldDefaultValueSet(Handle, ):
  retval = _ctdbsdk.ctdbIsFieldDefaultValueSet(Handle, )
  return retval

def GetFieldDefaultDateType(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldDefaultDateType(Handle, )
  if retval == 0:
    raise DatabaseError( "GetFieldDefaultDateType failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFieldDefaultTimeType(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldDefaultTimeType(Handle, )
  if retval == 0:
    raise DatabaseError( "GetFieldDefaultTimeType failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetFieldDefaultValueAsBinary(Handle, buffer, pLength, ):
  retval = _ctdbsdk.ctdbGetFieldDefaultValueAsBinary(Handle, buffer.encode(ctdb_const.CTREE_CHAR_ENCODING), pLength, )
  if retval != 0:
    raise DatabaseError( "GetFieldDefaultValueAsBinary failed.", retval)
  return retval

def GetFieldStatus(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldStatus(Handle, )
  return retval

def GetFieldBinaryFlag(Handle, ):
  retval = _ctdbsdk.ctdbGetFieldBinaryFlag(Handle, )
  if retval == 0:
    raise DatabaseError( "GetFieldBinaryFlag failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetFieldBinaryFlag(Handle, flag, ):
  retval = _ctdbsdk.ctdbSetFieldBinaryFlag(Handle, flag, )
  if retval != 0:
    raise DatabaseError( "SetFieldBinaryFlag failed.", retval)
  return retval

def AddVirtualField(Handle, FieldName, FieldType, FieldLength, VirtualInfo, ):
  retval = _ctdbsdk.ctdbAddVirtualField(Handle, FieldName.encode(ctdb_const.CTREE_CHAR_ENCODING), FieldType, FieldLength, VirtualInfo, )
  if retval is None: 
    raise DatabaseError( "AddVirtualField failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetVirtualFieldClear(Handle, vclear, ):
  retval = _ctdbsdk.ctdbSetVirtualFieldClear(Handle, vclear, )
  if retval != 0:
    raise DatabaseError( "SetVirtualFieldClear failed.", retval)
  return retval

def DateCheck(year, month, day, ):
  retval = _ctdbsdk.ctdbDateCheck(year, month, day, )
  if retval != 0:
    raise DatabaseError( "DateCheck failed.", retval)
  return retval

def DatePack(pDate, year, month, day, ):
  retval = _ctdbsdk.ctdbDatePack(pDate, year, month, day, )
  if retval != 0:
    raise DatabaseError( "DatePack failed.", retval)
  return retval

def DateUnpack(date, pyear, pmonth, pday, ):
  retval = _ctdbsdk.ctdbDateUnpack(date, pyear, pmonth, pday, )
  if retval != 0:
    raise DatabaseError( "DateUnpack failed.", retval)
  return retval

def DateToString(date, DateType):
  buf = ctypes.create_string_buffer(251)
  retval = _ctdbsdk.ctdbDateToString(date, DateType, buf, 250 )
  if retval != 0:
    raise DatabaseError( "DateToString failed.", retval)
  return buf.value.decode(ctdb_const.CTREE_CHAR_ENCODING)

def StringToDate(pStr, DateType, pDate, ):
  retval = _ctdbsdk.ctdbStringToDate(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), DateType, pDate, )
  if retval != 0:
    raise DatabaseError( "StringToDate failed.", retval)
  return retval

def GetDay(date, ):
  retval = _ctdbsdk.ctdbGetDay(date, )
  if retval == 0:
    raise DatabaseError( "GetDay failed.") 
  return retval

def GetMonth(date, ):
  retval = _ctdbsdk.ctdbGetMonth(date, )
  if retval == 0:
    raise DatabaseError( "GetMonth failed.")
  return retval

def GetYear(date, ):
  retval = _ctdbsdk.ctdbGetYear(date, )
  if retval == 0:
    raise DatabaseError( "GetYear failed.")
  return retval

def IsLeapYear(date, ):
  retval = _ctdbsdk.ctdbIsLeapYear(date, )
  if retval == 0:
    raise DatabaseError( "IsLeapYear failed.")
  return retval

def DayOfWeek(date, ):
  retval = _ctdbsdk.ctdbDayOfWeek(date, )
  if retval == -1: 
    raise DatabaseError( "DayOfWeek failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetDefDateType(Handle, ):
  retval = _ctdbsdk.ctdbGetDefDateType(Handle, )
  if retval == 0:
    raise DatabaseError( "GetDefDateType failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetDefDateType(Handle, DateType, ):
  retval = _ctdbsdk.ctdbSetDefDateType(Handle, DateType, )
  if retval != 0:
    raise DatabaseError( "SetDefDateType failed.", retval)
  return retval

def CurrentDate():
  value = ctypes.c_uint32()
  retval = _ctdbsdk.ctdbCurrentDate(ctypes.byref(value))
  if retval != 0:
    raise DatabaseError( "CurrentDate failed.", retval)
  return value.value

def StringFormatToDate(pStr, Mask, pDate, julianbase, ):
  retval = _ctdbsdk.ctdbStringFormatToDate(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pDate, julianbase, )
  if retval != 0:
    raise DatabaseError( "StringFormatToDate failed.", retval)
  return retval

def DateToStringFormat(Date, Mask, pStr, julianbase, ):
  retval = _ctdbsdk.ctdbDateToStringFormat(Date, Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), julianbase, )
  if retval != 0:
    raise DatabaseError( "DateToStringFormat failed.", retval)
  return retval

def StringFormatToTime(pStr, Mask, pTime, ):
  retval = _ctdbsdk.ctdbStringFormatToTime(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pTime, )
  if retval != 0:
    raise DatabaseError( "StringFormatToTime failed.", retval)
  return retval

def StringFormatToTimeMsec(pStr, Mask, pTime, ):
  retval = _ctdbsdk.ctdbStringFormatToTimeMsec(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pTime, )
  if retval != 0:
    raise DatabaseError( "StringFormatToTimeMsec failed.", retval)
  return retval

def TimeToStringFormat(Time, Mask, pStr, ):
  retval = _ctdbsdk.ctdbTimeToStringFormat(Time, Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "TimeToStringFormat failed.", retval)
  return retval

def TimeMsecToStringFormat(Time, Mask, pStr, ):
  retval = _ctdbsdk.ctdbTimeMsecToStringFormat(Time, Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "TimeMsecToStringFormat failed.", retval)
  return retval

def StringFormatToDateTime(pStr, Mask, pDateTime, julianbase, ):
  retval = _ctdbsdk.ctdbStringFormatToDateTime(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pDateTime, julianbase, )
  if retval != 0:
    raise DatabaseError( "StringFormatToDateTime failed.", retval)
  return retval

def DateTimeToStringFormat(DateTime, Mask, pStr, julianbase, ):
  retval = _ctdbsdk.ctdbDateTimeToStringFormat(DateTime, Mask.encode(ctdb_const.CTREE_CHAR_ENCODING), pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), julianbase, )
  if retval != 0:
    raise DatabaseError( "DateTimeToStringFormat failed.", retval)
  return retval

def TimeCheck(hour, minute, second, ):
  retval = _ctdbsdk.ctdbTimeCheck(hour, minute, second, )
  if retval != 0:
    raise DatabaseError( "TimeCheck failed.", retval)
  return retval

def TimeCheckMsec(hour, minute, second, millisec, ):
  retval = _ctdbsdk.ctdbTimeCheckMsec(hour, minute, second, millisec, )
  if retval != 0:
    raise DatabaseError( "TimeCheckMsec failed.", retval)
  return retval

def TimePack(pTime, hour, minute, second, ):
  retval = _ctdbsdk.ctdbTimePack(pTime, hour, minute, second, )
  if retval != 0:
    raise DatabaseError( "TimePack failed.", retval)
  return retval

def TimeUnpack(Time, hour, minute, second, ):
  retval = _ctdbsdk.ctdbTimeUnpack(Time, hour, minute, second, )
  if retval != 0:
    raise DatabaseError( "TimeUnpack failed.", retval)
  return retval

def TimePackMsec(pTime, hour, minute, second, millisec, ):
  retval = _ctdbsdk.ctdbTimePackMsec(pTime, hour, minute, second, millisec, )
  if retval != 0:
    raise DatabaseError( "TimePackMsec failed.", retval)
  return retval

def TimeUnpackMsec(Time, hour, minute, second, millisec, ):
  retval = _ctdbsdk.ctdbTimeUnpackMsec(Time, hour, minute, second, millisec, )
  if retval != 0:
    raise DatabaseError( "TimeUnpackMsec failed.", retval)
  return retval

def TimeToString(time, TimeType):
  buf = ctypes.create_string_buffer(251)
  retval = _ctdbsdk.ctdbTimeToString(time, TimeType, buf, 250 )
  if retval != 0:
    raise DatabaseError( "TimeToString failed.", retval)
  return buf.value.decode(ctdb_const.CTREE_CHAR_ENCODING)

def StringToTime(pStr, TimeType, pTime, ):
  retval = _ctdbsdk.ctdbStringToTime(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), TimeType, pTime, )
  if retval != 0:
    raise DatabaseError( "StringToTime failed.", retval)
  return retval

def TimeMsecToString(Time, TimeType, pStr, size, ):
  retval = _ctdbsdk.ctdbTimeMsecToString(Time, TimeType, pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), size, )
  if retval != 0:
    raise DatabaseError( "TimeMsecToString failed.", retval)
  return retval

def StringToTimeMsec(pStr, TimeType, pTime, ):
  retval = _ctdbsdk.ctdbStringToTimeMsec(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), TimeType, pTime, )
  if retval != 0:
    raise DatabaseError( "StringToTimeMsec failed.", retval)
  return retval

def GetHour(Time, ):
  retval = _ctdbsdk.ctdbGetHour(Time, )
  if retval == -1: 
    raise DatabaseError( "GetHour failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetMinute(Time, ):
  retval = _ctdbsdk.ctdbGetMinute(Time, )
  if retval == -1: 
    raise DatabaseError( "GetMinute failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetSecond(Time, ):
  retval = _ctdbsdk.ctdbGetSecond(Time, )
  if retval == -1: 
    raise DatabaseError( "GetSecond failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetDefTimeType(Handle, ):
  retval = _ctdbsdk.ctdbGetDefTimeType(Handle, )
  if retval == 0:
    raise DatabaseError( "GetDefTimeType failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def SetDefTimeType(Handle, TimeType, ):
  retval = _ctdbsdk.ctdbSetDefTimeType(Handle, TimeType, )
  if retval != 0:
    raise DatabaseError( "SetDefTimeType failed.", retval)
  return retval

def CurrentTime():
  value = ctypes.c_uint32()
  retval = _ctdbsdk.ctdbCurrentTime(ctypes.byref(value))
  if retval != 0:
    raise DatabaseError( "CurrentTime failed.", retval)
  return value.value

def DateTimePack(pDateTime, year, month, day, hour, minute, second, ):
  retval = _ctdbsdk.ctdbDateTimePack(pDateTime, year, month, day, hour, minute, second, )
  if retval != 0:
    raise DatabaseError( "DateTimePack failed.", retval)
  return retval

def DateTimeUnpack(DateTime, pYear, pMonth, pDay, pHour, pMinute, pSecond, ):
  retval = _ctdbsdk.ctdbDateTimeUnpack(DateTime, pYear, pMonth, pDay, pHour, pMinute, pSecond, )
  if retval != 0:
    raise DatabaseError( "DateTimeUnpack failed.", retval)
  return retval

def DateTimePackMsec(pDateTime, year, month, day, hour, minute, second, millisec, ):
  retval = _ctdbsdk.ctdbDateTimePackMsec(pDateTime, year, month, day, hour, minute, second, millisec, )
  if retval != 0:
    raise DatabaseError( "DateTimePackMsec failed.", retval)
  return retval

def DateTimeUnpackMsec(DateTime, pYear, pMonth, pDay, pHour, pMinute, pSecond, pMillisec, ):
  retval = _ctdbsdk.ctdbDateTimeUnpackMsec(DateTime, pYear, pMonth, pDay, pHour, pMinute, pSecond, pMillisec, )
  if retval != 0:
    raise DatabaseError( "DateTimeUnpackMsec failed.", retval)
  return retval

def DateTimeGetDate(DateTime, pDate, ):
  retval = _ctdbsdk.ctdbDateTimeGetDate(DateTime, pDate, )
  if retval != 0:
    raise DatabaseError( "DateTimeGetDate failed.", retval)
  return retval

def DateTimeGetTime(DateTime, pTime, ):
  retval = _ctdbsdk.ctdbDateTimeGetTime(DateTime, pTime, )
  if retval != 0:
    raise DatabaseError( "DateTimeGetTime failed.", retval)
  return retval

def DateTimeGetTimeMsec(DateTime, pTime, ):
  retval = _ctdbsdk.ctdbDateTimeGetTimeMsec(DateTime, pTime, )
  if retval != 0:
    raise DatabaseError( "DateTimeGetTimeMsec failed.", retval)
  return retval

def DateTimeSetDate(pDateTime, Date, ):
  retval = _ctdbsdk.ctdbDateTimeSetDate(pDateTime, Date, )
  if retval != 0:
    raise DatabaseError( "DateTimeSetDate failed.", retval)
  return retval

def DateTimeSetTime(pDateTime, Time, ):
  retval = _ctdbsdk.ctdbDateTimeSetTime(pDateTime, Time, )
  if retval != 0:
    raise DatabaseError( "DateTimeSetTime failed.", retval)
  return retval

def DateTimeSetTimeMsec(pDateTime, Time, ):
  retval = _ctdbsdk.ctdbDateTimeSetTimeMsec(pDateTime, Time, )
  if retval != 0:
    raise DatabaseError( "DateTimeSetTimeMsec failed.", retval)
  return retval

def DateTimeToString(DateTime, DateType, TimeType):
  buf = ctypes.create_string_buffer(251)
  retval = _ctdbsdk.ctdbDateTimeToString(DateTime, DateType,  TimeType, buf, 250 )
  if retval != 0:
    raise DatabaseError( "DateTimeToString failed.", retval)
  return buf.value.decode(ctdb_const.CTREE_CHAR_ENCODING)

def StringToDateTime(pStr, pDateTime, DateType, TimeType, ):
  retval = _ctdbsdk.ctdbStringToDateTime(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), pDateTime, DateType, TimeType, )
  if retval != 0:
    raise DatabaseError( "StringToDateTime failed.", retval)
  return retval

def CurrentDateTime():
  value = ctypes.c_double()
  retval = _ctdbsdk.ctdbCurrentDateTime(ctypes.byref(value))
  if retval != 0:
    raise DatabaseError( "CurrentDateTime failed.", retval)
  return value.value

def CurrentDateTimeUTC(pDateTime, ):
  retval = _ctdbsdk.ctdbCurrentDateTimeUTC(pDateTime, )
  if retval != 0:
    raise DatabaseError( "CurrentDateTimeUTC failed.", retval)
  return retval

def CurrentTimestamp(timestamp, ):
  retval = _ctdbsdk.ctdbCurrentTimestamp(timestamp, )
  if retval != 0:
    raise DatabaseError( "CurrentTimestamp failed.", retval)
  return retval

def MoneyToLong(money, pValue, ):
  retval = _ctdbsdk.ctdbMoneyToLong(money, pValue, )
  if retval != 0:
    raise DatabaseError( "MoneyToLong failed.", retval)
  return retval

def LongToMoney(value, pMoney, ):
  retval = _ctdbsdk.ctdbLongToMoney(value, pMoney, )
  if retval != 0:
    raise DatabaseError( "LongToMoney failed.", retval)
  return retval

def MoneyToFloat(money, pValue, ):
  retval = _ctdbsdk.ctdbMoneyToFloat(money, pValue, )
  if retval != 0:
    raise DatabaseError( "MoneyToFloat failed.", retval)
  return retval

def FloatToMoney(value, pMoney, ):
  retval = _ctdbsdk.ctdbFloatToMoney(value, pMoney, )
  if retval != 0:
    raise DatabaseError( "FloatToMoney failed.", retval)
  return retval

def MoneyToString(money, BufferSize, ):
  buf = ctypes.create_string_buffer(BufferSize+1)
  retval = _ctdbsdk.ctdbMoneyToString(money, buf, BufferSize, )
  if retval != 0:
    raise DatabaseError( "MoneyToString failed.", retval)
  return buf.value.decode(ctdb_const.CTREE_CHAR_ENCODING)

def StringToMoney(pStr, pMoney, ):
  retval = _ctdbsdk.ctdbStringToMoney(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), pMoney, )
  if retval != 0:
    raise DatabaseError( "StringToMoney failed.", retval)
  return retval

def MoneyAdd(left, right, pResult, ):
  retval = _ctdbsdk.ctdbMoneyAdd(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "MoneyAdd failed.", retval)
  return retval

def MoneySub(left, right, pResult, ):
  retval = _ctdbsdk.ctdbMoneySub(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "MoneySub failed.", retval)
  return retval

def MoneyMul(left, right, pResult, ):
  retval = _ctdbsdk.ctdbMoneyMul(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "MoneyMul failed.", retval)
  return retval

def MoneyDiv(left, right, pResult, ):
  retval = _ctdbsdk.ctdbMoneyDiv(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "MoneyDiv failed.", retval)
  return retval

def MoneyCmp(left, right, ):
  retval = _ctdbsdk.ctdbMoneyCmp(left, right, )
  if retval == 0:
    raise DatabaseError( "MoneyCmp failed.") 
  return retval

def MoneyAbs(left, ):
  retval = _ctdbsdk.ctdbMoneyAbs(left, )
  if retval == 0:
    raise DatabaseError( "MoneyAbs failed.")
  return retval

def BlobAlloc(size, ):
  retval = _ctdbsdk.ctdbBlobAlloc(size, )
  if retval is None: 
    raise DatabaseError( "BlobAlloc failed.") 
  return retval

def BlobFree(pBlob, ):
  retval = _ctdbsdk.ctdbBlobFree(pBlob, )

def BlobGetData(pBlob, ):
  retval = _ctdbsdk.ctdbBlobGetData(pBlob, )
  if retval is None: 
    raise DatabaseError( "BlobGetData failed.")
  return retval

def BlobGetSize(pBlob, ):
  retval = _ctdbsdk.ctdbBlobGetSize(pBlob, )
  if retval == 0:
    raise DatabaseError( "BlobGetSize failed.")
  return retval

def BlobSet(pBlob, buffer, size, ):
  retval = _ctdbsdk.ctdbBlobSet(pBlob, buffer, size, )
  if retval != 0:
    raise DatabaseError( "BlobSet failed.", retval)
  return retval

def BlobCmp(left, right, ):
  retval = _ctdbsdk.ctdbBlobCmp(left, right, )
  if retval == 0:
    raise DatabaseError( "BlobCmp failed.")
  return retval

def BlobClear(pBlob, ):
  retval = _ctdbsdk.ctdbBlobClear(pBlob, )
  if retval != 0:
    raise DatabaseError( "BlobClear failed.", retval)
  return retval

def BigIntToLong(value, pLong, ):
  retval = _ctdbsdk.ctdbBigIntToLong(value, pLong, )
  if retval != 0:
    raise DatabaseError( "BigIntToLong failed.", retval)
  return retval

def LongToBigInt(value, pBigInt, ):
  retval = _ctdbsdk.ctdbLongToBigInt(value, pBigInt, )
  if retval != 0:
    raise DatabaseError( "LongToBigInt failed.", retval)
  return retval

def BigIntToFloat(value, pFloat, ):
  retval = _ctdbsdk.ctdbBigIntToFloat(value, pFloat, )
  if retval != 0:
    raise DatabaseError( "BigIntToFloat failed.", retval)
  return retval

def FloatToBigInt(value, pBigInt, ):
  retval = _ctdbsdk.ctdbFloatToBigInt(value, pBigInt, )
  if retval != 0:
    raise DatabaseError( "FloatToBigInt failed.", retval)
  return retval

def BigIntToString(value, pStr, size, ):
  retval = _ctdbsdk.ctdbBigIntToString(value, pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), size, )
  if retval != 0:
    raise DatabaseError( "BigIntToString failed.", retval)
  return retval

def UnsignedBigIntToString(value, pStr, size, ):
  retval = _ctdbsdk.ctdbUnsignedBigIntToString(value, pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), size, )
  if retval != 0:
    raise DatabaseError( "UnsignedBigIntToString failed.", retval)
  return retval

def StringToBigInt(pStr, pValue, ):
  retval = _ctdbsdk.ctdbStringToBigInt(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), pValue, )
  if retval != 0:
    raise DatabaseError( "StringToBigInt failed.", retval)
  return retval

def StringToUnsignedBigInt(pStr, pValue, ):
  retval = _ctdbsdk.ctdbStringToUnsignedBigInt(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), pValue, )
  if retval != 0:
    raise DatabaseError( "StringToUnsignedBigInt failed.", retval)
  return retval

def MoneyToCurrency(money, pCurrency, ):
  retval = _ctdbsdk.ctdbMoneyToCurrency(money, pCurrency, )
  if retval != 0:
    raise DatabaseError( "MoneyToCurrency failed.", retval)
  return retval

def CurrencyToMoney(currency, pMoney, ):
  retval = _ctdbsdk.ctdbCurrencyToMoney(currency, pMoney, )
  if retval != 0:
    raise DatabaseError( "CurrencyToMoney failed.", retval)
  return retval

def CurrencyToLong(currency, pValue, ):
  retval = _ctdbsdk.ctdbCurrencyToLong(currency, pValue, )
  if retval != 0:
    raise DatabaseError( "CurrencyToLong failed.", retval)
  return retval

def LongToCurrency(value, pCurrency, ):
  retval = _ctdbsdk.ctdbLongToCurrency(value, pCurrency, )
  if retval != 0:
    raise DatabaseError( "LongToCurrency failed.", retval)
  return retval

def CurrencyToBigInt(currency, pValue, ):
  retval = _ctdbsdk.ctdbCurrencyToBigInt(currency, pValue, )
  if retval != 0:
    raise DatabaseError( "CurrencyToBigInt failed.", retval)
  return retval

def BigIntToCurrency(value, pCurrency, ):
  retval = _ctdbsdk.ctdbBigIntToCurrency(value, pCurrency, )
  if retval != 0:
    raise DatabaseError( "BigIntToCurrency failed.", retval)
  return retval

def CurrencyToFloat(currency, pValue, ):
  retval = _ctdbsdk.ctdbCurrencyToFloat(currency, pValue, )
  if retval != 0:
    raise DatabaseError( "CurrencyToFloat failed.", retval)
  return retval

def FloatToCurrency(value, pCurrency, ):
  retval = _ctdbsdk.ctdbFloatToCurrency(value, pCurrency, )
  if retval != 0:
    raise DatabaseError( "FloatToCurrency failed.", retval)
  return retval

def CurrencyToString(currency, BufferSize, ):
  buf = ctypes.create_string_buffer(BufferSize+1)
  retval = _ctdbsdk.ctdbCurrencyToString(currency, buf, BufferSize, )
  if retval != 0:
    raise DatabaseError( "CurrencyToString failed.", retval)
  return buf.value.decode(ctdb_const.CTREE_CHAR_ENCODING)

def StringToCurrency(pStr, pCurrency, ):
  retval = _ctdbsdk.ctdbStringToCurrency(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), pCurrency, )
  if retval != 0:
    raise DatabaseError( "StringToCurrency failed.", retval)
  return retval

def CurrencyAdd(left, right, pResult, ):
  retval = _ctdbsdk.ctdbCurrencyAdd(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "CurrencyAdd failed.", retval)
  return retval

def CurrencySub(left, right, pResult, ):
  retval = _ctdbsdk.ctdbCurrencySub(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "CurrencySub failed.", retval)
  return retval

def CurrencyMul(left, right, pResult, ):
  retval = _ctdbsdk.ctdbCurrencyMul(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "CurrencyMul failed.", retval)
  return retval

def CurrencyDiv(left, right, pResult, ):
  retval = _ctdbsdk.ctdbCurrencyDiv(left, right, pResult, )
  if retval != 0:
    raise DatabaseError( "CurrencyDiv failed.", retval)
  return retval

def CurrencyCmp(left, right, ):
  retval = _ctdbsdk.ctdbCurrencyCmp(left, right, )
  if retval == 0:
    raise DatabaseError( "CurrencyCmp failed.")
  return retval

def CurrencyAbs(value, ):
  retval = _ctdbsdk.ctdbCurrencyAbs(value, )
  if retval == 0:
    raise DatabaseError( "CurrencyAbs failed.")
  return retval

def CurrencyRound(value, scale, ):
  retval = _ctdbsdk.ctdbCurrencyRound(value, scale, )
  if retval != 0:
    raise DatabaseError( "CurrencyRound failed.", retval)
  return retval

def MoneyToNumber(money, pNumber, ):
  retval = _ctdbsdk.ctdbMoneyToNumber(money, pNumber, )
  if retval != 0:
    raise DatabaseError( "MoneyToNumber failed.", retval)
  return retval

def NumberToMoney(pNumber, pMoney, ):
  retval = _ctdbsdk.ctdbNumberToMoney(pNumber, pMoney, )
  if retval != 0:
    raise DatabaseError( "NumberToMoney failed.", retval)
  return retval

def NumberToLong(pNumber, pValue, ):
  retval = _ctdbsdk.ctdbNumberToLong(pNumber, pValue, )
  if retval != 0:
    raise DatabaseError( "NumberToLong failed.", retval)
  return retval

def LongToNumber(value, pNumber, ):
  retval = _ctdbsdk.ctdbLongToNumber(value, pNumber, )
  if retval != 0:
    raise DatabaseError( "LongToNumber failed.", retval)
  return retval

def NumberToBigInt(pNumber, pValue, ):
  retval = _ctdbsdk.ctdbNumberToBigInt(pNumber, pValue, )
  if retval != 0:
    raise DatabaseError( "NumberToBigInt failed.", retval)
  return retval

def NumberToUnsignedBigInt(pNumber, pValue, ):
  retval = _ctdbsdk.ctdbNumberToUnsignedBigInt(pNumber, pValue, )
  if retval != 0:
    raise DatabaseError( "NumberToUnsignedBigInt failed.", retval)
  return retval

def BigIntToNumber(value, pNumber, ):
  retval = _ctdbsdk.ctdbBigIntToNumber(value, pNumber, )
  if retval != 0:
    raise DatabaseError( "BigIntToNumber failed.", retval)
  return retval

def NumberToCurrency(pNumber, pValue, ):
  retval = _ctdbsdk.ctdbNumberToCurrency(pNumber, pValue, )
  if retval != 0:
    raise DatabaseError( "NumberToCurrency failed.", retval)
  return retval

def CurrencyToNumber(value, pNumber, ):
  retval = _ctdbsdk.ctdbCurrencyToNumber(value, pNumber, )
  if retval != 0:
    raise DatabaseError( "CurrencyToNumber failed.", retval)
  return retval

def NumberToFloat(pNumber, pValue, ):
  retval = _ctdbsdk.ctdbNumberToFloat(pNumber, pValue, )
  if retval != 0:
    raise DatabaseError( "NumberToFloat failed.", retval)
  return retval

def FloatToNumber(value, pNumber, ):
  retval = _ctdbsdk.ctdbFloatToNumber(value, pNumber, )
  if retval != 0:
    raise DatabaseError( "FloatToNumber failed.", retval)
  return retval

def NumberToString(pNumber, ):
  buf = ctypes.create_string_buffer(51)
  retval = _ctdbsdk.ctdbNumberToString(pNumber, buf, 50, )
  if retval != 0:
    raise DatabaseError( "NumberToString failed.", retval)
  return buf.value.decode(ctdb_const.CTREE_CHAR_ENCODING)

def StringToNumber(pStr, pNumber, ):
  retval = _ctdbsdk.ctdbStringToNumber(pStr.encode(ctdb_const.CTREE_CHAR_ENCODING), pNumber, )
  if retval != 0:
    raise DatabaseError( "StringToNumber failed.", retval)
  return retval

def NumberAdd(pLeft, pRight, pResult, ):
  retval = _ctdbsdk.ctdbNumberAdd(pLeft, pRight, pResult, )
  if retval != 0:
    raise DatabaseError( "NumberAdd failed.", retval)
  return retval

def NumberSub(pLeft, pRight, pResult, ):
  retval = _ctdbsdk.ctdbNumberSub(pLeft, pRight, pResult, )
  if retval != 0:
    raise DatabaseError( "NumberSub failed.", retval)
  return retval

def NumberMul(pLeft, pRight, pResult, ):
  retval = _ctdbsdk.ctdbNumberMul(pLeft, pRight, pResult, )
  if retval != 0:
    raise DatabaseError( "NumberMul failed.", retval)
  return retval

def NumberDiv(pLeft, pRight, pResult, ):
  retval = _ctdbsdk.ctdbNumberDiv(pLeft, pRight, pResult, )
  if retval != 0:
    raise DatabaseError( "NumberDiv failed.", retval)
  return retval

def NumberZero(pNumber, ):
  retval = _ctdbsdk.ctdbNumberZero(pNumber, )
  if retval != 0:
    raise DatabaseError( "NumberZero failed.", retval)
  return retval

def IsNumberZero(pNumber, ):
  retval = _ctdbsdk.ctdbIsNumberZero(pNumber, )
  if retval == 0:
    raise DatabaseError( "IsNumberZero failed.")
  return retval

def NumberCmp(pLeft, pRight, ):
  retval = _ctdbsdk.ctdbNumberCmp(pLeft, pRight, )
  if retval == 0:
    raise DatabaseError( "NumberCmp failed.")
  return retval

def NumberAbs(pSource, pResult, ):
  retval = _ctdbsdk.ctdbNumberAbs(pSource, pResult, )
  if retval != 0:
    raise DatabaseError( "NumberAbs failed.", retval)
  return retval

def NumberNegate(pSource, pResult, ):
  retval = _ctdbsdk.ctdbNumberNegate(pSource, pResult, )
  if retval != 0:
    raise DatabaseError( "NumberNegate failed.", retval)
  return retval

def NumberCopy(pDest, pSource, ):
  retval = _ctdbsdk.ctdbNumberCopy(pDest, pSource, )
  if retval != 0:
    raise DatabaseError( "NumberCopy failed.", retval)
  return retval

def NumberRound(num, scale, ):
  retval = _ctdbsdk.ctdbNumberRound(num, scale, )
  if retval != 0:
    raise DatabaseError( "NumberRound failed.", retval)
  return retval

def NumberGetDecimal(data, digit_before, digit_after, ):
  retval = _ctdbsdk.ctdbNumberGetDecimal(data, digit_before, digit_after, )
  if retval != 0:
    raise DatabaseError( "NumberGetDecimal failed.", retval)
  return retval

def GetResultSetHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetResultSetHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetResultSetHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AllocateResultSet(Handle, ResSetName, ):
  retval = _ctdbsdk.ctdbAllocateResultSet(Handle, ResSetName.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval is None: 
    raise DatabaseError( "AllocateResultSet failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def FreeResultSet(Handle, ):
  retval = _ctdbsdk.ctdbFreeResultSet(Handle, )

def ResultSetOnOff(Handle, RecordHandle, OnOffFlag, AutoSortFlag, LocateMode, ):
  retval = _ctdbsdk.ctdbResultSetOnOff(Handle, RecordHandle, OnOffFlag, AutoSortFlag, LocateMode, )
  if retval != 0:
    raise DatabaseError( "ResultSetOnOff failed.", retval)
  return retval

def GetResultSetByName(Handle, ResSetName, ):
  retval = _ctdbsdk.ctdbGetResultSetByName(Handle, ResSetName.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval is None: 
    raise DatabaseError( "GetResultSetByName failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def GetResultSetCriHandle(Handle, ):
  retval = _ctdbsdk.ctdbGetResultSetCriHandle(Handle, )
  if retval is None: 
    raise DatabaseError( "GetResultSetCriHandle failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def AddCriteria(Handle, FieldHandle, LowValue, HighValue, CriteriaOp, ):
  retval = _ctdbsdk.ctdbAddCriteria(Handle, FieldHandle, LowValue.encode(ctdb_const.CTREE_CHAR_ENCODING), HighValue.encode(ctdb_const.CTREE_CHAR_ENCODING), CriteriaOp, )
  if retval is None: 
    raise DatabaseError( "AddCriteria failed.", _ctdbsdk.ctdbGetError(Handle))
  return retval

def RemoveCriteria(Handle, CriteriaHandle, ):
  retval = _ctdbsdk.ctdbRemoveCriteria(Handle, CriteriaHandle, )
  if retval != 0:
    raise DatabaseError( "RemoveCriteria failed.", retval)
  return retval

def UpdateCriteria(Handle, LowValue, HighValue, ):
  retval = _ctdbsdk.ctdbUpdateCriteria(Handle, LowValue.encode(ctdb_const.CTREE_CHAR_ENCODING), HighValue.encode(ctdb_const.CTREE_CHAR_ENCODING), )
  if retval != 0:
    raise DatabaseError( "UpdateCriteria failed.", retval)
  return retval

