/*
 * ctdb_tutorial4.c
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
 *  2.  Create 4 tables each with an index
 *  3.  Add records in multiple tables under transaction processing control
 *  4.  Display the contents of the tables
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

/* Session handle */
CTHANDLE hSession;

/* Database handle */
CTHANDLE hDatabase;

/* Table handles */
CTHANDLE hTableCustMast;
CTHANDLE hTableCustOrdr;
CTHANDLE hTableOrdrItem;
CTHANDLE hTableItemMast;

/* Record handles */
CTHANDLE hRecordCustMast;
CTHANDLE hRecordCustOrdr;
CTHANDLE hRecordOrdrItem;
CTHANDLE hRecordItemMast;

/* Function declarations */

#ifdef PROTOTYPE
VOID Initialize(VOID), Define(VOID), Manage(VOID), Done(VOID);

VOID Create_CustomerMaster_Table(VOID), Create_ItemMaster_Table(VOID);
VOID Create_OrderItems_Table(VOID), Create_CustomerOrders_Table(VOID);

VOID Add_CustomerMaster_Records(VOID), Add_ItemMaster_Records(VOID);
VOID Add_Transactions(VOID);
VOID Display_CustomerOrders(VOID), Display_OrderItems(VOID);
VOID Delete_Records(CTHANDLE hRecord);
VOID Check_Table_Mode(CTHANDLE hTable);

VOID Handle_Error(CTSTRING);
#else
VOID Initialize(), Define(), Manage(), Done();

VOID Create_CustomerMaster_Table(), Create_ItemMaster_Table();
VOID Create_OrderItems_Table(), Create_CustomerOrders_Table();

VOID Add_CustomerMaster_Records(), Add_ItemMaster_Records();
VOID Add_Transactions();
VOID Display_CustomerOrders(), Display_OrderItems(VOID);
VOID Delete_Records();
VOID Check_Table_Mode();

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
#ifdef TRANPROC
   Initialize();

   Define();

   Manage();

   Done();
#else
   printf("\nThis tutorial demonstrates basic Transaction Processing. Transaction Processing is not");
   printf("\nactivated in your chosen c-tree's model. In order to run this program select a ");
   printf("\nc-tree model that supports Transaction processing, like the Client-Side c-tree model.");
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
 * Open the tables, if they exist. Otherwise create and open the tables
 */

#ifdef PROTOTYPE
VOID Define(VOID)
#else
VOID Define()
#endif
{
   printf("DEFINE\n");

   Create_CustomerMaster_Table();
   Create_CustomerOrders_Table();
   Create_OrderItems_Table();
   Create_ItemMaster_Table();
}


/*
 * Manage()
 *
 * Populates table and perform a simple query
 *
 */

