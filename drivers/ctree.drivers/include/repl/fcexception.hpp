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
 *      Copyright (c) 2013 - 2015 FairCom Corporation.
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
 */

#ifndef _FCEXCEPTION_HPP_
#define _FCEXCEPTION_HPP_

#include "fcerror.hpp"

/*^****************************************************************************\
*
*   FCException
*   Faircom exception class
*
*   Manages the Faircom exception
*
\******************************************************************************/
class FCException
{
	/* Constructors & destructor */
	public:
		FCException(int LogAgent, const char *AgentName, const char *FunctionName, int Level, int ErrorCode, const char *Message, const char *SourceFile, int LineNbr);
		FCException(const FCException &excep);
		virtual ~FCException();

	/* Methods */
	public:
		virtual int getLogAgent() const { return _logAgent; };
		virtual const char *getAgentName() const  { return _agentName; };
		virtual const char *getFunctionName() const  { return _functionName; };
		virtual int getLevel() const { return _level; };
		virtual int getErrorCode() const { return _error; };
		virtual const char *getMessage() const { return _message; };
		virtual const char *getSourceFile()const { return _file; };
		virtual int getLineNbr() const { return _line; };

		virtual void buildUserError( char *errorBuf );
		virtual void buildUserError(const char *errorMsg, char *errorBuf);

	/* Members */
	private:
		int _logAgent;
		char *_agentName;
		char *_functionName;
		int _level;
		int _error;
		char *_message;
		const char *_file;
		int _line;
};
/*~****************************************************************************/

/* Class type definitions */
typedef FCException *pFCException, **ppFCException;

#endif /* _FCEXCEPTION_HPP_ */