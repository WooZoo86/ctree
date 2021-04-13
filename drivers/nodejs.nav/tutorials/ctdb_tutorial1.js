const ctdb = require('ctdbsdk');
const {deleteRecords} = require('./deleteRecords');
const {addRecords} = require('./addRecords');
var ref = require('ref-napi');


var hSession = ctdb.AllocSession(ctdb.CTSESSION_CTREE);

ctdb.Logon(hSession, "FAIRCOMS", "ADMIN", "ADMIN");

var hTable = ctdb.AllocTable(hSession);

try {
    console.log("Open table...");
    ctdb.OpenTable(hTable, "custmast", ctdb.CTOPEN_NORMAL);
} catch(e) {

    console.log("Add fields...\n");
    ctdb.AddField(hTable, "cm_custnumb", ctdb.CT_FSTRING, 4);
    ctdb.AddField(hTable, "cm_custzipc", ctdb.CT_FSTRING, 9);
    ctdb.AddField(hTable, "cm_custstat", ctdb.CT_FSTRING, 2);
    ctdb.AddField(hTable, "cm_custratg", ctdb.CT_FSTRING, 1);
    ctdb.AddField(hTable, "cm_custname", ctdb.CT_STRING, 47);
    ctdb.AddField(hTable, "cm_custaddr", ctdb.CT_STRING, 47);
    ctdb.AddField(hTable, "cm_custcity", ctdb.CT_STRING, 47);

    
    /* create table */
    console.log("Create table...\n");
    ctdb.CreateTable(hTable, "custmast", ctdb.CTCREATE_NORMAL);
    ctdb.OpenTable(hTable, "custmast", ctdb.CTOPEN_NORMAL);
}

var mode = ctdb.GetTableCreateMode(hTable);
if ((mode & ctdb.CTCREATE_TRNLOG) != 0) {
    mode = mode ^ ctdb.CTCREATE_TRNLOG;
    retval = ctdb.UpdateCreateMode(hTable,mode);
    if (retval != 0)
        console.log("Check_Table_Mode(); ctdbUpdateCreateMode");
}

hRecord = ctdb.AllocRecord(hTable);

deleteRecords(hRecord);
addRecords(hRecord);

var custnumb = Buffer.alloc(4+1);
var custname = Buffer.alloc(47+1);

var retval = ctdb.FirstRecord(hRecord);
while (retval != ctdb.END_OF_FILE) {
    retval = 0;
    retval |= ctdb.GetFieldAsString(hRecord, 0, custnumb, custnumb.length);
    retval |= ctdb.GetFieldAsString(hRecord, 4, custname, custname.length);
    if (retval) {
        console.log("Display_Records(): ctdbGetFieldAsString()");
        break;
    }
    let custnumbStr = ref.readCString(custnumb, 0);
    let custnameStr = ref.readCString(custname, 0);

    console.log(custnumbStr + ", " + custnameStr);

    /* read next record */
    retval = ctdb.NextRecord(hRecord);
    if (retval == ctdb.END_OF_FILE)
        break;   /* reached end of file */

    if (retval) {
        console.log("Display_Records(): ctdbNextRecord()");
        break;
    }
}

ctdb.CloseTable(hTable);

console.log("Logout...\n");
ctdb.Logout(hSession);
    

ctdb.FreeRecord(hRecord);
ctdb.FreeTable(hTable);
ctdb.FreeSession(hSession);

