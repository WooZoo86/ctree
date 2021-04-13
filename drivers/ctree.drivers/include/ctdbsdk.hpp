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

#ifndef _CTDBSDK_HPP_
#define _CTDBSDK_HPP_
/*^****************************************************************************\
*
*   Header Files
*
\******************************************************************************/
#include "ctdbsdk.h"
/*^****************************************************************************\
*
*	CTDB DLL export macros
*
\******************************************************************************/
#ifdef ctdbEXPORT
#undef ctdbEXPORT
#endif

#ifdef ctPortWIN32
#if (defined(ctDLLLIB) || defined(ctFeatSRVDLL))
#ifdef ctdbDLLEXP
#define ctdbEXPORT	__declspec(dllexport)
#else	/* ctdbDLLEXP */
#define ctdbEXPORT	__declspec(dllimport)
#endif	/* ctdbDLLEXP */
#endif	/* ctDLLLIB  or ctFeatSRVDLL */
#endif	/* ctPortWIN32 */

#ifndef ctdbEXPORT
#define ctdbEXPORT
#endif
/*^****************************************************************************\
*
*   use header only for C++ compilers
*
\******************************************************************************/
#ifdef __cplusplus
/*^****************************************************************************\
*
*   CTDB C++ API version
*
*   Bits  0-15   Build number
*   Bits 16-23   Version number
*   Bits 24-31   Release number
*
\******************************************************************************/
#define CTDB_CPP_BUILD_NBR      0x00000001
#define CTDB_CPP_VERSION_NBR    0x00010000
#define CTDB_CPP_RELEASE_NBR    0x00000000
#define CTDB_CPP_VERSION        (CTDB_CPP_RELEASE_NBR | CTDB_CPP_VERSION_NBR | CTDB_CPP_BUILD_NBR)
/*^****************************************************************************\
*
*   CTException
*   Base exception class for CTDB C++ API
*
\******************************************************************************/
class ctdbEXPORT CTException
{
    // Constructors & destructor
    public:
        CTException(NINT ErrorCode);
        CTException(NINT ErrorCode, cpTEXT ErrorMsg);
        CTException(NINT ErrorCode, cpTEXT SourceFile, NINT LineNbr);
        CTException(NINT ErrorCode, cpTEXT ErrorMsg, cpTEXT SourceFile, NINT LineNbr);
        virtual ~CTException();
       
    // Methods
    public:
        virtual NINT GetErrorCode() const;
        virtual cpTEXT GetErrorMsg() const;
        virtual cpTEXT GetSourceFile() const;
        virtual NINT GetLineNbr() const;
                
   // Members
   private:
        NINT    m_error;
        cpTEXT  m_msg;
        cpTEXT  m_file;
        NINT    m_line;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTString
*   CTDB C++ API string class
*
\******************************************************************************/
class ctdbEXPORT CTString
{
    // Constructors & destructor
    public:
        CTString();
        CTString(cpTEXT ptr);
        CTString(cpTEXT ptr, VRLEN size);
        CTString(const CTString& str);
        CTString(const NINT value);
        CTString(const double value);
#ifdef ctdbUNICODE
		CTString(pWCHAR value);
#endif
        virtual ~CTString();

    // Operators
    public:
        CTString& operator=(const CTString& str);
        CTString& operator=(cpTEXT str);
#ifdef ctdbUNICODE
		CTString& operator=(pWCHAR str);
#endif
        CTString& operator+=(const CTString& str);
        char& operator[](const NINT index);
        friend ctdbEXPORT CTString operator+(const CTString& lhs, const CTString& rhs);
        friend ctdbEXPORT CTString operator+(const CTString& lhs, cpTEXT rhs);
        friend ctdbEXPORT CTString operator+(cpTEXT lhs, const CTString& rhs);
        CTBOOL operator<(const CTString& str);
        CTBOOL operator<=(const CTString& str);
        CTBOOL operator>(const CTString& str);
        CTBOOL operator>=(const CTString& str);
        CTBOOL operator==(const CTString& str);
        CTBOOL operator!=(const CTString& str);
        
    // Methods
    public:
        pTEXT c_str() const;
        NINT Compare(const CTString& str) const;
        NINT CompareIC(const CTString& str) const;
        void Delete(const NINT index, const NINT count);
        void Empty();
        void Insert(const CTString& substr, const NINT index);
        static CTString IntToHex(const NINT value, const NINT digits);
        CTBOOL IsDelimiter(const CTString& str, const NINT index) const;
        CTBOOL IsEmpty() const;
        CTBOOL IsPathDelimiter(const NINT index); 
        pTEXT LastChar() const;
        NINT LastDelimiter(const CTString& delimiters) const;
        CTString Left(const NINT count);
        NINT Length() const;
        void LowerCase();
        void PadLeft(const NINT newlength, const char padChar = ' ');
        void PadRight(const NINT newlength, const char padChar = ' ');
        NINT Pos(const CTString& substr) const;
        CTString Right(const NINT count);
        void SetLength(const NINT newLength);
        static CTString StringOfChar(const char ch, const NINT count = 1);
        CTString SubString(const NINT index, const NINT count) const;
        NINT ToInt() const;
        double ToDouble() const;
        void Trim();
        void TrimLeft();
        void TrimRight();
        void UpperCase();
#ifdef ctdbUNICODE
		void AsUTF16(pWCHAR buffer, NINT size);
#endif

    protected:
        void Alloc(const NINT len);
        void Free();
        void Copy(cpTEXT str);
        void Copy(const CTString& str);
        void Copy(const NINT value);
        void Copy(const double value);
#ifdef ctdbUNICODE
		void Copy(pWCHAR str);
#endif
                
    // Members
    private:
        pTEXT   m_text;    
};
/*~****************************************************************************/


/*^****************************************************************************\
*
*   CTJsonString
*   CTDB C++ API CTJsonString
*
\******************************************************************************/
class ctdbEXPORT CTJsonString
{
	// Constructors & destructor
public:
	CTJsonString();
	CTJsonString(cpTEXT ptr);
	CTJsonString(cpTEXT ptr, VRLEN size);
	CTJsonString(const CTJsonString& str);
#ifdef ctdbUNICODE
	CTJsonString(pWCHAR ptr);
#endif
	virtual ~CTJsonString();

	// Operators
public:
	CTJsonString & operator=(const CTJsonString& str);
	CTJsonString & operator=(cpTEXT str);
	CTJsonString & operator=(const CTString& str);
#ifdef ctdbUNICODE
	CTJsonString & operator=(pWCHAR str);
#endif

	// Methods
public:
	pTEXT c_str() const;
	CTString *ToCTString() const;

private:
	CTString   *m_jsonstring;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTDate
*   CTDB C++ API date class
*
\******************************************************************************/
class ctdbEXPORT CTDate
{
    // Methods
    public:
        CTDATE GetDate() const
            {return m_date;}
            
        void SetDate(CTDATE Date)
            {m_date = Date;}
            
        void SetDate(const CTDate& Date)
            {m_date = Date.m_date;}
            
    // Constructor & destructor
    public:
        CTDate()
            {m_date = 0;}
            
        CTDate(NINT year, NINT month, NINT day)
            {Pack(year, month, day);}
            
        CTDate(CTDATE Date)
            {SetDate(Date);}
            
        CTDate(const CTDate& Date)
            {SetDate(Date);}
            
        virtual ~CTDate();
        
    // Operators
    public:
        CTDate& operator=(const CTDate& Date)
            {SetDate(Date); return *this;}
            
        CTDate& operator=(const CTDATE Date)
            {SetDate(Date); return *this;}
        
        CTBOOL operator<(const CTDate& Date) const
            {return (m_date < Date.m_date) ? YES : NO;}
            
        CTBOOL operator<=(const CTDate& Date) const
            {return (m_date <= Date.m_date) ? YES : NO;}
            
        CTBOOL operator>(const CTDate& Date) const
            {return (m_date > Date.m_date) ? YES : NO;}
            
        CTBOOL operator>=(const CTDate& Date) const
            {return (m_date >= Date.m_date) ? YES : NO;}
            
        CTBOOL operator==(const CTDate& Date) const
            {return (m_date == Date.m_date) ? YES : NO;}
            
        CTBOOL operator!=(const CTDate& Date) const
            {return (m_date != Date.m_date) ? YES : NO;}
            
    // Methods
    public:
        void Pack(NINT year, NINT month, NINT day);
        void Unpack(NINT& year, NINT& month, NINT& day) const;
        NINT Year() const;
        NINT Month() const;
        NINT Day() const;
        NINT DayOfWeek() const;
        CTBOOL IsLeapYear() const;
        CTString DateToString(CTDATE_TYPE DateType) const;
        void StringToDate(const CTString& str, CTDATE_TYPE DateType);
        static CTDate CurrentDate();
        
    // Members
    private:
        CTDATE  m_date;    
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTTime
*   CTDB C++ API Time class
*
\******************************************************************************/
class ctdbEXPORT CTTime
{
    // Constructors & destructor
    public:
        CTTime()
            {m_time = 0;}
            
        CTTime(NINT hour, NINT minute, NINT second)
            {Pack(hour, minute, second);}
            
