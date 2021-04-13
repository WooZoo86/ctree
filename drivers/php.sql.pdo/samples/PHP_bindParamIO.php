<?php
   // PHP_bindParamIO.php
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
   print("\t<title>PHP bindParam IO</title>\n");
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
   // Create a STP with INOUT parameter
   //
   
   function Defines($ses) {
      print("\t<h4>DEFINE</h4>\n");

      // create table
/*      print("\t\tCreate STP...<br>\n");
	  
     $qry = $ses->exec(
         "CREATE PROCEDURE testProc( INOUT arg1 INTEGER )
          BEGIN
	         arg1 = arg1*2;
          END");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE PROCEDURE)"); */
   }
   

   //
   // Manage()
   //
   // This function performs simple record functions of add, delete and gets
   //

   function Manage($ses) {
      print("\t\tCall STP...<br>\n");
	  
	  $fld = 3;
	  
	  $qry_cmd = 'CALL testProc( :arg )';
	  $qry = $ses->prepare($qry_cmd);
	  
	  if(!$qry->bindParam(':arg', $fld, PDO::PARAM_INT|PDO::PARAM_INPUT_OUTPUT))
         Handle_Error($qry, "bindParam");

	  if (!$qry->execute())
		 Handle_Error($qry, "execute");

      print("testProc output value is: " . $fld . "\n");
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
