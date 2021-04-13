import FairCom.CtreeDb.*;
import FairCom.CtreeDb.Types.*;
import java.io.*;

/**
 *
 * @author FairCom Corporation
 */
public class JTDB_Tutorial1 {

    static CTSession MySession;
    static CTTable MyTable;
    static CTRecord MyRecord;

    public static void main(String[] args) throws IOException {
        // TODO code application logic here

        Initialize();

        Define();

        Manage();

        Done();

        System.out.println("\nPress <ENTER> key to exit . . .");
        System.in.read();
    }

    static void Initialize() throws IOException {
        System.out.println("INIT");

        try {
            // allocate objects
            MySession = new CTSession(SESSION_TYPE.CTREE);
            MyTable = new CTTable(MySession);
            MyRecord = new CTRecord(MyTable);
        } catch (CTException E) {
            Handle_Exception(E);
        }

        try {
            // connect to server
            System.out.println("\tLogon to server...");
            MySession.Logon("FAIRCOMS", "ADMIN", "ADMIN");
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Define()
    //
    // Open the table, if it exists. Otherwise create and open the table
    //
    static void Define() throws IOException {
        boolean do_create = false;

        System.out.println("DEFINE");

        try {
            System.out.println("\tOpen table...");
            MyTable.Open("custmast", OPEN_MODE.NORMAL);
        } catch (CTException E) {
            // table does not exist. Try to create it
            do_create = true;
        }

        if (do_create) {
            // create the table
            System.out.println("\tAdd fields...");
            try {
                MyTable.AddField("cm_custnumb", FIELD_TYPE.CHARS, 4);
                MyTable.AddField("cm_custzipc", FIELD_TYPE.CHARS, 9);
                MyTable.AddField("cm_custstat", FIELD_TYPE.CHARS, 2);
                MyTable.AddField("cm_custrtng", FIELD_TYPE.CHARS, 1);
                MyTable.AddField("cm_custname", FIELD_TYPE.VARCHAR, 47);
                MyTable.AddField("cm_custaddr", FIELD_TYPE.VARCHAR, 47);
                MyTable.AddField("cm_custcity", FIELD_TYPE.VARCHAR, 47);

                System.out.println("\tCreate table...");
                MyTable.Create("custmast", CREATE_MODE.NORMAL);

                MyTable.Open("custmast", OPEN_MODE.NORMAL);
            } catch (CTException E) {
                Handle_Exception(E);
            }
        } else {
            Check_Table_Mode(MyTable);
        }
    }

    //
    // Manage()
    //
    // This function performs simple record functions of add, delete and gets
    //
    static void Manage() throws IOException {
        System.out.println("MANAGE");

        // delete any existing records
        Delete_Records();

        // populate the table with data
        Add_Records();

        // display contents of table
        Display_Records();
    }

    //
    // Done()
    //
    // This function handles the housekeeping of closing, freeing,
    // disconnecting and logging out of the database
    //
    static void Done() throws IOException {
        System.out.println("DONE");

        try {
            // close table
            System.out.println("\tClose table...");
            MyTable.Close();

            // logout
            System.out.println("\tLogout...");
            MySession.Logoff();

            // This section is only needed for the AppServer DLL model.
            // Stop the AppServer DatabaseEngine
            boolean AppServerModel = true;
            if (AppServerModel) {
                CTSession.StopDatabaseEngine();
            }

        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Check_Table_Mode()
    //
    // Check if existing table has transaction processing flag enabled.
    // If a table is under transaction processing control, modify the
    // table mode to disable transaction processing
    //
    static void Check_Table_Mode(CTTable table) throws IOException {
        try {
            // get table create mode
            int mode = table.GetCreateMode();

            // check if table is under transaction processing control
            if ((mode & CREATE_MODE.TRNLOG) != 0) {
                // change file mode to disable transaction processing
                mode ^= CREATE_MODE.TRNLOG;
                table.UpdateCreateMode(mode);
            }
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Delete_Records()
    //
    // This function deletes all the records in the table
    //
    static void Delete_Records() throws IOException {
        boolean found;

        System.out.println("\tDelete records...");

        try {
            // read first record
            found = MyRecord.First();

            while (found) // while records are found
            {
                // delete record
                MyRecord.Delete();
                // read next record
                found = MyRecord.Next();
            }
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }
    //
    // Add_Records()
    //
    // This function adds records to a table in the database from an
    // array of Strings
    //

    public static class DATA_RECORD {
        // struct members

        public String number, zipcode, state, rating, name, address, city;
        // struct constructor

        public DATA_RECORD(String number, String zipcode, String state, String rating, String name, String address, String city) {
            this.number = number;
            this.zipcode = zipcode;
            this.state = state;
            this.rating = rating;
            this.name = name;
            this.address = address;
            this.city = city;
        }
    };

    static void Add_Records() throws IOException {
        DATA_RECORD[] data = new DATA_RECORD[4];
        data[0] = new DATA_RECORD("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange");
        data[1] = new DATA_RECORD("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford");
        data[2] = new DATA_RECORD("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta");
        data[3] = new DATA_RECORD("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia");


        int nRecords = data.length;

        System.out.println("\tAdd records...");



        try {
            for (int i = 0; i
                    < nRecords; i++) {
                MyRecord.Clear();

                // populate record buffer with data
                MyRecord.SetFieldAsString(0, data[i].number);
                MyRecord.SetFieldAsString(1, data[i].zipcode);
                MyRecord.SetFieldAsString(2, data[i].state);
                MyRecord.SetFieldAsString(3, data[i].rating);
                MyRecord.SetFieldAsString(4, data[i].name);
                MyRecord.SetFieldAsString(5, data[i].address);
                MyRecord.SetFieldAsString(6, data[i].city);

                // add record
                MyRecord.Write();


            }
        } catch (CTException E) {
            Handle_Exception(E);


        }
    }

    //
    // Display_Records()
    //
    // This function displays the contents of a table. First() and Next()
    // fetch the record. Then each field is parsed and displayed
    //
    static void Display_Records() throws IOException {
        boolean found;
        String custnumb;
        String custname;

        System.out.print("\tDisplay records...");



        try {
            // read first record
            found = MyRecord.First();



            while (found) {
                custnumb = MyRecord.GetFieldAsString(0);
                custname = MyRecord.GetFieldAsString(4);

                System.out.println("\n\t" + custnumb + "\t" + custname);

                // read next record
                found = MyRecord.Next();


            }
        } catch (CTException E) {
            Handle_Exception(E);


        }
    }

    //
    // Handle_Exception()
    //
    // This function handles unexpected exceptions. It displays an error message
    // allowing the user to acknowledge before terminating the application
    //
    static void Handle_Exception(CTException err) throws IOException {
        System.out.println("\nERROR: [" + err.GetErrorCode() + "] - " + err.GetErrorMsg());
        System.out.println("*** Execution aborted *** ");
        System.out.println("\nPress <ENTER> key to exit . . .");
        System.in.read();
        System.exit(1);

    }
}
