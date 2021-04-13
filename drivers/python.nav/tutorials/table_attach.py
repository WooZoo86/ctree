# -*- coding: Latin-1 -*-

import faircom_nav as nav
import os


# ================================================================================
#
# Log into the FairCom Server and connect to one of its databases.
#

def connect():
  nav.Logger.log("CONNECT")

  # Connect to the FairCom server.
  try:
    my_server.connect()
    nav.Logger.log("\tLogged onto Faircom Server Instance " + my_server.server_name + ".")
  
  except nav.DatabaseError as e:
    nav.Logger.log("\tFaircom Server Instance is not running.")
    nav.Logger.log("\tNOTE: The evaluation edition automatically shuts down periodically.")
    nav.Logger.exit_with_faircom_error(e)
  
  # Try to connect to the database.
  # If the database does not exist, create it and then connect to it.
  try:
    my_database.connect(my_server) # try to connect to the database.
    nav.Logger.log("\tConnected to FairCom Database " + my_database.database_name + ".")

  except nav.DatabaseError as e:
      # The 'connect' call failed.
      if e.error_code == 101:
        nav.Logger.log("\tDatabase " + my_database.database_name + " does not exist.")
        try:
          my_database.create() # create the database
          nav.Logger.log("\tCreated FairCom Database " + my_database.database_name + " in Faircom Server " + my_server.server_name + ".")
        except nav.DatabaseError as e:
          nav.Logger.log("\tCould not create Faircom Database " + my_database.database_name + " with path " + my_database.database_path + ".")
          nav.Logger.exit_with_faircom_error(e)
        try:
          my_database.connect(my_server)
          nav.Logger.log("\tConnected to FairCom Database " + my_database.database_name + ".")
        except nav.DatabaseError as e:
          nav.Logger.log("\tCould not connect to Faircom Database " + my_database.database_name + ".")
          nav.Logger.exit_with_faircom_error(e)
      else:
        nav.Logger.log("\tCould not connect to Faircom Database " + my_database.database_name + ".")
        nav.Logger.exit_with_faircom_error(e)



# ================================================================================
#
# Disconnect from database
#

def disconnect():
  nav.Logger.log("DISCONNECT")

  try:
    my_database.disconnect()
    nav.Logger.log("\tDisconnected from FairCom Database " + my_database.database_name + ".")
    my_server.disconnect()
    nav.Logger.log("\tLogged out of FairCom Server Instance " + my_server.server_name + ".")
  except nav.DatabaseError as e:
    nav.Logger.log("\tCould not close/disconnect.")
    nav.Logger.exit_with_faircom_error(e)


# ************************************************************************************
# ************************************************************************************


# Login information
faircom_server_name = "FAIRCOMS"
database_name = "ctreeSQL"
user_name = "ADMIN"
password = "ADMIN"

# Objects needed by this program
my_server = nav.FaircomServer(faircom_server_name, user_name, password)
my_database = nav.FaircomDatabase(database_name)

nav.Logger.log("Table attacher for python.nav")

connect()

# AddTable(FileName, FolderThatFileIsIn)
# 'Name' is the name of the table be added, including the file extension, usually .dat.
# 'Path' specifies where the table files are on disk. If Path is left empty, c-tree will attempt 
#   to locate the files in the Server directory (client/server) or in the execution directory (standalone).
# "D:\Kevin\Kevin_SVN_Branch\python.nav\tutorials\athlete.dat"
# "D:\Kevin\Kevin_SVN_Branch\python.nav\tutorials\athlete.idx"
try:
  my_database.CTDatabase.AddTable("athlete.dat", "D:\\Kevin\\Kevin_SVN_Branch\\python.nav\\tutorials\\")
  nav.Logger.log("Attached table to session database!")
except nav.DatabaseError as e:
  nav.Logger.log("Could not add table - %s." % (str(e)))

disconnect()

input("\nDone! Press <ENTER> key to exit . . .")
