/*
 * lowlevel.c =This is a sample program provided to show you how to use
 *             c-tree LOW LEVEL functions. The application is a very simple
 *             one; creating and updating a simple database.
 *
 *             The application is extremely simple, and of no practial use
 *             other than to demonstrate the very basic use of c-tree. The
 *             key is a single segment, no duplicates are allowed.
 *
 *             The data input functions are extremely simple, and do little
 *             or no error checking.
 *
 *             If any value is passed on the command line, this program
 *             assumes that you want to create the database. Otherwise
 *             it assumes that the database has already been created.
 */

/*      Special Note - we use a function "toupper", which is not found
 *              in all C compilers. It translates any lower case letter
 *              into an upper case letter.
 */

#include "ctreep.h"
#ifdef PROTOTYPE
#include <ctype.h>
#endif

#ifndef ctrt_printf
#define ctrt_printf printf /* ensure console (non-GUI) output */
#endif

#ifdef ctPortMAC
#define ctCONSOLE_H <console.h>
#include ctCONSOLE_H
#endif


/* We always prefer to use symbolic names
 * whenever we can, for constants. This
 * allows us to easily change the constant
 * throughout the program by just changing
 * the definition in one place. Here we are
 * defining the file numbers that we will
 * use for both the data and the index file.*/
								 
#define INVENTDAT 1	 /* file numbers for the data and	*/
#define INVENTIDX 2	 /* index file.				*/

#define INPBUFSIZ 128
TEXT  inpbuf[INPBUFSIZ];    /* general purpose input buffer */
LONG  datarec;              /* data record position         */
TEXT  keyfld[26];           /* buffer to build key in       */

#define PADLEN (128 - ctSIZE(COUNT) - 26 - 50 - 10 - 2*ctSIZE(double))

struct INVENTORY {          /* data record format                   */
	TEXT	delete_flag[2];	/* delete flag byte                     */
	TEXT    item[26];       /* Item ID - this is the key value      */
	TEXT    descrip[50];    /* Item Description                     */
	TEXT    location[10];   /* Item Location                        */
	double  quantity;       /* Quantity on hand                     */
	double  cost;           /* Unit Cost                            */
	TEXT    pad[PADLEN];
	} invent;

/* ************************************************************************* */


#ifdef PROTOTYPE
VOID transkey(pTEXT,pTEXT,NINT);
VOID terminate(pTEXT,COUNT); /* an error routine for serious errors  */
VOID func_error(COUNT);      /* examine the error var. and print message*/
VOID getfld(void );
#else
VOID func_error();
VOID terminate();
VOID transkey();
VOID getfld();
#endif

#ifdef PROTOTYPE
NINT main (NINT argc,pTEXT argv[])
#else
NINT main (argc,argv)
NINT argc;
pTEXT argv[];
#endif
{
#ifdef PROTOTYPE
	VOID db_create(void), db_init(void), database(void), db_close(void);
#else
	VOID db_create(), db_init(), database(), db_close();
#endif

#ifdef ctPortMAC
	argc = ccommand(&argv);
#endif

#ifdef ctThrds
{
	NINT	err;
	if ((err = ctThrdInit(2,(LONG) 0,  (pctINIT)0))) {
		ctrt_printf("\nctThrdInit failed. Error={%d}\n", err);
		fflush(stdout);
		ctrt_exit(1);
	}
}
#endif

        printf("\nc-treeACE Version 11\n\nSimple Low Level Function Example\n\n");

	/* You must always initialize c-tree before you use any of the functions. */
										 
	/* Initialize the c-tree system */
	if (InitCTreeXtd(10,2,4,10,USERPRF_NTKEY,"admin","ADMIN","FAIRCOMS"))
		terminate("Could not initialize c-tree",-1);
		
	if (argc > 1)
		db_create();  /* create the database files    */
	db_init();        /* open the database files that are already created */

	database();       /* perform database routines    */
	db_close();       /* close the files, and any other ending stuff */
	fflush(stdout);
	return(0);        /* dummy to remove compiler warning */
}

