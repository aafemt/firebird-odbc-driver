/*
 *  
 *     The contents of this file are subject to the Initial 
 *     Developer's Public License Version 1.0 (the "License"); 
 *     you may not use this file except in compliance with the 
 *     License. You may obtain a copy of the License at 
 *     http://www.ibphoenix.com/idpl.html. 
 *
 *     Software distributed under the License is distributed on 
 *     an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either 
 *     express or implied.  See the License for the specific 
 *     language governing rights and limitations under the License.
 *
 *
 *  The Original Code was created by Vladimir Tsvigun for IBPhoenix.
 *
 *  Copyright (c) 2003 Vladimir Tsvigun
 *  All Rights Reserved.
 */

// SupportFunctions.cpp: implementation of the SupportFunctions class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <windows.h>
#endif
#include <time.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "Mlist.h"
#include "SupportFunctions.h"

namespace IscDbcLibrary {

#define ADD_SUPPORT_FN( typeFn, key, nameSql, nameFb, translateFn )																	\
	fn.set( SupportFunctions::typeFn, key, nameSql, sizeof(nameSql)-1, nameFb, sizeof(nameFb)-1, &SupportFunctions::translateFn );	\
	if ( j = listSupportFunctions.SearchAndInsert( &fn ), j < 0 )																	\
		listSupportFunctions[-j-1] = fn																								\

SupportFunctions supportFn;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SupportFunctions::SupportFunctions()
{
	CSupportFunction fn;
	int j;
	supportFn = NULL;

//  String functions

    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_BIT_LENGTH, 		"BIT_LENGTH", 		"BIT_LENGTH",		defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_CHAR_LENGTH, 	"CHAR_LENGTH", 		"CHAR_LENGTH",		defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_CHARACTER_LENGTH,"CHARACTER_LENGTH", "CHARACTER_LENGTH",	defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_OCTET_LENGTH, 	"OCTET_LENGTH", 	"OCTET_LENGTH",		defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_POSITION, 		"POSITION", 		"POSITION",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_ASCII, 			"ASCII", 			"ASCII",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_CHAR, 			"CHAR", 			"CHAR",				defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_CONCAT, 			"CONCAT", 			"CONCAT",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_DIFFERENCE, 		"DIFFERENCE", 		"DIFFERENCE",		defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_INSERT, 			"INSERT", 			"INSERT",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_LCASE, 			"LCASE", 			"LCASE",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_LEFT, 			"LEFT", 			"LEFT",				defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_LENGTH, 			"LENGTH", 			"LENGTH",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_LOCATE, 			"LOCATE", 			"LOCATE",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_LOCATE_2, 		"LOCATE_2", 		"LOCATE_2",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_LTRIM, 			"LTRIM", 			"LTRIM",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_REPEAT, 			"REPEAT", 			"REPEAT",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_REPLACE, 		"REPLACE", 			"REPLACE",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_RIGHT, 			"RIGHT", 			"RIGHT",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_RTRIM, 			"RTRIM", 			"RTRIM",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_SOUNDEX, 		"SOUNDEX", 			"SOUNDEX",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_SPACE, 			"SPACE", 			"SPACE",			defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_SUBSTRING, 		"SUBSTRING", 		"SUBSTRING",		defaultTranslator);
    ADD_SUPPORT_FN( STR_FN, SQL_FN_STR_UCASE, 			"UCASE", 			"UPPER",			defaultTranslator);

//  Numeric functions

	ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_ABS, 		"ABS", 		"ABS",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_ACOS, 		"ACOS", 	"ACOS",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_ASIN, 		"ASIN", 	"ASIN",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_ATAN, 		"ATAN",		"ATAN",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_ATAN2, 		"ATAN2", 	"ATAN2",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_CEILING,		"CEILING",	"CEILING",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_COS,			"COS",		"COS",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_COT, 		"COT", 		"COT",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_DEGREES, 	"DEGREES", 	"DEGREES",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_EXP, 		"EXP", 		"EXP",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_FLOOR, 		"FLOOR", 	"FLOOR",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_LOG, 		"LOG", 		"LOG",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_LOG10, 		"LOG10", 	"LOG10",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_MOD, 		"MOD", 		"MOD",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_PI, 			"PI", 		"PI",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_POWER, 		"POWER", 	"POWER",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_RADIANS, 	"RADIANS", 	"RADIANS",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_RAND, 		"RAND", 	"RAND",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_ROUND, 		"ROUND", 	"ROUND",	defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_SIGN, 		"SIGN", 	"SIGN",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_SIN, 		"SIN", 		"SIN",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_SQRT, 		"SQRT", 	"SQRT",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_TAN, 		"TAN", 		"TAN",		defaultTranslator);
    ADD_SUPPORT_FN( NUM_FN, SQL_FN_NUM_TRUNCATE,	"TRUNCATE", "TRUNCATE", defaultTranslator);

