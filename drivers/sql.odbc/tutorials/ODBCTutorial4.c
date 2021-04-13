/*
 * ODBCTutorial4.c
 *
 * Public domain ODBC example
 *
 * FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
 *
 * The goal of this tutorial is to introduce the most basic ODBC API
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
void Delete_Tables(void);
void Add_CustomerMaster_Records(void), Add_ItemMaster_Records(void);
void Add_Transactions();
void Display_CustomerOrders(void), Display_OrderItems(void);
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

   /* disable commit after each single SQL statement */
   if ((rc = SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, 0)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_DBC, hDbc, "SQLSetConnectAttr(SQL_AUTOCOMMIT_OFF)");

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
   RETCODE  rc;

   printf("DEFINE\n");

   /* delete tables... */
   Delete_Tables();
   /* ...and re-create them with constraints */
   Create_CustomerMaster_Table();
   Create_ItemMaster_Table();
   Create_CustomerOrders_Table();
   Create_OrderItems_Table();

   if ((rc = SQLExecDirect(hStmt, "COMMIT WORK", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(COMMIT WORK)");
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
   RETCODE  rc;

   printf("DONE\n");

   /* re-enable autocommit */
   if ((rc = SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (void *)SQL_AUTOCOMMIT_ON, 0)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_DBC, hDbc, "SQLSetConnectAttr(SQL_AUTOCOMMIT_ON)");

   Delete_Tables();

   /* free statement handles */
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
 * Delete_Tables()
 *
 * This function removes all existing tables
 */

void Delete_Tables(void)
{
   RETCODE  rc;

   if ((rc = SQLExecDirect(hStmt, "DROP TABLE ordritem", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(DROP TABLE)");
   if ((rc = SQLExecDirect(hStmt, "DROP TABLE custordr", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(DROP TABLE)");
   if ((rc = SQLExecDirect(hStmt, "DROP TABLE custmast", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(DROP TABLE)");
   if ((rc = SQLExecDirect(hStmt, "DROP TABLE itemmast", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(DROP TABLE)");
}


/*
 * Create_CustomerMaster_Table()
 *
 * Create the table CustomerMaster
 */

void Create_CustomerMaster_Table(void)
{
   RETCODE  rc;

   /* define table CustomerMaster */
   printf("\ttable CustomerMaster\n");

   if ((rc = SQLExecDirect(hStmt,
      "CREATE TABLE custmast ( \
         cm_custnumb CHAR(4) PRIMARY KEY, \
         cm_custzipc CHAR(9), \
         cm_custstat CHAR(2), \
         cm_custrtng CHAR(1), \
         cm_custname VARCHAR(47), \
         cm_custaddr VARCHAR(47), \
         cm_custcity VARCHAR(47))",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");
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
         co_ordrnumb CHAR(6) PRIMARY KEY, \
         co_custnumb CHAR(4), \
         FOREIGN KEY (co_custnumb) REFERENCES custmast)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");
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
         oi_itemnumb CHAR(5), \
         FOREIGN KEY (oi_itemnumb) REFERENCES itemmast, \
         FOREIGN KEY (oi_ordrnumb) REFERENCES custordr)",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");
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
         im_itemnumb CHAR(5) PRIMARY KEY, \
         im_itemdesc VARCHAR(47))",
      SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(CREATE TABLE)");
}


/*
 * Add_Transactions()
 *
 * Add an Order and associated Items "as a transaction" to their
 * respective tables.  A transaction is committed or aborted if the
 * customer number on the order is confirmed valid.  Likewise each
 * item in the order is verified to be a valid item.
 */

typedef struct {
   SQLTCHAR       *ordrdate, *promdate, *ordrnumb, *custnumb;
} ORDER_DATA;

typedef struct {
   SQLTCHAR       *ordrnumb;
   SQLUSMALLINT   sequnumb;
   SQLUSMALLINT   quantity;
   SQLTCHAR       *itemnumb;
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

void Add_Transactions(void)
{
   RETCODE     rc;
   SQLINTEGER  i, j = 0;
   SQLINTEGER  nOrders = sizeof(orders) / sizeof(ORDER_DATA);
   SQLINTEGER  nItems = sizeof(items) / sizeof(ORDERITEM_DATA);
   SQLTCHAR    sCommand[512];

   printf("\tAdd transaction records... \n");

   for (i = 0; i < nOrders; i++)
   {
      /* add order record */
      sprintf(sCommand, "INSERT INTO custordr VALUES ('%s', '%s', '%s', '%s')",
         orders[i].ordrdate,
         orders[i].promdate,
         orders[i].ordrnumb,
         orders[i].custnumb);
      if ((rc = SQLExecDirect(hStmt, sCommand, SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");

      /* process order items */
      while (!(strcmp(items[j].ordrnumb, orders[i].ordrnumb)))
      {
         /* add item record */
         sprintf(sCommand, "INSERT INTO ordritem VALUES (%d, %d, '%s', '%s')",
            items[j].sequnumb,
            items[j].quantity,
            items[j].ordrnumb,
            items[j].itemnumb);
         if ((rc = SQLExecDirect(hStmt, sCommand , SQL_NTS)) != SQL_SUCCESS)
            Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");

         /* bump to next item */
         j++;

         /* exit the while loop on last item */
         if (j >= nItems)
            break;
      }

      /* commit the transaction */
      if ((rc = SQLExecDirect(hStmt, "COMMIT WORK", SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(COMMIT WORK)");
   }
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

   printf("\tAdd records in table CustomerMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      strcpy (sCommand, "INSERT INTO custmast VALUES ");
      strcat (sCommand, data[i]);
      if ((rc = SQLExecDirect(hStmt, sCommand ,SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");
   }

   if ((rc = SQLExecDirect(hStmt, "COMMIT WORK", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(COMMIT WORK)");
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

   printf("\tAdd records in table ItemMaster...\n");

   /* add one record at time to table */
   for (i = 0; i < nRecords; i++)
   {
      strcpy (sCommand, "INSERT INTO itemmast VALUES ");
      strcat (sCommand, data[i]);
      if ((rc = SQLExecDirect(hStmt, sCommand ,SQL_NTS)) != SQL_SUCCESS)
         Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(INSERT)");
   }

   if ((rc = SQLExecDirect(hStmt, "COMMIT WORK", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(COMMIT WORK)");
}


/*
 * Display_CustomerOrders()
 *
 * This function displays the contents of CustomerOrders table
 */

void Display_CustomerOrders(void)
{
   RETCODE  rc;
   SQLTCHAR ordrnumb[6+1], custnumb[4+1];
   SQLLEN   cbData;

   printf("\n\tCustomerOrders Table...\n");

   rc = SQLExecDirect(hStmt, "SELECT * FROM custordr" ,SQL_NTS);
   if (rc != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(SELECT)");

   /* fetch and display each individual record */
   while ((rc = SQLFetch(hStmt)) == SQL_SUCCESS)
   {
      SQLGetData(hStmt, 3, SQL_C_CHAR, ordrnumb, sizeof(ordrnumb), &cbData);
      SQLGetData(hStmt, 4, SQL_C_CHAR, custnumb, sizeof(custnumb), &cbData);
      printf("\t   %s   %s\n", ordrnumb, custnumb);
   }

   SQLFreeStmt(hStmt,SQL_CLOSE);
}


/*
 * Display_OrderItems()
 *
 * This function displays the contents of OrderItems table
 */

void Display_OrderItems(void)
{
   RETCODE  rc;
   SQLTCHAR ordrnumb[6+1], itemnumb[5+1];
   SQLLEN   cbData;

   printf("\n\tOrderItems Table...\n");

   rc = SQLExecDirect(hStmt, "SELECT * FROM ordritem" ,SQL_NTS);
   if (rc != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(SELECT)");

   /* fetch and display each individual record */
   while ((rc = SQLFetch(hStmt)) == SQL_SUCCESS)
   {
      SQLGetData(hStmt, 3, SQL_C_CHAR, ordrnumb, sizeof(ordrnumb), &cbData);
      SQLGetData(hStmt, 4, SQL_C_CHAR, itemnumb, sizeof(itemnumb), &cbData);
      printf("\t   %s   %s\n", ordrnumb, itemnumb);
   }

   SQLFreeStmt(hStmt,SQL_CLOSE);
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

   const SQLINTEGER  TABLE_NOT_FOUND = -20005;
   const SQLINTEGER  CONSTRAINT_VIOLATION = -20116;
   const SQLINTEGER  CANNOT_CONNECT = -20212;

   if (!HandleType) {
      printf("%s - SQL ERROR: %s\n", sErrMsg, "Out of memory");
   } else {
      i = 1;
      while (SQLGetDiagRec(HandleType, Handle, i++, szState, &sdwNative,
            szMsg, sizeof(szMsg), &swMsgLen) != SQL_NO_DATA) {
   
         if (sdwNative == TABLE_NOT_FOUND ||
            sdwNative == CONSTRAINT_VIOLATION)
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

/* end of ODBCTutorial4.c */
