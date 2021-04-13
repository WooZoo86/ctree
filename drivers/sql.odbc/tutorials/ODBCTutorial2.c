/*
 * ODBCTutorial2.c
 *
 * Public domain ODBC example
 *
 * FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
 *
 * The goal of this tutorial is to introduce the most basic ODBC API
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

#ifndef DH_OS_UNIX
#include "windows.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "sqlext.h"
#ifndef DH_OS_UNIX
#include "conio.h"
#endif

#ifdef DH_OS_UNIX
#define MY_DSN "6597@localhost:ctreeSQL"   /* ODBC DSN used this tutorial */
#else
#define MY_DSN "FairCom ODBC Driver"   /* ODBC DSN used this tutorial */
#endif


/* Global declarations */

HENV  hEnv;
HDBC  hDbc;
HSTMT hStmt;


/* Function declarations */

void Initialize(void), Manage(void), Define(void), Done(void);
void Create_CustomerMaster_Table(void);
void Create_CustomerOrders_Table(void);
void Create_OrderItems_Table(void);
void Create_ItemMaster_Table(void);
void Delete_Records(SQLTCHAR*);
void Add_CustomerMaster_Records(void);
void Add_CustomerOrders_Records(void);
void Add_OrderItems_Records(void);
void Add_ItemMaster_Records(void);
void Handle_Error(SQLSMALLINT, SQLHANDLE, UCHAR*);


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
   RETCODE  rc;

   printf("INIT\n");

   /* allocate environment handle */
   if ((rc = SQLAllocEnv(&hEnv)) != SQL_SUCCESS)
      Handle_Error(0, NULL, "SQLAllocEnv()");

   /* allocate connection handle */
   if ((rc = SQLAllocConnect(hEnv, &hDbc)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_ENV, hEnv, "SQLAllocConnect()");

   /* connect to server */
   printf("\tLogon to server...\n");
   if ((rc = SQLConnect(hDbc, MY_DSN, SQL_NTS, "ADMIN", SQL_NTS, "ADMIN", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_DBC, hDbc, "SQLConnect()");

   /* allocate statement handle */
   if ((rc = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_DBC, hDbc, "SQLAllocHandle(SQL_HANDLE_STMT)");
}


/*
 * Define()
 *
 * Create the tables
 */

void Define(void)
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

void Manage(void)
{
   RETCODE  rc;
   SQLTCHAR custname[47+1];
   SQLREAL  total;
   SQLLEN   cbData;

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

   if ((rc = SQLExecDirect(hStmt,
         "SELECT cm_custname, SUM(im_itempric * oi_quantity) "
         "FROM custmast, custordr, ordritem, itemmast "
         "WHERE co_custnumb = cm_custnumb AND co_ordrnumb = oi_ordrnumb AND oi_itemnumb = im_itemnumb "
         "GROUP BY co_ordrnumb, cm_custname",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(SELECT)");

   /* for each order in the CustomerOrders table */
   while ((rc = SQLFetch(hStmt)) == SQL_SUCCESS)
   {
      if ((rc = SQLGetData(hStmt, 1, SQL_C_CHAR, custname, sizeof(custname), &cbData)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLGetData()");
      if ((rc = SQLGetData(hStmt, 2, SQL_C_FLOAT, &total, sizeof(total), &cbData)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLGetData()");
      /* output data to stdout */
      printf("\t\t%-20s %.2f\n", custname, total);
   }

   SQLFreeStmt(hStmt, SQL_CLOSE);
}


/*
 * Done()
 *
 * This function handles the housekeeping of closing connection and
 * freeing of associated memory
 */

void Done(void)
{
   RETCODE  rc;

   printf("DONE\n");

   /* free statement handle */
   if ((rc = SQLFreeHandle(SQL_HANDLE_STMT, hStmt)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_DBC, hDbc, "SQLFreeHandle(SQL_HANDLE_STMT)");

   /* disconnect from server */
   printf("\tLogout...\n");
   if ((rc = SQLDisconnect(hDbc)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_DBC, hDbc, "SQLDisconnect()");

   /* free connection handle */
   if ((rc = SQLFreeHandle(SQL_HANDLE_DBC, hDbc)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_ENV, hEnv, "SQLFreeHandle(SQL_HANDLE_DBC)");

   /* free environment handle */
   if ((rc = SQLFreeHandle(SQL_HANDLE_ENV, hEnv)) != SQL_SUCCESS)
      Handle_Error(0, NULL, "SQLFreeHandle(SQL_HANDLE_ENV)");
}


/*
 * Create_CustomerMaster_Table()
 *
 * Create the CustomerMaster
 */

void Create_CustomerMaster_Table(void)
{
   RETCODE  rc;

   /* define table CustomerMaster */
   printf("\ttable CustomerMaster\n");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE TABLE custmast ( \
         cm_custnumb CHAR(4), \
         cm_custzipc CHAR(9), \
         cm_custstat CHAR(2), \
         cm_custrtng CHAR(1), \
         cm_custname VARCHAR(47), \
         cm_custaddr VARCHAR(47), \
         cm_custcity VARCHAR(47))",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE UNIQUE INDEX cm_custnumb_idx ON custmast (cm_custnumb)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE INDEX)");
}


/*
 * Create_CustomerOrders_Table()
 *
 * Create the table CustomerOrders
 */

void Create_CustomerOrders_Table(void)
{
   RETCODE  rc;

   /* define table CustomerOrders */
   printf("\ttable CustomerOrders\n");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE TABLE custordr ( \
         co_ordrdate DATE, \
         co_promdate DATE, \
         co_ordrnumb CHAR(6), \
         co_custnumb CHAR(4))",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE UNIQUE INDEX co_ordrnumb_idx ON custordr (co_ordrnumb)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE INDEX)");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE INDEX co_custnumb_idx ON custordr (co_custnumb)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE INDEX)");
}


/*
 * Create_OrderItems_Table()
 *
 * Create the table OrderItems
 */

void Create_OrderItems_Table(void)
{
   RETCODE  rc;

   /* define table OrderItems */
   printf("\ttable OrderItems\n");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE TABLE ordritem ( \
         oi_sequnumb SMALLINT, \
         oi_quantity SMALLINT, \
         oi_ordrnumb CHAR(6), \
         oi_itemnumb CHAR(5))",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE UNIQUE INDEX oi_ordrnumb_idx ON ordritem (oi_ordrnumb, oi_sequnumb)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE INDEX)");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE INDEX)");
}


/*
 * Create_ItemMaster_Table()
 *
 * Create the table ItemMaster
 */

void Create_ItemMaster_Table(void)
{
   RETCODE  rc;

   /* define table ItemMaster */
   printf("\ttable ItemMaster\n");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE TABLE itemmast ( \
         im_itemwght INTEGER, \
         im_itempric MONEY, \
         im_itemnumb CHAR(5), \
         im_itemdesc VARCHAR(47))",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE UNIQUE INDEX im_itemnumb_idx ON itemmast (im_itemnumb)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE INDEX)");
}


/*
 * Add_CustomerMaster_Records()
 *
 * This function adds records to table CustomerMaster from an
 * array of strings
 */

void Add_CustomerMaster_Records(void)
{
   RETCODE     rc;
   SQLINTEGER  i;
   SQLTCHAR    sCommand[512];
   SQLTCHAR    *data[] = {
      "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
      "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
      "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
      "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
   };
   SQLINTEGER  nRecords = sizeof(data) / sizeof(data[0]);

   Delete_Records("custmast");

   printf("\tAdd records in table CustomerMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      strcpy (sCommand, "INSERT INTO custmast VALUES ");
      strcat (sCommand, data[i]);
      if ((rc = SQLExecDirect(hStmt, sCommand ,SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");
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
   RETCODE     rc;
   SQLINTEGER  i;
   SQLTCHAR    sCommand[512];
   SQLTCHAR    *data[] = {
      "('09/01/2002','09/05/2002','1','1001')",
      "('09/02/2002','09/06/2002','2','1002')"
   };
   SQLINTEGER  nRecords = sizeof(data) / sizeof(data[0]);

   Delete_Records("custordr");

   printf("\tAdd records in table CustomerOrders...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      strcpy (sCommand, "INSERT INTO custordr VALUES ");
      strcat (sCommand, data[i]);
      if ((rc = SQLExecDirect(hStmt, sCommand ,SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");
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
   RETCODE     rc;
   SQLINTEGER  i;
   SQLTCHAR    sCommand[512];
   SQLTCHAR    *data[] = {
      "(1,2,'1','1')",
      "(2,1,'1','2')",
      "(3,1,'1','3')",
      "(1,3,'2','3')"
   };
   SQLINTEGER  nRecords = sizeof(data) / sizeof(data[0]);

   Delete_Records("ordritem");

   printf("\tAdd records in table OrderItems...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      strcpy (sCommand, "INSERT INTO ordritem VALUES ");
      strcat (sCommand, data[i]);
      if ((rc = SQLExecDirect(hStmt, sCommand ,SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");
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
   RETCODE     rc;
   SQLINTEGER  i;
   SQLTCHAR    sCommand[512];
   SQLTCHAR    *data[] = {
      "(10,19.95,'1','Hammer')",
      "(3,  9.99,'2','Wrench')",
      "(4, 16.59,'3','Saw')",
      "(1,  3.98,'4','Pliers')"
   };
   SQLINTEGER  nRecords = sizeof(data) / sizeof(data[0]);

   Delete_Records("itemmast");

   printf("\tAdd records in table ItemMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      strcpy (sCommand, "INSERT INTO itemmast VALUES ");
      strcat (sCommand, data[i]);
      if ((rc = SQLExecDirect(hStmt, sCommand ,SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");
   }
}


/*
 * Delete_Records()
 *
 * This function deletes all the records in a tables
 */

void Delete_Records(SQLTCHAR* table)
{
   RETCODE  rc;
   SQLTCHAR sCommand[512];

   printf("\tDelete records...\n");

   sprintf (sCommand, "DELETE FROM %s", table);
   if ((rc = SQLExecDirect(hStmt, sCommand, SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(DELETE)");
}


/*
 * Handle_Error()
 *
 * General error routine that retrieves and displays specific SQL Error
 * before exiting the tutorial.  If the error returned indicates an object
 * already exists, execution is returned to the calling function.
 */

void Handle_Error(SQLSMALLINT HandleType, SQLHANDLE Handle, UCHAR* sErrMsg)
{
   SQLINTEGER  sdwNative;
   SQLSMALLINT swMsgLen, i;
   SQLTCHAR    szState[6];
   SQLTCHAR    szMsg[SQL_MAX_MESSAGE_LENGTH];

   const SQLINTEGER  TABLE_ALREADY_EXISTS = -20041;
   const SQLINTEGER  INDEX_ALREADY_EXISTS = -20028;
   const SQLINTEGER  CANNOT_CONNECT = -20212;

   if (!HandleType) {
      printf("%s - SQL ERROR: %s\n", sErrMsg, "Out of memory");
   } else {
      i = 1;
      while (SQLGetDiagRec(HandleType, Handle, i++, szState, &sdwNative,
            szMsg, sizeof(szMsg), &swMsgLen) != SQL_NO_DATA) {
   
         if (sdwNative == TABLE_ALREADY_EXISTS ||
            sdwNative == INDEX_ALREADY_EXISTS)
            return;
   
         printf("%s - SQL ERROR: [%d] - %s\n", sErrMsg, sdwNative, szMsg);

         if (sdwNative == CANNOT_CONNECT)
            printf("Perhaps your c-tree server is not running?\n");
      }
   }
   printf("*** Execution aborted *** \nPress <ENTER> key to exit...");
   getchar();

   exit(1);
}

/* end of ODBCTutorial2.c */
