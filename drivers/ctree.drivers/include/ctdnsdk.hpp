/*
 *      OFFICIAL NOTIFICATION: the following CONFIDENTIAL and PROPRIETARY 
 * 	property legend shall not be removed from this source code module 
 * 	for any reason.
 *
 *	This program is the CONFIDENTIAL and PROPRIETARY property 
 *	of FairCom(R) Corporation. Any unauthorized use, reproduction or
 *	transfer of this computer program is strictly prohibited. The 
 *      contents of this file may not be disclosed to third parties, copied or
 *      duplicated in any form, in whole or in part, without the prior written
 *      permission of the FairCom(R) Corporation.
 *
 *      Copyright (c) 1992 - 2020 FairCom Corporation.
 *	This is an unpublished work, and is subject to limited distribution and
 *	restricted disclosure only. ALL RIGHTS RESERVED.
 *
 *			RESTRICTED RIGHTS LEGEND
 *	Use, duplication, or disclosure by the Government is subject to
 *	restrictions set forth in subparagraph (c)(1)(ii) of the Rights in
 * 	Technical Data and Computer Software clause at DFARS 252.227-7013, and/or
 *      in similar or successor clauses in the FAR, DOD or NASA FAR Supplement.
 *      Unpublished rights reserved under the Copyright Laws of the United States.
 *	FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203.
 *
 *	c-treeACE(tm)	Version 11
 */

#ifndef _CTDNSDK_HPP_
#define _CTDNSDK_HPP_

#ifndef ctNoOldGetSet
#define oldGetSet
#endif
/*^****************************************************************************\
*
*   Header Files
*
\******************************************************************************/
#include "ctdbsdk.h"
#include "CtDbNet.h"

using namespace System;
using namespace System::Text;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace FairCom::CtreeDb::ENUMS;
using namespace FairCom::CtreeDb::INDEXES;
using namespace FairCom::CtreeDb::BATCH;
using namespace FairCom::CtreeDb::REBUILD;

[assembly:AssemblyTitleAttribute("FairCom.CtreeDb")];
[assembly:AssemblyDescriptionAttribute("c-treePlus for .NET")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("FairCom Corporation")];
#if _MSC_VER == 1310
[assembly:AssemblyProductAttribute("V7")];
#else
[assembly:AssemblyProductAttribute("V8")];
#endif
[assembly:AssemblyCopyrightAttribute("Copyright (c) 1992 - 2020 FairCom Corporation.")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];
[assembly:AssemblyVersionAttribute("1.0.1.0")];
[assembly:AssemblyDelaySignAttribute(false)];
[assembly:AssemblyKeyFileAttribute(fcKEY)];
//[assembly:AssemblyKeyFileAttribute("..\\..\\..\\..\\ctreedotNET\\faircom.snk")];
[assembly:AssemblyKeyNameAttribute("")];

