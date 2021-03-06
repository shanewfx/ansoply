#include "StdAfx.h"
#include ".\dynamiceffectbitmap.h"
#include "project.h"
#include "EffectDraw.h"
#include <time.h>
#include <sstream>

CDynamicEffectBitmap::CDynamicEffectBitmap(void)
{
//	m_uDrawStyle = 50;
	m_uDelay = 50;
}

CDynamicEffectBitmap::~CDynamicEffectBitmap(void)
{
}

void CDynamicEffectBitmap::Draw()
{
	if( m_actualPlayEnd )
		return;
	if( !m_bVisibility )
		return;
	RECT rt = {0, 0, m_uWidth, m_uHeight};
	int nStep = 1;
	EFFECTDRAWPROC drawproc = ::GetEffectProc(m_uDrawStyle);

	IDirectDrawSurface7* pDDS = GetSurface();
	HDC hdcDest = NULL;
	if( m_bNxDraw )
	{

		pDDS->GetDC(&hdcDest);
	}


	// Get a DC for the bitmap
	//HDC hdcBitmap = CreateCompatibleDC( NULL );
	//if( NULL == hdcBitmap )
	//	return;

	//if( uOriginalSize == 1)
	{

		if( GetTickCount() - m_nStart > m_uDelay )
		{
			m_nProgress += nStep;
			//RECT rt = {0, 0, m_uWidth, m_uHeight};
			///::SelectObject( hdcBitmap, m_hBmp );
			if( m_bPlayEnd )
			{
				if( !m_endCountTime ) 
					m_endCountTime = GetTickCount();
				if( m_endtime != -1 && GetTickCount() - m_endCountTime > m_endtime )
					m_actualPlayEnd = TRUE;
				m_nProgress = 100;
			}
			if( m_bLoopPlayEnd )
			{
				if( !m_endCountTime ) 
					m_endCountTime = GetTickCount();
				if( m_endtime != -1 && GetTickCount() - m_endCountTime > m_endtime )
				{
					m_bLoopPlayEnd = FALSE;
					m_nProgress = 0;
					m_bClear = TRUE;
					if( m_uPlayBeginTime > m_uPlayTimes )
					{
						m_uPlayBeginTime = 1;
						ChangeBitmap();
					}
				}
				else
					m_nProgress = 100;
			}
			if( m_bChangeStyle )
			{
				if( !m_endCountTime ) 
					m_endCountTime = GetTickCount();
				if( m_endtime != -1 && GetTickCount() - m_endCountTime > m_endtime )
				{
					m_bChangeStyle = FALSE;
					m_nProgress = 0;
					m_bClear = TRUE;
					if( m_uPlayBeginTime > m_uPlayTimes )
					{
						m_uPlayBeginTime = 1;
						ChangeBitmap();
					}
					if( m_drawtype == PLAY_RANDOM )
					{
						m_uDrawStyle = (rand() % 290) + 1;
					}
					else if( m_drawtype == PLAY_SEQUENCE )
					{
						m_uDrawStyle++;
						if( m_uDrawStyle > m_uDrawStyleEnd )
							m_uDrawStyle = m_uDrawStyleBegin;	
					}
					drawproc = ::GetEffectProc(m_uDrawStyle);
				}
				else
				{
					//m_bNxDraw = FALSE;
					m_nProgress = 100;
				}
			}

			//if( m_nProgress <= 100 )
				drawproc(hdcDest, m_hdcBitmap, rt, nStep, m_nProgress);

			m_nStart = GetTickCount();

			if( m_nProgress > 100 || m_bClear )
			{
				//HBRUSH hbrFill = CreateSolidBrush(RGB(0, 0, 0));
				FillRect(hdcDest, &rt, m_hbrFill);

				//CString str;
				//str.Format("progress:%d\n", m_nProgress);
				//OutputDebugString(str);

				m_uPlayBeginTime++;
				if( m_drawtype == PLAY_RANDOM && m_nProgress)
				{
					//m_uDrawStyle = (rand() % 290) + 1;
					m_bChangeStyle = TRUE;
					m_endCountTime = GetTickCount();
				}
				else if( m_drawtype == PLAY_SEQUENCE && m_nProgress )
				{
					//m_uDrawStyle++;
					//if( m_uDrawStyle > m_uDrawStyleEnd )
					//	m_uDrawStyle = m_uDrawStyleBegin;
					m_bChangeStyle = TRUE;
					m_endCountTime = GetTickCount();
				}
				if( m_playType == PLAY_THROUGH && m_uPlayBeginTime > m_uPlayTimes )
				{
					m_bPlayEnd = TRUE;
				}
				else if( m_playType == PLAY_LOOP && !m_bLoopPlayEnd && m_nProgress )
				{
					m_endCountTime = GetTickCount();
					m_bLoopPlayEnd = TRUE;
				}
				m_nProgress = 0;
				m_bClear = FALSE;
			}
		}
		if( m_StopTimeExpire && GetTickCount() > m_StopTimeExpire )
		{
			//if( !m_endCountTime) 
			//	m_endCountTime = GetTickCount();
			//if( m_endtime != -1 && GetTickCount() - m_endCountTime > m_endtime )
			//	m_bPlayEnd = TRUE;
			m_actualPlayEnd = TRUE;
		}

		//if( !m_bNxDraw )
		//	BitBlt( hdcDest, 0, 0, m_uWidth, m_uHeight, m_hdcBitmap, 0, 0, SRCCOPY );
		//	//drawproc(hdcDest, m_hdcBitmap, rt, nStep, 100);
		//if( m_endtime != -1 && GetTickCount() - m_endCountTime > m_endtime )
		//{
		//	m_bNxDraw = TRUE;
		//}

		//BitBlt( hdcDest, 0, 0, m_uWidth, m_uHeight, hdcBitmap, 0, 0, SRCCOPY );
	}
	//	else
	{
		//USES_CONVERSION;
		//Bitmap originalBMP(T2W(m_sFilePath.c_str()));
		//Graphics g(hdcDest);
		//g.DrawImage(&originalBMP, Rect(0, 0, m_uWidth, m_uHeight), 0, 0, 
		//	originalBMP.GetWidth(), originalBMP.GetHeight(), UnitPixel, NULL );
	}


	//DeleteDC( hdcBitmap );
	pDDS->ReleaseDC(hdcDest);
	DWORD dwFlags = D3DTEXTR_TRANSPARENTWHITE;
	if( dwFlags & (D3DTEXTR_TRANSPARENTWHITE|D3DTEXTR_TRANSPARENTBLACK) )
	{
		// Lock the texture surface
		DDSURFACEDESC2 ddsdAlpha={0};
		ddsdAlpha.dwSize = sizeof(ddsdAlpha);
		pDDS->Lock( NULL, &ddsdAlpha, 0, NULL );

		//DWORD dwAlphaMask = ddsdAlpha.ddpfPixelFormat.dwRGBAlphaBitMask;
		DWORD dwAlphaMask = m_uAlpha << 24;
		DWORD dwRGBMask   = ( ddsdAlpha.ddpfPixelFormat.dwRBitMask |
			ddsdAlpha.ddpfPixelFormat.dwGBitMask |
			ddsdAlpha.ddpfPixelFormat.dwBBitMask );
		//DWORD dwColorkey  = 0x00000000; // Colorkey on black
		DWORD dwColorkey  = m_uTransparentColor;


		// Add an opaque alpha value to each non-colorkeyed pixel
		for( DWORD y = 0; y < m_uHeight; y++ )
		{
			WORD*  p16 = (WORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);
			DWORD* p32 = (DWORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);

			for( DWORD x = 0; x < m_uWidth; x++ )
			{

				if( *p32 != 0 )
				{
					if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 16 )
					{
						if( ( *p16 &= dwRGBMask ) != dwColorkey )
							*p16 |= dwAlphaMask;
						p16++;
					}
					else if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 32 || ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 24)
					{

						if( ( *p32 &= dwRGBMask ) != dwColorkey )
							*p32 |= dwAlphaMask;
						p32++;
					}
				}
				else if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 16 )
				{
					p16++;
				}
				else if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 32 || ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 24)
				{
					p32++;
				}
			}
		}
		pDDS->Unlock( NULL );
		//		DeleteDC( hdcBitmap );
		pDDS->ReleaseDC(hdcDest);
	}
	pDDS->ReleaseDC(hdcDest);


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

LONG CDynamicEffectBitmap::SetDynamicEffectBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle)
{
	USES_CONVERSION;

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
	//m_MilliSec = uMilli;
	m_uDrawStyle = uDrawStyle;


	m_iter = m_BitmapList.begin();
	BitmapType bmpType = *m_iter;
	Color backColor;
	bmpType.pBitmap->GetHBITMAP(backColor, &m_hBmp);

	m_hdcBitmap = CreateCompatibleDC( NULL );
	SelectObject(m_hdcBitmap, m_hBmp);
	

	return 0;
}

void CDynamicEffectBitmap::ChangeBitmap()
{
	m_iter++;
	if( m_iter == m_BitmapList.end() )
		m_iter = m_BitmapList.begin();

	BitmapType bmpType = *m_iter;
	Color backColor;
	bmpType.pBitmap->GetHBITMAP(backColor, &m_hBmp);

	SelectObject(m_hdcBitmap, m_hBmp);
}