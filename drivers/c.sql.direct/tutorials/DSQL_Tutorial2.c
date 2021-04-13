/*
 * DSQL_Tutorial2.c
 *
 * Public domain Direct SQL example
 *
 * FairCom Corporation(www.faircom.com), 6300 West Sugar Creek Drive, Columbia, MO USA 65203
 *
 * The goal of this tutorial is to introduce the most basic Direct SQL API
 * to accomplish creating and manipulating a table through the ctreeServer
 *
 * Functionally, this application will perform the following:
 *  1.  Create a database
 *  2.  Create 4 tables each with an index
 *  3.  Populate each table with a few records
 *  4.  Build a query utilizing the advantage of indexes
 *  5.  Output the results of the query
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
void Delete_Records(CTSQLCHAR*);
void Add_CustomerMaster_Records(void);
void Add_CustomerOrders_Records(void);
void Add_OrderItems_Records(void);
void Add_ItemMaster_Records(void);
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

   /* enable autocommit */
   if ((rc = ctsqlSetAutoCommit(hConn, CTSQL_TRUE)) != CTSQLRET_OK)
      Handle_Error( "ctsqlSetAutoCommit()");
}


/*
 * Define()
 *
 * Create the tables
 */

void Define(void)
{
   printf("DEFINE\n");

   ctsqlExecuteDirect(hCmd, "DROP TABLE ordritem");
   ctsqlExecuteDirect(hCmd, "DROP TABLE custordr");
   ctsqlExecuteDirect(hCmd, "DROP TABLE custmast");
   ctsqlExecuteDirect(hCmd, "DROP TABLE itemmast");

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

void Manage(void)
{
   CTSQLRET       rc;
   CTSQLCHAR      custname[47+1];
   NUMERIC        ntotal;
   SMALLFLOAT     ftotal;
   pCTSQLCURSOR   hCursor = NULL;

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

   if ((rc = ctsqlPrepare(hCmd,
         "SELECT cm_custname, SUM(im_itempric * oi_quantity) "
         "FROM custmast, custordr, ordritem, itemmast "
         "WHERE co_custnumb = cm_custnumb AND co_ordrnumb = oi_ordrnumb AND oi_itemnumb = im_itemnumb "
         "GROUP BY co_ordrnumb, cm_custname"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlPrepare(SELECT)");

   if ((rc = ctsqlExecute(hCmd, &hCursor)) != CTSQLRET_OK)
      Handle_Error("ctsqlExecute(SELECT)");

   /* for each order in the CustomerOrders table */
   while ((rc = ctsqlNext(hCursor)) == CTSQLRET_OK)
   {
      if ((rc = ctsqlGetChar(hCursor, 0, custname)) != CTSQLRET_OK)
         Handle_Error("ctsqlGetChar()");
      if ((rc = ctsqlGetMoney(hCursor, 1, &ntotal)) != CTSQLRET_OK)
         Handle_Error("ctsqlGetReal()");
      if ((rc = ctsqlConvert(CTSQL_MONEY, &ntotal, sizeof(ntotal),
         NULL, CTSQL_REAL, &ftotal, sizeof(ftotal))) != CTSQLRET_OK)
         Handle_Error("ctsqlConvert()");

      /* output data to stdout */
      printf("\t\t%-20s %.2f\n", custname, ftotal);
   }

   ctsqlFreeCursor(hCursor);
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
 * Create_CustomerMaster_Table()
 *
 * Create the CustomerMaster
 */

void Create_CustomerMaster_Table(void)
{
   CTSQLRET rc;

   /* define table CustomerMaster */
   printf("\ttable CustomerMaster\n");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE TABLE custmast ( \
         cm_custnumb CHAR(4), \
         cm_custzipc CHAR(9), \
         cm_custstat CHAR(2), \
         cm_custrtng CHAR(1), \
         cm_custname VARCHAR(47), \
         cm_custaddr VARCHAR(47), \
         cm_custcity VARCHAR(47))"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE UNIQUE INDEX cm_custnumb_idx ON custmast (cm_custnumb)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE INDEX)");
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
         co_ordrnumb CHAR(6), \
         co_custnumb CHAR(4))"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE UNIQUE INDEX co_ordrnumb_idx ON custordr (co_ordrnumb)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE INDEX)");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE INDEX co_custnumb_idx ON custordr (co_custnumb)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE INDEX)");
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
         oi_itemnumb CHAR(5))"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE UNIQUE INDEX oi_ordrnumb_idx ON ordritem (oi_ordrnumb, oi_sequnumb)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE INDEX)");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE INDEX)");
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
         im_itemnumb CHAR(5), \
         im_itemdesc VARCHAR(47))"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE TABLE)");

   if ((rc = ctsqlExecuteDirect(hCmd,
      "CREATE UNIQUE INDEX im_itemnumb_idx ON itemmast (im_itemnumb)"
      )) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(CREATE INDEX)");
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

   Delete_Records("custmast");

   printf("\tAdd records in table CustomerMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      ctsql_strcpy (sCommand, "INSERT INTO custmast VALUES ");
      ctsql_strcat (sCommand, data[i]);
      if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
         Handle_Error("ctsqlExecuteDirect(INSERT)");
   }
}


