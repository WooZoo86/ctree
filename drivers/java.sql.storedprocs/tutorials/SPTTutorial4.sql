--
-- SPTTutorial4.sql
--
-- Public domain Stored Procedure and Triggers example
--
-- FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
--
-- The goal of this tutorial is to introduce the most basic stored procedures and triggers
-- to accomplish creating and manipulating a table through the ctreeServer
--
-- Functionally, this application will perform the following:
--  1.  Set Automatic Transactions OFF
--  2.  Create 4 tables each with an index
--  3.  Add records in multiple tables under transaction processing control
--  4.  Display the contents of the tables
--

SET ECHO OFF

-- Initialize
ECHO INIT;

SET AUTOCOMMIT OFF;

IF EXISTS (select proc_name from sysprocedures where proc_name = 'define')
BEGIN
	DROP PROCEDURE Define;
END

IF EXISTS (select proc_name from sysprocedures where proc_name = 'add_customermaster_record')
BEGIN
	DROP PROCEDURE Add_CustomerMaster_Record;
END

IF EXISTS (select proc_name from sysprocedures where proc_name = 'add_customerorders_record')
BEGIN
	DROP PROCEDURE Add_CustomerOrders_Record;
END

IF EXISTS (select proc_name from sysprocedures where proc_name = 'add_orderitems_record')
BEGIN
	DROP PROCEDURE Add_OrderItems_Record;
END

IF EXISTS (select proc_name from sysprocedures where proc_name = 'add_itemmaster_record')
BEGIN
	DROP PROCEDURE Add_ItemMaster_Record;
END

IF EXISTS (select proc_name from sysprocedures where proc_name = 'delete_records')
BEGIN
	DROP PROCEDURE Delete_Records;
END

IF EXISTS (select triggername from systrigger where triggername = 'validate_customerorders_record')
BEGIN
	DROP TRIGGER Validate_CustomerOrders_Record;
END

IF EXISTS (select triggername from systrigger where triggername = 'validate_orderitems_record')
BEGIN
	DROP TRIGGER Validate_OrderItems_Record;
END

IF EXISTS (select tbl from systables where tbl = 'ordritem')
BEGIN
	DROP TABLE ordritem;
END
IF EXISTS (select tbl from systables where tbl = 'custordr')
BEGIN
	DROP TABLE custordr;
END
IF EXISTS (select tbl from systables where tbl = 'itemmast')
BEGIN
	DROP TABLE itemmast;
END
IF EXISTS (select tbl from systables where tbl = 'custmast')
BEGIN
	DROP TABLE custmast;
END

ECHO Creating procedure Define...

CREATE PROCEDURE Define()
BEGIN
   int TABLE_ALREADY_EXIST = -20041;
   int INDEX_ALREADY_EXIST = -20028;
   
   try
   {
      SQLIStatement cm = new SQLIStatement (
         "CREATE TABLE custmast (" +
            "cm_custnumb CHAR(4), " +
            "cm_custzipc CHAR(9), " +
            "cm_custstat CHAR(2), " +
            "cm_custrtng CHAR(1), " +
            "cm_custname VARCHAR(47), " +
            "cm_custaddr VARCHAR(47), " +
            "cm_custcity VARCHAR(47))"
      );
      cm.execute();
   }
   catch (DhSQLException e)
   {
      if (e.sqlErr != TABLE_ALREADY_EXIST)
         throw e;
   }
   try
   {
      SQLIStatement cm1 = new SQLIStatement (
         "CREATE INDEX cm_custnumb_idx ON custmast (cm_custnumb)"
      );
      cm1.execute();
   }
   catch (DhSQLException e)
   {
      if (e.sqlErr != INDEX_ALREADY_EXIST)
         throw e;
   }

   try
   {
      SQLIStatement co = new SQLIStatement (
         "CREATE TABLE custordr (" +
            "co_ordrdate DATE, " +
            "co_promdate DATE, " +
            "co_ordrnumb CHAR(6), " +
            "co_custnumb CHAR(4))"
      );
      co.execute();
   }
   catch (DhSQLException e)
   {   
      if (e.sqlErr != TABLE_ALREADY_EXIST)
         throw e;
   }
   try
   {
      SQLIStatement co1 = new SQLIStatement (
         "CREATE INDEX co_ordrnumb_idx ON custordr (co_ordrnumb)"
      );
      co1.execute();
   }
   catch (DhSQLException e)
   {
      if (e.sqlErr != INDEX_ALREADY_EXIST)
         throw e;
   }
   try
   {
      SQLIStatement co2 = new SQLIStatement (
         "CREATE INDEX co_custnumb_idx ON custordr (co_custnumb)"
      );
      co2.execute();
   }
   catch (DhSQLException e)
   {
      if (e.sqlErr != INDEX_ALREADY_EXIST)
         throw e;
   }

   try
   {
      SQLIStatement oi = new SQLIStatement (
         "CREATE TABLE ordritem (" +
            "oi_sequnumb SMALLINT, " +
            "oi_quantity SMALLINT, " +
            "oi_ordrnumb CHAR(6), " +
            "oi_itemnumb CHAR(5))"
      );
      oi.execute();
   }
   catch (DhSQLException e)
   {   
      if (e.sqlErr != TABLE_ALREADY_EXIST)
         throw e;
   }
   try
   {
      SQLIStatement oi1 = new SQLIStatement (
         "CREATE INDEX oi_ordrnumb_idx ON ordritem (oi_ordrnumb, oi_sequnumb)"
      );
      oi1.execute();
   }
   catch (DhSQLException e)
   {
      if (e.sqlErr != INDEX_ALREADY_EXIST)
         throw e;
   }
   try
   {
      SQLIStatement oi2 = new SQLIStatement (
         "CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb)"
      );
      oi2.execute();
   }
   catch (DhSQLException e)
   {
      if (e.sqlErr != INDEX_ALREADY_EXIST)
         throw e;
   }

   try
   {
      SQLIStatement im = new SQLIStatement (
         "CREATE TABLE itemmast (" +
            "im_itemwght INTEGER, " +
            "im_itempric MONEY, " +
            "im_itemnumb CHAR(5), " +
            "im_itemdesc VARCHAR(47))"
      );
      im.execute();
   }
   catch (DhSQLException e)
   {   
      if (e.sqlErr != TABLE_ALREADY_EXIST)
         throw e;
   }
   try
   {
      SQLIStatement im1 = new SQLIStatement (
         "CREATE INDEX im_itemnumb_idx ON itemmast (im_itemnumb)"
      );
      im1.execute();
   }
   catch (DhSQLException e)
   {
      if (e.sqlErr != INDEX_ALREADY_EXIST)
         throw e;
   }