/********************************************************
*                                                       *
* db_create:    creates the data files and indices.     *
*               If any of the files already exist there *
*               will be an error. The files are closed  *
*               so all intended file modes take effect. *
*                                                       *
********************************************************/
#ifdef PROTOTYPE
VOID db_create(void)
#else
VOID db_create()
#endif
{
	/* Create the data file         */
	if (CreateDataFile(INVENTDAT,"invent.dat",sizeof(invent),4096,ctVIRTUAL|ctSHARED|ctFIXED))
		terminate("Could not create invent.dat",INVENTDAT);
	/* the second parameter is no longer used */
	if (CloseCtFile(INVENTDAT,0))
		terminate("Could not close invent.dat after creation",INVENTDAT);

	/* Create the index file        */
	if (CreateIndexFile(INVENTIDX,"invent.idx",25,0,0,0,4096,ctVIRTUAL|ctSHARED))
		terminate("Could not create invent.idx",INVENTIDX);
	if (CloseCtFile(INVENTIDX,0))
		terminate("Could not close invent.idx after creation",INVENTIDX);

	printf("\nSuccessfully created data files and indices");
	return;
}

/********************************************************
*                                                       *
* db_init:      Open the data files and indices. They   *
*               must have been already created. Most of *
*               the important parameters for the files  *
*               are set when the file was created.	     *
*                                                       *
********************************************************/

#ifdef PROTOTYPE
VOID db_init(void)
#else
VOID db_init()
#endif
{
	/* Open the data file */
	if (OpenCtFile(INVENTDAT,"invent.dat",ctVIRTUAL|ctSHARED)) {
		db_create();
		if (OpenCtFile(INVENTDAT,"invent.dat",ctVIRTUAL|ctSHARED))
			terminate("Could not open invent.dat",INVENTDAT);
	}
		
	/* Open the index file */
	if (OpenCtFile(INVENTIDX,"invent.idx",ctVIRTUAL|ctSHARED))
		terminate("Could not open invent.idx",INVENTIDX);

	return;
}

/********************************************************
*                                                       *
* db_close:      close the data files and indices.       *
*                                                       *
********************************************************/

#ifdef PROTOTYPE
VOID db_close(void)
#else
VOID db_close()
#endif
{

	if (CloseCtFile(INVENTDAT,0))	/* the second parameter is no longer used*/
		func_error(INVENTDAT);
	if (CloseCtFile(INVENTIDX,0))
		func_error(INVENTIDX);
		
	StopUser();	/* Terminate this user with server and/or free-up
			 * c-tree PLUS(tm) memory allocations.
			 * You can include this even if you are
			 * not sure if you will be using the server.
			 */
	fflush(stdout);
	ctrt_exit(0);
}

/********************************************************
*                                                       *
* database:     This is the main action function.       *
*                                                       *
********************************************************/

#ifdef PROTOTYPE
VOID database(void)
#else
VOID database()

#endif
{
    TEXT choice[2];

#ifdef PROTOTYPE
	VOID datadd(void), datdel(void);
#else
	VOID datadd(), datdel();
#endif

    choice[0] = '\0';

    while (choice[0] != 'Q')
    {
		printf("\n\nA)dd  D)elete  Q)uit:");
		fflush(stdout);
		ctsfill(inpbuf,0,INPBUFSIZ);
		if (!ctrt_fgets(inpbuf, sizeof(inpbuf), stdin))
			inpbuf[0] = 'Q';
		choice[0] = (TEXT)toupper((NINT)inpbuf[0]);
		switch (choice[0])
		{

case 'A':
		datadd();       /* add new entry to database */
		break;

case 'D':
		datdel();      /* delete existing entries */
		break;

default:
		break;

		} /* end switch */
    } /* end while */
}

/********************************************************
*                                                       *
* dataadd:      Add a new record                        *
*                                                       *
********************************************************/

