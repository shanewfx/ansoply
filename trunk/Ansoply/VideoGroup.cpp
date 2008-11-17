#include "StdAfx.h"
#include "project.h"
#include "videogroup.h"
#include ".\videogroup.h"

CVideoGroup::CVideoGroup() : 
	m_hThread(NULL),
	m_curVideoObj(NULL),
	m_playEvent(PLAY_NONE),
	//m_uX(0),
	//m_uY(0),
	//m_uWidth(0),
	//m_uHeight(0),
	m_uAlpha(0),
	m_rate(1.0),
	m_bDefaultOutput(FALSE),
	m_PlayPauseEvent(NULL),
	m_pauseReset(FALSE),
	m_pMultiSAP(NULL)
{
	m_PlayPauseEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_StopTimeExpire = 0;

	SetObjectType(video);
}

CVideoGroup::~CVideoGroup(void)
{
	if (m_curVideoObj)
	{
		m_curVideoObj->StopMovie();
	}

	if ( m_hThread != NULL )
		TerminateThread(m_hThread, 0);

	list<CVideoObject*>::iterator i = m_videos.begin();

	while (i != m_videos.end())
	{
		CVideoObject* pVideoObject = *i;//m_videos.GetNextValue(pos);
		if (pVideoObject)
		{
			ReleaseFilter(pVideoObject);
			m_pMultiSAP->m_movieList.Delete(pVideoObject->m_dwUserID);
			delete pVideoObject;
		}
		i++;
	}
}

void   CVideoGroup::ReleaseFilter(CVideoObject * pObject)
{
	// Stop the graph.
	pObject->m_Mc->Stop();

	// Enumerate the filters in the graph.
	IEnumFilters *pEnum = NULL;
	HRESULT hr = pObject->m_Gb->EnumFilters(&pEnum);
	if (SUCCEEDED(hr))
	{
		IBaseFilter *pFilter = NULL;
		CComPtr<IGraphConfig>              GC; 
		pObject->m_Gb->QueryInterface(IID_IGraphConfig, (LPVOID *)&GC);
		while (S_OK == pEnum->Next(1, &pFilter, NULL))
		{
			// Remove the filter.
			//pVideoObject->m_Gb->RemoveFilter(pFilter);
			GC->RemoveFilterEx(pFilter, 0);
			// Reset the enumerator.
			pEnum->Reset();
			pFilter->Release();
		}
		pEnum->Release();
	}
	pObject->m_SAN->AdviseSurfaceAllocator(pObject->m_dwUserID, NULL);

	pObject->m_Gb = NULL;
	pObject->m_Bf = NULL;
	pObject->m_Fg = NULL;
	pObject->m_SAN = NULL;
	pObject->m_pAP = NULL;

	pObject->m_lpDDTexture = NULL ;
	pObject->m_lpDDDecode = NULL;

	//pObject->m_Mc = NULL;
	//pObject->m_Ms = NULL;
	//pObject->m_Me = NULL;
	//pObject->m_SAN->AdviseSurfaceAllocator(pObject->m_dwUserID, NULL);

	//pObject->CloseMovie();
	//pObject->Release();
}

LONG CVideoGroup::AddVideoObject(CVideoObject* pVideoObject)
{
//	size_t nCount = m_videos.GetCount();
//	if ( nCount < 9)
//	{
//		m_videos.AddTail( pVideoObject );
	m_videos.push_back(pVideoObject);
	return pVideoObject->GetObjectID();
//	}
//	return -1;
}

CVideoObject* CVideoGroup::GetVideoObject(ULONG uID)
{
	list<CVideoObject*>::iterator i = m_videos.begin();
	while (i != m_videos.end())
	{
		CVideoObject* pVideoObject = *i;
		if (pVideoObject->GetObjectID() == uID)
		{
			return pVideoObject;
		}
		i++;
	}
	return NULL;
}

LONG CVideoGroup::DelVideoFile(ULONG uID)
{
	list<CVideoObject*>::iterator i = m_videos.begin();
	while (i != m_videos.end())
	{
		CVideoObject* pVideoObject = *i;
		if (pVideoObject->GetObjectID() == uID )
		{
			m_threadIter = m_videos.erase(i);
			m_pMultiSAP->m_movieList.Delete(pVideoObject->m_dwUserID);
			if( pVideoObject == m_curVideoObj )  // if del the current playing video
			{
				Next();
			}

			//pVideoObject->m_SAN->RestoreDDrawSurfaces();

			ReleaseFilter(pVideoObject);
		
			delete pVideoObject;

			return 0;
		}
		// Silly BUG!!!!!!!
		i++;
	}
	return -1;
}

