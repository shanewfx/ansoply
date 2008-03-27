#include "StdAfx.h"
#include "project.h"
#include "dynamicbitmap.h"

CDynamicBitmap::CDynamicBitmap(void)
{
	m_uWidth  = 0;
	m_uHeight = 0;
}

CDynamicBitmap::~CDynamicBitmap(void)
{
}

LONG CDynamicBitmap::SetDynamicBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uMilli)
{
	USES_CONVERSION;
/*	string str = sBitmapFilePath;
	int index = 0;
	do 
	{
		index = str.find(';', index);
		m_bitmapFileArray.push_back( str.substr(0, index) );
		string fileName = str.substr(0, index);
		str.erase(0, index + 1);

		Bitmap * pBitmap = Bitmap::FromFile( T2W(fileName.), FALSE );
		m_BitmapList.push_back( pBitmap );

	} while(index != string::npos);
*/	

	CString str(sBitmapFilePath);
	int index = str.Find(';');
	while( index != -1 )
	{
		CString fileName = str.Left( index );
		//m_bitmapFileArray.Add( fileName );
		m_bitmapFileArray.push_back( fileName );

		Bitmap * pBitmap = Bitmap::FromFile( T2W(fileName), FALSE );
		m_BitmapList.push_back( pBitmap );

		HBITMAP hBmp;
		Color backColor;
		pBitmap->GetHBITMAP(backColor, &hBmp);
		// Get the bitmap structure (to extract width, height, and bpp)
		BITMAP bm;
		GetObject( hBmp, sizeof(BITMAP), &bm );
		if( m_uWidth  < bm.bmWidth ) m_uWidth = bm.bmWidth;
		if( m_uHeight < bm.bmHeight) m_uHeight = bm.bmHeight;

		str = str.Right( str.GetLength() - index - 1 );
		index = str.Find(';');
	}

	m_uAlpha = uAlpha;
	m_uTransparentColor = uTransparentColor;
	m_uX = uX;
	m_uY = uY;
	m_MilliSec = uMilli;

	return 0;
}

IDirectDrawSurface7* CDynamicBitmap::GetSurface()
{
	return m_pDDS;
}

void CDynamicBitmap::SetSurface(IDirectDrawSurface7* pSurface)
{
	m_pDDS = pSurface;
}

void CDynamicBitmap::Draw()
{
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
			m_uWidth, 
			m_uHeight};
		m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00);
	}
}