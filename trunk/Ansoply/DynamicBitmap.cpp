#include "StdAfx.h"
#include "dynamicbitmap.h"

CDynamicBitmap::CDynamicBitmap(void)
{
	m_uWidth  = 0;
	m_uHeight = 0;
	InitializeCriticalSection(&m_CS);
	SetObjectType(dynamicbitmap);
}

CDynamicBitmap::~CDynamicBitmap(void)
{
	DeleteCriticalSection(&m_CS);
}

LONG CDynamicBitmap::SetDynamicBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uMilli)
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

		BitmapType bmpType;
		Bitmap * pBitmap = Bitmap::FromFile( T2W(fileName), FALSE );
		bmpType.pBitmap = pBitmap;

		HBITMAP hBmp;
		Color backColor;
		pBitmap->GetHBITMAP(backColor, &hBmp);
		// Get the bitmap structure (to extract width, height, and bpp)
		BITMAP bm;
		GetObject( hBmp, sizeof(BITMAP), &bm );

//		if( m_uWidth  < bm.bmWidth ) m_uWidth = bm.bmWidth;
//		if( m_uHeight < bm.bmHeight) m_uHeight = bm.bmHeight;

		bmpType.uWidth = bm.bmWidth;
		bmpType.uHeight = bm.bmHeight;
		m_BitmapList.push_back( bmpType );

		str = str.Right( str.GetLength() - index - 1 );
		index = str.Find(';');
	}

	m_uAlpha = uAlpha;
	m_uTransparentColor = uTransparentColor;
	m_uX = uX;
	m_uY = uY;
	m_uWidth = uWidth;
	m_uHeight = uHeight;
	m_uOriginalSize = uOriginalSize;
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
	if( !m_bVisibility )
		return;

	EnterCriticalSection(&m_CS);
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

		m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0xFF, bSelected, m_pMultiSAP->m_uSelectFrameColor);
	}
	LeaveCriticalSection(&m_CS);
}