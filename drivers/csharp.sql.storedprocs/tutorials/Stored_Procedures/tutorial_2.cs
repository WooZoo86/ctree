/**
 * Stored Procedure Name: tutorial_2
 *
 * Parameters: 
 *
 *
 * Result Set: 
 *     name  VARCHAR(40)
 *     total  MONEY(8)
 */

#region Using list
using Ctree.SqlSP;
using System;
using System.Collections.Generic;
using System.Text;
#endregion

#region Stored procedure namespace and class header
namespace Tutorials.Stored_Procedures
{
	class tutorial_2 : SqlStoredProc
	{
#endregion

		#region Result Set References
		enum RSCol
		{
			name = 0,
			total = 1,
		}
		#endregion
		private struct DATA_RECORD
		{
			// struct members
			public string number, zipcode, state, rating, name, address, city;

			// struct constructor
			public DATA_RECORD(string number, string zipcode, string state, string rating, string name, string address, string city)
			{
				this.number = number;
				this.zipcode = zipcode;
				this.state = state;
				this.rating = rating;
				this.name = name;
				this.address = address;
				this.city = city;
			}
		};

		private struct ITEM_DATA
		{
			// struct members
			public int weight;
			public decimal price;
			public string itemnum, description;

			// struct constructor
			public ITEM_DATA(int weight, Decimal price, string itemnum, string description)
			{
				this.weight = weight;
				this.price = price;
				this.itemnum = itemnum;
				this.description = description;
			}
		};

		private struct ORDER_DATA
		{
			// struct members
			public DateTime orderdate, promdate;
			public string ordernum, custnum;
			// struct constructor
			public ORDER_DATA(string orderdate, string promdate, string ordernum, string custnum)
			{
				this.orderdate = DateTime.Parse(orderdate);
				this.promdate = DateTime.Parse(promdate);
				this.ordernum = ordernum;
				this.custnum = custnum;
			}
		};

		private struct ORDERITEM_DATA
		{
			// struct members
			public Int16 seqnumber, quantity;
			public string ordernum;
			public string itemnum;

			// struct constructor
			public ORDERITEM_DATA(Int16 seqnumber, Int16 quantity, string ordernum, string itemnum)
			{
				this.seqnumber = seqnumber;
				this.quantity = quantity;
				this.ordernum = ordernum;
				this.itemnum = itemnum;
			}
		};

		private void Create_CustomerMaster_Table()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\ttable Customer Master");

			SqlSpCommand create_cmd = NewSqlSpCommand();
				create_cmd.ExecuteNonQuery(
					"CREATE TABLE custmast (" +
						"cm_custnumb CHAR(4), " +
						"cm_custzipc CHAR(9), " +
						"cm_custstat CHAR(2), " +
						"cm_custrtng CHAR(1), " +
						"cm_custname VARCHAR(47), " +
						"cm_custaddr VARCHAR(47), " +
						"cm_custcity VARCHAR(47))"
				);

				create_cmd.ExecuteNonQuery(
					"CREATE UNIQUE INDEX cm_custnumb_idx ON custmast (cm_custnumb)"
				);
		}

		private void Create_ItemMaster_Table()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\ttable Item Master");

			SqlSpCommand create_cmd = NewSqlSpCommand();
				create_cmd.ExecuteNonQuery(
					 "CREATE TABLE itemmast (" +
						"im_itemwght INTEGER, " +
						"im_itempric MONEY, " +
						"im_itemnumb CHAR(5), " +
						"im_itemdesc VARCHAR(47))"
				 );

