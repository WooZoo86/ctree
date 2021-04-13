//
// Tutorial1.cs
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
//


using System;
using FairCom.CtreeDb;
using FairCom.CtreeDb.ENUMS;

namespace Tutorial1
{
	class Tutorial1
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
				// This section is only needed for the AppServer DLL model.
				bool AppServerModel = true;
				if (AppServerModel)
				{
					// Set c-tree database engine configuration file name.
					CTSession.SetConfigurationFile("ctsrvr.cfg");
					// Start c-tree database engine.
					CTSession.StartDatabaseEngine();
				}


				// allocate objects
				MySession = new CTSession(SESSION_TYPE.CTREE_SESSION);
				MyTable = new CTTable(MySession);
				MyRecord = new CTRecord(MyTable);
			}
			catch(CTException E)
			{
				Handle_Exception(E);
			}

			try
			{
				// connect to server
				Console.WriteLine("\tLogon to server...");
				MySession.Logon("FAIRCOMS", "ADMIN", "ADMIN");
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

		static void Define()
		{
			bool do_create = false;

			Console.WriteLine("DEFINE");

			try
			{
				Console.WriteLine("\tOpen table...");
				MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN);
			}
			catch (CTException)
			{
				// table does not exist. Try to create it
				do_create = true;
			}

			if (do_create)
			{
				// create the table
				Console.WriteLine("\tAdd fields...");
				try
				{
					MyTable.AddField("cm_custnumb", FIELD_TYPE.FSTRING, 4);
					MyTable.AddField("cm_custzipc", FIELD_TYPE.FSTRING, 9);
					MyTable.AddField("cm_custstat", FIELD_TYPE.FSTRING, 2);
					MyTable.AddField("cm_custrtng", FIELD_TYPE.FSTRING, 1);
					MyTable.AddField("cm_custname", FIELD_TYPE.VSTRING, 47);
					MyTable.AddField("cm_custaddr", FIELD_TYPE.VSTRING, 47);
					MyTable.AddField("cm_custcity", FIELD_TYPE.VSTRING, 47);

					Console.WriteLine("\tCreate table...");
					MyTable.Create("custmast", CREATE_MODE.NORMAL_CREATE);

					MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN);
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

		static void Manage()
		{
			Console.WriteLine("MANAGE");

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

				// This section is only needed for the AppServer DLL model.
				// Stop the AppServer DatabaseEngine
				bool AppServerModel = true;
				if (AppServerModel)
				{
					CTSession.StopDatabaseEngine();
				}

			}
			catch (CTException E)
			{
				Handle_Exception(E);
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
		// Delete_Records()
		//
		// This function deletes all the records in the table
		//

		static void Delete_Records()
		{
			bool  found;

			Console.WriteLine("\tDelete records...");

			try
			{
				// read first record
				found = MyRecord.First();

				while (found)  // while records are found
				{
					// delete record
					MyRecord.Delete();
					// read next record
					found = MyRecord.Next();
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

		static void Add_Records()
		{
			DATA_RECORD[] data = new DATA_RECORD[4];
			data[0] = new DATA_RECORD("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange");
			data[1] = new DATA_RECORD("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford");
			data[2] = new DATA_RECORD("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta");
			data[3] = new DATA_RECORD("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia");
			int   nRecords = data.Length;

			Console.WriteLine("\tAdd records...");

			try
			{
				for(int i = 0; i < nRecords; i++)
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

// end of Tutorial1.cs
