#include "StdAfx.h"
//#include "project.h"
#include "bitmapobject.h"

CBitmapObject::CBitmapObject() : 
	m_pBitmap(NULL),
	m_uAlpha(0),
	m_uTransparentColor(0),
	//m_uX(0),
	//m_uY(0),
	m_pDDS(NULL)
{
	SetObjectType(bitmap);
}

CBitmapObject::~CBitmapObject(void)
{
	if (m_pDDS)m_pDDS->Release();


}

IDirectDrawSurface7* CBitmapObject::GetSurface()
{
	return m_pDDS;
}

void CBitmapObject::SetSurface(IDirectDrawSurface7* pSurface)
{
	m_pDDS = pSurface;
}

LONG CBitmapObject::SetBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize)
{
	USES_CONVERSION;
	m_pBitmap = Bitmap::FromFile( T2W(sBitmapFilePath), FALSE );
	if (m_pBitmap)
	{
		m_sFilePath = sBitmapFilePath;
		m_uAlpha = uAlpha;
		m_uTransparentColor = uTransparentColor;
		m_uX = uX;
		m_uY = uY;

		if( uOriginalSize == 1 )
		{
			HBITMAP hBmp;
			Color backColor;
			m_pBitmap->GetHBITMAP(backColor, &hBmp);
			// Get the bitmap structure (to extract width, height, and bpp)
			BITMAP bm;
			GetObject( hBmp, sizeof(BITMAP), &bm );
			m_uWidth = bm.bmWidth;
			m_uHeight = bm.bmHeight;
		}
		else
		{
			m_uWidth = uWidth;
			m_uHeight = uHeight;
		}
		return 0;
	}
	return -1;
}

void CBitmapObject::Draw()
{
	if( !m_bVisibility )
		return;

	IDirectDrawSurface7* pDDS = GetSurface();
	if (pDDS)
	{
		RECT srcRECT = {
			0,
			0, 
			m_uWidth, 
			m_uHeight};
		RECT dstRECT = {
		    m_uX,
		 	m_uY,
			m_uX + m_uWidth, 
			m_uY + m_uHeight};

		BOOL bSelected = FALSE;
		if( m_pMultiSAP->m_lSelectGroupID == GetObjectID() )
			bSelected = TRUE;

		m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00, bSelected, m_pMultiSAP->m_uSelectFrameColor);
	}
}
