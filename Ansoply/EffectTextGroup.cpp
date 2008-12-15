#include "StdAfx.h"
#include ".\effecttextgroup.h"
#include "EffectTextEx.h"

CEffectTextGroup::CEffectTextGroup(void)
{
	m_iter = m_effectextlist.begin();
	InitializeCriticalSection(&m_cs);
}

CEffectTextGroup::~CEffectTextGroup(void)
{
	DeleteCriticalSection(&m_cs);
}

void CEffectTextGroup::Draw()
{
	if( m_effectextlist.size() == 0 )
		return;
	EnterCriticalSection(&m_cs);
	if( m_iter == m_effectextlist.end() )
		m_iter = m_effectextlist.begin();

	CEffectTextEx * pEffectText = *m_iter;
	if( GetTickCount() - pEffectText->m_nStart > pEffectText->m_uDelay )
	{
		pEffectText->m_nProgress += 1;
	}

	//if( pEffectBitmap->m_uPlayBeginTime > pEffectBitmap->m_uPlayTimes )
	{
		//////////////////////////////////////////////////////////////////////////
		if( pEffectText->m_bPlayEnd )
		{
			if( !pEffectText->m_endCountTime ) 
				pEffectText->m_endCountTime = GetTickCount();
			if( pEffectText->m_endtime != -1 && GetTickCount() - pEffectText->m_endCountTime > pEffectText->m_endtime )
			{
				//pEffectBitmap->m_endCountTime = GetTickCount();
				pEffectText->m_bPlayEnd = FALSE;
				pEffectText->m_actualPlayEnd = TRUE;
				pEffectText->m_nProgress = 0;
				pEffectText->m_bClear = TRUE;
				pEffectText->Clear();

				if( pEffectText->m_uPlayBeginTime > pEffectText->m_uPlayTimes )
				{
					pEffectText->m_uPlayBeginTime = 1;
					pEffectText->Clear();
					EnterCriticalSection(&m_cs);
					m_iter++;
					LeaveCriticalSection(&m_cs);
				}
			}
			else
			{
				pEffectText->m_nProgress = 100;
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
		if( pEffectText->m_bChangeStyle )
		{
			if( !pEffectText->m_endCountTime ) 
				pEffectText->m_endCountTime = GetTickCount();
			if( pEffectText->m_endtime != -1 && GetTickCount() - pEffectText->m_endCountTime > pEffectText->m_endtime )
			{
				pEffectText->m_bChangeStyle = FALSE;
				pEffectText->m_nProgress = 0;
				pEffectText->m_bClear = TRUE;
				if( pEffectText->m_drawtype == PLAY_RANDOM )
				{
					pEffectText->m_uDrawStyle = (rand() % 290) + 1;
				}
				else if( pEffectText->m_drawtype == PLAY_SEQUENCE )
				{
					pEffectText->m_uDrawStyle++;
					if( pEffectText->m_uDrawStyle > pEffectText->m_uDrawStyleEnd )
						pEffectText->m_uDrawStyle = pEffectText->m_uDrawStyleBegin;	
				}
				//drawproc = ::GetEffectProc(m_uDrawStyle);

				if( pEffectText->m_uPlayBeginTime > pEffectText->m_uPlayTimes )
				{
					pEffectText->m_uPlayBeginTime = 1;
					pEffectText->Clear();
					m_iter++;
				}

			}
			else
			{
				//m_bNxDraw = FALSE;
				pEffectText->m_nProgress = 100;
			}
		}
		//////////////////////////////////////////////////////////////////////////

	}

	pEffectText->Draw();

	LeaveCriticalSection(&m_cs);

}

void CEffectTextGroup::AddText(CEffectTextEx * pEffectText)
{
	EnterCriticalSection(&m_cs);
	m_effectextlist.push_back(pEffectText);
	LeaveCriticalSection(&m_cs);
}

void CEffectTextGroup::InsertText(ULONG uWhere, CEffectTextEx * pEffectText)
{
	EnterCriticalSection(&m_cs);
	std::list<CEffectTextEx*>::iterator iter = m_effectextlist.begin();
	for(; iter != m_effectextlist.end(); ++iter)
	{
		CEffectTextEx * pText = *iter;
		if( pText->GetObjectID() == uWhere )
		{
			m_effectextlist.insert(iter, pEffectText);
			break;
		}
	}
	LeaveCriticalSection(&m_cs);
}