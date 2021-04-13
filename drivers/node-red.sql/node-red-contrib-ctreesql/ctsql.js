const ctsqlapi = require ('./ctsqlapi');
var ref = require('ref-napi');

function readColumn(conn, cursor, column, columnName) {
	var type = ctsqlapi.ctsqlGetColumnType(cursor, column);
	var size = ctsqlapi.ctsqlGetColumnLength(cursor, column);
    if (ctsqlapi.ctsqlIsColumnNull(cursor, column)) {
        return null;
    }
	switch (type) {
        case ctsqlapi.CTSQL_CHAR:
        case ctsqlapi.CTSQL_VARCHAR:
            var buffer = Buffer.alloc(size);
            var rc = ctsqlapi.ctsqlGetChar(cursor, column, buffer);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return ref.readCString(buffer, 0);
        case ctsqlapi.CTSQL_SMALLINT:
            var smallBuffer = ref.alloc("short");
            var rc = ctsqlapi.ctsqlGetSmallInt(cursor, column, smallBuffer);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return ref.deref(smallBuffer);
        case ctsqlapi.CTSQL_INTEGER:
            var intBuffer = ref.alloc("int");
            var rc = ctsqlapi.ctsqlGetInteger(cursor, column, intBuffer);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return ref.deref(intBuffer);
        case ctsqlapi.CTSQL_TINYINT:
            var tIntBuffer = ref.alloc("char");
            var rc = ctsqlapi.ctsqlGetTinyInt(cursor, column, tIntBuffer);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return ref.deref(tIntBuffer);
        case ctsqlapi.CTSQL_BIT:
            var bit = ref.alloc("char");
            var rc = ctsqlapi.ctsqlGetBit(cursor, column, bit);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return (ref.deref(bit) == 1 ? true : false);
        case ctsqlapi.CTSQL_NUMERIC:
        case ctsqlapi.CTSQL_MONEY:
            var buffer = Buffer.alloc(16);
            var rc = ctsqlapi.ctsqlGetNumericAsString(cursor, column, buffer, 16);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return parseFloat(ref.readCString(buffer, 0));
        case ctsqlapi.CTSQL_BIGINT:
            var bigInt = ref.alloc(ref.types.longlong);
            var rc = ctsqlapi.ctsqlGetBigInt(cursor, column, bigInt);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            //ctsqlapi.ctsqlConvert(ctsqlapi.CTSQL_BIGINT, bigIntbuffer, 8, null, ctsqlapi.CTSQL_CHAR, charBuffer, 32);
            return ref.deref(bigInt);
        case ctsqlapi.CTSQL_BIGINT: // this is skipped for now.
            var bigInt = new ctsqlapi.SQLBIGINT;
            var rc = ctsqlapi.ctsqlGetBigInt(cursor, column, bigInt.ref());
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            //ctsqlapi.ctsqlConvert(ctsqlapi.CTSQL_BIGINT, bigIntbuffer, 8, null, ctsqlapi.CTSQL_CHAR, charBuffer, 32);
            return bigInt;
        case ctsqlapi.CTSQL_REAL:
            var floatBuffer = ref.alloc(ref.types.float);
            var rc = ctsqlapi.ctsqlGetReal(cursor, column, floatBuffer);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return ref.deref(floatBuffer);
        case ctsqlapi.CTSQL_FLOAT: // CTSQL_FLOAT means double and CTSQL_REAL means float
            var doubleBuffer = ref.alloc("double");
            var rc = ctsqlapi.ctsqlGetFloat(cursor, column, doubleBuffer);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return ref.deref(doubleBuffer);
        case ctsqlapi.CTSQL_DATE:
            var date = new ctsqlapi.SQLDATE();
            var rc = ctsqlapi.ctsqlGetDate(cursor, column, date.ref());
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            return {
                year: date.year,
                month: date.month,
                day: date.day
            };
        case ctsqlapi.CTSQL_TIME:
            var time = new ctsqlapi.SQLTIME();
            var rc = ctsqlapi.ctsqlGetTime(cursor, column, time.ref());
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            // ctsqlConvert(CTSQL_TIME, (void*)&timeBuffer, 32, (CTSQLCHAR*)"HH24:MI:SS.MLS", CTSQL_CHAR, buffer, 32);
            return {
                hours: time.hours,
                mins: time.mins,
                secs: time.secs,
                msecs: time.msecs
            };
        case ctsqlapi.CTSQL_TIMESTAMP:
            var timestamp = new ctsqlapi.SQLTIMESTAMP();
            var rc = ctsqlapi.ctsqlGetTimeStamp(cursor, column, timestamp.ref());
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            //ctsqlConvert(CTSQL_TIMESTAMP, (void*)&timeStampBuffer, 32, (CTSQLCHAR*)"MM/DD/YYYY HH24:MI:SS.MLS", CTSQL_CHAR, buffer, 32);
            return {
                year: timestamp.ts_date.year,
                month: timestamp.ts_date.month,
                day: timestamp.ts_date.day,
                hours: timestamp.ts_time.hours,
                mins: timestamp.ts_time.mins,
                secs: timestamp.ts_time.secs,
                msecs: timestamp.ts_time.msecs
            };
        case ctsqlapi.CTSQL_BINARY:
        case ctsqlapi.CTSQL_VARBINARY:
            throw "(VAR)BINARY is not yet supported";
            break;
        case ctsqlapi.CTSQL_LVC:
        case ctsqlapi.CTSQL_CLOB:
            var bytesRead = ref.alloc("int");
            var buffer = Buffer.alloc(size+1);
            var rc = ctsqlapi.ctsqlGetBlob(cursor, column, buffer, size + 1, 0, bytesRead);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            buffer[ref.deref(bytesRead)]=0;
            return ref.readCString(buffer, 0);
        case ctsqlapi.CTSQL_LVB:
        case ctsqlapi.CTSQL_BLOB:
            var bytesRead = ref.alloc("int");
            var buffer = Buffer.alloc(size+1);
            var rc = ctsqlapi.ctsqlGetBlob(cursor, column, buffer, size + 1, 0, bytesRead);
            if (rc != ctsqlapi.CTSQLRET_OK)
                throw ctsqlapi.ctsqlGetErrorMessage(conn);
            //ctsqlConvert(CTSQL_LVB, (void*)&binaryValue, colLength, NULL, CTSQL_CHAR, value, colLength);
            return Buffer.from(buffer, 0, ref.deref(bytesRead));
        default:  
            console.log("missing column type handler for: " + columnName + ", type:" +type);
    }
}

