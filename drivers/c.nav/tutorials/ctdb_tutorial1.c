/*
 * ctdb_tutorial1.c
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
 */

#ifdef _WIN32_WCE
#undef UNICODE
#undef _UNICODE
#define main my_main
#endif


/* Preprocessor definitions and includes */

#include "ctdbsdk.h" /* c-tree headers */

#define END_OF_FILE INOT_ERR  /* INOT_ERR is ctree's 101 error. See cterrc.h */


/* Global declarations */

CTHANDLE hSession;
CTHANDLE hDatabase;
CTHANDLE hTable;
CTHANDLE hRecord;


/* Function declarations */

#ifdef PROTOTYPE
VOID Initialize(VOID), Define(VOID), Manage(VOID), Done(VOID);
VOID Add_Records(VOID), Display_Records(VOID);
VOID Delete_Records(CTHANDLE), Check_Table_Mode(CTHANDLE);
VOID Handle_Error(CTSTRING);
#else
VOID Initialize(), Define(), Manage(), Done();
VOID Add_Records(), Display_Records();
VOID Delete_Records(), Check_Table_Mode();
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
   Initialize();

   Define();

   Manage();

   Done();

#ifndef ctPortAppleiOS
   printf("\nPress <ENTER> key to exit . . .\n");
#ifndef ctPortWINCE
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
 * Open the table, if it exists. Otherwise create and open the table
 */

#ifdef PROTOTYPE
VOID Define(VOID)
#else
VOID Define()
#endif
{
   CTHANDLE hField1, hField2, hField3, hField4;
   CTHANDLE hField5, hField6, hField7;

   printf("DEFINE\n");

   /* allocate a table handle */
   if ((hTable = ctdbAllocTable(hDatabase)) == NULL)
      Handle_Error("Define(); ctdbAllocTable()");

   /* open table */
   printf("\tOpen table...\n");
   if (ctdbOpenTable(hTable, "custmast", CTOPEN_NORMAL))
   {
      /* define table fields */
      printf("\tAdd fields...\n");
      hField1 = ctdbAddField(hTable, "cm_custnumb", CT_FSTRING, 4);
      hField2 = ctdbAddField(hTable, "cm_custzipc", CT_FSTRING, 9);
      hField3 = ctdbAddField(hTable, "cm_custstat", CT_FSTRING, 2);
      hField4 = ctdbAddField(hTable, "cm_custratg", CT_FSTRING, 1);
      hField5 = ctdbAddField(hTable, "cm_custname", CT_STRING, 47);
      hField6 = ctdbAddField(hTable, "cm_custaddr", CT_STRING, 47);
      hField7 = ctdbAddField(hTable, "cm_custcity", CT_STRING, 47);

      if (!hField1 || !hField2 || !hField3 || !hField4 ||
          !hField5 || !hField6|| !hField7)
         Handle_Error("Define(); ctdbAddField()");

      /* create table */
      printf("\tCreate table...\n");
      if (ctdbCreateTable(hTable, "custmast", CTCREATE_NORMAL))
         Handle_Error("Define(); ctdbCreateTable()");

      if (ctdbOpenTable(hTable, "custmast", CTOPEN_NORMAL))
         Handle_Error("Define(); ctdbOpenTable()");
   }
   else
      Check_Table_Mode(hTable);
}


/*
 * Manage()
 *
 * This function performs simple record functions of add, delete and gets
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
   Add_Records();

   /* display contents of table */
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
   printf("\tClose table...\n");
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
}


/*
 * Add_Records()
 *
 * This function adds records to a table in the database from an
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
VOID Add_Records(VOID)
#else
VOID Add_Records()
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
         Handle_Error("Add_Records(): ctdbSetFieldAsString()");

      /* add record */
      if (ctdbWriteRecord(hRecord))
         Handle_Error("Add_Records(): ctdbWriteRecord()");
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
   if (retval != CTDBRET_OK)
      Handle_Error("Display_Records(): ctdbFirstRecord()");

   while (retval != END_OF_FILE)
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

/* end of ctdb_tutorial1.c */
