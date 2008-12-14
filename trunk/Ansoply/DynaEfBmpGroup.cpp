#include "StdAfx.h"
#include ".\dynaefbmpgroup.h"
#include "EffectBitmap.h"

CDynaEfBmpGroup::CDynaEfBmpGroup(void)
{
	m_iter = m_effectbmplist.begin();
	InitializeCriticalSection(&m_cs);
}

CDynaEfBmpGroup::~CDynaEfBmpGroup(void)
{
	DeleteCriticalSection(&m_cs);
}

void CDynaEfBmpGroup::Draw()
{
	if( m_effectbmplist.size() == 0 )
		return;

	if( m_iter == m_effectbmplist.end() )
		m_iter = m_effectbmplist.begin();

	CEffectBitmap * pEffectBitmap = *m_iter;

	pEffectBitmap->Draw();

	if( pEffectBitmap->m_uPlayBeginTime > pEffectBitmap->m_uPlayTimes )
	{
		pEffectBitmap->m_uPlayBeginTime = 1;
		m_iter++;
	}

	pEffectBitmap->m_uPlayBeginTime++;
}

void CDynaEfBmpGroup::AddBitmap(CEffectBitmap * pEffectBitmap)
{
	EnterCriticalSection(&m_cs);
	m_effectbmplist.push_back(pEffectBitmap);
	LeaveCriticalSection(&m_cs);
}