#ifdef PROTOTYPE
VOID datadd(void)
#else
VOID datadd()
#endif
{

	printf("\nADD NEW DATA\n\n");

        /* Initialize the new record so that all fields are blank */
	invent.delete_flag[0] = '\0';
	invent.delete_flag[1] = '\0';
	invent.item[0]     = '\0';
	invent.descrip[0]  = '\0';
	invent.location[0] = '\0';
	invent.quantity    = 0.0;
	invent.cost        = 0.0;

	getfld();               /* acquire new item info            */

	transkey(keyfld,invent.item,sizeof(invent.item)); /* prepare key for use */

	/* Look to see if this key is already   *
	 * in the file.                         */
	if (GetKey(INVENTIDX,keyfld))
	{
		printf("\nKey already in file, cannot add");
		return;
	}
	if (uerr_cod)					/* Check for error in EQLKEY call*/
	{
		func_error(INVENTIDX);     
		return;
	}
				/* Get data record from data file */
	if ((datarec = NewData(INVENTDAT)) == 0)
				/* assignment intended */
	{
	 	func_error(INVENTDAT);
		return;
	}

	/* Write data record to data file */
	if (WriteData(INVENTDAT,datarec,&invent))
	{
		func_error(INVENTDAT);
		ReleaseData(INVENTDAT,datarec);
		/* if we cannot write to *
		 * the record, we will   *
		 * return the record to  *
		 * the pool.             */
		LockCtData(INVENTDAT,ctFREE,datarec);
		/* NewData puts a lock on  *
		 * the record automatically*
		 * that we must free       */
		return;
	}

	/* Add key to the index, now that we know*
	 * that we have successfully added the   *
	 * record to the data file.              */
	if (AddKey(INVENTIDX,keyfld,datarec,REGADD))
	{
		func_error(INVENTIDX);
		ReleaseData(INVENTDAT,datarec);
		/* If cannot add key,     *
		 * then return the record.*/
		LockCtData(INVENTDAT,ctFREE,datarec);
		/* NewData puts a lock on  *
		 * the record automatically*
		 * that we must free       */
		return;
	}

	printf("\nSuccessful Addition");
	LockCtData(INVENTDAT,ctFREE,datarec);
	/* release the lock that NewData placed*/
	return;
}

/**********************************************************
*                                                         *
* transkey:     The key field must be properly formatted  *
*               by us, as c-tree does not format it       *
*               automatically with low level functions.   *
*               We are going to do two things to the      *
*               key. First, we will translate all of the  *
*               alpha characters to upper case. Second,   *
*               we will pad the key to its full length.   *
*               This second part is very critical! c-tree *
*               looks at the entire buffer when comparing *
*               keys, and if you have garbage after a     *
*               null terminated string in a key buffer,   *
*               that becomes a part of the key!           *
*                                                         *
***********************************************************/

#ifdef PROTOTYPE
VOID transkey(pTEXT dest,pTEXT source,NINT len)
#else
VOID transkey(dest,source,len)
	pTEXT dest,source;
	NINT len;
#endif
{
TEXT ch;
	len--;
			
	/* loop until field filled or null found,
	 * translating any lower case to upper case */
	while(*source &&  len-- > 0)
	{
		ch = *source++;
		*dest++ = (TEXT)toupper((NINT)ch);
	}
	/* fill the rest of the field with nulls, if needed */
	while(len-- > 0)
		*dest++ = '\0';

	*dest = '\0';
}


/********************************************************
*                                                       *
* getfld:       enter input information                 *
*                                                       *
********************************************************/

#ifdef PROTOTYPE
VOID getfld(void)
#else
VOID getfld()
#endif
{

	printf("\nEnter Item ID:     ");
	fflush(stdout);
	ctsfill(inpbuf,0,INPBUFSIZ);
	ctrt_fgets(inpbuf, sizeof(inpbuf), stdin);
	if (inpbuf[0] != '\0')
		cpybuf(invent.item,inpbuf,sizeof(invent.item));
	printf("\nEnter Description: ");
	fflush(stdout);
	ctsfill(inpbuf,0,INPBUFSIZ);
	ctrt_fgets(inpbuf, sizeof(inpbuf), stdin);
	if (inpbuf[0] != '\0')
		cpybuf(invent.descrip,inpbuf,sizeof(invent.descrip));
	printf("\nEnter Location:    ");
	fflush(stdout);
	ctsfill(inpbuf,0,INPBUFSIZ);
	ctrt_fgets(inpbuf, sizeof(inpbuf), stdin);
	if (inpbuf[0] != '\0')
		cpybuf(invent.location,inpbuf,sizeof(invent.location));
	printf("\nEnter Quantity:    ");
	fflush(stdout);
	ctsfill(inpbuf,0,INPBUFSIZ);
	ctrt_fgets(inpbuf, sizeof(inpbuf), stdin);
	if (inpbuf[0] != '\0')
		sscanf(inpbuf,"%lf",&invent.quantity);
	printf("\nEnter Cost:        ");
	fflush(stdout);
	ctsfill(inpbuf,0,INPBUFSIZ);
	ctrt_fgets(inpbuf, sizeof(inpbuf), stdin);
	if (inpbuf[0] != '\0')
		sscanf(inpbuf,"%lf",&invent.cost);
}

