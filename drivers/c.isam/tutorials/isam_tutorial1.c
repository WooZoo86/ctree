/*
 * isam_tutorial1.c
 *
 * Public domain ISAM example
 *
 * FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203 USA
 *
 * The goal of this tutorial is to introduce the most basic c-tree Plus ISAM API
 * to accomplish creating and manipulating a table through the c-tree Server
 *
 * From a functional point of view this application will perform the following:
 *  1.  Logon onto a session
 *  2.  Add 1 table with some fields
 *  3.  Populate the table with a few records
 *  4.  Display the contents of the table
 *
 */

/* Preprocessor definitions and includes */

#include "ctreep.h"  /* c-tree headers */

#define END_OF_FILE INOT_ERR

#define NUMBLEN 4
#define ZIPCLEN 9
#define STATLEN 3
#define RATGLEN 1
#define NAMELEN 47
#define ADDRLEN 47
#define CITYLEN 47

#define NBR_OF_FIELDS 7

#define FIXED_RECORD_SIZE (NUMBLEN + ZIPCLEN + STATLEN + RATGLEN)

#define MAX_RECORD_SIZE 256


/* Global declarations */

FILNO custmast_filno; /* data file number */

/* Data Record Definitions */

DATOBJ custmast_doda[] = {
   {"cm_custnumb",NULL,CT_FSTRING,NUMBLEN},
   {"cm_custzipc",NULL,CT_FSTRING,ZIPCLEN},
   {"cm_custstat",NULL,CT_FSTRING,STATLEN},
   {"cm_custratg",NULL,CT_FSTRING,RATGLEN},
   {"cm_custname",NULL,CT_STRING,NAMELEN},
   {"cm_custaddr",NULL,CT_STRING,ADDRLEN},
   {"cm_custcity",NULL,CT_STRING,CITYLEN}
};


/* Data File Definitions */

IFIL custmast_ifil = {
   "custmast",       /* data file name                         */
   -1,               /* data file number                       */
   FIXED_RECORD_SIZE,/* data record length                     */
   4096,             /* data extension size                    */
   ctVLENGTH,        /* data file mode                         */
   0,                /* number of indices                      */
   0,                /* index extension size                   */
   0,                /* index file mode                        */
   (pIIDX)0,         /* pointer to index array                 */
   "cm_custnumb",    /* pointer to first field name (r-tree)   */
   "cm_custcity"     /* pointer to last field name (r-tree)    */
};


/* Function declarations */

#ifdef PROTOTYPE
VOID Initialize(VOID), Define(VOID), Manage(VOID), Done(VOID);
VOID Add_Records(VOID), Display_Records(VOID), Delete_Records(VOID);
VOID Handle_Error(pTEXT, NINT);
#else
VOID Initialize(), Define(), Manage(), Done();
VOID Add_Records(), Display_Records(), Delete_Records();
VOID Handle_Error();
#endif


/*
 * main()
 *
 * The main() function implements the concept of "init, define, manage
 * and you're done..."
 */

#ifdef PROTOTYPE
NINT main (NINT argc, pTEXT argv[])
#else
NINT main (argc, argv)
NINT argc;
pTEXT argv[];
#endif
{
   Initialize();

   Define();

   Manage();

   Done();

   printf ("\nPress <ENTER> key to exit . . .");
   getchar();

   return(0);
}


/*
 * Initialize()
 *
 * Perform the minimum requirement of logging onto the c-tree Server
 */

#ifdef PROTOTYPE
VOID Initialize(VOID)
#else
VOID Initialize()
#endif
{
#ifdef ctThrds
   NINT  retval;
#endif

   printf("INIT\n");

#ifdef ctThrds
   /* initialize c-tree multi-thread environment */
   if ((retval = ctThrdInit(3, 0L, NULL)) != 0)
      Handle_Error("Initialize(): ctThrdInit()", retval);
#endif

   /* initialize c-tree Plus and log on to c-tree Server */
   printf("\tLogon to server...\n");
   if (InitISAMXtd(16, 16, 16, 16, 0, "ADMIN", "ADMIN", "FAIRCOMS"))
      Handle_Error("Initialize(): InitISAMXtd()", 0);
}


/*
 * Define()
 *
 * Open the table, if it exists. Otherwise create and open the table
 */

