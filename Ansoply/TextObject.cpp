#include "StdAfx.h"
#include "textobject.h"

CTextObject::CTextObject() :
m_pDDSFontCache(NULL),
m_text(NULL),
m_cx(0),
m_cy(0),
m_uItalic(0),
m_uBold(0),
m_uWidth(0),
m_uHeight(0),
m_uColor(0)
{
	ZeroMemory(m_facename, 32);
	ZeroMemory(&m_logFont, sizeof(m_logFont));

	SetObjectType(text);
}

CTextObject::~CTextObject(void)
{
	if (m_text)
		delete []m_text;
	if (m_pDDSFontCache)
		m_pDDSFontCache->Release();
}

void CTextObject::SetDDSFontCache(IDirectDrawSurface7* pDDS)
{
	m_pDDSFontCache = pDDS;
}

void CTextObject::SetLogFont(const LOGFONT * logFont)
{
	memcpy( &m_logFont, logFont, sizeof( LOGFONT ) );
}

LONG CTextObject::SetText(ULONG uX, 
						  ULONG uY, 
						  LPCTSTR sText, 
						  LPCTSTR sFaceName, 
						  ULONG uItalic, 
						  ULONG uBold, 
						  ULONG uUnderLine, 
						  ULONG uWidth,
						  ULONG uHeight, 
						  ULONG uColor)
{
	if ( m_text )
		delete []m_text;

	m_text = new TCHAR[ _tcslen(sText) + 1 ];
	if ( !m_text )
		return -1;

	_tcscpy(m_text, sText);
	_tcscpy(m_facename, sFaceName);
	m_text[_tcslen(sText)] = '\0';
	m_cx = uX;
	m_cy = uY;
	m_uItalic = uItalic;
	m_uBold   = uBold;
	m_uUnderLine = uUnderLine;
	m_uWidth = uWidth;
	m_uHeight = uHeight;
	m_uColor = uColor;
	return 0;
}

LOGFONT& CTextObject::GetFont()
{
	return m_logFont;
}

LPCTSTR CTextObject::GetText()
{
	return m_text;
}

LPCTSTR CTextObject::GetFaceName()
{
	return m_facename;
}

ULONG CTextObject::GetTextLen()
{
	if (!m_text)
	{
		return 0;
	}
	return _tcslen(m_text);
}

ULONG CTextObject::GetXCoordinate()
{
	return m_cx;
}

ULONG CTextObject::GetYCoordinate()
{
	return m_cy;
}

ULONG CTextObject::GetColor()
{
	return m_uColor;
}

void CTextObject::Draw()
{
	if( !m_bVisibility )
		return;

	HRESULT hr = E_FAIL;
	RECT srcRECT = {0, 0, m_uSurfaceWidth, m_uSurfaceHeight};
	RECT dstRECT = {0, 0, m_uSurfaceWidth, m_uSurfaceHeight};

	IDirectDrawSurface7* pDDS = GetDDSFontCache();
	if (pDDS)
	{
		BOOL bSelected = FALSE;
		if( m_pMultiSAP->m_lSelectGroupID == GetObjectID() )
			bSelected = TRUE;

		hr = m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00, bSelected, m_pMultiSAP->m_uSelectFrameColor);
	}
}
