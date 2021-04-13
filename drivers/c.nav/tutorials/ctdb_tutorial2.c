/*
 * ctdb_tutorial2.c
 *
 * Public domain c-treeDB C example
 *
 * FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
 * FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203
 *
 * The goal of this tutorial is to introduce the most basic CTDB API
 * to accomplish creating and manipulating a table through the ctreeServer
 *
 * Functionally, this application will perform the following:
 *  1.  Create a database
 *  2.  Create 4 tables each with an index
 *  3.  Populate each table with a few records
 *  4.  Build a query utilizing the advantage of indexes
 *  5.  Output the results of the query
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
VOID Add_CustomerOrders_Records(VOID), Add_OrderItems_Records(VOID);
VOID Delete_Records(CTHANDLE hRecord);
VOID Check_Table_Mode(CTHANDLE hTable);

VOID Handle_Error(CTSTRING);
#else
VOID Initialize(), Define(), Manage(), Done();

VOID Create_CustomerMaster_Table(), Create_ItemMaster_Table();
VOID Create_OrderItems_Table(), Create_CustomerOrders_Table();

VOID Add_CustomerMaster_Records(), Add_ItemMaster_Records();
VOID Add_CustomerOrders_Records(), Add_OrderItems_Records();
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
   Initialize();

   Define();

   Manage();

   Done();

#ifndef ctPortAppleiOS
   printf("\nPress <ENTER> key to exit . . .\n");
   getchar();
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
   CTDBRET  retval;
   CTSIGNED quantity;
   CTFLOAT  price, total;
   TEXT     itemnumb[5+1], custnumb[4+1], ordrnumb[6+1], custname[47+1];
   CTBOOL   isOrderFound, isItemFound;

   printf("MANAGE\n");

   /* populate the tables with data */
   Add_CustomerMaster_Records();
   Add_CustomerOrders_Records();
   Add_OrderItems_Records();
   Add_ItemMaster_Records();

   /* perform a query:
      list customer name and total amount per order

      name               total
      @@@@@@@@@@@@@      $xx.xx

      for each order in the CustomerOrders table
         fetch order number
         fetch customer number
         fetch name from CustomerMaster table based on customer number
         for each order item in OrderItems table
            fetch item quantity
            fetch item number
            fetch item price from ItemMaster table based on item number
         next
      next
   */
   printf("\n\tQuery Results\n");

   /* get the first order */
   if (ctdbFirstRecord(hRecordCustOrdr))
      Handle_Error("Manage(): ctdbFirstRecord()");

   isOrderFound = YES;
   while (isOrderFound)   /* for each order in the CustomerOrders table */
   {
      /* fetch order number */
      retval = ctdbGetFieldAsString(hRecordCustOrdr, 2, ordrnumb, sizeof(ordrnumb));
      /* fetch customer number */
      retval |= ctdbGetFieldAsString(hRecordCustOrdr, 3, custnumb, sizeof(custnumb));
      if (retval)
         Handle_Error("Manage(): ctdbGetFieldAsString()");

      /* fetch name from CustomerMaster table based on customer number */
      if (ctdbClearRecord(hRecordCustMast))
         Handle_Error("Manage(): ctdbClearRecord()");
      if (ctdbSetFieldAsString(hRecordCustMast, 0, custnumb))
         Handle_Error("Manage(): ctdbSetFieldAsString()");
      if (ctdbFindRecord(hRecordCustMast, CTFIND_EQ))
         Handle_Error("Manage(): ctdbFindRecord()");
      if (ctdbGetFieldAsString(hRecordCustMast, 4, custname, sizeof(custname)))
         Handle_Error("Manage(): ctdbGetFieldAsString()");

      /* fetch item price from OrderItems table */
      if (ctdbClearRecord(hRecordOrdrItem))
         Handle_Error("Manage(): ctdbClearRecord()");
      if (ctdbSetFieldAsString(hRecordOrdrItem, 2, ordrnumb))
         Handle_Error("Manage(): ctdbSetFieldAsString()");
      /* define a recordset to scan only items applicable to this order */
      if (ctdbRecordSetOn(hRecordOrdrItem, 6))
         Handle_Error("Manage(): ctdbRecordSetOn()");
      if (ctdbFirstRecord(hRecordOrdrItem))
         Handle_Error("Manage(): ctdbFirstRecord()");
      isItemFound = YES;

      total = 0;
      while (isItemFound)   /* for each order item in OrderItems table */
      {
         /* fetch item quantity */
         if (ctdbGetFieldAsSigned(hRecordOrdrItem, 1, &quantity))
            Handle_Error("Manage(): ctdbGetFieldAsSigned()");
         /* fetch item number */
         if (ctdbGetFieldAsString(hRecordOrdrItem, 3, itemnumb, sizeof(itemnumb)))
            Handle_Error("Manage(): ctdbGetFieldAsString()");

         /* fetch item price from ItemMaster table based on item number */
         if (ctdbClearRecord(hRecordItemMast))
            Handle_Error("Manage(): ctdbClearRecord()");
         if (ctdbSetFieldAsString(hRecordItemMast, 2, itemnumb))
            Handle_Error("Manage(): ctdbSetFieldAsString()");
         if (ctdbFindRecord(hRecordItemMast, CTFIND_EQ))
            Handle_Error("Manage(): ctdbFindRecord()");
         if (ctdbGetFieldAsFloat(hRecordItemMast, 1, &price))
            Handle_Error("Manage(): ctdbGetFieldAsFloat()");

         /* calculate order total */
         total += (price * quantity);

         /* read next record */
         retval = ctdbNextRecord(hRecordOrdrItem);
         if (retval != CTDBRET_OK)
         {
            if (retval == END_OF_FILE)
               isItemFound = NO;
            else
                 Handle_Error("Manage(): ctdbNextRecord()");
         }
      }

      ctdbRecordSetOff(hRecordOrdrItem);

      /* output data to stdout */
      printf("\t\t%-20s %.2f\n", custname, total);

      /* read next order */
      retval = ctdbNextRecord(hRecordCustOrdr);
      if (retval != CTDBRET_OK)
      {
         if (retval == END_OF_FILE)
            isOrderFound = NO;
         else
            Handle_Error("Manage(): ctdbNextRecord()");
      }
   }
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
      if (ctdbCreateTable(hTableCustMast, "custmast", CTCREATE_NORMAL))
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
      if (ctdbCreateTable(hTableCustOrdr, "custordr", CTCREATE_NORMAL))
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
      if (ctdbCreateTable(hTableOrdrItem, "ordritem", CTCREATE_NORMAL))
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
      if (ctdbCreateTable(hTableItemMast, "itemmast", CTCREATE_NORMAL))
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

   if ((hRecordCustMast = ctdbAllocRecord(hTableCustMast)) == NULL)
      Handle_Error("Add_Customer_Records(): ctdbAllocRecord()");

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
 * Add_CustomerOrders_Records()
 *
 * This function adds records to table CustomerOrders from an
 * array of strings
 */

