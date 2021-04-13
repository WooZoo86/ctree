--
-- SPTTutorial3.sql
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
--  2.  Add 1 table with some fields
--  3.  Populate the table with a few records
--  4.  Display the contents of the table
--  5.  Update one record under locking control
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

IF EXISTS (select proc_name from sysprocedures where proc_name = 'delete_records')
BEGIN
	DROP PROCEDURE Delete_Records;
END

IF EXISTS (select tbl from systables where tbl = 'custmast')
BEGIN
	DROP TABLE custmast;
END

ECHO Creating procedure Define...

CREATE PROCEDURE Define()
BEGIN
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
   SQLIStatement cmi = new SQLIStatement (
      "CREATE UNIQUE INDEX cm_custnumb_idx ON custmast (cm_custnumb)"
   );
   cmi.execute();
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

-- Define
ECHO DEFINE;

CALL Define();
COMMIT WORK;

-- Manage
ECHO MANAGE;

ECHO Delete records...;
CALL Delete_Records('custmast');

ECHO Add records...;
CALL Add_CustomerMaster_Record('1000', '92867', 'CA', '1', 'Bryan Williams', '2999 Regency', 'Orange');
CALL Add_CustomerMaster_Record('1001', '61434', 'CT', '1', 'Michael Jordan', '13 Main', 'Harford');
CALL Add_CustomerMaster_Record('1002', '73677', 'GA', '1', 'Joshua Brown', '4356 Cambridge', 'Atlanta');
CALL Add_CustomerMaster_Record('1003', '10034', 'MO', '1', 'Keyon Dooling', '19771 Park Avenue', 'Columbia');
COMMIT WORK;

UPDATE custmast SET cm_custname = 'KEYON DOOLING' WHERE cm_custnumb = '1003';
ECHO Issue a COMMIT WORK to commit changes and release locks

-- end of SPTTutorial3.sql
