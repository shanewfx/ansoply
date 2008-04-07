#include "StdAfx.h"
#include "project.h"
#include "videoobject.h"
#include ".\videoobject.h"

CVideoObject::CVideoObject() 
{
}

CVideoObject::~CVideoObject(void)
{
}

ULONG CVideoObject::GetCurrentPlayingPos(void)
{
	if( m_Ms )
	{
		LONGLONG curPos;
		m_Ms->GetCurrentPosition(&curPos);
		return curPos / 10000000;
	}
	return 0;
}
