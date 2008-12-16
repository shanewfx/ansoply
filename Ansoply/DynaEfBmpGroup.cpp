#include "StdAfx.h"
#include ".\dynaefbmpgroup.h"
#include "EffectBitmapex.h"

CDynaEfBmpGroup::CDynaEfBmpGroup(void)
{
	m_bPlay = FALSE;
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

	//if( !m_bPlay )
	//	return;

	EnterCriticalSection(&m_cs);
	if( m_iter == m_effectbmplist.end() )
		m_iter = m_effectbmplist.begin();

	CEffectBitmapEx * pEffectBitmap = *m_iter;
	if( GetTickCount() - pEffectBitmap->m_nStart > pEffectBitmap->m_uDelay )
	{
		if( m_bPlay )
			pEffectBitmap->m_nProgress += 1;
	}

	//if( pEffectBitmap->m_uPlayBeginTime > pEffectBitmap->m_uPlayTimes )
	if( m_bPlay )
	{
		//////////////////////////////////////////////////////////////////////////
		if( pEffectBitmap->m_bPlayEnd )
		{
			if( !pEffectBitmap->m_endCountTime ) 
				pEffectBitmap->m_endCountTime = GetTickCount();
			if( pEffectBitmap->m_endtime != -1 && GetTickCount() - pEffectBitmap->m_endCountTime > pEffectBitmap->m_endtime )
			{
				//pEffectBitmap->m_endCountTime = GetTickCount();
				pEffectBitmap->m_bPlayEnd = FALSE;
				pEffectBitmap->m_actualPlayEnd = TRUE;
				pEffectBitmap->m_nProgress = 0;
				pEffectBitmap->m_bClear = TRUE;
				pEffectBitmap->Clear();

				if( pEffectBitmap->m_uPlayBeginTime > pEffectBitmap->m_uPlayTimes )
				{
					pEffectBitmap->m_uPlayBeginTime = 1;
					pEffectBitmap->Clear();
					EnterCriticalSection(&m_cs);
					m_iter++;
					LeaveCriticalSection(&m_cs);
				}
			}
			else
			{
				pEffectBitmap->m_nProgress = 100;
			}
		}
		//if( pEffectBitmap->m_bLoopPlayEnd )
		//{
		//	if( !pEffectBitmap->m_endCountTime ) 
		//		pEffectBitmap->m_endCountTime = GetTickCount();
		//	if( pEffectBitmap->m_endtime != -1 && GetTickCount() - pEffectBitmap->m_endCountTime > pEffectBitmap->m_endtime )
		//	{
		//		pEffectBitmap->m_bLoopPlayEnd = FALSE;
		//		pEffectBitmap->m_nProgress = 0;
		//		pEffectBitmap->m_bClear = TRUE;

		//		pEffectBitmap->Clear();
		//		if( pEffectBitmap->m_uPlayBeginTime > pEffectBitmap->m_uPlayTimes )
		//		{
		//			pEffectBitmap->m_uPlayBeginTime = 1;
		//			pEffectBitmap->Clear();
		//			m_iter++;
		//		}
		//	}
		//	else
		//		pEffectBitmap->m_nProgress = 100;
		//}
		if( pEffectBitmap->m_bChangeStyle )
		{
			if( !pEffectBitmap->m_endCountTime ) 
				pEffectBitmap->m_endCountTime = GetTickCount();
			if( pEffectBitmap->m_endtime != -1 && GetTickCount() - pEffectBitmap->m_endCountTime > pEffectBitmap->m_endtime )
			{
				pEffectBitmap->m_bChangeStyle = FALSE;
				pEffectBitmap->m_nProgress = 0;
				pEffectBitmap->m_bClear = TRUE;
				if( pEffectBitmap->m_drawtype == PLAY_RANDOM )
				{
					pEffectBitmap->m_uDrawStyle = (rand() % 290) + 1;
				}
				else if( pEffectBitmap->m_drawtype == PLAY_SEQUENCE )
				{
					pEffectBitmap->m_uDrawStyle++;
					if( pEffectBitmap->m_uDrawStyle > pEffectBitmap->m_uDrawStyleEnd )
						pEffectBitmap->m_uDrawStyle = pEffectBitmap->m_uDrawStyleBegin;	
				}
				//drawproc = ::GetEffectProc(m_uDrawStyle);

				if( pEffectBitmap->m_uPlayBeginTime > pEffectBitmap->m_uPlayTimes )
				{
					pEffectBitmap->m_uPlayBeginTime = 1;
					pEffectBitmap->Clear();
					m_iter++;
				}

			}
			else
			{
				//m_bNxDraw = FALSE;
				pEffectBitmap->m_nProgress = 100;
			}
		}
		//////////////////////////////////////////////////////////////////////////

	}
	if( m_bPlay || pEffectBitmap->m_nProgress != 0 )
		pEffectBitmap->Draw();

	LeaveCriticalSection(&m_cs);

	//pEffectBitmap->m_uPlayBeginTime++;
}

void CDynaEfBmpGroup::AddBitmap(CEffectBitmapEx * pEffectBitmap)
{
	EnterCriticalSection(&m_cs);
	m_effectbmplist.push_back(pEffectBitmap);
	LeaveCriticalSection(&m_cs);
}

void CDynaEfBmpGroup::InsertBitmap(ULONG uWhere, CEffectBitmapEx * pEffectBitmap)
{
	EnterCriticalSection(&m_cs);
	std::list<CEffectBitmapEx*>::iterator iter = m_effectbmplist.begin();
	for(; iter != m_effectbmplist.end(); ++iter)
	{
		CEffectBitmapEx * pBitmap = *iter;
		if( pBitmap->GetObjectID() == uWhere )
		{
			m_effectbmplist.insert(iter, pEffectBitmap);
			break;
		}
	}
	LeaveCriticalSection(&m_cs);
}
