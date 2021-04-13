var ffi = require('ffi-napi');
var ref = require('ref-napi');
var Struct = require('ref-struct-napi');

var SQLBIGINT = Struct({
  'll': 'ulong',
  'hl': 'long'
});
var SQLBIGINTPtr = ref.refType(SQLBIGINT);

var SQLDATE = Struct({
  'year': 'short',
  'month': 'char',
  'day': 'char'
});
var SQLDATEPtr = ref.refType(SQLDATE);

var SQLTIME = Struct({
  'hours': 'char',
  'mins': 'char',
  'secs': 'char',
  'msecs': 'short'
});
var SQLTIMEPtr = ref.refType(SQLTIME);

var SQLTIMESTAMP = Struct({
  'ts_date': SQLDATE,
  'ts_time': SQLTIME
});
var SQLTIMESTAMPPtr = ref.refType(SQLTIMESTAMP);

var cursor = 'void'
  , cursorPtr = ref.refType(cursor)
  , cursorPtrPtr = ref.refType(cursorPtr)

var ctsqlapi_function_list = {
  'ctsqlSetSSL': ['int', ['pointer', 'string', ]],
  'ctsqlNewConnection': ['pointer', []],
  'ctsqlFreeConnection': ['void', ['pointer', ]],
  'ctsqlConnect': ['int', ['pointer', 'string', 'string', 'string', ]],
  'ctsqlDisconnect': ['int', ['pointer', ]],
  'ctsqlAttach': ['int', ['pointer', ]],
  'ctsqlDetach': ['int', ['pointer', ]],
  'ctsqlGetDatabase': ['string', ['pointer', ]],
  'ctsqlGetUsername': ['string', ['pointer', ]],
  'ctsqlGetPassword': ['string', ['pointer', ]],
  'ctsqlIsActiveConn': ['uchar', ['pointer', ]],
  'ctsqlBegin': ['int', ['pointer', ]],
  'ctsqlCommit': ['int', ['pointer', ]],
  'ctsqlAbort': ['int', ['pointer', ]],
  'ctsqlGetErrorMessage': ['string', ['pointer', ]],
  'ctsqlGetError': ['int', ['pointer', ]],
  'ctsqlClearError': ['void', ['pointer', ]],
  'ctsqlSetIsolationLevel': ['int', ['pointer', 'int', ]],
  'ctsqlGetIsolationLevel': ['int', ['pointer', ]],
  'ctsqlGetAutoCommit': ['uchar', ['pointer', ]],
  'ctsqlSetAutoCommit': ['int', ['pointer', 'uchar', ]],
  'ctsqlClearAutoCommit': ['int', ['pointer', ]],
  'ctsqlGetErrorPos': ['int', ['pointer', ]],
  'ctsqlIsUnicodeLib': ['uchar', []],
  //'ctsqlSetPreserveCursor': ['int', ['pointer', 'uchar', ]], // This will be added in the next release.
  'ctsqlNewCommand': ['pointer', ['pointer', ]],
  'ctsqlFreeCommand': ['void', ['pointer', ]],
  'ctsqlGetParameter': ['int', ['pointer', 'int', 'pointer', 'int', ]],
  'ctsqlSetParameter': ['int', ['pointer', 'int', 'short', 'int', 'uchar', 'pointer', ]],
  'ctsqlSetParameterAsString': ['int', ['pointer', 'int', 'string', ]],
  'ctsqlSetIntegerParameter': ['int', ['pointer', 'int', 'short', 'uchar', 'int', ]],
  'ctsqlSetBigIntParameter': ['int', ['pointer', 'int', 'uchar', 'pointer', ]],
  'ctsqlSetNumericParameter': ['int', ['pointer', 'int', 'short', 'uchar', 'pointer', ]],
  'ctsqlSetFloatParameter': ['int', ['pointer', 'int', 'short', 'uchar', 'double', ]],
  'ctsqlSetDateParameter': ['int', ['pointer', 'int', 'uchar', 'pointer', ]],
  'ctsqlSetTimeParameter': ['int', ['pointer', 'int', 'uchar', 'pointer', ]],
  'ctsqlSetTimeStampParameter': ['int', ['pointer', 'int', 'uchar', 'pointer', ]],
  'ctsqlSetNCharParameter': ['int', ['pointer', 'int', 'short', 'uchar', 'string', 'int', ]],
  'ctsqlSetCharParameter': ['int', ['pointer', 'int', 'short', 'uchar', 'string', 'int', ]],
  'ctsqlSetBinaryParameter': ['int', ['pointer', 'int', 'uchar', 'pointer', 'int', ]],
  'ctsqlGetParameterCount': ['int', ['pointer', ]],
  'ctsqlGetParameterType': ['short', ['pointer', 'int', ]],
  'ctsqlGetParameterLength': ['int', ['pointer', 'int', ]],
  'ctsqlGetParameterPrecision': ['short', ['pointer', 'int', ]],
  'ctsqlGetParameterScale': ['short', ['pointer', 'int', ]],
  'ctsqlGetParameterNullFlag': ['int', ['pointer', 'int', ]],
  'ctsqlGetParameterName': ['string', ['pointer', 'int', ]],
  'ctsqlGetParameterIndexByName': ['int', ['pointer', 'string', ]],
  'ctsqlSetParameterScale': ['int', ['pointer', 'int', 'short', ]],
  'ctsqlSetParameterPrecision': ['int', ['pointer', 'int', 'short', ]],
  'ctsqlPrepare': ['int', ['pointer', 'string', ]],
  'ctsqlExecute': ['int', ['pointer', 'pointer', ]],
  'ctsqlExecuteDirect': ['int', ['pointer', 'string', ]],
  'ctsqlAffectedRows': ['int', ['pointer', ]],
  'ctsqlClose': ['int', ['pointer', ]],
  'ctsqlSetBlob': ['int', ['pointer', 'int', 'pointer', 'int', 'int', ]],
  'ctsqlGetTimeout': ['int', ['pointer', ]],
  'ctsqlSetTimeout': ['int', ['pointer', 'int', ]],
  'ctsqlIsSelect': ['uchar', ['pointer', ]],
  'ctsqlIsProcedureCall': ['uchar', ['pointer', ]],
  'ctsqlSetTupleCount': ['int', ['pointer', 'int', ]],
  'ctsqlGetTupleCount': ['int', ['pointer', ]],
  'ctsqlPrepareBatch': ['int', ['pointer', 'string', 'int', ]],
  'ctsqlNextBatchItem': ['int', ['pointer', ]],
  'ctsqlSetNumericParameterAsString': ['int', ['pointer', 'int', 'short', 'uchar', 'string', ]],
  //'ctsqlGetNumericParameterAsString': ['int', ['pointer', 'int', 'string', 'int', ]], // This will be added in the next release.
  //'ctsqlIsParameterNull': ['uchar', ['pointer', 'int', ]], // This will be added in the next release.
  'ctsqlSetScrollableCursor': ['int', ['pointer', 'uchar', ]],
  'ctsqlGetScrollableCursor': ['uchar', ['pointer', ]],
  'ctsqlNewCursor': ['pointer', ['pointer', ]],
  'ctsqlNewDACursor': ['pointer', ['void', ]],
  'ctsqlFreeCursor': ['void', ['pointer', ]],
  'ctsqlGetColumnCount': ['int', ['pointer', ]],
  'ctsqlGetColumnNameLen': ['int', ['pointer', 'int', ]],
  'ctsqlGetColumnName': ['string', ['pointer', 'int', ]],
  'ctsqlGetVariableAddress': ['pointer', ['pointer', 'int', ]],
  'ctsqlGetColumnTitle': ['int', ['pointer', 'int', 'string', 'int', ]],
  'ctsqlGetColumnType': ['short', ['pointer', 'int', ]],
  'ctsqlGetColumnLength': ['int', ['pointer', 'int', ]],
  'ctsqlGetColumnPrecision': ['short', ['pointer', 'int', ]],
  'ctsqlGetColumnScale': ['short', ['pointer', 'int', ]],
  'ctsqlIsNullable': ['int', ['pointer', 'int', ]],
  'ctsqlNext': ['int', ['pointer', ]],
  'ctsqlIsColumnNull': ['uchar', ['pointer', 'int', ]],
  'ctsqlGetNChar': ['int', ['pointer', 'int', 'string', ]],
  'ctsqlGetChar': ['int', ['pointer', 'int', 'string', ]],
  'ctsqlGetNumeric': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetSmallInt': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetInteger': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetReal': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetFloat': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetDate': ['int', ['pointer', 'int', SQLDATEPtr, ]],
  'ctsqlGetMoney': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetTime': ['int', ['pointer', 'int', SQLTIMEPtr, ]],
  'ctsqlGetTimeStamp': ['int', ['pointer', 'int', SQLTIMESTAMPPtr, ]],
  'ctsqlGetTinyInt': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetBinary': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetBytes': ['int', ['pointer', 'int', 'uchar', 'int', ]],
  'ctsqlGetBit': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlGetBigInt': ['int', ['pointer', 'int', SQLBIGINTPtr, ]],
  'ctsqlGetBlob': ['int', ['pointer', 'int', 'pointer', 'int', 'int', 'int', ]],
  'ctsqlGetBlobByAddress': ['int', ['pointer', 'pointer', 'pointer', 'int', 'int', 'int', ]],
  'ctsqlGetTableName': ['int', ['pointer', 'int', 'string', 'int', ]],
  'ctsqlGetBaseTableName': ['int', ['pointer', 'int', 'string', 'int', ]],
  'ctsqlGetBaseColumnName': ['int', ['pointer', 'int', 'string', 'int', ]],
  'ctsqlIsSearchable': ['int', ['pointer', 'int', ]],
  'ctsqlIsUpdatable': ['int', ['pointer', 'int', ]],
  'ctsqlGetNumericAsString': ['int', ['pointer', 'int', 'string', 'int', ]],
  'ctsqlCompare': ['int', ['short', 'pointer', 'int', 'pointer', 'int', 'pointer', ]],
  'ctsqlConvert': ['int', ['short', 'pointer', 'int', 'string', 'short', 'pointer', 'int', ]],
  'ctsqlDayOfWeek': ['int', ['pointer', ]],
  'ctsqlAddNumeric': ['int', ['pointer', 'pointer', 'pointer', ]],
  'ctsqlSubNumeric': ['int', ['pointer', 'pointer', 'pointer', ]],
  'ctsqlMulNumeric': ['int', ['pointer', 'pointer', 'pointer', ]],
  'ctsqlDivNumeric': ['int', ['pointer', 'pointer', 'pointer', ]],
  'ctsqlRoundNumeric': ['int', ['pointer', 'int', 'int', ]],
  'ctsqlNumericToString': ['int', ['pointer', 'string', 'int', ]],
  'ctsqlStringToNumeric': ['int', ['pointer', 'int', 'pointer', ]],
  'ctsqlCleanPooled': ['int', ['pointer', ]],
  'ctsqlNewProcInfo': ['pointer', ['string', 'string', 'int', ]],
  'ctsqlFreeProcInfo': ['void', ['pointer', ]],
  'ctsqlDumpStp': ['int', ['pointer', 'pointer', ]],
  'ctsqlDumpStpRaw': ['int', ['pointer', 'pointer', 'pointer', 'pointer', ]],
  'ctsqlDeployStp': ['int', ['pointer', 'pointer', ]],
  'ctsqlDeployStpRaw': ['int', ['pointer', 'pointer', 'pointer', 'int', ]],
  'ctsqlLogStp': ['void', ['string', ]],
  'ctsqlErrStp': ['void', ['string', ]],
};