VOID Define(VOID)
{
   printf("DEFINE\n");

   /* attempt to open files */
   printf("\tOpen table...\n");
   custmast_filno = OpenFileWithResource(-1, "custmast.dat", ctEXCLUSIVE);
   if (custmast_filno >= 0)
   {
      /* delete files to avoid any possible incompatibility
         with existing files created by other tutorials */
      TRANBEG(ctTRNLOG); /* Begin */
      if (DeleteRFile(custmast_filno))
         Handle_Error("Define(): DeleteRFile()", 0);
      TRANEND(ctFREE); /* Commit */
   }

   /* create files */
   printf("\tCreate table...\n");
   if (CreateIFile(&custmast_ifil))
      Handle_Error("Define(): CreateIFile()", 0);

   /* store record information into data file */
   if (PutDODA(custmast_ifil.tfilno, custmast_doda, (UCOUNT)NBR_OF_FIELDS))
      Handle_Error("Define(): PutDODA()", 0);

   /* close files */
   CloseIFile(&custmast_ifil);

   /* open files */
   custmast_filno = OpenFileWithResource(-1, "custmast.dat", ctEXCLUSIVE);
   if (custmast_filno < 0)
      Handle_Error("Define(): OpenFileWithResource()", 0);
}


/*
 * Manage()
 *
 * This function performs simple record functions of add, delete and gets
 */

#ifdef PROTOTYPE
VOID Manage(VOID)
#else
VOID Manage()
#endif
{
   printf("MANAGE\n");

   /* delete any existing record */
   Delete_Records();

   /* populate the table with data */
   Add_Records();

   /* show contents of table */
   Display_Records();
}


/*
 * Done()
 *
 * This function handles the housekeeping of closing tables and
 * freeing of associated memory
 */

#ifdef PROTOTYPE
VOID Done(VOID)
#else
VOID Done()
#endif
{
   COUNT retval;

   printf("DONE\n");

   /* close and delete table (optional) */
   printf("\tClose table...\n");
   retval = DeleteRFile(custmast_filno);
   if (retval != NO_ERROR)
      Handle_Error("Done(): DeleteRFile()", 0);

   /* logout and free memory */
   printf("\tLogout...\n");
   CloseISAM();
#ifdef ctThrds
   ctThrdTerm();
#endif
}


/*
 * Delete_Records()
 *
 * This function deletes all the records in the table
 */

#ifdef PROTOTYPE
VOID Delete_Records(VOID)
#else
VOID Delete_Records()
#endif
{
   COUNT retval;
   NINT  empty;
   TEXT  recbuf[MAX_RECORD_SIZE];
   VRLEN reclen;

   printf("\tDelete records...\n");

   empty = NO;
   reclen = sizeof(recbuf);
   retval = FirstVRecord(custmast_filno, &recbuf, &reclen);
   if (retval != NO_ERROR)
   {
      if (retval == END_OF_FILE)
         empty = YES;
      else
         Handle_Error("Delete_Records(): FirstVRecord()", 0);
   }

   while (empty == NO) /* while table is not empty */
   {
      /* delete record */
      if (DeleteVRecord(custmast_filno))
         Handle_Error("Delete_Records(): DeleteVRecord()", 0);

      /* read next record */
      reclen = sizeof(recbuf);
      retval = NextVRecord(custmast_filno, &recbuf, &reclen);
      if (retval != NO_ERROR)
      {
         if (retval == END_OF_FILE)
            empty = YES;
         else
            Handle_Error("Delete_Records(): NextVRecord()", 0);
      }
   }
}


/*
 * Add_Records()
 *
 * This function adds records to a table in the database from an
 * array of strings
 */

typedef struct {
   pTEXT number, zipcode, state, rating, name, address, city;
} CUSTOMER_DATA;

CUSTOMER_DATA data[] = {
   "1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency",      "Orange",
   "1001", "61434", "CT", "1", "Michael Jordan", "13 Main",           "Harford",
   "1002", "73677", "GA", "1", "Joshua Brown",   "4356 Cambridge",    "Atlanta",
   "1003", "10034", "MO", "1", "Keyon Dooling",  "19771 Park Avenue", "Columbia"
};

