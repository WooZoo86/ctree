# -*- coding: Latin-1 -*-

import faircom_nav as nav
from datetime import * 
import csv, sys, os


# ================================================================================
#
# Convert a date string from my CSV file to a Python 'date'
#
# Format of a date string is YearDigits-MonthDigits-DayDigits.  Digits might or might not be zero-padded.
#
# If there is an error, I log it and return None.
#

def convert_string_to_date(date_string, line_number):
  try:
    # There should be 3 pieces which are delimited by dashes.
    pieces = date_string.split("-")
    if len(pieces)!=3:
      nav.Logger.log("Error on line %d - could not convert date string (%s) to date. Does not have 2 dashes." % (line_number, date_string))
      return None
    # Each of the 3 pieces should be pure numeric digits.
    if (not pieces[0].isdecimal()) or (not pieces[1].isdecimal()) or (not pieces[2].isdecimal()) :
      nav.Logger.log("Error on line %d - could not convert date string (%s) to date. Format is incorrect." % (line_number, date_string))
      return None
    # Build a date out of the pieces
    the_date=date(int(pieces[0]), int(pieces[1]), int(pieces[2]))
    return the_date
  except Exception as e:
    nav.Logger.log("Error on line %d - could not convert date string (%s) to date [%s]." % (line_number, date_string, str(e)))
    return None
  

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
# validate_csv_file_fields
# 
# Give me a CSV file that has the column names in the first line, and I will make sure
# they match the 'field_defs' dictionary that is passed into this function.
# 
# I do other error checking as well, and return a dictionary of mappings from CSV file
# columns to c-tree table columns.  This will be used for fast record inserts later.
#

def validate_csv_file_fields(csv_file_path, field_defs):
  field_mappings = {} # the dictionary of mappings I will return
  nav.Logger.log("VALIDATE CSV FILE FIELDS / COLUMNS")

  # does the CSV file actually exist?
  if not os.path.isfile(csv_file_path):
    nav.Logger.exit_with_app_error("Error - the CSV file I am trying to read does not exist.")

  with open(csv_file_path, newline='', encoding='Latin-1') as csvfile:
    csv_reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    # I will look at only the first line in the file - the column names.
    row = next(csv_reader, None) # Read the first row (which has the column names)
    if row is None:
      nav.Logger.exit_with_app_error("Error! The CSV file has no lines / rows.")
    if len(row) == 0:
      nav.Logger.exit_with_app_error("Error! The first line of the CSV contains no column names.")

    print("\tThe CSV file has "+str(len(row))+" columns: ", end='')
    print(', '.join(row))
    # The number of field names in the CSV file should not exceed the number of fields in the 'field_defs' list.
    if len(row) > len(field_defs):
      nav.Logger.exit_with_app_error("Error! The CSV file has more columns (%d) than the field_defs list has (%d)." % (len(row),len(field_defs)))

    # Look at each of the column names in the CSV file and make sure there are no empty or repeated column names, 
    # make sure each uniquely maps to a field in field_defs, etc.
    seen=set() # This set will hold all of the column names I have seen so far.
    for index, csv_column_name in enumerate(row):
      # Is the column name empty / pure white space?
      if csv_column_name.isspace():
        nav.Logger.exit_with_app_error("Error! Column number %d is blank / pure white space." % (index))
      csv_column_name=csv_column_name.strip().lower() # Trim off white space and convert to lower case
      # All column names must start with a letter!
      if not csv_column_name[0].isalpha():
        nav.Logger.exit_with_app_error("Error! Column number %d (%s) does not start with a letter." % (index, csv_column_name))
      # Have I already seen this lower-cased column name?
      # This gives us a case-insensitive compare, which we need, because c-tree column names are case-insensitive.
      if csv_column_name in seen:
        nav.Logger.exit_with_app_error("Error! Column name '%s' occurs more than once in the CSV file (case-insensitive)." % (csv_column_name))
      else:
        seen.add(csv_column_name)
        
      # See if 'field_defs' contains a dictionary whose 'Name' item matches csv_column_name (case-insensitive).
      # If csv_column_name is not found in field_defs, the result is (None, None).
      (column_dict_index, column_dict) = next(((index,dict) for (index,dict) in enumerate(field_defs) if dict["Name"].lower() == csv_column_name), (None, None))
      if column_dict_index is None:
        nav.Logger.exit_with_app_error("Error! The field_defs list does not contain a dictionary whose name matches field #%d (%s) in the CSV file." % (index, csv_column_name))
      else:
        print("\tCSV File column[%d](%s) matches Field_defs[%d](%s)." % (index, csv_column_name, column_dict_index, column_dict['Name'], ))
        # Remember this mapping.
        field_mappings[index]=column_dict_index

  return field_mappings



