<?php
   // PHP_Tutorial1.php
   //
   // Public domain PHP example
   //
   // FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
   //
   // The goal of this tutorial is to introduce the most basic PHP API
   // to accomplish creating and manipulating a table through the ctreeServer
   //
   // Functionally, this application will perform the following:
   //  1.  Logon onto a session
   //  2.  Add 1 table with some fields
   //  3.  Populate the table with a few records
   //  4.  Display the contents of the table
   //

   print("<html>\n");
   print("<head>\n");
   print("\t<title>PHP Tutorial 1</title>\n");
   print("</head>\n");
   print("<body>\n");

   //
   // Implementation of the concept of "init, define, manage and you're done..."
   //

   $session = Initialize();
   Defines($session);
   Manage($session);
   Done($session);


   //
   // Initialize()
   //
   // Perform the minimum requirement of logging onto the c-tree Server
   //

   function Initialize() {
      print("\t<h4>INIT</h4>\n");

      // connect to server
      print("\t\tLogon to server...<br>\n");
      $ses = ctsql_connect("localhost:ctreeSQL", "admin", "ADMIN");
      if (!$ses)
         Handle_Error("ctsql_connect()");

      return ($ses);
   }


   //
   // Define()
   //
   // Create the table for containing a list of existing customers
   //
   
   function Defines($ses) {
      print("\t<h4>DEFINE</h4>\n");

      // create table
      print("\t\tCreate table...<br>\n");
      $qry = ctsql_query(
         "CREATE TABLE custmast ( 
            cm_custnumb CHAR(4), 
            cm_custzipc CHAR(9), 
            cm_custstat CHAR(2), 
            cm_custrtng CHAR(1), 
            cm_custname VARCHAR(47), 
            cm_custaddr VARCHAR(47), 
            cm_custcity VARCHAR(47))",
         $ses);
      if (!$qry)
         Handle_Error("ctsql_query(CREATE TABLE)");

      if (!ctsql_commit($ses))
         Handle_Error("ctsql_commit()");
   }
   

   //
   // Manage()
   //
   // This function performs simple record functions of add, delete and gets
   //

   function Manage($ses) {
      print("\t<h4>MANAGE</h4>\n");
      
      // delete any existing records
      Delete_Records($ses);

      // populate the table with data
      Add_Records($ses);

      // display contents of table
      Display_Records($ses);
   }

   
   //
   // Done()
   //
   // This function handles the housekeeping of closing, freeing,
   // disconnecting and logging out of the database
   //

   function Done ($ses) {
      print("\t<h4>DONE</h4>\n");

      // logout
      print("\t\tLogout...<br>\n");
      ctsql_close($ses);
   }


   //
   // Delete_Records()
   //
   // This function deletes all the records in the table
   //
   
   function Delete_Records ($ses) {
      print("\t\tDelete records...<br>\n");

      $qry = ctsql_query("DELETE FROM custmast", $ses);
      if (!$qry)
         if (100 == ctsql_errno())
            return;
         else
            Handle_Error("ctsql_query(DELETE)");

      if (!ctsql_commit($ses))
         Handle_Error("ctsql_commit()");
   }


   //
   // Add_Records()
   //
   // This function adds records to a table in the database from an
   // array of strings
   //

   function Add_Records ($ses) {
      print("\t\tAdd records...<br>\n");

      $data = array(
         "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
         "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
         "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
         "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
      );

      foreach ($data as $values) {
         $qry = ctsql_query("INSERT INTO custmast VALUES $values", $ses);
         if (!$qry)
            Handle_Error("ctsql_query(INSERT)");
      }

      if (!ctsql_commit($ses))
         Handle_Error("ctsql_commit()");
   }


   //
   // Display_Records()
   //
   // This function displays the contents of a table.
   //

   function Display_Records ($ses) {
      print("\t\tDisplay records...<br>\n");

      $qry = ctsql_query("SELECT cm_custnumb \"Number\", cm_custname \"Name\" FROM custmast", $ses);
      if (!is_resource($qry))
         Handle_Error("ctsql_query(SELECT)");
      else {
         print("\t\t<TABLE border=1>\n\t\t\t<TR><TH>Number</TH><TH>Name</TH></TR>\n");

         while ($values = ctsql_fetch_row($qry)) {
            print("\t\t\t<TR>");
            foreach ($values as $content) {
               if (is_null($content))
                  print ("<TD>NULL</TD>");
               else
                  print ("<TD>$content</TD>");
            }
            print("</TR>\n");
         }

         print("\t\t</TABLE>\n");

         if (ctsql_errno())
            Handle_Error("ctsql_fetch_row()");

         ctsql_free_result($qry);
      }
   }


   //
   // Handle_Error()
   //
   // General error routine that retrieves and displays specific SQL Error
   // before exiting the tutorial.  If the error returned indicates an object
   // already exists, execution is returned to the calling function.
   //

   function Handle_Error($msg) {
      $TABLE_ALREADY_EXISTS = -20041;
      $INDEX_ALREADY_EXISTS = -20028;

      $err = ctsql_errno();
      if ($err == $TABLE_ALREADY_EXISTS || $err == $INDEX_ALREADY_EXISTS)
         return;

      print("$msg - SQL ERROR: [$err] - " . ctsql_error() . " <br>\n");
      print("*** Execution aborted *** <br>\n");
      exit();
   }

   print("</body>\n");
   print("</html>\n");

// end of PHP_Tutorial2.php
?>
