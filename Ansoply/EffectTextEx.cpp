#include "StdAfx.h"
#include ".\effecttextex.h"
#include "project.h"
#include "EffectDraw.h"
#include "CMultiSAP.h"
#include <time.h>
#include <sstream>

CEffectTextEx::CEffectTextEx(void)
{
	SetObjectType(effecttext);
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

	m_uTransparentColor = 0;

	m_hbrFill = CreateSolidBrush(RGB(0, 0, 0));

	InitializeCriticalSection(&m_cs);
}

CEffectTextEx::~CEffectTextEx(void)
{
	DeleteFont(m_hFont);
	DeleteDC(m_hdcText);
	DeleteBrush( m_hbrFill );
	DeleteCriticalSection(&m_cs);
}


void CEffectTextEx::Draw()
{
	////if( m_actualPlayEnd )
	////	return;
	if( !m_bVisibility )
		return;

	EnterCriticalSection(&m_cs);

	HRESULT hr;

	HDC hdcDest;

	m_pDDSFontCache->GetDC(&hdcDest);

	int nStep = 1;
	EFFECTDRAWPROC drawproc = ::GetEffectProc(m_uDrawStyle);

	RECT rt;
	rt.top = 0;
	rt.left = 0;
	rt.right = m_uRegionWidth;
	rt.bottom = m_uRegionHeight;

	if( GetTickCount() - m_nStart > m_uDelay )
	{
		drawproc(hdcDest, m_hdcText, rt, nStep, m_nProgress);

		m_nStart = GetTickCount();
		if( m_bClear )
		{
			//HBRUSH hbrFill = CreateSolidBrush(RGB(0, 0, 0));
			FillRect(hdcDest, &rt, m_hbrFill);	
			m_bClear = FALSE;
		}

		if( m_nProgress > 100 )
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
			if( m_playType == PLAY_THROUGH && m_nProgress /*m_uPlayBeginTime > m_uPlayTimes*/ )
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
		}
	}
	if( m_StopTimeExpire && GetTickCount() > m_StopTimeExpire )
		m_actualPlayEnd = TRUE;


	m_pDDSFontCache->ReleaseDC(hdcDest);

	DDSURFACEDESC2 surfDesc;
	INITDDSTRUCT(surfDesc);

	hr = m_pDDSFontCache->Lock(NULL, &surfDesc, DDLOCK_WAIT, NULL);

	if(hr == DD_OK)
	{
		LPDWORD lpDst = (LPDWORD)surfDesc.lpSurface;

		//DWORD dwAlphaMask = 0x26 << 24;
		//DWORD dwRGBMask   = ( surfDesc.ddpfPixelFormat.dwRBitMask |
		//	surfDesc.ddpfPixelFormat.dwGBitMask |
		//	surfDesc.ddpfPixelFormat.dwBBitMask );
		//DWORD dwColorkey  = 0xFFFFFF;

		//			for(row = 0; row < 1 * size.cy; row++)
		for(int i = 0; i < m_uRegionHeight; i++)
		{
			LPDWORD lp = lpDst;

			//WORD*  p16 = (WORD*)((BYTE*)surfDesc.lpSurface + i*surfDesc.lPitch);
			//DWORD* p32 = (DWORD*)((BYTE*)surfDesc.lpSurface + i*surfDesc.lPitch);

			//				for(col = 0; col < m_pTextObject->GetTextLen() * size.cx; col++)
			for(int j = 0; j < m_uRegionWidth; j++)
			{
				DWORD dwPel = *lp;

				if(dwPel)
				{
					dwPel <<= 24;
					//						dwPel |= 0x00FFFFFF;
					dwPel |= GetColor();
				}

				//if( surfDesc.ddpfPixelFormat.dwRGBBitCount == 16 )
				//{
				//	if( ( *p16 &= dwRGBMask ) != dwColorkey )
				//		*p16 |= dwAlphaMask;
				//	p16++;
				//}
				//else if( surfDesc.ddpfPixelFormat.dwRGBBitCount == 32 || surfDesc.ddpfPixelFormat.dwRGBBitCount == 24)
				//{
				//	if( ( *p32 &= dwRGBMask ) != dwColorkey )
				//		*p32 |= dwAlphaMask;
				//	p32++;
				//}

				*lp++ = dwPel;
			}
			lpDst += (surfDesc.lPitch / 4);
		}
		m_pDDSFontCache->Unlock(NULL);
	}


	//////////////////////////////////////////////////////////////////////////
	DWORD dwFlags = D3DTEXTR_TRANSPARENTWHITE;
	if( dwFlags & (D3DTEXTR_TRANSPARENTWHITE|D3DTEXTR_TRANSPARENTBLACK) )
	{
		// Lock the texture surface
		DDSURFACEDESC2 ddsdAlpha={0};
		ddsdAlpha.dwSize = sizeof(ddsdAlpha);
		m_pDDSFontCache->Lock( NULL, &ddsdAlpha, 0, NULL );

		//DWORD dwAlphaMask = ddsdAlpha.ddpfPixelFormat.dwRGBAlphaBitMask;
		DWORD dwAlphaMask = m_uAlpha << 24;
		DWORD dwRGBMask   = ( ddsdAlpha.ddpfPixelFormat.dwRBitMask |
			ddsdAlpha.ddpfPixelFormat.dwGBitMask |
			ddsdAlpha.ddpfPixelFormat.dwBBitMask );
		//DWORD dwColorkey  = 0x00000000; // Colorkey on black
		DWORD dwColorkey  = m_uTransparentColor;

		// Add an opaque alpha value to each non-colorkeyed pixel
		for( DWORD y = 0; y < m_uRegionHeight; y++ )
		{
			WORD*  p16 = (WORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);
			DWORD* p32 = (DWORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);

			for( DWORD x = 0; x < m_uRegionHeight; x++ )
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
		m_pDDSFontCache->Unlock( NULL );
		//		DeleteDC( hdcBitmap );
		//m_pDDSFontCache->ReleaseDC(hdcDest);
	}
	//////////////////////////////////////////////////////////////////////////

	RECT srcRECT = {0, 0, m_uSurfaceWidth, m_uSurfaceHeight};
	RECT dstRECT = {m_cx, m_cy, m_uSurfaceWidth, m_uSurfaceHeight};

	IDirectDrawSurface7* pDDS = GetDDSFontCache();
	if (pDDS)
	{
		BOOL bSelected = FALSE;
		if( m_pMultiSAP->m_lSelectGroupID == GetObjectID() )
			bSelected = TRUE;

		hr = m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00, bSelected, m_pMultiSAP->m_uSelectFrameColor);
	}
	LeaveCriticalSection(&m_cs);
}

