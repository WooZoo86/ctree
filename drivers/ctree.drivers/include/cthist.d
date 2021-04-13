			History Documentation
			=====================


INTRODUCTION
============

The history function, CTHIST, permits an application to scan backward or
forward through the transaction logs, returning either key values or data
records and optionally the user ID and node name of the process which performed
the update. When scanning backward, CTHIST will look for both active log files
(those ending with "FCS") and for inactive log files (those ending with "FCA").
The information extracted from the transaction logs can be based on:

	o a particular record position of a specified data file;
	o a particular (unique) key value of a specified index;
	o all updates to a specified file;
	o updates made by a particular user ID and/or node name; or
	o some combination of the above.


CTHIST is available in single-user, transaction processing applications, or
in client-server applications. Files created without TRNLOG in their file
mode are not included in the transaction logs, and are not accessible to the
CTHIST function.


CTHIST can be used "on-line," meaning that current files and transaction logs
can be interrogated as part of an active application. Or, an "off-line"
utility can be built from CTHIST which examines a set of data and index files
along with the log files saved at the time a single-user application is
terminated, or a server is shut down.


There are four types of calls made to CTHIST. The first two of them are routine
search calls with the purpose of returning log entries. The third is used to
specify a beginning log number, and the last is used to reset the history
state to permit a new set of history calls to be made. These calls can be
characterized as follows:

	first search call
	-----------------
	   A first search call to CTHIST specifies the characteristics
	   of the search and what type of information to return. This
	   call returns the first entries in the log which satisfy the
	   search criteria.

	subsequent search call
	----------------------
	   Subsequent search calls to CTHIST return the next entries in the
	   log which satisfy the search criteria. On these subsequent calls,
	   it is not appropriate to specify search criteria or the type of
	   information to return. These are specified in the first search call.
	   It is required on every search call, including the first search
	   call, to specify the address of an output buffer and the length
	   of the buffer. The buffer address and length may be different on
	   each call.

	preliminary log call
	--------------------
	   A preliminary call only specifies a beginning log number.

	terminating call
	----------------
	   A terminating call cleans up the current history set, and
	   permits a new set of history calls to be made starting with a
	   new first search call.


For on-line use, the basic pattern of calls to CTHIST is:

	o make a first search call
	o make repeated subsequent search calls

An on-line search is performed backward through the logs. The starting log is
not explicitly specified. The log scan begins with the current log position.


For an off-line utility, the basic pattern of use is almost the same as above
except that an optional preliminary log call to CTHIST, as noted above,
may be made to specify the starting log number. Off-line searches may be made
in either forward or backward directions through the logs. While backward
searches are the most common type, if additional log files have accumulated
since the data and index files were saved, it is meaningful to search forward.

Beginning with Release ????, the file create, open and close entries in the
log carry a time stamp which permits CTHIST to locate the appropriate position
in the log to begin off-line searches. However, if one does not specify an
explicit file, then the beginning log number can be used to help narrow the
CTHIST search.


A call to CTHIST which returns a (non-zero) error code automatically frees
internal memory allocated to the current history set, and resets the
history status to permit a new history set to be begun. No terminating call
is required. When there is no more information in the transaction logs
which satisfy the search criteria, CTHIST returns HENT_ERR(618). If a first
search call is made before the log entries for the current history set
are exhausted and before a terminating call is made, then a HMID_ERR(622)
will be returned.


If one desires to switch to a new set of history calls prior to exhausting
all the log entries which satisfy the search critera, two approaches may be
used. The most simple is to make a terminating call as noted above to terminate
the existing history set. Alternatively, any number of history sets may be
maintained simultaneoulsy, just as multiple batches are maintained. The
CHGHST call is used to switch among multiple history sets, and the FREHST call
frees all the internal memory allocated to support the history sets. (There
is no ALCHST call. Remember, the ALCBAT and ALCSET calls are now unnecessary.)



CTHIST CALL SYNTAX AND PARAMETERS
=================================

