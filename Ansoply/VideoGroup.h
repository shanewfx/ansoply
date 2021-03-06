#pragma once
#include "movie.h"
#include "ansoplyobject.h"
#include "VideoObject.h"
#include <list>
using namespace std;


class CVideoGroup : 
	public CAnsoplyObject
{
	friend class CMultiSAP;
	friend DWORD SmoothPlayThread(LPVOID param);
public:
	CVideoGroup();
	virtual ~CVideoGroup(void);
	
	LONG AddVideoObject(CVideoObject* pVideoObject);
	CVideoObject* GetVideoObject(ULONG uID);
	LONG DelVideoFile(ULONG uID);
	ULONG GetCount();
	LONG Play();
	CVideoObject * GetCurVideoObj(void);
	void    Stop(void);
	void    Pause(void);
	REFTIME GetPosition(void);
	int		SetVideoPosAndSize(unsigned long uX, unsigned long uY, unsigned long uWidth, unsigned long uHeight);
	LONG	GetVideoPosAndSize(ULONG* uX, ULONG* uY, ULONG* uWidth, ULONG* uHeight);
	LONG	GetFirstVideoObjectID();
	LONG	GetNextVideoObjectID(ULONG & uObjectID);
	LONG	SetVideoAlpha(ULONG uAlpha);
	LONG	GetVideoAlpha(ULONG& uAlpha);
	LONG	SetPlayMode(ULONG uPlayMode);
	LONG	GetPlayMode(ULONG& uPlayMode);
	LONG	Previous();
	LONG	Next();
	LONG	Seek(ULONG uPosition);
//	BOOL	SelectGroup(LONG cX, LONG cY);
	LONG	SetRate(DOUBLE rate);
	LONG	GetRate(DOUBLE& rate);
	LONG	GetVideoLength(ULONG uFileID, DOUBLE* uLength);
	LONG    SetPlayTimes(ULONG uPlayTimes);
	LONG    SetPlayTimeout(ULONG uTimeout_s);

	virtual void Draw();
	ULONG       m_uSurfaceWidth;
	ULONG       m_uSurfaceHeight;
	CD3DHelper* m_pD3DHelper;
	RECT        m_rcDst;
	CMultiSAP * m_pMultiSAP;

	list<CVideoObject*>::iterator m_threadIter;
protected:
	static DWORD WINAPI SmoothPlayThread(LPVOID param);

	void   ReleaseFilter(CVideoObject * pObject);

private:
	HANDLE m_hThread;
//	CAtlList<ULONG, CVideoObject*> m_videos;
	list<CVideoObject*> m_videos;
	CVideoObject*                 m_curVideoObj;

	HANDLE      m_PlayPauseEvent;


	PLAY_TYPE	m_playEvent;

	BOOL        m_pauseReset;
	DOUBLE		m_rate;
	ULONG       m_uLevel;
	ULONG		m_uAlpha;

	//ULONG		m_uRate;

	//ULONG		m_uX;
	//ULONG		m_uY;
	//ULONG		m_uWidth;
	//ULONG		m_uHeight;

	BOOL        m_bDefaultOutput;
public:
	LONG GetCurrentFileID(LONG * uFileID);
	LONG GetCurrentPlayingPos(ULONG * uCurPos);
	LONG SetVideoFile(CVideoObject * pObject, ULONG uOldFileID);
};
