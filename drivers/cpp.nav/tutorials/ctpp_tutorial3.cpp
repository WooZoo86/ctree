//
// ctpp_tutorial3.c
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
//  5.  Update one record under locking control
//


// Preprocessor definitions and includes

#include "ctdbsdk.hpp"  // c-tree headers

#ifdef ctPortAppleiOS
#define main my_main
#endif

#define LOCK_SUPPORT

#ifndef ctCLIENT
#ifdef  NOTFORCE
#undef LOCK_SUPPORT
#endif
#endif


// Global declarations

CTSession   *MySession = (CTSession *)0;
CTTable     *MyTable = (CTTable *)0;
CTRecord    *MyRecord = (CTRecord *)0;


// Function declarations

VOID Initialize(VOID), Define(VOID), Manage(VOID), Done(VOID);
VOID Create_CustomerMaster_Table(VOID), Check_Table_Mode(CTTable *);
VOID Add_CustomerMaster_Records(VOID), Update_CustomerMaster_Record(VOID);
VOID Delete_Records(CTRecord *), Display_Records(VOID);
VOID Handle_Exception(CTException);


//
// main()
//
// The main() function implements the concept of "init, define, manage
// and you're done..."
//

int main (NINT argc, pTEXT argv[])
{
#ifdef LOCK_SUPPORT
   Initialize();

   Define();

   Manage();

   Done();
#else
   printf("\nThis tutorial demonstrates basic Record Locking. Record Locking is not");
   printf("\napplicable to c-tree's SingleUser model. In order to run this program");
   printf("\nselect a c-tree Multi-User or Client-Side type c-tree model");
#endif

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
   printf("DEFINE\n");

   Create_CustomerMaster_Table();
}



//
// Manage()
//
// This function performs record adds and updates using locking
//

VOID Manage(VOID)
{
   printf("MANAGE\n");

   // populate the table with data
   Add_CustomerMaster_Records();

   // display contents of table
   Display_Records();

   // update a record under locking control
   Update_CustomerMaster_Record();

   // display again after update and effects of lock
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
// Create_CustomerMaster_Table()
//
// Open table CustomerMaster, if it exists. Otherwise create it
// along with its indices and open it
//

VOID Create_CustomerMaster_Table(VOID)
{
   CTBOOL   do_create = NO;

   // define table CustomerMaster
   printf("\ttable CustomerMaster\n");
   try
   {
      MyTable->Open("custmast", CTOPEN_NORMAL);
   }
   catch (...)
   {
      // table does not exist
      do_create = YES;
   }

   if (do_create)
   {
      try
      {
         // define table fields
         CTField field1 = MyTable->AddField("cm_custnumb", CT_FSTRING, 4);
         MyTable->AddField("cm_custzipc", CT_FSTRING, 9);
         MyTable->AddField("cm_custstat", CT_FSTRING, 2);
         MyTable->AddField("cm_custratg", CT_FSTRING, 1);
         MyTable->AddField("cm_custname", CT_STRING, 47);
         MyTable->AddField("cm_custaddr", CT_STRING, 47);
         MyTable->AddField("cm_custcity", CT_STRING, 47);

         // define index
         CTIndex index1 = MyTable->AddIndex("cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
         index1.AddSegment(field1, CTSEG_SCHSEG);

         // create table
         printf("\tCreate table...\n");
         MyTable->Create("custmast", CTCREATE_NORMAL);

         // open table
         printf("\tOpen table...\n");
         MyTable->Open("custmast", CTOPEN_NORMAL);
      }
      catch (CTException E)
      {
         Handle_Exception(E);
      }
   }
   else
   {
      Check_Table_Mode(MyTable);

      // confirm the index exists, if not then add the index
      //
      // this scenario arises out of the fact that this table was created in tutorial 1
      // without indexes. The index is now created by the call to ctdbAlterTable

      do_create = NO;
      try
      {
         MyTable->GetIndex("cm_custnumb_idx");
      }
      catch (CTException E)
      {
         do_create = YES;
      }

      if (do_create)
      {
         try
         {
            CTField field1 = MyTable->GetField("cm_custnumb");
            CTIndex index1 = MyTable->AddIndex("cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
            index1.AddSegment(field1, CTSEG_SCHSEG);
            MyTable->Alter(CTDB_ALTER_NORMAL);
         }
         catch (CTException E)
         {
            Handle_Exception(E);
         }
      }
   }
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
// Add_CustomerMaster_Records()
//
// This function adds records to table CustomerMaster from an
// array of strings
//

VOID Add_CustomerMaster_Records(VOID)
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

   Delete_Records(MyRecord);

   printf("\tAdd records...\n");

   try
   {
      for (CTSIGNED i = 0; i < nRecords; i++)
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
// Delete_Records()
//
// This function deletes all the records in the table
//

VOID Delete_Records(CTRecord *record)
{
   CTBOOL   found;

   printf("\tDelete records...\n");

   try
   {
      // enable session-wide lock flag
      MySession->Lock(CTLOCK_WRITE_BLOCK);

      // read first record
      found = record->First();

      while (found)  // while records are found
      {
         // delete record
         record->Delete();
         // read next record
         found = record->Next();
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
   TEXT     custnumb[4+1];
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

         // display data
         printf("\n\t\t%-8s%10s\n",custnumb, custname);

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
// Update_CustomerMaster_Records()
//
// Update one record under locking control to demonstrate the effects
// of locking
//

VOID Update_CustomerMaster_Record(VOID)
{
   printf("\tUpdate record...\n");

   try
   {
      // enable session-wide lock flag
      MySession->Lock(CTLOCK_WRITE_BLOCK);

      MyRecord->Clear();
      MyRecord->SetFieldAsString(0, "1003");
      // find record by customer number
      if (MyRecord->Find(CTFIND_EQ))
      {
         MyRecord->SetFieldAsString(4, "KEYON DOOLING");
         // rewrite record
         MyRecord->Write();

         printf("\tPress <ENTER> key to unlock\n");
         getchar();
      }
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }

   MySession->Unlock();
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

// end of ctpp_tutorial3.cpp
