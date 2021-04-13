//
// ctpp_tutorial2.c
//
// Public domain c-treeDB C++ example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic CTDB++ API
// to accomplish creating and manipulating a table through the ctreeServer
//
// Functionally, this application will perform the following:
//  1.  Create a database
//  2.  Create 4 tables each with an index
//  3.  Populate each table with a few records
//  4.  Build a query utilizing the advantage of indexes
//  5.  Output the results of the query
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
VOID Check_Table_Mode(CTTable *);
VOID Add_CustomerMaster_Records(VOID), Add_CustomerOrders_Records(VOID);
VOID Add_OrderItems_Records(VOID), Add_ItemMaster_Records(VOID);
VOID Delete_Records(CTRecord *);
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
   CTSIGNED quantity;
   CTFLOAT  price, total;
   TEXT     itemnumb[5+1], custnumb[4+1], ordrnumb[6+1], custname[47+1];
   CTBOOL   isOrderFound, isItemFound;

   printf("MANAGE\n");

   // populate the tables with data
   Add_CustomerMaster_Records();
   Add_CustomerOrders_Records();
   Add_OrderItems_Records();
   Add_ItemMaster_Records();

   // perform a query:
   // list customer name and total amount per order

   // name               total
   // @@@@@@@@@@@@@      $xx.xx

   // for each order in the CustomerOrders table
   //    fetch order number
   //    fetch customer number
   //    fetch name from CustomerMaster table based on customer number
   //    for each order item in OrderItems table
   //       fetch item quantity
   //       fetch item number
   //       fetch item price from ItemMaster table based on item number
   //    next
   // next

   printf("\n\tQuery Results\n");

   try
   {
      // get the first order
      isOrderFound = recordCustOrdr->First();

      while (isOrderFound) // for each order in the CustomerOrders table
      {
         // fetch order number
         strcpy(ordrnumb, recordCustOrdr->GetFieldAsString(2).c_str());
         // fetch customer number
         strcpy(custnumb, recordCustOrdr->GetFieldAsString(3).c_str());

         // fetch name from CustomerMaster table based on customer number
         recordCustMast->Clear();
         recordCustMast->SetFieldAsString(0, custnumb);
         if (!recordCustMast->Find(CTFIND_EQ))
            continue;   // not possible in our canned example
         strcpy(custname, recordCustMast->GetFieldAsString(4).c_str());

         // fetch item price from OrderItems table
         recordOrdrItem->Clear();
         recordOrdrItem->SetFieldAsString(2, ordrnumb);
         // define a recordset to scan only items applicable to this order
         recordOrdrItem->RecordSetOn(6);
         isItemFound = recordOrdrItem->First();

         total = 0;
         while (isItemFound) // for each order item in OrderItems table
         {
            // fetch item quantity
            quantity = recordOrdrItem->GetFieldAsSigned(1);
            // fetch item number
            strcpy(itemnumb, recordOrdrItem->GetFieldAsString(3).c_str());

            // fetch item price from ItemMaster table based on item number
            recordItemMast->Clear();
            recordItemMast->SetFieldAsString(2, itemnumb);
            recordItemMast->Find(CTFIND_EQ);
            price = recordItemMast->GetFieldAsFloat(1);

            // calculate order total
            total += (price * quantity);

            isItemFound = recordOrdrItem->Next();
         }

         recordOrdrItem->RecordSetOff();

         // output data to stdout
         printf("\t\t%-20s %.2f\n", custname, total);

         // read next order
         if (!recordCustOrdr->Next())
            isOrderFound = 0;
      }
   }
   catch(CTException E)
   {
      Handle_Exception(E);
   }
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

   // close table
   printf("\tClose tables...\n");
   try
   {
      tableCustMast->Close();
      tableCustOrdr->Close();
      tableOrdrItem->Close();
      tableItemMast->Close();

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
      tableCustMast->Open("custmast", CTOPEN_NORMAL);
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
         tableCustMast->Create("custmast", CTCREATE_NORMAL);

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
         tableCustOrdr->Create("custordr", CTCREATE_NORMAL);

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
         tableOrdrItem->Create("ordritem", CTCREATE_NORMAL);

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
         tableItemMast->AddField("im_itemwght", CT_INT4, 4);
         tableItemMast->AddField("im_itempric", CT_MONEY, 4);
         CTField field1 = tableItemMast->AddField("im_itemnumb", CT_FSTRING, 5);
         tableItemMast->AddField("im_itemdesc", CT_STRING, 47);

         // define indices
         CTIndex index1 = tableItemMast->AddIndex("im_itemnumb_idx", CTINDEX_FIXED, NO, NO);
         index1.AddSegment(field1, CTSEG_SCHSEG);

         // create table
         printf("\tCreate table...\n");
         tableItemMast->Create("itemmast", CTCREATE_NORMAL);

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
// If a table is under transaction processing control, modify the
// table mode to disable transaction processing
//

VOID Check_Table_Mode(CTTable * table)
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

   Delete_Records(recordCustMast);

   printf("\tAdd records in table CustomerMaster...\n");

   try
   {
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
   }

   catch(CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Add_CustomerOrders_Records()
//
// This function adds records to table CustomerOrders from an
// array of strings
//

VOID Add_CustomerOrders_Records(VOID)
{
   CTDate   orderdate;
   CTDate   promisedate;

   typedef struct {
      cpTEXT orderdate, promisedate, ordernum, customernum;
   } DATA_RECORD;

   DATA_RECORD data[] = {
      {"09/01/2002", "09/05/2002",  "1",  "1001"},
      {"09/02/2002", "09/06/2002",  "2",  "1002"}
   };
   CTSIGNED nRecords = sizeof(data) / sizeof(DATA_RECORD);


   Delete_Records(recordCustOrdr);

   printf("\tAdd records in table CustomerOrders...\n");

   try
   {
      for (CTSIGNED i = 0; i < nRecords; i++)
      {
         recordCustOrdr->Clear();

         orderdate.StringToDate(data[i].orderdate, CTDATE_MDCY);
         promisedate.StringToDate(data[i].promisedate, CTDATE_MDCY);
         // populate record buffer with data
         recordCustOrdr->SetFieldAsDate(0, orderdate);
         recordCustOrdr->SetFieldAsDate(1, promisedate);
         recordCustOrdr->SetFieldAsString(2, data[i].ordernum);
         recordCustOrdr->SetFieldAsString(3, data[i].customernum);

         // add record
         recordCustOrdr->Write();
      }
   }

   catch(CTException E)
   {
      Handle_Exception(E);
   }
}


//
// Add_OrderItems_Records()
//
// This function adds records to table OrderItems from an
// array of strings
//

VOID Add_OrderItems_Records(VOID)
{
   typedef struct {
      CTSIGNED sequencenum, quantity;
      cpTEXT ordernum, itemnum;
   } DATA_RECORD;

   DATA_RECORD data[] = {
      {1,   2, "1",  "1"},
      {2,   1, "1",  "2"},
      {3,   1, "1",  "3"},
      {1,   3, "2",  "3"}
   };
   CTSIGNED nRecords = sizeof(data) / sizeof(DATA_RECORD);

   Delete_Records(recordOrdrItem);

   printf("\tAdd records in table OrderItems...\n");

   try
   {
      for (CTSIGNED i = 0; i < nRecords; i++)
      {
         recordOrdrItem->Clear();

         // populate record buffer with data
         recordOrdrItem->SetFieldAsSigned(0, data[i].sequencenum);
         recordOrdrItem->SetFieldAsSigned(1, data[i].quantity);
         recordOrdrItem->SetFieldAsString(2, data[i].ordernum);
         recordOrdrItem->SetFieldAsString(3, data[i].itemnum);

         // add record
         recordOrdrItem->Write();
      }
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

// end of ctpp_tutorial2.cpp
