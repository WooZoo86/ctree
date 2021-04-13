import datetime
import sys
import os

if os.name == 'nt':
    if sys.version_info >= (3,6,0):
        sys.path.append(os.getcwd())
    if sys.version_info >= (3,8,0):
        os.add_dll_directory(os.getcwd())

import pyctree

global connection
global cursor

'''
    tutorial4.py
    
    Public domain Python SQL example
    
    FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
    
    The goal of this tutorial is to introduce the most basic Python SQL commands
    to accomplish creating and manipulating a table through the ctreeServer
    
    Functionally, this application will perform the following:
    1.  Create a database
    2.  Create 4 tables each with an index, several with contraints
    3.  Add records in multiple tables under transaction processing control. Some data will be bad and violate the contraints and be rejected.
    5.  Display the contents of the tables
    '''


'''
    Main()
    
    The main() function implements the concept of "init, define, manage
    and you're done... '
    '''   
def main():
    
    Initialize()
    
    Define()
    
    Manage()
    
    Done()
    
    if sys.version_info >= (3,0,0):
        input("Press <ENTER> key to exit . . .")
    else:
        raw_input("Press <ENTER> key to exit . . .")
   
    return

'''
    Initialize()
    
    Perform the minimum requirement of logging onto the c-tree Server
    '''
def Initialize():
    global connection
    global cursor
    
    print("Init\n")
    print("\tLogon to server...")
    
    ''' Connect to server '''
    try:
        connection = pyctree.connect(user='ADMIN', password='ADMIN', host='127.0.0.1', port='6597')
        cursor = connection.cursor()
        connection.autocommit = False
    except Exception as e:
        Handle_Exception(e)
    return


'''
    Define()
    
    Create the table for containing a list of existing customers
    '''
def Define():
    print ('Define\n')
    
    try:
        print("\tDropping ordritem")
        cursor.execute("DROP TABLE ordritem")
    except Exception as  e:
        Handle_Exception(e)
    
    try:
        print("\tDropping custordr")
        cursor.execute("DROP TABLE custordr")
    except Exception as e:
        Handle_Exception(e)
    
    try:
        print("\tDropping itemmast")
        cursor.execute("DROP TABLE itemmast")
    except Exception as e:
        Handle_Exception(e)
    
    try:
        print("\tDropping custmast")
        cursor.execute("DROP TABLE custmast")
    except Exception as e:
        Handle_Exception(e)

    try:
        ''' create CustomerMaster table '''
        print ("\tCreate CustomerMaster table...")
        cursor.execute("CREATE TABLE custmast (" +
                       "cm_custnumb CHAR(4) PRIMARY KEY, " +
                       "cm_custzipc CHAR(9), " +
                       "cm_custstat CHAR(2), " +
                       "cm_custrtng CHAR(1), " +
                       "cm_custname VARCHAR(47), " +
                       "cm_custaddr VARCHAR(47), " +
                       "cm_custcity VARCHAR(47))"
                       )
            
        ''' create CustomerOrders table '''
        print ("\tCreate CustomerOrders table...")
        cursor.execute("CREATE TABLE custordr (" +
                      "co_ordrdate DATE, " +
                      "co_promdate DATE, " +
                      "co_ordrnumb CHAR(6) PRIMARY KEY, " +
                      "co_custnumb CHAR(4), " +
                      "FOREIGN KEY (co_custnumb) REFERENCES custmast)"
                      )
           
        ''' create OrderItems table '''
        print ("\tCreate OrderItems table...")
        cursor.execute("CREATE TABLE ordritem (" +
                      "oi_sequnumb SMALLINT, " +
                      "oi_quantity SMALLINT, " +
                      "oi_ordrnumb CHAR(6), " +
                      "oi_itemnumb CHAR(5), " +
                      "FOREIGN KEY (oi_itemnumb) REFERENCES itemmast, " +
                      "FOREIGN KEY (oi_ordrnumb) REFERENCES custordr)"
                      )
           
        ''' create ItemMaster table '''
        print ("\tCreate ItemMaster table...")
        cursor.execute("CREATE TABLE itemmast (" +
                      "im_itemwght INTEGER, " +
                      "im_itempric MONEY, " +
                      "im_itemnumb CHAR(5) PRIMARY KEY, " +
                      "im_itemdesc VARCHAR(47))"
                      )
    except Exception as e:
        Handle_Exception(e)
    
    return


'''
    Manage()
    
    This function performs simple record functions of add, delete and gets
    '''
def Manage():
    print ("Manage\n")
    
    add_records()
    
    display_records()
    
    return;


