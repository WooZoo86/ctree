const ctdb = require('ctdbsdk');

var data = [
	{number: "1000", zipcode: "92867", state: "CA", rating: "1", name: "Bryan Williams", address: "2999 Regency",      city: "Orange"},
	{number: "1001", zipcode: "61434", state: "CT", rating: "1", name: "Michael Jordan", address: "13 Main",           city: "Harford"},
	{number: "1002", zipcode: "73677", state: "GA", rating: "1", name: "Joshua Brown",   address: "4356 Cambridge",    city: "Atlanta"},
	{number: "1003", zipcode: "10034", state: "MO", rating: "1", name: "Keyon Dooling",  address: "19771 Park Avenue", city: "Columbia"}
];

module.exports.addRecords = function(hRecord)
{
	console.log("Add records...\n");

	/* add data to table */
	for (let i = 0; i < data.length; i++) {
		/* clear record buffer */
		ctdb.ClearRecord(hRecord);

		var retval = 0;
		/* populate record buffer with data */
		retval |= ctdb.SetFieldAsString(hRecord, 0, data[i].number);
		retval |= ctdb.SetFieldAsString(hRecord, 1, data[i].zipcode);
		retval |= ctdb.SetFieldAsString(hRecord, 2, data[i].state);
		retval |= ctdb.SetFieldAsString(hRecord, 3, data[i].rating);
		retval |= ctdb.SetFieldAsString(hRecord, 4, data[i].name);
		retval |= ctdb.SetFieldAsString(hRecord, 5, data[i].address);
		retval |= ctdb.SetFieldAsString(hRecord, 6, data[i].city);

		if (retval)
			Handle_Error("Add_Records(): ctdbSetFieldAsString()");

		/* add record */
		if (ctdb.WriteRecord(hRecord))
			Handle_Error("Add_Records(): ctdbWriteRecord()");
	}
}
