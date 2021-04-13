'
' Tutorial3.vb
'
' Public domain Visual Basic ISAM .NET example
'
' FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
'
' The goal of this tutorial is to introduce the most basic ISAM .NET API
' to accomplish creating and manipulating a table through the ctreeServer
'
' Functionally, this application will perform the following:
'  1.  Logon onto a session
'  2.  Add 1 table with some fields
'  3.  Populate the table with a few records
'  4.  Display the contents of the table
'  5.  Update one record under locking control
'


Imports System
Imports FairCom.CtreeDb
Imports FairCom.CtreeDb.ENUMS



Module Tutorial3HL

   Dim MySession As CTSession
   Dim MyTable As CTTable
   Dim MyRecord As CTRecord

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
         ' allocate objects
         MySession = New CTSession(SESSION_TYPE.CTREE_SESSION)
         MyTable = New CTTable(MySession)
         MyRecord = New CTRecord(MyTable)
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

   End Sub


   '
   ' Manage()
   '
   ' This function performs record adds and updates using locking
   '

   Sub Manage()

      Console.WriteLine("MANAGE")

      ' populate the table with data
      Add_CustomerMaster_Records()

      ' display contents of table
      Display_Records()

      ' update a record under locking control
      Update_CustomerMaster_Record()

      ' display again after update and effects of lock
      Display_Records()

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
         Console.WriteLine(ControlChars.Tab + "Close table...")
         MyTable.Close()

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
         MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN)
      Catch
         ' table does not exist
         do_create = True
      End Try

      If (do_create) Then
         ' define table fields
         Console.WriteLine(ControlChars.Tab + "Add fields...")
         Try
            field1 = MyTable.AddField("cm_custnumb", FIELD_TYPE.FSTRING, 4)
            MyTable.AddField("cm_custzipc", FIELD_TYPE.FSTRING, 9)
            MyTable.AddField("cm_custstat", FIELD_TYPE.FSTRING, 2)
            MyTable.AddField("cm_custratg", FIELD_TYPE.FSTRING, 1)
            MyTable.AddField("cm_custname", FIELD_TYPE.VSTRING, 47)
            MyTable.AddField("cm_custaddr", FIELD_TYPE.VSTRING, 47)
            MyTable.AddField("cm_custcity", FIELD_TYPE.VSTRING, 47)

            ' define index
            index1 = MyTable.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, False, False)
            index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG)

            ' create table
            Console.WriteLine(ControlChars.Tab + "Create table...")
            MyTable.Create("custmast", CREATE_MODE.NORMAL_CREATE)

            ' open table
            Console.WriteLine(ControlChars.Tab + "Open table...")
            MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN)
         Catch E As CTException
            Handle_Exception(E)
         End Try

      Else
         Check_Table_Mode(MyTable)

         ' confirm the index exists, if not then add the index
         '
         ' Me scenario arises out of the fact that Me table was created in tutorial 1
         ' without indexes. The index is now created by the call to ctdbAlterTable

         do_create = False
         Try
            MyTable.GetIndex("cm_custnumb_idx")
         Catch
            do_create = True
         End Try

         If (do_create) Then
            Try
               field1 = MyTable.GetField("cm_custnumb")
               index1 = MyTable.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, False, False)
               index1.AddSegment(field1, SEG_MODE.SCHSEG_SEG)
               MyTable.Alter(ALTER_TABLE.NORMAL)
            Catch E As CTException
               Handle_Exception(E)
            End Try
         End If
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

      Delete_Records(MyRecord)

      Console.WriteLine(ControlChars.Tab + "Add records...")

      Try
         Dim i As Integer
         For i = 0 To nRecords - 1
            MyRecord.Clear()

            ' populate record buffer with data
            MyRecord.SetFieldAsString(0, data(i).number)
            MyRecord.SetFieldAsString(1, data(i).zipcode)
            MyRecord.SetFieldAsString(2, data(i).state)
            MyRecord.SetFieldAsString(3, data(i).rating)
            MyRecord.SetFieldAsString(4, data(i).name)
            MyRecord.SetFieldAsString(5, data(i).address)
            MyRecord.SetFieldAsString(6, data(i).city)

            ' add record
            MyRecord.Write()
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
         ' enable session-wide lock flag
         MySession.Lock(LOCK_MODE.WRITE_BLOCK_LOCK)

         ' read first record
         found = record.First()

         While (found)  ' while records are found
            ' delete record
            record.Delete()
            ' read next record
            found = record.Next()
         End While

         ' reset session-wide locks
         MySession.Unlock()
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Display_Records()
   '
   ' This function displays the contents of a table. First() and Next()
   ' fetch the record. Then each field is parsed and displayed
   '

   Sub Display_Records()

      Dim found As Boolean
      Dim custnumb As String
      Dim custname As String

      Console.Write(ControlChars.Tab + "Display records...")

      Try
         ' read first record
         found = MyRecord.First()

         While (found)
            custnumb = MyRecord.GetFieldAsString(0)
            custname = MyRecord.GetFieldAsString(4)

            Console.WriteLine(ControlChars.NewLine + ControlChars.Tab + ControlChars.Tab + "{0,-8}{1,-20}", custnumb, custname)

            ' read next record
            found = MyRecord.Next()
         End While
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Update_CustomerMaster_Records()
   '
   ' Update one record under locking control to demonstrate the effects
   ' of locking
   '

   Sub Update_CustomerMaster_Record()

      Console.WriteLine(ControlChars.Tab + "Update Record...")

      Try
         ' enable session-wide lock flag
         MySession.Lock(LOCK_MODE.WRITE_BLOCK_LOCK)

         MyRecord.Clear()
         MyRecord.SetFieldAsString(0, "1003")
         ' find record by customer number
         If (MyRecord.Find(FIND_MODE.EQ)) Then
            MyRecord.SetFieldAsString(4, "KEYON DOOLING")
            ' rewrite record
            MyRecord.Write()

            Console.WriteLine(ControlChars.Tab + "Press <ENTER> key to unlock")
            Console.ReadLine()
         End If

         ' reset session-wide locks
         MySession.Unlock()
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

' end of Tutorial3.vb
