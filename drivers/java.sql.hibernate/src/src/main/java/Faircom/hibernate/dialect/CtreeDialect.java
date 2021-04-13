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
 *      Copyright (c) 1992 - 2017 FairCom Corporation.
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
package Faircom.hibernate.dialect;

import java.sql.CallableStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import org.hibernate.dialect.Dialect;
import org.hibernate.dialect.function.NoArgSQLFunction;
import org.hibernate.dialect.function.StandardSQLFunction;
import org.hibernate.dialect.function.VarArgsSQLFunction;
import org.hibernate.type.StandardBasicTypes;

/**
 * An SQL dialect for CtreeSQL.
 *
 * @author Faircom Corporation
 */
@SuppressWarnings("deprecation")
public class CtreeDialect extends Dialect {
    
	public CtreeDialect() {
		super();

                /*
                 * Ctree SQL data types
                 */
		registerColumnType( Types.BIT, "bit" );
		registerColumnType( Types.BOOLEAN, "bit" );
		registerColumnType( Types.TINYINT, "tinyint" );
		registerColumnType( Types.SMALLINT, "smallint" );
		registerColumnType( Types.INTEGER, "integer" );
		registerColumnType( Types.BIGINT, "bigint" );
		registerColumnType( Types.FLOAT, "float($p)" );
		registerColumnType( Types.DOUBLE, "float($p)" );
		registerColumnType( Types.NUMERIC, "numeric($p,$s)" );
		registerColumnType( Types.REAL, "real" );
		registerColumnType( Types.DATE, "date" );
		registerColumnType( Types.TIME, "time" );
		registerColumnType( Types.TIMESTAMP, "timestamp" );
		registerColumnType( Types.VARBINARY, "varbinary($l)" );
		registerColumnType( Types.LONGVARBINARY, "lvarbinary" );
		registerColumnType( Types.BLOB, "lvarbinary" );
		registerColumnType( Types.CHAR, "char($l)" );
		registerColumnType( Types.VARCHAR, "varchar($l)" );
		registerColumnType( Types.LONGVARCHAR, "lvarchar" );
		registerColumnType( Types.CLOB, "lvarchar" );

                /*
                 * Ctree Scalar SQL functions
                 */
                registerFunction( "abs", new StandardSQLFunction("abs") );
                registerFunction( "acos", new StandardSQLFunction("acos", StandardBasicTypes.DOUBLE) );
                registerFunction( "add_months", new StandardSQLFunction("add_months", StandardBasicTypes.DATE) );
                registerFunction( "ascii", new StandardSQLFunction("ascii", StandardBasicTypes.INTEGER) );
                registerFunction( "asin", new StandardSQLFunction("asin", StandardBasicTypes.DOUBLE) );
                registerFunction( "atan", new StandardSQLFunction("atan", StandardBasicTypes.DOUBLE) );
                registerFunction( "atan2", new StandardSQLFunction("atan2", StandardBasicTypes.DOUBLE) );
                registerFunction( "cast", new StandardSQLFunction("cast") );
                registerFunction( "ceiling", new StandardSQLFunction("ceiling") );
                registerFunction( "char", new StandardSQLFunction("char", StandardBasicTypes.CHARACTER) );
                registerFunction( "chartorowid", new StandardSQLFunction("chartorowid") );
                registerFunction( "chr", new StandardSQLFunction("chr", StandardBasicTypes.CHARACTER) );
                registerFunction( "chr", new StandardSQLFunction("chr", StandardBasicTypes.CHARACTER) );
                registerFunction( "coalesce", new StandardSQLFunction("coalesce") );
                registerFunction( "concat", new VarArgsSQLFunction(StandardBasicTypes.STRING, "", "||", "") );
                registerFunction( "cos", new StandardSQLFunction("cos", StandardBasicTypes.DOUBLE) );
                registerFunction( "curdate", new NoArgSQLFunction("curdate", StandardBasicTypes.DATE, false) );
                registerFunction( "current_date", new NoArgSQLFunction("current_date", StandardBasicTypes.DATE, false) );
                registerFunction( "current_timestamp", new NoArgSQLFunction("current_timestamp", StandardBasicTypes.TIMESTAMP, false) );
                registerFunction( "current_user", new NoArgSQLFunction("current_user", StandardBasicTypes.STRING, false) );
                registerFunction( "curtime", new NoArgSQLFunction("curtime", StandardBasicTypes.TIME, false) );
                registerFunction( "database", new NoArgSQLFunction("database", StandardBasicTypes.STRING, false) );
                registerFunction( "datalength", new StandardSQLFunction("datalength", StandardBasicTypes.SHORT) );
                registerFunction( "dateadd", new StandardSQLFunction("dateadd", StandardBasicTypes.DATE) );
                registerFunction( "datediff", new StandardSQLFunction("datediff", StandardBasicTypes.INTEGER) );
                registerFunction( "dayname", new StandardSQLFunction("dayname", StandardBasicTypes.STRING) );
                registerFunction( "dayofmonth", new StandardSQLFunction("dayofmonth", StandardBasicTypes.SHORT) );
                registerFunction( "dayofweek", new StandardSQLFunction("dayofweek", StandardBasicTypes.SHORT) );
                registerFunction( "dayofyear", new StandardSQLFunction("dayofyear", StandardBasicTypes.SHORT) );
                registerFunction( "db_name", new NoArgSQLFunction("db_name", StandardBasicTypes.STRING, false) );
                registerFunction( "decode", new StandardSQLFunction("decode") );
                registerFunction( "degrees", new StandardSQLFunction("degrees", StandardBasicTypes.DOUBLE) );
                registerFunction( "difference", new StandardSQLFunction("difference", StandardBasicTypes.INTEGER) );
                registerFunction( "exp", new StandardSQLFunction("exp", StandardBasicTypes.DOUBLE) );
                registerFunction( "floor", new StandardSQLFunction("floor") );
                registerFunction( "greatest", new StandardSQLFunction("greatest") );
                registerFunction( "hour", new StandardSQLFunction("hour", StandardBasicTypes.SHORT) );
                registerFunction( "ifnull", new StandardSQLFunction("ifnull") );
                registerFunction( "initcap", new StandardSQLFunction("initcap") );
                registerFunction( "insert", new StandardSQLFunction("insert", StandardBasicTypes.STRING) );
                registerFunction( "instr", new StandardSQLFunction("instr", StandardBasicTypes.INTEGER) );
                registerFunction( "isnull", new StandardSQLFunction("isnull") );
                registerFunction( "isnumeric", new StandardSQLFunction("isnumeric", StandardBasicTypes.BOOLEAN) );
                registerFunction( "last_day", new StandardSQLFunction("last_day", StandardBasicTypes.DATE) );
                registerFunction( "last_ident", new NoArgSQLFunction("last_ident", StandardBasicTypes.DOUBLE, false) );
                registerFunction( "lcase", new StandardSQLFunction("lcase") );
                registerFunction( "least", new StandardSQLFunction("least") );
                registerFunction( "left", new StandardSQLFunction("left") );
                registerFunction( "length", new StandardSQLFunction("length", StandardBasicTypes.SHORT) );
                registerFunction( "locate", new StandardSQLFunction("locate", StandardBasicTypes.SHORT) );
                registerFunction( "localtime", new StandardSQLFunction("localtime", StandardBasicTypes.TIME) );
                registerFunction( "localtimestamp", new StandardSQLFunction("localtimestamp", StandardBasicTypes.TIMESTAMP) );
                registerFunction( "log", new StandardSQLFunction("log", StandardBasicTypes.INTEGER) );
                registerFunction( "log10", new StandardSQLFunction("log10", StandardBasicTypes.INTEGER) );
                registerFunction( "lower", new StandardSQLFunction("lower") );
                registerFunction( "lpad", new StandardSQLFunction("lpad", StandardBasicTypes.STRING) );
                registerFunction( "ltrim", new StandardSQLFunction("ltrim") );
                registerFunction( "minute", new StandardSQLFunction("minute", StandardBasicTypes.SHORT) );
                registerFunction( "mod", new StandardSQLFunction("mod", StandardBasicTypes.INTEGER) );
                registerFunction( "monthname", new StandardSQLFunction("monthname", StandardBasicTypes.STRING) );
                registerFunction( "month", new StandardSQLFunction("month", StandardBasicTypes.SHORT) );
                registerFunction( "months_between", new StandardSQLFunction("months_between", StandardBasicTypes.FLOAT) );
                registerFunction( "next_day", new StandardSQLFunction("next_day", StandardBasicTypes.DATE) );
                registerFunction( "now", new NoArgSQLFunction("now", StandardBasicTypes.TIMESTAMP, false) );
                registerFunction( "nullif", new StandardSQLFunction("nullif") );
                registerFunction( "nvl", new StandardSQLFunction("nvl") );
                registerFunction( "octet_lenght", new StandardSQLFunction("octet_lenght", StandardBasicTypes.SHORT) );
                registerFunction( "overlay", new StandardSQLFunction("overlay") );
                registerFunction( "pi", new NoArgSQLFunction("pi", StandardBasicTypes.DOUBLE, false) );
                registerFunction( "power", new StandardSQLFunction("power", StandardBasicTypes.FLOAT) );
                registerFunction( "prefix", new StandardSQLFunction("prefix") );
                registerFunction( "quarter", new StandardSQLFunction("quarter", StandardBasicTypes.SHORT) );
                registerFunction( "radians", new StandardSQLFunction("radians", StandardBasicTypes.DOUBLE) );
                registerFunction( "rand", new StandardSQLFunction("rand", StandardBasicTypes.DOUBLE) );
                registerFunction( "repeat", new StandardSQLFunction("repeat", StandardBasicTypes.STRING) );
                registerFunction( "replace", new StandardSQLFunction("replace", StandardBasicTypes.STRING) );
                registerFunction( "right", new StandardSQLFunction("right", StandardBasicTypes.STRING) );
                registerFunction( "round", new StandardSQLFunction("round") );
                registerFunction( "rowid", new NoArgSQLFunction("rowid", StandardBasicTypes.LONG, false) );
                registerFunction( "rowidtochar", new StandardSQLFunction("rowidtochar", StandardBasicTypes.STRING) );
                registerFunction( "rpad", new StandardSQLFunction("rpad", StandardBasicTypes.STRING) );
                registerFunction( "rtrim", new StandardSQLFunction("rtrim") );
                registerFunction( "second", new StandardSQLFunction("second", StandardBasicTypes.SHORT) );
                registerFunction( "sign", new StandardSQLFunction("sign", StandardBasicTypes.INTEGER) );
                registerFunction( "sin", new StandardSQLFunction("sin", StandardBasicTypes.DOUBLE) );
                registerFunction( "soundex", new StandardSQLFunction("soundex") );
                registerFunction( "space", new StandardSQLFunction("space", StandardBasicTypes.STRING) );
                registerFunction( "sqrt", new StandardSQLFunction("sqrt", StandardBasicTypes.DOUBLE) );
                registerFunction( "substr", new StandardSQLFunction("substr", StandardBasicTypes.STRING) );
                registerFunction( "substring", new StandardSQLFunction( "substr", StandardBasicTypes.STRING ) );
                registerFunction( "suffix", new StandardSQLFunction("suffix") );
                registerFunction( "suser_name", new StandardSQLFunction("suser_name", StandardBasicTypes.STRING) );
                registerFunction( "sysdate", new NoArgSQLFunction("sysdate", StandardBasicTypes.DATE, false) );
                registerFunction( "systime", new NoArgSQLFunction("systime", StandardBasicTypes.TIME, false) );
                registerFunction( "systimestamp", new NoArgSQLFunction("systimestamp", StandardBasicTypes.TIMESTAMP, false) );
                registerFunction( "tan", new StandardSQLFunction("tan", StandardBasicTypes.DOUBLE) );
                registerFunction( "timestampadd", new StandardSQLFunction("timestampadd", StandardBasicTypes.TIMESTAMP) );
                registerFunction( "timestampdiff", new StandardSQLFunction("timestampdiff", StandardBasicTypes.INTEGER) );
                registerFunction( "to_char", new StandardSQLFunction("to_char", StandardBasicTypes.STRING) );
                registerFunction( "to_date", new StandardSQLFunction("to_date", StandardBasicTypes.DATE) );
                registerFunction( "to_number", new StandardSQLFunction("to_number", StandardBasicTypes.DOUBLE) );
                registerFunction( "to_time", new StandardSQLFunction("to_time", StandardBasicTypes.TIME) );
                registerFunction( "to_timestamp", new StandardSQLFunction("to_timestamp", StandardBasicTypes.TIMESTAMP) );
                registerFunction( "translate", new StandardSQLFunction("translate", StandardBasicTypes.STRING) );
                registerFunction( "trim", new StandardSQLFunction("trim") );
                registerFunction( "truncate", new StandardSQLFunction("truncate") );
                registerFunction( "ucase", new StandardSQLFunction("ucase") );
                registerFunction( "uid", new NoArgSQLFunction("uid", StandardBasicTypes.INTEGER, false) );
                registerFunction( "upper", new StandardSQLFunction("upper") );
                registerFunction( "user", new NoArgSQLFunction("user", StandardBasicTypes.STRING, false) );
                registerFunction( "user_name", new StandardSQLFunction("user_name", StandardBasicTypes.STRING) );
                registerFunction( "week", new StandardSQLFunction("week", StandardBasicTypes.SHORT) );
                registerFunction( "year", new StandardSQLFunction("year", StandardBasicTypes.SHORT) );
	}

