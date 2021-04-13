//
// Tutorial3.cs
//
// Public domain C# ISAM .NET example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic ISAM .NET API
// to accomplish creating and manipulating a table through the ctreeServer
//
// Functionally, this application will perform the following:
//  1.  Logon onto a session
//  2.  Add 1 table with some fields
//  3.  Populate the table with a few records
//  4.  Display the contents of the table
//  5.  Update one record under locking control
//


using System;
using FairCom.CtreeDb;
using FairCom.CtreeDb.ENUMS;

namespace Tutorial3
{
	class Tutorial3
	{
		static CTSession MySession;
		static CTTable MyTable;
		static CTRecord MyRecord;


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
            // allocate objects
            MySession = new CTSession(SESSION_TYPE.CTREE_SESSION);
            MyTable = new CTTable(MySession);
            MyRecord = new CTRecord(MyTable);
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
      }


      //
      // Manage()
      //
      // This function performs record adds and updates using locking
      //
    
      static void Manage()
		{
			Console.WriteLine("MANAGE");

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

      static void Done()
      {
         Console.WriteLine("DONE");

         try
         {
            // close table
            Console.WriteLine("\tClose table...");
            MyTable.Close();

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
         bool do_create = false;

         // define table CustomerMaster
         Console.WriteLine("\ttable CustomerMaster");
         try
         {
            MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN);
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
               CTField field1 = MyTable.AddField("cm_custnumb", FIELD_TYPE.FSTRING, 4);
               MyTable.AddField("cm_custzipc", FIELD_TYPE.FSTRING, 9);
               MyTable.AddField("cm_custstat", FIELD_TYPE.FSTRING, 2);
               MyTable.AddField("cm_custratg", FIELD_TYPE.FSTRING, 1);
               MyTable.AddField("cm_custname", FIELD_TYPE.VSTRING, 47);
               MyTable.AddField("cm_custaddr", FIELD_TYPE.VSTRING, 47);
               MyTable.AddField("cm_custcity", FIELD_TYPE.VSTRING, 47);

               // define index
               CTIndex index1 = MyTable.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, false, false);
               index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG);

               // create table
               Console.WriteLine("\tCreate table...");
               MyTable.Create("custmast", CREATE_MODE.NORMAL_CREATE);

               // open table
               Console.WriteLine("\tOpen table...");
               MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN);
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

            do_create = false;
            try
            {
               MyTable.GetIndex("cm_custnumb_idx");
            }
            catch (CTException)
            {
               do_create = true;
            }

            if (do_create)
            {
               try
               {
                  CTField field1 = MyTable.GetField("cm_custnumb");
                  CTIndex index1 = MyTable.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, false, false);
                  index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG);
                  MyTable.Alter(ALTER_TABLE.NORMAL);
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

      public struct DATA_RECORD
      {
         // struct members
         public string number, zipcode, state, rating, name, address, city;
         // struct constructor
         public DATA_RECORD(string number, string zipcode, string state, string rating, string name, string address, string city)
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
         DATA_RECORD[] data = new DATA_RECORD[4];
         data[0] = new DATA_RECORD("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange");
         data[1] = new DATA_RECORD("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford");
         data[2] = new DATA_RECORD("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta");
         data[3] = new DATA_RECORD("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia");
         int   nRecords = data.Length;

         Delete_Records(MyRecord);

         Console.WriteLine("\tAdd records...");

         try
         {
            for (int i = 0; i < nRecords; i++)
            {
               MyRecord.Clear();

               // populate record buffer with data
               MyRecord.SetFieldAsString(0, data[i].number);
               MyRecord.SetFieldAsString(1, data[i].zipcode);
               MyRecord.SetFieldAsString(2, data[i].state);
               MyRecord.SetFieldAsString(3, data[i].rating);
               MyRecord.SetFieldAsString(4, data[i].name);
               MyRecord.SetFieldAsString(5, data[i].address);
               MyRecord.SetFieldAsString(6, data[i].city);

               // add record
               MyRecord.Write();
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

      static void Delete_Records(CTRecord record)
      {
         bool found;

         Console.WriteLine("\tDelete records...");

         try
         {
            // enable session-wide lock flag
            MySession.Lock(LOCK_MODE.WRITE_BLOCK_LOCK);

            // read first record
            found = record.First();

            while (found)  // while records are found
            {
               // delete record
               record.Delete();
               // read next record
               found = record.Next();
            }

            // reset session-wide locks
            MySession.Unlock();
         }
         catch (CTException E)
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

      static void Display_Records()
      {
         bool found;
         string custnumb;
         string custname;

         Console.Write("\tDisplay records...");

         try
         {
            // read first record
            found = MyRecord.First();

            while (found)
            {
               custnumb = MyRecord.GetFieldAsString(0);
               custname = MyRecord.GetFieldAsString(4);

               Console.WriteLine("\n\t\t{0,-8}{1,-20}", custnumb, custname);

               // read next record
               found = MyRecord.Next();
            }
         }

         catch (CTException E)
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

      static void Update_CustomerMaster_Record()
      {
         Console.WriteLine("\tUpdate Record...");

         try
         {
            // enable session-wide lock flag
            MySession.Lock(LOCK_MODE.WRITE_BLOCK_LOCK);

            MyRecord.Clear();
            MyRecord.SetFieldAsString(0, "1003");
            // find record by customer number
            if (MyRecord.Find(FIND_MODE.EQ))
            {
               MyRecord.SetFieldAsString(4, "KEYON DOOLING");
               // rewrite record
               MyRecord.Write();

               Console.WriteLine("\tPress <ENTER> key to unlock");
               Console.ReadLine();
            }

            // reset session-wide locks
            MySession.Unlock();
         }
         catch(CTException E)
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

// end of Tutorial3.cs


