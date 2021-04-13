//
// ctpp_tutorial1.c
//
// Public domain c-treeDB C++ example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic CTDB++ API
// to accomplish creating and manipulating a table through the ctreeServer
//
// Functionally, this application will perform the following:
//  1.  Logon onto a session
//  2.  Add 1 table with some fields
//  3.  Populate the table with a few records
//  4.  Display the contents of the table
//


// Preprocessor definitions and includes

#include "ctdbsdk.hpp"  // c-tree headers

#ifdef ctPortAppleiOS
#define main my_main
#endif

// Global declarations

CTSession   *MySession = (CTSession *)0;
CTTable     *MyTable = (CTTable *)0;
CTRecord    *MyRecord = (CTRecord *)0;

// Function declarations

VOID Initialize(VOID), Define(VOID), Manage(VOID), Done(VOID);
VOID Add_Records(VOID), Display_Records(VOID), Delete_Records(VOID);
VOID Check_Table_Mode(CTTable *);
VOID Handle_Exception(CTException);


//
// main()
//
// The main() function implements the concept of "init, define, manage
// and you're done..."
//

int main (NINT argc, pTEXT argv[])
{
   Initialize();

   Define();

   Manage();

   Done();

   printf("\nPress <ENTER> key to exit . . .\n");
   getchar();

   return(0);
}


//
// Initialize()
//
// Perform the minimum requirement of logging onto the c-tree Server
//

VOID Initialize(VOID)
{
   printf("INIT\n");

   try
   {
      ctdbStartDatabaseEngine(); // This function is required when you are using the Server DLL model to start the underlying Server.
                                 // It does nothing in all other c-tree models

      // allocate the session object
      MySession = new CTSession(CTSESSION_CTREE);

      // allocate the table objects
      MyTable =  new CTTable(MySession);

      // allocate the record objects
      MyRecord =  new CTRecord(MyTable);

      // connect to server
      printf("\tLogon to server...\n");
      MySession->Logon("FAIRCOMS", "ADMIN", "ADMIN");
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }
}

//
// Define()
//
// Open the table, if it exists. Otherwise create and open the table
//

VOID Define(VOID)
{
   CTBOOL do_create = NO;

   printf("DEFINE\n");
   try
   {
      printf("\tOpen table...\n");
      MyTable->Open("custmast", CTOPEN_NORMAL);
   }
   catch (...)
   {
      // table does not exist. Try to create it
      do_create = YES;
   }

   if (do_create)
   {
      // create the table
      printf("\tAdd fields...\n");
      try
      {
         MyTable->AddField("cm_custnumb", CT_FSTRING, 4);
         MyTable->AddField("cm_custzipc", CT_FSTRING, 9);
         MyTable->AddField("cm_custstat", CT_FSTRING, 2);
         MyTable->AddField("cm_custrtng", CT_FSTRING, 1);
         MyTable->AddField("cm_custname", CT_STRING, 47);
         MyTable->AddField("cm_custaddr", CT_STRING, 47);
         MyTable->AddField("cm_custcity", CT_STRING, 47);

         printf("\tCreate table...\n");
         MyTable->Create("custmast", CTCREATE_NORMAL);

         MyTable->Open("custmast", CTOPEN_NORMAL);
      }
      catch (CTException E)
      {
         Handle_Exception(E);
      }
   }
   else
      Check_Table_Mode(MyTable);
}


//
// Manage()
//
// This function performs simple record functions of add, delete and gets
//

VOID Manage(VOID)
{
   printf("MANAGE\n");

   // delete any existing records
   Delete_Records();

   // populate the table with data
   Add_Records();

   // display contents of table
   Display_Records();
}


//
// Done()
//
// This function handles the housekeeping of closing, freeing,
// disconnecting and logging out of the database
//

VOID Done(VOID)
{
   printf("DONE\n");

   try
   {
      // close table
      printf("\tClose table...\n");
      MyTable->Close();
      // logout
      printf("\tLogout...\n");
      MySession->Logout();
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }

   // If you are linked to the Server DLL, then we should stop our Server at the end of the program.
   // It does nothing in all other c-tree models.
   ctdbStopDatabaseEngine();
   
}


//
// Check_Table_Mode()
//
// Check if existing table has transaction processing flag enabled.
// If a table is under transaction processing control, modify the
// table mode to disable transaction processing
//

VOID Check_Table_Mode(CTTable *table)
{
   try
   {
      // get table create mode
      CTCREATE_MODE mode = table->GetCreateMode();

      // check if table is under transaction processing control
      if ((mode & CTCREATE_TRNLOG))
      {
         // change file mode to disable transaction processing
         mode ^= CTCREATE_TRNLOG;
         table->UpdateCreateMode(mode);
      }
   }
   catch (CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Delete_Records()
//
// This function deletes all the records in the table
//

VOID Delete_Records(VOID)
{
   CTBOOL   found;

   printf("\tDelete records...\n");

   try
   {
      // read first record
      found = MyRecord->First();

      while (found)  // while records are found
      {
         // delete record
         MyRecord->Delete();
         // read next record
         found = MyRecord->Next();
      }
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Add_Records()
//
// This function adds records to a table in the database from an
// array of strings
//

VOID Add_Records(VOID)
{
   typedef struct {
      cpTEXT number, zipcode, state, rating, name, address, city;
   } DATA_RECORD;

   DATA_RECORD data[] = {
      "1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency",      "Orange",
      "1001", "61434", "CT", "1", "Michael Jordan", "13 Main",           "Harford",
      "1002", "73677", "GA", "1", "Joshua Brown",   "4356 Cambridge",    "Atlanta",
      "1003", "10034", "MO", "1", "Keyon Dooling",  "19771 Park Avenue", "Columbia"
   };
   CTSIGNED nRecords = sizeof(data) / sizeof(DATA_RECORD);

   printf("\tAdd records...\n");

   try
   {
      for(CTSIGNED i = 0; i < nRecords; i++)
      {
         MyRecord->Clear();

         // populate record buffer with data
         MyRecord->SetFieldAsString(0, data[i].number);
         MyRecord->SetFieldAsString(1, data[i].zipcode);
         MyRecord->SetFieldAsString(2, data[i].state);
         MyRecord->SetFieldAsString(3, data[i].rating);
         MyRecord->SetFieldAsString(4, data[i].name);
         MyRecord->SetFieldAsString(5, data[i].address);
         MyRecord->SetFieldAsString(6, data[i].city);

         // add record
         MyRecord->Write();
      }
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Display_Records()
//
// This function displays the contents of a table. First() and Next()
// fetch the record. Then each field is parsed and displayed
//

VOID Display_Records(VOID)
{
   CTBOOL   found;
   TEXT     custnumb[47+1];
   TEXT     custname[47+1];

   printf("\tDisplay records...");

   try
   {
      // read first record
      found = MyRecord->First();

      while (found)
      {
         strcpy(custnumb, MyRecord->GetFieldAsString(0).c_str());
         strcpy(custname, MyRecord->GetFieldAsString(4).c_str());

         printf("\n\t\t%-8s%-20s\n",custnumb, custname);

         // read next record
         found = MyRecord->Next();
      }
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Handle_Exception()
//
// This function handles unexpected C++ exceptions. It displays an error message
// allowing the user to acknowledge before terminating the application
//

VOID Handle_Exception(CTException err)
{
   printf ("\nERROR: [%d] - %s\n", err.GetErrorCode(), err.GetErrorMsg());
   printf("*** Execution aborted *** \nPress <ENTER> key to exit...");
   getchar();

   exit(1);
}

// end of ctpp_tutorial1.cpp
