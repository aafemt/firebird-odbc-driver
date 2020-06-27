/*
 *
 *     The contents of this file are subject to the Initial
 *     Developer's Public License Version 1.0 (the "License");
 *     you may not use this file except in compliance with the
 *     License. You may obtain a copy of the License at
 *     http://www.ibphoenix.com/main.nfs?a=ibphoenix&page=ibp_idpl.
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

// IscHeadSqlVar.h: interface for the IscHeadSqlVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ISCHEADSQLVAR_H_)
#define _ISCHEADSQLVAR_H_

#include "Sqlda.h"

namespace IscDbcLibrary {

#define MAKEHEAD(a, b, c, d)	\
{								\
    sqlvar->sqltype = a + 1;	\
    sqlvar->sqlscale = b;		\
    sqlvar->sqlsubtype = c;		\
    sqlvar->sqllen = d;			\
}

class IscHeadSqlVar : public HeadSqlVar
{
	XSQLVAR		*sqlvar;
	char		*saveSqldata;
	short		*saveSqlind;
	bool		replaceForParamArray;
	short		sqlMultiple;

public:

	IscHeadSqlVar( CAttrSqlVar *attrVar )
	{
		sqlvar = attrVar->varOrg;
		saveSqldata = sqlvar->sqldata;
		saveSqlind = sqlvar->sqlind;
		replaceForParamArray = attrVar->replaceForParamArray;

		if ( !(sqlvar->sqllen % getCharsetSize( sqlvar->sqlsubtype )) )
			sqlMultiple = getCharsetSize( sqlvar->sqlsubtype );
		else
			sqlMultiple = 1;
	}
	virtual ~IscHeadSqlVar() {}

	void		setTypeText()	 override	{ MAKEHEAD(SQL_TEXT, 0, 0, 0); }
	void		setTypeVarying() override	{ MAKEHEAD(SQL_VARYING, 0, 0, 0); }
	void		setTypeBoolean() override	{ MAKEHEAD(SQL_BOOLEAN, 0, 0, sizeof(TYPE_BOOLEAN)); }
	void		setTypeShort()	 override	{ MAKEHEAD(SQL_SHORT, 0, 0, sizeof (short)); }
	void		setTypeLong()	 override	{ MAKEHEAD(SQL_LONG, 0, 0, sizeof (int)); }
	void		setTypeFloat()	 override	{ MAKEHEAD(SQL_FLOAT, 0, 0, sizeof (float)); }
	void		setTypeDouble()	 override	{ MAKEHEAD(SQL_DOUBLE, 0, 0, sizeof (double)); }
	void		setType_D_Float() override	{ MAKEHEAD(SQL_D_FLOAT, 0, 0, sizeof (double)); }
	void		setTypeTimestamp() override	{ MAKEHEAD(SQL_TIMESTAMP, 0, 0, sizeof (ISC_TIMESTAMP)); }
	void		setTypeBlob()	 override	{ MAKEHEAD(SQL_BLOB, 0, 0, sizeof (ISC_QUAD)); }
	void		setTypeArray()	 override	{ MAKEHEAD(SQL_ARRAY, 0, 0, sizeof (ISC_QUAD)); }
	void		setTypeQuad()	 override	{ MAKEHEAD(SQL_QUAD, 0, 0, sizeof (QUAD)); }
	void		setTypeTime()	 override	{ MAKEHEAD(SQL_TYPE_TIME, 0, 0, sizeof (ISC_TIME)); }
	void		setTypeDate()	 override	{ MAKEHEAD(SQL_TYPE_DATE, 0, 0, sizeof (ISC_DATE)); }
	void		setTypeInt64()	 override	{ MAKEHEAD(SQL_INT64, 0, 0, sizeof (QUAD)); }

	void		setSqlType ( short type ) override { sqlvar->sqltype = type; }
	void		setSqlScale ( short scale ) override { sqlvar->sqlscale = scale; }
	void		setSqlSubType ( short subtype ) override { sqlvar->sqlsubtype = subtype; }
	void		setSqlLen ( short len ) override { sqlvar->sqllen = len; }
	short		getSqlMultiple () override { return sqlMultiple; }

	char *		getSqlData() override { return sqlvar->sqldata; }
	short *		getSqlInd() override { return sqlvar->sqlind; }
	void		setSqlData( char *data ) override { sqlvar->sqldata = data; }
	void		setSqlInd( short *ind ) override { sqlvar->sqlind = ind; }

	bool		isReplaceForParamArray () override { return replaceForParamArray; }

	void		release() override { delete this; }
	void		restoreOrgPtrSqlData() override { sqlvar->sqldata = saveSqldata;	sqlvar->sqlind = saveSqlind; }
};

}; // end namespace IscDbcLibrary

#endif // !defined(_ISCHEADSQLVAR_H_)
