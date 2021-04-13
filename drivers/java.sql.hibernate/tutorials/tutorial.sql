--
-- tutorial1.sql
--
-- FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
--
-- Create the table needed for the Tutorial1 for Hibernate
--

SET ECHO OFF

-- Initialize
ECHO INIT;

SET AUTOCOMMIT ON;

-- Define
ECHO DEFINE;

DROP TABLE IF EXISTS custmast;

ECHO Create table...;
CREATE TABLE custmast (
   cm_custnumb CHAR(4) PRIMARY KEY,
   cm_custzipc CHAR(9),
   cm_custstat CHAR(2),
   cm_custrtng CHAR(1),
   cm_custname VARCHAR(47),
   cm_custaddr VARCHAR(47),
   cm_custcity VARCHAR(47));

-- Done
ECHO DONE;

-- end of tutorial1.sql