/********************************************************
*                                                       *
* datdel:       find and delete record                  *
*                                                       *
********************************************************/


#ifdef PROTOTYPE
VOID datdel(void)
#else
VOID datdel()
#endif
{

	printf("\nDELETE DATA\n");

	printf("\nEnter Item to Delete:");
	fflush(stdout);
	ctsfill(inpbuf,0,INPBUFSIZ);
	ctrt_fgets(inpbuf, sizeof(inpbuf), stdin);
	transkey(keyfld,inpbuf,sizeof(invent.item));
		/* Prepare key for use. It is important to form
		 * this key in the same way as we do keys to be added,
		 * since we will be looking for an exact match
		 */

	/* find the key to delete in index */
	if (!(datarec = GetKey(INVENTIDX,keyfld)))
	{
		if (uerr_cod)
			func_error(INVENTIDX);
		else
			printf("\nKey not found");
		return;
	}

	/* read the record to display */
	if (ReadData(INVENTDAT,datarec,&invent))
		func_error(INVENTDAT);
	else
	{
		printf("\n\nItem        %s",invent.item);
		printf("\nDescription %s",invent.descrip);
		printf("\nLocation    %s",invent.location);
		printf("\nQuantity    %f",invent.quantity);
		printf("\nCost        %f",invent.cost);
	}

	/* Delete the key from index */
	if (DeleteKey(INVENTIDX,keyfld,datarec))
	{
		printf("\n\nKey delete failed (code %d).",uerr_cod);
		return;
	}

	/* Return the data record to pool */
	if (ReleaseData(INVENTDAT,datarec))
		printf("\n\nData record delete failed (code %d).",uerr_cod);
	else
		printf("\n\nDelete Successful");

}

/********************************************************
*                                                       *
* terminate:    if an error occurs in a place           *
*               where we should terminate the program,  *
*               call this function.                     *
*                                                       *
*               You may wish to have a more             *
*               sophisticated error routine that will   *
*               look at the error code and give the user*
*               more information.                       *
*                                                       *
********************************************************/

#ifdef PROTOTYPE
VOID terminate(pTEXT termsg,COUNT fil)
#else
VOID terminate(termsg,fil)
	pTEXT termsg;
	COUNT fil;
#endif
{
	printf("\n\n%s",termsg);
	func_error(fil);
	/* Call the routine that will give you  *
	 * a meaningful message                 */

	STPUSR();
	/* This is needed to shut the user down *
	 * if you are using a file server. If   *
	 * you aren't, it is a good idea to     *
	 * include since it will free up c-tree *
	 * PLUS(tm)'s memory allocations.	*/
	fflush(stdout);
	ctrt_exit(1);
}

/********************************************************
*                                                       *
* func_error:   A simple error message handler. You can *
*               add other error conditions as you need. *
*                                                       *
********************************************************/

#ifdef PROTOTYPE
VOID func_error(COUNT fil)
#else
VOID func_error(fil)
	COUNT fil;
#endif
{

	switch (uerr_cod)
	{

case NO_ERROR:
		break;         /* no error occured, so return */
case DLOK_ERR:
		printf("\nCouldn't get lock on record");
		break;
case FNOP_ERR:
		printf("\nCould not open file %d",fil);
		printf("\nIf the files do not exist, you need to create them.");
		printf("\nTo do so, type in \"lowlevel create\" on the command line.");
		break;
case KCRAT_ERR:
case DCRAT_ERR:
		printf("\nCould not create file [%d]",fil);
		break;
case KOPN_ERR:
case DOPN_ERR:
		printf("\nTried to create existing file [%d]",fil);
		break;
case KDUP_ERR:
		printf("\nKey already in index");
		break;
case FUNK_ERR:
case FCRP_ERR:
		printf("\nHeader record of file %d is damaged",fil);
		break;
case SEEK_ERR:
case WRITE_ERR:
case READ_ERR:
		printf("\nFailure while trying to read or write record");
		break;
case DADV_ERR:
		printf("\nServer did not find proper lock");
		break;
case UDLK_ERR:
		printf("\nCannot unlock data record");
		break;
default:
		printf("\nError %d on file %d",uerr_cod,fil);
		break;

	} /* end switch */
}

/* end of lowlevel.c */

