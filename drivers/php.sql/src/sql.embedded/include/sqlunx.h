/*****************************************************************
** SQLUNX.H - Mappings of Windows-style declarations and typedefs
**	      for unix.
**
** Copyright: 1992-1999 MERANT, Inc.	
** This software contains confidential and proprietary
** information of MERANT, Inc.
*********************************************************************/

#ifndef __SQLUNX
#define __SQLUNX

/* Unix versions of Wintel declaration modifiers */

#define NEAR
#define FAR
#define EXPORT
#define PASCAL
#define VOID void
#define CALLBACK
#define _cdecl
#define __stdcall

/* Windows-style typedefs */

typedef VOID * HANDLE;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
#ifndef FAIRCOM_MOD
typedef long LONG;
#endif
typedef int BOOL;
typedef VOID * LPVOID;
typedef VOID * PVOID;
typedef VOID * HMODULE;
typedef int GLOBALHANDLE;
typedef int (*FARPROC)();
typedef char *LPSTR;
typedef const char * LPCSTR;
typedef VOID * HINSTANCE;
typedef VOID * HWND;
typedef unsigned int WPARAM;
typedef unsigned long LPARAM;
typedef VOID * HKEY; 
typedef VOID * PHKEY;
typedef BYTE * LPBYTE;
typedef char CHAR;
typedef BOOL * LPBOOL;
typedef DWORD * LPDWORD;
typedef char * LPWSTR;
typedef const char * LPCWSTR;
typedef char TCHAR;
#ifndef FAIRCOM_MOD
typedef char WCHAR;
#endif

/* DC737 BEGIIN */
#if DH_ENABLE_VCHAR
typedef char VCHAR;
#endif
/* DC737 END */

typedef TCHAR * LPTSTR;
typedef const TCHAR* LPCTSTR;

#endif
