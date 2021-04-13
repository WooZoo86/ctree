/**
 * Stored Procedure Name: tutorial_1
 *
 * Parameters: 
 *
 *
 * Result Set: 
 *     custnumb  VARCHAR(4)
 *     custname  VARCHAR(47)
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
	class tutorial_1 : SqlStoredProc
	{
#endregion

		#region Result Set References
		enum RSCol
		{
			custnumb = 0,
			custname = 1,
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

		private void Add_Records()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tAdd Records...");

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

		private void Delete_Records()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tDelete Records...");

			SqlSpCommand delete_cmd = NewSqlSpCommand();
			delete_cmd.ExecuteNonQuery("DELETE FROM custmast");
		}

		private void Display_Records()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + "\tDisplay Records...");

			SqlSpCommand display_cmd = NewSqlSpCommand();
			String query_stmt = "SELECT cm_custnumb, cm_custname FROM custmast";
			display_cmd.Prepare(query_stmt);

			display_cmd.Execute();
			SqlSpRow RSrow = NewResultSetRow();
			while (display_cmd.MoveNext())
			{
				RSrow[0].Value = display_cmd.CurrentRow[0].Value;
				RSrow[1].Value = display_cmd.CurrentRow[1].Value;
				ResultSetAddRow(RSrow);
			}
		}

		private void Init()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " INIT");

			SqlSpCommand init_cmd = NewSqlSpCommand();
			init_cmd.ExecuteNonQuery("DROP TABLE custmast");

			init_cmd.Execute();
		}

		private void Define()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " DEFINE");

			SqlSpCommand create_cmd = NewSqlSpCommand();

			create_cmd.ExecuteNonQuery("CREATE TABLE custmast (" +
				"cm_custnumb CHAR(4), " +
				"cm_custzipc CHAR(9), " +
				"cm_custstat CHAR(2), " +
				"cm_custrtng CHAR(1), " +
				"cm_custname VARCHAR(47), " +
				"cm_custaddr VARCHAR(47), " +
				"cm_custcity VARCHAR(47))");

		}

		private void Manage()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " MANAGE");
			Delete_Records();

			Add_Records();

			Display_Records();
		}

		private void Done()
		{
			DateTime dt = DateTime.Now;
			string line = dt.ToString();
			Log(line + " DONE");
			Delete_Records();
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