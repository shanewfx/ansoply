#pragma once
#include "ansoplyobject.h"

class CTextObject : 
	public CAnsoplyObject
{
	friend class CMultiSAP;
public:
	CTextObject();
	~CTextObject(void);

	void SetDDSFontCache(IDirectDrawSurface7*);
	IDirectDrawSurface7* GetDDSFontCache();
	void SetLogFont(const LOGFONT * logFont);
	LONG SetText(
		ULONG uX, 
		ULONG uY,
		LPCTSTR sText,
		LPCTSTR sFaceName, 
		ULONG uItalic, 
		ULONG uBold, 
		ULONG uUnderLine, 
		ULONG uWidth,
		ULONG uHeight,
		ULONG uColor);
	LOGFONT& GetFont();
	LPCTSTR GetText();
	LPCTSTR GetFaceName();
	ULONG GetTextLen();
	ULONG GetXCoordinate();
	ULONG GetYCoordinate();
	ULONG GetColor();
	ULONG GetItalic() { return m_uItalic; }
	ULONG GetBold() { return m_uBold; }
	ULONG GetUnderLine() { return m_uUnderLine;	}
	ULONG GetWidth() { return m_uWidth; }
	ULONG GetHeight() { return m_uHeight; }

	void  SetAlphaBlt(CAlphaBlt * pAlphaBlt)
	{
		m_pAlphaBlt = pAlphaBlt;
	}
	virtual void Draw();

	ULONG       m_uSurfaceWidth;
	ULONG       m_uSurfaceHeight;

	ULONG       m_uRegionWidth;
	ULONG       m_uRegionHeight;

private:
	IDirectDrawSurface7* m_pDDSFontCache;
	LOGFONT     m_logFont;
	TCHAR*      m_text;        // hold the text
	TCHAR       m_facename[32];
	ULONG		m_cx;
	ULONG		m_cy;
	ULONG       m_uItalic;
	ULONG       m_uBold;
	ULONG       m_uUnderLine;
	ULONG       m_uWidth;
	ULONG       m_uHeight;
	ULONG       m_uColor;



	CMultiSAP * m_pMultiSAP;

	CAlphaBlt* m_pAlphaBlt;
};

inline IDirectDrawSurface7* CTextObject::GetDDSFontCache()
{
	return m_pDDSFontCache;
}
