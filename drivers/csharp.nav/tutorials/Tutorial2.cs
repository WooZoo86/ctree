//
// Tutorial2.cs
//
// Public domain C# ISAM .NET example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic ISAM .NET API
// to accomplish creating and manipulating a table through the ctreeServer
//
// Functionally, this application will perform the following:
//  1.  Create a database
//  2.  Create 4 tables each with an index
//  3.  Populate each table with a few records
//  4.  Build a query utilizing the advantage of indexes
//  5.  Output the results of the query
//


using System;
using FairCom.CtreeDb;
using FairCom.CtreeDb.ENUMS;

namespace Tutorial2
{
	class Tutorial2
	{
		static CTSession  MySession;

      static CTTable    tableCustOrdr;
		static CTTable    tableOrdrItem;
		static CTTable    tableItemMast;
		static CTTable    tableCustMast;

      static CTRecord   recordCustOrdr;
		static CTRecord   recordOrdrItem;
		static CTRecord   recordItemMast;
		static CTRecord   recordCustMast;


      //
      // main()
      //
      // The main() function implements the concept of "init, define, manage
      // and you're done..."
      //

      [STAThread]
      static void Main(string[] args)
      {
         Initialize();

         Define();

         Manage();

         Done();

         Console.WriteLine("\nPress <ENTER> key to exit . . .");
         Console.ReadLine();
      }


      //
      // Initialize()
      //
      // Perform the minimum requirement of logging onto the c-tree Server
      //