        CTTime(CTTIME Time)
            {m_time = Time;}
            
        CTTime(const CTTime& Time)
            {m_time = Time.m_time;}
            
        virtual ~CTTime();

    // Operators
    public:
        CTTime& operator=(CTTIME Time)
            {m_time = Time; return *this;}
            
        CTTime& operator=(const CTTime& Time)
            {m_time = Time.m_time; return *this;}

        CTBOOL operator<(const CTTime& Time) const
            {return (m_time < Time.m_time) ? YES : NO;}
            
        CTBOOL operator<=(const CTTime& Time) const
            {return (m_time <= Time.m_time) ? YES : NO;}
            
        CTBOOL operator>(const CTTime& Time) const
            {return (m_time > Time.m_time) ? YES : NO;}
            
        CTBOOL operator>=(const CTTime& Time) const
            {return (m_time >= Time.m_time) ? YES : NO;}
            
        CTBOOL operator==(const CTTime& Time) const
            {return (m_time == Time.m_time) ? YES : NO;}
            
        CTBOOL operator!=(const CTTime& Time) const
            {return (m_time != Time.m_time) ? YES : NO;}
        
    // Methods
    public:
        CTTIME GetTime() const
            {return m_time;}
            
        void SetTime(CTTIME Time)
            {m_time = Time;}
            
        void SetTime(const CTTime& Time)
            {m_time = Time.m_time;}
            
        void Pack(NINT hour, NINT minute, NINT second);
        void Unpack(NINT& hour, NINT& minute, NINT& second) const;
        NINT Hour() const;
        NINT Minute() const;
        NINT Second() const;
        CTString TimeToString(CTTIME_TYPE TimeType) const;
        void StringToTime(const CTString& str, CTTIME_TYPE TimeType);
        static CTTime CurrentTime();
        
    // Members
    private:
        CTTIME  m_time;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTDateTime
*   CTDB C++ API Date Time class
*
\******************************************************************************/
class ctdbEXPORT CTDateTime
{
    // Constructors & destructors
    public:
        CTDateTime()
            {m_datetime = 0.0;}
            
        CTDateTime(NINT year, NINT month, NINT day, NINT hour = 0, NINT minute = 0, NINT second = 0)
            {Pack(year, month, day, hour, minute, second);}
            
        CTDateTime(CTDATE Date, CTTIME Time = 0)
            {SetDateTime(Date, Time);}
            
        CTDateTime(const CTDate& Date, const CTTime& Time = 0)
            {SetDateTime(Date, Time);}
            
        CTDateTime(CTDATETIME DateTime)
            {SetDateTime(DateTime);}
            
        CTDateTime(const CTDateTime& DateTime)
            {SetDateTime(DateTime);}
            
        virtual ~CTDateTime();
        
    // Operators
    public:
        CTDateTime& operator=(CTDATETIME DateTime)
            {SetDateTime(DateTime); return *this;}
            
        CTDateTime& operator=(const CTDateTime& DateTime)
            {SetDateTime(DateTime); return *this;}
            
        CTBOOL operator<(const CTDateTime& DateTime) const
            {return (m_datetime < DateTime.m_datetime) ? YES : NO;}
            
        CTBOOL operator<=(const CTDateTime& DateTime) const
            {return (m_datetime <= DateTime.m_datetime) ? YES : NO;}
            
        CTBOOL operator>(const CTDateTime& DateTime) const
            {return (m_datetime > DateTime.m_datetime) ? YES : NO;}
            
        CTBOOL operator>=(const CTDateTime& DateTime) const
            {return (m_datetime >= DateTime.m_datetime) ? YES : NO;}
            
        CTBOOL operator==(const CTDateTime& DateTime) const
            {return (m_datetime == DateTime.m_datetime) ? YES : NO;}
            
        CTBOOL operator!=(const CTDateTime& DateTime) const
            {return (m_datetime != DateTime.m_datetime) ? YES : NO;}
            
    // Methods
    public:
        CTDATETIME GetDateTime() const
            {return m_datetime;}
            
        void SetDateTime(CTDATETIME DateTime)
            {m_datetime = DateTime;}
            
        void SetDateTime(const CTDateTime& DateTime)
            {m_datetime = DateTime.m_datetime;}
            
        void SetDateTime(CTDATE Date, CTTIME Time = 0);
        void SetDateTime(const CTDate& Date, const CTTime& Time = 0);
        void Pack(NINT year, NINT month, NINT day, NINT hour = 0, NINT minute = 0, NINT second = 0);
        void Unpack(NINT& year, NINT& month, NINT& day, NINT& hour, NINT& minute, NINT& second) const;
        CTDate GetDate() const;
        CTTime GetTime() const;
        NINT Year() const;
        NINT Month() const;
        NINT Day() const;
        NINT DayOfWeek() const;
        CTBOOL IsLeapYear() const;
        NINT Hour() const;
        NINT Minute() const;
        NINT Second() const;
        CTString DateTimeToString(CTDATE_TYPE DateType, CTTIME_TYPE TimeType) const;
        void StringToDateTime(const CTString& str, CTDATE_TYPE DateType, CTTIME_TYPE TimeType);
        static CTDateTime CurrentDateTime();
        static CTDateTime CurrentDate();
        
    // Members
    private:
        CTDATETIME  m_datetime;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTMoney
*   CTDB C++ API Money class
*
\******************************************************************************/
class ctdbEXPORT CTMoney
{
    // Constructors & destructor
    public:
        CTMoney()
            {m_money = 0;}
           
        CTMoney(CTFLOAT value)
            {SetMoney(value);}
            
        CTMoney(CTMONEY money)
            {SetMoney(money);}
            
        CTMoney(const CTString& str)
            {SetMoney(str);}
            
        CTMoney(const CTMoney& money)
            {SetMoney(money);}
            
        virtual ~CTMoney();
        
        
    // Operators
    public:
        CTMoney& operator=(CTFLOAT value)
            {SetMoney(value); return *this;}
            
        CTMoney& operator=(CTMONEY value)
            {SetMoney(value); return *this;}
            
        CTMoney& operator=(const CTString& str)
            {SetMoney(str); return *this;}
            
        CTMoney& operator=(const CTMoney& money)
            {SetMoney(money); return *this;}
            
        CTMoney& operator+=(const CTMoney& money)
            {*this = *this + money; return *this;}
            
        CTMoney& operator-=(const CTMoney& money)
            {*this = *this - money; return *this;}

        CTMoney& operator*=(const CTMoney& money)
            {*this = *this * money; return *this;}

        CTMoney& operator/=(const CTMoney& money)
            {*this = *this / money; return *this;}