/*^****************************************************************************\
*
*   CTDN  API version
*
*   Bits  0-15   Build number
*   Bits 16-23   Version number
*   Bits 24-31   Release number
*
\******************************************************************************/
#define CTDN_BUILD_NBR      0x00000001
#define CTDN_VERSION_NBR    0x00010000
#define CTDN_RELEASE_NBR    0x00000000
#define CTDN_VERSION        (CTDN_RELEASE_NBR | CTDN_VERSION_NBR | CTDN_BUILD_NBR)
/*^****************************************************************************\
*
*   CTException
*   Base exception class for CTDN  API
*
\******************************************************************************/
public __gc class CTException : public System::Exception
{
    // Constructors & destructor
    public:
        CTException(NINT ErrorCode);
        CTException(NINT ErrorCode, String* ErrorMsg);
        CTException(NINT ErrorCode, pTEXT SourceFile, NINT LineNbr);
        CTException(NINT ErrorCode, pTEXT ErrorMsg, pTEXT SourceFile, NINT LineNbr);
        virtual ~CTException();
       
    // Methods
    public:
        virtual NINT GetErrorCode() ;
		virtual String* GetErrorMsg();
        virtual String* GetSourceFile();
        virtual NINT GetLineNbr() ;
                
   // Members
   private:
        NINT    m_error;
		String *m_msg;
		String *m_file;
        NINT    m_line;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTDate
*   CTDN API date class
*
\******************************************************************************/
public __gc class CTDate
{
    // Methods
    public:
        CTDATE GetDate() 
            {return m_date;}

		void SetDate(CTDATE Date)
            {m_date = Date;}
            
        void SetDate( CTDate& Date)
            {m_date = Date.m_date;}

        void Pack(NINT year, NINT month, NINT day);

    // Constructors & destructor
    public:
        CTDate()
            {m_date = 0;}
            
        CTDate(NINT year, NINT month, NINT day)
            {Pack(year, month, day);}
            
        CTDate(CTDATE Date)
            {SetDate(Date);}
            
        CTDate( CTDate& Date)
            {SetDate(Date);}
            
        virtual ~CTDate()
            {}
        
    // Operators
    public:
		static CTDate* op_Implicit(CTDATE Date)
            {return new CTDate(Date);}

		static CTDate* op_Implicit(CTDate* Date)
            {return new CTDate(*Date);}

		static bool op_LessThan(CTDate& Date1, CTDate& Date2) 
            {return (Date1.m_date < Date2.m_date) ? YES : NO;}

		static bool op_LessThanOrEqual(CTDate& Date1, CTDate& Date2) 
            {return (Date1.m_date <= Date2.m_date) ? YES : NO;}

		static bool op_GreaterThan(CTDate& Date1, CTDate& Date2) 
            {return (Date1.m_date > Date2.m_date) ? YES : NO;}

		static bool op_GreaterThanOrEqual(CTDate& Date1, CTDate& Date2) 
            {return (Date1.m_date >= Date2.m_date) ? YES : NO;}

		static bool op_Equality(CTDate& Date1, CTDate& Date2) 
            {return (Date1.m_date == Date2.m_date) ? YES : NO;}

		static bool op_Inequality(CTDate& Date1, CTDate& Date2) 
            {return (Date1.m_date != Date2.m_date) ? YES : NO;}

            
    // Methods
    public:
        NINT Year() ;
        NINT Month() ;
        NINT Day() ;
        NINT DayOfWeek() ;
        bool IsLeapYear() ;
        void Unpack([Out]NINT __gc* year, [Out]NINT __gc* month, [Out]NINT __gc* day) ;
		String* DateToString(DATE_TYPE DateType) ;
        void StringToDate(String* str, DATE_TYPE DateType);
        static CTDate* CurrentDate();
    // Members
    private:
        CTDATE  m_date;    
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTTime
*   CTDN API Time class
*
\******************************************************************************/
public __gc class CTTime
{
    // Methods
    public:
        void Pack(NINT hour, NINT minute, NINT second);

	// Constructors & destructor
    public:
        CTTime()
            {m_time = 0;}
            
        CTTime(NINT hour, NINT minute, NINT second)
            {Pack(hour, minute, second);}
            
        CTTime(CTTIME Time)
            {m_time = Time;}
            
        CTTime( CTTime& Time)
            {m_time = Time.m_time;}
            
        virtual ~CTTime()
            {}

    // Operators
    public:
		static CTTime* op_Implicit(CTTIME Time)
            {return new CTTime(Time);}

		static CTTime* op_Implicit(CTTime* Time)
            {return new CTTime(*Time);}

		static bool op_LessThan(CTTime& Time1, CTTime& Time2)
            {return (Time1.m_time < Time2.m_time) ? YES : NO;}

        static bool op_LessThanOrEqual(CTTime& Time1, CTTime& Time2)
            {return (Time1.m_time <= Time2.m_time) ? YES : NO;}

        static bool op_GreaterThan(CTTime& Time1, CTTime& Time2)
            {return (Time1.m_time > Time2.m_time) ? YES : NO;}

        static bool op_GreaterThanOrEqual(CTTime& Time1, CTTime& Time2)
            {return (Time1.m_time >= Time2.m_time) ? YES : NO;}

        static bool op_Equality(CTTime& Time1, CTTime& Time2)
            {return (Time1.m_time == Time2.m_time) ? YES : NO;}

        static bool op_Inequality(CTTime& Time1, CTTime& Time2)
            {return (Time1.m_time != Time2.m_time) ? YES : NO;}

    // Methods
    public:
        CTTIME GetTime() 
            {return m_time;}
            
        void SetTime(CTTIME Time)
            {m_time = Time;}
            
        void SetTime( CTTime& Time)
            {m_time = Time.m_time;}
            
        NINT Hour() ;
        NINT Minute() ;
        NINT Second() ;

        void Unpack([Out]NINT __gc* hour, [Out]NINT __gc* minute, [Out]NINT __gc* second);
        String* TimeToString(TIME_TYPE TimeType);
        void StringToTime(String* str, TIME_TYPE TimeType);
        static CTTime* CurrentTime();
    // Members
    private:
        CTTIME  m_time;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTDateTime
*   CTDN API Date Time class
*
\******************************************************************************/
public __gc class CTDateTime
{
    // Methods
	public:
	void Pack(NINT year, NINT month, NINT day, NINT hour, NINT minute, NINT second);
	void SetDateTime(CTDate* Date, CTTime* Time);
	void SetDateTime(CTDATE Date, CTTIME Time);
    void SetDateTime(CTDateTime* DateTime)
		{m_datetime = DateTime->m_datetime;}
            
    void SetDateTime(CTDATETIME DateTime)
        {m_datetime = DateTime;}


	// Constructors & destructors
    public:
        CTDateTime()
            {m_datetime = 0.0;}
 
		CTDateTime(NINT year, NINT month, NINT day)
            {Pack(year, month, day, 0, 0, 0);}
		CTDateTime(CTDATE Date)
            {SetDateTime(Date, 0);}
		CTDateTime(CTDATE Date, CTTIME Time)
            {SetDateTime(Date, Time);}
		CTDateTime(CTDate* Date)
            {SetDateTime(Date, (CTTime*)0);}
		CTDateTime(CTDate* Date, CTTime* Time)
            {SetDateTime(Date, Time);}
        CTDateTime(CTDateTime* DateTime)
            {SetDateTime(DateTime);}
        CTDateTime(CTDATETIME DateTime)
            {SetDateTime(DateTime);}
            
        virtual ~CTDateTime()
            {}
        
    // Operators
    public:
		static CTDateTime* op_Implicit(CTDATETIME DateTime)
			{return new CTDateTime(DateTime);}

		static bool op_LessThan(CTDateTime& DateTime1, CTDateTime& DateTime2)
            {return (DateTime1.m_datetime < DateTime2.m_datetime) ? YES : NO;}

		static bool op_LessThanOrEqual(CTDateTime& DateTime1, CTDateTime& DateTime2)
            {return (DateTime1.m_datetime <= DateTime2.m_datetime) ? YES : NO;}

		static bool op_GreaterThan(CTDateTime& DateTime1, CTDateTime& DateTime2)
            {return (DateTime1.m_datetime > DateTime2.m_datetime) ? YES : NO;}

		static bool op_GreaterThanOrEqual(CTDateTime& DateTime1, CTDateTime& DateTime2)
            {return (DateTime1.m_datetime >= DateTime2.m_datetime) ? YES : NO;}

		static bool op_Equalty(CTDateTime& DateTime1, CTDateTime& DateTime2)
            {return (DateTime1.m_datetime == DateTime2.m_datetime) ? YES : NO;}
	
		static bool op_Inequality(CTDateTime& DateTime1, CTDateTime& DateTime2)
            {return (DateTime1.m_datetime != DateTime2.m_datetime) ? YES : NO;}
            
    // Methods
    public:
        CTDATETIME GetDateTime() 
            {return m_datetime;}
                     
        NINT Year() ;
        NINT Month() ;
        NINT Day() ;
        NINT DayOfWeek() ;
        bool IsLeapYear() ;
        NINT Hour() ;
        NINT Minute() ;
        NINT Second() ;
        void Unpack([Out]NINT __gc* year, [Out]NINT __gc* month, [Out]NINT __gc* day, [Out]NINT __gc* hour, [Out]NINT __gc* minute, [Out]NINT __gc* second);
        CTDate* GetDate();
        CTTime* GetTime();
		static CTDateTime* CurrentDateTime();
        static CTDateTime* CurrentDate();
        void StringToDateTime(String* str, DATE_TYPE DateType, TIME_TYPE TimeType);
        String* DateTimeToString(DATE_TYPE DateType, TIME_TYPE TimeType);

		// Members
    private:
        CTDATETIME  m_datetime;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTMoney
*   CTDN API Money class
*
\******************************************************************************/
public __gc class CTMoney
{
    // Methods
    public:
        void SetMoney(CTFLOAT value);
        void SetMoney(CTMONEY money);
		void SetMoney(String* str);
        void SetMoney(CTMoney* money);

	// Constructors & destructor
    public:
        CTMoney()
            {m_money = 0;}
           
        CTMoney(CTFLOAT value)
            {SetMoney(value);}
            
        CTMoney(CTMONEY money)
            {SetMoney(money);}
            
		CTMoney(String* str)
            {SetMoney(str);}
            
		CTMoney( CTMoney* money)
            {SetMoney(money);}
            
        virtual ~CTMoney()
        {}
        
        
    // Operators
    public:
		static CTMoney* op_Implicit(float value)
            {return new CTMoney(value);}

		static CTMoney* op_Implicit(CTMONEY value)
            {return new CTMoney(value);}
		
		static CTMoney* op_Implicit(String* str)
            {return new CTMoney(str);}

		static CTMoney* op_Implicit(CTMoney* money)
            {return new CTMoney(money);}

		CTMoney* abs(CTMoney* money);
        static CTMoney* op_Addition(CTMoney* left, CTMoney* right);
        static CTMoney* op_Subtraction(CTMoney* left, CTMoney* right);
        static CTMoney* op_Multiply(CTMoney* left, CTMoney* right);
        static CTMoney* op_Division(CTMoney* left, CTMoney* right);
		static bool op_LessThan(CTMoney* left, CTMoney* right);
		static bool op_LessThanOrEqual(CTMoney* left, CTMoney* right);
		static bool op_GreaterThan(CTMoney* left, CTMoney* right);
		static bool op_GreaterThanOrEqual(CTMoney* left, CTMoney* right);
		static bool op_Equality(CTMoney* left, CTMoney* right);
		static bool op_Inequality(CTMoney* left, CTMoney* right);
            
    // Methods
    public:
        CTMONEY AsMoney() ;
		__int64 AsLong();
        float AsFloat();
        String* AsString();
		void StringToMoney(String* str);
    // Members
    public:
        CTMONEY m_money;

};

/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTBigint
*   CTDN API big integer (64 bit integer) class
*	
*
\******************************************************************************/
public __gc class CTBigint
{
		// Methods
	public:
		void SetBigint(LONG value);
		void SetBigint(ULONG value);
		void SetBigint(CTFLOAT value);
		bool IsZero() ;
		void SetBigint(CTMoney* value);
		void SetBigint(String* value);
		void SetBigint(CTBigint* value);

	// Constructors
	public:
		CTBigint()
			{m_bigint = 0;}
		CTBigint(LONG value)
			{SetBigint(value);}
		CTBigint(CTFLOAT value)
			{SetBigint(value);}
		CTBigint(CTBIGINT value)
			{m_bigint = value;}
		CTBigint(CTUBIGINT value)
			{m_bigint = value;}
		CTBigint(CTMoney* value)
			{SetBigint(value);}
		CTBigint(String* value)
			{SetBigint(value);}
		CTBigint(CTBigint* value)
			{SetBigint(value);}
		virtual ~CTBigint()
			{}
		
	// operators
	public:
		static CTBigint* op_Implicit(LONG value)
            {return new CTBigint(value);}
		static CTBigint* op_Implicit(CTFLOAT value)
            {return new CTBigint(value);}
		static CTBigint* op_Implicit(CTBIGINT value)
            {return new CTBigint(value);}
		static CTBigint* op_Implicit(CTUBIGINT value)
            {return new CTBigint(value);}
		static CTBigint* op_Implicit(CTMoney* value)
            {return new CTBigint(value);}
		static CTBigint* op_Implicit(String* value)
            {return new CTBigint(value);}
		static CTBigint* op_Implicit(CTBigint* value)
            {return new CTBigint(value);}
		CTBigint* abs(CTBigint* value);
        static CTBigint* op_Addition(CTBigint* left, CTBigint* right);
        static CTBigint* op_Subtraction(CTBigint* left, CTBigint* right);
        static CTBigint* op_Multiply(CTBigint* left, CTBigint* right);
        static CTBigint* op_Division(CTBigint* left, CTBigint* right);
		static bool op_LessThan(CTBigint* left, CTBigint* right);
		static bool op_LessThanOrEqual(CTBigint* left, CTBigint* right);
		static bool op_GreaterThan(CTBigint* left, CTBigint* right);
		static bool op_GreaterThanOrEqual(CTBigint* left, CTBigint* right);
		static bool op_Equality(CTBigint* left, CTBigint* right);
		static bool op_Inequality(CTBigint* left, CTBigint* right);

	// Methods
	public:
		__int64 AsLong();
		unsigned __int64 AsUnsignedLong();
		float AsFloat();
		CTMoney* AsMoney() ;
		String* AsString();
		CTBIGINT AsBigint() ;
		CTUBIGINT AsUnsignedBigint(); 
		void Zero();

	// Members
	public:
		CTBIGINT	m_bigint;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTCurrency
*   CTDN API currency class
*
\******************************************************************************/
public __gc class CTCurrency
{
	// Methods
	public:
		void SetCurrency(LONG value);
		void SetCurrency(CTFLOAT value);
		void SetCurrency(CTMoney* value);
		void SetCurrency(String* value);
		void SetCurrency(CTBigint* value);

	// Constructors & destructor
	public:
		CTCurrency()
			{m_currency = 0;}
		CTCurrency(LONG value)
			{SetCurrency(value);}
		CTCurrency(CTFLOAT value)
			{SetCurrency(value);}
		CTCurrency(CTCURRENCY value)
			{m_currency = value;}
		CTCurrency(CTMoney* value)
			{SetCurrency(value);}
		CTCurrency(String* value)
			{SetCurrency(value);}
		CTCurrency(CTBigint* value)
			{SetCurrency(value);}
		CTCurrency(CTCurrency* value)
			{m_currency = value->m_currency;}
		virtual ~CTCurrency()
			{}
					
	// operators
	public:
		static CTCurrency* op_Implicit(LONG value)
            {return new CTCurrency(value);}
		static CTCurrency* op_Implicit(CTFLOAT value)
            {return new CTCurrency(value);}
		static CTCurrency* op_Implicit(CTCURRENCY value)
            {return new CTCurrency(value);}
		static CTCurrency* op_Implicit(CTMoney* value)
            {return new CTCurrency(value);}
		static CTCurrency* op_Implicit(String* value)
            {return new CTCurrency(value);}
		static CTCurrency* op_Implicit(CTBigint* value)
            {return new CTCurrency(value);}
		static CTCurrency* op_Implicit(CTCurrency* value)
            {return new CTCurrency(value);}
		static CTCurrency* abs(CTCurrency* value);
        static CTCurrency* op_Addition(CTCurrency* left, CTCurrency* right);
        static CTCurrency* op_Subtraction(CTCurrency* left, CTCurrency* right);
        static CTCurrency* op_Multiply(CTCurrency* left, CTCurrency* right);
        static CTCurrency* op_Division(CTCurrency* left, CTCurrency* right);
		static bool op_LessThan(CTCurrency* left, CTCurrency* right);
		static bool op_LessThanOrEqual(CTCurrency* left, CTCurrency* right);
		static bool op_GreaterThan(CTCurrency* left, CTCurrency* right);
		static bool op_GreaterThanOrEqual(CTCurrency* left, CTCurrency* right);
		static bool op_Equality(CTCurrency* left, CTCurrency* right);
		static bool op_Inequality(CTCurrency* left, CTCurrency* right);
	
	// Methods
	public:
		bool IsZero() ;
		void Zero();
		CTCURRENCY AsCurrency() ;
		CTCurrency* Round(NINT scale);
		__int64 AsLong();
		float AsFloat();
		CTMoney* AsMoney();
		String* AsString();
		CTBigint* AsBigint();
	// Members
	public:
		CTCURRENCY	m_currency;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTNumber
*   CTDN  API CTNumber class
*
\******************************************************************************/
public __gc class CTNumber
{
	// Constructors & destructor
	public:
		CTNumber();
		CTNumber(LONG value);
		CTNumber(CTFLOAT value);
		CTNumber(ctdbNUMBER value);
		CTNumber(CTMoney* value);
		CTNumber(String* value);
		CTNumber(CTBigint* value);
		CTNumber(CTCurrency* value);
		CTNumber(CTNumber* value);
		virtual ~CTNumber();
			
	// operators
	public:
		static CTNumber* op_Implicit(LONG value)
            {return new CTNumber(value);}
		static CTNumber* op_Implicit(DOUBLE value)
            {return new CTNumber(value);}
		static CTNumber* op_Implicit(ctdbNUMBER value)
            {return new CTNumber(value);}
		static CTNumber* op_Implicit(CTMoney* value)
            {return new CTNumber(value);}
		static CTNumber* op_Implicit(String* value)
            {return new CTNumber(value);}
		static CTNumber* op_Implicit(CTBigint* value)
            {return new CTNumber(value);}
		static CTNumber* op_Implicit(CTCurrency* value)
            {return new CTNumber(value);}
		static CTNumber* op_Implicit(CTNumber* value)
            {return new CTNumber(value);}
		static CTNumber* abs(CTNumber* value);
        static CTNumber* op_Addition(CTNumber* left, CTNumber* right);
        static CTNumber* op_Subtraction(CTNumber* left, CTNumber* right);
		static CTNumber* op_Multiply(CTNumber* left, CTNumber* right);
	    static CTNumber* op_Division(CTNumber* left, CTNumber* right);
		static bool op_LessThan(CTNumber* left, CTNumber* right);
		static bool op_LessThanOrEqual(CTNumber* left, CTNumber* right);
		static bool op_GreaterThan(CTNumber* left, CTNumber* right);
		static bool op_GreaterThanOrEqual(CTNumber* left, CTNumber* right);
		static bool op_Equality(CTNumber* left, CTNumber* right);
		static bool op_Inequality(CTNumber* left, CTNumber* right);

	// Methods
	public:
		bool IsZero() ;
		void Zero() ;
		NINT IntegralDigits() ;
		NINT DecimalDigits() ;
		void SetNumber(LONG value);
		void SetNumber(CTFLOAT value);
		float AsFloat();
		CTMoney* AsMoney();
		CTNumber* Round(NINT scale);
		String* AsString();
		CTBigint* AsBigint();
		CTCurrency* AsCurrency();
		__int64 AsLong() ;
		ctdbNUMBER AsNumber();
		void SetNumber(ctdbNUMBER value);
		void SetNumber(String* value);
		void SetNumber(CTMoney* value);
		void SetNumber(CTBigint* value);
		void SetNumber(CTCurrency* value);
		void SetNumber(CTNumber* value);
	// Members
public:
		ctdbNUMBER m_number;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTBlob
*   CTDN  API BLOB class
*
\******************************************************************************/
public __gc class CTBlob
{
    // Constructors & destructor
    public:
        CTBlob();
        virtual ~CTBlob();
        CTBlob(IntPtr data, VRLEN size);
        CTBlob(ctdbBLOB pBlob);
        CTBlob(CTBlob* blob);
//		CTBlob(Byte arr __gc[]);

    // Operators
    public:
		static CTBlob* op_Implicit(ctdbBLOB blob)
            {return new CTBlob(blob);}
		static CTBlob* op_Implicit(CTBlob* blob)
            {return new CTBlob(blob);}
		static bool op_LessThan(CTBlob* left, CTBlob* right);
		static bool op_LessThanOrEqual(CTBlob* left, CTBlob* right);
		static bool op_GreaterThan(CTBlob* left, CTBlob* right);
		static bool op_GreaterThanOrEqual(CTBlob* left, CTBlob* right);
		static bool op_Equality(CTBlob* left, CTBlob* right);
		static bool op_Inequality(CTBlob* left, CTBlob* right);

        VRLEN GetSize() ;
        void GetBlob([Out]ctdbBLOB __gc* pBlob);
        void SetBlob(IntPtr data, VRLEN size);
        void SetBlob(CTBlob* blob);
        void SetBlob(ctdbBLOB pBlob);
//		void AsByteArray(Byte arr __gc[]);

    // Members
    public:
        ctdbBLOB m_blob;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   Forward class declarations
*
\******************************************************************************/
public __gc class CTSession;
public __gc class CTDatabase;
public __gc class CTTable;
public __gc class CTResource;
public __gc class CTRecord;
public __gc class CTField;
public __gc class CTIndex;
public __gc class CTSegment;
public __gc class CTHelloWorld; /* CTDB HELLO WORLD */

/*^****************************************************************************\
*
*   CTBase
*   CTDN  API base class
*
\******************************************************************************/
public __gc class CTBase
{
    // Constructors & destructor
    public:
        CTBase();
        virtual ~CTBase();

    // Methods
    public:
        virtual CTDBRET GetError();
        virtual void SetError( CTDBRET code);
        virtual void ClearError();
        virtual bool IsTransActive() ;
        virtual void Begin();
        virtual void Commit();
        virtual void Abort();
        virtual NINT SetSavePoint();
        virtual void RestoreSavePoint( NINT SavePoint);
		virtual bool IsLockActive();
		virtual LOCK_MODE GetLockMode();
        virtual void Lock(LOCK_MODE mode);
		virtual void Unlock();
        virtual NINT GetHandleId() ;
        virtual DATE_TYPE GetDefDateType() ;
        virtual TIME_TYPE GetDefTimeType() ;
        virtual void SetDefDateType(DATE_TYPE DateType);
        virtual void SetDefTimeType(TIME_TYPE TimeType);
		virtual pVOID GetUserTag();
        virtual IntPtr GetHandle() ;
        virtual void SetHandle(IntPtr Handle);
		virtual void SetDefFloatFormat(String* format);
		virtual String* GetDefFloatFormat();
		virtual void SetUserTag([In]IntPtr tagptr);
		virtual KEEP_MODE GetKeepLock();
		virtual void SetKeepLock(KEEP_MODE mode);
		virtual void SwitchInstance();	
#ifdef CTDB_CALLBACK
		virtual NINT GetHandleType();
		virtual TABLE_TYPE GetTableType();
#endif
		virtual LONG GetSystemConfig(NINT index);
		virtual BEGIN_MODE GetTransactionMode();
		virtual void SetTransactionMode(BEGIN_MODE mode);
		virtual OPS_MODE GetOperation();
		virtual void SetOperation(OPS_MODE mode, OPS_STATE state);
		virtual bool GetAutoCommit();
		virtual void SetAutoCommit(bool flag);
		virtual bool IsUnicodeLib();
    // Members
    public:
        CTHANDLE    m_handle;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTSession
*   CTDN  API session class
*
\******************************************************************************/
public __gc class CTSession : public CTBase 
{
    // Constructors & destructor
    public:
		CTSession(SESSION_TYPE SessionType);
		CTSession();
		void Dispose();
     //   virtual ~CTSession();
        
    // Methods
    public:
        virtual void Logout();
        virtual NINT GetParam(SESSION_PARAM ParamType) ;
        virtual void SetParam(SESSION_PARAM ParamType,  NINT value);
        virtual bool IsActive() ;
        virtual void DisconnectAll();
		virtual bool GetLogonOnly();
		virtual NINT GetDatabaseCount();
		virtual void SetSessionType(SESSION_TYPE SessionType);
		virtual SESSION_TYPE GetSessionType();
		virtual void Logon();
		virtual void Logon(String* dbEngine, String* user, String* password);
		virtual void Create();
		virtual void Create(String* dbEngine, String* user, String* password);
		virtual void CreateSession()
			{Create();}
		virtual void CreateSession(String* dbEngine, String* user, String* password)
			{Create(dbEngine, user, password);}
        virtual String* GetServerName();
        virtual String* GetUserLogonName();
        virtual String* GetPassword();
        virtual void SetPath(String* Path);
        virtual String* GetPath();
        virtual bool FirstDatabase([Out]StringBuilder* Name,[Out]StringBuilder* Path);
        virtual bool NextDatabase(StringBuilder* Name, StringBuilder* Path);
        virtual bool FindDatabase(String* Name, StringBuilder* Path);
		virtual bool FindDatabase(String* Name, StringBuilder* Path, [Out]unsigned __int64 __gc* Uid);
		virtual bool FindDatabase(unsigned __int64 Uid, StringBuilder* Name, StringBuilder* Path);
        virtual void CreateDatabase(String* Name, String* Path);
        virtual void AddDatabase(String* Name, String* Path);
        virtual void DeleteDatabase(String* Name);
        virtual void DropDatabase(String* Name);
        virtual void GetDatabaseUID(String* Name, [Out]unsigned __int64 __gc* Uid);
		virtual void SetLogonOnly();
		virtual void SetLogonOnly(bool flag);
		virtual void SetCurrentNodeName(String* NodeName);
		virtual void SetPathPrefix(String* Path);
		virtual void ClearPathPrefix();
		virtual String* GetPathPrefix();
		virtual LIB_TYPE GetLibType();
		virtual bool IsSQLServer();
		virtual void SetExclusive();
		virtual void SetExclusive(bool flag);
		virtual bool IsExclusive();
		virtual void Attach(bool isTransactionActive);
		virtual void Attach()
			{Attach(false);}
		virtual void Attach(String* Ctreeid, bool isTransactionActive);
		virtual void Attach(String* Ctreeid)
			{Attach(Ctreeid, false);}
		virtual void Attach(CTSession* Session);
		virtual void Detach();
		virtual ATTACH_MODE GetAttachMode();
		static CTDBRET SetConfigurationFile(String* ConfigFile);
		static CTDBRET StartDatabaseEngine();
		static void StopDatabaseEngine();
		virtual int GetSessionId(void);
		virtual void SetSessionId(int sessid);

	// Members
	private:
		VRLEN	m_scanrec;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTDatabase
*   CTDN API database class
*
\******************************************************************************/
public __gc class CTDatabase : public CTBase
{
    // Constructors & destructor
    public:
        CTDatabase( CTSession& Handle);
//        CTDatabase( CTSession* Handle);
//        virtual ~CTDatabase();
		void Dispose();

        
    // Methods
    public:
    	virtual bool IsActive();
        virtual void Disconnect();
		virtual void CloseAll();
		virtual NINT GetTableCount();
        virtual void Connect(String* Name);
        virtual void Create(String* Name, String* Path);
		virtual void CreateDatabase(String* Name, String* Path)
			{Create(Name, Path);}
        virtual void AddTable(String* Name, String* Path);
        virtual void DeleteTable(String* Name, String* Password);
        virtual void DropTable(String* Name);
        virtual bool FirstTable(StringBuilder* Name, StringBuilder* Path);
        virtual bool NextTable(StringBuilder* Name, StringBuilder* Path);
        virtual bool FindTable(String* Name, StringBuilder* Path);
		virtual bool FindTable(String* Name, StringBuilder* Path, [Out]unsigned __int64 __gc* Uid);
        virtual bool FindTable(unsigned __int64 uid, StringBuilder* Name, StringBuilder* Path);
        virtual void GetTableUID(String* Name, [Out]unsigned __int64 __gc* Uid);
		virtual String* GetPath();
		virtual String* GetName();
		virtual String* GetDefaultSqlTableOwner();
		virtual void SetDefaultSqlTableOwner(String* Owner);
		virtual bool IsSQL();
		virtual void SetExclusive()
			{SetExclusive(true);}
		virtual void SetExclusive(CTBOOL flag);
		virtual CTBOOL IsExclusive();
		virtual void RenameTable (String* OldName, String* NewName);

	// Members
	private:
		VRLEN	m_scanrec;
}; 
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTTable
*   CTDN API table class
*
\******************************************************************************/
public __gc class CTTable : public CTBase
{
    // Constructors & destructor
    public:
        CTTable( CTDatabase& Handle);
        CTTable( CTSession& Handle);
//		CTTable( CTDatabase* Handle);
//        CTTable( CTSession* Handle);
//        virtual ~CTTable();
		void Dispose();
        
    // Methods
    public:
        virtual bool IsActive() ;
        virtual OPEN_MODE GetOpenMode() ;
        virtual void Close();
        virtual VRLEN GetFieldCount() ;
        virtual VRLEN GetIndexCount() ;
        virtual CREATE_MODE GetCreateMode() ;
        virtual NINT GetDataDefaultExtentSize() ;
        virtual NINT GetIndexDefaultExtentSize() ;
        virtual LONG GetPermission() ;
        virtual void SetDataDefaultExtentSize( NINT size);
        virtual void SetIndexDefaultExtentSize( NINT size);
        virtual void SetPermission( LONG Permmask);
        virtual void DelField( NINT FieldNumber);
		virtual void MoveField( NINT FieldNumber, NINT newNumber);
        virtual void DelIndex(NINT IndexNumber);
        virtual void DelSegment(NINT IndexNUmber, NINT SegNumber);
        virtual void Alter(ALTER_TABLE Action);
        virtual void ResetAll();
        virtual bool HasNullFieldSupport();
		virtual bool HasRecbyt();
		virtual bool HasRowid();
		virtual void UnlockTable();
		virtual void UpdateCreateMode(CREATE_MODE mode);
		virtual String* GetName();
        virtual String* GetPath();
        virtual String* GetDataExtension();
        virtual String* GetIndexExtension();
        virtual void Open(String* Name, OPEN_MODE OpenMode);
        virtual CTField* GetField(NINT FieldNumber);
        virtual CTIndex* GetIndex(NINT IndexNumber);
		virtual CTIndex* GetIndexByUID(unsigned __int64 uid);
        virtual String* GetPassword();
        virtual void SetPassword(String* Password);
        virtual String* GetGroupid();
        virtual void SetPath(String* Path);
		virtual void SetDataExtension(String* Ext);
        virtual void SetIndexExtension(String* Ext);
        virtual void SetGroupid(String* Groupid);
        virtual void Create(String* Name, CREATE_MODE CreateMode);
        virtual void CreateTable(String* Name, CREATE_MODE CreateMode)
			{Create(Name, CreateMode);}
		virtual CTField* AddField(String* Name, FIELD_TYPE Type, VRLEN Length);
        virtual CTField* InsertField(NINT BeforeField,String* Name, FIELD_TYPE Type, VRLEN Length);
        virtual CTField* InsertField(String* BeforeField, String* Name, FIELD_TYPE Type, VRLEN Length);
        virtual void DelField(String* FieldName);
		virtual void MoveField(String* FieldName, NINT newNumber);
        virtual CTField* GetField(String* FieldName);
        virtual NINT GetFieldNumber(String* FieldName);
        virtual CTIndex* AddIndex(String* name, KEY_TYPE KeyType, bool AllowDuplicates, bool NullFlag);
        virtual void DelIndex(String* IndexName);
        virtual CTIndex* GetIndex(String* name);
        virtual CTSegment* GetSegment(CTIndex* pIndex, VRLEN SegNumber);
        virtual CTSegment* AddSegment(CTIndex* pIndex, CTField* pField, SEG_MODE SegMode);
        virtual CTSegment* AddSegment(CTIndex* pIndex, String* FieldName, SEG_MODE SegMode);
        virtual CTSegment* AddSegment(CTIndex* pIndex, NINT FieldNumber, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(CTIndex* pIndex, NINT offset, NINT length, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(NINT IndexNbr, NINT FieldNbr, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(NINT IndexNbr, String* FieldName, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(NINT IndexNbr, CTField* pField, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(String* IndexName, String* FieldName, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(String* IndexName, NINT FieldNumber, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(String* IndexName, CTField* pField, SEG_MODE SegMode);
        virtual CTSegment* InsertSegment(CTIndex* pIndex, NINT BeforeSegment, CTField* Field, SEG_MODE SegMode);
        virtual CTSegment* InsertSegment(CTIndex* pIndex, NINT BeforeSegment, String* FieldName, SEG_MODE SegMode);
        virtual CTSegment* InsertSegment(CTIndex* pIndex, NINT BeforeSegment, NINT FieldNumber, SEG_MODE SegMode);
		virtual CTSegment* InsertSegment(CTIndex* pIndex, NINT BeforeSegment, NINT offset, NINT length, SEG_MODE SegMode);
		virtual CTSegment* InsertSegment(NINT IndexNbr, NINT BeforeSegment, NINT FieldNumber, SEG_MODE SegMode);
		virtual CTSegment* InsertSegment(NINT IndexNbr, NINT BeforeSegment, String* FieldName, SEG_MODE SegMode);
		virtual CTSegment* InsertSegment(String* IndexName, NINT BeforeSegment, String* FieldName, SEG_MODE SegMode);
		virtual CTSegment* InsertSegment(String* IndexName, NINT BeforeSegment, NINT FieldNumber, SEG_MODE SegMode);
		virtual CTSegment* InsertSegment(String* IndexName, NINT BeforeSegment, CTField* Field, SEG_MODE SegMode);
		virtual CTSegment* InsertSegment(NINT IndexNbr, NINT BeforeSegment, CTField* Field, SEG_MODE SegMode);
		virtual void DelSegment(String* IndexName, NINT SegNumber);

#ifdef CTDB_CNDX_IDX 
		virtual void UpdateCndxIndex(NINT indexnbr, String* cndexpr);
		virtual void UpdateCndxIndex(String* indexname, String* cndexpr);
		virtual void GetCndxIndex(NINT indexnbr, StringBuilder* cndexpr);
		virtual void GetCndxIndex(String* indexname, StringBuilder* cndexpr);
#endif /* CTDB_CNDX_IDX  */

#ifdef CTDB_FILTER_020617
		virtual bool IsFilteredRecord();
		virtual void FilterRecord(String* cndexpr);
		virtual void GetFilter(StringBuilder* cndexpr);
#endif /* CTDB_FILTER_020617 */

#ifdef CTDB_PAD_RESOURCE
		virtual void GetPadChar([Out]TEXT __gc* Padchar, [Out]TEXT __gc* Dmlchar);
		virtual void SetPadChar(NINT padchar, NINT dmlchar);
		virtual void UpdatePadChar(NINT padchar, NINT dmlchar, bool rebuild);
#endif
		virtual bool HasDelField();
		virtual void SetIndexFilename(NINT IndexNumber, String* Path, String* Filename);
		virtual void SetIndexFilename(String* IndexName, String* Path, String* Filename);
		virtual String* GetIndexFilename(NINT IndexNumber);
		virtual String* GetIndexFilename(String* IndexName);
		virtual NINT GetDatno();
		virtual NINT GetIdxno(NINT index);
		virtual NINT GetIdxno(String* IndexName);
		virtual void Remove();
#ifdef CTDB_SYSTEM_FILTER
		virtual void SystemFilterOn(SYS_FILTER mode);
		virtual void SystemFilterOff(SYS_FILTER mode);
#endif /* CTDB_SYSTEM_FILTER */
#ifdef CTDB_DEFAULT_VALUE
		virtual void ClearAllFieldDefaultValue();
#endif /* CTDB_DEFAULT_VALUE */
		virtual void MoveSegment(CTIndex* hIndex, NINT segNumber, NINT newIndex);
		virtual void MoveSegment(NINT indexNumber, NINT segNumber, NINT newIndex);
		virtual void MoveSegment(String* indexName, NINT segNumber, NINT newIndex);
		virtual TABLE_STATUS GetStatus();
		virtual void Attach(NINT datno);
//		virtual void AttachXtd(NINT datno, NINT nbrfields, pDATOBJ dodaptr, pIFIL ifilptr);
		virtual void Detach();
		virtual String* GetOwner();
		virtual void SetOwner(String* owner);
		virtual void Rebuild(REBUILD_MODE mode);
		virtual ctdb::IFIL_STRUCT GetIFIL();
		virtual ctdb::IIDX_STRUCT GetIIDX(ctdb::IFIL_STRUCT ifil, int IndexNo);
		virtual ctdb::ISEG_STRUCT GetISEG(ctdb::IIDX_STRUCT iidx, int SegNo);
		virtual ctdb::DATOBJ_STRUCT GetDATOBJ(int FieldNo);
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTResource
*   CTDB C++ API resource class
*
\******************************************************************************/
public __gc class CTResource
{
	// members
	private:
		CTHANDLE m_resource;

    // Constructor & destructor
    public:
		CTResource(CTTable& Table);
		CTResource(CTTable& Table, ULONG type, ULONG number);
		CTResource(CTTable& Table, ULONG type, ULONG number, String* name);
//		virtual ~CTResource();
		void Dispose();
	
    // Methods
    public:
		virtual void Unlock();
		virtual void Add(Byte Data __gc[]);
		virtual void Delete();
		virtual void Update(Byte Data __gc[]);
		virtual bool First()
			{return First(false);}
		virtual bool First(bool Lock);
		virtual bool Next()
			{return Next(false);}
		virtual bool Next(bool Lock);
		virtual bool Find(ULONG Type, ULONG Number)
			{return Find(Type, Number, false);}
		virtual bool Find(ULONG Type, ULONG Number, bool Lock);
		virtual bool Find(String* Name)
			{return Find(Name, false);}
		virtual bool Find(String* Name, bool Lock);
		virtual bool IsLocked();
		virtual ULONG GetType();
		virtual void SetType(ULONG Type);
		virtual ULONG GetNumber();
		virtual void SetNumber(ULONG Number);
		virtual String* GetName();
		virtual void SetName(String* Name);
		virtual VRLEN GetDataLength();
		virtual Byte GetData()[];
		virtual void SetData(Byte Data __gc[]);
};
/*^****************************************************************************\
*
*   CTRecord
*   CTDN API record management class
*
\******************************************************************************/
public __gc class CTRecord : public CTBase
{
    // Constructors & destructor
    public:
        CTRecord( CTTable* Handle);
        CTRecord( CTRecord* Handle);
    //    virtual ~CTRecord();
		void Dispose();
        
    // Methods
    public:
        virtual bool First();
        virtual bool Next();
		virtual VRLEN GetFieldLength(NINT FieldNbr);
        virtual bool Last();
        virtual bool Prev();
        virtual bool Find(FIND_MODE FindMode);
        virtual void Clear();
        virtual void Read();
        virtual void Write();
        virtual void Delete();
        virtual void Reset();
		virtual void CopyBuffer(CTRecord* Source);
        virtual bool IsNew() ;
        virtual bool IsEdited() ;
        virtual void SetNew(bool flag);
        virtual void SetEdited(bool flag);
        virtual VRLEN GetRecordLength() ;
        virtual VRLEN GetRecordSize() ;
        virtual bool IsNullField(NINT FieldNumber);
        virtual void SetDefaultIndex(NINT Indexno);
        virtual void SetDefaultIndex(IDXNO Indexno);
        virtual void SetDefaultIndex(String* Name);
        virtual NINT GetDefaultIndex();
		virtual String* GetDefaultIndexName();

        virtual FIELD_TYPE GetFieldType(NINT FieldNumber);

		virtual unsigned __int64 GetRecordCount();
		virtual void RecordSetOn(NINT siglen);
		virtual bool IsRecordSetOn();
		virtual void RecordSetOff();
		virtual bool IsVariableField(NINT FieldNbr);
		virtual VRLEN GetFieldSize(NINT FieldNbr);
		virtual VRLEN GetFieldOffset(NINT FieldNbr);
        virtual void ClearField( NINT FieldNbr);
        virtual void LockRecord(LOCK_MODE mode);
        virtual void UnlockRecord();
		virtual LOCK_MODE GetRecordLock();

        virtual bool FindTarget(IntPtr Target, FIND_MODE FindMode);
        virtual bool FindTarget(Byte TargetKey __gc[], FIND_MODE FindMode);
		virtual void BuildTargetKey(FIND_MODE FindMode, IntPtr TargetKey, VRLEN __gc* TargetLen);
		virtual void BuildTargetKey(FIND_MODE FindMode, Byte TargetKey __gc[], VRLEN __gc* TargetLen);
		virtual __int64 GetRecordPos();
		virtual __int64 GetRecordPosAtPercentile(int Offset);
		virtual CTDBRET GetRecordPosAtOffset([Out]__int64 __gc* Offset);
		virtual void SetRecordPos(__int64 offset);
		virtual void SetRecordOffset(__int64 offset);
		virtual void SeekRecord(__int64 offset);    
        virtual String* GetFieldName(NINT FieldNumber);
        virtual NINT GetFieldByName(String* FieldName);
        virtual FIELD_TYPE GetFieldType(String* FieldName)
            {return GetFieldType(GetFieldByName(FieldName));}

        virtual bool IsNullField(String* FieldName)
            {return IsNullField(GetFieldByName(FieldName));}

		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]bool __gc* Value);				// Bool
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]bool __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTSIGNED __gc* Value);			// Int32
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTSIGNED __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTUNSIGNED __gc* Value);		// UInt32
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTUNSIGNED __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTBIGINT __gc* Value);			// Int64
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTBIGINT __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTUBIGINT __gc* Value);			// UInt64
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTUBIGINT __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]float __gc* Value);			// Float
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]float __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]double __gc* Value);			// Double
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]double __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]StringBuilder __gc* Value);	// String
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]StringBuilder __gc* Value)
            {return GetFieldValue(GetFieldByName(FieldName), Value);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]Byte Arr __gc[]);				// Bytes
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]Byte Arr __gc[])
            {return GetFieldValue(GetFieldByName(FieldName), Arr);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTBlob __gc* Blob);			// CTBlob
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTBlob __gc* Blob)
            {return GetFieldValue(GetFieldByName(FieldName), Blob);}
		virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTNumber __gc* Number);		// CTNumber
		virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTNumber __gc* Number)
            {return GetFieldValue(GetFieldByName(FieldName), Number);}
        virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTDate __gc* Date);			// CTDate
        virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTDate __gc* Date)
            {return GetFieldValue(GetFieldByName(FieldName), Date);}
        virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTTime __gc* Time);			// CTTime
        virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTTime __gc* Time)
            {return GetFieldValue(GetFieldByName(FieldName), Time);}
        virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTDateTime __gc* CtDateTime);	// CTDateTime
        virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTDateTime __gc* CtDateTime)
            {return GetFieldValue(GetFieldByName(FieldName), CtDateTime);}
        virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]DateTime __gc* DateTime);	// CTDateTime
        virtual CTDBRET GetFieldValue(String* FieldName, [Out]DateTime __gc* DateTime)
            {return GetFieldValue(GetFieldByName(FieldName), DateTime);}
        virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTMoney __gc* Money);			// CTMoney
        virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTMoney __gc* Money)
            {return GetFieldValue(GetFieldByName(FieldName), Money);}
        virtual CTDBRET GetFieldValue(NINT FieldNumber, [Out]CTCurrency __gc* Currency);	// CTCurrency
        virtual CTDBRET GetFieldValue(String* FieldName, [Out]CTCurrency __gc* Currency)
            {return GetFieldValue(GetFieldByName(FieldName), Currency);}
        virtual CTDBRET GetFieldValue(NINT FieldNumber, String* s);	// String
        virtual CTDBRET GetFieldValue(String* FieldName, String* s)
            {return GetFieldValue(GetFieldByName(FieldName), s);}

        virtual String* GetFieldAsString(NINT FieldNumber);
        virtual String* GetFieldAsString(String* FieldName)
            {return GetFieldAsString(GetFieldByName(FieldName));}


