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

// ParametersEvents.h: interface for the ParametersEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ParametersEvents_H_)
#define _ParametersEvents_H_

#include "Connection.h"
#include "ParameterEvent.h"

namespace IscDbcLibrary {

class ParameterEvent;

class ParametersEvents : public PropertiesEvents
{
public:
	ParametersEvents();
	virtual ~ParametersEvents();

	void		putNameEvent( const char *name ) override;
	int			getCount() override;
	const char	*getNameEvent( int index ) override;
	int			findIndex( const char * name ) override;
	unsigned long getCountExecutedEvents( int index ) override;
	bool		isChanged( int index ) override;
	void		addRef() override;
	int			release() override;

	inline ParameterEvent *getHeadPosition( int pos = 0 );
	inline ParameterEvent *getNext();
	void clear();

public:
	int				useCount;
	ParameterEvent	*parameters;
	ParameterEvent	*parameterPositions;
	int				count;
};

inline
int ParametersEvents::getCount()
{
	return count;
}

inline
ParameterEvent* ParametersEvents::getHeadPosition( int pos )
{
	parameterPositions = parameters;

	while ( pos-- )
		parameterPositions = parameterPositions->nextParameter;

	return parameterPositions;
}

inline
ParameterEvent* ParametersEvents::getNext()
{
	if ( !parameterPositions )
		return NULL;

	return ( parameterPositions = parameterPositions->nextParameter );
}

}; // end namespace IscDbcLibrary

#endif // !defined(_ParametersEvents_H_)
