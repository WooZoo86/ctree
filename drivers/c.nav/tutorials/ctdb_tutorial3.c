/*
 * ctdb_tutorial3.c
 *
 * Public domain c-treeDB C example
 *
 * FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
 *
 * The goal of this tutorial is to introduce the most basic CTDB API
 * to accomplish creating and manipulating a table through the ctreeServer
 *
 * Functionally, this application will perform the following:
 *  1.  Logon onto a session
 *  2.  Add 1 table with some fields
 *  3.  Populate the table with a few records
 *  4.  Display the contents of the table
 *  5.  Update one record under locking control
 */

#ifdef _WIN32_WCE
#undef UNICODE
#undef _UNICODE
#define main my_main
#endif

/* Preprocessor definitions and includes */

#include "ctdbsdk.h" /* c-tree headers */

#define LOCK_SUPPORT

#ifndef ctCLIENT
#ifdef NOTFORCE
#ifndef ctSRVR
#undef LOCK_SUPPORT
#endif
#endif
#endif

#define END_OF_FILE INOT_ERR   /* INOT_ERR is ctree's 101 error. See cterrc.h */


/* Global declarations */

CTHANDLE hSession;
CTHANDLE hDatabase;
CTHANDLE hTable;
CTHANDLE hRecord;


/* Function declarations */

#ifdef PROTOTYPE
VOID Initialize(VOID), Define(VOID), Manage(VOID), Done(VOID);
VOID Add_CustomerMaster_Records(VOID), Display_Records(VOID);
VOID Update_CustomerMaster_Record(VOID), Create_CustomerMaster_Table(VOID);
VOID Delete_Records(CTHANDLE), Check_Table_Mode(CTHANDLE);
VOID Handle_Error(CTSTRING);
#else
VOID Initialize(), Define(), Manage(), Done();
VOID Add_CustomerMaster_Records(), Display_Records();
VOID Delete_Records(), Check_Table_Mode();
VOID Update_CustomerMaster_Record(), Create_CustomerMaster_Table();
VOID Handle_Error();
#endif


#ifdef ctPortAppleiOS
#define main my_main
#endif

/*
 * main()
 *
 * The main() function implements the concept of "init, define, manage
 * and you're done..."
 */

#ifdef PROTOTYPE
NINT main (NINT argc, pTEXT argv[])
#else
NINT main (argc, argv)
NINT argc;
TEXT argv[];
#endif
{
#ifdef LOCK_SUPPORT
   Initialize();

   Define();

   Manage();

   Done();
#else
   printf("\nThis tutorial demonstrates basic Record Locking. Record Locking is not");
   printf("\napplicable to c-tree's SingleUser model. In order to run this program");
   printf("\nselect a c-tree Multi-User or Client-Side type c-tree model");
#endif

#ifndef ctPortWINCE
#ifndef ctPortAppleiOS
   printf("\nPress <ENTER> key to exit . . .\n");
   getchar();
#endif
#endif

   return(0);
}


/*
 * Initialize()
 *
 * Perform the minimum requirement of logging onto the c-tree Server
 */

#ifdef PROTOTYPE
VOID Initialize(VOID)
#else
VOID Initialize()
#endif
{
   CTDBRET  retval;
   
   printf("INIT\n");

   if ((retval = ctdbStartDatabaseEngine())) /* This function is required when you are using the Server DLL model to start the underlying Server. */
      Handle_Error("Initialize(): ctdbStartDatabaseEngine()"); /* It does nothing in all other c-tree models */

   /* allocate session handle */
   if ((hSession = ctdbAllocSession(CTSESSION_CTREE)) == NULL)
      Handle_Error("Initialize(): ctdbAllocSession()");

   hDatabase = hSession; /* database not used in this tutorial */

   /* connect to server */
   printf("\tLogon to server...\n");
   if (ctdbLogon(hSession, "FAIRCOMS", "ADMIN", "ADMIN"))
      Handle_Error("Initialize(): ctdbLogon()");
}


/*
 * Define()
 *
 * Open the table, if they exist. Otherwise create and open the table
 */

#ifdef PROTOTYPE
VOID Define(VOID)
#else
VOID Define()
#endif
{
   printf("DEFINE\n");

   Create_CustomerMaster_Table();
}


/*
 * Manage()
 *
 * This function performs record adds and updates using locking
 */

