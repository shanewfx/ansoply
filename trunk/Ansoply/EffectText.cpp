#include "StdAfx.h"
#include ".\effecttext.h"
#include "EffectDraw.h"
#include <time.h>

CEffectText::CEffectText(void)
{
//	srand((unsigned)time(NULL));
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
}

CEffectText::~CEffectText(void)
{
	DeleteFont(m_hFont);
	DeleteDC(m_hdcText);
}

void CEffectText::Draw()
{
	if( m_actualPlayEnd )
		return;
	if( !m_bVisibility )
		return;

	HRESULT hr;

	//if(hr == DD_OK)
	{
		HDC hdcDest;

		m_pDDSFontCache->GetDC(&hdcDest);

		int nStep = 1;
		EFFECTDRAWPROC drawproc = ::GetEffectProc(m_uDrawStyle);


		//if( !bRegion )
		//{
		//	int row = pTextObject->GetYCoordinate();
		//	int col = pTextObject->GetXCoordinate();
		//	TextOut(hdcDest, col, row, pTextObject->GetText(), pTextObject->GetTextLen());
		//}
		//else
		{
			RECT rt;
			rt.top = GetYCoordinate();
			rt.left = GetXCoordinate();
			rt.right = GetXCoordinate() + m_uRegionWidth;
			rt.bottom = GetYCoordinate() + m_uRegionHeight;
			//HDC hdcText = CreateCompatibleDC( NULL );
			//if( NULL == hdcText )
			//	return;
			//HBITMAP hbmp = CreateCompatibleBitmap(hdcDest, m_uRegionWidth, m_uRegionHeight);

			//SelectObject(hdcText, hbmp);

			//::SelectObject(hdcText, m_hFont);
			//SetTextColor(hdcText, RGB(255, 255, 255));
			//SetBkColor(hdcText, RGB(0,0,0));
			//SetBkMode(hdcText, TRANSPARENT);


			//DrawText(hdcText, GetText(), GetTextLen(), &rt, DT_WORDBREAK);
			if( GetTickCount() - m_nStart > m_uDelay )
			{
				m_nProgress += nStep;
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
						m_nProgress = 100;
				}
				drawproc(hdcDest, m_hdcText, rt, nStep, m_nProgress);

				m_nStart = GetTickCount();
				if( m_nProgress > 100 || m_bClear )
				{
					HBRUSH hbrFill = CreateSolidBrush(RGB(0, 0, 0));
					FillRect(hdcDest, &rt, hbrFill);	
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
						m_bPlayEnd = TRUE;
					else if( m_playType == PLAY_LOOP && !m_bLoopPlayEnd && m_nProgress )
					{
						m_endCountTime = GetTickCount();
						m_bLoopPlayEnd = TRUE;
					}

					m_bClear = FALSE;
					m_nProgress = 0;
				}
			}
			if( m_StopTimeExpire && GetTickCount() > m_StopTimeExpire )
				m_actualPlayEnd = TRUE;
			//DeleteDC(hdcText);
			//DeleteBitmap(hbmp);
		}

		m_pDDSFontCache->ReleaseDC(hdcDest);

		DDSURFACEDESC2 surfDesc;
		INITDDSTRUCT(surfDesc);

		hr = m_pDDSFontCache->Lock(NULL, &surfDesc, DDLOCK_WAIT, NULL);

		if(hr == DD_OK)
		{
			LPDWORD lpDst = (LPDWORD)surfDesc.lpSurface;

			//			for(row = 0; row < 1 * size.cy; row++)
			for(int i = 0; i < m_uRegionHeight; i++)
			{
				LPDWORD lp = lpDst;

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
					else
					{
						//						dwPel = 0x80000000;
					}

					*lp++ = dwPel;
				}
				lpDst += (surfDesc.lPitch / 4);
			}
			m_pDDSFontCache->Unlock(NULL);
		}
	}

	//HRESULT hr = E_FAIL;
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

LONG CEffectText::SetText(ULONG uX, 
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
						  ULONG uDelay)
{
	CTextObject::SetText(uX, uY, sText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor);

	m_hFont = CreateFontIndirect( &GetFont() );

	m_uDrawStyle = uDrawStyle;
	m_uDelay = uDelay;

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
