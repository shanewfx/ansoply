#pragma once
#include "textobject.h"

class CEffectText :
	public CTextObject
{
public:
	CEffectText(void);
	~CEffectText(void);

	virtual void Draw();

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
		ULONG uDelay);

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
private:

	ULONG m_uDelay;

	DWORD m_nStart;

	int m_nProgress;
	HBITMAP m_hBmp;
	HFONT m_hFont;
};
