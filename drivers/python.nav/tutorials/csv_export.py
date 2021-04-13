# -*- coding: Latin-1 -*-

import faircom_nav as nav
from datetime import * 
import csv, sys, os


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
# Write the contents of the table to a CSV file
#
# write_column_names - boolean which says if the first line of the CSV file should contain the column names.
#
# index_number - lets you specify an index to sort the order of the records as they are written to the CSV file.
#
# field_numbers_to_ignore - a list of zero-based field numbers which should not be written to the CSV file.
#

def dump_table_to_csv_file(csv_file_path, write_column_names=True, index_number=None, field_numbers_to_ignore=[]):

  nav.Logger.log("DUMPING TABLE TO FILE.")

  if type(field_numbers_to_ignore) is not list:
    nav.Logger.exit_with_app_error("Error!  field_numbers_to_ignore needs to be a list and not a %s." % (str(type(field_numbers_to_ignore))))

  # Fill a list with all of the field / column names in the table.
  try:
    num_fields = my_table.myCTTable.GetFieldCount() # how many fields are there?
    field_names = [] 
    for field_number in range(num_fields):
      if field_number in field_numbers_to_ignore:
        continue
      field = my_table.myCTTable.GetField(field_number) # get a field based on the field number
      field_names.append(field.GetName())
  except nav.DatabaseError as e:
    nav.Logger.log("\tError - Could not get field names from table.")
    nav.Logger.exit_with_faircom_error(e)

  # Tell the user about it.
  nav.Logger.log("\tTable has %d fields.  I will write %d of them:  %s" % (num_fields, len(field_names), ', '.join(field_names)))

  if len(field_names) == 0:
    nav.Logger.log("\tI cannot write a CSV file with no fields.  Returning.")
    return

  # Open the output file and write the field names (if my caller wants me to)
  try:
    record_number=0
    with open(csv_file_path, 'w', newline='', encoding='Latin-1') as csv_file:
      #writer = csv.DictWriter(csv_file, fieldnames=field_names)
      writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_NONNUMERIC)
      if write_column_names:
        writer.writerow(field_names)

      # Now traverse all of the rows in the table, extract their contents, and write them to the CSV file.
      try:
        field_number = None
        rec = my_table.new_record_buffer()  # type = CTRecord

        # If my caller specified an index, set the collation / sort order of the record read-out
        #   by selecting that index.
        if index_number is not None:
          rec.set_default_index(index_number)

        found = rec.first()     # read first record

        while found is True:
          # rec holds one record / row from the table.  Let's get all the field data as strings
          # and put them into the 'field_list', which we will then pass to the CSV file writer.
          record_number += 1
          field_data = []
          for field_number in range(num_fields):
            if field_number in field_numbers_to_ignore:
              continue
            field_data.append(rec.GetFieldAsString(field_number))

          field_number = None
          writer.writerow(field_data)

          found = rec.next()    # read next record

      except nav.DatabaseError as e:
        nav.Logger.exit_with_app_error("Error while processing record #%d, field #%s - %s" % (record_number, str(field_number), str(e)))

    nav.Logger.log("\tWrote %d records to the CSV file." % (record_number))

  except Exception as e:
    nav.Logger.log("\tError writing CSV file.")
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

# Output file name.
csv_file_path = "test1.csv"
# Name of the table I will read
table_name = "athlete"

# Login information
faircom_server_name = "FAIRCOMS"
database_name = "ctreeSQL"
user_name = "ADMIN"
password = "ADMIN"

# Objects needed by this program
my_server = nav.FaircomServer(faircom_server_name, user_name, password)
my_database = nav.FaircomDatabase(database_name)
my_table = nav.Table(table_name)

nav.Logger.log("CSV file writer for python.nav")

connect()

nav.Logger.log("OPEN TABLE")

try:
  my_table.open(my_database)
  nav.Logger.log("\tOpened " + my_table.table_name + " table in " + str(my_table.get_open_mode()) + " mode.")

except nav.DatabaseError as e:
    nav.Logger.log("\tCould not open " + my_table.table_name + " table.")
    nav.Logger.exit_with_faircom_error(e)


dump_table_to_csv_file(csv_file_path, write_column_names=True, index_number=nav.CTDB_DATA_IDXNO, field_numbers_to_ignore=[0])


nav.Logger.log("CLOSE TABLE")

try:
  my_table.close()
  nav.Logger.log("\tClosed " + my_table.table_name + " table.")

except nav.DatabaseError as e:
    nav.Logger.log("\tCould not close " + my_table.table_name + " table.")
    nav.Logger.exit_with_faircom_error(e)

disconnect()

input("\nDone! Press <ENTER> key to exit . . .")
