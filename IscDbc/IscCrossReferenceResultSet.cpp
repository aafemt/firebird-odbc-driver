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
 *  The Original Code was created by James A. Starkey for IBPhoenix.
 *
 *  Copyright (c) 1999, 2000, 2001 James A. Starkey
 *  All Rights Reserved.
 */

// IscCrossReferenceResultSet.cpp: implementation of the IscCrossReferenceResultSet class.
//
//////////////////////////////////////////////////////////////////////

#include <string.h>
#include "IscDbc.h"
#include "IscCrossReferenceResultSet.h"
#include "IscDatabaseMetaData.h"

#define SQL_CASCADE				0
#define SQL_RESTRICT			1
#define SQL_SET_NULL			2
#define SQL_NO_ACTION			3
#define SQL_SET_DEFAULT			4

#define UPD_RULE		10
#define DEL_RULE		11

namespace IscDbcLibrary {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IscCrossReferenceResultSet::IscCrossReferenceResultSet(IscDatabaseMetaData *metaData)
		: IscMetaDataResultSet(metaData)
{

}

void IscCrossReferenceResultSet::getCrossReference (const char * primaryCatalog,
													const char * primarySchema,
													const char * primaryTable,
													const char * foreignCatalog,
													const char * foreignSchema,
													const char * foreignTable)
{
	char sql[4096] =
		"select cast (NULL as varchar(7)) as pktable_cat,\n"						// 1
				" cast (NULL as varchar(7)) as pktable_schem,\n"					// 2
				" cast (pkey.rdb$relation_name as varchar(31)) as pktable_name,\n"	// 3
				" cast (pseg.rdb$field_name as varchar(31)) as pkcolumn_name,\n"	// 4
				" cast (NULL as varchar(7)) as fktable_cat,\n"						// 5
				" cast (NULL as varchar(7)) as fktable_schem,\n"					// 6
				" cast (fkey.rdb$relation_name as varchar(31)) as fktable_name,\n"	// 7
				" cast (fseg.rdb$field_name as varchar(31)) as fkcolumn_name,\n"	// 8
				" cast (pseg.rdb$field_position+1 as smallint) as key_seq,\n"		// 9
				" cast (0 as smallint) as update_rule,\n"							// 10
				" cast (0 as smallint) as delete_rule,\n"							// 11
				" cast (fkey.rdb$constraint_name as varchar(31)) as fk_name,\n"		// 12
				" cast (refc.rdb$const_name_uq as varchar(31)) as pk_name,\n"		// 13
				" 7 as deferrability,\n"											// 14	SQL_NOT_DEFERRABLE
				" refc.rdb$update_rule,\n"											// 15
				" refc.rdb$delete_rule\n"											// 16

		"from rdb$relation_constraints fkey\n"
		" join rdb$ref_constraints refc on fkey.rdb$constraint_name = refc.rdb$constraint_name\n"
		" join rdb$relation_constraints pkey on refc.rdb$const_name_uq = pkey.rdb$constraint_name\n"
		" join rdb$indices fidx on fkey.rdb$index_name = fidx.rdb$index_name\n"
		" join rdb$indices pidx on pkey.rdb$index_name = pidx.rdb$index_name\n"
		" join rdb$index_segments fseg on fidx.rdb$index_name = fseg.rdb$index_name\n"
		" join rdb$index_segments pseg on pidx.rdb$index_name = pseg.rdb$index_name\n"
		"  and pseg.rdb$field_position = fseg.rdb$field_position\n"
		"where fkey.rdb$constraint_type = 'FOREIGN KEY'\n"
		"  and pkey.rdb$constraint_type = 'PRIMARY KEY'\n";

	char * ptFirst = sql + strlen(sql);

	// TODO: These parameters cannot be patterns by ODBC specs. Fix it!
	if (primaryTable && *primaryTable)
		expandPattern(ptFirst, " and ","pidx.rdb$relation_name", primaryTable);

	if (foreignTable && *foreignTable)
		expandPattern(ptFirst, " and ","fkey.rdb$relation_name", foreignTable);

	addString(ptFirst, "order by pkey.rdb$relation_name, fkey.rdb$relation_name, pseg.rdb$field_position\n");
	prepareStatement (sql);
	numberColumns = 14;
}

bool IscCrossReferenceResultSet::nextFetch()
{
	if (!IscResultSet::nextFetch())
		return false;

	int len;
	sqlda->updateShort ( 10, getRule ( sqlda->getText(15, len)) );
	sqlda->updateShort ( 11, getRule ( sqlda->getText(16, len)) );

	return true;
}

int IscCrossReferenceResultSet::getRule(const char * rule)
{
	if (stringEqual (rule, "CASCADE"))
		return SQL_CASCADE;

	if (stringEqual (rule, "RESTRICT"))
		return SQL_RESTRICT;

	if (stringEqual (rule, "SET NULL"))
		return SQL_SET_NULL;

	if (stringEqual (rule, "SET DEFAULT"))
		return SQL_SET_DEFAULT;

	return SQL_NO_ACTION;
}

bool IscCrossReferenceResultSet::stringEqual(const char * p1, const char * p2)
{
	while (*p1 && *p2)
		if (*p1++ != *p2++)
			return false;

	if (*p1 && *p1++ != ' ')
		return false;

	if (*p2 && *p2++ != ' ')
		return false;

	return true;
}

}; // end namespace IscDbcLibrary
