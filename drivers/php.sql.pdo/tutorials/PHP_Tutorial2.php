<?php
   // PHP_Tutorial2.php
   //
   // Public domain PHP example using PDO
   //
   // FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
   //
   // The goal of this tutorial is to introduce the most basic PHP API
   // to accomplish creating and manipulating a table through the ctreeServer
   //
   // Functionally, this application will perform the following:
   //  1.  Create a database
   //  2.  Create 4 tables each with an index
   //  3.  Populate each table with a few records
   //  4.  Build a query utilizing the advantage of indexes
   //  5.  Output the results of the query

   print("<html>\n");
   print("<head>\n");
   print("\t<title>PHP Tutorial 2</title>\n");
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
   // Create the tables
   //

   function Defines($ses) {
      print("\t<h4>DEFINE</h4>\n");

      if (!$ses->beginTransaction())
         Handle_Error($ses, "beginTransaction()");

      Create_CustomerMaster_Table($ses);
      Create_CustomerOrders_Table($ses);
      Create_OrderItems_Table($ses);
      Create_ItemMaster_Table($ses);

      if (!$ses->commit())
         Handle_Error($ses, "commit");
   }


   //
   // Manage()
   //
   // Populates table and perform a simple query
   //
   
   function Manage($ses) {
      print("\t<h4>MANAGE</h4>\n");

      if (!$ses->beginTransaction())
         Handle_Error($ses, "beginTransaction()");
      
      // populate the tables with data
      Add_CustomerMaster_Records($ses);
      Add_CustomerOrders_Records($ses);
      Add_OrderItems_Records($ses);
      Add_ItemMaster_Records($ses);

      if (!$ses->commit())
         Handle_Error($ses, "commit");

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

      $qry = $ses->query(
               "SELECT cm_custname \"Name\", SUM(im_itempric * oi_quantity) \"Total\"" .
               "FROM custmast, custordr, ordritem, itemmast " .
               "WHERE co_custnumb = cm_custnumb AND co_ordrnumb = oi_ordrnumb AND oi_itemnumb = im_itemnumb " .
               "GROUP BY co_ordrnumb, cm_custname");
      if (!$qry)
         Handle_Error($ses, "query(SELECT)");
      else {
         print("\t\t<TABLE border=1>\n\t\t\t<TR><TH>Name</TH><TH>Total</TH></TR>\n");

         foreach ($qry as $row)
            print "\t\t\t<TR><TD>" . $row['Name'] . "</TD><TD>" . $row['Total'] . "</TR>\n";

         print("\t\t</TABLE>\n");

         if ($qry->errorCode())
            Handle_Error($qry, "fetch()");

         $qry = null;
      }
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
   // Create_CustomerMaster_Table()
   //
   // Create the table CustomerMaster
   //

   function Create_CustomerMaster_Table ($ses) {
      print("\t\ttable CustomerMaster<br>\n");

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
   // Create_CustomerOrders_Table()
   //
   // Create the table CustomerOrders
   //

   function Create_CustomerOrders_Table ($ses) {
      print("\t\ttable CustomerOrders<br>\n");

      $qry = $ses->exec(
      "CREATE TABLE custordr (
         co_ordrdate DATE,
         co_promdate DATE,
         co_ordrnumb CHAR(6),
         co_custnumb CHAR(4))");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE TABLE)");

      $qry = $ses->exec(
         "CREATE UNIQUE INDEX co_ordrnumb_idx ON custordr (co_ordrnumb)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE INDEX)");

      $qry = $ses->exec(
         "CREATE INDEX co_custnumb_idx ON custordr (co_custnumb)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE INDEX)");
   }


   //
   // Create_OrderItems_Table()
   //
   // Create the table OrderItems
   //

   function Create_OrderItems_Table ($ses) {
      print("\t\ttable OrderItems<br>\n");

      $qry = $ses->exec(
      "CREATE TABLE ordritem (
         oi_sequnumb SMALLINT,
         oi_quantity SMALLINT,
         oi_ordrnumb CHAR(6),
         oi_itemnumb CHAR(5))");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE TABLE)");

      $qry = $ses->exec(
         "CREATE UNIQUE INDEX oi_ordrnumb_idx ON ordritem (oi_ordrnumb, oi_sequnumb)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE INDEX)");

      $qry = $ses->exec(
         "CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE INDEX)");
   }


   //
   // Create_ItemMaster_Table()
   //
   // Create the table ItemMaster
   //

   function Create_ItemMaster_Table ($ses) {
      print("\t\ttable ItemMaster<br>\n");

      $qry = $ses->exec(
      "CREATE TABLE itemmast (
         im_itemwght INTEGER,
         im_itempric MONEY,
         im_itemnumb CHAR(5),
         im_itemdesc VARCHAR(47))");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE TABLE)");

      $qry = $ses->exec(
         "CREATE UNIQUE INDEX im_itemnumb_idx ON itemmast (im_itemnumb)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE INDEX)");
   }


   //
   // Add_CustomerMaster_Records()
   //
   // This function adds records to table CustomerMaster from an
   // array of strings
   //

   function Add_CustomerMaster_Records ($ses) {
      print("\t\tAdd records in table CustomerMaster...<br>\n");

      $data = array(
         "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
         "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
         "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
         "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
      );

      Delete_Records($ses, "custmast");

      foreach ($data as $values) {
         $qry = $ses->exec("INSERT INTO custmast VALUES $values");
         if (!$qry)
            Handle_Error($ses, "exec(INSERT)");
      }
   }


   //
   // Add_CustomerOrders_Records()
   //
   // This function adds records to table CustomerOrders from an
   // array of strings
   //

   function Add_CustomerOrders_Records ($ses) {
      print("\t\tAdd records in table CustomerOrders...<br>\n");

      $data = array(
         "('09/01/2002','09/05/2002','1','1001')",
         "('09/02/2002','09/06/2002','2','1002')"
      );

      Delete_Records($ses, "custordr");

      foreach ($data as $values) {
         $qry = $ses->exec("INSERT INTO custordr VALUES $values");
         if (!$qry)
            Handle_Error($ses, "exec(INSERT)");
      }
   }


   //
   // Add_OrderItems_Records()
   //
   // This function adds records to table OrderItems from an
   // array of strings
   //

   function Add_OrderItems_Records ($ses) {
      print("\t\tAdd records in table OrderItems...<br>\n");

      $data = array(
         "(1,2,'1','1')",
         "(2,1,'1','2')",
         "(3,1,'1','3')",
         "(1,3,'2','3')"
      );

      Delete_Records($ses, "ordritem");

      foreach ($data as $values) {
         $qry = $ses->exec("INSERT INTO ordritem VALUES $values");
         if (!$qry)
            Handle_Error($ses, "exec(INSERT)");
      }
   }


   //
   // Add_ItemMaster_Records()
   //
   // This function adds records to table ItemMaster from an
   // array of strings
   //

   function Add_ItemMaster_Records ($ses) {
      print("\t\tAdd records in table ItemMaster...<br>\n");

      $data = array(
         "(10,19.95,'1','Hammer')",
         "(3,  9.99,'2','Wrench')",
         "(4, 16.59,'3','Saw')",
         "(1,  3.98,'4','Pliers')"
      );

      Delete_Records($ses, "itemmast");

      foreach ($data as $values) {
         $qry = $ses->exec("INSERT INTO itemmast VALUES $values");
         if (!$qry)
            Handle_Error($ses, "exec(INSERT)");
      }
   }


   //
   // Delete_Records()
   //
   // This function deletes all the records in a tables
   //

   function Delete_Records ($ses, $table) {
      print("\t\tDelete records...<br>\n");
	  
      $qry = $ses->exec("DELETE FROM $table");
      if (!$qry)
         if (0000 == $ses->errorCode())
            return;
         else
            Handle_Error($ses, "exec(DELETE)");
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

// end of PHP_Tutorial2.php
?>
