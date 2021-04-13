<?php
   // PHP_Tutorial1.php
   //
   // Public domain PHP example using PDO
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
      print("\t<h4>DEFINE</h4>\n");

      // create table
      print("\t\tCreate table...<br>\n");
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
      $ses = null;
   }


   //
   // Delete_Records()
   //
   // This function deletes all the records in the table
   //
   
   function Delete_Records ($ses) {
      print("\t\tDelete records...<br>\n");

      $qry = $ses->exec("DELETE FROM custmast");
      if (!$qry)
         if (0000 == $ses->errorCode())
            return;
         else
            Handle_Error($ses, "exec(DELETE)");
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
      print("\t\tDisplay records...<br>\n");

      print("\t\t<TABLE border=1>\n\t\t\t<TR><TH>Number</TH><TH>Name</TH></TR>\n");

      $qry = $ses->query('SELECT cm_custnumb "Number", cm_custname "Name" FROM custmast');
      if (!$qry)
          Handle_Error($ses, "query(SELECT)");

      foreach ($qry as $row) {
          print("\t\t\t<TR>");
          print "<TD>" . $row['Number'] . "</TD><TD>" . $row['Name'] . "</TD>";
          print("</TR>\n");
      }

      print("\t\t</TABLE>\n");

      if ($qry->errorCode())
          Handle_Error($qry, "fetch()");

      $qry = null;
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

// end of PHP_Tutorial1.php
?>
