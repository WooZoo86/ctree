--
-- ISQL_Tutorial2.sql
--
-- Public domain Interactive SQL example
--
-- FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
--
-- The goal of this tutorial is to introduce the most basic interactive SQL commands
-- to accomplish creating and manipulating a table through the ctreeServer
--
-- Functionally, this application will perform the following:
--  1.  Create a database
--  2.  Create 4 tables each with an index
--  3.  Populate each table with a few records
--  4.  Build a query utilizing the advantage of indexes
--  5.  Output the results of the query
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

ECHO table CustomerMaster...;
CREATE TABLE custmast (
   cm_custnumb CHAR(4),
   cm_custzipc CHAR(9),
   cm_custstat CHAR(2),
   cm_custrtng CHAR(1),
   cm_custname VARCHAR(47),
   cm_custaddr VARCHAR(47),
   cm_custcity VARCHAR(47));
CREATE UNIQUE INDEX cm_custnumb_idx ON custmast (cm_custnumb);

ECHO table CustomerOrders...;
CREATE TABLE custordr (
   co_ordrdate DATE,
   co_promdate DATE,
   co_ordrnumb CHAR(6),
   co_custnumb CHAR(4));
CREATE UNIQUE INDEX co_ordrnumb_idx ON custordr (co_ordrnumb);
CREATE INDEX co_custnumb_idx ON custordr (co_custnumb);

ECHO table OrderItems...;
CREATE TABLE ordritem (
   oi_sequnumb SMALLINT,
   oi_quantity SMALLINT,
   oi_ordrnumb CHAR(6),
   oi_itemnumb CHAR(5)
);
CREATE UNIQUE INDEX oi_ordrnumb_idx ON ordritem (oi_ordrnumb, oi_sequnumb);
CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb);

ECHO table ItemMaster...;
CREATE TABLE itemmast (
   im_itemwght INTEGER,
   im_itempric MONEY,
   im_itemnumb CHAR(5),
   im_itemdesc VARCHAR(47)
);
CREATE UNIQUE INDEX im_itemnumb_idx ON itemmast (im_itemnumb);

-- Manage
ECHO MANAGE;

ECHO Delete records...;
DELETE FROM custmast;
DELETE FROM custordr;
DELETE FROM ordritem;
DELETE FROM itemmast;

ECHO Add records...;
INSERT INTO custmast VALUES ('1000', '92867', 'CA', '1', 'Bryan Williams', '2999 Regency', 'Orange');
INSERT INTO custmast VALUES ('1001', '61434', 'CT', '1', 'Michael Jordan', '13 Main', 'Harford');
INSERT INTO custmast VALUES ('1002', '73677', 'GA', '1', 'Joshua Brown', '4356 Cambridge', 'Atlanta');
INSERT INTO custmast VALUES ('1003', '10034', 'MO', '1', 'Keyon Dooling', '19771 Park Avenue', 'Columbia');

INSERT INTO custordr VALUES ('09/01/2002', '09/05/2002', '1', '1001');
INSERT INTO custordr VALUES ('09/02/2002', '09/06/2002', '2', '1002');

INSERT INTO ordritem VALUES (1, 2, '1', '1');
INSERT INTO ordritem VALUES (2, 1, '1', '2');
INSERT INTO ordritem VALUES (3, 1, '1', '3');
INSERT INTO ordritem VALUES (1, 3, '2', '3');

INSERT INTO itemmast VALUES (10, 19.95,  '1', 'Hammer');
INSERT INTO itemmast VALUES (3,   9.99,  '2', 'Wrench');
INSERT INTO itemmast VALUES (4,  16.59,  '3', 'Saw');
INSERT INTO itemmast VALUES (1,   3.98,  '4', 'Pliers');

ECHO;
ECHO Query results;

SELECT cm_custname "Name", SUM(im_itempric * oi_quantity) "Total"
   FROM custmast, custordr, ordritem, itemmast
   WHERE co_custnumb = cm_custnumb AND co_ordrnumb = oi_ordrnumb AND oi_itemnumb = im_itemnumb
   GROUP BY co_ordrnumb, cm_custname;

-- Done
ECHO DONE;

-- end of ISQL_Tutorial2.sql