function ctsql() {
}

ctsql.prototype.connect = function(db, user, pass) {
  this.hConn = ctsqlapi.ctsqlNewConnection();
  var rc = ctsqlapi.ctsqlConnect(this.hConn, db, user, pass);
  if (rc != ctsqlapi.CTSQLRET_OK)
    throw new ctsqlConnectError(rc, ctsqlapi.ctsqlGetErrorMessage(this.hConn));
  ctsqlapi.ctsqlSetAutoCommit(this.hConn, 1);
}

ctsql.prototype.query = function(query, params) {
  var result={success:true};
  var hCmd = ctsqlapi.ctsqlNewCommand(this.hConn);
  var rc = ctsqlapi.ctsqlPrepare(hCmd, query);
  if( rc != ctsqlapi.CTSQLRET_OK)
    throw new ctsqlPrepareError(rc, ctsqlapi.ctsqlGetErrorMessage(this.hConn));
  if(params) {
    for (var p = 0; p < params.length; p++) {
      //console.log("setting parameter: " + params[p]);
      ctsqlapi.ctsqlSetParameterAsString( hCmd, p, ""+params[p]);
    }
  } else {
    // ctsqlapi.ctsqlExecuteDirect(hCmd, query);
  }
  var cursorPP = ref.alloc(ctsqlapi.cursorPtrPtr)
  rc = ctsqlapi.ctsqlExecute(hCmd, cursorPP);
  if( rc != ctsqlapi.CTSQLRET_OK)
    throw new ctsqlExecuteError(rc, ctsqlapi.ctsqlGetErrorMessage(this.hConn));

  var cursorP = cursorPP.deref();
    
  if( query.toLowerCase().startsWith("select ") ) {
    var columnCount = ctsqlapi.ctsqlGetColumnCount(cursorP);
    var columnNames = [];
    for (var i = 0; i < columnCount; i++) {
        columnNames.push(ctsqlapi.ctsqlGetColumnName(cursorP, i));
    }
    result = {columnNames:columnNames};
    result.rows = [];
    while (ctsqlapi.ctsqlNext(cursorP) == ctsqlapi.CTSQLRET_OK) {
        var row = [];
        for (var c = 0; c < columnCount; c++) {
            row[columnNames[c]] = row[c] = readColumn(this.hConn, cursorP, c, columnNames[c]);
        }
        result.rows.push(row);
    }
  }
  ctsqlapi.ctsqlFreeCursor(cursorP);
  ctsqlapi.ctsqlFreeCommand(hCmd);
  return result;
}

ctsql.prototype.end = function() {
  ctsqlapi.ctsqlDisconnect(this.hConn);
  ctsqlapi.ctsqlFreeConnection(this.hConn);
}

class ctsqlError extends Error {

  constructor(message){
    
    super(message);
    this.name = this.constructor.name;
    Error.captureStackTrace(this, this.constructor);
  }
}

class ctsqlConnectError extends ctsqlError {
   constructor(error, message) {
		
      super(`ctsql failed to connect with error ${error}`);
      this.data = { error, message };
   }
}

class ctsqlPrepareError extends ctsqlError {
   constructor(error, message) {
		
      super(`ctsql failed to prepare statement with error ${error}`);
      this.data = { error, message };
   }
}

class ctsqlExecuteError extends ctsqlError {
   constructor(error, message) {
		
      super(`ctsql failed to execute statement with error ${error}`);
      this.data = { error, message };
   }
}


module.exports = new ctsql();
module.exports.ctsqlConnectError = ctsqlConnectError;
module.exports.ctsqlPrepareError = ctsqlPrepareError;
module.exports.ctsqlExecuteError = ctsqlExecuteError;


//var cursor = ctsqlapi.ctsqlNewCursor(hCmd);
//
//console.log(columnCount);
