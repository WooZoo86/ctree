<?php 
// PHP_Tutorial3.php
 
// Public domain PHP example using PDO
 
// FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA

// The goal of this tutorial is to introduce the most basic PHP API
// to accomplish creating and manipulating a table through the ctreeServer
 
// Functionally, this application will perform the following:
//  1.  Logon onto a session
//  2.  Add 1 table with some fields
//  3.  Populate the table with a few records
//  4.  Display the contents of the table
//  5.  Update one record under locking control


print("<html>\n");
   print("<head>\n");
      print("<title>PHP Tutorial 3</title>\n");
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
      echo "<h4>INIT</h4>\n";

      // connect to server
      try {
         $ses = new PDO('ctsql:port=6597;host=localhost;dbname=ctreeSQL', 'admin', 'ADMIN');
      }
      catch( PDOException $Exception ) {
         print($Exception->getMessage() . " - SQL ERROR [" . $Exception->getCode() . "]<br>\n");
         print("*** Execution aborted *** <br>\n");
         exit();
      }

      return ($ses);
   }


   //
   // Define()
   //
   // Create the table for containing a list of existing customers
   //
   
   function Defines($ses) {
      echo "<h4>DEFINE</h4>\n";

      $qry = $ses->exec(
         "CREATE TABLE custmast ( 
            cm_custnumb CHAR(4), 
            cm_custzipc CHAR(9), 
            cm_custstat CHAR(2), 
            cm_custrtng CHAR(1), 
            cm_custname VARCHAR(47), 
            cm_custaddr VARCHAR(47), 
            cm_custcity VARCHAR(47))");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE TABLE)");

      $qry = $ses->exec(
         "CREATE UNIQUE INDEX cm_custnumb_idx ON custmast (cm_custnumb)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE INDEX)");
   }
   

   //
   // Manage()
   //
   // This function performs simple record functions of add, delete and gets
   //

   function Manage($ses) {
      echo "<h4>MANAGE</h4>\n";

      // delete any existing records
      Delete_Records($ses);

      // populate the table with data
      Add_CustomerMaster_Records($ses);

      // display contents of table
      Display_Records($ses);

      // update a record under locking control
      Update_CustomerMaster_Records($ses);

      // display again after update and effects of lock
      Display_Records($ses);
   }

   
   //
   // Done()
   //
   // This function handles the housekeeping of closing, freeing,
   // disconnecting and logging out of the database
   //

   function Done ($ses) {
      echo "<h4>DONE</h4>\n";

      // logout
      $ses = null;
   }


   //
   // Delete_Records()
   //
   // This function deletes all the records in the table
   //
   
   function Delete_Records ($ses) {
      echo "Delete records...<br>\n";

      $qry = $ses->exec("DELETE FROM custmast");
      if (!$qry)
         if (0000 == $ses->errorCode())
            return;
         else
            Handle_Error($ses, "exec(DELETE)");
   }


   //
   // Add_CustomerMaster_Records()
   //
   // This function adds records to table CustomerMaster from an
   // array of strings
   //

   function Add_CustomerMaster_Records ($ses) {
      echo "Add records...<br>\n";

      $data = array(
         "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
         "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
         "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
         "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
      );
	  
      if (!$ses->beginTransaction())
         Handle_Error($ses, "beginTransaction()");

      foreach ($data as $values) {
         $qry = $ses->exec("INSERT INTO custmast VALUES $values");
         if (!$qry)
            Handle_Error($ses, "exec(INSERT)");
      }

      if (!$ses->commit())
         Handle_Error($ses, "commit");
   }


   //
   // Display_Records()
   //
   // This function displays the contents of a table.
   //

   function Display_Records ($ses) {
      echo "Display records...<br>\n";

      $qry = $ses->query("SELECT cm_custnumb \"Number\", cm_custname \"Name\" FROM custmast");
      if (!$qry)
         Handle_Error("query(SELECT)");
      else {
         print("<TABLE border=1><TR><TH>Number</TH><TH>Name</TH></TR>\n");

         foreach ($qry as $row)
            print "\t\t\t<TR><TD>" . $row['Number'] . "</TD><TD>" . $row['Name'] . "</TR>\n";

         print("\t\t</TABLE>\n");

         if ($qry->errorCode())
            Handle_Error($qry, "fetch()");

         $qry = null;
      }
   }


   //
   // Update_CustomerMaster_Records()
   //
   // Update one record under locking control to demonstrate the effects
   // of locking
   //

   function Update_CustomerMaster_Records ($ses) {
      echo "Display records...<br>\n";
   }


   //
   // Handle_Error()
   //
   // General error routine that retrieves and displays specific SQL Error
   // before exiting the tutorial.  If the error returned indicates an object
   // already exists, execution is returned to the calling function.
   //

   function Handle_Error($hdl, $msg) {
      $SUCCESS = 00000;
      $TABLE_ALREADY_EXISTS = 20041;
      $INDEX_ALREADY_EXISTS = 20028;

      $err = $hdl->errorCode();
      if ($err == $SUCCESS || $err == $TABLE_ALREADY_EXISTS || $err == $INDEX_ALREADY_EXISTS)
         return;

      print("$msg - SQL ERROR: [$err] - " . $hdl->errorInfo()[2] . " <br>\n");
      print("*** Execution aborted *** <br>\n");
      exit();
   }


   print("</body>\n");
print("</html>\n");

// end of PHP_Tutorial3.php
?>