//	Time and Date functions

    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_CURRENT_DATE, 		"CURRENT_DATE", 	"cast('now' as date)",		fullreplaceTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_CURRENT_TIME, 		"CURRENT_TIME", 	"cast('now' as time)",		fullreplaceTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_CURRENT_TIMESTAMP, "CURRENT_TIMESTAMP","cast('now' as timestamp)",	fullreplaceTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_CURDATE, 			"CURDATE", 			"cast('now' as date)",		fullreplaceTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_CURTIME, 			"CURTIME", 			"cast('now' as time)",		fullreplaceTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_DAYNAME, 			"DAYNAME", 			"DAYNAME",			defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_DAYOFMONTH, 		"DAYOFMONTH", 		"DAYOFMONTH",		defaultTranslator); 
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_DAYOFWEEK, 		"DAYOFWEEK", 		"DAYOFWEEK",		defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_DAYOFYEAR, 		"DAYOFYEAR", 		"DAYOFYEAR",		defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_EXTRACT, 			"EXTRACT", 			"EXTRACT",			defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_HOUR, 				"HOUR", 			"HOUR",				defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_MINUTE, 			"MINUTE", 			"MINUTE",			defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_MONTH, 			"MONTH", 			"MONTH",			defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_MONTHNAME, 		"MONTHNAME", 		"MONTHNAME",		defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_NOW, 				"NOW", 				"NOW",				defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_QUARTER,			"QUARTER",			"QUARTER",			defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_SECOND, 			"SECOND", 			"SECOND",			defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_TIMESTAMPADD, 		"TIMESTAMPADD", 	"TIMESTAMPADD",		defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_TIMESTAMPDIFF, 	"TIMESTAMPDIFF", 	"TIMESTAMPDIFF",	defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_WEEK, 				"WEEK", 			"WEEK",				defaultTranslator);
    ADD_SUPPORT_FN( TD_FN, SQL_FN_TD_YEAR, 				"YEAR", 			"YEAR",				defaultTranslator);

//  System functions

    ADD_SUPPORT_FN( SYS_FN, SQL_FN_SYS_DBNAME, 			"DBNAME", 			"DBNAME",			defaultTranslator);
    ADD_SUPPORT_FN( SYS_FN, SQL_FN_SYS_IFNULL, 			"IFNULL", 			"IFNULL",			defaultTranslator);
    ADD_SUPPORT_FN( SYS_FN, SQL_FN_SYS_USERNAME, 		"USER", 			"CURRENT_USER",		fullreplaceTranslator);
}

void SupportFunctions::translateNativeFunction ( char *&ptIn, char *&ptOut )
{
	CSupportFunction fn;

	while( *ptIn == ' ' )ptIn++;

	fn.nameSqlFn = ptIn;
	char * end = ptIn;

	while( *end != ' ' && *end != '(' )end++;
	fn.lenSqlFn = end - ptIn;

	int ret = listSupportFunctions.Search( &fn );
	if( ret != -1 )
	{
		supportFn = &listSupportFunctions[ ret ];
		(this->*supportFn->translate)( ptIn, ptOut );
	}
}

}; // end namespace IscDbcLibrary