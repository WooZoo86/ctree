import FairCom.CtreeDb.*;
import FairCom.CtreeDb.Types.*;
import java.io.*;
import java.math.BigDecimal;
import java.util.Calendar;

/**
 *
 * @author FairCom Corporation
 */
public class JTDB_Tutorial4 {

    static CTSession MySession;
    static CTTable tableCustOrdr;
    static CTTable tableOrdrItem;
    static CTTable tableItemMast;
    static CTTable tableCustMast;
    static CTRecord recordCustOrdr;
    static CTRecord recordOrdrItem;
    static CTRecord recordItemMast;
    static CTRecord recordCustMast;

    public static void main(String[] args) throws IOException, CTException {
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
            // allocate the session object
            MySession = new CTSession(SESSION_TYPE.CTREE);

            // allocate the table objects
            tableCustOrdr = new CTTable(MySession);
            tableOrdrItem = new CTTable(MySession);
            tableItemMast = new CTTable(MySession);
            tableCustMast = new CTTable(MySession);

            // allocate the record objects
            recordCustOrdr = new CTRecord(tableCustOrdr);
            recordOrdrItem = new CTRecord(tableOrdrItem);
            recordItemMast = new CTRecord(tableItemMast);
            recordCustMast = new CTRecord(tableCustMast);
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
        System.out.println("DEFINE");

        Create_CustomerMaster_Table();
        Create_CustomerOrders_Table();
        Create_OrderItems_Table();
        Create_ItemMaster_Table();
    }

    //
    // Manage()
    //
    // Populates table and perform a simple query
    //
    static void Manage() throws IOException, CTException {
        System.out.println("MANAGE");

        // populate the tables with data
        Add_CustomerMaster_Records();
        Add_ItemMaster_Records();

        Add_Transactions();

        // display the orders and their items
        Display_CustomerOrders();
        Display_OrderItems();
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
            // close tables
            System.out.println("\tClose tables...");
            tableCustMast.Close();
            tableCustOrdr.Close();
            tableOrdrItem.Close();
            tableItemMast.Close();

            // logout
            System.out.println("\tLogout...");
            MySession.Logoff();
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Create_CustomerMaster_Table()
    //
    // Open table CustomerMaster, if it exists. Otherwise create it
    // along with its indices and open it
    //
    static void Create_CustomerMaster_Table() throws IOException {
        boolean do_create = false;

        // define table CustomerMaster
        System.out.println("\ttable CustomerMaster");
        try {
            tableCustMast.Open("custmast", OPEN_MODE.NORMAL);
        } catch (CTException E) {
            // table does not exist
            do_create = true;
        }

        if (do_create) {
            try {
                // define table fields
                CTField field1 = tableCustMast.AddField("cm_custnumb", FIELD_TYPE.CHARS, 4);
                tableCustMast.AddField("cm_custzipc", FIELD_TYPE.CHARS, 9);
                tableCustMast.AddField("cm_custstat", FIELD_TYPE.CHARS, 2);
                tableCustMast.AddField("cm_custratg", FIELD_TYPE.CHARS, 1);
                tableCustMast.AddField("cm_custname", FIELD_TYPE.VARCHAR, 47);
                tableCustMast.AddField("cm_custaddr", FIELD_TYPE.VARCHAR, 47);
                tableCustMast.AddField("cm_custcity", FIELD_TYPE.VARCHAR, 47);

                // define index
                CTIndex index1 = tableCustMast.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, false, false);
                index1.AddSegment(field1, SEG_MODE.SCHSEG);

                // create table
                System.out.println("\tCreate table...");
                tableCustMast.Create("custmast", CREATE_MODE.TRNLOG);

                // open table
                System.out.println("\tOpen table...");
                tableCustMast.Open("custmast", OPEN_MODE.NORMAL);
            } catch (CTException E) {
                Handle_Exception(E);
            }
        } else {
            Check_Table_Mode(tableCustMast);

            // confirm the index exists, if not then add the index
            //
            // this scenario arises out of the fact that this table was created in tutorial 1
            // without indexes. The index is now created by the call to ctdbAlterTable

            do_create = false;
            try {
                tableCustMast.GetIndex("cm_custnumb_idx");
            } catch (CTException E) {
                do_create = true;
            }

            if (do_create) {
                try {
                    CTField field1 = tableCustMast.GetField("cm_custnumb");
                    CTIndex index1 = tableCustMast.AddIndex("cm_custnumb_idx", KEY_TYPE.FIXED_INDEX, false, false);
                    index1.AddSegment(field1, SEG_MODE.SCHSEG);
                    tableCustMast.Alter(ALTER_TABLE.NORMAL);
                } catch (CTException E) {
                    Handle_Exception(E);
                }
            }
        }
    }

