//
// JDBC_Tutorial1.java
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
//  2.  Add 1 table with some fields
//  3.  Populate the table with a few records
//  4.  Display the contents of the table
//

import java.sql.*;
import java.io.*;

public class JDBC_Tutorial1 {

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

         // create a statement handle
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
   // Create the table for containing a list of existing customers
   //

   private static void Define ()
   {
      System.out.println("DEFINE");

      try
      {
         stmt.executeUpdate("DROP TABLE ordritem");
      }
      catch (SQLException e)
      {
      }

      try
      {
         stmt.executeUpdate("DROP TABLE custordr");
      }
      catch (SQLException e)
      {
      }

      try
      {
         stmt.executeUpdate("DROP TABLE itemmast");
      }
      catch (SQLException e)
      {
      }

      try
      {
         stmt.executeUpdate("DROP TABLE custmast");
      }
      catch (SQLException e)
      {
      }

      try
      {
         // create table
         System.out.println("\tCreate table...");
         stmt.executeUpdate("CREATE TABLE custmast (" +
            "cm_custnumb CHAR(4), " +
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
   // Manage()
   //
   // This function performs simple record functions of add, delete and gets
   //

   private static void Manage ()
   {
      System.out.println("MANAGE");

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

   private static void Done ()
   {
      System.out.println("DONE");

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
   // Delete_Records()
   //
   // This function deletes all the records in the table
   //

   private static void Delete_Records ()
   {
      System.out.println("\tDelete records...");

      try
      {
         stmt.executeUpdate("DELETE FROM custmast");
      }
      catch (SQLException e)
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

   private static void Add_Records ()
   {
      System.out.println("\tAdd records...");

      String data[] = {
         "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
         "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
         "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
         "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
      };

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
   }


   //
   // Display_Records()
   //
   // This function displays the contents of a table.
   //

   private static void Display_Records ()
   {
      System.out.print("\tDisplay records...");

      try
      {
         // execute a query statement
         ResultSet rs = stmt.executeQuery ("SELECT * FROM custmast");

         // fetch and display each individual record
         while (rs.next()) {
            System.out.println("\n\t\t" + rs.getString(1) + "   " + rs.getString(5));
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
      int TABLE_ALREADY_EXISTS = -20041;
      int INDEX_ALREADY_EXISTS = -20028;

      if (se.getErrorCode() == TABLE_ALREADY_EXISTS ||
         se.getErrorCode() == INDEX_ALREADY_EXISTS)
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

/* end of JDBC_Tutorial1.java */