typedef struct {
   CTSTRING orderdate, promisedate, ordernum, customernum;
} ORDER_DATA;

ORDER_DATA data1[] = {
   {"09/01/2002", "09/05/2002",  "1",  "1001"},
   {"09/02/2002", "09/06/2002",  "2",  "1002"}
};

#ifdef PROTOTYPE
VOID Add_CustomerOrders_Records(VOID)
#else
VOID Add_CustomerOrders_Records()
#endif
{
   CTDBRET  retval;
   CTSIGNED i;
   CTSIGNED nRecords = sizeof(data1) / sizeof(ORDER_DATA);
   CTDATE   orderdate;
   CTDATE   promisedate;


   if ((hRecordCustOrdr = ctdbAllocRecord(hTableCustOrdr)) == NULL)
      Handle_Error("Add_CustomerOrders_Records(): ctdbAllocRecord()");

   Delete_Records(hRecordCustOrdr);

   printf("\tAdd records in table CustomerOrders...\n");

   /* add records to table */
   for (i = 0; i < nRecords; i++)
   {
      /* clear record buffer */
      ctdbClearRecord(hRecordCustOrdr);

      retval = 0;
      retval |= ctdbStringToDate(data1[i].orderdate, CTDATE_MDCY ,&orderdate);
      retval |= ctdbStringToDate(data1[i].promisedate, CTDATE_MDCY, &promisedate);
      /* populate record buffer with data */
      retval |= ctdbSetFieldAsDate(hRecordCustOrdr, 0, orderdate);
      retval |= ctdbSetFieldAsDate(hRecordCustOrdr, 1, promisedate);
      retval |= ctdbSetFieldAsString(hRecordCustOrdr, 2, data1[i].ordernum);
      retval |= ctdbSetFieldAsString(hRecordCustOrdr, 3, data1[i].customernum);

      if (retval)
         Handle_Error("Add_CustomerOrders_Records(): ctdbSetFieldAsString()|ctdbSetFieldAsDate()");

      /* add record */
      if (ctdbWriteRecord(hRecordCustOrdr))
         Handle_Error("Add_CustomerOrders_Records(): ctdbWriteRecord()");
   }
}


/*
 * Add_OrderItems_Records()
 *
 * This function adds records to table OrderItems from an
 * array of strings
 */

typedef struct {
   COUNT sequencenum, quantity;
   CTSTRING ordernum, itemnum;
} ORDERITEM_DATA;

ORDERITEM_DATA data2[] = {
   {1,   2, "1",  "1"},
   {2,   1, "1",  "2"},
   {3,   1, "1",  "3"},
   {1,   3, "2",  "3"}
};

#ifdef PROTOTYPE
VOID Add_OrderItems_Records(VOID)
#else
VOID Add_OrderItems_Records()
#endif
{
   CTDBRET  retval;
   CTSIGNED i;
   CTSIGNED nRecords = sizeof(data2) / sizeof(ORDERITEM_DATA);

   if ((hRecordOrdrItem = ctdbAllocRecord(hTableOrdrItem)) == NULL)
      Handle_Error("Add_OrderItems_Records(): ctdbAllocRecord()");

   Delete_Records(hRecordOrdrItem);

   printf("\tAdd records in table OrderItems...\n");

   /* add records to table */
   for (i = 0; i < nRecords; i++)
   {
      /* clear record buffer */
      ctdbClearRecord(hRecordOrdrItem);

      retval = 0;
      /* populate record buffer with data */
      retval |= ctdbSetFieldAsSigned(hRecordOrdrItem, 0, data2[i].sequencenum);
      retval |= ctdbSetFieldAsSigned(hRecordOrdrItem, 1, data2[i].quantity);
      retval |= ctdbSetFieldAsString(hRecordOrdrItem, 2, data2[i].ordernum);
      retval |= ctdbSetFieldAsString(hRecordOrdrItem, 3, data2[i].itemnum);

      if(retval)
         Handle_Error("Add_OrderItems_Records(): ctdbSetFieldAsString()");

      /* add record */
      if (ctdbWriteRecord(hRecordOrdrItem))
         Handle_Error("Add_OrderItems_Records(): ctdbWriteRecord()");
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

   if ((hRecordItemMast = ctdbAllocRecord(hTableItemMast)) == NULL)
      Handle_Error("Add_ItemMaster_Records(): ctdbAllocRecord()");

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

/* end of ctdb_tutorial2.c */
