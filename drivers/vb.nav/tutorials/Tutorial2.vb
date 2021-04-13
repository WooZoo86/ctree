' Tutorial2.vs
'
' Public domain Visual Basic ISAM .NET example
'
' FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
'
' The goal of this tutorial is to introduce the most basic ISAM .NET API
' to accomplish creating and manipulating a table through the ctreeServer
'
' Functionally, this application will perform the following:
'  1.  Create a database
'  2.  Create 4 tables each with an index
'  3.  Populate each table with a few records
'  4.  Build a query utilizing the advantage of indexes
'  5.  Output the results of the query
'


Imports System
Imports FairCom.CtreeDb
Imports FairCom.CtreeDb.ENUMS



Module Tutorial2HL

   Dim MySession As CTSession

   Dim tableCustOrdr As CTTable
   Dim tableOrdrItem As CTTable
   Dim tableItemMast As CTTable
   Dim tableCustMast As CTTable

   Dim recordCustOrdr As CTRecord
   Dim recordOrdrItem As CTRecord
   Dim recordItemMast As CTRecord
   Dim recordCustMast As CTRecord


   '
   ' main()
   '
   ' The main() function implements the concept of "init, define, manage
   ' and you're done..."
   '

   Sub Main()

      Initialize()

      Define()

      Manage()

      Done()

      Console.WriteLine(ControlChars.NewLine + "Press <ENTER> key to exit . . .")
      Console.ReadLine()

   End Sub


   '
   ' Initialize()
   '
   ' Perform the minimum requirement of logging onto the c-tree Server
   '

   Sub Initialize()

      Console.WriteLine("INIT")

      Try
         ' allocate the session object
         MySession = New CTSession(SESSION_TYPE.CTREE_SESSION)

         ' allocate the table objects
         tableCustOrdr = New CTTable(MySession)
         tableOrdrItem = New CTTable(MySession)
         tableItemMast = New CTTable(MySession)
         tableCustMast = New CTTable(MySession)

         ' allocate the record objects
         recordCustOrdr = New CTRecord(tableCustOrdr)
         recordOrdrItem = New CTRecord(tableOrdrItem)
         recordItemMast = New CTRecord(tableItemMast)
         recordCustMast = New CTRecord(tableCustMast)
      Catch E As CTException
         Handle_Exception(E)
      End Try

      Try
         ' connect to server
         Console.WriteLine(ControlChars.Tab + "Logon to server...")
         MySession.Logon("FAIRCOMS", "ADMIN", "ADMIN")
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Define()
   '
   ' Open the table, if it exists. Otherwise create and open the table
   '

   Sub Define()

      Console.WriteLine("DEFINE")

      Create_CustomerMaster_Table()
      Create_CustomerOrders_Table()
      Create_OrderItems_Table()
      Create_ItemMaster_Table()

   End Sub


   '
   ' Manage()
   '
   ' Populates table and perform a simple query
   '

   Sub Manage()

      Dim quantity As Integer
      Dim price, total As Double
      Dim itemnumb, custnumb, ordrnumb, custname As String
      Dim isOrderFound, isItemFound As Boolean

      Console.WriteLine("MANAGE")

      ' populate the tables with data
      Add_CustomerMaster_Records()
      Add_CustomerOrders_Records()
      Add_OrderItems_Records()
      Add_ItemMaster_Records()

      ' perform a query:
      ' list customer name and total amount per order

      ' name               total
      ' @@@@@@@@@@@@@      $xx.xx

      ' for each order in the CustomerOrders table
      '    fetch order number
      '    fetch customer number
      '    fetch name from CustomerMaster table based on customer number
      '    for each order item in OrderItems table
      '       fetch item quantity
      '       fetch item number
      '       fetch item price from ItemMaster table based on item number
      '    next
      ' next

      Console.WriteLine(ControlChars.NewLine + ControlChars.Tab + "Query Results")

      Try
         ' get the first order
         isOrderFound = recordCustOrdr.First()

         While (isOrderFound) ' for each order in the CustomerOrders table
            ' fetch order number
            ordrnumb = recordCustOrdr.GetFieldAsString(2)
            ' fetch customer number
            custnumb = recordCustOrdr.GetFieldAsString(3)

            ' fetch name from CustomerMaster table based on customer number
            recordCustMast.Clear()
            recordCustMast.SetFieldAsString(0, custnumb)
            If (recordCustMast.Find(FIND_MODE.EQ) <> True) Then
               Continue While
            End If
            custname = recordCustMast.GetFieldAsString(4)

            ' fetch item price from OrderItems table
            recordOrdrItem.Clear()
            recordOrdrItem.SetFieldAsString(2, ordrnumb)
            ' define a recordset to scan only items applicable to Me order
            recordOrdrItem.RecordSetOn(6)
            isItemFound = recordOrdrItem.First()

            total = 0
            While (isItemFound)   ' for each order item in OrderItems table
               ' fetch item quantity
               recordOrdrItem.GetFieldValue(1, quantity)
               ' fetch item number
               itemnumb = recordOrdrItem.GetFieldAsString(3)

               ' fetch item price from ItemMaster table based on item number
               recordItemMast.Clear()
               recordItemMast.SetFieldAsString(2, itemnumb)
               recordItemMast.Find(FIND_MODE.EQ)
               recordItemMast.GetFieldValue(1, price)

               ' calculate order total
               total += (price * quantity)

               isItemFound = recordOrdrItem.Next()
            End While
            recordOrdrItem.RecordSetOff()

            ' output data to stdout
            Console.WriteLine(ControlChars.Tab + ControlChars.Tab + "{0,-20}{1,-8}", custname, total)

            ' read next order
            If (recordCustOrdr.Next() <> True) Then
               isOrderFound = False
            End If
         End While
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Done()
   '
   ' This function handles the housekeeping of closing, freeing,
   ' disconnecting and logging out of the database
   '

   Sub Done()

      Console.WriteLine("DONE")

      Try
         ' close table
         Console.WriteLine(ControlChars.Tab + "Close tables...")
         tableCustMast.Close()
         tableCustOrdr.Close()
         tableOrdrItem.Close()
         tableItemMast.Close()

         ' logout
         Console.WriteLine(ControlChars.Tab + "Logout...")
         MySession.Logout()
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Create_CustomerMaster_Table()
   '
   ' Open table CustomerMaster, if it exists. Otherwise create it
   ' along with its indices and open it
   '

   Sub Create_CustomerMaster_Table()

      Dim do_create As Boolean = False
      Dim field1 As CTField
      Dim index1 As CTIndex

      ' define table CustomerMaster
      Console.WriteLine(ControlChars.Tab + "table CustomerMaster")
      Try
         tableCustMast.Open("custmast", OPEN_MODE.NORMAL_OPEN)
      Catch
         ' table does not exist
         do_create = True
      End Try

      If (do_create) Then
         ' define table fields
         Console.WriteLine(ControlChars.Tab + "Add fields...")
         Try
            field1 = tableCustMast.AddField("cm_custnumb", FIELD_TYPE.FSTRING, 4)
            tableCustMast.AddField("cm_custzipc", FIELD_TYPE.FSTRING, 9)
            tableCustMast.AddField("cm_custstat", FIELD_TYPE.FSTRING, 2)
            tableCustMast.AddField("cm_custratg", FIELD_TYPE.FSTRING, 1)
            tableCustMast.AddField("cm_custname", FIELD_TYPE.VSTRING, 47)
            tableCustMast.AddField("cm_custaddr", FIELD_TYPE.VSTRING, 47)
            tableCustMast.AddField("cm_custcity", FIELD_TYPE.VSTRING, 47)

            ' define index
            index1 = tableCustMast.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, False, False)
            index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG)

            ' create table
            Console.WriteLine(ControlChars.Tab + "Create table...")
            tableCustMast.Create("custmast", CREATE_MODE.NORMAL_CREATE)

            ' open table
            Console.WriteLine(ControlChars.Tab + "Open table...")
            tableCustMast.Open("custmast", OPEN_MODE.NORMAL_OPEN)
         Catch E As CTException
            Handle_Exception(E)
         End Try

      Else
         Check_Table_Mode(tableCustMast)

         ' confirm the index exists, if not then add the index
         '
         ' Me scenario arises out of the fact that Me table was created in tutorial 1
         ' without indexes. The index is now created by the call to ctdbAlterTable

         do_create = False
         Try
            tableCustMast.GetIndex("cm_custnumb_idx")
         Catch
            do_create = True
         End Try

         If (do_create) Then
            Try
               field1 = tableCustMast.GetField("cm_custnumb")
               index1 = tableCustMast.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, False, False)
               index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG)
               tableCustMast.Alter(ALTER_TABLE.NORMAL)
            Catch E As CTException
               Handle_Exception(E)
            End Try
         End If
      End If

   End Sub


   '
   ' Create_CustomerOrders_Table()
   '
   ' Open table CustomerOrders, if it exists. Otherwise create it
   ' along with its indices and open it
   '

   Sub Create_CustomerOrders_Table()

      Dim do_create As Boolean = False
      Dim field1, field2 As CTField
      Dim index1, index2 As CTIndex

      ' define table CustomerOrders
      Console.WriteLine(ControlChars.Tab + "table CustomerOrders")
      Try
         tableCustOrdr.Open("custordr", OPEN_MODE.NORMAL_OPEN)
      Catch
         ' table does not exist
         do_create = True
      End Try

      If (do_create) Then
         Try
            ' define table fields
            tableCustOrdr.AddField("co_ordrdate", FIELD_TYPE.DATE, 4)
            tableCustOrdr.AddField("co_promdate", FIELD_TYPE.DATE, 4)
            field1 = tableCustOrdr.AddField("co_ordrnumb", FIELD_TYPE.FSTRING, 6)
            field2 = tableCustOrdr.AddField("co_custnumb", FIELD_TYPE.FSTRING, 4)

            ' define indices
            index1 = tableCustOrdr.AddIndex("co_ordrnumb_idx", KEY_TYPE.LEADING_INDEX, False, False)
            index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG)
            index2 = tableCustOrdr.AddIndex("co_custnumb_idx", KEY_TYPE.LEADING_INDEX, True, False)
            index2.AddSegment(field2, SEG_MODE.SCHSEG_SEG)

            ' create table
            Console.WriteLine(ControlChars.Tab + "Create table...")
            tableCustOrdr.Create("custordr", CREATE_MODE.NORMAL_CREATE)

            ' open table
            Console.WriteLine(ControlChars.Tab + "Open table...")
            tableCustOrdr.Open("custordr", OPEN_MODE.NORMAL_OPEN)
         Catch E As CTException
            Handle_Exception(E)
         End Try
      Else
         Check_Table_Mode(tableCustOrdr)
      End If

   End Sub


   '
   ' Create_OrderItems_Table()
   '
   ' Open table OrderItems, if it exists. Otherwise create it
   ' along with its indices and open it
   '

   Sub Create_OrderItems_Table()

      Dim do_create As Boolean = False
      Dim field1, field2, field3 As CTField
      Dim index1, index2 As CTIndex

      ' define table OrderItems
      Console.WriteLine(ControlChars.Tab + "table OrderItems")
      Try
         tableOrdrItem.Open("ordritem", OPEN_MODE.NORMAL_OPEN)
      Catch
         ' table does not exist
         do_create = True
      End Try

      If (do_create) Then
         Try
            ' define table fields
            field1 = tableOrdrItem.AddField("oi_sequnumb", FIELD_TYPE.INT2, 2)
            tableOrdrItem.AddField("oi_quantity", FIELD_TYPE.INT2, 2)
            field2 = tableOrdrItem.AddField("oi_ordrnumb", FIELD_TYPE.FSTRING, 6)
            field3 = tableOrdrItem.AddField("oi_itemnumb", FIELD_TYPE.FSTRING, 5)

            ' define indices
            index1 = tableOrdrItem.AddIndex("oi_ordrnumb_idx", KEY_TYPE.LEADING_INDEX, False, False)
            index1.AddSegment(field2, SEG_MODE.SCHSEG_SEG)
            index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG)
            index2 = tableOrdrItem.AddIndex("oi_itemnumb_idx", KEY_TYPE.LEADING_INDEX, True, False)
            index2.AddSegment(field3, SEG_MODE.SCHSEG_SEG)

            ' create table
            Console.WriteLine(ControlChars.Tab + "Create table...")
            tableOrdrItem.Create("ordritem", CREATE_MODE.NORMAL_CREATE)

            ' open table
            Console.WriteLine(ControlChars.Tab + "Open table...")
            tableOrdrItem.Open("ordritem", OPEN_MODE.NORMAL_OPEN)
         Catch E As CTException
            Handle_Exception(E)
         End Try
      Else
         Check_Table_Mode(tableOrdrItem)
      End If

   End Sub


   '
   ' Create_ItemMaster_Table()
   '
   ' Open table ItemMaster, if it exists. Otherwise create it
   ' along with its indices and open it
   '

   Sub Create_ItemMaster_Table()

      Dim do_create As Boolean = False
      Dim field1 As CTField
      Dim index1 As CTIndex

      ' define table ItemMaster
      Console.WriteLine(ControlChars.Tab + "table ItemMaster")
      Try
         tableItemMast.Open("itemmast", OPEN_MODE.NORMAL_OPEN)
      Catch
         ' table does not exist
         do_create = True
      End Try

      If (do_create) Then
         Try
            ' define table fields
            tableItemMast.AddField("im_itemwght", FIELD_TYPE.INT4, 4)
            tableItemMast.AddField("im_itempric", FIELD_TYPE.MONEY, 4)
            field1 = tableItemMast.AddField("im_itemnumb", FIELD_TYPE.FSTRING, 5)
            tableItemMast.AddField("im_itemdesc", FIELD_TYPE.VSTRING, 47)

            ' define indices
            index1 = tableItemMast.AddIndex("im_itemnumb_idx", KEY_TYPE.LEADING_INDEX, False, False)
            index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG)

            ' create table
            Console.WriteLine(ControlChars.Tab + "Create table...")
            tableItemMast.Create("itemmast", CREATE_MODE.NORMAL_CREATE)

            ' open table
            Console.WriteLine(ControlChars.Tab + "Open table...")
            tableItemMast.Open("itemmast", OPEN_MODE.NORMAL_OPEN)
         Catch E As CTException
            Handle_Exception(E)
         End Try
      Else
         Check_Table_Mode(tableItemMast)
      End If

   End Sub


   '
   ' Check_Table_Mode()
   '
   ' Check if existing table has transaction processing flag enabled.
   ' If a table is under transaction processing control, modify the
   ' table mode to disable transaction processing
   '

   Sub Check_Table_Mode(ByVal table As CTTable)

      Try
         ' get table create mode
         Dim mode As CREATE_MODE = table.GetCreateMode()

         ' check if table is under transaction processing control
         If ((mode And CREATE_MODE.TRNLOG_CREATE) <> 0) Then
            ' change file mode to disable transaction processing
            mode = mode Xor CREATE_MODE.TRNLOG_CREATE
            table.UpdateCreateMode(mode)
         End If
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Add_CustomerMaster_Records()
   '
   ' This function adds records to table CustomerMaster from an
   ' array of strings
   '

   Public Structure CUSTOMER_DATA
      ' struct members
      Public number, zipcode, state, rating, name, address, city As String
      ' struct constructor
      Public Sub New(ByVal number As String, ByVal zipcode As String, ByVal state As String, ByVal rating As String, ByVal name As String, ByVal address As String, ByVal city As String)
         Me.number = number
         Me.zipcode = zipcode
         Me.state = state
         Me.rating = rating
         Me.name = name
         Me.address = address
         Me.city = city
      End Sub
   End Structure

   Sub Add_CustomerMaster_Records()
      Dim data(3) As CUSTOMER_DATA
      data(0) = New CUSTOMER_DATA("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange")
      data(1) = New CUSTOMER_DATA("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford")
      data(2) = New CUSTOMER_DATA("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta")
      data(3) = New CUSTOMER_DATA("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia")
      Dim nRecords As Integer = data.Length

      Delete_Records(recordCustMast)

      Console.WriteLine(ControlChars.Tab + "Add records in table CustomerMaster...")

      Try
         Dim i As Integer
         For i = 0 To nRecords - 1
            recordCustMast.Clear()

            ' populate record buffer with data
            recordCustMast.SetFieldAsString(0, data(i).number)
            recordCustMast.SetFieldAsString(1, data(i).zipcode)
            recordCustMast.SetFieldAsString(2, data(i).state)
            recordCustMast.SetFieldAsString(3, data(i).rating)
            recordCustMast.SetFieldAsString(4, data(i).name)
            recordCustMast.SetFieldAsString(5, data(i).address)
            recordCustMast.SetFieldAsString(6, data(i).city)

            ' add record
            recordCustMast.Write()
         Next
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Add_CustomerOrders_Records()
   '
   ' This function adds records to table CustomerOrders from an
   ' array of strings
   '

   Public Structure ORDER_DATA
      ' struct members
      Public orderdate, promisedate, ordernum, customernum As String
      ' struct constructor
      Public Sub New(ByVal orderdate As String, ByVal promisedate As String, ByVal ordernum As String, ByVal customernum As String)
         Me.orderdate = orderdate
         Me.promisedate = promisedate
         Me.ordernum = ordernum
         Me.customernum = customernum
      End Sub
   End Structure

   Sub Add_CustomerOrders_Records()

      Dim data(1) As ORDER_DATA
      data(0) = New ORDER_DATA("09/01/2002", "09/05/2002", "1", "1001")
      data(1) = New ORDER_DATA("09/02/2002", "09/06/2002", "2", "1002")
      Dim nRecords As Integer = data.Length

      Dim orderdate As CTDate = New CTDate()
      Dim promisedate As CTDate = New CTDate()

      Delete_Records(recordCustOrdr)

      Console.WriteLine(ControlChars.Tab + "Add records in table CustomerOrders...")

      Try
         Dim i As Integer
         For i = 0 To nRecords - 1
            recordCustOrdr.Clear()

            orderdate.StringToDate(data(i).orderdate, DATE_TYPE.MDCY_DATE)
            promisedate.StringToDate(data(i).promisedate, DATE_TYPE.MDCY_DATE)
            ' populate record buffer with data
            recordCustOrdr.SetFieldValue(0, orderdate)
            recordCustOrdr.SetFieldValue(1, promisedate)
            recordCustOrdr.SetFieldAsString(2, data(i).ordernum)
            recordCustOrdr.SetFieldAsString(3, data(i).customernum)

            ' add record
            recordCustOrdr.Write()
         Next
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Add_OrderItems_Records()
   '
   ' This function adds records to table OrderItems from an
   ' array of strings
   '

   Public Structure ORDERITEM_DATA
      ' struct members
      Public sequencenum, quantity As Integer
      Public ordernum, itemnum As String
      ' struct constructor
      Public Sub New(ByVal sequencenum As Integer, ByVal quantity As Integer, ByVal ordernum As String, ByVal itemnum As String)
         Me.sequencenum = sequencenum
         Me.quantity = quantity
         Me.ordernum = ordernum
         Me.itemnum = itemnum
      End Sub
   End Structure

   Sub Add_OrderItems_Records()
      Dim data(3) As ORDERITEM_DATA
      data(0) = New ORDERITEM_DATA(1, 2, "1", "1")
      data(1) = New ORDERITEM_DATA(2, 1, "1", "2")
      data(2) = New ORDERITEM_DATA(3, 1, "1", "3")
      data(3) = New ORDERITEM_DATA(1, 3, "2", "3")
      Dim nRecords As Integer = data.Length

      Delete_Records(recordOrdrItem)

      Console.WriteLine(ControlChars.Tab + "Add records in table OrderItems...")

      Try
         Dim i As Integer
         For i = 0 To nRecords - 1
            recordOrdrItem.Clear()

            ' populate record buffer with data
            recordOrdrItem.SetFieldValue(0, data(i).sequencenum)
            recordOrdrItem.SetFieldValue(1, data(i).quantity)
            recordOrdrItem.SetFieldAsString(2, data(i).ordernum)
            recordOrdrItem.SetFieldAsString(3, data(i).itemnum)

            ' add record
            recordOrdrItem.Write()
         Next
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Add_ItemMaster_Records()
   '
   ' This function adds records to table ItemMaster from an
   ' array of strings
   '

   Public Structure ITEM_DATA
      ' struct members
      Public weight As Integer
      Public price As CTMoney
      Public itemnum, description As String
      ' struct constructor
      Public Sub New(ByVal weight As Integer, ByVal price As CTMoney, ByVal itemnum As String, ByVal description As String)
         Me.weight = weight
         Me.price = price
         Me.itemnum = itemnum
         Me.description = description
      End Sub
   End Structure

   Sub Add_ItemMaster_Records()
      Dim data(3) As ITEM_DATA
      Data(0) = New ITEM_DATA(10, 1995, "1", "Hammer")
      Data(1) = New ITEM_DATA(3, 999, "2", "Wrench")
      Data(2) = New ITEM_DATA(4, 1659, "3", "Saw")
      Data(3) = New ITEM_DATA(1, 398, "4", "Pliers")
      Dim nRecords As Integer = Data.Length

      Delete_Records(recordItemMast)

      Console.WriteLine(ControlChars.Tab + "Add records in table ItemMaster...")

      Try
         Dim i As Integer
         For i = 0 To nRecords - 1
            recordItemMast.Clear()

            ' populate record buffer with data
            recordItemMast.SetFieldValue(0, data(i).weight)
            recordItemMast.SetFieldValue(1, data(i).price)
            recordItemMast.SetFieldAsString(2, Data(i).itemnum)
            recordItemMast.SetFieldAsString(3, Data(i).description)

            ' add record
            recordItemMast.Write()
         Next
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Delete_Records()
   '
   ' This function deletes all the records in the table
   '

   Sub Delete_Records(ByVal record As CTRecord)

      Dim found As Boolean

      Console.WriteLine(ControlChars.Tab + "Delete records...")
      Try
         ' read first record
         found = record.First()

         While (found)  ' while records are found
            ' delete record
            record.Delete()
            ' read next record
            found = record.Next()
         End While
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Handle_Exception()
   '
   ' This function handles unexpected exceptions. It displays an error message
   ' allowing the user to acknowledge before terminating the application
   '

   Sub Handle_Exception(ByVal err As CTException)

      Console.WriteLine()
      Console.WriteLine("ERROR: [{0}] - {1}", err.GetErrorCode(), err.GetErrorMsg())
      Console.WriteLine("*** Execution aborted *** ")
      Console.WriteLine("Press <ENTER> key to exit . . .")
      Console.ReadLine()
      Environment.Exit(1)

   End Sub

End Module

' end of Tutorial2.vb