END

ECHO Creating procedure Add_CustomerMaster_Record...

CREATE PROCEDURE Add_CustomerMaster_Record (
   IN cm_custnumb CHAR(4),
   IN cm_custzipc CHAR(9),
   IN cm_custstat CHAR(2),
   IN cm_custrtng CHAR(1),
   IN cm_custname VARCHAR(47),
   IN cm_custaddr VARCHAR(47),
   IN cm_custcity VARCHAR(47)
)
BEGIN
   SQLIStatement st = new SQLIStatement (
      "INSERT INTO custmast VALUES (?,?,?,?,?,?,?)"
   );
   st.setParam (1, cm_custnumb);
   st.setParam (2, cm_custzipc);
   st.setParam (3, cm_custstat);
   st.setParam (4, cm_custrtng);
   st.setParam (5, cm_custname);
   st.setParam (6, cm_custaddr);
   st.setParam (7, cm_custcity);
   st.execute();
END

ECHO Creating procedure Add_CustomerOrders_Record...

CREATE PROCEDURE Add_CustomerOrders_Record (
   IN co_ordrdate DATE,
   IN co_promdate DATE,
   IN co_ordrnumb CHAR(6),
   IN co_custnumb CHAR(4)
)
BEGIN
   SQLIStatement st = new SQLIStatement (
      "INSERT INTO custordr VALUES (?,?,?,?)"
   );
   st.setParam (1, co_ordrdate);
   st.setParam (2, co_promdate);
   st.setParam (3, co_ordrnumb);
   st.setParam (4, co_custnumb);
   st.execute();
END

ECHO Creating procedure Add_OrderItems_Record...

CREATE PROCEDURE Add_OrderItems_Record (
   IN oi_sequnumb SMALLINT,
   IN oi_quantity SMALLINT,
   IN oi_ordrnumb CHAR(6),
   IN oi_itemnumb CHAR(5)
)
BEGIN
   SQLIStatement st = new SQLIStatement (
      "INSERT INTO ordritem VALUES (?,?,?,?)"
   );
   st.setParam (1, oi_sequnumb);
   st.setParam (2, oi_quantity);
   st.setParam (3, oi_ordrnumb);
   st.setParam (4, oi_itemnumb);
   st.execute();
END

ECHO Creating procedure Add_ItemMaster_Record...

CREATE PROCEDURE Add_ItemMaster_Record (
   IN im_itemwght INTEGER,
   IN im_itempric MONEY,
   IN im_itemnumb CHAR(5),
   IN im_itemdesc VARCHAR(47)
)
BEGIN
   SQLIStatement st = new SQLIStatement (
      "INSERT INTO itemmast VALUES (?,?,?,?)"
   );
   st.setParam (1, im_itemwght);
   st.setParam (2, im_itempric);
   st.setParam (3, im_itemnumb);
   st.setParam (4, im_itemdesc);
   st.execute();