    //
    // Create_CustomerOrders_Table()
    //
    // Open table CustomerOrders, if it exists. Otherwise create it
    // along with its indices and open it
    //
    static void Create_CustomerOrders_Table() throws IOException {
        boolean do_create = false;

        // define table CustomerOrders
        System.out.println("\ttable CustomerOrders");
        try {
            tableCustOrdr.Open("custordr", OPEN_MODE.NORMAL);
        } catch (CTException E) {
            // table does not exist
            do_create = true;
        }

        if (do_create) {
            try {
                // define table fields
                tableCustOrdr.AddField("co_ordrdate", FIELD_TYPE.DATE, 4);
                tableCustOrdr.AddField("co_promdate", FIELD_TYPE.DATE, 4);
                CTField field1 = tableCustOrdr.AddField("co_ordrnumb", FIELD_TYPE.CHARS, 6);
                CTField field2 = tableCustOrdr.AddField("co_custnumb", FIELD_TYPE.CHARS, 4);

                // define indices
                CTIndex index1 = tableCustOrdr.AddIndex("co_ordrnumb_idx", KEY_TYPE.LEADING_INDEX, false, false);
                index1.AddSegment(field1, SEG_MODE.SCHSEG);
                CTIndex index2 = tableCustOrdr.AddIndex("co_custnumb_idx", KEY_TYPE.LEADING_INDEX, true, false);
                index2.AddSegment(field2, SEG_MODE.SCHSEG);

                // create table
                System.out.println("\tCreate table...");
                tableCustOrdr.Create("custordr", CREATE_MODE.TRNLOG);

                // open table
                System.out.println("\tOpen table...");
                tableCustOrdr.Open("custordr", OPEN_MODE.NORMAL);
            } catch (CTException E) {
                Handle_Exception(E);
            }
        } else {
            Check_Table_Mode(tableCustOrdr);
        }
    }

    //
    // Create_OrderItems_Table()
    //
    // Open table OrderItems, if it exists. Otherwise create it
    // along with its indices and open it
    //
    static void Create_OrderItems_Table() throws IOException {
        boolean do_create = false;

        // define table OrderItems
        System.out.println("\ttable OrderItems");
        try {
            tableOrdrItem.Open("ordritem", OPEN_MODE.NORMAL);
        } catch (CTException E) {
            // table does not exist
            do_create = true;
        }

        if (do_create) {
            try {
                // define table fields
                CTField field1 = tableOrdrItem.AddField("oi_sequnumb", FIELD_TYPE.SMALLINT, 2);
                tableOrdrItem.AddField("oi_quantity", FIELD_TYPE.SMALLINT, 2);
                CTField field2 = tableOrdrItem.AddField("oi_ordrnumb", FIELD_TYPE.CHARS, 6);
                CTField field3 = tableOrdrItem.AddField("oi_itemnumb", FIELD_TYPE.CHARS, 5);

                // define indices
                CTIndex index1 = tableOrdrItem.AddIndex("oi_ordrnumb_idx", KEY_TYPE.LEADING_INDEX, false, false);
                index1.AddSegment(field2, SEG_MODE.SCHSEG);
                index1.AddSegment(field1, SEG_MODE.SCHSEG);
                CTIndex index2 = tableOrdrItem.AddIndex("oi_itemnumb_idx", KEY_TYPE.LEADING_INDEX, true, false);
                index2.AddSegment(field3, SEG_MODE.SCHSEG);

                // create table
                System.out.println("\tCreate table...");
                tableOrdrItem.Create("ordritem", CREATE_MODE.TRNLOG);

                // open table
                System.out.println("\tOpen table...");
                tableOrdrItem.Open("ordritem", OPEN_MODE.NORMAL);
            } catch (CTException E) {
                Handle_Exception(E);
            }
        } else {
            Check_Table_Mode(tableOrdrItem);
        }
    }

