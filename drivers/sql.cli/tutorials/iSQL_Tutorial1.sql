--
-- ISQL_Tutorial1.sql
--
-- Public domain Interactive SQL example
--
-- FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
--
-- The goal of this tutorial is to introduce the most basic interactive SQL commands
-- to accomplish creating and manipulating a table through the ctreeServer
--
-- Functionally, this application will perform the following:
--  1.  Logon onto a session
--  2.  Add 1 table with some fields
--  3.  Populate the table with a few records
--  4.  Display the contents of the table
--

SET ECHO OFF

-- Initialize
ECHO INIT;

SET AUTOCOMMIT ON;

-- Define
ECHO DEFINE;

-- Drop tutorial tables if they exist
DROP TABLE IF EXISTS ordritem;
DROP TABLE IF EXISTS custordr;
DROP TABLE IF EXISTS itemmast;
DROP TABLE IF EXISTS custmast;

ECHO Create table...;
CREATE TABLE custmast (
   cm_custnumb CHAR(4),
   cm_custzipc CHAR(9),
   cm_custstat CHAR(2),
   cm_custrtng CHAR(1),
   cm_custname VARCHAR(47),
   cm_custaddr VARCHAR(47),
   cm_custcity VARCHAR(47));

-- Manage
ECHO MANAGE;

ECHO Delete records...;
DELETE FROM custmast;

ECHO Add records...;
INSERT INTO custmast VALUES ('1000', '92867', 'CA', '1', 'Bryan Williams', '2999 Regency', 'Orange');
INSERT INTO custmast VALUES ('1001', '61434', 'CT', '1', 'Michael Jordan', '13 Main', 'Harford');
INSERT INTO custmast VALUES ('1002', '73677', 'GA', '1', 'Joshua Brown', '4356 Cambridge', 'Atlanta');
INSERT INTO custmast VALUES ('1003', '10034', 'MO', '1', 'Keyon Dooling', '19771 Park Avenue', 'Columbia');

ECHO Display records...;
SELECT cm_custnumb "Number", cm_custname "Name" FROM custmast;

ECHO Delete records...;
DELETE FROM custmast;

-- Done
ECHO DONE;

-- end of ISQL_Tutorial1.sql