'''
    add_records()
    
    This function adds records to a table in the database from an
    array of strings
    '''
def add_records():
    print ("\tAdd records in table CustomerMaster...")
    
    try:
        data = [
                "('1000','92867','CA','1','Bryan Williams','2999 Regency','Orange')",
                "('1001','61434','CT','1','Michael Jordan','13 Main','Harford')",
                "('1002','73677','GA','1','Joshua Brown','4356 Cambridge','Atlanta')",
                "('1003','10034','MO','1','Keyon Dooling','19771 Park Avenue','Columbia')"
                ]
        ''' add one record at time to table '''
        for row in data:
            cursor.execute("INSERT INTO custmast VALUES " + row)
        connection.commit()
        
        print ("\tAdd records in table ItemMaster...")
        data = [
                "(10,19.95,'1','Hammer')",
                "(3,  9.99,'2','Wrench')",
                "(4, 16.59,'3','Saw')",
                "(1,  3.98,'4','Pliers')"
                ]
        ''' add one record at time to table '''
        for row in data:
            cursor.execute("INSERT INTO itemmast VALUES " + row)
        connection.commit()
        
        print ("\tAdd transaction records...")
        print ("\tContraints violations expected")
        '''bad customer number in 2nd row'''
        orders = [
                ["'09/01/2002'", "'09/05/2002'", "'1'", "'1001'"],
                ["'09/02/2002'", "'09/06/2002'", "'2'", "'9999'"],
                ["'09/22/2002'", "'09/26/2002'", "'3'", "'1003'"]
                ]
                
        ''' bad item number in row 6'''
        items = [
                [1, 2, "'1'", "'1'"],
                [2, 1, "'1'", "'2'"],
                [1, 1, "'2'", "'3'"],
                [2, 3, "'2'", "'4'"],
                [1, 2, "'3'", "'3'"],
                [2, 2, "'3'", "'99'"]
                ]
        ''' add one record at time to table '''
        j = 0
        nItems = len(items)
        for row in orders:
            try:
                queryStr = "INSERT INTO custordr VALUES (" + row[0] + ", " + row[1] + ", " + row[2] + ", " + row[3] + ")"
                cursor.execute(queryStr)
            except Exception as e :
                Handle_Exception(e)
            ''' add one record at time to table '''
            while items[j][2] == row[2]:
                try:
                    queryStr = "\tINSERT INTO ordritem VALUES (" + str(items[j][0]) + ", " + str(items[j][1]) + ", " + items[j][2] + ", " + items[j][3] + ")"
                    cursor.execute(queryStr)
                except Exception as e :
                    Handle_Exception(e)
                j += 1
                if j >= nItems:
                    break
        connection.commit()
    
    except Exception as e :
        Handle_Exception(e);
    return;


'''
    display()
    
    This function displays the contents of a table.
    '''
def display_records():
    print("\tDisplay records...");
    print("\n\tCustomerOrders Table...")
    try:
        ''' execute a query statement '''
        cursor.execute ("SELECT * FROM custordr");
        rows = cursor.fetchall()
                    
        ''' fetch and display each individual record '''
        for row in rows:
            print("\t{0}\t{1}".format(row[2], row[3]))
    except Exception as e:
        Handle_Exception(e)

    print("\n\tOrderItems Table...")
    try:
        ''' execute a query statement '''
        cursor.execute ("SELECT * FROM ordritem");
        rows = cursor.fetchall()
        
        ''' fetch and display each individual record '''
        for row in rows:
            print("\t{0}\t{1}".format(row[2], row[3]))
    except Exception as e:
        Handle_Exception(e)

    return


'''
    Done()
    
    This function handles the housekeeping of closing, freeing,
    disconnecting and logging out of the database
    '''
def Done():
    print("Done")
    try:
        ''' remove tables '''
        cursor.execute ("DROP TABLE ORDRITEM")
        cursor.execute ("DROP TABLE CUSTORDR")
        cursor.execute ("DROP TABLE ITEMMAST")
        cursor.execute ("DROP TABLE CUSTMAST")
    except Exception as e:
        Handle_Exception(e)

    connection.commit()
    cursor.close()
    connection.close()
    print("\tLogout...")
    return


def Handle_Exception(e):

     
    if e.args[0] == -20005:
        return
    else:
        print("error", e)
        if e.args[0] == -20212:
           print("Perhaps your c-tree server is not running?")
        if e.args[0] != -20116:
           print("*** Execution aborted *** \nPress <ENTER> key to exit...")
           sys.exit(1)

main()