ULONG CVideoGroup::GetCount()
{
//	return m_videos.GetCount();
	return m_videos.size();
}

LONG CVideoGroup::Play()
{
	m_playEvent = PLAY_NONE;

	if ( !m_hThread )
	{
		//m_hThread = (HANDLE)_beginthread(SmoothPlayThread, 0, this);
		m_hThread = CreateThread(NULL, 0, SmoothPlayThread, this, 0, NULL);
		//  _beginthreadex returns 0 on an error.
		return m_hThread != 0 ? 0 : -1;
	}
	else
	{
        SetEvent( m_PlayPauseEvent );
	}
	return 0;
}

DWORD CVideoGroup::SmoothPlayThread(LPVOID param)
{
	ATLASSERT( param != NULL );
	CVideoGroup * pVideoGroup = (CVideoGroup*)param;

	do
	{
		if (pVideoGroup->m_videos.empty())
		{
			break;
		}

		//list<CVideoObject*>::iterator i = pVideoGroup->m_videos.begin();
		pVideoGroup->m_threadIter = pVideoGroup->m_videos.begin();
		while ( !pVideoGroup->m_videos.empty() && pVideoGroup->m_threadIter != pVideoGroup->m_videos.end() )
		{
			CVideoObject* videoObject = NULL;
			if (pVideoGroup->m_playEvent == PLAY_NONE)
			{
				videoObject = *pVideoGroup->m_threadIter;
				pVideoGroup->m_curVideoObj = videoObject;
			}
			else if (pVideoGroup->m_playEvent == PLAY_PREVIOUS)
			{
				pVideoGroup->m_playEvent = PLAY_NONE;
				if (pVideoGroup->m_threadIter != pVideoGroup->m_videos.begin())
				{
					pVideoGroup->m_threadIter--;
					videoObject = *pVideoGroup->m_threadIter;//pVideoGroup->m_videos.GetPreValue( pos );
					pVideoGroup->m_curVideoObj = videoObject;
				}
			}
			if (videoObject)
			{
				videoObject->PlayMovie(pVideoGroup->m_pauseReset);
				pVideoGroup->SetRate(pVideoGroup->m_rate);
				if( pVideoGroup->m_bDefaultOutput )
				{
					_beginthread(CMultiSAP::SetDefaultThread, 0, pVideoGroup);
				}
				else
				{
					pVideoGroup->SetVideoPosAndSize(
						pVideoGroup->m_uX,
						pVideoGroup->m_uY,
						pVideoGroup->m_uWidth,
						pVideoGroup->m_uHeight);
				}

				pVideoGroup->m_pauseReset = FALSE;

				long event;
				//videoObject->m_Me->WaitForCompletion(INFINITE, &event);

				HRESULT hr = E_ABORT;
				while ( hr == E_ABORT )
				{
					hr = videoObject->m_Me->WaitForCompletion(2000, &event);
					if( pVideoGroup->m_StopTimeExpire && GetTickCount() > pVideoGroup->m_StopTimeExpire )
						goto END;
				}

				if (pVideoGroup->m_playEvent == PLAY_TERMINATE)
				{
					pVideoGroup->m_playType = PLAY_THROUGH;
					pVideoGroup->m_uPlayTimes = 0;
					break;
				}
				if( pVideoGroup->m_playEvent == PLAY_PAUSE )
				{
					DWORD dwBegin = GetTickCount();
					WaitForSingleObject(pVideoGroup->m_PlayPauseEvent, INFINITE);
					pVideoGroup->m_playEvent = PLAY_NONE;
					if (pVideoGroup->m_StopTimeExpire)
					{
						pVideoGroup->m_StopTimeExpire += (GetTickCount() - dwBegin);
					}
					continue;
				}
				if (pVideoGroup->m_playEvent == PLAY_PREVIOUS)
				{
					continue;
				}
				if( pVideoGroup->m_threadIter == pVideoGroup->m_videos.end() )
					break;
				pVideoGroup->m_threadIter++;
			}
		}
	}while ( pVideoGroup->m_playType == PLAY_LOOP || pVideoGroup->m_uPlayBeginTime++ < pVideoGroup->m_uPlayTimes );

END:
	pVideoGroup->m_curVideoObj = NULL;
	//CloseHandle(pVideoGroup->m_hThread);
	pVideoGroup->m_hThread = NULL;

	return 0;
}

