#pragma once
#include "textobject.h"

class CMultiSAP;

class CEffectTextEx :
	public CTextObject
{
public:
	CEffectTextEx(void);
	~CEffectTextEx(void);

	virtual void Draw();

	void Clear();

	LONG SetText(ULONG uX, 
		ULONG uY, 
		LPCTSTR sText, 
		LPCTSTR sFaceName, 
		ULONG uItalic, 
		ULONG uBold, 
		ULONG uUnderLine, 
		ULONG uWidth,
		ULONG uHeight, 
		ULONG uColor,
		ULONG uDrawStyle,
		ULONG uDelay, 
		ULONG uAlpha, 
		ULONG uTransparentColor);

	LONG SetText(CMultiSAP * pMultiSAP,
		ULONG uX,
		ULONG uY,
		LPCTSTR sFaceName,
		ULONG uItalic,
		ULONG uBold,
		ULONG uUnderLine,
		ULONG uWidth,
		ULONG uHeight,
		ULONG uColor,
		ULONG uAlpha, 
		ULONG uTransparentColor,
		ULONG uRegionWidth, ULONG uRegionHeight);

	ULONG m_uDrawStyle;
	BOOL  m_bPlayEnd;
	BOOL  m_bLoopPlayEnd;
	BOOL  m_actualPlayEnd;
	BOOL  m_bClear;
	BOOL  m_bChangeStyle;

	PLAY_TYPE m_drawtype;
	ULONG m_uDrawStyleBegin;
	ULONG m_uDrawStyleEnd;
	LONG  m_endtime;
	DWORD m_endCountTime;

	HDC m_hdcText;

	ULONG m_uDelay;

	DWORD m_nStart;

	HBRUSH m_hbrFill;

	int m_nProgress;
	HBITMAP m_hBmp;
	HFONT m_hFont;

	CRITICAL_SECTION m_cs;

	ULONG m_uTransparentColor;
};