    //
    // Create_ItemMaster_Table()
    //
    // Open table ItemMaster, if it exists. Otherwise create it
    // along with its indices and open it
    //
    static void Create_ItemMaster_Table() throws IOException {
        boolean do_create = false;

        // define table ItemMaster
        System.out.println("\ttable ItemMaster");
        try {
            tableItemMast.Open("itemmast", OPEN_MODE.NORMAL);
        } catch (CTException E) {
            // table does not exist
            do_create = true;
        }

        if (do_create) {
            try {
                // define table fields
                tableItemMast.AddField("im_itemwght", FIELD_TYPE.INTEGER, 4);
                tableItemMast.AddField("im_itempric", FIELD_TYPE.MONEY, 4);
                CTField field1 = tableItemMast.AddField("im_itemnumb", FIELD_TYPE.CHARS, 5);
                tableItemMast.AddField("im_itemdesc", FIELD_TYPE.VARCHAR, 47);

                // define indices
                CTIndex index1 = tableItemMast.AddIndex("im_itemnumb_idx", KEY_TYPE.LEADING_INDEX, false, false);
                index1.AddSegment(field1, SEG_MODE.SCHSEG);

                // create table
                System.out.println("\tCreate table...");
                tableItemMast.Create("itemmast", CREATE_MODE.TRNLOG);

                // open table
                System.out.println("\tOpen table...");
                tableItemMast.Open("itemmast", OPEN_MODE.NORMAL);
            } catch (CTException E) {
                Handle_Exception(E);
            }
        } else {
            Check_Table_Mode(tableItemMast);
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

            // check if table is not under transaction processing control
            if ((mode & CREATE_MODE.TRNLOG) == 0) {
                // change file mode to enable transaction processing
                mode |= CREATE_MODE.TRNLOG;
                table.UpdateCreateMode(mode);
            }
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Add_CustomerMaster_Records()
    //
    // This function adds records to table CustomerMaster from an
    // array of Strings
    //
    public static class CUSTOMER_DATA {
        // struct members

        public String number, zipcode, state, rating, name, address, city;
        // struct constructor

        public CUSTOMER_DATA(String number, String zipcode, String state, String rating, String name, String address, String city) {
            this.number = number;
            this.zipcode = zipcode;
            this.state = state;
            this.rating = rating;
            this.name = name;
            this.address = address;
            this.city = city;
        }
    };

    static void Add_CustomerMaster_Records() throws IOException {
        CUSTOMER_DATA[] data = new CUSTOMER_DATA[4];
        data[0] = new CUSTOMER_DATA("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange");
        data[1] = new CUSTOMER_DATA("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford");
        data[2] = new CUSTOMER_DATA("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta");
        data[3] = new CUSTOMER_DATA("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia");
        int nRecords = data.length;

        Delete_Records(recordCustMast);

        System.out.println("\tAdd records in table CustomerMaster...");

        try {
            // start a transaction
            MySession.Begin();

            for (int i = 0; i < nRecords; i++) {
                recordCustMast.Clear();

                // populate record buffer with data
                recordCustMast.SetFieldAsString(0, data[i].number);
                recordCustMast.SetFieldAsString(1, data[i].zipcode);
                recordCustMast.SetFieldAsString(2, data[i].state);
                recordCustMast.SetFieldAsString(3, data[i].rating);
                recordCustMast.SetFieldAsString(4, data[i].name);
                recordCustMast.SetFieldAsString(5, data[i].address);
                recordCustMast.SetFieldAsString(6, data[i].city);

                // add record
                recordCustMast.Write();
            }

            // commit transaction
            MySession.Commit();
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Add_ItemMaster_Records()
    //
    // This function adds records to table ItemMaster from an
    // array of Strings
    //
    public static class ITEM_DATA {
        // struct members

        public int weight;
        public BigDecimal price;
        public String itemnum, description;
        // struct constructor

        public ITEM_DATA(int weight, BigDecimal price, String itemnum, String description) {
            this.weight = weight;
            this.price = price;
            this.itemnum = itemnum;
            this.description = description;
        }
    };

    static void Add_ItemMaster_Records() throws IOException {
        ITEM_DATA[] data = new ITEM_DATA[4];
        data[0] = new ITEM_DATA(10, new BigDecimal("19.95"), "1", "Hammer");
        data[1] = new ITEM_DATA(3, new BigDecimal("9.99"), "2", "Wrench");
        data[2] = new ITEM_DATA(4, new BigDecimal("16.59"), "3", "Saw");
        data[3] = new ITEM_DATA(1, new BigDecimal("3.98"), "4", "Pliers");
        int nRecords = data.length;

        Delete_Records(recordItemMast);

        System.out.println("\tAdd records in table ItemMaster...");

        try {
            // start a transaction
            MySession.Begin();

            for (int i = 0; i < nRecords; i++) {
                recordItemMast.Clear();

                // populate record buffer with data
                recordItemMast.SetFieldAsInt(0, data[i].weight);
                recordItemMast.SetFieldAsBigDecimal(1, data[i].price);
                recordItemMast.SetFieldAsString(2, data[i].itemnum);
                recordItemMast.SetFieldAsString(3, data[i].description);

                // add record
                recordItemMast.Write();
            }

            // commit transaction
            MySession.Commit();
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Delete_Records()
    //
    // This function deletes all the records in the table
    //
    static void Delete_Records(CTRecord record) throws IOException {
        boolean found;

        System.out.println("\tDelete records...");

        try {
            // write lock required for transaction updates
            record.Lock(LOCK_MODE.WRITE);

            // start a transaction
            record.Begin();

            // read first record
            found = record.First();

            while (found) // while records are found
            {
                // delete record
                record.Delete();
                // read next record
                found = record.Next();
            }

            // commit transaction
            record.Commit();

            // free locks
            record.Unlock();
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Add_Transactions()
    //
    // Add an Order and associated Items "as a transaction" to their
    // respective tables.  A transaction is committed or aborted if the
    // customer number on the order is confirmed valid.  Likewise each
    // item in the order is verified to be a valid item.  SavePoints are
    // established as an order is processed, allowing a transaction to
    // rollback to the previously verified item
    //
    public static class ORDER_DATA {
        // struct members

        public Calendar orderdate, promdate;
        public String ordernum, custnum;
        // struct constructor

        public ORDER_DATA(Calendar orderdate, Calendar promdate, String ordernum, String custnum) {
            this.orderdate = orderdate;
            this.promdate = promdate;
            this.ordernum = ordernum;
            this.custnum = custnum;
        }
    };

    public static class ORDERITEM_DATA {
        // struct members

        public String ordernum;
        public int seqnumber, quantity;
        public String itemnum;
        // struct constructor

        public ORDERITEM_DATA(String ordernum, int seqnumber, int quantity, String itemnum) {
            this.ordernum = ordernum;
            this.seqnumber = seqnumber;
            this.quantity = quantity;
            this.itemnum = itemnum;
        }
    };

    static void Add_Transactions() throws IOException, CTException {
        ORDER_DATA[] orders = new ORDER_DATA[3];
        Calendar orddate0 = Calendar.getInstance();
        Calendar promdate0 = Calendar.getInstance();
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        orddate0.set(2002, 9 - 1, 01);
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        promdate0.set(2002, 9 - 1, 05);
        orders[0] = new ORDER_DATA(orddate0, promdate0, "1", "1001");
        Calendar orddate1 = Calendar.getInstance();
        Calendar promdate1 = Calendar.getInstance();
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        orddate1.set(2002, 9-1, 02);
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        promdate1.set(2002, 9-1, 06);
        orders[1] = new ORDER_DATA(orddate1, promdate1, "2", "9999"); // bad customer number
        Calendar orddate2 = Calendar.getInstance();
        Calendar promdate2 = Calendar.getInstance();
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        orddate1.set(2002, 9-1, 22);
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        promdate1.set(2002, 9-1, 26);
        orders[2] = new ORDER_DATA(orddate2, promdate2, "3", "1003");
        int nOrders = orders.length;

        ORDERITEM_DATA[] items = new ORDERITEM_DATA[6];
        items[0] = new ORDERITEM_DATA("1", 1, 2, "1");
        items[1] = new ORDERITEM_DATA("1", 2, 1, "2");
        items[2] = new ORDERITEM_DATA("2", 1, 1, "3");
        items[3] = new ORDERITEM_DATA("2", 2, 3, "4");
        items[4] = new ORDERITEM_DATA("3", 1, 2, "3");
        items[5] = new ORDERITEM_DATA("3", 2, 2, "99");   // bad item number
        int nItems = items.length;

        int savepoint;
        int j = 0;

        Delete_Records(recordCustOrdr);
        Delete_Records(recordOrdrItem);

        System.out.println("\tAdd transaction records...");

        // process orders
        for (int i = 0; i < nOrders; i++) {
            // start a transaction
            MySession.Begin();

            try {
                recordCustOrdr.Clear();

                // populate record buffer with order data
                recordCustOrdr.SetFieldAsCalendar(0, orders[i].orderdate);
                recordCustOrdr.SetFieldAsCalendar(1, orders[i].promdate);
                recordCustOrdr.SetFieldAsString(2, orders[i].ordernum);
                recordCustOrdr.SetFieldAsString(3, orders[i].custnum);

                // add order record
                recordCustOrdr.Write();
            } catch (CTException E) {
                // abort transaction on error
                Handle_Exception(E);
            }

            // set transaction savepoint
            savepoint = recordCustOrdr.SetSavePoint();

            // process order items
            while (items[j].ordernum.equals(orders[i].ordernum)) {
                try {
                    recordOrdrItem.Clear();

                    // populate record buffer with order item data
                    recordOrdrItem.SetFieldAsInt(0, items[j].seqnumber);
                    recordOrdrItem.SetFieldAsInt(1, items[j].quantity);
                    recordOrdrItem.SetFieldAsString(2, items[j].ordernum);
                    recordOrdrItem.SetFieldAsString(3, items[j].itemnum);

                    // add order item record
                    recordOrdrItem.Write();

                    // check that item exists in ItemMaster table
                    recordItemMast.Clear();
                    recordItemMast.SetFieldAsString(2, items[j].itemnum);
                    if (!recordItemMast.Find(FIND_MODE.EQUAL)) // if not found, restore back to previous savepoint
                    {
                        recordItemMast.RestoreSavePoint(savepoint);
                    } else // set transaction savepoint
                    {
                        savepoint = recordItemMast.SetSavePoint();
                    }
                } catch (CTException E) {
                    // abort transaction on error
                    Handle_Exception(E);
                }

                // bump to next item
                j++;

                // exit the while loop on last item
                if (j >= nItems) {
                    break;
                }
            }

            // check that customer exists in CustomerMaster table
            recordCustMast.Clear();
            recordCustMast.SetFieldAsString(0, orders[i].custnum);

            // commit or abort the transaction
            if (!recordCustMast.Find(FIND_MODE.EQUAL)) {
                MySession.Abort();
            } else {
                MySession.Commit();
            }
        }
    }

    //
    // Display_CustomerOrders()
    //
    // This function displays the contents of a table. ctdbFirstRecord() and
    // ctdbNextRecord() fetch the record. Then each field is parsed and displayed
    //
    static void Display_CustomerOrders() throws IOException {
        String custnumb;
        String ordrnumb;

        System.out.println("\tCustomerOrder table...");

        try {
            // read first record
            if (recordCustOrdr.First()) {
                do {
                    ordrnumb = recordCustOrdr.GetFieldAsString(2);
                    custnumb = recordCustOrdr.GetFieldAsString(3);

                    // display data
                    System.out.println("\t" + ordrnumb + "\t" + custnumb);
                } // read next record until end of file
                while (recordCustOrdr.Next());
            }
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }

    //
    // Display_OrderItems()
    //
    // This function displays the contents of a table. ctdbFirstRecord() and
    // ctdbNextRecord() fetch the record. Then each field is parsed and displayed
    //
    static void Display_OrderItems() throws IOException {
        String itemnumb;
        String ordrnumb;

        System.out.println("\n\tOrderItems Table...");

        try {
            // read first record
            if (recordOrdrItem.First()) {
                do {
                    // get field data from record buffer
                    ordrnumb = recordOrdrItem.GetFieldAsString(2);
                    itemnumb = recordOrdrItem.GetFieldAsString(3);

                    // display data
                    System.out.println("\t" + ordrnumb + "\t" + itemnumb);
                } // read next record until end of file
                while (recordOrdrItem.Next());
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
