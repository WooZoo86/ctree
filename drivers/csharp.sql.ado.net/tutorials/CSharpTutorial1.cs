//
// CSharpTutorial1.cs
//
// Public domain C# ADO.NET example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic ADO.NET API
// to accomplish creating and manipulating a table through the ctreeServer
//
// Functionally, this application will perform the following:
//  1.  Logon onto a session
//  2.  Add 1 table with some fields
//  3.  Populate the table with a few records
//  4.  Display the contents of the table
//

using System;
using Ctree.Data.SqlClient;

namespace CSharpTutorial
{
   class Tutorial1
   {
      // declare connection, command and reader objects
      static CtreeSqlConnection conn;
      static CtreeSqlCommand cmd;
      static CtreeSqlDataReader rdr;

      //
      // main()
      //
      // The main() function implements the concept of "init, define, manage
      // and you're done..."
      //

      static void Main()
      {
         Initialize();

         Define();

         Manage();

         Done();

         Console.Write("\nPress <ENTER> key to exit . . .");
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
            // initialize connection object
            conn = new CtreeSqlConnection();
            conn.ConnectionString = "UID=ADMIN;PWD=ADMIN;Database=CtreeSQL;Server=localhost;Service=6597;";

            // initialize command object
            cmd = new CtreeSqlCommand();
            cmd.CommandType = System.Data.CommandType.Text;
            cmd.Connection = conn;
            cmd.Transaction = null;

            // connect to server
            Console.WriteLine("\tLogon to server...");
            conn.Open();
         }
         catch (CtreeSqlException e)
         {
            Handle_Exception(e);
         }
         catch (Exception e)
         {
            Handle_Exception(e);
         }
      }


      //
      // Define()
      //
      // Create the table for containing a list of existing customers
      //

      static void Define()
      {
         Console.WriteLine("DEFINE");

         try
         {
            // create table
            Console.WriteLine("\tCreate table...");
            cmd.CommandText = "CREATE TABLE custmast (" +
               "cm_custnumb CHAR(4)," +
               "cm_custzipc CHAR(9)," +
               "cm_custstat CHAR(2)," +
               "cm_custrtng CHAR(1)," +
               "cm_custname VARCHAR(47)," +
               "cm_custaddr VARCHAR(47)," +
               "cm_custcity VARCHAR(47))";
            cmd.ExecuteNonQuery();
         }
         catch (CtreeSqlException e)
         {
            Handle_Exception(e);
         }
         catch (Exception e)
         {
            Handle_Exception(e);
         }
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
            // logout
            Console.WriteLine("\tLogout...");
            conn.Close();
         }
         catch (CtreeSqlException e)
         {
            Handle_Exception(e);
         }
         catch (Exception e)
         {
            Handle_Exception(e);
         }
      }


      //
      // Delete_Records()
      //
      // This function deletes all the records in the table
      //

      static void Delete_Records()
      {
         Console.WriteLine("\tDelete records...");

         try
         {
            cmd.CommandText = "DELETE FROM custmast";
            cmd.ExecuteNonQuery();
         }
         catch (CtreeSqlException e)
         {
            Handle_Exception(e);
         }
         catch (Exception e)
         {
            Handle_Exception(e);
         }
      }


      //
      // Add_Records()
      //
      // This function adds records to a table in the database from an
      // array of strings
      //

      static void Add_Records()
      {
         String[] data = {
            "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
            "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
            "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
            "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
         };

         Console.WriteLine("\tAdd records...");

         try
         {
            // add one record at time to table
            for (int i = 0; i < data.Length; i++)
            {
               cmd.CommandText = "INSERT INTO custmast VALUES " + data[i];
               cmd.ExecuteNonQuery();
            }
         }
         catch (CtreeSqlException e)
         {
            Handle_Exception(e);
         }
         catch (Exception e)
         {
            Handle_Exception(e);
         }
      }


      //
      // Display_Records()
      //
      // This function displays the contents of a table.
      //

      static void Display_Records()
      {
         Console.Write("\tDisplay records...");

         try
         {
            cmd.CommandText = "SELECT * FROM custmast";

            // get a resultset
            rdr = (CtreeSqlDataReader)cmd.ExecuteReader();

            // read the returned resultset
            while (rdr.Read())
            {
               Console.WriteLine("\n\t\t{0}   {1}", rdr.GetString(0), rdr.GetString(4));
            }
            // close the reader
            rdr.Close();
         }
         catch (CtreeSqlException e)
         {
            Handle_Exception(e);
         }
         catch (Exception e)
         {
            Handle_Exception(e);
         }
      }


      //
      // Handle_Exception()
      //
      // This function handles unexpected exceptions. It displays an error message
      // allowing the user to acknowledge before terminating the application
      //

      static void Handle_Exception(Exception e)
      {
         Console.WriteLine("Error: " + e.Message);
         Error_Exit();
      }

      static void Handle_Exception(CtreeSqlException e)
      {
         int TABLE_ALREADY_EXISTS =  -20041;
         int INDEX_ALREADY_EXISTS =  -20028;

         if (e.ErrorNumber == TABLE_ALREADY_EXISTS ||
            e.ErrorNumber == INDEX_ALREADY_EXISTS)
            return;
         else
         {
            Console.WriteLine("Error: " + e.ErrorNumber + " - " + e.ErrorMessage);
            if (e.ErrorNumber == -30096 || e.ErrorNumber == -20212)
               Console.WriteLine("Perhaps your c-tree server is not running?");
         }
         Error_Exit();
      }

      static void Error_Exit()
      {
         Console.WriteLine("*** Execution aborted *** \nPress <ENTER> key to exit...");
         Console.ReadLine();
         Environment.Exit(1);
      }
   }
}

/* end of CSharpTutorial1.cs */