CVideoObject * CVideoGroup::GetCurVideoObj(void)
{
	return m_curVideoObj;
}

void CVideoGroup::Stop(void)
{
//	if (m_curVideoObj) m_curVideoObj->StopMovie();
	if (m_curVideoObj)
	{	
		m_StopTimeExpire = 0;
		m_playEvent = PLAY_TERMINATE;
		m_curVideoObj->SeekToPosition(m_curVideoObj->GetDuration(), TRUE);
	}
}

void CVideoGroup::Pause(void)
{
	if (m_curVideoObj)
	{
		m_playEvent = PLAY_PAUSE;
		ResetEvent( m_PlayPauseEvent );

		m_curVideoObj->PauseMovie();

		m_pauseReset = TRUE;
	}
}

REFTIME CVideoGroup::GetPosition(void)
{
	if (m_curVideoObj) 
	{
		return m_curVideoObj->GetCurrentPosition();
	}
	return 0;
}

int CVideoGroup::SetVideoPosAndSize(unsigned long uX, 
									unsigned long uY, 
									unsigned long uWidth, 
									unsigned long uHeight)
{
	m_uX = uX;
	m_uY = uY;
	m_uWidth = uWidth;
	m_uHeight = uHeight;	

	return 0;
}

LONG CVideoGroup::GetVideoPosAndSize(ULONG* uX, ULONG* uY, ULONG* uWidth, ULONG* uHeight)
{
	*uX = m_uX;
	*uY = m_uY;
	*uWidth = m_uWidth;
	*uHeight = m_uHeight;

	return 0;
}

LONG CVideoGroup::GetFirstVideoObjectID()
{
//	if (m_videos.IsEmpty()) return -1;
//	POSITION pos = m_videos.GetStartPosition();
//	CVideoObject* pVideoObject = m_videos.GetNextValue(pos);
	if (m_videos.empty()) return -1;
	list<CVideoObject*>::iterator i = m_videos.begin();
	return (*i)->GetObjectID();
}

LONG CVideoGroup::GetNextVideoObjectID(ULONG & uObjectID)
{
//	if (m_videos.IsEmpty()) return -1;
//	POSITION pos = m_videos.GetStartPosition();
	if (m_videos.empty()) return -1;
	list<CVideoObject*>::iterator i = m_videos.begin();
	
	while (i != m_videos.end())
	{
		CVideoObject* pVideoObject = *i;//m_videos.GetNextValue(pos);
		if (pVideoObject)
		{
			if (pVideoObject->GetObjectID() == uObjectID)
			{
				list<CVideoObject*>::iterator nextIter = i;
				nextIter++;
				if (nextIter != m_videos.end())
				{
					CVideoObject* pVideoObject = *nextIter;//m_videos.GetNextValue(pos);
					if (pVideoObject)
					{
						uObjectID = pVideoObject->GetObjectID();
						return 0;
					}
				}
			}
		}
		i++;
	}
	uObjectID = 0;
	return 0;
}

LONG CVideoGroup::SetVideoAlpha(ULONG uAlpha)
{
	if (uAlpha < 0x0 || uAlpha > 0xFF)
	{
		return -1;
	}
	m_uAlpha = uAlpha;
	return 0;
}

LONG CVideoGroup::GetVideoAlpha(ULONG& uAlpha)
{
	uAlpha = m_uAlpha;
	return 0;
}

LONG CVideoGroup::SetPlayMode(ULONG uPlayMode)
{
	if (PLAY_THROUGH == uPlayMode || PLAY_LOOP == uPlayMode)
	{
		m_playType = (PLAY_TYPE)uPlayMode;
		if( PLAY_THROUGH == uPlayMode )
			m_uPlayTimes = 0;
		return 0;
	}
	return -1;
}

LONG CVideoGroup::SetPlayTimes(ULONG uPlayTimes)
{
	m_uPlayBeginTime = 1;
	m_uPlayTimes = uPlayTimes;

	m_StopTimeExpire = 0;

	m_playType = (PLAY_TYPE)PLAY_THROUGH;
	return 0;
}

LONG CVideoGroup::SetPlayTimeout(ULONG uTimeout_s)
{
	m_StopTimeExpire = GetTickCount() + uTimeout_s * 1000;
	return 0;
}

LONG CVideoGroup::Previous()
{
	if (m_curVideoObj)
	{
		m_playEvent = PLAY_PREVIOUS;
		m_curVideoObj->SeekToPosition(m_curVideoObj->GetDuration(), TRUE);
		return 0;
	}
	return -1;
}

