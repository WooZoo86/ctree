import FairCom.CtreeDb.*;
import FairCom.CtreeDb.Types.*;
import java.io.*;
import java.math.BigDecimal;
import java.util.Calendar;

/**
 *
 * @author FairCom Corporation
 */
public class JTDB_Tutorial2 {

    static CTSession MySession;
    static CTTable tableCustOrdr;
    static CTTable tableOrdrItem;
    static CTTable tableItemMast;
    static CTTable tableCustMast;
    static CTRecord recordCustOrdr;
    static CTRecord recordOrdrItem;
    static CTRecord recordItemMast;
    static CTRecord recordCustMast;

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
    static void Manage() throws IOException {
        int quantity;
        BigDecimal price, total;
        String itemnumb, custnumb, ordrnumb, custname;
        boolean isOrderFound, isItemFound;

        System.out.println("MANAGE");

        // populate the tables with data
        Add_CustomerMaster_Records();
        Add_CustomerOrders_Records();
        Add_OrderItems_Records();
        Add_ItemMaster_Records();

        // perform a query:
        // list customer name and total amount per order

        // name               total
        // @@@@@@@@@@@@@      $xx.xx

        // for each order in the CustomerOrders table
        //    fetch order number
        //    fetch customer number
        //    fetch name from CustomerMaster table based on customer number
        //    for each order item in OrderItems table
        //       fetch item quantity
        //       fetch item number
        //       fetch item price from ItemMaster table based on item number
        //    next
        // next

        System.out.println("\n\tQuery Results");

        try {
            // get the first order
            isOrderFound = recordCustOrdr.First();

            while (isOrderFound) // for each order in the CustomerOrders table
            {
                // fetch order number
                ordrnumb = recordCustOrdr.GetFieldAsString(2);
                // fetch customer number
                custnumb = recordCustOrdr.GetFieldAsString(3);

                // fetch name from CustomerMaster table based on customer number
                recordCustMast.Clear();
                recordCustMast.SetFieldAsString(0, custnumb);
                if (!recordCustMast.Find(FIND_MODE.EQUAL)) {
                    continue;   // not possible in our canned example
                }
                custname = recordCustMast.GetFieldAsString(4);

                // fetch item price from OrderItems table
                recordOrdrItem.Clear();
                recordOrdrItem.SetFieldAsString(2, ordrnumb);
                // define a recordset to scan only items applicable to this order
                recordOrdrItem.RecordSetOn(6);
                isItemFound = recordOrdrItem.First();

                total = BigDecimal.ZERO;
                while (isItemFound) // for each order item in OrderItems table
                {
                    // fetch item quantity
                    quantity = recordOrdrItem.GetFieldAsInt(1);
                    // fetch item number
                    itemnumb = recordOrdrItem.GetFieldAsString(3);

                    // fetch item price from ItemMaster table based on item number
                    recordItemMast.Clear();
                    recordItemMast.SetFieldAsString(2, itemnumb);
                    recordItemMast.Find(FIND_MODE.EQUAL);
                    price = recordItemMast.GetFieldAsBigDecimal(1);

                    // calculate order total
                    total = total.add(price.multiply(new BigDecimal(quantity)));

                    isItemFound = recordOrdrItem.Next();
                }

                recordOrdrItem.RecordSetOff();

                // output data to stdout
                System.out.println("\t" + custname + "\t" + total);

                // read next order
                if (!recordCustOrdr.Next()) {
                    isOrderFound = false;
                }
            }
        } catch (CTException E) {
            Handle_Exception(E);
        }
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
                tableCustMast.Create("custmast", CREATE_MODE.NORMAL);

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
                tableCustOrdr.Create("custordr", CREATE_MODE.NORMAL);

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
                tableOrdrItem.Create("ordritem", CREATE_MODE.NORMAL);

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
                tableItemMast.Create("itemmast", CREATE_MODE.NORMAL);

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
            for (int i = 0; i
                    < nRecords; i++) {
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
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }
    //
    // Add_CustomerOrders_Records()
    //
    // This function adds records to table CustomerOrders from an
    // array of Strings
    //

    public static class ORDER_DATA {
        // struct members

        public Calendar orderdate, promisedate;
        public String ordernum, customernum;
        // struct constructor

        public ORDER_DATA(Calendar orderdate, Calendar promisedate, String ordernum, String customernum) {
            this.orderdate = orderdate;
            this.promisedate = promisedate;
            this.ordernum = ordernum;
            this.customernum = customernum;
        }
    };

    static void Add_CustomerOrders_Records() throws IOException {
        ORDER_DATA[] data = new ORDER_DATA[2];
        Calendar orddate0 = Calendar.getInstance();
        Calendar promdate0 = Calendar.getInstance();
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        orddate0.set(2002, 9-1, 01);
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        promdate0.set(2002, 9-1, 05);
        data[0] = new ORDER_DATA(orddate0, promdate0, "1", "1001");
        Calendar orddate1 = Calendar.getInstance();
        Calendar promdate1 = Calendar.getInstance();
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        orddate1.set(2002, 9-1, 02);
        //Java.util.Calendar.MONTH is Zero Based. ie: January = 0
        promdate1.set(2002, 9-1, 06);
        data[1] = new ORDER_DATA(orddate1, promdate1, "2", "1002");

        int nRecords = data.length;
        
        Delete_Records(recordCustOrdr);

        System.out.println("\tAdd records in table CustomerOrders...");

        try {
            for (int i = 0; i
                    < nRecords; i++) {
                recordCustOrdr.Clear();

                // populate record buffer with data
                recordCustOrdr.SetFieldAsCalendar(0, data[i].orderdate);
                recordCustOrdr.SetFieldAsCalendar(1, data[i].promisedate);
                recordCustOrdr.SetFieldAsString(2, data[i].ordernum);
                recordCustOrdr.SetFieldAsString(3, data[i].customernum);

                // add record
                recordCustOrdr.Write();
            }
        } catch (CTException E) {
            Handle_Exception(E);
        }
    }
    //
    // Add_OrderItems_Records()
    //
    // This function adds records to table OrderItems from an
    // array of Strings
    //

    public static class ORDERITEM_DATA {
        // struct members

        public int sequencenum, quantity;
        public String ordernum, itemnum;
        // struct constructor

        public ORDERITEM_DATA(
                int sequencenum, int quantity, String ordernum, String itemnum) {
            this.sequencenum = sequencenum;
            this.quantity = quantity;
            this.ordernum = ordernum;
            this.itemnum = itemnum;
        }
    };

    static void Add_OrderItems_Records() throws IOException {
        ORDERITEM_DATA[] data = new ORDERITEM_DATA[4];
        data[0] = new ORDERITEM_DATA(1, 2, "1", "1");
        data[1] = new ORDERITEM_DATA(2, 1, "1", "2");
        data[2] = new ORDERITEM_DATA(3, 1, "1", "3");
        data[3] = new ORDERITEM_DATA(1, 3, "2", "3");

        int nRecords = data.length;

        Delete_Records(
                recordOrdrItem);

        System.out.println("\tAdd records in table OrderItems...");

        try {
            for (int i = 0; i
                    < nRecords; i++) {
                recordOrdrItem.Clear();

                // populate record buffer with data
                recordOrdrItem.SetFieldAsInt(0, data[i].sequencenum);
                recordOrdrItem.SetFieldAsInt(1, data[i].quantity);
                recordOrdrItem.SetFieldAsString(2, data[i].ordernum);
                recordOrdrItem.SetFieldAsString(3, data[i].itemnum);

                // add record
                recordOrdrItem.Write();
            }
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
    }

    static void Add_ItemMaster_Records() throws IOException {
        ITEM_DATA[] data = new ITEM_DATA[4];
        data[0] = new ITEM_DATA(10, new BigDecimal("19.95"), "1", "Hammer");
        data[1] = new ITEM_DATA(3, new BigDecimal("9.99"), "2", "Wrench");
        data[2] = new ITEM_DATA(4, new BigDecimal("16.59"), "3", "Saw");
        data[3] = new ITEM_DATA(1, new BigDecimal("3.98"), "4", "Pliers");

        int nRecords = data.length;

        Delete_Records(
                recordItemMast);

        System.out.println("\tAdd records in table ItemMaster...");

        try {
            for (int i = 0; i
                    < nRecords; i++) {
                recordItemMast.Clear();

                // populate record buffer with data
                recordItemMast.SetFieldAsInt(0, data[i].weight);
                recordItemMast.SetFieldAsBigDecimal(1, data[i].price);
                recordItemMast.SetFieldAsString(2, data[i].itemnum);
                recordItemMast.SetFieldAsString(3, data[i].description);

                // add record
                recordItemMast.Write();

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
    static void Delete_Records(CTRecord record) throws IOException {
        boolean found;

        System.out.println("\tDelete records...");

        try {
            // read first record
            found = record.First();

            while (found) // while records are found
            {
                // delete record
                record.Delete();
                // read next record
                found = record.Next();
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