/*
 * Add_CustomerOrders_Records()
 *
 * This function adds records to table CustomerOrders from an
 * array of strings
 */

void Add_CustomerOrders_Records(void)
{
   CTSQLRET    rc;
   INTEGER     i;
   CTSQLCHAR   sCommand[512];
   CTSQLCHAR   *data[] = {
      "('09/01/2002','09/05/2002','1','1001')",
      "('09/02/2002','09/06/2002','2','1002')"
   };
   INTEGER     nRecords = sizeof(data) / sizeof(data[0]);

   Delete_Records("custordr");

   printf("\tAdd records in table CustomerOrders...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      ctsql_strcpy (sCommand, "INSERT INTO custordr VALUES ");
      ctsql_strcat (sCommand, data[i]);
      if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
         Handle_Error("ctsqlExecuteDirect(INSERT)");
   }
}


/*
 * Add_OrderItems_Records()
 *
 * This function adds records to table OrderItems from an
 * array of strings
 */

void Add_OrderItems_Records(void)
{
   CTSQLRET    rc;
   INTEGER     i;
   CTSQLCHAR   sCommand[512];
   CTSQLCHAR   *data[] = {
      "(1,2,'1','1')",
      "(2,1,'1','2')",
      "(3,1,'1','3')",
      "(1,3,'2','3')"
   };
   INTEGER     nRecords = sizeof(data) / sizeof(data[0]);

   Delete_Records("ordritem");

   printf("\tAdd records in table OrderItems...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      ctsql_strcpy (sCommand, "INSERT INTO ordritem VALUES ");
      ctsql_strcat (sCommand, data[i]);
      if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
         Handle_Error("ctsqlExecuteDirect(INSERT)");
   }
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

   Delete_Records("itemmast");

   printf("\tAdd records in table ItemMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      ctsql_strcpy (sCommand, "INSERT INTO itemmast VALUES ");
      ctsql_strcat (sCommand, data[i]);
      if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
         Handle_Error("ctsqlExecuteDirect(INSERT)");
   }
}


/*
 * Delete_Records()
 *
 * This function deletes all the records in a tables
 */

void Delete_Records(CTSQLCHAR* table)
{
   CTSQLRET    rc;
   CTSQLCHAR   sCommand[512];

   printf("\tDelete records...\n");

   sprintf (sCommand, "DELETE FROM %s", table);
   if ((rc = ctsqlExecuteDirect(hCmd, sCommand)) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(DELETE)");
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

   const INTEGER  TABLE_ALREADY_EXISTS = -20041;
   const INTEGER  INDEX_ALREADY_EXISTS = -20028;

   if (!hConn) {
      printf("%s - SQL ERROR: %s\n", sErrMsg, "Out of memory");
   } else {
      rc = ctsqlGetError (hConn);
      if (rc == TABLE_ALREADY_EXISTS || rc == INDEX_ALREADY_EXISTS)
         return;
   
      printf("%s - SQL ERROR: [%d] - %s\n", sErrMsg, rc, ctsqlGetErrorMessage(hConn));

      if (rc == -20212)
         printf("Perhaps your c-tree server is not running?\n");
   }
   printf("*** Execution aborted *** \nPress <ENTER> key to exit...");
   getchar();

   exit(1);
}

/* end of DSQL_Tutorial2.c */
