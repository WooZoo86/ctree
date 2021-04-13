--
-- VisualTutorial1.sql - ADO.NET Tutorial
--
-- Public domain SQL example
--
-- FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203
--
-- c-tree PLUS(tm) - Version 11
--
-- This script is used to create some test data in order to demostrate
-- the ctreeACE ADO.NET Data Provider.
--

SET ECHO OFF

-- Initialize
ECHO INIT;

-- Drop tables just is case they already exist.
DROP TABLE IF EXISTS ordritem;
DROP TABLE IF EXISTS custordr;
DROP TABLE IF EXISTS itemmast;
DROP TABLE IF EXISTS custmast;

-- Define
ECHO DEFINE;

ECHO table CustomerMaster...;
CREATE TABLE custmast (
   cm_custnumb CHAR(4),
   cm_custzipc CHAR(9),
   cm_custstat CHAR(2),
   cm_custrtng CHAR(1),
   cm_custname VARCHAR(47),
   cm_custaddr VARCHAR(47),
   cm_custcity VARCHAR(47),
   PRIMARY KEY (cm_custnumb)
);

ECHO table CustomerOrders...;
CREATE TABLE custordr (
   co_ordrdate DATE,
   co_promdate DATE,
   co_ordrnumb CHAR(6),
   co_custnumb CHAR(4),
   PRIMARY KEY (co_ordrnumb)
);
CREATE INDEX co_custnumb_idx ON custordr (co_custnumb);

ECHO table OrderItems...;
CREATE TABLE ordritem (
   oi_sequnumb SMALLINT,
   oi_quantity SMALLINT,
   oi_ordrnumb CHAR(6),
   oi_itemnumb CHAR(5),
   PRIMARY KEY (oi_ordrnumb, oi_sequnumb)
);
CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb);

ECHO table ItemMaster...;
CREATE TABLE itemmast (
   im_itemwght INTEGER,
   im_itempric MONEY,
   im_itemnumb CHAR(5),
   im_itemdesc VARCHAR(47),
   PRIMARY KEY (im_itemnumb)
);

COMMIT WORK;

-- Manage
ECHO MANAGE;

ECHO Delete records...;
DELETE FROM custmast;
DELETE FROM custordr;
DELETE FROM ordritem;
DELETE FROM itemmast;
COMMIT WORK;

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
COMMIT WORK;

ECHO;
ECHO Query results;
SELECT * FROM custmast;

-- Done
ECHO DONE;

-- end of VisualTutorial1.sql