END

-- Define
ECHO DEFINE;

CALL Define();
COMMIT WORK;

ECHO Creating trigger Validate_CustomerOrders_Record...

CREATE TRIGGER Validate_CustomerOrders_Record
   BEFORE INSERT ON custordr
   REFERENCING NEWROW
   FOR EACH ROW
BEGIN
   SQLCursor cur = new SQLCursor ("SELECT cm_custnumb FROM custmast WHERE cm_custnumb = ?");

   String custnumb = (String) NEWROW.getValue(4, CHAR);
   cur.setParam(1, custnumb);
   
   cur.open();
   cur.fetch();
   if (!cur.found())
   {
      cur.close();
      DhSQLException ex = new DhSQLException (666, new String("Invalid customer number"));
      throw ex;
   }
   cur.close();
END

ECHO Creating trigger Validate_OrderItems_Record...

CREATE TRIGGER Validate_OrderItems_Record
   BEFORE INSERT ON ordritem
   REFERENCING NEWROW
   FOR EACH ROW
BEGIN
   SQLCursor cur = new SQLCursor ("SELECT co_ordrnumb FROM custordr WHERE co_ordrnumb = ?");

   String ordrnumb = (String) NEWROW.getValue(3, CHAR);
   cur.setParam(1, ordrnumb);
   
   cur.open();
   cur.fetch();
   if (!cur.found())
   {
      cur.close();
      DhSQLException ex = new DhSQLException (666, new String("Invalid order number"));
      throw ex;
   }
   cur.close();

   cur = new SQLCursor ("SELECT im_itemnumb FROM itemmast WHERE im_itemnumb = ?");

   String itemnumb = (String) NEWROW.getValue(4, CHAR);
   cur.setParam(1, itemnumb);
   
   cur.open();
   cur.fetch();
   if (!cur.found())
   {
      cur.close();
      DhSQLException ex = new DhSQLException (666, new String("Invalid item number"));
      throw ex;
   }
   cur.close();
END

ECHO Creating procedure Delete_Records...

CREATE PROCEDURE Delete_Records (
   IN tablename CHAR(256)
)
BEGIN
   SQLIStatement st = new SQLIStatement (
      "DELETE FROM " + tablename
   );
   st.execute();
END

-- Manage
ECHO MANAGE;

ECHO Delete records...;
CALL Delete_Records('custmast');
CALL Delete_Records('custordr');
CALL Delete_Records('ordritem');
CALL Delete_Records('itemmast');

ECHO Add records...;
CALL Add_CustomerMaster_Record('1000', '92867', 'CA', '1', 'Bryan Williams', '2999 Regency', 'Orange');
CALL Add_CustomerMaster_Record('1001', '61434', 'CT', '1', 'Michael Jordan', '13 Main', 'Harford');
CALL Add_CustomerMaster_Record('1002', '73677', 'GA', '1', 'Joshua Brown', '4356 Cambridge', 'Atlanta');
CALL Add_CustomerMaster_Record('1003', '10034', 'MO', '1', 'Keyon Dooling', '19771 Park Avenue', 'Columbia');
CALL Add_ItemMaster_Record(10, 19.95, '1', 'Hammer');
CALL Add_ItemMaster_Record(3, 9.99, '2', 'Wrench');
CALL Add_ItemMaster_Record(4, 16.59, '3', 'Saw');
CALL Add_ItemMaster_Record(1, 3.98, '4', 'Pliers');
COMMIT WORK;

CALL Add_CustomerOrders_Record ('09/01/2002', '09/05/2002', '1', '1001');
CALL Add_OrderItems_Record (1,  2, '1', '1');
CALL Add_OrderItems_Record (2,  1, '1', '2');

CALL Add_CustomerOrders_Record ('09/02/2002', '09/06/2002', '2', '9999');
ECHO NOTE: trigger execution failure expected
CALL Add_OrderItems_Record (1,  1, '2', '3');
ECHO NOTE: trigger execution failure expected
CALL Add_OrderItems_Record (2,  3, '2', '4');
ECHO NOTE: trigger execution failure expected

CALL Add_CustomerOrders_Record ('09/22/2002', '09/26/2002', '3', '1003');
CALL Add_OrderItems_Record (1,  2, '3', '3');
CALL Add_OrderItems_Record (2,  2, '3', '99');
ECHO NOTE: trigger execution failure expected
COMMIT WORK;

SELECT co_ordrnumb "Order", co_custnumb "Name" FROM custordr;
SELECT oi_ordrnumb "Order", oi_itemnumb "Item" FROM ordritem;

-- Done
ECHO DONE;
DROP TRIGGER Validate_CustomerOrders_Record;
DROP TRIGGER Validate_OrderItems_Record;
COMMIT WORK;

-- end of SPTTutorial4.sql
