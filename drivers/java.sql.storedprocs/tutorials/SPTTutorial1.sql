--
-- SPTTutorial1.sql
--
-- Public domain Stored Procedure and Triggers example
--
-- FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
--
-- The goal of this tutorial is to introduce the most basic stored procedures and triggers
-- to accomplish creating and manipulating a table through the ctreeServer
--
-- Functionally, this application will perform the following:
--  1.  Set Automatic Transactions ON
--  2.  Add 1 table with some fields
--  3.  Populate the table with a few records
--  4.  Display the contents of the table
--

SET ECHO OFF

-- Initialize
ECHO INIT;

SET AUTOCOMMIT ON;

IF EXISTS (select proc_name from sysprocedures where proc_name = 'define')
BEGIN
	DROP PROCEDURE Define;
END
IF EXISTS (select proc_name from sysprocedures where proc_name = 'add_records')
BEGIN
	DROP PROCEDURE Add_Records;
END
IF EXISTS (select proc_name from sysprocedures where proc_name = 'display_records')
BEGIN
	DROP PROCEDURE Display_Records;
END
IF EXISTS (select proc_name from sysprocedures where proc_name = 'delete_records')
BEGIN
	DROP PROCEDURE Delete_Records;
END
IF EXISTS (select tbl from systables where tbl = 'custmast')
BEGIN
	DROP TABLE custmast;
END

echo Creating procedure Define...

CREATE PROCEDURE Define()
BEGIN
   SQLIStatement st = new SQLIStatement (
      "CREATE TABLE custmast (" +
         "cm_custnumb CHAR(4), " +
         "cm_custzipc CHAR(9), " +
         "cm_custstat CHAR(2), " +
         "cm_custrtng CHAR(1), " +
         "cm_custname VARCHAR(47), " +
         "cm_custaddr VARCHAR(47), " +
         "cm_custcity VARCHAR(47))"
   );
   st.execute();
END

echo Creating procedure Add_Records...

CREATE PROCEDURE Add_Records (
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
      "INSERT INTO custmast VALUES (?,?,?,?,?,?,?) "
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

echo Creating procedure Display_Records...

CREATE PROCEDURE Display_Records ()
RESULT (
   Numb CHAR(4),
   Name CHAR(47)  
)
BEGIN
   SQLCursor cur = new SQLCursor ("SELECT cm_custnumb, cm_custname FROM custmast");
   cur.open();
   cur.fetch();
   while (cur.found())
   {
      SQLResultSet.set(1, cur.getValue(1, CHAR));
      SQLResultSet.set(2, cur.getValue(2, CHAR));

      SQLResultSet.insert();
      cur.fetch();
   }
   cur.close();
END

echo Creating procedure Delete_Records...

CREATE PROCEDURE Delete_Records ()
BEGIN
   SQLIStatement sp_DeleteTable = new SQLIStatement ("DELETE FROM custmast");
   sp_DeleteTable.execute();
END

-- Define
ECHO DEFINE;

CALL Define();

-- Manage
ECHO MANAGE;

ECHO Delete records...;
CALL Delete_Records ();

ECHO Add records...;
CALL Add_Records('1000', '92867', 'CA', '1', 'Bryan Williams', '2999 Regency', 'Orange');
CALL Add_Records('1001', '61434', 'CT', '1', 'Michael Jordan', '13 Main', 'Harford');
CALL Add_Records('1002', '73677', 'GA', '1', 'Joshua Brown', '4356 Cambridge', 'Atlanta');
CALL Add_Records('1003', '10034', 'MO', '1', 'Keyon Dooling', '19771 Park Avenue', 'Columbia');

ECHO Display records...;
CALL Display_Records();

ECHO Delete records...;
CALL Delete_Records ();

-- Done
ECHO DONE;

-- end of SPTTutorial1.sql