LONG CEffectTextEx::SetText(ULONG uX, 
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
						  ULONG uDelay, ULONG uAlpha, ULONG uTransparentColor)
{
	CTextObject::SetText(uX, uY, sText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor);

	m_hFont = CreateFontIndirect( &GetFont() );

	m_uDrawStyle = uDrawStyle;
	m_uDelay = uDelay;

	m_uAlpha = uAlpha;
	m_uTransparentColor = uTransparentColor;

	HDC hdcDest;

	m_pDDSFontCache->GetDC(&hdcDest);

	m_hdcText = CreateCompatibleDC( NULL );

	HBITMAP hbmp = CreateCompatibleBitmap(hdcDest, m_uRegionWidth, m_uRegionHeight);

	SelectObject(m_hdcText, hbmp);

	::SelectObject(m_hdcText, m_hFont);
	SetTextColor(m_hdcText, RGB(255, 255, 255));
	SetBkColor(m_hdcText, RGB(0,0,0));
	SetBkMode(m_hdcText, TRANSPARENT);

	m_pDDSFontCache->ReleaseDC(hdcDest);

	RECT rt;
	rt.top = GetYCoordinate();
	rt.left = GetXCoordinate();
	rt.right = GetXCoordinate() + m_uRegionWidth;
	rt.bottom = GetYCoordinate() + m_uRegionHeight;
	DrawText(m_hdcText, GetText(), GetTextLen(), &rt, DT_WORDBREAK);

	DeleteBitmap(hbmp);

	return 0;
}