# ================================================================================
#
# create_table
# 
# I create the database table.
#
# If it already exists, I either delete it (when delete_if_already_exists is True), 
# or I throw an error.
#

def create_table(delete_if_already_exists=False):
  nav.Logger.log("CREATE TABLE")
 
  # If the table already exists, exit with error or delete the table
  if my_database.CTDatabase.FindTable(my_table.table_name) != None: # This searches the DB but not the hard disk.
    if delete_if_already_exists:
      try:
        nav.Logger.log("\tTable '%s' already exists.  Deleting it..." % (my_table.table_name))
        my_table.open(my_database)
        my_table.delete()
        nav.Logger.log("\tDeleted table '%s'." % (my_table.table_name))
      except nav.DatabaseError as e:
        nav.Logger.exit_with_faircom_error(e)
    else:
      nav.Logger.exit_with_app_error("Error!  Table " + my_table.table_name + " already exists.")

  # Later, if it does exist, validate the columns match, and if it does, import it?

  try:
    # Create the new table
    # 'field_defs' is required, 'index_information' and 'identity_field_information' are optional.
    my_table.create(my_database, field_defs=field_defs, index_information=index_information, identity_field_information=identity_field_information)
    nav.Logger.log("\tCreated table '" + my_table.table_name + "'.")

  except nav.DatabaseError as e:
    nav.Logger.log("\tCould not create " + my_table.table_name + " table.")
    if e.error_code == 4093:
      nav.Logger.log("\tIndex file already exists.")
    nav.Logger.exit_with_faircom_error(e)

  return



# ================================================================================
#
# Read the records from the CSV file into the table
#
# If there is trouble processing a field from the CSV file, we skip that line.
# The 'skip_line' deals with that.
#

def fill_table(csv_file_path, field_mappings):
  nav.Logger.log("FILL TABLE")

  try:
    my_table.open(my_database)
    nav.Logger.log("\tOpened " + my_table.table_name + " table in " + str(my_table.get_open_mode()) + " mode.")

  except nav.DatabaseError as e:
      nav.Logger.log("\tCould not open " + my_table.table_name + " table.")
      nav.Logger.exit_with_faircom_error(e)

  try:
    rec = my_table.new_record_buffer()

    my_server.tran_begin()

    rec.SetBatch(nav.CTBATCH_INS , 0, 1000000)

    lines_in_transaction = 0
    with open(csv_file_path, newline='', encoding='Latin-1') as csvfile:
      csv_reader = csv.reader(csvfile, delimiter=',', quotechar='"')
      next(csv_reader, None) # Skip the first row (which has the column names)
      for row in csv_reader:
        # row is a single line from the CSV file.
        
        # Look at each field in this line / row and add it to a new record.  Then write the new record.
        rec.clear()
        skip_line = False
        for index, field in enumerate(row):
          # 'field' is a string that represents one column value that should be stored in a record.
          # Dates need special treatment.
          if field_defs[field_mappings[index]]["Type"]==nav.FieldTypeEnum.DATE:
            ret=convert_string_to_date(field, csv_reader.line_num) # my function which handles my date format
            if ret is None: # if date conversion failed
              skip_line = True
              break
            field = ret

          # I have a special try/except just for the set_field_value call because it can reject all kinds
          # of stuff for being out of range, etc.  I will not exit the program for this, but we will reject
          # this record.
          try:
            rec.set_field_value(field_mappings[index], field)
          except nav.DatabaseError as e:
            nav.Logger.log("Error on line %d, field #%d, value[%s] - [%s]." % (csv_reader.line_num, index+1, field, str(e)))
            skip_line = True
            break
          
        if skip_line:
          continue

        # rec.write()    # add new record to table in non-batch mode.
        rec.InsertBatch() # insert this record into the batch.  Do this instead of rec.Write().
        lines_in_transaction+=1

        # I don't want my transactions to get too big, so I will commit them every so often.
        if lines_in_transaction >= 5000:
          nav.Logger.log("\tCommitting with %d lines in the transaction." % (lines_in_transaction))
          my_server.tran_commit()
          nav.Logger.log("\tCommitted.")
          my_server.tran_begin()
          lines_in_transaction = 0


      my_server.tran_commit()

      rec.EndBatch() # Write any records that are still in the batch buffer.

      nav.Logger.log("\tAdded " + str(rec.get_record_count()) + " new records.")

  except nav.DatabaseError as e:
    my_server.tran_rollback()
    nav.Logger.log("Error while processing line %d from the CSV file." % (csv_reader.line_num))
    nav.Logger.exit_with_faircom_error(e)

  try:
    my_table.close()
    nav.Logger.log("\tClosed " + my_table.table_name + " table.")

  except nav.DatabaseError as e:
      nav.Logger.log("\tCould not close " + my_table.table_name + " table.")
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

