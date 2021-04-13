/*
 * DSQL_Tutorial1.c
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
 *  2.  Add 1 table with some fields
 *  3.  Populate the table with a few records
 *  4.  Display the contents of the table
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
void Add_Records(void), Display_Records(void), Delete_Records(void);
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

void Initialize (void)
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
 * Create the table for containing a list of existing customers
 */

void Define(void)
{
   CTSQLRET rc;

   printf("DEFINE\n");

   ctsqlExecuteDirect(hCmd, "DROP TABLE ordritem");
   ctsqlExecuteDirect(hCmd, "DROP TABLE custordr");
   ctsqlExecuteDirect(hCmd, "DROP TABLE custmast");
   ctsqlExecuteDirect(hCmd, "DROP TABLE itemmast");

   /* create table */
   printf("\tCreate table...\n");
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
 * Delete_Records()
 *
 * This function deletes all the records in the table
 */

void Delete_Records(void)
{
   CTSQLRET rc;

   printf("\tDelete records...\n");

   if ((rc = ctsqlExecuteDirect(hCmd, "DELETE FROM custmast")) != CTSQLRET_OK)
      Handle_Error("ctsqlExecuteDirect(DELETE)");
}


/*
 * Add_Records()
 *
 * This function adds records to a table from an array of strings
 */

void Add_Records(void)
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

   printf("\tAdd records...\n");

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
 * Display_Records()
 *
 * This function displays the contents of a table.
 */

void Display_Records(void)
{
   CTSQLRET       rc;
   CTSQLCHAR      custnumb[4+1];
   CTSQLCHAR      custname[47+1];
   pCTSQLCURSOR   hCursor = NULL;

   printf("\tDisplay records...");

   rc = ctsqlPrepare(hCmd, "SELECT * FROM custmast");
   if (rc != CTSQLRET_OK)
      Handle_Error("ctsqlPrepare(SELECT)");

   rc = ctsqlExecute(hCmd, &hCursor);
   if (rc != CTSQLRET_OK)
      Handle_Error("ctsqlExecute(SELECT)");

   /* fetch and display each individual record */
   while ((rc = ctsqlNext(hCursor)) == CTSQLRET_OK)
   {
      ctsqlGetChar(hCursor, 0, custnumb);
      ctsqlGetChar(hCursor, 4, custname);

      printf("\n\t\t%-8s%10s\n", custnumb, custname);
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

/* end of DSQL_Tutorial1.c */
