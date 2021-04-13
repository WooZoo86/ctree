/*
 * DSQL_Tutorial4.c
 *
 * Public domain Direct SQL example
 *
 * FairCom Corporation(www.faircom.com), 6300 West Sugar Creek Drive, Columbia, MO USA 65203
 *
 * The goal of this tutorial is to introduce the most basic Direct SQL API
 * to accomplish creating and manipulating a table through the ctreeServer
 *
 * Functionally, this application will perform the following:
 *  1.  Logon onto a session
 *  2.  Create 4 tables each with an index
 *  3.  Add records in multiple tables under transaction processing control
 *  4.  Display the contents of the tables
 */

/* Preprocessor definitions and includes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctsqlapi.h"


/* Global declarations */

pCTSQLCONN hConn;
pCTSQLCMD hCmd;


/* Function declarations */

void Initialize(void), Manage(void), Define(void), Done(void);
void Create_CustomerMaster_Table(void);
void Create_CustomerOrders_Table(void);
void Create_OrderItems_Table(void);
void Create_ItemMaster_Table(void);
void Delete_Tables(void);
void Add_CustomerMaster_Records(void), Add_ItemMaster_Records(void);
void Add_Transactions();
void Display_CustomerOrders(void), Display_OrderItems(void);
void Handle_Error(CTSQLCHAR*);


/*
 * main()
 *
 * The main() function implements the concept of "init, define, manage
 * and you're done..."
 */

int main(int argc, char* argv[])
{
   Initialize();

   Define();

   Manage();

   Done();

   printf("\nPress <ENTER> key to exit . . .\n");
   getchar();

   return(0);
}


/*
 * Initialize()
 *
 * Perform the minimum requirement of logging onto the c-tree Server
 */

void Initialize(void)
{
   CTSQLRET rc;

   printf("INIT\n");

   /* allocate connection handle */
   if ((hConn = ctsqlNewConnection()) == NULL)
      Handle_Error("ctsqlNewConnection()");

   /* allocate command handle */
   if ((hCmd = ctsqlNewCommand(hConn)) == NULL)
      Handle_Error("ctsqlNewCommand()");

   /* connect to server */
   printf("\tLogon to server...\n");
   if ((rc = ctsqlConnect(hConn, "6597@localhost:ctreeSQL", "admin", "ADMIN")) != CTSQLRET_OK)
      Handle_Error( "ctsqlConnect()");

   /* disable autocommit */
   if ((rc = ctsqlSetAutoCommit(hConn, CTSQL_FALSE)) != CTSQLRET_OK)
      Handle_Error( "ctsqlSetAutoCommit()");
}


/*
 * Define()
 *
 * Create the tables
 */

void Define(void)
{
   CTSQLRET rc;

   printf("DEFINE\n");

   /* delete tables... */
   Delete_Tables();
   /* ...and re-create them with constraints */
   Create_CustomerMaster_Table();
   Create_CustomerOrders_Table();
   Create_OrderItems_Table();
   Create_ItemMaster_Table();

   if ((rc = ctsqlCommit(hConn)) != CTSQLRET_OK)
      Handle_Error("ctsqlCommit()");
}


/*
 * Manage()
 *
 * Populates table and perform a simple query
 *
 */

void Manage(void)
{
   printf("MANAGE\n");

   /* populate the tables with data */
   Add_CustomerMaster_Records();
   Add_ItemMaster_Records();

   Add_Transactions();

   /* display the orders and their items */
   Display_CustomerOrders();
   Display_OrderItems();
}


/*
 * Done()
 *
 * This function handles the housekeeping of closing connection and
 * freeing of associated memory
 */

void Done(void)
{
   CTSQLRET rc;

   printf("DONE\n");

   /* re-enable autocommit */
   if ((rc = ctsqlSetAutoCommit(hConn, CTSQL_TRUE)) != CTSQLRET_OK)
      Handle_Error( "ctsqlSetAutoCommit()");

   Delete_Tables();

   /* disconnect from server */
   printf("\tLogout...\n");
   if ((rc = ctsqlDisconnect(hConn)) != CTSQLRET_OK)
      Handle_Error("ctsqlDisconnect()");

   /* free command handle */
   if (hCmd)
      ctsqlFreeCommand(hCmd);

   /* free connection handle */
   ctsqlFreeConnection(hConn);
}


/*
 * Delete_Tables()
 *
 * This function removes all existing tables
 */