void CEffectTextEx::Clear()
{
	IDirectDrawSurface7* pDDS = GetDDSFontCache();
	HDC hdcDest = NULL;
	RECT rt = {0, 0, m_uWidth, m_uHeight};
	pDDS->GetDC(&hdcDest);
	FillRect(hdcDest, &rt, m_hbrFill);
	pDDS->ReleaseDC(hdcDest);
	if (pDDS)
	{
		RECT srcRECT = {0, 0, m_uSurfaceWidth, m_uSurfaceHeight};
		RECT dstRECT = {m_cx, m_cy, m_uSurfaceWidth, m_uSurfaceHeight};
		BOOL bSelected = FALSE;
		if( m_pMultiSAP->m_lSelectGroupID == GetObjectID() )
			bSelected = TRUE;

		m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00, bSelected, m_pMultiSAP->m_uSelectFrameColor);

	}
}

LONG CEffectTextEx::SetText(CMultiSAP * pMultiSAP,
			 ULONG uX,
			 ULONG uY,
			 LPCTSTR sFaceName,
			 ULONG uItalic,
			 ULONG uBold,
			 ULONG uUnderLine,
			 ULONG uWidth,
			 ULONG uHeight,
			 ULONG uColor, ULONG uAlpha, ULONG uTransparentColor,
			 ULONG uRegionWidth, ULONG uRegionHeight)
{
	EnterCriticalSection(&m_cs);
	memset(m_facename, 0, 32);
	_tcscpy(m_facename, sFaceName);
	m_cx = uX;
	m_cy = uY;
	m_uItalic = uItalic;
	m_uBold   = uBold;
	m_uUnderLine = uUnderLine;
	m_uWidth = uWidth;
	m_uHeight = uHeight;
	m_uColor = uColor;

	m_uAlpha = uAlpha;
	m_uTransparentColor = uTransparentColor;

	m_uRegionWidth = uRegionWidth;
	m_uRegionHeight = uRegionHeight;

	LOGFONT lfChar;
	ZeroMemory(&lfChar, sizeof(lfChar));
	lfChar.lfWidth          = uWidth;
	lfChar.lfHeight         = uHeight;
	if( uItalic == 1) lfChar.lfItalic         = TRUE;
	if( uUnderLine == 1) lfChar.lfUnderline   = TRUE;
	lfChar.lfCharSet        = DEFAULT_CHARSET;
	lfChar.lfPitchAndFamily = DEFAULT_PITCH;
	StringCchCopy(lfChar.lfFaceName, NUMELMS(lfChar.lfFaceName), sFaceName);
	if( uBold == 1)	
		lfChar.lfWeight        = FW_BOLD;
	else	
		lfChar.lfWeight        = FW_NORMAL;
	lfChar.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	lfChar.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lfChar.lfQuality       = ANTIALIASED_QUALITY;
	SetLogFont( &lfChar );

	m_hFont = CreateFontIndirect( &GetFont() );

	HDC hdcDest;
	IDirectDrawSurface7* pDDS = NULL;
	HRESULT hr = pMultiSAP->DDARGB32SurfaceInit(&pDDS, TRUE, m_uRegionWidth, m_uRegionHeight);
	SetDDSFontCache(pDDS);
	m_pDDSFontCache->GetDC(&hdcDest);

	m_hdcText = CreateCompatibleDC( NULL );

	HBITMAP hbmp = CreateCompatibleBitmap(hdcDest, m_uRegionWidth, m_uRegionHeight);

	SelectObject(m_hdcText, hbmp);

	::SelectObject(m_hdcText, m_hFont);
	SetTextColor(m_hdcText, RGB(255, 255, 255));
	SetBkColor(m_hdcText, RGB(0,0,0));
	SetBkMode(m_hdcText, TRANSPARENT);

	m_pDDSFontCache->ReleaseDC(hdcDest);

	RECT rt;
	rt.top = 0;
	rt.left = 0;
	rt.right = m_uRegionWidth;
	rt.bottom = m_uRegionHeight;
	DrawText(m_hdcText, GetText(), GetTextLen(), &rt, DT_WORDBREAK);

	DeleteBitmap(hbmp);

	LeaveCriticalSection(&m_cs);
	return 0;
}