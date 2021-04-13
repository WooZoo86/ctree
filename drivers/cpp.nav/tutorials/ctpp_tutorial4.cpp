//
// ctpp_tutorial4.c
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
//  2.  Create 4 tables each with an index
//  3.  Add records in multiple tables under transaction processing control
//  4.  Display the contents of the tables
//


// Preprocessor definitions and includes

#include "ctdbsdk.hpp"  // c-tree headers

#ifdef ctPortAppleiOS
#define main my_main
#endif

// Global declarations

CTSession   *MySession = (CTSession *)0;

CTTable     *tableCustMast = (CTTable *)0;
CTTable     *tableCustOrdr = (CTTable *)0;
CTTable     *tableOrdrItem = (CTTable *)0;
CTTable     *tableItemMast = (CTTable *)0;

CTRecord    *recordCustMast = (CTRecord *)0;
CTRecord    *recordCustOrdr = (CTRecord *)0;
CTRecord    *recordOrdrItem = (CTRecord *)0;
CTRecord    *recordItemMast = (CTRecord *)0;


// Function declarations

VOID Initialize(VOID), Define(VOID), Manage(VOID), Done(VOID);
VOID Create_CustomerMaster_Table(VOID), Create_CustomerOrders_Table(VOID);
VOID Create_OrderItems_Table(VOID), Create_ItemMaster_Table(VOID);
VOID Check_Table_Mode(CTTable*);
VOID Add_CustomerMaster_Records(VOID), Add_ItemMaster_Records(VOID);
VOID Add_Transactions(VOID), Delete_Records(CTRecord*);
VOID Display_CustomerOrders(VOID), Display_OrderItems(VOID);
VOID Handle_Exception(CTException);


//
// main()
//
// The main() function implements the concept of "init, define, manage
// and you're done..."
//

int main (NINT argc, pTEXT argv[])
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

   printf("\nPress <ENTER> key to exit . . .\n");
#ifndef ctPortWINCE
   getchar();
#endif

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
      tableCustMast = new CTTable(MySession);
      tableCustOrdr = new CTTable(MySession);
      tableOrdrItem = new CTTable(MySession);
      tableItemMast = new CTTable(MySession);

      // allocate the record objects
      recordCustMast = new CTRecord(tableCustMast);
      recordCustOrdr = new CTRecord(tableCustOrdr);
      recordOrdrItem = new CTRecord(tableOrdrItem);
      recordItemMast = new CTRecord(tableItemMast);

      // connect to server
      printf("\tLogon to server...\n");
      MySession->Logon("FAIRCOMS", "ADMIN", "ADMIN");
   }
   catch (CTException E)
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
   Create_CustomerOrders_Table();
   Create_OrderItems_Table();
   Create_ItemMaster_Table();
}


//
// Manage()
//
// Populates table and perform a simple query
//