# Input file name.  The first line of this file should contain the column names
#csv_file_path = "athletes_big_2.csv"
csv_file_path = "athletes.csv"
# Name of the table I will create
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

nav.Logger.log("CSV file reader for python.nav")

# Table Field / Column Definitions
# This REQUIRED item is a [list] of {dictionaries}, where each dictionary defines one column / field in the table.
# Each field dict must have a name and type, and can have other optional items.
# You must specify at least one field/column when creating a table.
# There must be a column / dictionary whose "Name" matches each field in the CSV file (case-insensitive).
# There can be more columns than the CSV file has, but there cannot be less.
# The fields will be added to the c-tree table in the following order, which does not have 
#   to match the order of the columns in the CSV file.
field_defs =  [
  {  "Name": "id",              "Type": nav.FieldTypeEnum.INT64_SIGNED,     "NotNull": True  }, 
  {  "Name": "name",            "Type": nav.FieldTypeEnum.STRING_FIXED_LENGTH,    "Length": 30     },  
  {  "Name": "ranking",         "Type": nav.FieldTypeEnum.INT16_SIGNED,       "NotNull": True  },  
  {  "Name": "birthDate",       "Type": nav.FieldTypeEnum.DATE,                        },  
  {  "Name": "playerNumber",    "Type": nav.FieldTypeEnum.DECIMAL,     "Scale": 6       },  
  {  "Name": "livedPast2000",   "Type": nav.FieldTypeEnum.BOOLEAN,                        },  
  {  "Name": "earnings",        "Type": nav.FieldTypeEnum.CURRENCY,                    },  
  {  "Name": "favoriteSaying",  "Type": nav.FieldTypeEnum.STRING,                  }, 
]


# This optional item is a [list] of {dictionaries}, where each dictionary defines one index.
#   Each index dict contains the index name, type, two flags, and a LIST of one or more segment-defining dicts.
#     Each segment-defining dict contains the name of the field and a Flags integer.
# We will have an index for the "name" and the "ranking" fields.  Each one gets one key segment.
NAME_INDEX_NAME = "athlete_name_idx"
RANK_INDEX_NAME = "athlete_rank_idx"
index_information = [
  { "IndexName": NAME_INDEX_NAME, "IndexType": nav.FIXED_LENGTH_KEY, "AllowDuplicates": True, "AllowNullKeys": True, \
    "SegmentList": [{"FieldName": "name", "Flags": nav.FIELD_NUMBER}] },
  { "IndexName": RANK_INDEX_NAME, "IndexType": nav.FIXED_LENGTH_KEY, "AllowDuplicates": True, "AllowNullKeys": False, \
    "SegmentList": [{"FieldName": "ranking", "Flags": nav.FIELD_NUMBER}] }
]


# Identity Field Info
# This optional item is a single {dictionary} which MUST have all three items shown here, if it is used.
identity_field_information = { "FieldName": "id", "Seed": 100, "Increment": 2 }


# Validate that the fields in the CSV file are legal and clean and match the field_defs list.
# Also produce a mapping dictionary which maps CSV field numbers to c-tree field numbers.
field_mappings = validate_csv_file_fields(csv_file_path, field_defs)

connect()

create_table(delete_if_already_exists=True)

fill_table(csv_file_path, field_mappings)

disconnect()

input("\nDone! Press <ENTER> key to exit . . .")
