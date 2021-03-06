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
 *  Copyright (c) 2005 Vladimir Tsvigun
 *  All Rights Reserved.
 */

// ServiceManager.h: interface for the ServiceManager class.

#if !defined(_ServiceManager_H_)
#define _ServiceManager_H_

#define ADD_PARAM(par,code) \
			*par++ = code

#define ADD_PARAM_LEN32(par,code,val) \
			*par++ = code; \
			*par++ = (char)val; \
			*par++ = (char)(val >> 8); \
			*par++ = (char)(val >> 16); \
			*par++ = (char)(val >> 24)

#define ADD_PARAM_STRING_LEN8(par,code,string) \
			*par++ = code; \
			*par++ = (char)strlen( string ); \
			for ( pt = string; *pt; ) \
			  *par++ = *pt++

#define ADD_PARAM_STRING_LEN16(par,code,string) \
			*par++ = code; \
			*par++ = (char)strlen( string ); \
			*par++ = (char)(strlen( string ) >> 8); \
			for ( pt = string; *pt; ) \
			  *par++ = *pt++

namespace IscDbcLibrary {

#define RESPONSE_BUFFER 1024

class CServiceManager : public ServiceManager
{
public:
	Properties*	allocProperties() override;
	void startBackupDatabase( Properties *prop, unsigned options ) override;
	void startRestoreDatabase( Properties *prop, unsigned options ) override;
	void exitRestoreDatabase( void ) override;
	void startStaticticsDatabase( Properties *prop, unsigned options ) override;
	void startShowDatabaseLog( Properties *prop ) override;
	void startRepairDatabase( Properties *prop, unsigned options, unsigned optionsValidate ) override;
	void startUsersQuery( Properties *prop ) override;
	bool nextQuery( char *outBuffer, int length, int &lengthOut, int &countError ) override;
	bool nextQueryLimboTransactionInfo( char *outBuffer, int length, int &lengthOut ) override;
	bool nextQueryUserInfo( char *outBuffer, int length, int &lengthOut ) override;
	void closeService() override;
	int	getDriverBuildKey() override;

	void loadShareLibrary();
	void unloadShareLibrary();
	JString getIscStatusText( ISC_STATUS *statusVector );
	void addRef() override;
	int release() override;

	CServiceManager();
	virtual ~CServiceManager();

	CFbDll		*GDS;
	Properties	*properties;
	isc_svc_handle	svcHandle;
	int			useCount;
};

}; // end namespace IscDbcLibrary

#endif // !defined(_ServiceManager_H_)
