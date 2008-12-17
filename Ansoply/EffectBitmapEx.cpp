#include "StdAfx.h"
#include ".\effectbitmapex.h"
#include "project.h"
#include "EffectDraw.h"
#include <time.h>
#include <sstream>

CEffectBitmapEx::CEffectBitmapEx(void)
{
	srand((unsigned)time(NULL));
	SetObjectType(effectbitmap);
	//	m_effectDraw = ::CreateEffectDraw();
	m_nStart = GetTickCount();
	m_nProgress = 0;
	m_bPlayEnd = FALSE;
	m_uDrawStyleBegin = 0;
	m_uDrawStyleEnd = 0;
	m_drawtype = PLAY_NONE;
	m_endtime = 0;
	m_endCountTime = 0;
	m_actualPlayEnd = FALSE;
	m_bLoopPlayEnd = FALSE;
	m_bClear = FALSE;
	m_bChangeStyle = FALSE;

	m_hbrFill = CreateSolidBrush(RGB(0, 0, 0));
	m_bNxDraw = TRUE;
	m_pOriginalBMP = NULL;
	m_pGraphics = NULL;
}

CEffectBitmapEx::~CEffectBitmapEx(void)
{
	DeleteBitmap( m_hBmp );
	DeleteDC( m_hdcBitmap );
	DeleteBrush( m_hbrFill );
	if( m_pOriginalBMP )
		delete m_pOriginalBMP;
	if( m_pGraphics )
		delete m_pGraphics;
}


void CEffectBitmapEx::Draw()
{
	//if( m_actualPlayEnd )
	//	return;
	if( !m_bVisibility )
		return;
	RECT rt = {0, 0, m_uWidth, m_uHeight};
	int nStep = 1;
	EFFECTDRAWPROC drawproc = ::GetEffectProc(m_uDrawStyle);

	IDirectDrawSurface7* pDDS = GetSurface();
	HDC hdcDest = NULL;
	pDDS->GetDC(&hdcDest);

	if( GetTickCount() - m_nStart > m_uDelay )
	{

		if( m_nProgress <= 100 )
			drawproc(hdcDest, m_hdcBitmap, rt, nStep, m_nProgress);

		m_nStart = GetTickCount();

		if( m_bClear )
		{
			FillRect(hdcDest, &rt, m_hbrFill);
			m_bClear = FALSE;
		}
		if( m_nProgress > 100  )
		{
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
			if( m_playType == PLAY_THROUGH && m_nProgress /* && m_uPlayBeginTime > m_uPlayTimes */)
			{
				m_bPlayEnd = TRUE;
				m_endCountTime = GetTickCount();
			}
			else if( m_playType == PLAY_LOOP && !m_bLoopPlayEnd && m_nProgress )
			{
				m_endCountTime = GetTickCount();
				m_bLoopPlayEnd = TRUE;
			}
			m_nProgress = 0;
			//m_bClear = FALSE;
		}
	}
	if( m_StopTimeExpire && GetTickCount() > m_StopTimeExpire )
	{
		m_actualPlayEnd = TRUE;
	}

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

LONG CEffectBitmapEx::SetBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay, HWND hWnd)
{
	CBitmapObject::SetBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY,
		uWidth, uHeight, uOriginalSize);

	m_uDrawStyle = uDrawStyle;
	m_uDelay = uDelay;

	//HBITMAP hBmp;
	Color backColor;
	m_pBitmap->GetHBITMAP(backColor, &m_hBmp);

	m_uOriginalSize = uOriginalSize;
	m_hdcBitmap = CreateCompatibleDC( NULL );
	if( uOriginalSize != 1 )
	{
		//USES_CONVERSION;
		//Bitmap originalBMP(T2W(m_sFilePath.c_str()));
		//m_pOriginalBMP = new Bitmap(T2W(m_sFilePath.c_str()));
		//Graphics g(m_hdcBitmap);

		BITMAP bm;
		GetObject( m_hBmp, sizeof(BITMAP), &bm );

		HBITMAP bmp = CreateBitmap(m_uWidth, m_uHeight, bm.bmPlanes, bm.bmBitsPixel, NULL);
		SelectObject(m_hdcBitmap, bmp);
		m_pGraphics = new Graphics(m_hdcBitmap);
		m_pGraphics->DrawImage(m_pBitmap, Rect(0, 0, m_uWidth, m_uHeight), 0, 0, 
			m_pBitmap->GetWidth(), m_pBitmap->GetHeight(), UnitPixel, NULL );


		//BITMAP bm;
		//GetObject( m_hBmp, sizeof(BITMAP), &bm );
		//tmphdcBitmap = CreateCompatibleDC( NULL );

		//HBITMAP bmp = CreateBitmap(m_uWidth, m_uHeight, bm.bmPlanes, bm.bmBitsPixel, NULL);
		//SelectObject(m_hdcBitmap, bmp);

		//SelectObject(tmphdcBitmap, m_hBmp);
		//bRet = StretchBlt(m_hdcBitmap, 
		//	0, 0, m_uWidth, m_uHeight, 
		//	tmphdcBitmap,
		//	0, 0, bm.bmWidth, bm.bmHeight,
		//	SRCCOPY );

	}
	else
	{
		SelectObject(m_hdcBitmap, m_hBmp);
	}

	return 0;
}

void CEffectBitmapEx::Clear()
{
	IDirectDrawSurface7* pDDS = GetSurface();
	HDC hdcDest = NULL;
	RECT rt = {0, 0, m_uWidth, m_uHeight};
	pDDS->GetDC(&hdcDest);
	FillRect(hdcDest, &rt, m_hbrFill);
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