COUNT CTHIST(COUNT filno,pVOID target,pVOID bufptr,LONG recbyt,VRLEN bufsiz,UCOUNT mode)


The file number parameter, filno, should be -1 except on the first search call.
On the first search call, filno may reference a particular data or index file
which the calling program has already opened, or filno may be -1 indicating
that information pertaining to any file which satisifies the search criteria
will be returned. When an index file is specified by filno, the mode parameter,
discussed below, indicates whether key values or associated data records are
to be returned.


The target parameter should be null except on the first search call. On the
first search call target points to either a key value, a user ID and/or node
name, or is null, depending on the search request.


The output buffer parameter, bufptr, specifies the address where the search
calls return the log entries satisfying the search criteria. On non-search
calls bufptr should be null. The information returned in the output buffer
consists of:

	o a 40-byte history header described in detail below
	o an optional record header which is returned for variable length data
	  records, superfile member data records, and resources in fixed or
	  variable length data files
	o the key value or data record entry
	o when requested (in the mode parameter discussed below), a null
	  terminated string with user ID and node name of the process which
	  made the log entry is appended; the node name, when present, is
	  preceeded by a vertical bar ('|')
	o when the file is not specified in the filno parameter, a null
	  termintated file name is appended


The record byte parameter, recbyt, is set to the starting log number on a
preliminary log call to CTHIST, is set to -1L on a terminating call to CTHIST,
is ignored on subsequent search calls, and is set to zero or a particular data
record location on the first search call.


The buffer size paremeter, bufsiz, specifies the length of the output buffer
specified by the bufptr parameter. If the buffer is too small to hold all the
output requested, it is simply truncated per the bufsiz parameter. However,
if bufsiz is less than 40, then error HSIZ_ERR(620) will be returned.


The mode parameter specifies what type of call is being made, how to interpret
the search criteria, and what information to return into the output buffer.
The following mode constants are found in ctport.h. Each represents a bit which
may be or'ed into the mode parameter.


	mode bit	usage
	-------------	------------------------------------------------
	ctHISTlog	signify preliminary log or terminate call
	ctHISTfirst	signify first search call
	ctHISTnext	signify subsequent search call
	ctHISTfrwd	scan logs forward (default is back)
	ctHISTuser	match user ID
	ctHISTnode	match node name
	ctHISTpos	match byte offset (record position)
	ctHISTkey	match key value
	ctHISTdata	return data record entries
	ctHISTindx	return key value entries
	ctHISTnet	return net change, not intra-transaction details
	ctHISTinfo	return User ID and node name info


Preliminary log calls and terminate calls appear as follows:

	CTHIST(-1,(pVOID)0,(pVOID)0,recbyt,(VRLEN)0,ctHISTlog);

where recbyt is set to (LONG)-1 to terminate the current history set, or
recbyt is set to the beginning log number. Subsequent search calls appear
as follows:

	CTHIST(-1,(pVOID)0,bufptr,(LONG)0,bufsiz,ctHISTnext);

where bufptr points to the output buffer and bufsiz specifies the length of the
output buffer.