VOID Manage(VOID)
{
   printf("MANAGE\n");

   // populate the tables with data
   Add_CustomerMaster_Records();
   Add_ItemMaster_Records();

   Add_Transactions();

   // display the orders and their items
   Display_CustomerOrders();
   Display_OrderItems();
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
      // close tables
      printf("\tClose tables...\n");
      tableCustOrdr->Close();
      tableOrdrItem->Close();
      tableItemMast->Close();
      tableCustMast->Close();

      // logout from session
      printf("\tLogout...\n");
      MySession->Logout();
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }

   // release record objects
   delete recordCustMast;
   delete recordItemMast;
   delete recordOrdrItem;
   delete recordCustOrdr;

   // release table objects
   delete tableCustMast;
   delete tableItemMast;
   delete tableOrdrItem;
   delete tableCustOrdr;

   // release session object
   delete MySession;
   
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
      tableCustMast->Open("custmast", CTOPEN_NORMAL);
   }
   catch (CTException E)
   {
      // table does not exist
      do_create = YES;
   }

   if (do_create)
   {
      try
      {
         // define table fields
         CTField field1 = tableCustMast->AddField("cm_custnumb", CT_FSTRING, 4);
         tableCustMast->AddField("cm_custzipc", CT_FSTRING, 9);
         tableCustMast->AddField("cm_custstat", CT_FSTRING, 2);
         tableCustMast->AddField("cm_custratg", CT_FSTRING, 1);
         tableCustMast->AddField("cm_custname", CT_STRING, 47);
         tableCustMast->AddField("cm_custaddr", CT_STRING, 47);
         tableCustMast->AddField("cm_custcity", CT_STRING, 47);

         // define index
         CTIndex index1 = tableCustMast->AddIndex("cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
         index1.AddSegment(field1, CTSEG_SCHSEG);

         // create table
         printf("\tCreate table...\n");
         tableCustMast->Create("custmast", CTCREATE_TRNLOG);

         // open table
         printf("\tOpen table...\n");
         tableCustMast->Open("custmast", CTOPEN_NORMAL);
      }
      catch (CTException E)
      {
         Handle_Exception(E);
      }
   }
   else
   {
      Check_Table_Mode(tableCustMast);

      // confirm the index exists, if not then add the index
      //
      // this scenario arises out of the fact that this table was created in tutorial 1
      // without indexes. The index is now created by the call to ctdbAlterTable

      do_create = NO;
      try
      {
         tableCustMast->GetIndex("cm_custnumb_idx");
      }
      catch (CTException E)
      {
         do_create = YES;
      }

      if (do_create)
      {
         try
         {
            CTField field1 = tableCustMast->GetField("cm_custnumb");
            CTIndex index1 = tableCustMast->AddIndex("cm_custnumb_idx", CTINDEX_FIXED, NO, NO);
            index1.AddSegment(field1, CTSEG_SCHSEG);
            tableCustMast->Alter(CTDB_ALTER_NORMAL);
         }
         catch (CTException E)
         {
            Handle_Exception(E);
         }
      }
   }
}


//
// Create_CustomerOrders_Table()
//
// Open table CustomerOrders, if it exists. Otherwise create it
// along with its indices and open it
//

VOID Create_CustomerOrders_Table(VOID)
{
   CTBOOL   do_create = NO;

   // define table CustomerOrders
   printf("\ttable CustomerOrders\n");
   try
   {
      tableCustOrdr->Open("custordr", CTOPEN_NORMAL);
   }
   catch (CTException E)
   {
      // table does not exist
      do_create = YES;
   }

   if (do_create)
   {
      try
      {
         // define table fields
         tableCustOrdr->AddField("co_ordrdate", CT_DATE, 4);
         tableCustOrdr->AddField("co_promdate", CT_DATE, 4);
         CTField field1 = tableCustOrdr->AddField("co_ordrnumb", CT_FSTRING, 6);
         CTField field2 = tableCustOrdr->AddField("co_custnumb", CT_FSTRING, 4);

         // define indices
         CTIndex index1 = tableCustOrdr->AddIndex("co_ordrnumb_idx", CTINDEX_LEADING, NO, NO);
         index1.AddSegment(field1, CTSEG_SCHSEG);
         CTIndex index2 = tableCustOrdr->AddIndex("co_custnumb_idx", CTINDEX_LEADING, YES, NO);
         index2.AddSegment(field2, CTSEG_SCHSEG);

         // create table
         printf("\tCreate table...\n");
         tableCustOrdr->Create("custordr", CTCREATE_TRNLOG);

         // open table
         printf("\tOpen table...\n");
         tableCustOrdr->Open("custordr", CTOPEN_NORMAL);
      }
      catch (CTException E)
      {
         Handle_Exception(E);
      }
   }
   else
      Check_Table_Mode(tableCustOrdr);
}


//
// Create_OrderItems_Table()
//
// Open table OrderItems, if it exists. Otherwise create it
// along with its indices and open it
//