	public String getAddColumnString() {
		return "add";
	}

	public String getForUpdateNowaitString() {
		return " for update nowait";
	}

	public boolean supportsLimit() {
		return true;
	}
        
	public boolean supportsLimitOffset() {
		return true;
	}
        
	public boolean supportsVariableLimit() {
		return false;
	}
        
	public String getLimitString(String querySelect, int offset, int limit) {
		String s = new StringBuilder( querySelect.length() + 10 ).append( querySelect )
                    .insert( querySelect.toLowerCase().indexOf( "select" ) + 6, " top " + limit + " skip " + offset )
                    .toString();
		return s;
	}

	public String getForUpdateString(String aliases) {
		return getForUpdateString() + " of " + aliases;
	}

	public String getForUpdateNowaitString(String aliases) {
		return getForUpdateString() + " of " + aliases + " nowait";
	}

	public boolean forUpdateOfColumns() {
		return true;
	}

	public ResultSet getResultSet(CallableStatement ps) throws SQLException {
		ps.execute();
		return ( ResultSet ) ps.getObject( 1 );
	}

	public boolean supportsUnionAll() {
		return true;
	}

	public boolean supportsCommentOn() {
		return true;
	}

	public boolean supportsTemporaryTables() {
		return true;
	}

	public String generateTemporaryTableName(String baseTableName) {
		String name = "HT_" + baseTableName;
		return name.length() > 30 ? name.substring( 1, 30 ) : name;
	}

	public String getCreateTemporaryTableString() {
		return "create global temporary table";
	}

	public String getCreateTemporaryTablePostfix() {
		return "on commit delete rows";
	}

	public boolean dropTemporaryTableAfterUse() {
		return false;
	}

	public boolean supportsCurrentTimestampSelection() {
		return true;
	}

	public String getCurrentTimestampSelectString() {
		return "select now()";
	}

	public boolean isCurrentTimestampSelectStringCallable() {
		return false;
	}

	public boolean supportsEmptyInList() {
		return false;
	}

	public boolean supportsExistsInSelect() {
		return false;
	}
        
	public boolean supportsIdentityColumns() {
		return true;
	}
	public String getIdentitySelectString() {
		return "select last_ident()";
	}
	public String getIdentityColumnString() {
		return "identity (0,1)"; // seed of 0 and increment of 1
	}

}
