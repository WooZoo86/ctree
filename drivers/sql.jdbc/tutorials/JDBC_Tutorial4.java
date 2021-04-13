//
// JDBC_Tutorial4.java
//
// Public domain JDBC example
//
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
//
// The goal of this tutorial is to introduce the most basic JDBC API
// to accomplish creating and manipulating a table through the ctreeServer
//
// Functionally, this application will perform the following:
//  1.  Logon onto a session
//  2.  Create 4 tables each with an index
//  3.  Add records in multiple tables under transaction processing control
//  4.  Display the contents of the tables
//

import java.sql.*;
import java.io.*;

public class JDBC_Tutorial4 {

   static Connection conn;
   static Statement stmt;

   //
   // main()
   //
   // The main() function implements the concept of "init, define, manage
   // and you're done..."
   //

   public static void main (String[] args)
      throws java.io.IOException
   {

      Initialize();

      Define();

      Manage();

      Done();

      System.out.print("\nPress <ENTER> key to exit . . .");
      System.in.read();
      System.exit(0);
   }


   //
   // Initialize()
   //
   // Perform the minimum requirement of logging onto the c-tree Server
   //

   private static void Initialize ()
   {
      System.out.println("INIT");

      try
      {
         // load the driver
         Class.forName ("ctree.jdbc.ctreeDriver");

         // connect to server
         System.out.println("\tLogon to server...");
         conn = DriverManager.getConnection ("jdbc:ctree://localhost:6597/ctreeSQL", "ADMIN", "ADMIN");

         // disable commit after each single SQL statement
         conn.setAutoCommit(false);

         // create statement handles
         stmt = conn.createStatement();
      }
      catch (SQLException e)
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

   private static void Define ()
   {
      System.out.println("DEFINE");

      // delete tables ...
      Delete_Tables();
      // ...and re-create them with constraints
      Create_CustomerMaster_Table();
      Create_ItemMaster_Table();
      Create_CustomerOrders_Table();
      Create_OrderItems_Table();
      try
      {
         conn.commit();
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }


   //
   // Manage()
   //
   // Populates table and perform a simple query
   //

   private static void Manage ()
   {
      System.out.println("MANAGE");

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

   private static void Done ()
   {
      System.out.println("DONE");

      Delete_Tables();
      try
      {
         conn.commit();
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }

      try
      {
         stmt.close();
         // logout
         System.out.println("\tLogout...");
         conn.close();
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }


   //
   // Delete_Tables()
   //
   // This function removes all existing tables
   //

   private static void Delete_Tables ()
   {

      try
      {
         stmt.executeUpdate("DROP TABLE ordritem");
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
      try
      {
         stmt.executeUpdate("DROP TABLE custordr");
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
      try
      {
         stmt.executeUpdate("DROP TABLE custmast");
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
      try
      {
         stmt.executeUpdate("DROP TABLE itemmast");
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }


   //
   // Create_CustomerMaster_Table()
   //
   // Create the table CustomerMaster
   //

   private static void Create_CustomerMaster_Table ()
   {
      // define table CustomerMaster
      System.out.println("\ttable CustomerMaster");

      try
      {
         stmt.executeUpdate("CREATE TABLE custmast (" +
            "cm_custnumb CHAR(4) PRIMARY KEY, " +
            "cm_custzipc CHAR(9), " +
            "cm_custstat CHAR(2), " +
            "cm_custrtng CHAR(1), " +
            "cm_custname VARCHAR(47), " +
            "cm_custaddr VARCHAR(47), " +
            "cm_custcity VARCHAR(47))"
         );
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }



   //
   // Create_CustomerOrders_Table()
   //
   // Create the table CustomerOrders
   //

   private static void Create_CustomerOrders_Table ()
   {
      // define table CustomerOrders
      System.out.println("\ttable CustomerOrders");

      try
      {
         stmt.executeUpdate("CREATE TABLE custordr (" +
            "co_ordrdate DATE, " +
            "co_promdate DATE, " +
            "co_ordrnumb CHAR(6) PRIMARY KEY, " +
            "co_custnumb CHAR(4), " +
            "FOREIGN KEY (co_custnumb) REFERENCES custmast)"
         );
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }


   //
   // Create_OrderItems_Table()
   //
   // Create the table OrderItems
   //

   private static void Create_OrderItems_Table ()
   {
      // define table OrderItems
      System.out.println("\ttable OrderItems");

      try
      {
         stmt.executeUpdate("CREATE TABLE ordritem (" +
            "oi_sequnumb SMALLINT, " +
            "oi_quantity SMALLINT, " +
            "oi_ordrnumb CHAR(6), " +
            "oi_itemnumb CHAR(5), " +
            "FOREIGN KEY (oi_itemnumb) REFERENCES itemmast, " +
            "FOREIGN KEY (oi_ordrnumb) REFERENCES custordr)"
         );
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }


   //
   // Create_ItemMaster_Table()
   //
   // Create the table ItemMaster
   //

   private static void Create_ItemMaster_Table ()
   {
      // define table ItemMaster
      System.out.println("\ttable ItemMaster");

      try
      {
         stmt.executeUpdate("CREATE TABLE itemmast (" +
            "im_itemwght INTEGER, " +
            "im_itempric MONEY, " +
            "im_itemnumb CHAR(5) PRIMARY KEY, " +
            "im_itemdesc VARCHAR(47))"
         );
      }
      catch (SQLException e)
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

   private static void Add_CustomerMaster_Records ()
   {
      String data[] = {
         "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
         "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
         "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
         "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
      };

      System.out.println("\tAdd records in table CustomerMaster...");

      try
      {
         // add one record at time to table
         for (int i = 0; i < data.length; i++) {
            stmt.executeUpdate("INSERT INTO custmast VALUES " + data[i]);
         }
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
      try
      {
         conn.commit();
      }
      catch (SQLException e)
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

   private static void Add_ItemMaster_Records ()
   {
      String data[] = {
         "(10,19.95,'1','Hammer')",
         "(3,  9.99,'2','Wrench')",
         "(4, 16.59,'3','Saw')",
         "(1,  3.98,'4','Pliers')"
      };

      System.out.println("\tAdd records in table ItemMaster...");

      try
      {
         // add one record at time to table
         for (int i = 0; i < data.length; i++) {
            stmt.executeUpdate("INSERT INTO itemmast VALUES " + data[i]);
         }
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
      try
      {
         conn.commit();
      }
      catch (SQLException e)
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

   private static void Add_Transactions()
   {
      int   i, j = 0;
      String[][] orders = {
         { "09/01/2002", "09/05/2002", "1", "1001" },
         { "09/02/2002", "09/06/2002", "2", "9999" },  // bad customer number
         { "09/22/2002", "09/26/2002", "3", "1003" }
      };

      String[][] items = {
         { "1", "1", "2", "1" },
         { "1", "2", "1", "2" },
         { "2", "1", "1", "3" },
         { "2", "2", "3", "4" },
         { "3", "1", "2", "3" },
         { "3", "2", "2", "99"}  // bad item number
      };

      System.out.println("\tAdd transaction records...");

      for (i = 0; i < orders.length; i++)
      {
         try
         {
            // add order record
            stmt.executeUpdate("INSERT INTO custordr VALUES (" +
               "'" + orders[i][0] + "'," +
               "'" + orders[i][1] + "'," +
               "'" + orders[i][2] + "'," +
               "'" + orders[i][3] + "')");
         }
         catch (SQLException e)
         {
            Handle_Exception(e);
         }

         // process order items
         while (items[j][0].compareTo(orders[i][2]) == 0)
         {
            try
            {
               // add item record
               stmt.executeUpdate("INSERT INTO ordritem VALUES (" +
                  items[j][1] + "," +
                  items[j][2] + "," +
                  "'" + items[j][0] + "'," +
                  "'" + items[j][3] + "')");
            }
            catch (SQLException e)
            {
               Handle_Exception(e);
            }

            // bump to next item
            j++;

            // exit the while loop on last item
            if (j >= items.length)
               break;
         }
         
         try
         {
            conn.commit();
         }
         catch (SQLException e)
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

   private static void Display_CustomerOrders ()
   {
      System.out.println("\n\tCustomerOrders Table...");

      try
      {
         // execute a query statement
         ResultSet rs = stmt.executeQuery ("SELECT * FROM custordr");

         // fetch and display each individual record
         while (rs.next()) {
            System.out.println("\t   " + rs.getString(3) + "   " + rs.getString(4));
         }
         rs.close();
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }


   //
   // Display_OrderItems()
   //
   // This function displays the contents of OrderItems table.
   //

   private static void Display_OrderItems ()
   {
      System.out.println("\n\tOrderItems Table...");

      try
      {
         // execute a query statement
         ResultSet rs = stmt.executeQuery ("SELECT * FROM ordritem");

         // fetch and display each individual record
         while (rs.next()) {
            System.out.println("\t   " + rs.getString(3) + "   " + rs.getString(4));
         }
         rs.close();
      }
      catch (SQLException e)
      {
         Handle_Exception(e);
      }
   }


   //
   // Handle_Exception()
   //
   // This function handles unexpected C++ exceptions. It displays an error message
   // allowing the user to acknowledge before terminating the application
   //

   private static void Handle_Exception (Exception e)
   {
      System.err.println("Exception: " + e.getMessage());
      Error_Exit();
   }

   private static void Handle_Exception (SQLException se)
   {
      int TABLE_NOT_FOUND = -20005;
      int CONSTRAINT_VIOLATION = -20116;

      if (se.getErrorCode() == TABLE_NOT_FOUND ||
         se.getErrorCode() == CONSTRAINT_VIOLATION)
         return;

      // loop through the SQL Exceptions
      while (se != null)
      {
         System.err.println("SQL Exception: " + se.getErrorCode() + " - " + se.getMessage()) ;
         if (se.getErrorCode() == 26003)
            System.err.println("Perhaps your c-tree server is not running?");
         se = se.getNextException();
      }
      Error_Exit();
   }

   private static void Error_Exit ()
   {
      System.err.print("*** Execution aborted *** \nPress <ENTER> key to exit...");
      try
      {
         System.in.read();
      }
      catch (IOException e) {;}
      System.exit(1);
   }

}

/* end of JDBC_Tutorial4.java */