LONG CVideoGroup::Next()
{
	if (m_curVideoObj)
	{
//		m_curVideoObj->StopMovie();
		m_curVideoObj->SeekToPosition(m_curVideoObj->GetDuration(), TRUE);
		return 0;
	}
	return -1;
}

LONG CVideoGroup::Seek(ULONG uPosition)
{
	if (m_curVideoObj)
	{
		m_curVideoObj->SeekToPosition(uPosition, TRUE);
		return 0;
	}
	return -1;	
}

LONG CVideoGroup::SetRate(DOUBLE rate)
{
	m_rate = rate;
	if ( m_curVideoObj && m_curVideoObj->m_Ms )
	{
		return m_curVideoObj->m_Ms->SetRate(rate);
	}
	return -1;
}

LONG CVideoGroup::GetVideoLength(ULONG uFileID, DOUBLE* uLength)
{
	CVideoObject* pVideoObject = GetVideoObject(uFileID);
	if (pVideoObject)
	{
		*uLength = pVideoObject->GetDuration();
		return 0;
	}
	return -1;
}

LONG CVideoGroup::GetPlayMode(ULONG& uPlayMode)
{
	uPlayMode = (ULONG)m_playType;
	return 0;
}

LONG CVideoGroup::GetRate(DOUBLE& rate)
{
	rate = m_rate;
	return 0;
}

void CVideoGroup::Draw()
{
	CVideoObject * pMovie = m_curVideoObj;

	if( !m_bVisibility )
		return;
	if( !pMovie || !pMovie->m_lpDDTexture )
		return;

	BOOL bSelectedChannel = FALSE;
	if (GetObjectID() == m_pMultiSAP->m_lSelectGroupID)
		bSelectedChannel = TRUE;

	ULONG cX, cY, uWidth, uHeight, uAlpha;
	GetVideoPosAndSize(&cX, &cY, &uWidth, &uHeight);
	GetVideoAlpha(uAlpha);

	//ATLTRACE("Movie: %d X:%d Y:%d Width:%d Height:%d\n", pMovie, cX, cY, uWidth, uHeight);

	pMovie->m_Vcur[0].x = cX;
	pMovie->m_Vcur[0].y = cY;

	pMovie->m_Vcur[1].x = cX + uWidth;
	pMovie->m_Vcur[1].y = cY;

	pMovie->m_Vcur[2].x = cX;
	pMovie->m_Vcur[2].y = cY + uHeight;

	pMovie->m_Vcur[3].x = cX + uWidth;
	pMovie->m_Vcur[3].y = cY + uHeight;

	RECT rt;
	rt.left = cX;
	rt.top = cY;
	rt.right = cX + m_uSurfaceWidth;
	rt.bottom = cY + m_uSurfaceHeight;

	m_pD3DHelper->RenderFrame( pMovie->m_lpDDTexture, 
		pMovie->m_Vcur, 
		m_rcDst, 
		rt,
		//m_movieList.GetDefaultTarget(),
		uAlpha,
		bSelectedChannel,
		m_pMultiSAP->m_uSelectFrameColor);
}
LONG CVideoGroup::GetCurrentFileID(LONG * uFileID)
{
	if( m_curVideoObj )
		*uFileID = m_curVideoObj->GetObjectID();
	else
		*uFileID = -1;
	return 0;
}

LONG CVideoGroup::GetCurrentPlayingPos(ULONG * uCurPos)
{
	if( m_curVideoObj )
		*uCurPos = m_curVideoObj->GetCurrentPlayingPos();
	else
		*uCurPos = 0;
	return 0;
}

LONG CVideoGroup::SetVideoFile(CVideoObject * pObject, ULONG uOldFileID)
{
	list<CVideoObject*>::iterator i = m_videos.begin();
	while (i != m_videos.end())
	{
		CVideoObject* pVideoObject = *i;
		if (pVideoObject->GetObjectID() == uOldFileID )
		{
			m_threadIter = m_videos.erase(i);

			m_videos.insert(m_threadIter, pObject);

			m_pMultiSAP->m_movieList.Delete(pVideoObject->m_dwUserID);
			if( pVideoObject == m_curVideoObj )  // if del the current playing video
			{
				Next();
			}

			ReleaseFilter(pVideoObject);

			delete pVideoObject;


			return 0;
		}
		i++;
	}
	return -1;
}