#ifdef oldGetSet
/// GetFieldAs 

        virtual bool GetFieldAsBool(NINT FieldNumber);
        virtual void GetFieldAsBlob(NINT FieldNumber, CTBlob __gc* Retval);
        virtual CTSIGNED GetFieldAsSigned(NINT FieldNumber);
        virtual CTUNSIGNED GetFieldAsUnsigned(NINT FieldNumber);

        virtual CTDate* GetFieldAsDate(NINT FieldNumber);
        virtual double GetFieldAsFloat(NINT FieldNumber);
        virtual CTTime* GetFieldAsTime(NINT FieldNumber);
        virtual CTDateTime* GetFieldAsDateTime(NINT FieldNumber);
        virtual CTMoney* GetFieldAsMoney(NINT FieldNumber);

        virtual TEXT GetFieldAsChar(NINT FieldNumber)
            {return (TEXT)GetFieldAsSigned(FieldNumber);}

        virtual UTEXT GetFieldAsByte(NINT FieldNumber)
            {return (UTEXT)GetFieldAsUnsigned(FieldNumber);}
            
        virtual COUNT GetFieldAsShort(NINT FieldNumber)
            {return (COUNT)GetFieldAsSigned(FieldNumber);}
            
        virtual UCOUNT GetFieldAsWord(NINT FieldNumber)
            {return (UCOUNT)GetFieldAsUnsigned(FieldNumber);}        

        virtual void GetFieldAsBlob(String* FieldName, CTBlob __gc* Retval)
            {return GetFieldAsBlob(GetFieldByName(FieldName), Retval);}

		virtual bool GetFieldAsBool(String* FieldName)
            {return GetFieldAsBool(GetFieldByName(FieldName));}

        virtual TEXT GetFieldAsChar(String* FieldName)
            {return GetFieldAsChar(GetFieldByName(FieldName));}
            
        virtual UTEXT GetFieldAsByte(String* FieldName)
            {return GetFieldAsByte(GetFieldByName(FieldName));}
            
        virtual COUNT GetFieldAsShort(String* FieldName)
            {return GetFieldAsShort(GetFieldByName(FieldName));}
            
        virtual UCOUNT GetFieldAsWord(String* FieldName)
            {return GetFieldAsWord(GetFieldByName(FieldName));}
        
        virtual CTSIGNED GetFieldAsSigned(String* FieldName)
            {return GetFieldAsSigned(GetFieldByName(FieldName));}
            
        virtual CTUNSIGNED GetFieldAsUnsigned(String* FieldName)
            {return GetFieldAsUnsigned(GetFieldByName(FieldName));}
            
        virtual CTDate* GetFieldAsDate(String* FieldName)
            {return GetFieldAsDate(GetFieldByName(FieldName));}
           
        virtual CTTime* GetFieldAsTime(String* FieldName)
            {return GetFieldAsTime(GetFieldByName(FieldName));}
            
        virtual CTDateTime* GetFieldAsDateTime(String* FieldName)
            {return GetFieldAsDateTime(GetFieldByName(FieldName));}
            
        virtual CTMoney* GetFieldAsMoney(String* FieldName)
            {return GetFieldAsMoney(GetFieldByName(FieldName));}
           
        virtual double GetFieldAsFloat(String* FieldName)
            {return GetFieldAsFloat(GetFieldByName(FieldName));}
            
		virtual CTBigint* GetFieldAsBigint(NINT FieldNumber);
		virtual CTBigint* GetFieldAsUnsignedBigint(NINT FieldNumber);

		virtual CTCurrency* GetFieldAsCurrency(NINT FieldNumber);
		virtual CTNumber* GetFieldAsNumber(NINT FieldNumber);		

		virtual CTBigint* GetFieldAsBigint(String* FieldName)
			{return GetFieldAsBigint(GetFieldByName(FieldName));}
		virtual CTBigint* GetFieldAsUnsignedBigint(String* FieldName)
			{return GetFieldAsUnsignedBigint(GetFieldByName(FieldName));}

		virtual CTCurrency* GetFieldAsCurrency(String* FieldName)
			{return GetFieldAsCurrency(GetFieldByName(FieldName));}

		virtual CTNumber* GetFieldAsNumber(String* FieldName)
			{return GetFieldAsNumber(GetFieldByName(FieldName));}

		virtual Byte GetFieldAsBytes(String* FieldName)[]
			{return GetFieldAsBytes(GetFieldByName(FieldName));}
  
		virtual Byte GetFieldAsBytes(NINT FieldNumber)[];