        friend ctdbEXPORT CTMoney abs(const CTMoney& money);
        friend ctdbEXPORT CTMoney operator+(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTMoney operator-(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTMoney operator*(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTMoney operator/(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTBOOL operator<(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTBOOL operator<=(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTBOOL operator>(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTBOOL operator>=(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTBOOL operator==(const CTMoney& left, const CTMoney& right);
        friend ctdbEXPORT CTBOOL operator!=(const CTMoney& left, const CTMoney& right);

    // Methods
    public:
        void SetInt(int value);
        void SetMoney(CTFLOAT value);
        void SetMoney(CTMONEY money);
        void SetMoney(const CTString& str);
        void SetMoney(const CTMoney& money);
		LONG AsLong() const;
		int AsInt() const;
        CTFLOAT AsFloat() const;
        CTMONEY AsMoney() const;
        CTString AsString() const;
        void StringToMoney(const CTString& str);
    // Members
    private:
        CTMONEY m_money;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTBigint
*   CTDB C++ API big integer (64 bit integer) class
*	
*
\******************************************************************************/
class ctdbEXPORT CTBigint
{
	// constructors
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
		CTBigint(const CTMoney& value)
			{SetBigint(value);}
		CTBigint(const CTString& value)
			{SetBigint(value);}
		CTBigint(const CTBigint& value)
			{SetBigint(value);}
		virtual ~CTBigint();
		
	// operators
	public:
		CTBigint& operator=(LONG value)
			{SetBigint(value); return *this;}
		CTBigint& operator=(CTFLOAT value)
			{SetBigint(value); return *this;}
		CTBigint& operator=(CTBIGINT value)
			{m_bigint = value; return *this;}
		CTBigint& operator=(CTUBIGINT value)
			{m_bigint = value; return *this;}
		CTBigint& operator=(const CTMoney& value)
			{SetBigint(value); return *this;}
		CTBigint& operator=(const CTString& value)
			{SetBigint(value); return *this;}
		CTBigint& operator=(const CTBigint& value)
			{SetBigint(value); return *this;}
		CTBigint& operator+=(const CTBigint& value)
			{*this = *this + value; return *this;}
		CTBigint& operator-=(const CTBigint& value)		
			{*this = *this - value; return *this;}
		CTBigint& operator*=(const CTBigint& value)		
			{*this = *this * value; return *this;}
		CTBigint& operator/=(const CTBigint& value)		
			{*this = *this / value; return *this;}
		friend ctdbEXPORT CTBigint abs(const CTBigint& value);
		friend ctdbEXPORT CTBigint operator+(const CTBigint& left, const CTBigint& right);        
		friend ctdbEXPORT CTBigint operator-(const CTBigint& left, const CTBigint& right);        
		friend ctdbEXPORT CTBigint operator*(const CTBigint& left, const CTBigint& right);        
		friend ctdbEXPORT CTBigint operator/(const CTBigint& left, const CTBigint& right);        
		friend ctdbEXPORT CTBOOL operator<(const CTBigint& left, const CTBigint& right);
		friend ctdbEXPORT CTBOOL operator<=(const CTBigint& left, const CTBigint& right);
		friend ctdbEXPORT CTBOOL operator>(const CTBigint& left, const CTBigint& right);
		friend ctdbEXPORT CTBOOL operator>=(const CTBigint& left, const CTBigint& right);
		friend ctdbEXPORT CTBOOL operator==(const CTBigint& left, const CTBigint& right);
		friend ctdbEXPORT CTBOOL operator!=(const CTBigint& left, const CTBigint& right);

	// Methods
	public:
		void SetBigint(LONG value);
		void SetBigint(CTFLOAT value);
		void SetBigint(const CTMoney& value);
		void SetBigint(const CTString& value);
		void SetBigint(const CTBigint& value);
		LONG AsLong() const;
		CTFLOAT AsFloat() const;
		CTMoney AsMoney() const;
		CTString AsString() const;
		CTBIGINT AsBigint() const;
		CTUBIGINT AsUnsignedBigint() const;
		CTBOOL IsZero() const;
		void Zero();
								
	// Members
	private:
		CTBIGINT	m_bigint;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTCurrency
*   CTDB C++ API currency class
*
\******************************************************************************/
class ctdbEXPORT CTCurrency
{
	// constructor & destructor
	public:
		CTCurrency()
			{m_currency = 0;}
		CTCurrency(LONG value)
			{SetCurrency(value);}
		CTCurrency(CTFLOAT value)
			{SetCurrency(value);}
		CTCurrency(CTCURRENCY value)
			{m_currency = value;}
		CTCurrency(const CTMoney& value)
			{SetCurrency(value);}
		CTCurrency(const CTString& value)
			{SetCurrency(value);}
		CTCurrency(const CTBigint& value)
			{SetCurrency(value);}
		CTCurrency(const CTCurrency& value)
			{m_currency = value.m_currency;}
		virtual ~CTCurrency();
					
	// operators
	public:
		CTCurrency& operator=(LONG value)
			{SetCurrency(value); return *this;}
		CTCurrency& operator=(CTFLOAT value)
			{SetCurrency(value); return *this;}
		CTCurrency& operator=(CTCURRENCY value)
			{m_currency = value; return *this;}
		CTCurrency& operator=(const CTMoney& value)
			{SetCurrency(value); return *this;}
		CTCurrency& operator=(const CTString& value)
			{SetCurrency(value); return *this;}
		CTCurrency& operator=(const CTBigint& value)
			{SetCurrency(value); return *this;}
		CTCurrency& operator=(const CTCurrency& value)
			{m_currency = value.m_currency; return *this;}
		CTCurrency& operator+=(const CTCurrency& value)
			{*this = *this + value; return *this;}
		CTCurrency& operator-=(const CTCurrency& value)
			{*this = *this - value; return *this;}
		CTCurrency& operator*=(const CTCurrency& value)
			{*this = *this * value; return *this;}
		CTCurrency& operator/=(const CTCurrency& value)
			{*this = *this / value; return *this;}
		friend ctdbEXPORT CTCurrency abs(const CTCurrency& value);
		friend ctdbEXPORT CTCurrency operator+(const CTCurrency& left, const CTCurrency& right);				
		friend ctdbEXPORT CTCurrency operator-(const CTCurrency& left, const CTCurrency& right);				
		friend ctdbEXPORT CTCurrency operator*(const CTCurrency& left, const CTCurrency& right);				
		friend ctdbEXPORT CTCurrency operator/(const CTCurrency& left, const CTCurrency& right);
		friend ctdbEXPORT CTBOOL operator<(const CTCurrency& left, const CTCurrency& right);
		friend ctdbEXPORT CTBOOL operator<=(const CTCurrency& left, const CTCurrency& right);
		friend ctdbEXPORT CTBOOL operator>(const CTCurrency& left, const CTCurrency& right);
		friend ctdbEXPORT CTBOOL operator>=(const CTCurrency& left, const CTCurrency& right);
		friend ctdbEXPORT CTBOOL operator==(const CTCurrency& left, const CTCurrency& right);
		friend ctdbEXPORT CTBOOL operator!=(const CTCurrency& left, const CTCurrency& right);
		
	// Methods
	public:
		CTBOOL IsZero() const;
		void Zero();
		CTCurrency Round(NINT scale);
		void SetCurrency(LONG value);
		void SetCurrency(CTFLOAT value);
		void SetCurrency(const CTMoney& value);
		void SetCurrency(const CTString& value);
		void SetCurrency(const CTBigint& value);
		LONG AsLong() const;
		CTFLOAT AsFloat() const;
		CTMoney AsMoney() const;
		CTString AsString() const;
		CTBigint AsBigint() const;
		CTCURRENCY AsCurrency() const;
		
	// Members
	private:
		CTCURRENCY	m_currency;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTNumber
*   CTDB C++ API CTNumber class
*
\******************************************************************************/
class ctdbEXPORT CTNumber
{
	// constructor & destructor
	public:
		CTNumber();
		CTNumber(LONG value);
		CTNumber(CTFLOAT value);
		CTNumber(pCTNUMBER value);
		CTNumber(const CTMoney& value);
		CTNumber(const CTString& value);
		CTNumber(const CTBigint& value);
		CTNumber(const CTCurrency& value);
		CTNumber(const CTNumber& value);
		virtual ~CTNumber();
			
	// operators
	public:
		CTNumber& operator=(LONG value)
			{SetNumber(value); return *this;}
		CTNumber& operator=(CTFLOAT value)
			{SetNumber(value); return *this;}
		CTNumber& operator=(pCTNUMBER value)
			{SetNumber(value); return *this;}
		CTNumber& operator=(const CTMoney& value)
			{SetNumber(value); return *this;}
		CTNumber& operator=(const CTString& value)
			{SetNumber(value); return *this;}
		CTNumber& operator=(const CTBigint& value)
			{SetNumber(value); return *this;}
		CTNumber& operator=(const CTCurrency& value)
			{SetNumber(value); return *this;}
		CTNumber& operator=(const CTNumber& value)
			{SetNumber(value); return *this;}
		CTNumber& operator+=(const CTNumber& value)
			{add(*this, value); return *this;}
		CTNumber& operator-=(const CTNumber& value)
			{sub(*this, value); return *this;}
		CTNumber& operator*=(const CTNumber& value)
			{mul(*this, value); return *this;}
		CTNumber& operator/=(const CTNumber& value)
			{div(*this, value); return *this;}
		friend ctdbEXPORT CTNumber abs(const CTNumber& value);
		friend ctdbEXPORT CTNumber operator+(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTNumber operator-(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTNumber operator*(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTNumber operator/(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTBOOL operator<(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTBOOL operator<=(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTBOOL operator>(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTBOOL operator>=(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTBOOL operator==(const CTNumber& left, const CTNumber& right);
		friend ctdbEXPORT CTBOOL operator!=(const CTNumber& left, const CTNumber& right);

	// Methods
	public:
		CTBOOL IsZero() const;
		void Zero() const;
		CTNumber Round(NINT scale);
		NINT IntegralDigits() const;
		NINT DecimalDigits() const;
		void SetNumber(LONG value);
		void SetNumber(CTFLOAT value);
		void SetNumber(const CTMoney& value);
		void SetNumber(const CTString& value);
		void SetNumber(const CTBigint& value);
		void SetNumber(const CTCurrency& value);
		void SetNumber(const CTNumber& value);
		void SetNumber(pCTNUMBER value);
		LONG AsLong() const;
		CTFLOAT AsFloat() const;
		CTMoney AsMoney() const;
		CTString AsString() const;
		CTBigint AsBigint() const;
		CTCurrency AsCurrency() const;
		pCTNUMBER AsNumber() const;

	private:
		void add(CTNumber& left, const CTNumber& right);
		void sub(CTNumber& left, const CTNumber& right);
		void mul(CTNumber& left, const CTNumber& right);
		void div(CTNumber& left, const CTNumber& right);

	// Members
	private:
		pCTNUMBER m_number;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   CTBlob
*   CTDB C++ API BLOB class
*
\******************************************************************************/
class ctdbEXPORT CTBlob
{
    // Constructors & destructor
    public:
        CTBlob();
        CTBlob(cpVOID data, VRLEN size);
        CTBlob(const CTString& str);
        CTBlob(const pCTBLOB pBlob);
        CTBlob(const CTBlob& blob);
        virtual ~CTBlob();
        
    // Operators
    public:
        CTBlob& operator=(const pCTBLOB pBlob);
        CTBlob& operator=(const CTBlob& blob);
        CTBOOL operator<(const CTBlob& blob);
        CTBOOL operator<=(const CTBlob& blob);
        CTBOOL operator>(const CTBlob& blob);
        CTBOOL operator>=(const CTBlob& blob);
        CTBOOL operator==(const CTBlob& blob);
        CTBOOL operator!=(const CTBlob& blob);
        
    // Methods
    public:
        pCTBLOB Get()
            {return m_blob;}
            
        void GetBlob(pCTBLOB pBlob) const;
        void GetBlob(pVOID& pdata, VRLEN& size);
        void SetBlob(const pCTBLOB pBlob);
        void SetBlob(const CTBlob& blob);
        void SetBlob(cpVOID data, VRLEN size);
        void SetBlob(const CTString& str);
		void UpdateBlob(cpVOID data, VRLEN size, VRLEN offset);
        void Resize(VRLEN size);
        void AsString(CTString& str) const;
        VRLEN GetSize() const;
    
    // Members
    public:
        pCTBLOB m_blob;
};
/*~***************************************************************************/

/*^****************************************************************************\
*
*   Forward class declarations
*
\******************************************************************************/
class CTSession;
class CTDatabase;
class CTTable;
class CTResource;
class CTRecord;
class CTField;
class CTIndex;
class CTSegment;
class CTFullTextIndex;
class CTFullTextIndexDictionary;
class CTHelloWorld;		/* CTDB HELLO WORLD */

/*^****************************************************************************\
*
*   CTBase
*   CTDB C++ API base class
*
\******************************************************************************/
#undef Begin
#undef Commit
#undef Abort
#undef SetSavePoint
#undef RestoreSavePoint

class ctdbEXPORT CTBase
{
    // Constructor & destructor
    public:
        CTBase();
        virtual ~CTBase();
        
    // Methods
    public:
        virtual CTDBRET GetError();
        virtual void SetError(const CTDBRET code);
        virtual void ClearError();
        virtual CTBOOL IsTransActive() const;
        virtual void Begin();
        virtual void Commit();
        virtual void Abort();
        virtual NINT SetSavePoint();
        virtual void RestoreSavePoint(const NINT SavePoint);
		virtual CTBOOL IsLockActive();
		virtual CTLOCK_MODE GetLockMode();
        virtual void Lock(CTLOCK_MODE mode);
		virtual void Unlock();
        virtual CTHANDLE GetHandle() const;
        virtual void SetHandle(CTHANDLE Handle);
        virtual NINT GetHandleId() const;
        virtual CTDATE_TYPE GetDefDateType() const;
        virtual CTTIME_TYPE GetDefTimeType() const;
        virtual void SetDefDateType(CTDATE_TYPE DateType);
        virtual void SetDefTimeType(CTTIME_TYPE TimeType);
		virtual void SetDefFloatFormat(const CTString& format);
		virtual CTString GetDefFloatFormat();
		virtual pVOID GetUserTag();
		virtual void SetUserTag(pVOID tagptr);
		virtual CTKEEP_MODE GetKeepLock();
		virtual void SetKeepLock(CTKEEP_MODE mode);
		virtual void SwitchInstance();	
#ifdef CTDB_CALLBACK
		virtual NINT GetHandleType();
		virtual CTDB_TABLE_TYPE GetTableType();
#endif
		virtual LONG GetSystemConfig(NINT index);
		virtual CTBEGIN_MODE GetTransactionMode();
		virtual void SetTransactionMode(CTBEGIN_MODE mode);
		virtual CTOPS_MODE GetOperation();
		virtual void SetOperation(CTOPS_MODE mode, CTOPS_STATE state);
		virtual CTBOOL GetAutoCommit();
		virtual void SetAutoCommit(CTBOOL flag);

    // Members
    public:
        CTHANDLE    m_handle;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTSession
*   CTDB C++ API session class
*
\******************************************************************************/
class ctdbEXPORT CTSession : public CTBase
{
    // Constructor & destructor
    public:
        CTSession(CTSESSION_TYPE SessionType = CTSESSION_CTDB);
        virtual ~CTSession();
        
    // Methods
    public:
		virtual void Logon(const CTString& dbEngine=ctdbDEFAULT_dbengine, 
        const CTString& user=ctdbDEFAULT_userid, const CTString& password=ctdbDEFAULT_userword);
        virtual void Logout();
		virtual void Create(const CTString& dbEngine=ctdbDEFAULT_dbengine, 
        const CTString& user=ctdbDEFAULT_userid, const CTString& password=ctdbDEFAULT_userword);       
        virtual CTString GetServerName() const;
        virtual CTString GetUserLogonName() const;
        virtual CTString GetPassword() const;
        virtual NINT GetParam(const CTSESSION_PARAM ParamType) const;
        virtual void SetParam(const CTSESSION_PARAM ParamType, const NINT value);
        virtual CTBOOL IsActive() const;
        virtual CTString GetPath();
        virtual void SetPath(const CTString Path);
        virtual CTBOOL FirstDatabase(CTString& Name, CTString& Path);
        virtual CTBOOL NextDatabase(CTString& Name, CTString& Path);
        virtual CTBOOL FindDatabase(const CTString& Name, CTString& Path);
        virtual CTBOOL FindDatabase(const CTString& Name, CTString& Path, ULONG& uid);
        virtual CTBOOL FindDatabase(ULONG uid, CTString& Name, CTString& Path);
        virtual void DisconnectAll();
        virtual void CreateDatabase(const CTString& Name, const CTString& Path);
        virtual void AddDatabase(const CTString& Name, const CTString& Path);
        virtual void DeleteDatabase(const CTString& Name);
        virtual void DropDatabase(const CTString& Name);
        virtual void GetDatabaseUID(const CTString& Name, ULONG& uid);
		virtual CTDatabase* GetFirstActive(VRLEN& ScanRec);
		virtual CTDatabase* GetFirstActive();
		virtual CTDatabase* GetNextActive(VRLEN& ScanRec);
		virtual CTDatabase* GetNextActive();
		virtual CTDatabase* FindActive(const CTString& Name);
		virtual CTDatabase* FindActive(ULONG uid);
		virtual void SetLogonOnly(CTBOOL flag = YES);
		virtual CTBOOL GetLogonOnly();
		virtual NINT GetDatabaseCount();
		virtual void SetSessionType(CTSESSION_TYPE SessionType);
		virtual CTSESSION_TYPE GetSessionType();
		virtual void SetCurrentNodeName(const CTString& NodeName);
		virtual void SetPathPrefix(const CTString& path);
		virtual void ClearPathPrefix();
		virtual CTString GetPathPrefix();
		virtual CTBOOL IsSQLServer() const;
		virtual void SetExclusive(CTBOOL flag = YES);
		virtual CTBOOL IsExclusive() const;
		virtual void Attach(CTBOOL isTransactionActive = NO);
		virtual void Attach(const CTString& ctreeid, CTBOOL isTransactionActive = NO);
		virtual void Attach(const CTSession& Session);
		virtual void Detach();
		virtual CTATTACH_MODE GetAttachMode() const;
		virtual void BeginImpersonation( NINT taskId );
		virtual void EndImpersonation();
		
		static CTDBRET SetConfigurationFile(pTEXT cfgfil);
		static CTDBRET StartDatabaseEngine();
		static void StopDatabaseEngine();
		virtual CTDateTime ServerDateTime();
		virtual void SetLogPath(const CTString& path);
		virtual void SetStatusLogPath(const CTString& path);
		virtual void SetTempPath(const CTString& path);
		
	// Members
	private:
		VRLEN	m_scanrec;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTDatabase
*   CTDB C++ API database class
*
\******************************************************************************/
class ctdbEXPORT CTDatabase : public CTBase
{
    // Constructor & destructor
    public:
        CTDatabase(const CTSession& Handle);
        CTDatabase(const CTSession* Handle);
        virtual ~CTDatabase();
        
    // Methods
    public:
    	virtual CTBOOL IsActive();
        virtual void Connect(const CTString& Name);
        virtual void Create(const CTString& Name, const CTString& Path);
        virtual void Disconnect();
        virtual CTBOOL FirstTable(CTString& Name, CTString& Path);
        virtual CTBOOL NextTable(CTString& Name, CTString& Path);
        virtual CTBOOL FindTable(const CTString& Name, CTString& Path);
        virtual CTBOOL FindTable(const CTString& Name, CTString& Path, ULONG& uid);
        virtual CTBOOL FindTable(ULONG uid, CTString& Name, CTString& Path);
        virtual void AddTable(const CTString& Name, const CTString& Path);
        virtual void DeleteTable(const CTString& Name, const CTString& Password);
        virtual void DropTable(const CTString& Name);
        virtual void GetTableUID(const CTString& Name, ULONG& uid);
		virtual CTTable* GetFirstActive(VRLEN& ScanRec);
		virtual CTTable* GetFirstActive();
		virtual CTTable* GetNextActive(VRLEN& ScanRec);
		virtual CTTable* GetNextActive();
		virtual CTTable* FindActive(const CTString& Name);
		virtual CTTable* FindActive(ULONG uid);
		virtual CTString GetPath();
		virtual CTString GetName();
		virtual void CloseAll();
		virtual NINT GetTableCount();
		virtual CTString GetDefaultSqlTableOwner();
		virtual void SetDefaultSqlTableOwner(const CTString& owner);
		virtual CTBOOL IsSQL() const;
		virtual void SetExclusive(CTBOOL flag = YES);
		virtual CTBOOL IsExclusive() const;
		virtual void RenameTable (const CTString& OldName, const CTString& NewName);
				
	// Members
	private:
		VRLEN	m_scanrec;
}; 
/*^****************************************************************************\
*
*   CTTable
*   CTDB C++ API table class
*
\******************************************************************************/
class ctdbEXPORT CTTable : public CTBase
{
    // Constructor & destructor
    public:
        CTTable(const CTDatabase& Handle);
        CTTable(const CTDatabase* Handle);
        CTTable(const CTSession& Handle);
        CTTable(const CTSession* Handle);
        virtual ~CTTable();
        
    // Methods
    public:
        virtual CTBOOL IsActive() const;
        virtual CTString GetName() const;
        virtual CTString GetPath() const;
        virtual CTString GetDataExtension() const;
        virtual CTString GetIndexExtension() const;
        virtual CTOPEN_MODE GetOpenMode() const;
        virtual CTCREATE_MODE GetCreateMode() const;
        virtual NINT GetDataDefaultExtentSize() const;
        virtual NINT GetIndexDefaultExtentSize() const;
        virtual CTString GetPassword() const;
        virtual CTString GetGroupid() const;
        virtual LONG GetPermission() const;
        virtual void SetPath(const CTString& Path);
        virtual void SetDataExtension(const CTString& Ext);
        virtual void SetIndexExtension(const CTString& Ext);
        virtual void SetDataDefaultExtentSize(const NINT size);
        virtual void SetIndexDefaultExtentSize(const NINT size);
        virtual void SetPassword(const CTString& Password);
        virtual void SetGroupid(const CTString& Groupid);
        virtual void SetPermission(const LONG Permmask);
        virtual void Create(const CTString& Name, const CTCREATE_MODE CreateMode);
        virtual void Open(const CTString& Name, const CTOPEN_MODE OpenMode);
        virtual void Close();
        virtual void Remove();
        virtual VRLEN GetFieldCount() const;
		virtual CTField AddField(const CTString& Name, CTDBTYPE Type, VRLEN Length);
        virtual CTField InsertField(const NINT BeforeField, const CTString& Name, CTDBTYPE Type, VRLEN Length);
        virtual CTField InsertField(const CTString& BeforeField, const CTString& Name, CTDBTYPE Type, VRLEN Length);
        virtual void DelField(const NINT FieldNumber);
        virtual void DelField(const CTString& FieldName);
		virtual void MoveField(const NINT FieldNumber, NINT newNumber);
		virtual void MoveField(const CTString& FieldName, NINT newNumber);
        virtual CTField GetField(NINT FieldNumber) const;
        virtual CTField GetField(const CTString& FieldName) const;
        virtual NINT GetFieldNumber(const CTString& FieldName) const;
        virtual VRLEN GetIndexCount() const;
        virtual CTIndex AddIndex(const CTString& name, CTDBKEY KeyType, CTBOOL AllowDuplicates, CTBOOL NullFlag);
        virtual void DelIndex(NINT IndexNumber);
        virtual void DelIndex(const CTString& IndexName);
        virtual CTIndex GetIndex(NINT IndexNumber);
        virtual CTIndex GetIndex(const CTString& name);
        virtual CTSegment GetSegment(const CTIndex& pIndex, VRLEN SegNumber);
        virtual CTSegment AddSegment(const CTIndex& pIndex, const CTField& pField, CTSEG_MODE SegMode);
        virtual CTSegment AddSegment(const CTIndex& pIndex, const CTString& FieldName, CTSEG_MODE SegMode);
        virtual CTSegment AddSegment(const CTIndex& pIndex, NINT FieldNumber, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(const CTIndex& pIndex, NINT offset, NINT length, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(NINT IndexNbr, NINT FieldNbr, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(NINT IndexNbr, const CTString& FieldName, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(NINT IndexNbr, const CTField& pField, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(const CTString& IndexName, const CTString& FieldName, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(const CTString& IndexName, NINT FieldNumber, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(const CTString& IndexName, const CTField& pField, CTSEG_MODE SegMode);
        virtual CTSegment InsertSegment(const CTIndex& pIndex, NINT BeforeSegment, const CTField& Field, CTSEG_MODE SegMode);
        virtual CTSegment InsertSegment(const CTIndex& pIndex, NINT BeforeSegment, const CTString& FieldName, CTSEG_MODE SegMode);
        virtual CTSegment InsertSegment(const CTIndex& pIndex, NINT BeforeSegment, NINT FieldNumber, CTSEG_MODE SegMode);
		virtual CTSegment InsertSegment(const CTIndex& pIndex, NINT BeforeSegment, NINT offset, NINT length, CTSEG_MODE SegMode);
		virtual CTSegment InsertSegment(NINT IndexNbr, NINT BeforeSegment, NINT FieldNumber, CTSEG_MODE SegMode);
		virtual CTSegment InsertSegment(NINT IndexNbr, NINT BeforeSegment, const CTString& FieldName, CTSEG_MODE SegMode);
		virtual CTSegment InsertSegment(const CTString& IndexName, NINT BeforeSegment, const CTString& FieldName, CTSEG_MODE SegMode);
		virtual CTSegment InsertSegment(const CTString& IndexName, NINT BeforeSegment, NINT FieldNumber, CTSEG_MODE SegMode);
		virtual CTSegment InsertSegment(const CTString& IndexName, NINT BeforeSegment, const CTField& Field, CTSEG_MODE SegMode);
		virtual CTSegment InsertSegment(NINT IndexNbr, NINT BeforeSegment, const CTField& Field, CTSEG_MODE SegMode);
        virtual void DelSegment(NINT IndexNUmber, NINT SegNumber);
		virtual void DelSegment(const CTString& IndexName, NINT SegNumber);
        virtual void Alter(NINT Action);
        virtual void ResetAll();
        virtual CTBOOL HasNullFieldSupport();
		virtual CTIndex GetIndexByUID(ULONG uid);
		virtual CTBOOL HasRecbyt();
		virtual CTBOOL HasRowid();
		virtual void UnlockTable();
#ifdef CTDB_CNDX_IDX 
		virtual void UpdateCndxIndex(NINT indexnbr, const CTString& cndexpr);
		virtual void UpdateCndxIndex(const CTString& indexname, const CTString& cndexpr);
		virtual void GetCndxIndex(NINT indexnbr, CTString& cndexpr);
		virtual void GetCndxIndex(const CTString& indexname, CTString& cndexpr);
#endif /* CTDB_CNDX_IDX  */

#ifdef CTDB_FILTER_020617
		virtual void FilterRecord(const CTString& cndexpr);
		virtual CTBOOL IsFilteredRecord();
		virtual void GetFilter(CTString& cndexpr);
#endif /* CTDB_FILTER_020617 */

#ifdef CTDB_PAD_RESOURCE
		virtual void GetPadChar(TEXT &Padchar, TEXT &Dmlchar);
		virtual void SetPadChar(NINT padchar, NINT dmlchar);
		virtual void UpdatePadChar(NINT padchar, NINT dmlchar, CTBOOL rebuild);
#endif
		virtual void UpdateCreateMode(CTCREATE_MODE mode);
		virtual CTBOOL HasDelField();
		virtual void SetIndexFilename(NINT IndexNumber, const CTString* path, const CTString* filename);
		virtual void SetIndexFilename(const CTString& IndexName, const CTString* path, const CTString* filename);
		virtual CTString GetIndexFilename(NINT IndexNumber);
		virtual CTString GetIndexFilename(const CTString& IndexName);
		virtual NINT GetDatno();
		virtual NINT GetIdxno(NINT index);
		virtual NINT GetIdxno(const CTString& IndexName);
#ifdef CTDB_SYSTEM_FILTER
		virtual void SystemFilterOn(CTSYSFILTER mode);
		virtual void SystemFilterOff(CTSYSFILTER mode);
#endif /* CTDB_SYSTEM_FILTER */
#ifdef CTDB_DEFAULT_VALUE
		virtual void ClearAllFieldDefaultValue();
#endif /* CTDB_DEFAULT_VALUE */
		virtual void MoveSegment(CTIndex hIndex, NINT segNumber, NINT newIndex);
		virtual void MoveSegment(NINT indexNumber, NINT segNumber, NINT newIndex);
		virtual void MoveSegment(const CTString& indexName, NINT segNumber, NINT newIndex);
		virtual ULONG GetStatus() const;
		virtual void Attach(NINT datno);
		virtual void AttachXtd(NINT datno, NINT nbrfields, pDATOBJ dodaptr, pIFIL ifilptr);
		virtual void Detach();
		virtual CTString GetOwner() const;
		virtual void SetOwner(const CTString& owner);
		virtual void Rebuild(CTREBUILD_MODE mode);
		virtual void SetRebuildCallback(pRBLCBFNC funcptr, UCOUNT step);
		virtual COUNT PartAdminByName(pTEXT partname, CTPART_MODE_E partmode);
		virtual COUNT PartAdminByKey(pVOID key, CTPART_MODE_E partmode);
		virtual COUNT PartAdminByNumber(LONG prawno, CTPART_MODE_E partmode);
		virtual NINT GetPartitionIndexNbr();
		virtual void SetPartitionIndexNbr(NINT idxno);
		virtual void SetPartitionNumberBits(UCOUNT bitno);
		virtual void SetPartitionRule(pTEXT expr);
		virtual void SetPartitionMaximumActive(UCOUNT max);
		virtual LONG  GetLastPartition() const;
		virtual LONG  GetFirstPartition() const;
		virtual void  Clone(CTTable &target, const CTString& Name);
		virtual void CreateMRTTable(const CTString& Name, const CTString& ParentName,  const CTCREATE_MODE CreateMode, const CTString& Filter);
		virtual void AddMRTTable(pCTDBDATABASE pDatabase, const CTString& Name, const CTString& ParentName, UINT info);
#if needed
		virtual CTHANDLE AllocVTableInfo(UCOUNT Size);
		virtual void FreeVTableInfo(pCTDBVTABLEINFO Info);
		virtual void GetVTableInfoFromTable(pCTDBVTABLEINFO VtableRes);
#endif
		virtual UINT GetVTableNumber();
		virtual CTBOOL IsVTable();
		virtual void RemoveVTableResource(pCTDBTABLE Parent, NINT number);
		virtual void SetMRTTableFilter(const CTString& Condition);

		virtual COUNT GetFullTextIndexCount() const;
		virtual CTFullTextIndex AddFullTextIndex(const CTString& name);
		virtual void DelFullTextIndex(NINT IndexNumber);
		virtual void DelFullTextIndex(const CTString& IndexName);
		virtual CTFullTextIndex GetFullTextIndex(NINT IndexNumber);
		virtual CTFullTextIndex GetFullTextIndex(const CTString& name);
		virtual void SetFullTextIndexOption(CTFullTextIndex& pIndex, UCOUNT option, CTString &pvalue, ULONG lvalue);
		virtual void SetFullTextIndexOption(NINT IndexNbr, UCOUNT option, CTString &pvalue, ULONG lvalue);
		virtual void SetFullTextIndexOption(const CTString& IndexName, UCOUNT option, CTString &pvalue, ULONG lvalue);
};
/*^****************************************************************************\
*
*   CTResource
*   CTDB C++ API resource class
*
\******************************************************************************/
class ctdbEXPORT CTResource
{
	// members
	private:
		CTHANDLE m_resource;

    // Constructor & destructor
    public:
		CTResource(const CTTable& hTable);
		CTResource(const CTTable& hTable, ULONG type, ULONG number);
		CTResource(const CTTable& hTable, ULONG type, ULONG number, const CTString& name);
		virtual ~CTResource();
	
    // Methods
    public:
		virtual void Unlock();
		virtual void Add(pVOID data, VRLEN size);
		virtual void Delete();
		virtual void Update(pVOID data, VRLEN size);
		virtual CTBOOL First(CTBOOL lock = NO) const;
		virtual CTBOOL Next(CTBOOL lock = NO) const;
		virtual CTBOOL Find(ULONG type, ULONG number, CTBOOL lock = NO) const;
		virtual CTBOOL Find(const CTString& name, CTBOOL lock = NO) const;
		virtual CTBOOL IsLocked() const;
		virtual ULONG GetType() const;
		virtual void SetType(ULONG type);
		virtual ULONG GetNumber() const;
		virtual void SetNumber(ULONG number);
		virtual CTString GetName() const;
		virtual void SetName(const CTString& name);
		virtual VRLEN GetDataLength() const;
		virtual pVOID GetData() const;
		virtual void SetData(pVOID data, VRLEN size);
};
/*^****************************************************************************\
*
*   CTRecord
*   CTDB C++ API record management class
*
\******************************************************************************/
class ctdbEXPORT CTRecord : public CTBase
{
    // Constructor & destructor
    public:
        CTRecord(const CTTable& Handle);
        CTRecord(const CTTable* Handle);
        CTRecord(const CTRecord& Handle);
        CTRecord(const CTRecord* Handle);
        virtual ~CTRecord();
        
    // Methods
    public:
        virtual CTBOOL First();
        virtual CTBOOL Last();
        virtual CTBOOL Next();
        virtual CTBOOL Prev();
        virtual CTBOOL Find(CTFIND_MODE FindMode);
        virtual CTBOOL FindTarget(pVOID target, CTFIND_MODE FindMode);
        virtual void Clear();
        virtual void Read();
        virtual void Write();
        virtual void Delete();
        virtual void Reset();
		virtual void CopyBuffer(const CTRecord& source);
		virtual void CopyBuffer(const CTRecord* source);
        virtual CTBOOL IsNew() const;
        virtual CTBOOL IsEdited() const;
        virtual void SetNew(CTBOOL flag);
        virtual void SetEdited(CTBOOL flag);
        virtual pVOID GetRecordBuffer();
		virtual CTOFFSET GetRecordPos() const;
		virtual void SetRecordPos(CTOFFSET offset);
		virtual void SetRecordOffset(CTOFFSET offset);
		virtual void SeekRecord(CTOFFSET offset);    
        virtual VRLEN GetRecordLength() const;
        virtual VRLEN GetRecordSize() const;
        virtual CTBOOL IsNullField(NINT FieldNumber);
        virtual NINT GetDefaultIndex();
        virtual CTString GetDefaultIndexName();
        virtual void SetDefaultIndex(NINT indexno);
        virtual void SetDefaultIndex(const CTString& name);
        virtual CTString GetFieldName(NINT FieldNumber);
        virtual CTDBTYPE GetFieldType(NINT FieldNumber);
        virtual CTBOOL GetFieldAsBool(NINT FieldNumber);
        virtual CTSIGNED GetFieldAsSigned(NINT FieldNumber);
        virtual CTUNSIGNED GetFieldAsUnsigned(NINT FieldNumber);
        virtual CTDate GetFieldAsDate(NINT FieldNumber);
        virtual CTTime GetFieldAsTime(NINT FieldNumber);
        virtual CTDateTime GetFieldAsDateTime(NINT FieldNumber);
        virtual CTMoney GetFieldAsMoney(NINT FieldNumber);
        virtual CTFLOAT GetFieldAsFloat(NINT FieldNumber);
        virtual CTString GetFieldAsString(NINT FieldNumber);
        virtual CTJsonString GetFieldAsJSON(NINT FieldNumber);
        virtual void GetFieldAsBlob(NINT FieldNumber, CTBlob& value);
        virtual void SetFieldAsBool(NINT FieldNumber, CTBOOL value);      
        virtual void SetFieldAsSigned(NINT FieldNumber, CTSIGNED value);      
        virtual void SetFieldAsUnsigned(NINT FieldNumber, CTUNSIGNED value);      
        virtual void SetFieldAsDate(NINT FieldNumber, const CTDate& value);      
        virtual void SetFieldAsTime(NINT FieldNumber, const CTTime& value);      
        virtual void SetFieldAsDateTime(NINT FieldNumber, const CTDateTime& value);      
        virtual void SetFieldAsMoney(NINT FieldNumber, const CTMoney& value);      
        virtual void SetFieldAsFloat(NINT FieldNumber, CTFLOAT value);      
        virtual void SetFieldAsString(NINT FieldNumber, const CTString& value);      
        virtual void SetFieldAsString(NINT FieldNumber, cpTEXT value);
        virtual void SetFieldAsJSON(NINT FieldNumber, const CTJSON value);
        virtual void SetFieldAsJSON(NINT FieldNumber, const CTJsonString &value);
        virtual void SetFieldAsBlob(NINT FieldNumber, CTBlob& value);      
        virtual CTBigint GetFieldAsBigint(NINT FieldNumber);
        virtual CTCurrency GetFieldAsCurrency(NINT FieldNumber);
        virtual CTNumber GetFieldAsNumber(NINT FieldNumber);		
        virtual void SetFieldAsBigint(NINT FieldNumber, const CTBigint& value);
        virtual void SetFieldAsCurrency(NINT FieldNumber, const CTCurrency& value);
        virtual void SetFieldAsNumber(NINT FieldNumber, const CTNumber& value);
            
        virtual CTDBTYPE GetFieldType(const CTString& FieldName)
            {return GetFieldType(GetFieldByName(FieldName));}

        virtual CTBOOL IsNullField(const CTString& FieldName)
            {return IsNullField(GetFieldByName(FieldName));}
            
        virtual CTBOOL GetFieldAsBool(const CTString& FieldName)
            {return GetFieldAsBool(GetFieldByName(FieldName));}
            
        virtual TEXT GetFieldAsChar(NINT FieldNumber)
            {return (TEXT)GetFieldAsSigned(FieldNumber);}
            
        virtual UTEXT GetFieldAsByte(NINT FieldNumber)
            {return (UTEXT)GetFieldAsUnsigned(FieldNumber);}
            
        virtual COUNT GetFieldAsShort(NINT FieldNumber)
            {return (COUNT)GetFieldAsSigned(FieldNumber);}
            
        virtual UCOUNT GetFieldAsWord(NINT FieldNumber)
            {return (UCOUNT)GetFieldAsUnsigned(FieldNumber);}        

        virtual TEXT GetFieldAsChar(const CTString& FieldName)
            {return GetFieldAsChar(GetFieldByName(FieldName));}
            
        virtual UTEXT GetFieldAsByte(const CTString& FieldName)
            {return GetFieldAsByte(GetFieldByName(FieldName));}
            
        virtual COUNT GetFieldAsShort(const CTString& FieldName)
            {return GetFieldAsShort(GetFieldByName(FieldName));}
            
        virtual UCOUNT GetFieldAsWord(const CTString& FieldName)
            {return GetFieldAsWord(GetFieldByName(FieldName));}
        
        virtual CTSIGNED GetFieldAsSigned(const CTString& FieldName)
            {return GetFieldAsSigned(GetFieldByName(FieldName));}
            
        virtual CTUNSIGNED GetFieldAsUnsigned(const CTString& FieldName)
            {return GetFieldAsUnsigned(GetFieldByName(FieldName));}
            
        virtual CTDate GetFieldAsDate(const CTString& FieldName)
            {return GetFieldAsDate(GetFieldByName(FieldName));}
            
        virtual CTTime GetFieldAsTime(const CTString& FieldName)
            {return GetFieldAsTime(GetFieldByName(FieldName));}
            
        virtual CTDateTime GetFieldAsDateTime(const CTString& FieldName)
            {return GetFieldAsDateTime(GetFieldByName(FieldName));}
            
        virtual CTMoney GetFieldAsMoney(const CTString& FieldName)
            {return GetFieldAsMoney(GetFieldByName(FieldName));}
            
        virtual CTFLOAT GetFieldAsFloat(const CTString& FieldName)
            {return GetFieldAsFloat(GetFieldByName(FieldName));}
            
        virtual CTString GetFieldAsString(const CTString& FieldName)
            {return GetFieldAsString(GetFieldByName(FieldName));}

        virtual CTJsonString GetFieldAsJSON(const CTString& FieldName)
            {return GetFieldAsJSON(GetFieldByName(FieldName));}
            
        virtual void GetFieldAsBlob(const CTString& FieldName, CTBlob& value)
            {GetFieldAsBlob(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsBool(const CTString& FieldName, CTBOOL value)
            {SetFieldAsBool(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsChar(NINT FieldNumber, TEXT value)
            {SetFieldAsSigned(FieldNumber, (CTSIGNED)value);}
            
        virtual void SetFieldAsByte(NINT FieldNumber, UTEXT value)
            {SetFieldAsUnsigned(FieldNumber, (CTUNSIGNED)value);}
            
        virtual void SetFieldAsShort(NINT FieldNumber, COUNT value)
            {SetFieldAsSigned(FieldNumber, (CTSIGNED)value);}
            
        virtual void SetFieldAsWord(NINT FieldNumber, UCOUNT value)
            {SetFieldAsUnsigned(FieldNumber, (CTUNSIGNED)value);}

        virtual void SetFieldAsChar(const CTString& FieldName, TEXT value)
            {SetFieldAsSigned(GetFieldByName(FieldName), (CTSIGNED)value);}
            
        virtual void SetFieldAsByte(const CTString& FieldName, UTEXT value)
            {SetFieldAsUnsigned(GetFieldByName(FieldName), (CTUNSIGNED)value);}
            
        virtual void SetFieldAsShort(const CTString& FieldName, COUNT value)
            {SetFieldAsSigned(GetFieldByName(FieldName), (CTSIGNED)value);}
            
        virtual void SetFieldAsWord(const CTString& FieldName, UCOUNT value)
            {SetFieldAsUnsigned(GetFieldByName(FieldName), (CTUNSIGNED)value);}
                
        virtual void SetFieldAsSigned(const CTString& FieldName, CTSIGNED value)
            {SetFieldAsSigned(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsUnsigned(const CTString& FieldName, CTUNSIGNED value)
            {SetFieldAsUnsigned(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsDate(const CTString& FieldName, const CTDate& value)
            {SetFieldAsDate(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsTime(const CTString& FieldName, const CTTime& value)
            {SetFieldAsTime(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsDateTime(const CTString& FieldName, const CTDateTime& value)
            {SetFieldAsDateTime(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsMoney(const CTString& FieldName, const CTMoney& value)
            {SetFieldAsMoney(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsFloat(const CTString& FieldName, CTFLOAT value)
            {SetFieldAsFloat(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsString(const CTString& FieldName, const CTString& value)
            {SetFieldAsString(GetFieldByName(FieldName), value);}
            
        virtual void SetFieldAsString(const CTString& FieldName, cpTEXT value)
        	{SetFieldAsString(GetFieldByName(FieldName), value);}

		virtual void SetFieldAsJSON(const CTString& FieldName, const CTJSON value)
			{SetFieldAsJSON(GetFieldByName(FieldName), value);}
        	
        virtual void SetFieldAsBlob(const CTString& FieldName, CTBlob& value)
            {SetFieldAsBlob(GetFieldByName(FieldName), value);}

		virtual CTBigint GetFieldAsBigint(const CTString& FieldName)
			{return GetFieldAsBigint(GetFieldByName(FieldName));}
		virtual CTCurrency GetFieldAsCurrency(const CTString& FieldName)
			{return GetFieldAsCurrency(GetFieldByName(FieldName));}
		virtual CTNumber GetFieldAsNumber(const CTString& FieldName)
			{return GetFieldAsNumber(GetFieldByName(FieldName));}
		virtual void SetFieldAsBigint(const CTString& FieldName, const CTBigint& value)
			{SetFieldAsBigint(GetFieldByName(FieldName), value);}
		virtual void SetFieldAsCurrency(const CTString& FieldName, const CTCurrency& value)
			{SetFieldAsCurrency(GetFieldByName(FieldName), value);}
		virtual void SetFieldAsNumber(const CTString& FieldName, const CTNumber& value)
			{SetFieldAsNumber(GetFieldByName(FieldName), value);}
         
		virtual CTUINT64 GetRecordCount();

		virtual void RecordSetOn(NINT siglen);
		virtual CTBOOL IsRecordSetOn();
		virtual void RecordSetOff();
		
		virtual CTBOOL IsVariableField(NINT FieldNbr);
	
		virtual VRLEN GetFieldLength(NINT FieldNbr);
		virtual VRLEN GetFieldSize(NINT FieldNbr);
		virtual VRLEN GetFieldOffset(NINT FieldNbr);
		virtual pVOID GetFieldAddress(NINT FieldNbr);
		
		virtual CTBOOL IsVariableField(const CTString& FieldName)
			{return IsVariableField(GetFieldByName(FieldName));}
		virtual VRLEN GetFieldLength(const CTString& FieldName)
			{return GetFieldLength(GetFieldByName(FieldName));}
		virtual VRLEN GetFieldSize(const CTString& FieldName)
			{return GetFieldSize(GetFieldByName(FieldName));}
		virtual VRLEN GetFieldOffset(const CTString& FieldName)
			{return GetFieldOffset(GetFieldByName(FieldName));}
		virtual pVOID GetFieldAddress(const CTString& FieldName)
			{return GetFieldAddress(GetFieldByName(FieldName));}
        virtual NINT GetFieldByName(const CTString& FieldName);
        virtual void ClearField(const NINT FieldNbr);
        virtual void ClearField(const CTString& FieldName)
        	{ClearField(GetFieldByName(FieldName));}
        
        virtual void LockRecord(NINT mode);
        virtual void UnlockRecord();
		virtual CTLOCK_MODE GetRecordLock();
		        
        virtual CTROWID GetRowid();
        virtual CTBOOL FindRowid(CTROWID rowid, CTFIND_MODE FindMode);
#ifdef CTDB_CNDX_IDX 
		virtual void CndxCompile(const CTString& expression);
		virtual CTBOOL CndxEval();
		virtual void CndxFree();
		virtual void CndxGetExpression(CTString& expression);
#endif /* CTDB_CNDX_IDX  */
		virtual CTBOOL Compare(CTRecord *record);
		virtual void BuildTargetKey(CTFIND_MODE FindMode, pVOID targetkey, pVRLEN targetlen);
		virtual void AtPercentile(NINT percent);
		virtual ULONG8 EstimateSpan(pVOID key1, pVOID key2);
		virtual LONG NumberOfKeyEntries(NINT index);
		virtual LONG NumberOfKeyEntries(const CTString& indexName);
		
		virtual void RangeOn(NINT SegCount, pVOID lRange, pVOID uRange, pNINT operators);
		virtual void RangeOff();
		virtual CTBOOL IsRangeOn();
		
		virtual void SwitchContext();
#ifdef ctdbRECORD_FILTER
		virtual void SetFilter(const CTString& cndexpr);
		virtual CTBOOL IsFiltered();
		virtual void GetFilter(CTString& cndexpr);
#endif /* CTDB_FILTER_020617 */

#ifdef ctdbUNICODE
		virtual void SetFieldAsUTF16(NINT FieldNumber, pWCHAR value);
		virtual void GetFieldAsUTF16(NINT FieldNumber, pWCHAR value, VRLEN size);
		virtual void SetFieldAsUTF16(const CTString& FieldName, pWCHAR value)
			{SetFieldAsUTF16(GetFieldByName(FieldName), value);}
		virtual void GetFieldAsUTF16(const CTString& FieldName, pWCHAR value, VRLEN size)
			{GetFieldAsUTF16(GetFieldByName(FieldName), value, size);}
#endif /* ctdbUNICODE */
		virtual LONG BatchLoaded() const;
		virtual LONG BatchLocked() const;
		virtual LONG BatchTotal() const;
		virtual CTBATCH_MODE BatchMode() const;
		virtual CTBOOL IsBatchActive() const;
		virtual void EndBatch();
		virtual void InsertBatch();
		virtual void NextBatch();
		virtual CTBOOL NextInBatch();
		virtual void SetBatch(CTBATCH_MODE mode, VRLEN targetLen = 0, VRLEN bufferLen = 0);
		virtual NINT GetErrorIndex() const;
		virtual CTBOOL JumpTo(LONG offset);
		virtual CTOFFSET GetRecordKeyPos() const;
		
		virtual void SetDefaultFullTextIndex(NINT indexno);
		virtual void FullTextSearchOn(CTString &query);
		virtual CTBOOL IsFullTextSearchOn();
		virtual void FullTextSearchOff();
		virtual void GetFullTextSearchErrorDetails(pNINT error, pNINT position);
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTField
*   CTDB C++ API field class
*
\******************************************************************************/
class ctdbEXPORT CTField : public CTBase
{
    // Constructor & destructor
    public:
        CTField();
        CTField(const CTField& pField);
        virtual ~CTField();
           
    // Operators
    public:
    	virtual CTField& operator=(const CTField& pField);
    	 
    // Methods
    public:
        virtual CTString GetName() const;
        virtual CTDBTYPE GetType() const;
        virtual VRLEN GetLength() const;
        virtual void SetName(const CTString& FieldName);
        virtual void SetType(const CTDBTYPE Type, const VRLEN Length = 0);
        virtual void SetLength(const VRLEN Length);
		virtual NINT GetNumber();
		virtual CTBOOL GetNullFlag() const;
		virtual NINT GetPrecision() const;
		virtual NINT GetScale() const;
		virtual void SetNullFlag(CTBOOL flag);
		virtual void SetPrecision(NINT precision);
		virtual void SetScale(NINT scale);
		virtual CTBOOL IsNumeric() const;
#ifdef CTDB_DEFAULT_VALUE
		virtual void SetFieldDefaultValue(const CTString& value);
		virtual void SetFieldDefaultValue(pTEXT value, VRLEN length);
		virtual VRLEN GetFieldDefaultValue(pTEXT& value);
		virtual VRLEN GetFieldDefaultValue(CTString& value);
		virtual void ClearFieldDefaultValue();
		virtual void SetFieldDefaultDateTimeType(CTDATE_TYPE dateType = CTDATE_MDCY, CTTIME_TYPE timeType = CTTIME_HMS);
		virtual CTBOOL IsFieldDefaultValueSet();
		virtual CTDATE_TYPE GetFieldDefaultDateType();
		virtual CTTIME_TYPE GetFieldDefaultTimeType();
#endif /* CTDB_DEFAULT_VALUE */
		virtual ULONG GetStatus() const;
		virtual void SetFieldStringEncoding(const CTString& encoding);
		virtual void SetFieldStringEncoding(pTEXT encoding);
		virtual CTString GetFieldStringEncoding() const;
		virtual pTEXT GetFieldStringEncoding();
};
/*^****************************************************************************\
*
*   CTIndex
*   CTDB C++ API index class
*
\******************************************************************************/
class ctdbEXPORT CTIndex : public CTBase
{
    // Constructor & destructor
    public:
        CTIndex();
        CTIndex(const CTIndex& pIndex);
        virtual ~CTIndex();
        
    // Operators
    public:
    	virtual CTIndex& operator=(const CTIndex& pIndex);

    // Methods
    public:
        virtual NINT GetKeyLength() const;
        virtual CTDBKEY GetKeyType() const;
        virtual NINT GetEmptyChar() const;
        virtual CTBOOL GetDuplicateFlag() const;
        virtual CTBOOL GetNullFlag() const;
        virtual CTBOOL GetTemporaryFlag() const;
        virtual void SetEmptyChar(NINT EmptyChar);
        virtual void SetDuplicateFlag(CTBOOL DupFlag);
        virtual void SetNullFlag(CTBOOL NullFlag);
        virtual void SetTemporaryFlag(CTBOOL TempFlag);
        virtual NINT GetSegmentCount() const;
        virtual CTSegment AddSegment(const CTField& pField, CTSEG_MODE SegMode);
		virtual CTSegment AddSegment(NINT offset, NINT length, CTSEG_MODE SegMode);
        virtual CTSegment InsertSegment(NINT BeforeSegment, const CTField& Field, CTSEG_MODE SegMode);
        virtual CTSegment InsertSegment(NINT BeforeSegment, NINT offset, NINT length, CTSEG_MODE SegMode);
        virtual void DelSegment(NINT SegmentNumber);
        virtual CTSegment GetSegment(NINT SegmentNumber);
        virtual NINT GetNumber();
        virtual CTString GetName();
        virtual ULONG GetUID();
        virtual void SetName(const CTString& IndexName);
        virtual void SetKeyType(CTDBKEY keytype);
        virtual void SetFilename(const CTString* path, const CTString* name);
        virtual CTString GetFilename();
        virtual NINT GetIdxno();
        virtual ULONG GetStatus() const;
        virtual void MoveSegment(NINT segmentNumber, NINT newIndex);
        virtual CTSegment AddJSONSegment(const CTField& pField, pTEXT key, CTDBTYPE Type, VRLEN Length);
};
/*^****************************************************************************\
*
*   CTSegment
*   CTDB C++ API segment class
*
\******************************************************************************/
class ctdbEXPORT CTSegment : public CTBase
{
    // Constructor & destructor
    public:
        CTSegment();
        CTSegment(const CTSegment& pSeg);
        virtual ~CTSegment();
        
    // Operators
    public:
    	virtual CTSegment& operator=(const CTSegment& pSeg);

    // Methods:
    public:
        virtual CTField GetField() const;
        virtual CTString GetFieldName() const;
        virtual CTField GetPartialField() const;
        virtual CTString GetPartialFieldName() const;
        virtual CTSEG_MODE GetMode() const;
        virtual void SetMode(CTSEG_MODE SegMode);
		virtual NINT GetNumber();
		virtual ULONG GetStatus() const;
		virtual void MoveSegment(NINT newIndex);
		virtual void SetField(CTField& field);
		virtual void SetJSONField(CTField& field, pTEXT key, CTDBTYPE type, VRLEN size);
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTFullTextIndex
*   CTDB C++ API Full Text index class
*
\******************************************************************************/
class ctdbEXPORT CTFullTextIndex : public CTBase
{
	// Constructor & destructor
public:
	CTFullTextIndex();
	CTFullTextIndex(const CTFullTextIndex& pIndex);
	virtual ~CTFullTextIndex();

	// Operators
public:
	virtual CTFullTextIndex& operator=(const CTFullTextIndex& pIndex);

	// Methods
public:
	virtual void AddField(const CTField& pField, ULONG mode);
	virtual NINT GetFieldCount() const;
	virtual CTField GetField(NINT FieldNumber);
	virtual ULONG GetFieldMode(NINT FieldNumber);
	virtual ULONG GetStatus() const;
	virtual void SetOption(UCOUNT option, CTString &pvalue, ULONG lvalue);
	virtual NINT GetNumber();
	virtual CTString GetName();
};
/*^****************************************************************************\
*
*   CTFullTextIndexDictionary
*   CTDB C++ API Full Text index Dictonary class
*
\******************************************************************************/
class ctdbEXPORT CTFullTextIndexDictionary : public CTBase
{
	// Constructor & destructor
public:
	CTFullTextIndexDictionary(const CTSession &session);
	CTFullTextIndexDictionary(const CTDatabase &database);
	CTFullTextIndexDictionary(const CTTable &table);
	virtual ~CTFullTextIndexDictionary();

	// Methods
public:
	virtual void SetOption(UCOUNT option, CTString &pvalue, ULONG lvalue);
#ifdef REMOVED_20171012 /* option causing troubles and requiring path to be stored in resource. see devlog for further details*/
	virtual void Create(CTString &name, CTString &path, CTCREATE_MODE CreateMode);
#endif
};
/*^****************************************************************************\
*
*   CTHelloWorld
*   CTDB C++ API session class
*               Example class used to illustrate all the locations in the
*		code required when adding a new function. By grepping to code for
*		"CTDB HELLO WORLD" we can see all the places where we must touch
*		when ading a new CTDB function.
*
\******************************************************************************/
class ctdbEXPORT CTHelloWorld : public CTBase	/* CTDB HELLO WORLD */
{
    // Constructor & destructor
    public:
        CTHelloWorld();
        virtual ~CTHelloWorld();
        
    // Methods
    public:
        
	virtual void HelloWorld(const CTString& HelloFileName,const CTString& HelloTextData,
		NINT HelloNintData, ULONG HelloULongData, CTFLOAT HelloFloatData); /* CTDB HELLO WORLD */
		
	// Members
	private:
		VRLEN	m_hiworld;
};
/*~****************************************************************************/

#endif /* __cplusplus */
#endif /* ~_CTDBSDK_HPP */