				create_cmd.ExecuteNonQuery(
					"CREATE UNIQUE INDEX im_itemnumb_idx ON itemmast (im_itemnumb)"
				);
		}

		private void Create_CustomerOrders_Table()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\ttable CustomerOrders");

			SqlSpCommand create_cmd = NewSqlSpCommand();
				create_cmd.ExecuteNonQuery(
					"CREATE TABLE custordr (" +
						"co_ordrdate DATE, " +
						"co_promdate DATE, " +
						"co_ordrnumb CHAR(6), " +
						"co_custnumb CHAR(4)) "
				 );
				create_cmd.ExecuteNonQuery(
					"CREATE UNIQUE INDEX co_ordrnumb_idx ON custordr (co_ordrnumb)"
				);
				create_cmd.ExecuteNonQuery(
					"CREATE INDEX co_custnumb_idx ON custordr (co_custnumb)"
				);
		}

		private void Create_OrderMaster_Table()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\ttable Order Master");
			SqlSpCommand create_cmd = NewSqlSpCommand();
				create_cmd.ExecuteNonQuery(
						"CREATE TABLE ordritem (" +
							"oi_sequnumb SMALLINT, " +
							"oi_quantity SMALLINT, " +
							"oi_ordrnumb CHAR(6), " +
							"oi_itemnumb CHAR(5))"
				);
				create_cmd.ExecuteNonQuery(
					"CREATE UNIQUE INDEX oi_ordrnumb_idx ON ordritem (oi_ordrnumb, oi_sequnumb)"
				);
				create_cmd.ExecuteNonQuery(
					"CREATE INDEX oi_itemnumb_idx ON ordritem (oi_itemnumb)"
				);
		}


		private void Add_CustomerMaster_Records()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tAdd Customer Master Records...");

			DATA_RECORD[] data = new DATA_RECORD[4];
			data[0] = new DATA_RECORD("1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange");
			data[1] = new DATA_RECORD("1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford");
			data[2] = new DATA_RECORD("1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta");
			data[3] = new DATA_RECORD("1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia");

			SqlSpCommand insert_cmd = NewSqlSpCommand();
			String insert_stmt = "INSERT INTO custmast VALUES (?,?,?,?,?,?,?) ";
			insert_cmd.Prepare(insert_stmt);
				foreach (DATA_RECORD record in data)
				{
					insert_cmd.Parameter[0].Value = record.number;
					insert_cmd.Parameter[1].Value = record.zipcode;
					insert_cmd.Parameter[2].Value = record.state;
					insert_cmd.Parameter[3].Value = record.rating;
					insert_cmd.Parameter[4].Value = record.name;
					insert_cmd.Parameter[5].Value = record.address;
					insert_cmd.Parameter[6].Value = record.city;

					insert_cmd.Execute();
				}
		}

		private void Add_ItemMaster_Records()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tAdd Item Master Records...");

			ITEM_DATA[] data = new ITEM_DATA[4];
			data[0] = new ITEM_DATA(10, new Decimal(19.95), "1", "Hammer");
			data[1] = new ITEM_DATA(3, new Decimal(9.99), "2", "Wrench");
			data[2] = new ITEM_DATA(4, new Decimal(16.59), "3", "Saw");
			data[3] = new ITEM_DATA(1, new Decimal(3.98), "4", "Pliers");
			int nRecords = data.Length;

			SqlSpCommand insert_cmd = NewSqlSpCommand();
			String insert_stmt = "INSERT INTO itemmast VALUES (?,?,?,?) ";
			insert_cmd.Prepare(insert_stmt);
				foreach (ITEM_DATA item in data)
				{
					insert_cmd.Parameter[0].Value = item.weight;
					insert_cmd.Parameter[1].Value = item.price;
					insert_cmd.Parameter[2].Value = item.itemnum;
					insert_cmd.Parameter[3].Value = item.description;

					insert_cmd.Execute();
				}
		}

		private void Add_OrderItems_Records()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tAdd Order Item Records...");

			ORDERITEM_DATA[] data = new ORDERITEM_DATA[4];
			data[0] = new ORDERITEM_DATA(1, 2, "1", "1");
			data[1] = new ORDERITEM_DATA(2, 1, "1", "2");
			data[2] = new ORDERITEM_DATA(3, 1, "1", "3");
			data[3] = new ORDERITEM_DATA(1, 3, "2", "3");

			SqlSpCommand insert_cmd = NewSqlSpCommand();
			String insert_stmt = "INSERT INTO ordritem VALUES (?,?,?,?)";

			insert_cmd.Prepare(insert_stmt);
				foreach (ORDERITEM_DATA item in data)
				{
					insert_cmd.Parameter[0].Value = item.seqnumber;
					insert_cmd.Parameter[1].Value = item.quantity;
					insert_cmd.Parameter[2].Value = item.ordernum;
					insert_cmd.Parameter[3].Value = item.itemnum;

					insert_cmd.Execute();
				}
			return;
		}

		private void Add_CustomerOrder_Records()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tAdd Customer Order Records...");

			ORDER_DATA[] data = new ORDER_DATA[2];
			data[0] = new ORDER_DATA("09/01/2002", "09/05/2002", "1", "1001");
			data[1] = new ORDER_DATA("09/02/2002", "09/06/2002", "2", "1002");

			SqlSpCommand insert_cmd = NewSqlSpCommand();
			String insert_stmt = "INSERT INTO custordr VALUES (?,?,?,?)";

			insert_cmd.Prepare(insert_stmt);

				foreach (ORDER_DATA order in data)
				{
					insert_cmd.Parameter[0].Value = order.orderdate;
					insert_cmd.Parameter[1].Value = order.promdate;
					insert_cmd.Parameter[2].Value = order.ordernum;
					insert_cmd.Parameter[3].Value = order.custnum;

					insert_cmd.Execute();
				}
			return;
		}


		private void Delete_Records(String tablename)
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tDelete Records...");

			SqlSpCommand delete_cmd = NewSqlSpCommand();
			delete_cmd.ExecuteNonQuery("DELETE FROM " + tablename);
		}


		private void Display_Query()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tDisplay Order Items...");
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

			SqlSpCommand display_cmd = NewSqlSpCommand();
			String query_stmt =
				"SELECT cm_custname \"Name\", SUM(im_itempric * oi_quantity) \"Total\" " +
					"FROM custmast, custordr, ordritem, itemmast " +
					"WHERE co_custnumb = cm_custnumb " +
					"   AND co_ordrnumb = oi_ordrnumb " +
					"   AND oi_itemnumb = im_itemnumb " +
					"GROUP BY co_ordrnumb, cm_custname"
			;
			int rv = display_cmd.Prepare(query_stmt);
			if (rv == 0)
			{
				SqlSpRow RSrow = NewResultSetRow();
				display_cmd.Execute();
				while (display_cmd.MoveNext())
				{
					RSrow[0].Value = display_cmd.CurrentRow[0].Value;
					RSrow[1].Value = display_cmd.CurrentRow[1].Value;
					ResultSetAddRow(RSrow);
				}
			}
			else
				Err("Prepare error " + rv.ToString());
		}

		private void Init()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " INIT");

			SqlSpCommand init_cmd = NewSqlSpCommand();
			init_cmd.ExecuteNonQuery("DROP TABLE custmast");
				init_cmd.ExecuteNonQuery("DROP TABLE custordr");
				init_cmd.ExecuteNonQuery("DROP TABLE ordritem");
				init_cmd.ExecuteNonQuery("DROP TABLE itemmast");

		}

		private void Define()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " DEFINE");

			Create_CustomerMaster_Table();
			Create_ItemMaster_Table();
			Create_CustomerOrders_Table();
			Create_OrderMaster_Table();
		}

		private void Manage()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " MANAGE");

			Add_CustomerMaster_Records();
			Add_ItemMaster_Records();
			Add_OrderItems_Records();
			Add_CustomerOrder_Records();

			Display_Query();
		}

		private void Done()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " DONE");
			//Delete_Records();
		}

		private void ExecuteSP()
		{
			Init();

			Define();

			Manage();

			Done();
		}

		#region Stored procedure class internal
		public override void Execute()
		{
			ExecuteSP();

		}
	}
}
		#endregion