/// End GetFieldAs
#endif oldGetSet
        virtual void SetFieldValue(NINT FieldNumber, bool value);						// Bool
		virtual void SetFieldValue(String* FieldName, bool value)
            {SetFieldValue(GetFieldByName(FieldName), value);}
        virtual void SetFieldValue(NINT FieldNumber, CTSIGNED value);					// Int32
        virtual void SetFieldValue(String* FieldName, CTSIGNED value)
            {SetFieldValue(GetFieldByName(FieldName), value);}
        virtual void SetFieldValue(NINT FieldNumber, CTUNSIGNED value);					// Uint32
		virtual void SetFieldValue(String* FieldName, CTUNSIGNED value)
            {SetFieldValue(GetFieldByName(FieldName), value);}
		virtual void SetFieldValue(NINT FieldNumber, CTBIGINT value);					// Int64
		virtual void SetFieldValue(String* FieldName, CTBIGINT value)
			{SetFieldValue(GetFieldByName(FieldName), value);}
        virtual void SetFieldValue(NINT FieldNumber, CTFLOAT value);					// Float 
		virtual void SetFieldValue(String* FieldName, CTFLOAT value)
            {SetFieldValue(GetFieldByName(FieldName), value);}
		virtual void SetFieldValue(NINT FieldNumber,String* value);						// String
        virtual void SetFieldValue(String* FieldName, String* value)
            {SetFieldValue(GetFieldByName(FieldName), value);}
		virtual void SetFieldValue(NINT FieldNumber, Byte Arr __gc[]);					// Bytes
		virtual void SetFieldValue(String* FieldName, Byte Arr __gc[])
			{SetFieldValue(GetFieldByName(FieldName), Arr);}
        virtual void SetFieldValue(NINT FieldNumber, CTBlob __gc* Blob);				// CTBlob  
		virtual void SetFieldValue(String* FieldName, CTBlob __gc* Blob)
            {SetFieldValue(GetFieldByName(FieldName), Blob);}
		virtual void SetFieldValue(NINT FieldNumber, CTNumber* Number);					// CTNumber
		virtual void SetFieldValue(String* FieldName, CTNumber* Number)
			{SetFieldValue(GetFieldByName(FieldName), Number);}
        virtual void SetFieldValue(NINT FieldNumber, CTDate* Date);						// CTDate
        virtual void SetFieldValue(String* FieldName, CTDate* Date)
            {SetFieldValue(GetFieldByName(FieldName), Date);}
        virtual void SetFieldValue(NINT FieldNumber, CTTime* Time);						// CTTime    
		virtual void SetFieldValue(String* FieldName, CTTime* Time)
            {SetFieldValue(GetFieldByName(FieldName), Time);}
        virtual void SetFieldValue(NINT FieldNumber, CTDateTime* CtDateTime);			// CTDateTime
		virtual void SetFieldValue(String* FieldName, CTDateTime* CtDateTime)
            {SetFieldValue(GetFieldByName(FieldName), CtDateTime);}
        virtual void SetFieldValue(NINT FieldNumber, [In]DateTime DateTime);				// CTDateTime
		virtual void SetFieldValue(String* FieldName, [In]DateTime DateTime)
            {SetFieldValue(GetFieldByName(FieldName), DateTime);}
        virtual void SetFieldValue(NINT FieldNumber, CTMoney* Money);					// CTMoney
        virtual void SetFieldValue(String* FieldName, CTMoney* Money)
            {SetFieldValue(GetFieldByName(FieldName), Money);}
		virtual void SetFieldValue(NINT FieldNumber, CTCurrency* Currency);				// CTCurrency
		virtual void SetFieldValue(String* FieldName, CTCurrency* Currency)
			{SetFieldValue(GetFieldByName(FieldName), Currency);}

        virtual void SetFieldAsString(NINT FieldNumber,String* value);  
		virtual void SetFieldAsString(String* FieldName, String* value)
            {SetFieldAsString(GetFieldByName(FieldName), value);}

