const ctdb = require('ctdbsdk');

// This function deletes all the records in the table
module.exports.deleteRecords = function(hRecord)
{
	var retval;
	var empty;

	console.log("Delete records...\n");

	empty = false;
	retval = ctdb.ctdbFirstRecord(hRecord);
	if (retval != ctdb.CTDBRET_OK) {
		if (retval == ctdb.END_OF_FILE)
			empty = true;
		else
			throw("Delete_Records(): ctdbFirstRecord()");
	}

	while (empty == false) /* while table is not empty */
	{
		/* delete record */
		ctdb.DeleteRecord(hRecord)

		/* read next record */
		retval = ctdb.NextRecord(hRecord);
		if (retval != ctdb.CTDBRET_OK) {
			if (retval == ctdb.END_OF_FILE)
				empty = true;
			else
                throw("Delete_Records(): ctdbNextRecord()");
		}
	}
}