VOID Create_OrderItems_Table(VOID)
{
   CTBOOL   do_create = NO;

   // define table OrderItems
   printf("\ttable OrderItems\n");
   try
   {
      tableOrdrItem->Open("ordritem", CTOPEN_NORMAL);
   }
   catch (CTException E)
   {
      // table does not exist
      do_create = YES;
   }

   if (do_create)
   {
      try
      {
         // define table fields
         CTField field1 = tableOrdrItem->AddField("oi_sequnumb", CT_INT2, 2);
         tableOrdrItem->AddField("oi_quantity", CT_INT2, 2);
         CTField field2 = tableOrdrItem->AddField("oi_ordrnumb", CT_FSTRING, 6);
         CTField field3 = tableOrdrItem->AddField("oi_itemnumb", CT_FSTRING, 5);

         // define indices
         CTIndex index1 = tableOrdrItem->AddIndex("oi_ordrnumb_idx", CTINDEX_LEADING, NO, NO);
         index1.AddSegment(field2, CTSEG_SCHSEG);
         index1.AddSegment(field1, CTSEG_SCHSEG);
         CTIndex index2 = tableOrdrItem->AddIndex("oi_itemnumb_idx", CTINDEX_LEADING, YES, NO);
         index2.AddSegment(field3, CTSEG_SCHSEG);

         // create table
         printf("\tCreate table...\n");
         tableOrdrItem->Create("ordritem", CTCREATE_TRNLOG);

         // open table
         printf("\tOpen table...\n");
         tableOrdrItem->Open("ordritem", CTOPEN_NORMAL);
      }
      catch (CTException E)
      {
         Handle_Exception(E);
      }
   }
   else
      Check_Table_Mode(tableOrdrItem);
}


//
// Create_ItemMaster_Table()
//
// Open table ItemMaster, if it exists. Otherwise create it
// along with its indices and open it
//

VOID Create_ItemMaster_Table(VOID)
{
   CTBOOL   do_create = NO;

   // define table ItemMaster
   printf("\ttable ItemMaster\n");
   try
   {
      tableItemMast->Open("itemmast", CTOPEN_NORMAL);
   }
   catch (CTException E)
   {
      // table does not exist
      do_create = YES;
   }

   if (do_create)
   {
      try
      {
         // define table fields
         tableItemMast->AddField("im_itemwght", CT_INT4, 4);
         tableItemMast->AddField("im_itempric", CT_MONEY, 4);
         CTField field1 = tableItemMast->AddField("im_itemnumb", CT_FSTRING, 5);
         tableItemMast->AddField("im_itemdesc", CT_STRING, 47);

         // define indices
         CTIndex index1 = tableItemMast->AddIndex("im_itemnumb_idx", CTINDEX_FIXED, NO, NO);
         index1.AddSegment(field1, CTSEG_SCHSEG);

         // create table
         printf("\tCreate table...\n");
         tableItemMast->Create("itemmast", CTCREATE_TRNLOG);

         // open table
         printf("\tOpen table...\n");
         tableItemMast->Open("itemmast", CTOPEN_NORMAL);
      }
      catch (CTException E)
      {
         Handle_Exception(E);
      }
   }
   else
      Check_Table_Mode(tableItemMast);
}


//
// Check_Table_Mode()
//
// Check if existing table has transaction processing flag enabled.
// If a table is not ready for transaction, modify the table mode to
// enable transaction processing
//

