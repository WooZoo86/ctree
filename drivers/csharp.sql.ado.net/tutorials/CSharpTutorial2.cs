//
// CSharpTutorial2.cs
//
// Public domain C# ADO.NET example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic ADO.NET API
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
using System.Collections;
using Ctree.Data.SqlClient;

namespace CSharpTutorial
{
   class Tutorial2
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

         Console.WriteLine("\n\tQuery Results...");

         try
         {
            cmd.CommandText = "SELECT cm_custname, SUM(im_itempric * oi_quantity) " +
               "FROM custmast, custordr, ordritem, itemmast " +
               "WHERE co_custnumb = cm_custnumb AND co_ordrnumb = oi_ordrnumb AND oi_itemnumb = im_itemnumb " +
               "GROUP BY co_ordrnumb, cm_custname";

            // get a resultset
            rdr = (CtreeSqlDataReader)cmd.ExecuteReader();

            // read the returned resultset
            while (rdr.Read())
            {
               Console.WriteLine("\t\t{0:-20s} \t{1}", rdr.GetString(0), rdr.GetString(1));
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

         try
         {
            cmd.CommandText = "CREATE UNIQUE INDEX cm_custnumb_idx ON custmast (cm_custnumb)";
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
                "co_ordrdate DATE," +
                "co_promdate DATE," +
                "co_ordrnumb CHAR(6)," +
                "co_custnumb CHAR(4))";
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
            cmd.CommandText = "CREATE UNIQUE INDEX co_ordrnumb_idx ON custordr (co_ordrnumb)";
            cmd.ExecuteNonQuery();
            cmd.CommandText = "CREATE INDEX co_custnumb_idx ON custordr (co_custnumb)";
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
                "oi_sequnumb SMALLINT," +
                "oi_quantity SMALLINT," +
                "oi_ordrnumb CHAR(6)," +
                "oi_itemnumb CHAR(5))";
            cmd.ExecuteNonQuery();
         }
         catch (CtreeSqlException e)
         {
            Handle_Exception(e);
         }
         catch (Exception e)
         {
            Console.WriteLine("Application Exception : " + e.Message + "\n");
         }

         try
         {
            cmd.CommandText = "CREATE UNIQUE INDEX oi_ordrnumb_idx ON ordritem (oi_ordrnumb, oi_sequnumb)";
            cmd.ExecuteNonQuery();
            cmd.CommandText = "CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb)";
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
                "im_itemwght INTEGER," +
                "im_itempric MONEY," +
                "im_itemnumb CHAR(5)," +
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

         try
         {
            cmd.CommandText = "CREATE INDEX im_itemnumb_idx ON itemmast (im_itemnumb)";
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

         Delete_Records("custmast");

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
      // Add_CustomerOrders_Records()
      //
      // This function adds records to table CustomerOrders from an
      // array of strings
      //

      static void Add_CustomerOrders_Records()
      {
         String[] data = {
            "('09/01/2002','09/05/2002','1','1001')",
            "('09/02/2002','09/06/2002','2','1002')"
         };

         Console.WriteLine("\tAdd records in table CustomerOrders...");

         Delete_Records("custordr");

         try
         {
            // add one record at time to table
            for (int i = 0; i < data.Length; i++)
            {
               cmd.CommandText = "INSERT INTO custordr VALUES " + data[i];
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
      // Add_OrderItems_Records()
      //
      // This function adds records to table OrderItems from an
      // array of strings
      //

      static void Add_OrderItems_Records()
      {
         String[] data = {
            "(1,2,'1','1')",
            "(2,1,'1','2')",
            "(3,1,'1','3')",
            "(1,3,'2','3')"
         };

         Console.WriteLine("\tAdd records in table OrderItems...");

         Delete_Records("ordritem");

         try
         {
            // add one record at time to table
            for (int i = 0; i < data.Length; i++)
            {
               cmd.CommandText = "INSERT INTO ordritem VALUES " + data[i];
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

         Delete_Records("itemmast");

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
      // Delete_Records()
      //
      // This function deletes all the records in a tables
      //

      static void Delete_Records(String Table)
      {
         Console.WriteLine("\tDelete records...");

         try
         {
            cmd.CommandText = "DELETE FROM " + Table;
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
         int TABLE_ALREADY_EXISTS = -20041;
         int INDEX_ALREADY_EXISTS = -20028;

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

/* end of CSharpTutorial2.cs */

