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

// MultibyteConvert.h

#if !defined(_MultibyteConvert_H_)
#define _MultibyteConvert_H_

namespace IscDbcLibrary {

class MultibyteConvert;

class CMultibyteConvert
{
public:

	CMultibyteConvert()
	{
	}
};

MBSTOWCS adressMbsToWcs( int charsetCode );
WCSTOMBS adressWcsToMbs( int charsetCode );

size_t fss_mbstowcs( wchar_t *wcs, const char *mbs, size_t length );
size_t fss_wcstombs( char *mbs, const wchar_t *wcs, size_t length );
size_t utf8_mbstowcs( wchar_t *wcs, const char *mbs, size_t lengthForMBS );
size_t utf8_wcstombs( char *mbs, const wchar_t *wcs, size_t lengthForMBS );
size_t ascii_mbstowcs(wchar_t* wcs, const char* mbs, size_t length);
size_t ascii_wcstombs(char* mbs, const wchar_t* wcs, size_t length);

}; // end namespace IscDbcLibrary

#endif // !defined(_MultibyteConvert_H_)
