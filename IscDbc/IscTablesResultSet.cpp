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

// IscTablesResultSet.cpp: implementation of the IscTablesResultSet class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include "IscDbc.h"
#include "IscTablesResultSet.h"
#include "IscConnection.h"
#include "IscDatabaseMetaData.h"
#include "IscResultSet.h"
#include "IscPreparedStatement.h"
#include "IscBlob.h"

#define TABLE_TYPE	4
#define REMARKS		5

namespace IscDbcLibrary {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IscTablesResultSet::IscTablesResultSet(IscDatabaseMetaData *metaData)
		: IscMetaDataResultSet(metaData)
{
	sqlAllTypes = 0;
	currentRowAllTypes = 0;
}

void IscTablesResultSet::getTables(const char * catalog, const char * schemaPattern, const char * tableNamePattern, int typeCount, const char * * types)
{
	const char *sqlAll =  "%";
	char sql[2048] = "";
	const char* ptSql = sql;

	bool showTables = false, showSystemTables = false, showViews = false, showGTT = false;

	for (int i = 0; i < typeCount; i++)
	{
		if (strcmp(types[i], "TABLE") == 0)
		{
			showTables = true;
		}
		else if (strcmp(types[i], "VIEW") == 0)
		{
			showViews = true;
		}
		else if (strcmp(types[i], "SYSTEM TABLE") == 0)
		{
			showSystemTables = true;
		}
		else if (strcmp(types[i], "GLOBAL TEMPORARY") == 0)
		{
			showGTT = true;
		}
		else if (strcmp(types[i], sqlAll) == 0)
		{
			showTables = true;
			showViews = true;
			showSystemTables = true;
			showGTT = true;
			sqlAllTypes = typeCount == 1; // Let's not show types on "TABLE,%"
		}
		// else unknown table type is ignored

		// It is not clear from MS specs how to threat empty types list so let's make it
		// the same way as if it contained an unknown type, returning empty set.
	}

	// MSDN: "If TableType is SQL_ALL_TABLE_TYPES and CatalogName, SchemaName,
	// and TableName are *empty strings*, the result set contains a list of
	// valid table types for the data source.

	// On the other hand:
	// HYC00 	Optional feature not implemented
	// A catalog was specified, and the driver or data source does not support catalogs.
	// A schema was specified, and the driver or data source does not support schemas.
	// A string search pattern was specified for the catalog name, table schema, or table name,
	// and the data source does not support search patterns for one or more of those arguments.

	// Let's relax requirements and let NULLs be valid as catalogue and schema patterns.
	if (sqlAllTypes && tableNamePattern != nullptr && *tableNamePattern == '\0')
	{
		// NULL as a table name pattern does not filter names.

		ptSql = "select cast (NULL as varchar(7)) as table_cat,\n"		// 1
				"cast (NULL as varchar(7)) as table_schem,\n"			// 2
				"cast (NULL as varchar(31)) as table_name,\n"			// 3
				"cast ('' as varchar(20)) as table_type,\n"				// 4
				"cast (NULL as varchar(7)) as remarks\n"				// 5
				"from rdb$database tbl\n";
		currentRowAllTypes = 0;
	}
	else
	{
		sqlAllTypes = false; // Prevent types list from appearing by mistake

		char* pt = sql;
		addString(pt, "select cast(NULL as varchar(7)) as table_cat,\n"					// 1
					  "cast (NULL as varchar(7)) as table_schem,\n"						// 2
					  "cast (tbl.rdb$relation_name as varchar(31)) as table_name,\n"	// 3
					  "case when tbl.rdb$relation_type in (4,5) then cast('GLOBAL TEMPORARY' as varchar(20))"
					  " when tbl.rdb$system_flag>=1 and tbl.rdb$relation_type in (0,3) then cast('SYSTEM TABLE' as varchar(20))"
					  " when tbl.rdb$relation_type=1 then cast('VIEW' as varchar(20))"
					  " when tbl.rdb$relation_type=0 then cast('TABLE' as varchar(20))"
					  " end as table_type,\n"											// 4
					  "cast (NULL as varchar(255)) as remarks,\n"						// 5
					  "tbl.rdb$description as remarks_blob\n"							// 6
					  "from rdb$relations tbl\n"
					  "where (1=0\n");

		if (showTables)
		{
			addString(pt, " or (tbl.rdb$relation_type=0 and (tbl.rdb$system_flag=0 or tbl.rdb$system_flag is null))\n");
		}
		if (showViews)
		{
			addString(pt, " or (tbl.rdb$relation_type=1 and (tbl.rdb$system_flag=0 or tbl.rdb$system_flag is null))\n");
		}
		if (showSystemTables)
		{
			addString(pt, " or (tbl.rdb$relation_type in (0,3) and tbl.rdb$system_flag>=1)\n");
		}
		if (showGTT)
		{
			addString(pt, " or tbl.rdb$relation_type in (4,5)\n");
		}

		addString(pt, ")\n");

		if (tableNamePattern && *tableNamePattern && strcmp(tableNamePattern, sqlAll) != 0)
		{
			expandPattern(pt, " and ", "tbl.rdb$relation_name", tableNamePattern);
		}

		addString(pt, " order by 4,3");

	}

	prepareStatement (ptSql);
	numberColumns = 5;
}

bool IscTablesResultSet::nextFetch()
{
	if ( sqlAllTypes )
	{
		switch (currentRowAllTypes++)
		{
		case 0:
			{
				if (!IscResultSet::nextFetch())
					return false;

				sqlda->updateVarying (4, "GLOBAL TEMPORARY");
				break;
			}
		case 1:
			{
				sqlda->updateVarying (4, "SYSTEM TABLE");
				break;
			}
		case 2:
			{
				sqlda->updateVarying (4, "TABLE");
				break;
			}
		case 3:
			{
				sqlda->updateVarying (4, "VIEW");
				break;
			}
		default:
			{
				IscResultSet::close();
				return false;
			}
		}

		return true;
	}

	if (!IscResultSet::nextFetch())
		return false;

	if ( !sqlda->isNull(6) )
		convertBlobToString( 5, 6 );

	return true;
}

}; // end namespace IscDbcLibrary