#ifdef PROTOTYPE
VOID Manage(VOID)
#else
VOID Manage()
#endif
{
   printf("MANAGE\n");

   if ((hRecordCustMast = ctdbAllocRecord(hTableCustMast)) == NULL)
      Handle_Error("Add_Customer_Records(): ctdbAllocRecord()");
   if ((hRecordCustOrdr = ctdbAllocRecord(hTableCustOrdr)) == NULL)
      Handle_Error("Add_Customer_Records(): ctdbAllocRecord()");
   if ((hRecordOrdrItem = ctdbAllocRecord(hTableOrdrItem)) == NULL)
      Handle_Error("Add_Customer_Records(): ctdbAllocRecord()");
   if ((hRecordItemMast = ctdbAllocRecord(hTableItemMast)) == NULL)
      Handle_Error("Add_Customer_Records(): ctdbAllocRecord()");

   /* write lock required for transaction updates */
   if (ctdbLock(hSession, CTLOCK_WRITE))
      Handle_Error("Manage(): ctdbLock()");

   /* start a transaction */
   if (ctdbBegin(hSession))
      Handle_Error("Manage(): ctdbBegin()");

   /* populate the tables with data */
   Add_CustomerMaster_Records();
   Add_ItemMaster_Records();

   /* commit transaction */
   if (ctdbCommit(hSession))
      Handle_Error("Manage(): ctdbCommit()");

   /* free locks */
   if (ctdbUnlock(hSession))
      Handle_Error("Manage(): ctdbUnlock()");

   Add_Transactions();

   /* display the orders and their items */
   Display_CustomerOrders();
   Display_OrderItems();
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

   /* close tables */
   printf("\tClose tables...\n");
   if (ctdbCloseTable(hTableCustMast))
      Handle_Error("Done(): ctdbCloseTable()");
   if (ctdbCloseTable(hTableOrdrItem))
      Handle_Error("Done(): ctdbCloseTable()");
   if (ctdbCloseTable(hTableCustOrdr))
      Handle_Error("Done(): ctdbCloseTable()");
   if (ctdbCloseTable(hTableItemMast))
      Handle_Error("Done(): ctdbCloseTable()");

   /* logout */
   printf("\tLogout...\n");
   if (ctdbLogout(hSession))
      Handle_Error("Done(): ctdbLogout()");

   /* free handles */
   ctdbFreeRecord(hRecordCustMast);
   ctdbFreeRecord(hRecordItemMast);
   ctdbFreeRecord(hRecordOrdrItem);
   ctdbFreeRecord(hRecordCustOrdr);

   ctdbFreeTable(hTableCustMast);
   ctdbFreeTable(hTableItemMast);
   ctdbFreeTable(hTableOrdrItem);
   ctdbFreeTable(hTableCustOrdr);

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
   if ((hTableCustMast = ctdbAllocTable(hDatabase)) == NULL)
      Handle_Error("Create_CustomerMaster_Table(): ctdbAllocTable()");

   /* open table */
   if (ctdbOpenTable(hTableCustMast, "custmast", CTOPEN_NORMAL))
   {
      /* define table fields */
      pField1 = ctdbAddField(hTableCustMast, "cm_custnumb", CT_FSTRING, 4);
      pField2 = ctdbAddField(hTableCustMast, "cm_custzipc", CT_FSTRING, 9);
      pField3 = ctdbAddField(hTableCustMast, "cm_custstat", CT_FSTRING, 2);
      pField4 = ctdbAddField(hTableCustMast, "cm_custratg", CT_FSTRING, 1);
      pField5 = ctdbAddField(hTableCustMast, "cm_custname", CT_STRING, 47);
      pField6 = ctdbAddField(hTableCustMast, "cm_custaddr", CT_STRING, 47);
      pField7 = ctdbAddField(hTableCustMast, "cm_custcity", CT_STRING, 47);

      if (!pField1 || !pField2 || !pField3 || !pField4 ||
          !pField5 || !pField6|| !pField7)
         Handle_Error("Create_CustomerMaster_Table(): ctdbAddField()");

      /* define index */
      pIndex = ctdbAddIndex(hTableCustMast, "cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
      pIseg = ctdbAddSegment(pIndex, pField1, CTSEG_SCHSEG);
      if (!pIndex || !pIseg)
         Handle_Error("Create_CustomerMaster_Table(): ctdbAddIndex()|ctdbAddSegment()");

      /* create table */
      if (ctdbCreateTable(hTableCustMast, "custmast", CTCREATE_TRNLOG))
         Handle_Error("Create_CustomerMaster_Table(): ctdbCreateTable()");

      /* open table */
      if (ctdbOpenTable(hTableCustMast, "custmast", CTOPEN_NORMAL))
         Handle_Error("Create_CustomerMaster_Table(): ctdbOpenTable()");
   }
   else
   {
      Check_Table_Mode(hTableCustMast);

      /* confirm the index exists, if not then add the index
       *
       * this scenario arises out of the fact that this table was created in tutorial 1
       * without indexes. The index is now created by the call to ctdbAlterTable
       */

      if (ctdbGetIndexByName(hTableCustMast, "cm_custnumb_idx") == NULL)
      {
         pField1 = ctdbGetFieldByName(hTableCustMast, "cm_custnumb");
         pIndex = ctdbAddIndex(hTableCustMast, "cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
         pIseg = ctdbAddSegment(pIndex, pField1, CTSEG_SCHSEG);
         if (!pIndex || !pIseg)
            Handle_Error("Create_CustomerMaster_Table(): ctdbAddIndex()|ctdbAddSegment()");

         if (ctdbAlterTable(hTableCustMast, CTDB_ALTER_NORMAL) != CTDBRET_OK)
            Handle_Error("Create_CustomerMaster_Table(): ctdbAlterTable()");
      }
   }
}


/*
 * Create_CustomerOrders_Table()
 *
 * Open table CustomerOrders, if it exists. Otherwise create it
 * along with its indices and open it
 */

#ifdef PROTOTYPE
VOID Create_CustomerOrders_Table(VOID)
#else
VOID Create_CustomerOrders_Table()
#endif
{
   CTHANDLE pField1, pField2, pField3, pField4;
   CTHANDLE pIndex1, pIndex2;
   CTHANDLE pIseg1, pIseg2;

   /* define table CustomerOrders */
   printf("\ttable CustomerOrders\n");

   /* allocate a table handle */
   if ((hTableCustOrdr = ctdbAllocTable(hDatabase)) == NULL)
      Handle_Error("Create_CustomerOrders_Table(): ctdbAllocTable()");

   /* open table */
   if (ctdbOpenTable(hTableCustOrdr, "custordr", CTOPEN_NORMAL))
   {
      /* define table fields */
      pField1 = ctdbAddField(hTableCustOrdr, "co_ordrdate", CT_DATE, 4);
      pField2 = ctdbAddField(hTableCustOrdr, "co_promdate", CT_DATE, 4);
      pField3 = ctdbAddField(hTableCustOrdr, "co_ordrnumb", CT_FSTRING, 6);
      pField4 = ctdbAddField(hTableCustOrdr, "co_custnumb", CT_FSTRING, 4);

      if (!pField1 || !pField2 || !pField3 || !pField4)
         Handle_Error("Define(): ctdbAddField()");

      /* define indices */
      pIndex1 = ctdbAddIndex(hTableCustOrdr, "co_ordrnumb_idx", CTINDEX_LEADING, NO, NO);
      pIseg1 = ctdbAddSegment(pIndex1, pField3, CTSEG_SCHSEG);
      pIndex2 = ctdbAddIndex(hTableCustOrdr, "co_custnumb_idx", CTINDEX_LEADING, YES, NO);
      pIseg2 = ctdbAddSegment(pIndex2, pField4, CTSEG_SCHSEG);
      if (!pIndex1 || !pIseg1 || !pIndex2 || !pIseg2)
         Handle_Error("Create_CustomerOrders_Table(): ctdbAddIndex()|ctdbAddSegment()");

      /* create table */
      if (ctdbCreateTable(hTableCustOrdr, "custordr", CTCREATE_TRNLOG))
         Handle_Error("Create_CustomerOrders_Table(): ctdbCreateTable()");

      /* open table */
      if (ctdbOpenTable(hTableCustOrdr, "custordr", CTOPEN_NORMAL))
         Handle_Error("Create_CustomerOrders_Table(): ctdbOpenTable()");
   }
   else
      Check_Table_Mode(hTableCustOrdr);
}


/*
 * Create_OrderItems_Table()
 *
 * Open table OrderItems, if it exists. Otherwise create it
 * along with its indices and open it
 */

#ifdef PROTOTYPE
VOID Create_OrderItems_Table(VOID)
#else
VOID Create_OrderItems_Table()
#endif
{
   CTHANDLE pField1, pField2, pField3, pField4;
   CTHANDLE pIndex1, pIndex2;
   CTHANDLE pIseg1, pIseg2, pIseg3;

   /* define table OrderItems */
   printf("\ttable OrderItems\n");

   /* allocate a table handle */
   if ((hTableOrdrItem = ctdbAllocTable(hDatabase)) == NULL)
      Handle_Error("Create_OrderItems_Table(): ctdbAllocTable()");

   if (ctdbOpenTable(hTableOrdrItem, "ordritem", CTOPEN_NORMAL))
   {
      /* define table fields */
      pField1 = ctdbAddField(hTableOrdrItem,"oi_sequnumb", CT_INT2, 2);
      pField2 = ctdbAddField(hTableOrdrItem,"oi_quantity", CT_INT2, 2);
      pField3 = ctdbAddField(hTableOrdrItem,"oi_ordrnumb", CT_FSTRING, 6);
      pField4 = ctdbAddField(hTableOrdrItem,"oi_itemnumb", CT_FSTRING, 5);
      if (!pField1 || !pField2 || !pField3 || !pField4)
         Handle_Error("Create_OrderItems_Table(): ctdbAddField()");

      /* define indices */
      pIndex1 = ctdbAddIndex(hTableOrdrItem, "oi_ordrnumb_idx" ,CTINDEX_LEADING, NO, NO);
      pIseg1 = ctdbAddSegment(pIndex1, pField3, CTSEG_SCHSEG);
      pIseg2 = ctdbAddSegment(pIndex1, pField1, CTSEG_SCHSEG);
      pIndex2 = ctdbAddIndex(hTableOrdrItem, "oi_itemnumb_idx" ,CTINDEX_LEADING, YES, NO);
      pIseg3 = ctdbAddSegment(pIndex2, pField4, CTSEG_SCHSEG);
      if (!pIndex1 || !pIseg1 || !pIseg2 || !pIndex2 || !pIseg3)
         Handle_Error("Create_OrderItems_Table(): ctdbAddIndex()|ctdbAddSegment()");

      /* create table */
      if (ctdbCreateTable(hTableOrdrItem, "ordritem", CTCREATE_TRNLOG))
         Handle_Error("Create_OrderItems_Table(): ctdbCreateTable()");

      /* open table */
      if (ctdbOpenTable(hTableOrdrItem, "ordritem", CTOPEN_NORMAL))
         Handle_Error("Create_OrderItems_Table(): ctdbOpenTable()");
   }
   else
      Check_Table_Mode(hTableOrdrItem);
}


/*
 * Create_ItemMaster_Table()
 *
 * Open table ItemMaster, if it exists. Otherwise create it
 * along with its indices and open it
 */

#ifdef PROTOTYPE
VOID Create_ItemMaster_Table(VOID)
#else
VOID Create_ItemMaster_Table()
#endif
{
   CTHANDLE pField1, pField2, pField3, pField4;
   CTHANDLE pIndex;
   CTHANDLE pIseg;

   /* define table ItemMaster */
   printf("\ttable ItemMaster\n");

   /* allocate a table handle */
   if ((hTableItemMast = ctdbAllocTable(hDatabase)) == NULL)
      Handle_Error("Create_ItemMaster_Table(): ctdbAllocTable()");

   /* open table */
   if (ctdbOpenTable(hTableItemMast, "itemmast", CTOPEN_NORMAL))
   {
      /* define table fields */
      pField1 = ctdbAddField(hTableItemMast, "im_itemwght", CT_INT4, 4);
      pField2 = ctdbAddField(hTableItemMast, "im_itempric", CT_MONEY, 4);
      pField3 = ctdbAddField(hTableItemMast, "im_itemnumb", CT_FSTRING, 5);
      pField4 = ctdbAddField(hTableItemMast, "im_itemdesc", CT_STRING, 47);
      if (!pField1 || !pField2 || !pField3 || !pField4)
         Handle_Error("Create_ItemMaster_Table(): ctdbAddField()");

      /* define index */
      pIndex = ctdbAddIndex(hTableItemMast, "im_itemnumb_idx", CTINDEX_FIXED, NO, NO);
      pIseg  = ctdbAddSegment(pIndex, pField3, CTSEG_SCHSEG);
      if (!pIndex || !pIseg)
         Handle_Error("Create_ItemMaster_Table(): ctdbAddIndex()|ctdbAddSegment()");

      /* create table */
      if (ctdbCreateTable(hTableItemMast, "itemmast", CTCREATE_TRNLOG))
         Handle_Error("Create_ItemMaster_Table(); ctdbCreateTable()");

      /* open table */
      if (ctdbOpenTable(hTableItemMast, "itemmast", CTOPEN_NORMAL))
         Handle_Error("Create_ItemMaster_Table(): ctdbOpenTable()");
   }
   else
      Check_Table_Mode(hTableItemMast);
}


/*
 * Check_Table_Mode()
 *
 * Check if existing table has transaction processing flag enabled.
 * If a table is not ready for transaction, modify the table mode to
 * enable transaction processing
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

   /* check if table is not under transaction processing control */
   if (!(mode & CTCREATE_TRNLOG))
   {
      /* change file mode to enable transaction processing */
      mode |= CTCREATE_TRNLOG;
      if (ctdbUpdateCreateMode(hTable, mode) != CTDBRET_OK)
         Handle_Error("Check_Table_Mode(); ctdbUpdateCreateMode");
   }
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

CUSTOMER_DATA data4[] = {
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
   CTSIGNED nRecords = sizeof(data4) / sizeof(CUSTOMER_DATA);

   Delete_Records(hRecordCustMast);

   printf("\tAdd records in table CustomerMaster...\n");

   /* add records to table */
   for (i = 0; i < nRecords; i++)
   {
      /* clear record buffer */
      ctdbClearRecord(hRecordCustMast);

      retval = 0;
      /* populate record buffer with data */
      retval |= ctdbSetFieldAsString(hRecordCustMast, 0, data4[i].number);
      retval |= ctdbSetFieldAsString(hRecordCustMast, 1, data4[i].zipcode);
      retval |= ctdbSetFieldAsString(hRecordCustMast, 2, data4[i].state);
      retval |= ctdbSetFieldAsString(hRecordCustMast, 3, data4[i].rating);
      retval |= ctdbSetFieldAsString(hRecordCustMast, 4, data4[i].name);
      retval |= ctdbSetFieldAsString(hRecordCustMast, 5, data4[i].address);
      retval |= ctdbSetFieldAsString(hRecordCustMast, 6, data4[i].city);

      if(retval)
         Handle_Error("Add_Customer_Records(): ctdbSetFieldAsString()");

      /* add record */
      if (ctdbWriteRecord(hRecordCustMast))
         Handle_Error("Add_Customer_Records(): ctdbWriteRecord()");
   }
}


/*
 * Add_ItemMaster_Records()
 *
 * This function adds records to table ItemMaster from an
 * array of strings
 */

typedef struct {
   CTSIGNED weight;
   CTMONEY  price;
   CTSTRING itemnum, description;
} ITEM_DATA;

ITEM_DATA data3[] = {
   {10,  1995, "1",  "Hammer"},
   {3,   999,  "2",  "Wrench"},
   {4,   1659, "3",  "Saw"},
   {1,   398,  "4",  "Pliers"}
};

#ifdef PROTOTYPE
VOID Add_ItemMaster_Records(VOID)
#else
VOID Add_ItemMaster_Records()
#endif
{
   CTDBRET  retval;
   CTSIGNED i;
   CTSIGNED nRecords = sizeof(data3) / sizeof(ITEM_DATA);

   Delete_Records(hRecordItemMast);

   printf("\tAdd records in table ItemMaster...\n");

   /* add records to table */
   for (i = 0; i < nRecords; i++)
   {
      /* clear record buffer */
      ctdbClearRecord(hRecordItemMast);

      retval = 0;
      /* populate record buffer with data */
      retval |= ctdbSetFieldAsSigned(hRecordItemMast, 0, data3[i].weight);
      retval |= ctdbSetFieldAsMoney(hRecordItemMast, 1, data3[i].price);
      retval |= ctdbSetFieldAsString(hRecordItemMast, 2, data3[i].itemnum);
      retval |= ctdbSetFieldAsString(hRecordItemMast, 3, data3[i].description);

      if(retval)
         Handle_Error("Add_ItemMaster_Records(): ctdbSetFieldAsString()|ctdbSetFieldAsSigned()");

      /* add record */
      if (ctdbWriteRecord(hRecordItemMast))
         Handle_Error("Add_ItemMaster_Records(): ctdbWriteRecord()");
   }
}


/*
 * Delete_Records()
 *
 * This function deletes all the records in the table based
 * on the input parameter
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

   if (ctdbClearRecord(hRecord))
      Handle_Error("Delete_Records(): ctdbClearRecord()");


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
 * Add_Transactions()
 *
 * Add an Order and associated Items "as a transaction" to their
 * respective tables.  A transaction is committed or aborted if the
 * customer number on the order is confirmed valid.  Likewise each
 * item in the order is verified to be a valid item.  SavePoints are
 * established as an order is processed, allowing a transaction to
 * rollback to the previously verified item
 */

typedef struct {
   CTSTRING orderdate, promdate, ordernum, custnum;
} ORDER_DATA;

typedef struct {
   CTSTRING ordernum;
   CTSIGNED sequnumb;
   CTSIGNED quantity;
   CTSTRING itemnumb;
} ORDERITEM_DATA;

ORDER_DATA orders[] = {
   {"09/01/2002", "09/05/2002", "1", "1001"},
   {"09/02/2002", "09/06/2002", "2", "9999"},   /* bad customer number */
   {"09/22/2002", "09/26/2002", "3", "1003"}
};

ORDERITEM_DATA items[] = {
   {"1", 1, 2, "1"},
   {"1", 2, 1, "2"},
   {"2", 1, 1, "3"},
   {"2", 2, 3, "4"},
   {"3", 1, 2, "3"},
   {"3", 2, 2, "99"} /* bad item number */
};

#ifdef PROTOTYPE
VOID Add_Transactions(VOID)
#else
VOID Add_Transactions()
#endif
{
   CTDBRET  retval;
   NINT     savepoint;
   CTDATE   orderdate;
   CTDATE   promdate;
   CTSIGNED i, j = 0;
   CTSIGNED nOrders = sizeof(orders) / sizeof(ORDER_DATA);
   CTSIGNED nItems = sizeof(items) / sizeof(ORDERITEM_DATA);

   /* write lock required for transaction updates */
   if (ctdbLock(hSession, CTLOCK_WRITE))
      Handle_Error("Add_Transactions(): ctdbLock()");

   /* start a transaction */
   if (ctdbBegin(hSession))
      Handle_Error("Add_Transactions(): ctdbBegin()");

   Delete_Records(hRecordCustOrdr);
   Delete_Records(hRecordOrdrItem);

   /* commit transaction */
   if (ctdbCommit(hSession))
      Handle_Error("Add_Transactions(): ctdbCommit()");

   /* free locks */
   if (ctdbUnlock(hSession))
      Handle_Error("Add_Transactions(): ctdbUnlock()");

   printf("\tAdd transaction records... \n");

   /* process orders */
   for(i = 0; i < nOrders; i++)
   {
      /* start a transaction */
      if (ctdbBegin(hSession))
         Handle_Error("Add_Transactions(): ctdbBegin()");

      ctdbClearRecord(hRecordCustOrdr);

      retval = 0;
      /* populate record buffer with order data */
      retval |= ctdbStringToDate(orders[i].orderdate, CTDATE_MDCY, &orderdate);
      retval |= ctdbStringToDate(orders[i].promdate, CTDATE_MDCY, &promdate);
      retval |= ctdbSetFieldAsDate(hRecordCustOrdr, 0, orderdate);
      retval |= ctdbSetFieldAsDate(hRecordCustOrdr, 1, promdate);
      retval |= ctdbSetFieldAsString(hRecordCustOrdr, 2, orders[i].ordernum);
      retval |= ctdbSetFieldAsString(hRecordCustOrdr, 3, orders[i].custnum);
      if(retval)
         Handle_Error("Add_Transactions(): ctdbSetFieldAsString()");

      /* add order record */
      if (ctdbWriteRecord(hRecordCustOrdr))
         Handle_Error("Add_Transactions(): ctdbWriteRecord()");

      /* set transaction savepoint */
      savepoint = ctdbSetSavePoint(hSession);

      /* process order items */
      while (!(strcmp(items[j].ordernum, orders[i].ordernum)))
      {
         ctdbClearRecord(hRecordOrdrItem);

         retval = 0;
         /* populate record buffer with order item data */
         retval |= ctdbSetFieldAsSigned(hRecordOrdrItem, 0, items[j].sequnumb);
         retval |= ctdbSetFieldAsSigned(hRecordOrdrItem, 1, items[j].quantity);
         retval |= ctdbSetFieldAsString(hRecordOrdrItem, 2, items[j].ordernum);
         retval |= ctdbSetFieldAsString(hRecordOrdrItem, 3, items[j].itemnumb);

         if (retval)
            Handle_Error("Add_Transactions(): ctdbSetFieldAsString()|ctdbSetFieldAsSigned()");

         /* add order item record */
         if (ctdbWriteRecord(hRecordOrdrItem))
            Handle_Error("Add_Transactions(): ctdbWriteRecord()");

         /* check that item exists in ItemMaster table */
         if (ctdbClearRecord(hRecordItemMast))
            Handle_Error("Add_Transactions(): ctdbClearRecord()");
         if (ctdbSetFieldAsString(hRecordItemMast, 2, items[j].itemnumb))
            Handle_Error("Add_Transactions(): ctdbSetFieldAsString()");
         if (ctdbFindRecord(hRecordItemMast, CTFIND_EQ))
            /* if not found, restore back to previous savepoint */
            ctdbRestoreSavePoint(hSession, savepoint);
         else
            /* set transaction savepoint */
            savepoint = ctdbSetSavePoint(hSession);

         /* bump to next item */
         j++;

         /* exit the while loop on last item */
         if (j >= nItems)
            break;
      }

      /* check that customer exists in CustomerMaster table */
      if ((retval = ctdbClearRecord(hRecordCustMast)) != CTDBRET_OK)
         Handle_Error("Add_Transactions(): ctdbClearRecord()");
      if (ctdbSetFieldAsString(hRecordCustMast, 0, orders[i].custnum))
         Handle_Error("Add_Transactions(): ctdbSetFieldAsString()");

      /* commit or abort the transaction */
      if (ctdbFindRecord(hRecordCustMast, CTFIND_EQ))
      {
         if (ctdbAbort(hSession))
            Handle_Error("Add_Transactions(): ctdbAbort()");
      }
      else
      {
         if (ctdbCommit(hSession))
            Handle_Error("Add_Transactions(): ctdbCommit()");
      }
   }
}


/*
 * Display_CustomerOrders()
 *
 * This function displays the contents of a table. ctdbFirstRecord() and
 * ctdbNextRecord() fetch the record. Then each field is parsed and displayed
 */

#ifdef PROTOTYPE
VOID Display_CustomerOrders(VOID)
#else
VOID Display_CustomerOrders()
#endif
{
   CTDBRET  retval;
   TEXT     custnumb[4+1];
   TEXT     ordrnumb[6+1];

   printf("\n\tCustomerOrder table...\n");

   /* read first record */
   retval = ctdbFirstRecord(hRecordCustOrdr);
   if (retval != CTDBRET_OK)
      Handle_Error("Display_CustomerOrders(): ctdbFirstRecord()");

   while (retval != END_OF_FILE)
   {
      retval = 0;
      retval |= ctdbGetFieldAsString(hRecordCustOrdr, 2, ordrnumb, sizeof(ordrnumb));
      retval |= ctdbGetFieldAsString(hRecordCustOrdr, 3, custnumb, sizeof(custnumb));
      if (retval)
         Handle_Error("Display_CustomerOrders(): ctdbGetFieldAsString()");

      printf("\t   %s   %s\n", ordrnumb, custnumb);

      /* read next record */
      retval = ctdbNextRecord(hRecordCustOrdr);
      if (retval == END_OF_FILE)
         break;   /* reached end of file */

      if (retval != CTDBRET_OK)
         Handle_Error("Display_CustomerOrders(): ctdbNextRecord()");
   }
}


/*
 * Display_OrderItems()
 *
 * This function displays the contents of a table. ctdbFirstRecord() and
 * ctdbNextRecord() fetch the record. Then each field is parsed and displayed
 */

#ifdef PROTOTYPE
VOID Display_OrderItems(VOID)
#else
VOID Display_OrderItems()
#endif
{
   CTDBRET  retval;
   TEXT     itemnumb[5+1];
   TEXT     ordrnumb[6+1];

   printf("\n\tOrderItems Table...\n");

   /* read first record */
   retval = ctdbFirstRecord(hRecordOrdrItem);
   if (retval != CTDBRET_OK)
      Handle_Error("Display_OrderItems(): ctdbFirstRecord()");

   while (retval != END_OF_FILE)
   {
      retval = 0;
      retval |= ctdbGetFieldAsString(hRecordOrdrItem, 2, ordrnumb, sizeof(ordrnumb));
      retval |= ctdbGetFieldAsString(hRecordOrdrItem, 3, itemnumb, sizeof(itemnumb));
      if (retval)
         Handle_Error("Display_OrderItems(): ctdbGetFieldAsString()");

      printf("\t   %s   %s\n", ordrnumb, itemnumb);

      /* read next record */
      retval = ctdbNextRecord(hRecordOrdrItem);
      if (retval == END_OF_FILE)
         break;   /* reached end of file */

      if (retval != CTDBRET_OK)
         Handle_Error("Display_OrderItems(): ctdbNextRecord()");
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

   ctdbFreeRecord(hRecordCustMast);
   ctdbFreeRecord(hRecordItemMast);
   ctdbFreeRecord(hRecordOrdrItem);
   ctdbFreeRecord(hRecordCustOrdr);

   ctdbFreeTable(hTableCustMast);
   ctdbFreeTable(hTableItemMast);
   ctdbFreeTable(hTableOrdrItem);
   ctdbFreeTable(hTableCustOrdr);

   ctdbFreeSession(hSession);
#ifndef ctPortAppleiOS
   getchar();
#endif
   exit(1);
}

/* end of ctdb_tutorial4.c */