var library_names = ['ctsqlapi', 'libctsqlapi', './ctsqlapi', './libctsqlapi'];
var ctsqlapi=null;

for( lib_name of library_names ) {
    try {
      ctsqlapi = ffi.Library(lib_name, ctsqlapi_function_list);
      break;
    } catch (e) {
    }
}
 
if( ctsqlapi == null )
    throw "Could not find ctsqlapi library. Neither on path nor locally."

ctsqlapi.cursor = cursor;
ctsqlapi.cursorPtr = cursorPtr;
ctsqlapi.cursorPtrPtr = cursorPtrPtr;

ctsqlapi.CTSQLRET_OK=0;
ctsqlapi.CTSQL_CHAR=1
ctsqlapi.CTSQL_NUMERIC=2
ctsqlapi.CTSQL_SMALLINT=3
ctsqlapi.CTSQL_INTEGER=4
ctsqlapi.CTSQL_SMALLFLOAT=5
ctsqlapi.CTSQL_REAL=5
ctsqlapi.CTSQL_FLOAT=6
ctsqlapi.CTSQL_DATE=7
ctsqlapi.CTSQL_MONEY=8
ctsqlapi.CTSQL_TIME=9
ctsqlapi.CTSQL_TIMESTAMP=10
ctsqlapi.CTSQL_TINYINT=11;
ctsqlapi.CTSQL_BINARY=12
ctsqlapi.CTSQL_BIT=13
ctsqlapi.CTSQL_LVC=14
ctsqlapi.CTSQL_LVB=15
ctsqlapi.CTSQL_BIGINT=16
ctsqlapi.CTSQL_NCHAR=17
ctsqlapi.CTSQL_NVARCHAR=18
ctsqlapi.CTSQL_NCHAR_CS=19
ctsqlapi.CTSQL_NVARCHAR_CS=20
ctsqlapi.CTSQL_VARCHAR=21
ctsqlapi.CTSQL_BLOB=22
ctsqlapi.CTSQL_CLOB=23
ctsqlapi.CTSQL_NLVC=24
ctsqlapi.CTSQL_NCLOB=25
ctsqlapi.CTSQL_VARBINARY=26

ctsqlapi.SQLBIGINT = SQLBIGINT;
ctsqlapi.SQLBIGINTPtr = SQLBIGINTPtr;
ctsqlapi.SQLDATE = SQLDATE;
ctsqlapi.SQLDATEPtr = SQLDATEPtr;
ctsqlapi.SQLTIME = SQLTIME;
ctsqlapi.SQLTIMEPtr = SQLTIMEPtr;
ctsqlapi.SQLTIMESTAMP = SQLTIMESTAMP;
ctsqlapi.SQLTIMESTAMPPtr = SQLTIMESTAMPPtr;

module.exports = ctsqlapi;