#ifdef oldGetSet
/// SetFieldAs

		virtual void SetFieldAsBigint(String* FieldName, CTBigint* value)
			{SetFieldAsBigint(GetFieldByName(FieldName), value);}

		virtual void SetFieldAsUnsignedBigint(String* FieldName, CTBigint* value)
			{SetFieldAsUnsignedBigint(GetFieldByName(FieldName), value);}

		virtual void SetFieldAsCurrency(String* FieldName, CTCurrency* value)
			{SetFieldAsCurrency(GetFieldByName(FieldName), value);}

		virtual void SetFieldAsNumber(String* FieldName, CTNumber* value)
			{SetFieldAsNumber(GetFieldByName(FieldName), value);}
  
		virtual void SetFieldAsBytes(String* FieldName, Byte arr __gc[])
			{SetFieldAsBytes(GetFieldByName(FieldName), arr);}
  
		virtual void SetFieldAsBytes(NINT FieldNumber, Byte arr __gc[]);

        virtual void SetFieldAsBool(NINT FieldNumber, bool value);      
        virtual void SetFieldAsBlob(NINT FieldNumber, CTBlob __gc* value);      
        virtual void SetFieldAsSigned(NINT FieldNumber, CTSIGNED value);      
        virtual void SetFieldAsUnsigned(NINT FieldNumber, CTUNSIGNED value);      
        virtual void SetFieldAsFloat(NINT FieldNumber, CTFLOAT value);      

        virtual void SetFieldAsChar(NINT FieldNumber, TEXT value)
            {SetFieldAsSigned(FieldNumber, (CTSIGNED)value);}
            
        virtual void SetFieldAsByte(NINT FieldNumber, UTEXT value)
            {SetFieldAsUnsigned(FieldNumber, (CTUNSIGNED)value);}
            
        virtual void SetFieldAsShort(NINT FieldNumber, COUNT value)
            {SetFieldAsSigned(FieldNumber, (CTSIGNED)value);}
            
        virtual void SetFieldAsWord(NINT FieldNumber, UCOUNT value)
            {SetFieldAsUnsigned(FieldNumber, (CTUNSIGNED)value);}

		virtual void SetFieldAsBlob(String* FieldName, CTBlob __gc* value)
            {SetFieldAsBlob(GetFieldByName(FieldName), value);}

		virtual void SetFieldAsBool(String* FieldName, bool value)
            {SetFieldAsBool(GetFieldByName(FieldName), value);}

        virtual void SetFieldAsChar(String* FieldName, TEXT value)
            {SetFieldAsSigned(GetFieldByName(FieldName), (CTSIGNED)value);}
            
        virtual void SetFieldAsByte(String* FieldName, UTEXT value)
            {SetFieldAsUnsigned(GetFieldByName(FieldName), (CTUNSIGNED)value);}
            
        virtual void SetFieldAsShort(String* FieldName, COUNT value)
            {SetFieldAsSigned(GetFieldByName(FieldName), (CTSIGNED)value);}
            
        virtual void SetFieldAsWord(String* FieldName, UCOUNT value)
            {SetFieldAsUnsigned(GetFieldByName(FieldName), (CTUNSIGNED)value);}
                
        virtual void SetFieldAsSigned(String* FieldName, CTSIGNED value)
            {SetFieldAsSigned(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsUnsigned(String* FieldName, CTUNSIGNED value)
            {SetFieldAsUnsigned(GetFieldByName(FieldName), value);}

		virtual void SetFieldAsFloat(String* FieldName, CTFLOAT value)
            {SetFieldAsFloat(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsDate(NINT FieldNumber, CTDate* value);      
        virtual void SetFieldAsTime(NINT FieldNumber, CTTime* value);      
        virtual void SetFieldAsDateTime(NINT FieldNumber, CTDateTime* value);      
        virtual void SetFieldAsMoney(NINT FieldNumber, CTMoney* value);      
		virtual void SetFieldAsBigint(NINT FieldNumber, CTBigint* value);
		virtual void SetFieldAsUnsignedBigint(NINT FieldNumber, CTBigint* value);
		virtual void SetFieldAsCurrency(NINT FieldNumber, CTCurrency* value);
		virtual void SetFieldAsNumber(NINT FieldNumber, CTNumber* value);
        virtual void SetFieldAsDate(String* FieldName, CTDate* value)
            {SetFieldAsDate(GetFieldByName(FieldName), value);}

		virtual void SetFieldAsTime(String* FieldName, CTTime* value)
            {SetFieldAsTime(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsDateTime(String* FieldName, CTDateTime* value)
            {SetFieldAsDateTime(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsMoney(String* FieldName, CTMoney* value)
            {SetFieldAsMoney(GetFieldByName(FieldName), value);}


/// End SetFieldAs
#endif oldGetSet

		virtual bool IsVariableField(String* FieldName)
			{return IsVariableField(GetFieldByName(FieldName));}

		virtual VRLEN GetFieldLength(String* FieldName)
			{return GetFieldLength(GetFieldByName(FieldName));}
		
		virtual VRLEN GetFieldSize(String* FieldName)
			{return GetFieldSize(GetFieldByName(FieldName));}
		
		virtual VRLEN GetFieldOffset(String* FieldName)
			{return GetFieldOffset(GetFieldByName(FieldName));}

        virtual void ClearField(String* FieldName)
        	{ClearField(GetFieldByName(FieldName));}

        virtual __int64 GetRowid();
        virtual bool FindRowid(__int64 rowid, FIND_MODE FindMode);

        virtual pVOID GetRecordBuffer();
		virtual void AtPercentile(NINT percent);
		virtual LONG EstimateSpan(Byte Key1 __gc[], Byte Key2 __gc[]);
	   	virtual LONG NumberOfKeyEntries(NINT index);
		virtual LONG NumberOfKeyEntries(String* indexName);
		        
#ifdef CTDB_CNDX_IDX 
		virtual bool CndxEval();
		virtual void CndxFree();
		virtual void CndxCompile(String* expression);
		virtual void CndxGetExpression(StringBuilder* expression);
		virtual bool CTRecord::Compare(CTRecord *record);
#endif /* CTDB_CNDX_IDX  */

		virtual void RangeOn(NINT SegCount, Byte lRange __gc[], Byte uRange __gc[], RANGE_OP operators __gc[]);
		virtual void RangeOff();
		virtual bool IsRangeOn();
		virtual void SwitchContext();
#ifdef ctdbRECORD_FILTER
		virtual void SetFilter(String* cndexpr);
		virtual CTBOOL IsFiltered();
		virtual void GetFilter(StringBuilder* cndexpr);
#endif /* CTDB_FILTER_020617 */
		virtual LONG BatchLoaded();
		virtual LONG BatchLocked();
		virtual LONG BatchTotal();
		virtual BATCH_MODE BatchMode();
		virtual CTBOOL IsBatchActive();
		virtual void EndBatch();
		virtual void InsertBatch();
		virtual void NextBatch();
		virtual void SetBatch(BATCH_MODE mode)
			{SetBatch(mode, 0, 0);};
		virtual void SetBatch(BATCH_MODE mode, VRLEN targetLen, VRLEN bufferLen);
		virtual int GetErrorIndex();
		virtual bool JumpTo(LONG offset);
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTField
*   CTDN API field class
*
\******************************************************************************/
public __gc class CTField : public CTBase
{
    // Constructors & destructor
    public:
        CTField();
        CTField(CTField& pField);
        virtual ~CTField();
           
    // Operators
    public:
		static CTField* op_Implicit(CTField* Field)
		{return new CTField(*Field);}
    	 
    // Methods
    public:
        virtual VRLEN GetLength() ;
		virtual bool GetNullFlag() ;
		virtual NINT GetPrecision() ;
		virtual NINT GetScale() ;
        virtual void SetType(FIELD_TYPE Type, VRLEN Length);
        virtual void SetLength( VRLEN Length);
		virtual NINT GetNumber();
		virtual void SetNullFlag(bool flag);
		virtual void SetPrecision(NINT precision);
		virtual void SetScale(NINT scale);
		virtual bool IsNumeric() ;
        virtual String* GetName();
        virtual FIELD_TYPE GetCTType();
        virtual void SetName(String* FieldName);
#ifdef CTDB_DEFAULT_VALUE
		virtual void SetFieldDefaultValue(String* Value);
		virtual VRLEN GetFieldDefaultValue(StringBuilder* Value);
		virtual void ClearFieldDefaultValue();
		virtual void SetFieldDefaultDateTimeType();
		virtual void SetFieldDefaultDateTimeType(DATE_TYPE DateType, TIME_TYPE TimeType);
		virtual CTBOOL IsFieldDefaultValueSet();
		virtual DATE_TYPE GetFieldDefaultDateType();
		virtual TIME_TYPE GetFieldDefaultTimeType();
#endif /* CTDB_DEFAULT_VALUE */
		virtual FIELD_STATUS GetStatus();

};
/*^****************************************************************************\
*
*   CTIndex
*   CTDN  API index class
*
\******************************************************************************/
public __gc class CTIndex : public CTBase
{
    // Constructors & destructor
    public:
        CTIndex();
        CTIndex( CTIndex& pIndex);
        virtual ~CTIndex();
    // Operators
    public:
		static CTIndex* op_Implicit(CTIndex* Index)
		{return new CTIndex(*Index);}
    // Methods
    public:
        virtual NINT GetKeyLength() ;
        virtual KEY_TYPE GetKeyType() ;
        virtual NINT GetEmptyChar() ;
        virtual bool GetDuplicateFlag() ;
        virtual bool GetNullFlag() ;
        virtual NINT GetSegmentCount() ;
        virtual void DelSegment(NINT SegmentNumber);
        virtual bool GetTemporaryFlag() ;
        virtual void SetEmptyChar(NINT EmptyChar);
        virtual void SetDuplicateFlag(bool DupFlag);
        virtual void SetNullFlag(bool NullFlag);
        virtual void SetTemporaryFlag(bool TempFlag);
		virtual NINT GetNumber();
		virtual ULONG GetUID();
        virtual CTSegment* GetSegment(NINT SegmentNumber);
		virtual String* GetName();
        virtual CTSegment* AddSegment(CTField* pField, SEG_MODE SegMode);
		virtual CTSegment* AddSegment(NINT offset, NINT length, SEG_MODE SegMode);
        virtual CTSegment* InsertSegment(NINT BeforeSegment, CTField* Field, SEG_MODE SegMode);
        virtual CTSegment* InsertSegment(NINT BeforeSegment, NINT offset, NINT length, SEG_MODE SegMode);
		virtual void SetName(String* IndexName);
		virtual void SetKeyType(KEY_TYPE keytype);
		virtual void SetFilename(String* Path, String* Name);
		virtual String* GetFilename();
		virtual NINT GetIdxno();
		virtual INDEX_STATUS GetStatus();
		virtual void MoveSegment(NINT segmentNumber, NINT newIndex);
};
/*^****************************************************************************\
*
*   CTSegment
*   CTDN  API segment class
*
\******************************************************************************/
public __gc class CTSegment : public CTBase
{
    // Constructors & destructor
    public:
        CTSegment();
        CTSegment( CTSegment& pSeg);
        virtual ~CTSegment();
    // Operators
    public:
		static CTSegment* op_Implicit(CTSegment* Segment)
		{return new CTSegment(*Segment);}
    // Methods:
    public:
        virtual SEG_MODE GetMode() ;
        virtual void SetMode(SEG_MODE SegMode);
		virtual NINT GetNumber();
        virtual CTField* GetField();
        virtual CTField* GetPartialField();
        virtual String* GetFieldName();
        virtual String* GetPartialFieldName();
		virtual SEGMENT_STATUS GetStatus();
		virtual void MoveSegment(NINT newIndex);
		virtual void SetField(CTField* Field);
};
/*~****************************************************************************/


/*^****************************************************************************\
*
*   CTHelloWorld
*   CTDN  API Hello World class 	CTDB HELLO WORLD 
*
\******************************************************************************/
public __gc class CTHelloWorld : public CTBase 
{
    // Constructors & destructor
    public:
		CTHelloWorld();
		void Dispose();
        
    // Methods
    public:
	virtual void CTHelloWorld::HelloWorld(String* HelloFileName,String* HelloTextData,
		NINT HelloNintData, ULONG HelloULongData, CTFLOAT HelloFloatData); /* CTDB HELLO WORLD */

	// Members
	private:
		VRLEN	m_hiworld;
};
/*~****************************************************************************/



#endif /* __cplusplus */
//#endif /* ~_CTDNSDK_HPP */
#ifdef ctPortDotNET
	}
}
using namespace FairCom::CtreeDb;
#endif ctPortDotNET
