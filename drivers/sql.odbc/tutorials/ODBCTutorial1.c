/*
 * ODBCTutorial1.c
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
void Add_Records(void), Display_Records(void), Delete_Records(void);
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
 * Create the table for containing a list of existing customers
 */

void Define(void)
{
   RETCODE  rc;

   printf("DEFINE\n");

   /* create table */
   printf("\tCreate table...\n");
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
}


/*
 * Manage()
 *
 * This function performs simple record functions of add, delete and gets
 */

void Manage(void)
{
   printf("MANAGE\n");

   /* delete any existing records */
   Delete_Records();

   /* populate the table with data */
   Add_Records();

   /* display contents of table */
   Display_Records();
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
 * Delete_Records()
 *
 * This function deletes all the records in the table
 */

void Delete_Records(void)
{
   RETCODE  rc;

   printf("\tDelete records...\n");

   if ((rc = SQLExecDirect(hStmt, "DELETE FROM custmast", SQL_NTS)) != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(DELETE)");
}


/*
 * Add_Records()
 *
 * This function adds records to a table from an array of strings
 */

void Add_Records(void)
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

   printf("\tAdd records...\n");

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
 * Display_Records()
 *
 * This function displays the contents of a table.
 */

void Display_Records(void)
{
   RETCODE  rc;
   SQLTCHAR custnumb[4+1];
   SQLTCHAR custname[47+1];
   SQLLEN   cbData;

   printf("\tDisplay records...");

   rc = SQLExecDirect(hStmt, "SELECT * FROM custmast" ,SQL_NTS);
   if (rc != SQL_SUCCESS)
      Handle_Error(SQL_HANDLE_STMT, hStmt, "SQLExecDirect(SELECT)");

   /* fetch and display each individual record */
   while ((rc = SQLFetch(hStmt)) == SQL_SUCCESS)
   {
      SQLGetData(hStmt, 1, SQL_C_CHAR, custnumb, sizeof(custnumb), &cbData);
      SQLGetData(hStmt, 5, SQL_C_CHAR, custname, sizeof(custname), &cbData);

      printf("\n\t\t%-8s%10s\n",custnumb, custname);
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

/* end of ODBCTutorial1.c */

