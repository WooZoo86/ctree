'
' Tutorial1.vb
'
' Public domain Visual Basic ISAM .NET example
'
' FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
'
' The goal of this tutorial is to introduce the most basic ISAM .NET API
' to accomplish creating and manipulating a table through the ctreeServer
'
' Functionally, Me application will perform the following:
'  1.  Logon onto a session
'  2.  Add 1 table with some fields
'  3.  Populate the table with a few records
'  4.  Display the contents of the table
'


Imports System
Imports FairCom.CtreeDb
Imports FairCom.CtreeDb.ENUMS




Module Tutorial1HL

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

      Console.WriteLine(vbCrLf + "Press <ENTER> key to exit . . .")
      Console.ReadLine()

   End Sub


   ' Initialize()
   ' 
   ' Perform the minimum requirement of logging onto the c-tree Server

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

      Dim do_create As Boolean = False

      Console.WriteLine("DEFINE")

      Try
         Console.WriteLine(ControlChars.Tab + "Open table...")
         MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN)
      Catch
         ' table does not exist. Try to create it
         do_create = True
      End Try

      If (do_create) Then
         ' create the table
         Console.WriteLine(ControlChars.Tab + "Add fields...")
         Try
            MyTable.AddField("cm_custnumb", FIELD_TYPE.FSTRING, 4)
            MyTable.AddField("cm_custzipc", FIELD_TYPE.FSTRING, 9)
            MyTable.AddField("cm_custstat", FIELD_TYPE.FSTRING, 2)
            MyTable.AddField("cm_custrtng", FIELD_TYPE.FSTRING, 1)
            MyTable.AddField("cm_custname", FIELD_TYPE.VSTRING, 47)
            MyTable.AddField("cm_custaddr", FIELD_TYPE.VSTRING, 47)
            MyTable.AddField("cm_custcity", FIELD_TYPE.VSTRING, 47)

            Console.WriteLine(ControlChars.Tab + "Create table...")
            MyTable.Create("custmast", CREATE_MODE.NORMAL_CREATE)

            MyTable.Open("custmast", OPEN_MODE.NORMAL_OPEN)
         Catch E As CTException
            Handle_Exception(E)
         End Try

      Else
         Check_Table_Mode(MyTable)
      End If

   End Sub


   '
   ' Manage()
   '
   ' This function performs simple record functions of add, delete and gets
   '

   Sub Manage()

      Console.WriteLine("MANAGE")

      ' delete any existing records
      Delete_Records()

      ' populate the table with data
      Add_Records()

      ' display contents of table
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
   ' Delete_Records()
   '
   ' This function deletes all the records in the table
   '

   Sub Delete_Records()

      Dim found As Boolean

      Console.WriteLine(ControlChars.Tab + "Delete records...")
      Try
         ' read first record
         found = MyRecord.First()

         While (found)  ' while records are found
            ' delete record
            MyRecord.Delete()
            ' read next record
            found = MyRecord.Next()
         End While
      Catch E As CTException
         Handle_Exception(E)
      End Try

   End Sub


   '
   ' Add_Records()
   '
   ' This function adds records to a table in the database from an
   ' array of strings
   '

   Public Structure DATA_RECORD
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

   Sub Add_Records()

      Dim data(3) As DATA_RECORD
      data(0) = New DATA_RECORD("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange")
      data(1) = New DATA_RECORD("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford")
      data(2) = New DATA_RECORD("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta")
      data(3) = New DATA_RECORD("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia")
      Dim nRecords As Integer = data.Length

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

' end of Tutorial1.vb
