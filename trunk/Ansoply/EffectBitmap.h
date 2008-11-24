#pragma once
#include "BitmapObject.h"

class CEffectBitmap :
	public CBitmapObject
{
public:
	CEffectBitmap(void);
	~CEffectBitmap(void);

	virtual void Draw();

	LONG SetBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay, HWND hWnd);

	ULONG m_uDrawStyle;
	BOOL  m_bPlayEnd;
	BOOL  m_actualPlayEnd;
	BOOL  m_bLoopPlayEnd;
	BOOL  m_bClear;
	BOOL  m_bChangeStyle;

	PLAY_TYPE m_drawtype;
	ULONG m_uDrawStyleBegin;
	ULONG m_uDrawStyleEnd;

	LONG m_endtime;
	DWORD m_endCountTime;
private:
//	HEFFECTDRAW m_effectDraw;

	ULONG m_uDelay;

	DWORD m_nStart;

	int m_nProgress;
	HBITMAP m_hBmp;
};