#ifdef PROTOTYPE
VOID Manage(VOID)
#else
VOID Manage()
#endif
{
   printf("MANAGE\n");

   /* allocate a record handle */
   if ((hRecord = ctdbAllocRecord(hTable)) == NULL)
      Handle_Error("Manage(): ctdbAllocRecord()");

   /* delete any existing records */
   Delete_Records(hRecord);

   /* populate the table with data */
   Add_CustomerMaster_Records();

   /* display contents of table */
   Display_Records();

   /* update a record under locking control */
   Update_CustomerMaster_Record();

   /* display again after update and effects of lock */
   Display_Records();
}


/*
 * Done()
 *
 * This function handles the housekeeping of closing tables and
 * freeing of associated memory
 */

#ifdef PROTOTYPE
VOID Done(VOID)
#else
VOID Done()
#endif
{
   printf("DONE\n");

   /* close table */
   printf("\tClose table\n");
   if (ctdbCloseTable(hTable))
      Handle_Error("Done(): ctdbCloseTable()");

   /* logout */
   printf("\tLogout...\n");
   if (ctdbLogout(hSession))
      Handle_Error("Done(): ctdbLogout()");

   /* free handles */
   ctdbFreeRecord(hRecord);
   ctdbFreeTable(hTable);
   ctdbFreeSession(hSession);
   
   /* If you are linked to the Server DLL, then we should stop our Server at the end of the program.   */
   /* It does nothing in all other c-tree models */
   ctdbStopDatabaseEngine();
}


/*
 * Create_CustomerMaster_Table()
 *
 * Open table CustomerMaster, if it exists. Otherwise create it
 * along with its indices and open it
 */