VOID Check_Table_Mode(CTTable* table)
{
   try
   {
      // get table create mode
      CTCREATE_MODE mode = table->GetCreateMode();

      // check if table is not under transaction processing control
      if (!(mode & CTCREATE_TRNLOG))
      {
         // change file mode to enable transaction processing
         mode |= CTCREATE_TRNLOG;
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

   Delete_Records(recordCustMast);

   printf("\tAdd records in table CustomerMaster...\n");

   try
   {
      // start a transaction
      recordCustMast->Begin();

      for (CTSIGNED i = 0; i < nRecords; i++)
      {
         recordCustMast->Clear();

         // populate record buffer with data
         recordCustMast->SetFieldAsString(0, data[i].number);
         recordCustMast->SetFieldAsString(1, data[i].zipcode);
         recordCustMast->SetFieldAsString(2, data[i].state);
         recordCustMast->SetFieldAsString(3, data[i].rating);
         recordCustMast->SetFieldAsString(4, data[i].name);
         recordCustMast->SetFieldAsString(5, data[i].address);
         recordCustMast->SetFieldAsString(6, data[i].city);

         // add record
         recordCustMast->Write();
      }

      // commit transaction
      recordCustMast->Commit();
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Add_ItemMaster_Records()
//
// This function adds records to table ItemMaster from an
// array of strings
//

VOID Add_ItemMaster_Records(VOID)
{
   typedef struct {
      CTSIGNED weight;
      CTMONEY  price;
      cpTEXT itemnum, description;
   } DATA_RECORD;

   DATA_RECORD data[] = {
      {10,  1995, "1",  "Hammer"},
      {3,   999,  "2",  "Wrench"},
      {4,   1659, "3",  "Saw"},
      {1,   398,  "4",  "Pliers"}
   };
   CTSIGNED nRecords = sizeof(data) / sizeof(DATA_RECORD);

   Delete_Records(recordItemMast);

   printf("\tAdd records in table ItemMaster...\n");

   try
   {
      // start a transaction
      recordItemMast->Begin();

      for (CTSIGNED i = 0; i < nRecords; i++)
      {
         recordItemMast->Clear();

         // populate record buffer with data
         recordItemMast->SetFieldAsSigned(0, data[i].weight);
         recordItemMast->SetFieldAsMoney(1, data[i].price);
         recordItemMast->SetFieldAsString(2, data[i].itemnum);
         recordItemMast->SetFieldAsString(3, data[i].description);

         // add record
         recordItemMast->Write();
      }

      // commit transaction
      recordItemMast->Commit();
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

VOID Delete_Records(CTRecord* record)
{
   CTBOOL   found;

   printf("\tDelete records...\n");

   try
   {
      // write lock required for transaction updates
      record->Lock(CTLOCK_WRITE);

      // start a transaction
      record->Begin();

      // read first record
      found = record->First();

      while (found)  // while records are found
      {
         // delete record
         record->Delete();
         // read next record
         found = record->Next();
      }

      // commit transaction
      record->Commit();

      // free locks
      record->Unlock();
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Add_Transactions()
//
// Add an Order and associated Items "as a transaction" to their
// respective tables.  A transaction is committed or aborted if the
// customer number on the order is confirmed valid.  Likewise each
// item in the order is verified to be a valid item.  SavePoints are
// established as an order is processed, allowing a transaction to
// rollback to the previously verified item
//

VOID Add_Transactions(VOID)
{
   typedef struct {
      cpTEXT orderdate, promdate, ordernum, custnum;
   } ORDER_DATA;

   typedef struct {
      cpTEXT ordernum;
      CTSIGNED seqnumber;
      CTSIGNED quantity;
      cpTEXT itemnum;
   } ITEM_DATA;

   ORDER_DATA orders[] = {
      {"09/01/2002", "09/05/2002", "1", "1001"},
      {"09/02/2002", "09/06/2002", "2", "9999"},   // bad customer number
      {"09/22/2002", "09/26/2002", "3", "1003"}
   };

   ITEM_DATA items[] = {
      {"1", 1, 2, "1"},
      {"1", 2, 1, "2"},
      {"2", 1, 1, "3"},
      {"2", 2, 3, "4"},
      {"3", 1, 2, "3"},
      {"3", 2, 2, "99"} // bad item number
   };
   CTSIGNED nOrders = sizeof(orders) / sizeof(ORDER_DATA);
   CTSIGNED nItems = sizeof(items) / sizeof(ITEM_DATA);
   NINT  savepoint;
   CTDate  orderdate;
   CTDate  promdate;
   CTSIGNED j = 0;

   Delete_Records(recordCustOrdr);
   Delete_Records(recordOrdrItem);

   printf("\tAdd transaction records... \n");

   // process orders
   for (CTSIGNED i = 0; i < nOrders; i++)
   {
      // start a transaction
      MySession->Begin();

      try
      {
         recordCustOrdr->Clear();

         // populate record buffer with order data
         orderdate.StringToDate(orders[i].orderdate, CTDATE_MDCY);
         promdate.StringToDate(orders[i].promdate, CTDATE_MDCY);
         recordCustOrdr->SetFieldAsDate(0, orderdate);
         recordCustOrdr->SetFieldAsDate(1, promdate);
         recordCustOrdr->SetFieldAsString(2, orders[i].ordernum);
         recordCustOrdr->SetFieldAsString(3, orders[i].custnum);

         // add order record
         recordCustOrdr->Write();
      }
      catch (CTException E)
      {
         Handle_Exception(E);
      }

      // set transaction savepoint
      savepoint = recordCustOrdr->SetSavePoint();

      // process order items
      while (!(strcmp(items[j].ordernum, orders[i].ordernum)))
      {
         try
         {
            recordOrdrItem->Clear();

            // populate record buffer with order item data
            recordOrdrItem->SetFieldAsSigned(0, items[j].seqnumber);
            recordOrdrItem->SetFieldAsSigned(1, items[j].quantity);
            recordOrdrItem->SetFieldAsString(2, items[j].ordernum);
            recordOrdrItem->SetFieldAsString(3, items[j].itemnum);

            // add order item record
            recordOrdrItem->Write();

            // check that item exists in ItemMaster table
            recordItemMast->Clear();
            recordItemMast->SetFieldAsString(2, items[j].itemnum);
            if (!recordItemMast->Find(CTFIND_EQ))
               // if not found, restore back to previous savepoint
               recordItemMast->RestoreSavePoint(savepoint);
            else
               // set transaction savepoint
               savepoint = recordItemMast->SetSavePoint();
         }
         catch (CTException E)
         {
            Handle_Exception(E);
         }

         // bump to next item
         j++;

         // exit the while loop on last item
         if (j >= nItems)
            break;
      }

      // check that customer exists in CustomerMaster table
      recordCustMast->Clear();
      recordCustMast->SetFieldAsString(0, orders[i].custnum);

      // commit or abort the transaction
      if (!recordCustMast->Find(CTFIND_EQ))
         recordCustMast->Abort();
      else
         recordCustMast->Commit();
   }
}


//
// Display_CustomerOrders()
//
// This function displays the contents of a table. ctdbFirstRecord() and
// ctdbNextRecord() fetch the record. Then each field is parsed and displayed
//

VOID Display_CustomerOrders(VOID)
{
   CTString custnumb;
   CTString ordrnumb;

   printf("\n\tCustomerOrder table...\n");

   try
   {
      // read first record
      if (recordCustOrdr->First())
      {
         do
         {
            ordrnumb = recordCustOrdr->GetFieldAsString(2);
            custnumb = recordCustOrdr->GetFieldAsString(3);

            // display data
            printf("\t   %s   %s\n", ordrnumb.c_str(), custnumb.c_str());
         }
         // read next record until end of file
         while (recordCustOrdr->Next());
      }
   }
   catch (CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Display_OrderItems()
//
// This function displays the contents of a table. ctdbFirstRecord() and
// ctdbNextRecord() fetch the record. Then each field is parsed and displayed
//

VOID Display_OrderItems(VOID)
{
   CTString itemnumb;
   CTString ordrnumb;

   printf("\n\tOrderItems Table...\n");

   try
   {
      // read first record
      if (recordOrdrItem->First())
      {
         do
         {
            // get field data from record buffer
            ordrnumb = recordOrdrItem->GetFieldAsString(2);
            itemnumb = recordOrdrItem->GetFieldAsString(3);

            // display data
            printf("\t   %s   %s\n", ordrnumb.c_str(), itemnumb.c_str());
         }
         // read next record until end of file
         while (recordOrdrItem->Next());
      }
   }
   catch (CTException E)
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

// end of ctpp_tutorial4.cpp
