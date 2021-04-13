//
// CSharpTutorial4.cs
//
// Public domain C# ADO.NET example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic ADO.NET API
// to accomplish creating and manipulating a table through the ctreeServer
//
//  1.  Logon onto a session
//  2.  Create 4 tables each with an index
//  3.  Add records in multiple tables under transaction processing control
//  4.  Display the contents of the tables

using System;
using System.Collections;
using Ctree.Data.SqlClient;

namespace CSharpTutorial
{
   class Tutorial4
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
            conn.ConnectionString = "UID=ADMIN;PWD=ADMIN;Database=CtreeSql;Server=localhost;Service=6597;";

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
      // Create the tables
      //

      static void Define()
      {
         Console.WriteLine("DEFINE");

         // delete tables ...
         Delete_Tables();
         // ...and re-create them with constraints
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
         Console.WriteLine("MANAGE");

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

      static void Done()
      {
         Console.WriteLine("DONE");

         Delete_Tables();

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
      // Delete_Tables()
      //
      // This function removes all existing tables
      //

      static void Delete_Tables()
      {

         try
         {
            cmd.CommandText = "DROP TABLE ordritem";
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
         try
         {
            cmd.CommandText = "DROP TABLE custordr";
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
         try
         {
            cmd.CommandText = "DROP TABLE custmast";
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
         try
         {
            cmd.CommandText = "DROP TABLE itemmast";
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
      // Create_CustomerMaster_Table()
      //
      // Create the table CustomerMaster
      //

      static void Create_CustomerMaster_Table()
      {
         Console.WriteLine("\ttable CustomerMaster...");

         try
         {
            cmd.CommandText = "CREATE TABLE custmast (" +
               "cm_custnumb CHAR(4) PRIMARY KEY, " +
               "cm_custzipc CHAR(9), " +
               "cm_custstat CHAR(2), " +
               "cm_custrtng CHAR(1), " +
               "cm_custname VARCHAR(47), " +
               "cm_custaddr VARCHAR(47), " +
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
      // Create_CustomerOrders_Table()
      //
      // Create the table CustomerOrders
      //

      static void Create_CustomerOrders_Table()
      {
         Console.WriteLine("\ttable CustomerOrders...");

         try
         {
            cmd.CommandText = "CREATE TABLE custordr (" +
               "co_ordrdate DATE, " +
               "co_promdate DATE, " +
               "co_ordrnumb CHAR(6) PRIMARY KEY, " +
               "co_custnumb CHAR(4), " +
               "FOREIGN KEY (co_custnumb) REFERENCES custmast)";
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
      // Create_OrderItems_Table()
      //
      // Create the table OrderItems
      //

      static void Create_OrderItems_Table()
      {
         Console.WriteLine("\ttable OrderItems...");

         try
         {
            cmd.CommandText = "CREATE TABLE ordritem (" +
               "oi_sequnumb SMALLINT, " +
               "oi_quantity SMALLINT, " +
               "oi_ordrnumb CHAR(6), " +
               "oi_itemnumb CHAR(5), " +
               "FOREIGN KEY (oi_itemnumb) REFERENCES itemmast, " +
               "FOREIGN KEY (oi_ordrnumb) REFERENCES custordr)";
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
      // Create_ItemMaster_Table()
      //
      // Create the table ItemMaster
      //

      static void Create_ItemMaster_Table()
      {
         Console.WriteLine("\ttable ItemMaster...");

         try
         {
            cmd.CommandText = "CREATE TABLE itemmast (" +
               "im_itemwght INTEGER, " +
               "im_itempric MONEY, " +
               "im_itemnumb CHAR(5) PRIMARY KEY, " +
               "im_itemdesc VARCHAR(47))";
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
      // Add_CustomerMaster_Records()
      //
      // This function adds records to table CustomerMaster from an
      // array of strings
      //

      static void Add_CustomerMaster_Records()
      {
         String[] data = {
            "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
            "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
            "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
            "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
         };

         Console.WriteLine("\tAdd records in table CustomerMaster...");

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
      // Add_ItemMaster_Records()
      //
      // This function adds records to table ItemMaster from an
      // array of strings
      //

      static void Add_ItemMaster_Records()
      {
         String[] data = {
            "(10,19.95,'1','Hammer')",
            "(3,  9.99,'2','Wrench')",
            "(4, 16.59,'3','Saw')",
            "(1,  3.98,'4','Pliers')"
         };

         Console.WriteLine("\tAdd records in table ItemMaster...");

         try
         {
            // add one record at time to table
            for (int i = 0; i < data.Length; i++)
            {
               cmd.CommandText = "INSERT INTO itemmast VALUES " + data[i];
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
      // Add_Transactions()
      //
      // Add an Order and associated Items "as a transaction" to their
      // respective tables.  A transaction is committed or aborted if the
      // customer number on the order is confirmed valid.  Likewise each
      // item in the order is verified to be a valid item.
      //

      static void Add_Transactions()
      {
         String[,] orders = {
            { "09/01/2002", "09/05/2002", "1", "1001" },
            { "09/02/2002", "09/06/2002", "2", "9999" },  // bad customer number
            { "09/22/2002", "09/26/2002", "3", "1003" }
         };

         String[,] items = {
            { "1", "1", "2", "1" },
            { "1", "2", "1", "2" },
            { "2", "1", "1", "3" },
            { "2", "2", "3", "4" },
            { "3", "1", "2", "3" },
            { "3", "2", "2", "99"}  // bad item number
         };

         Console.WriteLine("\tAdd transaction records...");

         for (int i = 0, j = 0; i < orders.GetLength(0); i++)
         {
            try
            {
               cmd.Transaction = conn.BeginTransaction();
               cmd.CommandText = "INSERT INTO custordr VALUES (" +
                  "'" + orders[i, 0] + "', " +
                  "'" + orders[i, 1] + "', " +
                  "'" + orders[i, 2] + "', " +
                  "'" + orders[i, 3] + "')";
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

            // process order items
            while (items[j, 0].CompareTo(orders[i, 2]) == 0)
            {
               try
               {
                  // add item record
                  cmd.CommandText = "INSERT INTO ordritem VALUES (" +
                     items[j, 1] + ", " +
                     items[j, 2] + ", " +
                     "'" + items[j, 0] + "', " +
                     "'" + items[j, 3] + "')";
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

               // bump to next item
               j++;

               // exit the while loop on last item
               if (j >= items.GetLength(0))
                  break;
            }

            try
            {
               cmd.Transaction.Commit();
            }
            catch (CtreeSqlException e)
            {
               Handle_Exception(e);
               cmd.Transaction.Rollback();
            }
            catch (Exception e)
            {
               Handle_Exception(e);
            }
         }
      }


      //
      // Display_CustomerOrders()
      //
      // This function displays the contents of CustomerOrders table.
      //

      static void Display_CustomerOrders()
      {
         Console.WriteLine("\n\tCustomerOrders Table...");

         try
         {
            // execute a query statement
            cmd.CommandText = "SELECT * FROM custordr";
            rdr = (CtreeSqlDataReader)cmd.ExecuteReader();

            // fetch and display each individual record
            while (rdr.Read())
            {
               Console.WriteLine("\t   {0}   {1}", rdr.GetString(2), rdr.GetString(3));
            }
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
      // Display_OrderItems()
      //
      // This function displays the contents of OrderItems table.
      //

      static void Display_OrderItems()
      {
         Console.WriteLine("\n\tOrderItems Table...");

         try
         {
            // execute a query statement
            cmd.CommandText = "SELECT * FROM ordritem";
            rdr = (CtreeSqlDataReader)cmd.ExecuteReader();

            // fetch and display each individual record
            while (rdr.Read())
            {
               Console.WriteLine("\t   {0}   {1}", rdr.GetString(2), rdr.GetString(3));
            }
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
         int TABLE_NOT_FOUND = -20005;
         int CONSTRAINT_VIOLATION = -20116;

         if (e.ErrorNumber == TABLE_NOT_FOUND ||
            e.ErrorNumber == CONSTRAINT_VIOLATION)
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

/* end of CSharpTutorial4.cs */

