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

// IscStatementMetaData.h: interface for the IscStatementMetaData class.

#ifndef _ISCSTATEMENTMETADATA_H_
#define _ISCSTATEMENTMETADATA_H_

#include "Connection.h"

namespace IscDbcLibrary
{

class Sqlda;
class IscConnection;

class IscStatementMetaData : public StatementMetaData
{
public:
	int objectVersion() override;
	bool isNullable (int index) override;
	int getScale (int index) override;
	int getPrecision (int index) override;
	int getNumPrecRadix (int index) override;
	int getColumnType (int index, int &realSqlType) override;
	int getColumnCount() override;
	int getColumnDisplaySize(int index) override;
	const char* getColumnLabel(int index) override;
	const char* getSqlTypeName(int index) override;
	const char* getColumnName(int index) override;
	const char* getTableName(int index) override;
	const char* getColumnTypeName(int index) override;
	bool isSigned (int index) override;
	bool isReadOnly (int index) override;
	bool isWritable (int index) override;
	bool isDefinitelyWritable (int index) override;
	bool isCurrency (int index) override;
	bool isCaseSensitive (int index) override;
	bool isAutoIncrement (int index) override;
	bool isSearchable (int index) override;
	int	 isBlobOrArray(int index) override;
	bool isColumnPrimaryKey(int index) override;
	const char*	getSchemaName (int index) override;
	const char*	getCatalogName (int index) override;
	void getSqlData(int index, Blob *& ptDataBlob, HeadSqlVar *& ptHeadSqlVar) override;
	void createBlobDataTransfer(int index, Blob *& ptDataBlob) override;
	WCSTOMBS getAdressWcsToMbs( int index ) override;
	MBSTOWCS getAdressMbsToWcs( int index ) override;

	IscStatementMetaData(IscStatement *stmt, Sqlda *ptSqlda);
	virtual ~IscStatementMetaData() {}

	IscStatement	*statement;
	Sqlda			*sqlda;
};

}; // end namespace IscDbcLibrary

#endif // !defined(_ISCSTATEMENTMETADATA_H_)
