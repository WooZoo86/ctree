<?php
   // PHP_Tutorial4.php
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
   //  2.  Create 4 tables each with an index
   //  3.  Add records in multiple tables under transaction processing control
   //  4.  Display the contents of the tables

   print("<html>\n");
   print("<head>\n");
   print("\t<title>PHP Tutorial 4</title>\n");
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

      // delete tables ...
      Delete_Tables($ses);
      // ...and re-create them with constraints
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
      Add_ItemMaster_Records($ses);

      if (!$ses->commit())
         Handle_Error($ses, "commit");

      Add_Transactions($ses);

      // display the orders and their items
      Display_CustomerOrders($ses);
      Display_OrderItems($ses);
   }


   //
   // Done()
   //
   // This function handles the housekeeping of closing, freeing,
   // disconnecting and logging out of the database
   //
   
   function Done ($ses) {
      print("\t<h4>DONE</h4>\n");

      Delete_Tables($ses);

      // logout
      print("\t\tLogout...<br>\n");
      $ses = null;
   }


   //
   // Delete_Tables()
   //
   // This function removes all existing tables
   //

   function Delete_Tables ($ses) {
      $qry = $ses->exec("DROP TABLE ordritem");
      if (!$qry)
         Handle_Error($ses, "exec(DROP TABLE)");

      $qry = $ses->exec("DROP TABLE custordr");
      if (!$qry)
         Handle_Error($ses, "exec(DROP TABLE)");

      $qry = $ses->exec("DROP TABLE custmast");
      if (!$qry)
         Handle_Error($ses, "exec(DROP TABLE)");

      $qry = $ses->exec("DROP TABLE itemmast");
      if (!$qry)
         Handle_Error($ses, "exec(DROP TABLE)");
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
            cm_custnumb CHAR(4) PRIMARY KEY, 
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
         co_ordrnumb CHAR(6) PRIMARY KEY,
         co_custnumb CHAR(4),
         FOREIGN KEY (co_custnumb) REFERENCES custmast)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE TABLE)");
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
         oi_itemnumb CHAR(5),
         FOREIGN KEY (oi_itemnumb) REFERENCES itemmast,
         FOREIGN KEY (oi_ordrnumb) REFERENCES custordr)");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE TABLE)");
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
         im_itemnumb CHAR(5) PRIMARY KEY,
         im_itemdesc VARCHAR(47))");
      if (!$qry)
         Handle_Error($ses, "exec(CREATE TABLE)");
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

      foreach ($data as $values) {
         $qry = $ses->exec("INSERT INTO custmast VALUES $values");
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

      foreach ($data as $values) {
         $qry = $ses->exec("INSERT INTO itemmast VALUES $values");
         if (!$qry)
            Handle_Error($ses, "exec(INSERT)");
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

   function Add_Transactions ($ses) {
      print("\t\tAdd transaction records...<br>\n");

      if (!$ses->beginTransaction())
         Handle_Error($ses, "beginTransaction()");

      $orders = array(
         array(
            'ordrdate' => '09/01/2002',
            'promdate' => '09/05/2002',
            'ordrnumb' => '1',
            'custnumb' => '1001'
         ),
         array(
            'ordrdate' => '09/02/2002',
            'promdate' => '09/06/2002',
            'ordrnumb' => '2',
            'custnumb' => '9999' // bad customer number
         ),
         array(
            'ordrdate' => '09/22/2002',
            'promdate' => '09/26/2002',
            'ordrnumb' => '3',
            'custnumb' => '1003'
         )
      );

      $items = array(
         array(
            'ordrnumb' => '1',
            'sequnumb' => '1',
            'quantity' => '2',
            'itemnumb' => '1'
         ),
         array(
            'ordrnumb' => '1',
            'sequnumb' => '2',
            'quantity' => '1',
            'itemnumb' => '2'
         ),
         array(
            'ordrnumb' => '2',
            'sequnumb' => '1',
            'quantity' => '1',
            'itemnumb' => '3'
         ),
         array(
            'ordrnumb' => '2',
            'sequnumb' => '2',
            'quantity' => '3',
            'itemnumb' => '4'
         ),
         array(
            'ordrnumb' => '3',
            'sequnumb' => '1',
            'quantity' => '2',
            'itemnumb' => '3'
         ),
         array(
            'ordrnumb' => '3',
            'sequnumb' => '2',
            'quantity' => '2',
            'itemnumb' => '99' // bad item number
         )
      );

      foreach ($orders as $order) {
         // add order record
         $qry = $ses->exec("INSERT INTO custordr VALUES (
            '$order[ordrdate]',
            '$order[promdate]',
            '$order[ordrnumb]',
            '$order[custnumb]')");
         if (!$qry)
            Handle_Error($ses, "exec(INSERT)");

         foreach ($items as $item) {
            // process order items
            if ($item['ordrnumb'] == $order['ordrnumb']) {
               $qr2 = $ses->exec("INSERT INTO ordritem VALUES (
                  $item[sequnumb],
                  $item[quantity],
                  '$item[ordrnumb]',
                  '$item[itemnumb]')");
               if (!$qr2)
                  Handle_Error($ses, "exec(INSERT)");
            }
         }
      }

      if (!$ses->commit())
         Handle_Error($ses, "commit");
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
   // Display_CustomerOrders()
   //
   // This function displays the contents of CustomerOrders table.
   //

   function Display_CustomerOrders ($ses) {
      print("\t\tCustomerOrders Table...<br>\n");

      $qry =  $ses->query("SELECT co_ordrnumb \"Order\", co_custnumb \"Customer\" FROM custordr");
      if (!$qry)
         Handle_Error($ses, "query(SELECT)");
      else {
         print("\t\t<TABLE border=1>\n\t\t\t<TR><TH>Order</TH><TH>Customer</TH></TR>\n");

         foreach ($qry as $row)
            print "\t\t\t<TR><TD>" . $row['Order'] . "</TD><TD>" . $row['Customer'] . "</TR>\n";

         print("\t\t</TABLE>\n");

         if ($qry->errorCode())
            Handle_Error($qry, "fetch()");

         $qry = null;
      }
   }


   //
   // Display_OrderItems()
   //
   // This function displays the contents of OrderItems table.
   //

   function Display_OrderItems ($ses) {
      print("\t\tOrderItems Table...<br>\n");

      $qry = $ses->query("SELECT oi_ordrnumb \"Order\", oi_itemnumb \"Item\" FROM ordritem");
      if (!$qry)
         Handle_Error($ses, "query(SELECT)");
      else {
         print("\t\t<TABLE border=1>\n\t\t\t<TR><TH>Order</TH><TH>Item</TH></TR>\n");

         foreach ($qry as $row)
            print "\t\t\t<TR><TD>" . $row['Order'] . "</TD><TD>" . $row['Item'] . "</TR>\n";

         print("\t\t</TABLE>\n");

         if ($qry->errorCode())
            Handle_Error($qry, "fetch()");

         $qry = null;
      }
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
      $TABLE_NOT_FOUND = 20005;
      $CONSTRAINT_VIOLATION = 20116;

      $err = $hdl->errorCode();
      if ($err == $SUCCESS || $err == $TABLE_NOT_FOUND || $err == $CONSTRAINT_VIOLATION)
         return;

      print("$msg - SQL ERROR: [$err] - " . $hdl->errorInfo()[2] . " <br>\n");
      print("*** Execution aborted *** <br>\n");
      exit();
   }

   print("</body>\n");
   print("</html>\n");

// end of PHP_Tutorial4.php
?>