A first search call has a mode parameter with ctHISTfirst or'ed in. If the
search is to be forward through the logs, then ctHISTfrwd must be or'ed in.
(The search direction otherwise defaults to backward.) There are three
types of matching or search criteria: ctHISTpos implies match data record
position (with a recbyt of zero meaning match all data record positions);
ctHISTkey implies match key value (with a null target meaning match all key
values); and ctHISTuser and/or ctHISTnode imply match user ID (with an empty
string target meaning match all user ID's). A first search call must use
exactly one of these three matching criteria. That is, either ctHISTpos
or ctHISTkey or one or both of ctHISTuser and ctHISTnode must be turned on.

The search criteria over specific files (signified by a non-negative filno
parameter) are specified by or'ing in either ctHISTpos or ctHISTkey
or ctHISTuser and/or ctHISTnode. When the search is over all files (signified
by a filno parameter of -1), ctHISTpos and ctHISTkey are not used, but at
least one of ctHISTuser and ctHISTnode must or'ed in. In all cases, either
ctHISTdata or ctHISTindx is or'ed in to specify the type of log entries to
return. The interpretation of the mode, filno, target and recbyt parameters
as used in the first search call is given in the following table:


		Possible First Search Call Combinations
		---------------------------------------

  ctHIST
p|k|u|n|d|i	NOTE: an x indicates the bit is turned on in the mode
o|e|s|o|a|n	      a's indicate one or more of these bits is turned on
s|y|e|d|t|d
 | |r|e|a|x filno  target   recbyt	interpretation
-+-+-+-+-+- ------ -------- ----------  ----------------------------------------
 | |a|a|x|  -1     user ID  zero	return all data entries for all data
 | | | | |				files updated by matching user
 | |a|a| |x -1     user ID  zero	return all index entries for all index
 | | | | |				files updated by matching user
x| | | |x|  data   NULL     zero	return all data entries for specified
 | | | | |				data file
x| | | |x|  data   NULL     non-zero	return data entries matching recbyt
 | | | | |				for specified data file
 | |a|a|x|  data   user ID  zero	return all data entries for specified
 | | | | |				data file made by matching user
 | |a|a|x|  data   user ID  non-zero	return data entries matching recbyt
 | | | | |				for specified data file made by
 | | | | |				matching user
 |x| | |x|  index  key      zero	return all data entries with index
 | | | | |				matching key*
 |x| | |x|  index  key      non-zero	return all data entries with index
 | | | | |				matching key and recbyt**
 |x| | | |x index  NULL     zero	return all index entries for specified
 | | | | |				index file
 |x| | | |x index  NULL     non-zero	return all index entries for specified
 | | | | |				index file which match recbyt
x| | | |x|  index  NULL     non-zero	return all data entries with index
 | | | | |				matching recbyt for specified index file
 | |a|a| |x index  user ID  zero	return all index entries for specified
 | | | | |				index file made by matching user
 | |a|a| |x index  user ID  non-zero	return all index entries for specified
 | | | | |				index file which match recbyt and
 | | | | |				made by matching user

					 * a data entry with index matching key
					   means that the key value for the
					   data record matches the target for
					   the specified index file
					   
					** an index entry matching recbyt means
					   that the index entry points to a
					   record offset that matches recbyt.


In addition to the combinations specified above, two additional mode bits may
be or'ed in. ctHISTinfo signifies that the user ID and node name of the process
which made the log entries should be returned (in the form of a null terminated
ASCII string with a verical bar '|' preceeding the node name, if any) in
addition to the data or index information requested. For searches of specific
files with specific matching criteria (i.e., a non-null target for an index or
a non-zero recbyt for a data file), then ctHISTnet can be or'ed in to signify
that only the net affect of each transaction should be returned, not each
individual update within the transaction. Also remember that ctHISTfirst must
be turned on, and optionaly ctHISTfwrd may be turned on.


When passing in a user ID as the target parameter (the mode includes
ctHISTuser and/or ctHISTnode), the following conventions must be noted.
Uers ID's are passed in as a null terminated ASCII string. If only ctHISTuser
is on, then the target is treated as case insensitive, and corresponds to
the user ID's specified during logon to a server. If only ctHISTnode is on,
then the target is treated as case sensitive, and corresponds to the node
name which can be set by the SETNODE function. If both ctHISTuser and
ctHISTnode are on, then the target is treated as a single null terminated
composite string beginning with a case insensitive user ID followed
by a vertical bar ('|') followed by a case sensitive node name. To match
all users, turn on ctHISTuser and pass a pointer to an empty string (""),
not a null pointer, for the target parameter.



History Output
==============

As outlined above, the output buffer contains the following information after a
successful first search call or subsequent search call:

	o a 40-byte history header 
	o an optional record header which is returned for variable length data
	  records, superfile member data records, and resources in fixed or
	  variable length data files
	o the key value or data record entry
	o when requested by including ctHISTinfo in the mode parameter, a null
	  terminated string with user ID and node name of the process which
	  made the log entry is appended; the node name, when present, is
	  preceeded by a vertical bar ('|'); if no user ID exists, then a null
	  byte is appended
	o when the file is not specified in the filno parameter, a null
	  terminated file name is appended


History Header
--------------

The history header is an instance of the 40-byte HSTRSP structure, defined
in ctport.h, which is composed of the following fields:

	LONG	tranno;	/* transaction number				*/
	LONG	recbyt;	/* the data record byte offset for the log entry*/
	LONG	lognum;	/* the log number for the entry			*/
	LONG	logpos;	/* the offset within the log for the entry	*/
	LONG	imglen;	/* the length of the data or key value returned	*/
	LONG	trntim;	/* the time stamp for the transaction		*/
	LONG	trnfil;	/* the internal file number for the log entry	*/
	LONG	resrvd;	/* reserved for future use			*/
	UCOUNT	membno;	/* the index member number			*/
	UCOUNT	imgmap;	/* details concerning the data returned		*/
	COUNT	trntyp;	/* the type of transaction log entry		*/
	COUNT	trnusr;	/* the internal user number which made the entry*/

[The history code released on the first CD (end of March / early April) defines
 this structure in ctstrc.h, not ctport.h.]

It is very important to note that more than one actual log entry may be
combined in order to return an image of a data record. Essentially, this
reflects the fact that variable length data records and resources are
composed of a header and the actual data. These components are written
to the log separately, and must be combined to generate a coherent data
entry. Further, a scan of the log based on an index file which returns the
corresponding data information may require more than one log entry to generate
the returned data entry. Therefore, the lognum, logpos and trntyp fields in
the history header reflect only one of possibly several log entries which
are combined to create the return information.


The components of HSTRSP are discussed here. Each data and index entry in
a transaction log belongs to a particular transaction. Each such
transaction is assigned a unique number. This transaction number is
returned in tranno. Each data and index entry is for a particular
file at a particular data record location. The recbyt field of HSTRSP is set
to this data record location, expressed as a byte offset from the beginning of
the file. The trnfil field is set to the unique file number assigned to
each data and index file upon their creation or actual opening. Note that
each time a file is opened anew it is assigned a new file number. The trntim
field is set to the commit time of the transaction to which the data or index
entry belongs. In the event that this commit time cannot be determined, it is
set to zero.

The imglen field is set to the length of the key value or data record image
returned in the output buffer just following the 40-byte history header. In
the event that there is an optional record header just before the data
or resource image, then imglen includes the length of this header. When user
ID's and/or file names are appended to the end of the key value or data record
image, the length of these strings is NOT included in imglen. Rather, these
null terminated ASCII string fields follow immediately after the key or record
image.

When a record header is present, the lowest order byte of imgmap contains
the length of the record header. The contents of the imgmap field can be
and'ed with ctHISTmapmask to determine the length of the record header. In
the event that the ctHISTnet mode bit has been turned on, and if the
transaction resulted in a delete of the data record in question, then the
ctHISTkdel bit of the imgmap field will be turned on to signify that the
deleted key value, not a data record image has been returned.

When the first search call is made with a file number of -1, indicating
entries for all data or index files are to be returned (with ctHISTdata or
ctHISTindx specifying the desired type of files), then one of the following
bits of the imgmap field will be turned on:

	ctHISTdatfile	- fixed length data file entry
	ctHISTidxfile	- index file entry
	ctHISTvarfile	- variable length data file entry

[The history code released on the first CD (end of March / early April) does
 not have these file type imgmap bits activated.]

In addition to one of these bits being set in the imgmap field, and providing
the output buffer is sufficiently long, the file name of the index or data
entry returned is appended to the end of the output (after, if requested, the
user ID string). If the appended file is for an index file, then the membno
field of the HSTRSP structure is set to the index member of the index file
returned. Remember, the host index is member number zero.

The position of the log entry in the transaction logs is specified by the
log number and the offset of the entry within the log. The log number is 
returned in lognum, and the offset is returned in logpos. Each log entry is
made by a specified user. A non-unique user number is assigned to each logon,
and stays assigned until a logoff. At that time, the user number may be
reassigned to another logon. The trnusr field is set to this internal, non-
unique user number. Each log entry is assigned a transaction type. This type
number determines how to interpret the contents of the transaction log entry.
Of particular interest to the CTHIST function are the following transaction
types (found in ctopt2.h):

	LADDKEY		add key value
	LDELKEY		delete key value
	NEWLINK		delete stack link
	NEWIMAGE	new record image
	OLDFILL		old image ff filled
	OLDIMAGE	old record image
	DIFIMAGE	old/new difference image
	LOGEXTFIL	extend file
	NODEXTFIL	extend file


Optional Record Header
----------------------

When a first or subsequent search call returns a data record which is for
a variable length data file, or for a data file which is a member of a
superfile, or for a resource record, then the data is almost always preceeded
by a record header. (The only exception would be if CTHIST could not find
or properly relate the log entries needed to create the composite header
and actual data image.) The least significant byte of the imgmap field of
the history header contains the length of the record header. Typical values
for the length are:

		 0 - no record header
		10 - variable length record header
		18 - superfile record header
		22 - resource record header

The first ten bytes of each header is comprised of:

		2-byte record mark
		4-byte total length
		4-byte utilized length

The record mark is 0xFAFA for an active data record, 0xFDFD for a deleted
data record, 0xFEFE for a resource record. Typically a fixed length data
record in a superfile will have a header record mark of 0xFAFA whether active
or deleted. One must look at the first byte of the actual data record
(just as in a fixed length file which is not part of a superfile) to determine
if it is active or deleted. A deleted fixed length data record begins with
a 0xFF byte.

The total length is the space used by the header, the actual data image, plus
any extra space not currently utilized by the record. The utilized length is
the length of the actual data not including the header or any extra space.
(In a properly configured file, moving from the first byte of the record header
by the total length should place you on the first byte of the next record
in the file.) CTHIST usually returns the entire (total length) data image,
not just the utilized length.


Example Output
--------------

The hex dump displayed below(from a LOW_HIGH environment) demonstrates a
possible result from a first search call of the form

	CTHIST(-1,"",outbuf,(LONG)0,(VRLEN)256,ctHISTfirst | ctHISTuser |
		ctHISTdata | ctHISTinfo);

The filno of -1 implies search all files, the ctHISTuser combined with an
empty string for the target implies match any user, the ctHISTdata implies
returning data record images, a recbyt of zero means all data records, and
ctHISTinfo implies returning user ID information.

This hex dump displays the contents of the 256 bytes of memory pointed to by
outbuf. It is for a deleted fixed length data record in a superfile.

relative
hex
address        hexadecimal memory dump of outbuf           ASCII equivalent
-------- ------------------------------------------------  ----------------
000000   20 00 00 00 92 58 00 00  01 00 00 00 3f e5 00 00   ....X......?...
000010   92 00 00 00 f9 6f dd 30  0e 00 00 00 00 00 00 00  .....o.0........
000020   00 00 12 02 0e 00 01 00  fa fa 92 00 00 00 80 00  ................
000030   00 00 02 00 00 00 00 58  00 00 ff 00 00 00 00 00  .......X........
000040   00 00 6a 65 73 73 20 20  20 20 20 20 20 20 20 20  ..jess          
000050   20 20 20 20 20 20 20 20  20 20 31 20 20 20 20 20            1     
000060   20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20                  
000070   20 20 31 20 20 20 20 20  20 20 20 20 20 20 20 20    1             

000080   20 20 20 20 20 20 20 20  20 20 20 20 20 20 20 20                  
000090   20 20 31 20 20 20 20 20  20 20 20 20 20 20 20 20    1             
0000a0   20 20 20 20 20 20 20 20  20 20 31 20 31 20 20 20            1 1   
0000b0   20 20 20 20 20 05 00 00  00 00 00 63 75 73 74 21       ......cust!
0000c0   63 75 73 74 2e 64 61 74  00 2c 08 00 f8 ad 05 00  cust.dat.,......
0000d0   d0 2b 08 00 bc bd 01 00  03 00 0c 00 a8 2a 08 00  .+...........*..
0000e0   21 00 00 00 38 40 0c 00  f4 6a 07 00 63 75 73 74  !...8@...j..cust
0000f0   21 63 75 73 74 7a 69 70  2e 69 64 78 00 4c 07 00  !custzip.idx.L..


The bytes from 0x00 to 0x27 represent the 40-byte history header. These
correspond to the following field values:

	LONG	tranno	-	32
	LONG	recbyt	-	0x5892
	LONG	lognum	-	1
	LONG	logpos	-	0xe53f
	LONG	imglen	-	146
	LONG	trntim	-	0x30dd6ff9
	LONG	trnfil	-	14
	LONG	resrvd	-	0
	UCOUNT	membno	-	0
	UCOUNT	imgmap	-	least significant byte: 18 (header length)
				bit mask 0x0200 (ctHISTdatfile => fixed length)
	COUNT	trntyp	-	14 (OLDIMAGE)
	COUNT	trnusr	-	1

The 146 bytes from 0x28 to 0xb9 represent the record header (18 bytes) and
the actual record image (128 bytes). The header shows an "active" record space,
with record mark 0xfafa, but the first byte of the fixed length record is a
0xff which indicates that it is deleted.

Since ctHISTinfo was included in the mode parameter, the null terminated
ASCII string beginning at byte 0xba is the user ID of the process which
made this log entry. Since byte 0xba is a zero, then the log did not contain
a user ID for user number 1 (as shown in trnusr above). If this log is from a
single-user application, no user ID is expected to be found in the log.

Since the filno parameter was -1, the user ID string should be followed by a
null terminated file name. Bytes 0xbb through 0xc8 contain the superfile
member name: cust!cust.dat. The bytes following 0xc8 are garbage. If the
bufsiz parameter had been less than 256, then the output from CTHIST would
simply be that shown in the hex dump truncated to the bufsiz length. However,
bufsiz must be at least 40, or an error HSIZ_ERR(620) will be returned, and
no output generated.



Multiple History Sets
=====================

The CHGHST function permits an application to simultaneously maintain any
number of history sets (where a set is defined to exist when either a first
search call or preliminary log call returns successfully. c-tree allocates
a history state structure (not the same as the 40-byte HSTRSP structure)
for each history set. CHGHST takes an arbitrary short integer as its input
argument. That is, the application can assign history set ID numbers in any
manner it wishes; except that the history set ID number of zero is reserved
for the default history set which exists whther or not CHGHST is called.
CHGHST returns a zero on success.

Call FREHST to free the memory associated with multiple history sets. It
is not necessary to call FREHST since either of the c-tree terminate calls,
CLISAM or STPUSR, will automatically invoke FREHST. However, if an application
desires to reduce its memory use prior to termination, then FREHST is
available.

Call Syntax and Parameters
--------------------------

COUNT CHGHST(COUNT hstnum)
COUNT FREHST(VOID )

The history set ID number is passed in the hstnum argument. Both functions
return zero on success and an error code on failure.



EXAMPLES
========

In the following examples, lines beginning with "..." represent a combination
of psuedo-code and comments.

Find All Key Value Updates For Specified Index
----------------------------------------------

struct {
	HSTRSP	hr;
	TEXT	keyval[288];
}	keybuf;
COUNT	retval;
COUNT	fileno;

...
... assume INTISAM has been called and the index file opened with fileno
... assigned to the desired index. The following calls will return
... the 40-byte history header, followed by the key value, followed by
... a null terminated user ID in the keybuf structure
...

	retval = CTHIST(fileno,NULL,&keybuf,(LONG)0,(VRLEN)sizeof(keybuf),
			ctHISTfirst | ctHISTkey | ctHISTindx | ctHISTinfo);
	while (retval == NO_ERROR) {
		...
		... do what you want with keybuf. keybuf.hr.imglen contains
		... the length of the key value returned. You can jump
		... over this length to find the beginning address of the
		... user ID: keybuf.keyval + keybuf.hr.imglen
		...
		retval = CTHIST(-1,NULL,&keybuf,(LONG)0,(VRLEN)sizeof(keybuf),
				ctHISTnext);
	}

	... normally, retval will be set to HENT_ERR indicating no more
	... log entries

Find All Data Entries Corresponding To Key Value
------------------------------------------------

struct {
	HSTRSP	hr;
	TEXT	recbuf[1024];
}	hstbuf;
pTEXT	target;
COUNT	retval;
COUNT	fileno;

...
... assume INTISAM has been called and the index file opened with fileno
... assigned to the desired index. We are further assuming that this index
... is mapped into a data file through a c-tree ISAM relationship. The
... following calls will return the 40-byte history header, followed by
... an optional record header followed by the record, followed by
... a null terminated user ID
...
... set target to point to the desired key value
...

	retval = CTHIST(fileno,target,&hstbuf,(LONG)0,(VRLEN)sizeof(hstbuf),
			ctHISTfirst | ctHISTkey | ctHISTdata | ctHISTinfo);
	while (retval == NO_ERROR) {
		...
		... do what you want with hstbuf.
		...
		... hstbuf.hr.imgmap & ctHISTmapmask is the length of the
		... optional record header (zero indicating no record
		... header). hstbuf.imglen is the length of the optional
		... header plus the actual data record
		...
		retval = CTHIST(-1,NULL,&keybuf,(LONG)0,(VRLEN)sizeof(keybuf),
				ctHISTnext);
	}


Limitations
===========

When CTHIST is called from a client in a heterogenous network, only the
history header is automatically converted to match the client's byte ordering.
The optional record header and the actual data or key image from the log are
returned in their native form.



Error Code Summary
==================

If CTHIST returns a non-zero value, then the current history set is canceled,
the memory associated with the set is freed, and a new first search call
can be made.

error
symbol		value	interpretation
--------	-----	-------------------------------------------------------
HNUL_ERR	610	NULL target not permitted for this request
HLOG_ERR	611	could not access/find transaction log
HSTR_ERR	612	must make a first search call (ctHISTfirst)
HONE_ERR	613	can only request data OR index entries, not both
HMAP_ERR	614	could not find ISAM map from specified index file to
			a data file
HIDX_ERR	615	cannot request index entries from a specified data file
HACT_ERR	616	CTHIST cannot be called during an application's
			own active transaction
HNOT_ERR	617	did not find target
HENT_ERR	618	no more transaction log entries
HZRO_ERR	619	zero recbyt not permitted on this request
HSIZ_ERR	620	bufsiz too small, must be at least sizeof(HSTRSP)
HTYP_ERR	621	transaction type found in log not expected
HMID_ERR	622	must reset CTHIST through a terminate call or
			preliminary log call
HMEM_ERR	623	not enough memory for CTHIST
HNET_ERR	624	net change only applies to specific match of key or
			record position
HMTC_ERR	625	must specify exactly one matching criteria: ctHISTpos
			or ctHISTkey or one or both of ctHISTuser/ctHISTnode
HUND_ERR	626	encountered an UNDTRAN (undo committed transaction)
			going forward: must completely restart this set of
			history calls (i.e., repeat the first search call and
			subsequent search calls: the undone transaction will
			be ignored)
HUNK_ERR	627	unknown type of request
HFIL_ERR	628	must specify filno
HTFL_ERR	629	could not initialize internal file ID: preserve files
			and contact FairCom

/* end of cthist.d */
