--
-- ISQL_Tutorial4.sql
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
--  2.  Create 4 tables each with an index
--  3.  Add records in multiple tables under transaction processing control
--  4.  Display the contents of the tables
--

SET ECHO OFF

-- Initialize
ECHO INIT;

SET AUTOCOMMIT OFF;

-- Define
ECHO DEFINE;

-- Drop tutorial tables if they exist
DROP TABLE IF EXISTS ordritem;
DROP TABLE IF EXISTS custordr;
DROP TABLE IF EXISTS itemmast;
DROP TABLE IF EXISTS custmast;

-- ...and re-create them with constraints
ECHO table CustomerMaster...;
CREATE TABLE custmast (
   cm_custnumb CHAR(4) PRIMARY KEY,
   cm_custzipc CHAR(9),
   cm_custstat CHAR(2),
   cm_custrtng CHAR(1),
   cm_custname VARCHAR(47),
   cm_custaddr VARCHAR(47),
   cm_custcity VARCHAR(47)
);
ECHO table ItemMaster...;
CREATE TABLE itemmast (
   im_itemwght INTEGER,
   im_itempric MONEY,
   im_itemnumb CHAR(5) PRIMARY KEY,
   im_itemdesc VARCHAR(47)
);
ECHO table CustomerOrders...;
CREATE TABLE custordr (
   co_ordrdate DATE,
   co_promdate DATE,
   co_ordrnumb CHAR(6) PRIMARY KEY,
   co_custnumb CHAR(4),
   FOREIGN KEY (co_custnumb) REFERENCES custmast
);
ECHO table OrderItems...;
CREATE TABLE ordritem (
   oi_sequnumb SMALLINT,
   oi_quantity SMALLINT,
   oi_ordrnumb CHAR(6),
   oi_itemnumb CHAR(5),
   FOREIGN KEY (oi_itemnumb) REFERENCES itemmast,
   FOREIGN KEY (oi_ordrnumb) REFERENCES custordr
);
COMMIT WORK;

-- Manage
ECHO MANAGE;

ECHO Add records...;
INSERT INTO custmast VALUES ('1000', '92867', 'CA', '1', 'Bryan Williams', '2999 Regency', 'Orange');
INSERT INTO custmast VALUES ('1001', '61434', 'CT', '1', 'Michael Jordan', '13 Main', 'Harford');
INSERT INTO custmast VALUES ('1002', '73677', 'GA', '1', 'Joshua Brown', '4356 Cambridge', 'Atlanta');
INSERT INTO custmast VALUES ('1003', '10034', 'MO', '1', 'Keyon Dooling', '19771 Park Avenue', 'Columbia');
INSERT INTO itemmast VALUES (10, 19.95,  '1', 'Hammer');
INSERT INTO itemmast VALUES (3, 9.99,  '2', 'Wrench');
INSERT INTO itemmast VALUES (4, 16.59,  '3', 'Saw');
INSERT INTO itemmast VALUES (1, 3.98,  '4', 'Pliers');
COMMIT WORK;

INSERT INTO custordr VALUES ('09/01/2002', '09/05/2002', '1', '1001');
INSERT INTO ordritem VALUES (1,  2, '1', '1');
INSERT INTO ordritem VALUES (2,  1, '1', '2');

INSERT INTO custordr VALUES ('09/02/2002', '09/06/2002', '2', '9999');
ECHO NOTE: constraint violation expected
INSERT INTO ordritem VALUES (1,  1, '2', '3');
ECHO NOTE: constraint violation expected
INSERT INTO ordritem VALUES (2,  3, '2', '4');
ECHO NOTE: constraint violation expected

INSERT INTO custordr VALUES ('09/22/2002', '09/26/2002', '3', '1003');
INSERT INTO ordritem VALUES (1,  2, '3', '3');
INSERT INTO ordritem VALUES (2,  2, '3', '99');
ECHO NOTE: constraint violation expected
COMMIT WORK;

SELECT co_ordrnumb "Order", co_custnumb "Name" FROM custordr;
SELECT oi_ordrnumb "Order", oi_itemnumb "Item" FROM ordritem;

-- Done
ECHO DONE;

DROP TABLE ordritem;
DROP TABLE custordr;
DROP TABLE itemmast;
DROP TABLE custmast;
COMMIT WORK;

-- end of ISQL_Tutorial4.sql