#ifdef PROTOTYPE
VOID Create_CustomerMaster_Table(VOID)
#else
VOID Create_CustomerMaster_Table()
#endif
{
   CTHANDLE pField1, pField2, pField3, pField4;
   CTHANDLE pField5, pField6, pField7;
   CTHANDLE pIndex;
   CTHANDLE pIseg;

   /* define table CustomerMaster */
   printf("\ttable CustomerMaster\n");

   /* allocate a table handle */
   if ((hTable = ctdbAllocTable(hDatabase)) == NULL)
      Handle_Error("Create_CustomerMaster_Table(): ctdbAllocTable()");

   /* open table */
   if (ctdbOpenTable(hTable, "custmast", CTOPEN_NORMAL))
   {
      /* define table fields */
      pField1 = ctdbAddField(hTable, "cm_custnumb", CT_FSTRING, 4);
      pField2 = ctdbAddField(hTable, "cm_custzipc", CT_FSTRING, 9);
      pField3 = ctdbAddField(hTable, "cm_custstat", CT_FSTRING, 2);
      pField4 = ctdbAddField(hTable, "cm_custratg", CT_FSTRING, 1);
      pField5 = ctdbAddField(hTable, "cm_custname", CT_STRING, 47);
      pField6 = ctdbAddField(hTable, "cm_custaddr", CT_STRING, 47);
      pField7 = ctdbAddField(hTable, "cm_custcity", CT_STRING, 47);

      if (!pField1 || !pField2 || !pField3 || !pField4 ||
          !pField5 || !pField6|| !pField7)
         Handle_Error("Create_CustomerMaster_Table(): ctdbAddField()");

      /* define index */
      pIndex = ctdbAddIndex(hTable, "cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
      pIseg = ctdbAddSegment(pIndex, pField1, CTSEG_SCHSEG);
      if (!pIndex || !pIseg)
         Handle_Error("Create_CustomerMaster_Table(): ctdbAddIndex()|ctdbAddSegment()");

      /* create table */
      if (ctdbCreateTable(hTable, "custmast", CTCREATE_NORMAL))
         Handle_Error("Create_CustomerMaster_Table(): ctdbCreateTable()");

      /* open table */
      if (ctdbOpenTable(hTable, "custmast", CTOPEN_NORMAL))
         Handle_Error("Create_CustomerMaster_Table(): ctdbOpenTable()");
   }
   else
   {
      Check_Table_Mode(hTable);

      /* confirm the index exists, if not then add the index
       *
       * this scenario arises out of the fact that this table was created in tutorial 1
       * without indexes. The index is now created by the call to ctdbAlterTable
       */

      if (ctdbGetIndexByName(hTable, "cm_custnumb_idx") == NULL)
      {
         pField1 = ctdbGetFieldByName(hTable, "cm_custnumb");
         pIndex = ctdbAddIndex(hTable, "cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
         pIseg = ctdbAddSegment(pIndex, pField1, CTSEG_SCHSEG);
         if (!pIndex || !pIseg)
            Handle_Error("Create_CustomerMaster_Table(): ctdbAddIndex()|ctdbAddSegment()");

         if (ctdbAlterTable(hTable, CTDB_ALTER_NORMAL) != CTDBRET_OK)
            Handle_Error("Create_CustomerMaster_Table(): ctdbAlterTable()");
      }
   }
}


/*
 * Check_Table_Mode()
 *
 * Check if existing table has transaction processing flag enabled.
 * If a table is under transaction processing control, modify the
 * table mode to disable transaction processing
 */

#ifdef PROTOTYPE
VOID Check_Table_Mode(CTHANDLE hTable)
#else
VOID Check_Table_Mode(hTable)
CTHANDLE hTable;
#endif
{
   CTCREATE_MODE mode;

   /* get table create mode */
   mode = ctdbGetTableCreateMode(hTable);

   /* check if table is under transaction processing control */
   if ((mode & CTCREATE_TRNLOG))
   {
      /* change file mode to disable transaction processing */
      mode ^= CTCREATE_TRNLOG;
      if (ctdbUpdateCreateMode(hTable, mode) != CTDBRET_OK)
         Handle_Error("Check_Table_Mode(); ctdbUpdateCreateMode");
   }
}


/*
 * Delete_Records()
 *
 * This function deletes all the records in the table
 */

#ifdef PROTOTYPE
VOID Delete_Records(CTHANDLE hRecord)
#else
VOID Delete_Records(hRecord)
CTHANDLE hRecord;
#endif
{
   CTDBRET  retval;
   CTBOOL   empty;

   printf("\tDelete records...\n");

   /* enable session-wide lock flag */
   if (ctdbLock(hSession, CTLOCK_WRITE_BLOCK))
      Handle_Error("Delete_Records(): ctdbLock()");

   empty = NO;
   retval = ctdbFirstRecord(hRecord);
   if (retval != CTDBRET_OK)
   {
      if (retval == END_OF_FILE)
         empty = YES;
      else
         Handle_Error("Delete_Records(): ctdbFirstRecord()");
   }

   while (empty == NO) /* while table is not empty */
   {
      /* delete record */
      if (ctdbDeleteRecord(hRecord))
         Handle_Error("Delete_Records(): ctdbDeleteRecord()");

      /* read next record */
      retval = ctdbNextRecord(hRecord);
      if (retval != CTDBRET_OK)
      {
         if (retval == END_OF_FILE)
            empty = YES;
         else
            Handle_Error("Delete_Records(): ctdbNextRecord()");
      }
   }
   if (ctdbUnlock(hSession))
      Handle_Error("Delete_Records(): ctdbUnlock()");
}


/*
 * Add_CustomerMaster_Records()
 *
 * This function adds records to table CustomerMaster from an
 * array of strings
 */

typedef struct {
   CTSTRING number, zipcode, state, rating, name, address, city;
} CUSTOMER_DATA;

CUSTOMER_DATA data[] = {
   "1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency",      "Orange",
   "1001", "61434", "CT", "1", "Michael Jordan", "13 Main",           "Harford",
   "1002", "73677", "GA", "1", "Joshua Brown",   "4356 Cambridge",    "Atlanta",
   "1003", "10034", "MO", "1", "Keyon Dooling",  "19771 Park Avenue", "Columbia"
};

#ifdef PROTOTYPE
VOID Add_CustomerMaster_Records(VOID)
#else
VOID Add_CustomerMaster_Records()
#endif
{
   CTDBRET  retval;
   CTSIGNED i;
   CTSIGNED nRecords = sizeof(data) / sizeof(CUSTOMER_DATA);

   printf("\tAdd records...\n");

   /* add data to table */
   for (i = 0; i < nRecords; i++)
   {
      /* clear record buffer */
      ctdbClearRecord(hRecord);

      retval = 0;
      /* populate record buffer with data */
      retval |= ctdbSetFieldAsString(hRecord, 0, data[i].number);
      retval |= ctdbSetFieldAsString(hRecord, 1, data[i].zipcode);
      retval |= ctdbSetFieldAsString(hRecord, 2, data[i].state);
      retval |= ctdbSetFieldAsString(hRecord, 3, data[i].rating);
      retval |= ctdbSetFieldAsString(hRecord, 4, data[i].name);
      retval |= ctdbSetFieldAsString(hRecord, 5, data[i].address);
      retval |= ctdbSetFieldAsString(hRecord, 6, data[i].city);

      if (retval)
         Handle_Error("Add_CustomerMaster_Records(): ctdbSetFieldAsString()");

      /* add record */
      if (ctdbWriteRecord(hRecord))
         Handle_Error("Add_CustomerMaster_Records(): ctdbWriteRecord()");
   }
}


/*
 * Display_Records()
 *
 * This function displays the contents of a table. ctdbFirstRecord() and
 * ctdbNextRecord() fetch the record. Then each field is parsed and displayed
 */

#ifdef PROTOTYPE
VOID Display_Records(VOID)
#else
VOID Display_Records()
#endif
{
   CTDBRET  retval;
   TEXT     custnumb[4+1];
   TEXT     custname[47+1];

   printf("\tDisplay records...");

   /* read first record */
   retval = ctdbFirstRecord(hRecord);
   if (retval == END_OF_FILE)
      return;

   while (retval == CTDBRET_OK)
   {
      retval = 0;
      retval |= ctdbGetFieldAsString(hRecord, 0, custnumb, sizeof(custnumb));
      retval |= ctdbGetFieldAsString(hRecord, 4, custname, sizeof(custname));
      if (retval)
         Handle_Error("Display_Records(): ctdbGetFieldAsString()");

      printf("\n\t\t%-8s%10s\n",custnumb, custname);

      /* read next record */
      retval = ctdbNextRecord(hRecord);
      if (retval == END_OF_FILE)
         break;   /* reached end of file */

      if (retval != CTDBRET_OK)
         Handle_Error("Display_Records(): ctdbNextRecord()");
   }
}


/*
 * Update_CustomerMaster_Records()
 *
 * Update one record under locking control to demonstrate the effects
 * of locking
 */

#ifdef PROTOTYPE
VOID Update_CustomerMaster_Record(VOID)
#else
VOID Update_CustomerMaster_Record()
#endif
{
   printf("\tUpdate record...\n");

   /* enable session-wide lock flag */
   if (ctdbLock(hSession, CTLOCK_WRITE_BLOCK))
      Handle_Error("Update_CustomerMaster_Record(): ctdbLock()");

   /* find record by customer number */
   if (ctdbClearRecord(hRecord))
      Handle_Error("Update_CustomerMaster_Record(): ctdbClearRecord()");
   if (ctdbSetFieldAsString(hRecord, 0, "1003"))
      Handle_Error("Update_CustomerMaster_Record(): ctdbSetFieldAsString()");
   if (ctdbFindRecord(hRecord, CTFIND_EQ))
      Handle_Error("Update_CustomerMaster_Record(): ctdbFindRecord()");

   if (ctdbSetFieldAsString(hRecord, 4, "KEYON DOOLING"))
      Handle_Error("Update_CustomerMaster_Record(): ctdbSetFieldAsString()");
   /* rewrite record */
   if (ctdbWriteRecord(hRecord))
      Handle_Error("Update_CustomerMaster_Record(): ctdbWriteRecord()");
   else
   {
      printf("\tPress <ENTER> key to unlock\n");
      getchar();
   }

   if (ctdbUnlock(hSession))
      Handle_Error("Update_CustomerMaster_Record(): ctdbUnlock()");
}

/*
 * Handle_Error()
 *
 * This function is a common bailout routine. It displays an error message
 * allowing the user to acknowledge before terminating the application
 */

#ifdef PROTOTYPE
VOID Handle_Error(CTSTRING errmsg)
#else
VOID Handle_Error(errmsg)
CTSTRING errmsg;
#endif
{
   printf("\nERROR: [%d] - %s \n", ctdbGetError(hSession), errmsg);
   printf("*** Execution aborted *** \n");
#ifndef ctPortAppleiOS
   printf("Press <ENTER> key to exit...");
#endif
   ctdbLogout(hSession);

   ctdbFreeRecord(hRecord);
   ctdbFreeTable(hTable);
   ctdbFreeSession(hSession);
#ifndef ctPortAppleiOS
   getchar();
#endif
   exit(1);
}

/* end of ctdb_tutorial3.c */