void Delete_Tables(void)
{
   CTSQLRET rc;

   if ((rc = ctsqlExecuteDirect(hCmd, "DROP TABLE ordritem")) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(DROP TABLE)");
   if ((rc = ctsqlExecuteDirect(hCmd, "DROP TABLE custordr")) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(DROP TABLE)");
   if ((rc = ctsqlExecuteDirect(hCmd, "DROP TABLE custmast")) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(DROP TABLE)");
   if ((rc = ctsqlExecuteDirect(hCmd, "DROP TABLE itemmast")) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(DROP TABLE)");
}


/*
 * Create_CustomerMaster_Table()
 *
 * Create the table CustomerMaster
 */

void Create_CustomerMaster_Table(void)
{
   CTSQLRET rc;

   /* define table CustomerMaster */
   printf("\ttable CustomerMaster\n");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE TABLE custmast ( \
         cm_custnumb CHAR(4) PRIMARY KEY, \
         cm_custzipc CHAR(9), \
         cm_custstat CHAR(2), \
         cm_custrtng CHAR(1), \
         cm_custname VARCHAR(47), \
         cm_custaddr VARCHAR(47), \
         cm_custcity VARCHAR(47))"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");
}


/*
 * Create_CustomerOrders_Table()
 *
 * Create the table CustomerOrders
 */

void Create_CustomerOrders_Table(void)
{
   CTSQLRET rc;

   /* define table CustomerOrders */
   printf("\ttable CustomerOrders\n");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE TABLE custordr ( \
         co_ordrdate DATE, \
         co_promdate DATE, \
         co_ordrnumb CHAR(6) PRIMARY KEY, \
         co_custnumb CHAR(4), \
         FOREIGN KEY (co_custnumb) REFERENCES custmast)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");
}


/*
 * Create_OrderItems_Table()
 *
 * Create the table OrderItems
 */

void Create_OrderItems_Table(void)
{
   CTSQLRET rc;

   /* define table OrderItems */
   printf("\ttable OrderItems\n");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE TABLE ordritem ( \
         oi_sequnumb SMALLINT, \
         oi_quantity SMALLINT, \
         oi_ordrnumb CHAR(6), \
         oi_itemnumb CHAR(5), \
         FOREIGN KEY (oi_itemnumb) REFERENCES itemmast, \
         FOREIGN KEY (oi_ordrnumb) REFERENCES custordr)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");
}


/*
 * Create_ItemMaster_Table()
 *
 * Create the table ItemMaster
 */

void Create_ItemMaster_Table(void)
{
   CTSQLRET rc;

   /* define table ItemMaster */
   printf("\ttable ItemMaster\n");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE TABLE itemmast ( \
         im_itemwght INTEGER, \
         im_itempric MONEY, \
         im_itemnumb CHAR(5) PRIMARY KEY, \
         im_itemdesc VARCHAR(47))"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");
}




/*
 * Add_CustomerMaster_Records()
 *
 * This function adds records to table CustomerMaster from an
 * array of strings
 */

void Add_CustomerMaster_Records(void)
{
   CTSQLRET    rc;
   INTEGER     i;
   CTSQLCHAR   sCommand[512];
   CTSQLCHAR   *data[] = {
      "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
      "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
      "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
      "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
   };
   INTEGER     nRecords = sizeof(data) / sizeof(data[0]);

   printf("\tAdd records in table CustomerMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      ctsql_strcpy (sCommand, "INSERT INTO custmast VALUES ");
      ctsql_strcat (sCommand, data[i]);
      if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
         Handle_Error("ctsqlExecuteDirect(INSERT)");
   }

   if ((rc = ctsqlCommit(hConn)) != CTSQLRET_OK)
      Handle_Error("ctsqlCommit()");
}


/*
 * Add_ItemMaster_Records()
 *
 * This function adds records to table ItemMaster from an
 * array of strings
 */

void Add_ItemMaster_Records(void)
{
   CTSQLRET    rc;
   INTEGER     i;
   CTSQLCHAR   sCommand[512];
   CTSQLCHAR   *data[] = {
      "(10,19.95,'1','Hammer')",
      "(3,  9.99,'2','Wrench')",
      "(4, 16.59,'3','Saw')",
      "(1,  3.98,'4','Pliers')"
   };
   INTEGER     nRecords = sizeof(data) / sizeof(data[0]);

   printf("\tAdd records in table ItemMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      ctsql_strcpy (sCommand, "INSERT INTO itemmast VALUES ");
      ctsql_strcat (sCommand, data[i]);
      if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
         Handle_Error("ctsqlExecuteDirect(INSERT)");
   }

   if ((rc = ctsqlCommit(hConn)) != CTSQLRET_OK)
      Handle_Error("ctsqlCommit()");
}


/*
 * Add_Transactions()
 *
 * Add an Order and associated Items "as a transaction" to their
 * respective tables.  A transaction is committed or aborted if the
 * customer number on the order is confirmed valid.  Likewise each
 * item in the order is verified to be a valid item.
 */

void Add_Transactions(void)
{
   typedef struct {
      CTSQLCHAR       *ordrdate, *promdate, *ordrnumb, *custnumb;
   } ORDER_DATA;

   typedef struct {
      CTSQLCHAR      *ordrnumb;
      USMALLINT      sequnumb;
      USMALLINT      quantity;
      CTSQLCHAR      *itemnumb;
   } ORDERITEM_DATA;

   ORDER_DATA orders[] = {
      {"09/01/2002", "09/05/2002", "1", "1001"},
      {"09/02/2002", "09/06/2002", "2", "9999"},   /* bad customer number */
      {"09/22/2002", "09/26/2002", "3", "1003"}
   };
   INTEGER  nOrders = sizeof(orders) / sizeof(ORDER_DATA);

   ORDERITEM_DATA items[] = {
      {"1", 1, 2, "1"},
      {"1", 2, 1, "2"},
      {"2", 1, 1, "3"},
      {"2", 2, 3, "4"},
      {"3", 1, 2, "3"},
      {"3", 2, 2, "99"} /* bad item number */
   };
   INTEGER  nItems = sizeof(items) / sizeof(ORDERITEM_DATA);

   CTSQLRET    rc;
   INTEGER     i, j = 0;
   CTSQLCHAR   sCommand[512];

   printf("\tAdd transaction records... \n");

   for (i = 0; i < nOrders; i++)
   {
      /* add order record */
      sprintf(sCommand, "INSERT INTO custordr VALUES ('%s', '%s', '%s', '%s')",
         orders[i].ordrdate,
         orders[i].promdate,
         orders[i].ordrnumb,
         orders[i].custnumb);
      if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
         Handle_Error("ctsqlExecuteDirect(INSERT)");

      /* process order items */
      while (!(strcmp(items[j].ordrnumb, orders[i].ordrnumb)))
      {
         /* add item record */
         sprintf(sCommand, "INSERT INTO ordritem VALUES (%d, %d, '%s', '%s')",
            items[j].sequnumb,
            items[j].quantity,
            items[j].ordrnumb,
            items[j].itemnumb);
         if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
            Handle_Error("ctsqlExecuteDirect(INSERT)");

         /* bump to next item */
         j++;

         /* exit the while loop on last item */
         if (j >= nItems)
            break;
      }

      /* commit the transaction */
      if ((rc = ctsqlCommit(hConn)) != CTSQLRET_OK)
         Handle_Error("ctsqlCommit()");
   }
}


/*
 * Display_CustomerOrders()
 *
 * This function displays the contents of CustomerOrders table
 */

void Display_CustomerOrders(void)
{
   CTSQLRET       rc;
   CTSQLCHAR      ordrnumb[6+1], custnumb[4+1];
   pCTSQLCURSOR   hCursor = NULL;

   printf("\n\tCustomerOrders Table...\n");

   rc = ctsqlPrepare(hCmd, "SELECT * FROM custordr");
   if (rc != CTSQLRET_OK)
      Handle_Error("ctsqlPrepare(SELECT)");

   rc = ctsqlExecute(hCmd, &hCursor);
   if (rc != CTSQLRET_OK)
      Handle_Error("ctsqlExecute(SELECT)");

   /* fetch and display each individual record */
   while ((rc = ctsqlNext(hCursor)) == CTSQLRET_OK)
   {
      ctsqlGetChar(hCursor, 2, ordrnumb);
      ctsqlGetChar(hCursor, 3, custnumb);

      printf("\t   %s   %s\n", ordrnumb, custnumb);
   }

   ctsqlFreeCursor(hCursor);
}


/*
 * Display_OrderItems()
 *
 * This function displays the contents of OrderItems table
 */

void Display_OrderItems(void)
{
   CTSQLRET       rc;
   CTSQLCHAR      ordrnumb[6+1], itemnumb[5+1];
   pCTSQLCURSOR   hCursor = NULL;

   printf("\n\tOrderItems Table...\n");

   rc = ctsqlPrepare(hCmd, "SELECT * FROM ordritem");
   if (rc != CTSQLRET_OK)
      Handle_Error("ctsqlPrepare(SELECT)");

   rc = ctsqlExecute(hCmd, &hCursor);
   if (rc != CTSQLRET_OK)
      Handle_Error("ctsqlExecute(SELECT)");

   /* fetch and display each individual record */
   while ((rc = ctsqlNext(hCursor)) == CTSQLRET_OK)
   {
      ctsqlGetChar(hCursor, 2, ordrnumb);
      ctsqlGetChar(hCursor, 3, itemnumb);

      printf("\t   %s   %s\n", ordrnumb, itemnumb);
   }

   ctsqlFreeCursor(hCursor);
}


/*
 * Handle_Error()
 *
 * General error routine that retrieves and displays specific SQL Error
 * before exiting the tutorial.  If the error returned indicates an object
 * already exists, execution is returned to the calling function.
 */

void Handle_Error(CTSQLCHAR* sErrMsg)
{
   CTSQLRET rc;

   const INTEGER  TABLE_NOT_FOUND = -20005;
   const INTEGER  CONSTRAINT_VIOLATION = -20116;

   if (!hConn) {
      printf("%s - SQL ERROR: %s\n", sErrMsg, "Out of memory");
   } else {
      rc = ctsqlGetError (hConn);
      if (rc == TABLE_NOT_FOUND || rc == CONSTRAINT_VIOLATION)
         return;
   
      printf("%s - SQL ERROR: [%d] - %s\n", sErrMsg, rc, ctsqlGetErrorMessage(hConn));

      if (rc == -20212)
         printf("Perhaps your c-tree server is not running?\n");
   }
   printf("*** Execution aborted *** \nPress <ENTER> key to exit...");
   getchar();

   exit(1);
}

/* end of DSQL_Tutorial4.c */
