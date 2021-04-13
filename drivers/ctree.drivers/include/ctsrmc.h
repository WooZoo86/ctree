//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MSG_START
//
// MessageText:
//
//  %1
//
#define MSG_START                        0x00000000L

//
// MessageId: MSG_STOP
//
// MessageText:
//
//  %1
//
#define MSG_STOP                         0x00000001L

//
// MessageId: MSG_ERR
//
// MessageText:
//
//  %1
//
#define MSG_ERR                          0xC0000002L

//
// MessageId: MSG_SCM
//
// MessageText:
//
//  To start the FairCom Server Service, use the "Services" Control Panel applet or the ctntinst.exe utility.
//
#define MSG_SCM                          0xC0000003L

//
// MessageId: MSG_NOSET
//
// MessageText:
//
//  The Server's settings file is missing.%nIt is required to operate this server.
//
#define MSG_NOSET                        0xC0000004L

//
// MessageId: MSG_BADSET
//
// MessageText:
//
//  The current Server's settings file is invalid.%nUse current FairCom utility to recreate the settings file.
//
#define MSG_BADSET                       0xC0000005L

//
// MessageId: MSG_ACTVAT
//
// MessageText:
//
//  This server must be activated with a FairCom activation key in order to operate. See 'Server Activation Key Card' within your package for more information.
//
#define MSG_ACTVAT                       0xC0000006L

/* end of ctsrmc.h */