      static void Initialize()
      {
         Console.WriteLine("INIT");

         try
         {
            // allocate the session object
            MySession = new CTSession(SESSION_TYPE.CTREE_SESSION);

            // allocate the table objects
            tableCustOrdr = new CTTable(MySession);
            tableOrdrItem = new CTTable(MySession);
            tableItemMast = new CTTable(MySession);
            tableCustMast = new CTTable(MySession);

            // allocate the record objects
            recordCustOrdr = new CTRecord(tableCustOrdr);
            recordOrdrItem = new CTRecord(tableOrdrItem);
            recordItemMast = new CTRecord(tableItemMast);
            recordCustMast = new CTRecord(tableCustMast);
         }
         catch (CTException E)
         {
            Handle_Exception(E);
         }

         try
         {
            // connect to server
            Console.WriteLine("\tLogon to server...");
            MySession.Logon("FAIRCOMS", "ADMIN", "ADMIN");
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

      static void Define()
		{
         Console.WriteLine("DEFINE");

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

      static void Manage()
      {
         int      quantity;
         double   price, total;
         string   itemnumb, custnumb, ordrnumb, custname;
         bool     isOrderFound, isItemFound;
   
			Console.WriteLine("MANAGE");

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

         Console.WriteLine("\n\tQuery Results");

         try
         {
            // get the first order
            isOrderFound = recordCustOrdr.First();

            while (isOrderFound) // for each order in the CustomerOrders table
            {
               // fetch order number
               ordrnumb = recordCustOrdr.GetFieldAsString(2);
               // fetch customer number
               custnumb = recordCustOrdr.GetFieldAsString(3);

               // fetch name from CustomerMaster table based on customer number
               recordCustMast.Clear();
               recordCustMast.SetFieldAsString(0, custnumb);
               if (!recordCustMast.Find(FIND_MODE.EQ))
                  continue;   // not possible in our canned example
               custname = recordCustMast.GetFieldAsString(4);

               // fetch item price from OrderItems table
               recordOrdrItem.Clear();
               recordOrdrItem.SetFieldAsString(2, ordrnumb);
               // define a recordset to scan only items applicable to this order
               recordOrdrItem.RecordSetOn(6);
               isItemFound = recordOrdrItem.First();

               total = 0;
               while (isItemFound)   // for each order item in OrderItems table
               {
                  // fetch item quantity
                  recordOrdrItem.GetFieldValue(1,out quantity);
                  // fetch item number
                  itemnumb = recordOrdrItem.GetFieldAsString(3);

                  // fetch item price from ItemMaster table based on item number
                  recordItemMast.Clear();
                  recordItemMast.SetFieldAsString(2, itemnumb);
                  recordItemMast.Find(FIND_MODE.EQ);
                  recordItemMast.GetFieldValue(1,out price);

                  // calculate order total
                  total += (price * quantity);

                  isItemFound = recordOrdrItem.Next();
               }

               recordOrdrItem.RecordSetOff();

               // output data to stdout
               Console.WriteLine("\t\t{0,-20}{1,-8}", custname, total);

               // read next order
               if (!recordCustOrdr.Next())
                  isOrderFound = false;
            }
         }
         catch (CTException E)
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

      static void Done()
      {
         Console.WriteLine("DONE");

         try
         {
            // close tables
            Console.WriteLine("\tClose tables...");
            tableCustMast.Close();
            tableCustOrdr.Close();
            tableOrdrItem.Close();
            tableItemMast.Close();

            // logout
            Console.WriteLine("\tLogout...");
            MySession.Logout();
         }
         catch (CTException E)
         {
            Handle_Exception(E);
         }
      }


      //
      // Create_CustomerMaster_Table()
      //
      // Open table CustomerMaster, if it exists. Otherwise create it
      // along with its indices and open it
      //

      static void Create_CustomerMaster_Table()
      {
         bool  do_create = false;

         // define table CustomerMaster
         Console.WriteLine("\ttable CustomerMaster");
         try
         {
            tableCustMast.Open("custmast", OPEN_MODE.NORMAL_OPEN);
         }
         catch (CTException)
         {
            // table does not exist
            do_create = true;
         }

         if (do_create)
         {
            try
            {
               // define table fields
               CTField field1 = tableCustMast.AddField("cm_custnumb", FIELD_TYPE.FSTRING, 4);
               tableCustMast.AddField("cm_custzipc", FIELD_TYPE.FSTRING, 9);
               tableCustMast.AddField("cm_custstat", FIELD_TYPE.FSTRING, 2);
               tableCustMast.AddField("cm_custratg", FIELD_TYPE.FSTRING, 1);
               tableCustMast.AddField("cm_custname", FIELD_TYPE.VSTRING, 47);
               tableCustMast.AddField("cm_custaddr", FIELD_TYPE.VSTRING, 47);
               tableCustMast.AddField("cm_custcity", FIELD_TYPE.VSTRING, 47);

               // define index
               CTIndex index1 = tableCustMast.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, false, false);
               index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG);

               // create table
               Console.WriteLine("\tCreate table...");
               tableCustMast.Create("custmast", CREATE_MODE.NORMAL_CREATE);

               // open table
               Console.WriteLine("\tOpen table...");
               tableCustMast.Open("custmast", OPEN_MODE.NORMAL_OPEN);
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

            do_create = false;
            try
            {
               tableCustMast.GetIndex("cm_custnumb_idx");
            }
            catch (CTException)
            {
               do_create = true;
            }

            if (do_create)
            {
               try
               {
                  CTField field1 = tableCustMast.GetField("cm_custnumb");
                  CTIndex index1 = tableCustMast.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, false, false);
                  index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG);
                  tableCustMast.Alter(ALTER_TABLE.NORMAL);
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

      static void Create_CustomerOrders_Table()
      {
         bool  do_create = false;

         // define table CustomerOrders
         Console.WriteLine("\ttable CustomerOrders");
         try
         {
            tableCustOrdr.Open("custordr", OPEN_MODE.NORMAL_OPEN);
         }
         catch (CTException)
         {
            // table does not exist
            do_create = true;
         }

         if (do_create)
         {
            try
            {
               // define table fields
               tableCustOrdr.AddField("co_ordrdate", FIELD_TYPE.DATE, 4);
               tableCustOrdr.AddField("co_promdate", FIELD_TYPE.DATE, 4);
               CTField field1 = tableCustOrdr.AddField("co_ordrnumb", FIELD_TYPE.FSTRING, 6);
               CTField field2 = tableCustOrdr.AddField("co_custnumb", FIELD_TYPE.FSTRING, 4);

               // define indices
               CTIndex index1 = tableCustOrdr.AddIndex("co_ordrnumb_idx", KEY_TYPE.LEADING_INDEX, false, false);
               index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG);
               CTIndex index2 = tableCustOrdr.AddIndex("co_custnumb_idx", KEY_TYPE.LEADING_INDEX, true, false);
               index2.AddSegment(field2, SEG_MODE.SCHSEG_SEG);

               // create table
               Console.WriteLine("\tCreate table...");
               tableCustOrdr.Create("custordr", CREATE_MODE.NORMAL_CREATE);

               // open table
               Console.WriteLine("\tOpen table...");
               tableCustOrdr.Open("custordr", OPEN_MODE.NORMAL_OPEN);
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

      static void Create_OrderItems_Table()
      {
         bool  do_create = false;

         // define table OrderItems
         Console.WriteLine("\ttable OrderItems");
         try
         {
            tableOrdrItem.Open("ordritem", OPEN_MODE.NORMAL_OPEN);
         }
         catch (CTException)
         {
            // table does not exist
            do_create = true;
         }

         if (do_create)
         {
            try
            {
               // define table fields
               CTField field1 = tableOrdrItem.AddField("oi_sequnumb", FIELD_TYPE.INT2, 2);
               tableOrdrItem.AddField("oi_quantity", FIELD_TYPE.INT2, 2);
               CTField field2 = tableOrdrItem.AddField("oi_ordrnumb", FIELD_TYPE.FSTRING, 6);
               CTField field3 = tableOrdrItem.AddField("oi_itemnumb", FIELD_TYPE.FSTRING, 5);

               // define indices
               CTIndex index1 = tableOrdrItem.AddIndex("oi_ordrnumb_idx", KEY_TYPE.LEADING_INDEX, false, false);
               index1.AddSegment(field2, SEG_MODE.SCHSEG_SEG);
               index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG);
               CTIndex index2 = tableOrdrItem.AddIndex("oi_itemnumb_idx", KEY_TYPE.LEADING_INDEX, true, false);
               index2.AddSegment(field3, SEG_MODE.SCHSEG_SEG);

               // create table
               Console.WriteLine("\tCreate table...");
               tableOrdrItem.Create("ordritem", CREATE_MODE.NORMAL_CREATE);

               // open table
               Console.WriteLine("\tOpen table...");
               tableOrdrItem.Open("ordritem", OPEN_MODE.NORMAL_OPEN);
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

      static void Create_ItemMaster_Table()
      {
         bool  do_create = false;

         // define table ItemMaster
         Console.WriteLine("\ttable ItemMaster");
         try
         {
            tableItemMast.Open("itemmast", OPEN_MODE.NORMAL_OPEN);
         }
         catch (CTException)
         {
            // table does not exist
            do_create = true;
         }

         if (do_create)
         {
            try
            {
               // define table fields
               tableItemMast.AddField("im_itemwght", FIELD_TYPE.INT4, 4);
               tableItemMast.AddField("im_itempric", FIELD_TYPE.MONEY, 4);
               CTField field1 = tableItemMast.AddField("im_itemnumb", FIELD_TYPE.FSTRING, 5);
               tableItemMast.AddField("im_itemdesc", FIELD_TYPE.VSTRING, 47);

               // define indices
               CTIndex index1 = tableItemMast.AddIndex("im_itemnumb_idx", KEY_TYPE.LEADING_INDEX, false, false);
               index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG);

               // create table
               Console.WriteLine("\tCreate table...");
               tableItemMast.Create("itemmast", CREATE_MODE.NORMAL_CREATE);

               // open table
               Console.WriteLine("\tOpen table...");
               tableItemMast.Open("itemmast", OPEN_MODE.NORMAL_OPEN);
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

      static void Check_Table_Mode(CTTable table)
      {
         try
         {
            // get table create mode
            CREATE_MODE mode = table.GetCreateMode();

            // check if table is under transaction processing control
            if ((mode & CREATE_MODE.TRNLOG_CREATE) != 0)
            {
               // change file mode to disable transaction processing
               mode ^= CREATE_MODE.TRNLOG_CREATE;
               table.UpdateCreateMode(mode);
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

      public struct CUSTOMER_DATA
      {
         // struct members
         public string number, zipcode, state, rating, name, address, city;
         // struct constructor
         public CUSTOMER_DATA(string number, string zipcode, string state, string rating, string name, string address, string city)
         {
            this.number = number;
            this.zipcode = zipcode;
            this.state = state;
            this.rating = rating;
            this.name = name;
            this.address = address;
            this.city = city;
         }
      };

      static void Add_CustomerMaster_Records()
      {
         CUSTOMER_DATA[] data = new CUSTOMER_DATA[4];
         data[0] = new CUSTOMER_DATA("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange");
         data[1] = new CUSTOMER_DATA("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford");
         data[2] = new CUSTOMER_DATA("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta");
         data[3] = new CUSTOMER_DATA("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia");
         int nRecords = data.Length;

         Delete_Records(recordCustMast);

         Console.WriteLine("\tAdd records in table CustomerMaster...");

         try
         {
            for (int i = 0; i < nRecords; i++)
            {
               recordCustMast.Clear();

               // populate record buffer with data
               recordCustMast.SetFieldAsString(0, data[i].number);
               recordCustMast.SetFieldAsString(1, data[i].zipcode);
               recordCustMast.SetFieldAsString(2, data[i].state);
               recordCustMast.SetFieldAsString(3, data[i].rating);
               recordCustMast.SetFieldAsString(4, data[i].name);
               recordCustMast.SetFieldAsString(5, data[i].address);
               recordCustMast.SetFieldAsString(6, data[i].city);

               // add record
               recordCustMast.Write();
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

      public struct ORDER_DATA
      {
         // struct members
         public string orderdate, promisedate, ordernum, customernum;
         // struct constructor
         public ORDER_DATA(string orderdate, string promisedate, string ordernum, string customernum)
         {
            this.orderdate = orderdate;
            this.promisedate = promisedate;
            this.ordernum = ordernum;
            this.customernum = customernum;
         }
      };

      static void Add_CustomerOrders_Records()
      {
         ORDER_DATA[] data = new ORDER_DATA[2];
         data[0] = new ORDER_DATA("09/01/2002", "09/05/2002",  "1",  "1001");
         data[1] = new ORDER_DATA("09/02/2002", "09/06/2002",  "2",  "1002");
         int nRecords = data.Length;

         CTDate   orderdate = new CTDate();
         CTDate   promisedate = new CTDate();

         Delete_Records(recordCustOrdr);

         Console.WriteLine("\tAdd records in table CustomerOrders...");

         try
         {
            for (int i = 0; i < nRecords; i++)
            {
               recordCustOrdr.Clear();

               orderdate.StringToDate(data[i].orderdate, DATE_TYPE.MDCY_DATE);
               promisedate.StringToDate(data[i].promisedate, DATE_TYPE.MDCY_DATE);
               // populate record buffer with data
               recordCustOrdr.SetFieldValue(0, orderdate);
               recordCustOrdr.SetFieldValue(1, promisedate);
               recordCustOrdr.SetFieldAsString(2, data[i].ordernum);
               recordCustOrdr.SetFieldAsString(3, data[i].customernum);

               // add record
               recordCustOrdr.Write();
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

      public struct ORDERITEM_DATA
      {
         // struct members
         public int sequencenum, quantity;
         public string ordernum, itemnum;
         // struct constructor
         public ORDERITEM_DATA(int sequencenum, int quantity, string ordernum, string itemnum)
         {
            this.sequencenum = sequencenum;
            this.quantity = quantity;
            this.ordernum = ordernum;
            this.itemnum = itemnum;
         }
      };

      static void Add_OrderItems_Records()
      {
         ORDERITEM_DATA[] data = new ORDERITEM_DATA[4];
         data[0] = new ORDERITEM_DATA(1,  2, "1",  "1");
         data[1] = new ORDERITEM_DATA(2,  1, "1",  "2");
         data[2] = new ORDERITEM_DATA(3,  1, "1",  "3");
         data[3] = new ORDERITEM_DATA(1,  3, "2",  "3");
         int nRecords = data.Length;

         Delete_Records(recordOrdrItem);

         Console.WriteLine("\tAdd records in table OrderItems...");

         try
         {
            for (int i = 0; i < nRecords; i++)
            {
               recordOrdrItem.Clear();

               // populate record buffer with data
               recordOrdrItem.SetFieldValue(0, data[i].sequencenum);
               recordOrdrItem.SetFieldValue(1, data[i].quantity);
               recordOrdrItem.SetFieldValue(2, data[i].ordernum);
               recordOrdrItem.SetFieldValue(3, data[i].itemnum);

               // add record
               recordOrdrItem.Write();
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

      public struct ITEM_DATA
      {
         // struct members
         public int weight;
         public CTMoney price;
         public string itemnum, description;
         // struct constructor
         public ITEM_DATA(int weight, CTMoney price, string itemnum, string description)
         {
            this.weight = weight;
            this.price = price;
            this.itemnum = itemnum;
            this.description = description;
         }
      };

      static void Add_ItemMaster_Records()
      {
         ITEM_DATA[] data = new ITEM_DATA[4];
         data[0] = new ITEM_DATA(10,  (CTMoney)1995, "1",  "Hammer");
         data[1] = new ITEM_DATA(3,   (CTMoney)999, "2", "Wrench");
         data[2] = new ITEM_DATA(4,   (CTMoney)1659, "3", "Saw");
         data[3] = new ITEM_DATA(1,   (CTMoney)398, "4", "Pliers");
         int nRecords = data.Length;

         Delete_Records(recordItemMast);

         Console.WriteLine("\tAdd records in table ItemMaster...");

         try
         {
            for (int i = 0; i < nRecords; i++)
            {
               recordItemMast.Clear();

               // populate record buffer with data
               recordItemMast.SetFieldValue(0, data[i].weight);
               recordItemMast.SetFieldValue(1, data[i].price);
               recordItemMast.SetFieldAsString(2, data[i].itemnum);
               recordItemMast.SetFieldAsString(3, data[i].description);

               // add record
               recordItemMast.Write();
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

      static void Delete_Records(CTRecord record)
      {
         bool found;

         Console.WriteLine("\tDelete records...");

         try
         {
            // read first record
            found = record.First();

            while (found)  // while records are found
            {
               // delete record
               record.Delete();
               // read next record
               found = record.Next();
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
      // This function handles unexpected exceptions. It displays an error message
      // allowing the user to acknowledge before terminating the application
      //

      static void Handle_Exception(CTException err)
      {
         Console.WriteLine("\nERROR: [{0}] - {1}", err.GetErrorCode(), err.GetErrorMsg());
         Console.WriteLine("*** Execution aborted *** ");
         Console.WriteLine("\nPress <ENTER> key to exit . . .");
         Console.ReadLine();
         Environment.Exit(1);
      }
   }
}

// end of Tutorial2.cs

            