#ifdef PROTOTYPE
VOID Add_Records(VOID)
#else
VOID Add_Records()
#endif
{
   COUNT i;
   COUNT nRecords = sizeof(data) / sizeof(CUSTOMER_DATA);
   TEXT  recbuf[MAX_RECORD_SIZE];
   VRLEN offset;

   printf("\tAdd records...\n");

   /* add data to table */
   for(i = 0; i < nRecords; i++)
   {
      ctsfill(recbuf, 0, sizeof(recbuf));

      /* populate record buffer with data */
      offset = 0;
      cpybuf(recbuf+offset, data[i].number, strlen(data[i].number));
      offset += NUMBLEN;
      cpybuf(recbuf+offset, data[i].zipcode, strlen(data[i].zipcode));
      offset += ZIPCLEN;
      cpybuf(recbuf+offset, data[i].state, strlen(data[i].state));
      offset += STATLEN;
      cpybuf(recbuf+offset, data[i].rating, strlen(data[i].rating));
      offset += RATGLEN;
      cpybuf(recbuf+offset, data[i].name, strlen(data[i].name));
      offset += (VRLEN) strlen(data[i].name) + 1;
      cpybuf(recbuf+offset, data[i].address, strlen(data[i].address));
      offset += (VRLEN) strlen(data[i].address) + 1;
      cpybuf(recbuf+offset, data[i].city, strlen(data[i].city));
      offset += (VRLEN) strlen(data[i].city) + 1;

      /* add record */
      if (AddVRecord(custmast_filno, recbuf, offset))
         Handle_Error("Add_Records():  AddVRecord()", 0);
   }
}


/*
 * Display_Records()
 *
 * This function displays the contents of a table. FirstVRecord() and
 * NextVRecord() fetch the record. Then each field is parsed and displayed
 */

#ifdef PROTOTYPE
VOID Display_Records(VOID)
#else
VOID Display_Records()
#endif
{
   COUNT retval;
   TEXT  recbuf[MAX_RECORD_SIZE];
   VRLEN reclen;
   TEXT  custnumb[NUMBLEN+1];
   TEXT  custname[NAMELEN+1];
   pTEXT fldptr;

   printf("\tDisplay records...");

   /* read first record */
   reclen = sizeof(recbuf);
   retval = FirstVRecord(custmast_filno, &recbuf, &reclen);
   if (retval != NO_ERROR)
      Handle_Error("Display_Records(): FirstVRecord()", 0);

   while (retval != END_OF_FILE) /* while records are found */
   {
      ctsfill(custnumb, 0, sizeof(custnumb));
      ctsfill(custname, 0, sizeof(custname));

      /* get customer number from record buffer */
      fldptr = recbuf + 0; /* set field pointer to field position */
      strncpy(custnumb, fldptr, NUMBLEN); /* copy field from record buffer to display string */

      /* get customer name from record buffer */
      fldptr = recbuf + FIXED_RECORD_SIZE; /* set field pointer to field position */
      strcpy(custname, fldptr); /* copy field from record buffer to display string */

      printf("\n\t\t%-8s%10s\n",custnumb, custname);

      /* read next record */
      reclen = sizeof(recbuf);
      retval = NextVRecord(custmast_filno, &recbuf, &reclen);
      if (retval == END_OF_FILE)
         break;   /* reached end of file */

      if (retval != NO_ERROR)
         Handle_Error("Display_Records(): NextVRecord()", 0);
   }
}


/*
 * Handle_Error()
 *
 * This function is a common bailout routine. It displays an error message
 * allowing the user to acknowledge before terminating the application
 */

#ifdef PROTOTYPE
VOID Handle_Error(pTEXT errmsg, NINT retval)
#else
VOID Handle_Error(errmsg, retval)
pTEXT errmsg;
NINT retval;
#endif
{
   if (!isam_err && retval)
      printf("\nERROR: [%d] - %s \n", retval, errmsg);
   else
      printf("\nERROR: %s\nisam_err = %d, isam_fil = %d, sysiocod = %d\n", errmsg, isam_err, isam_fil, sysiocod);
   printf("*** Execution aborted *** \nPress <ENTER> key to exit...");
   getchar();

   exit(1);
}

/* end of isam_tutorial1.c */
