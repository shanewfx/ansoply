#pragma once
#include "bitmapobject.h"

class CMultiSAP;

class CEffectBitmapEx :
	public CBitmapObject
{
public:
	CEffectBitmapEx(void);
	~CEffectBitmapEx(void);

	virtual void Draw();

	void Clear();

	LONG SetBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay, HWND hWnd);

	LONG SetBitmap(CMultiSAP* pMultiSAP, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight);

	ULONG m_uDrawStyle;
	BOOL  m_bPlayEnd;
	BOOL  m_actualPlayEnd;
	BOOL  m_bLoopPlayEnd;
	BOOL  m_bClear;
	BOOL  m_bChangeStyle;

	BOOL  m_bNxDraw;

	HDC m_hdcBitmap;
	HDC tmphdcBitmap;

	Bitmap * m_pOriginalBMP;

	Graphics * m_pGraphics;

	PLAY_TYPE m_drawtype;
	ULONG m_uDrawStyleBegin;
	ULONG m_uDrawStyleEnd;

	LONG m_endtime;
	DWORD m_endCountTime;

	ULONG m_uOriginalSize;

	HBRUSH m_hbrFill;

	//	HEFFECTDRAW m_effectDraw;

	ULONG m_uDelay;

	DWORD m_nStart;

	int m_nProgress;
	HBITMAP m_hBmp;

	CRITICAL_SECTION m_cs;
};
