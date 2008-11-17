#include "StdAfx.h"
#include ".\effectbitmap.h"
#include "project.h"
#include <time.h>

CEffectBitmap::CEffectBitmap(void)
{
	SetObjectType(effectbitmap);
	m_effectDraw = ::CreateEffectDraw();
}

CEffectBitmap::~CEffectBitmap(void)
{
	::DeleteEffectDraw(m_effectDraw);
}

void CEffectBitmap::Draw()
{
	//if( !m_bVisibility )
	//	return;

	//IDirectDrawSurface7* pDDS = GetSurface();
	//if (pDDS)
	//{
	//	RECT srcRECT = {
	//		0,
	//		0, 
	//		m_uWidth, 
	//		m_uHeight};
	//	RECT dstRECT = {
	//		m_uX,
	//		m_uY,
	//		m_uX + m_uWidth, 
	//		m_uY + m_uHeight};

	//	BOOL bSelected = FALSE;
	//	if( m_pMultiSAP->m_lSelectGroupID == GetObjectID() )
	//		bSelected = TRUE;

	//	m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00, bSelected, m_pMultiSAP->m_uSelectFrameColor);
	//}
}

LONG CEffectBitmap::SetBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawSytle, HWND hWnd)
{
	CBitmapObject::SetBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY,
		uWidth, uHeight, uOriginalSize);

	m_uDrawStyle = uDrawSytle;

	HBITMAP hBmp;
	Color backColor;
	m_pBitmap->GetHBITMAP(backColor, &hBmp);

	SetParams(m_effectDraw, hWnd, hBmp, ED_HBITMAPWNDBK, NULL, ED_STRETCHED|ED_TRANSPARENT, 0, ED_TITLED, 0);

	//InstallCustomEffectProc((EFFECTDRAWPROC)CustomEffect);
	//InstallEventProc(m_effectDraw, (EFFECTDRAWEVENTPROC)OnDrawClear);

	//RandomSeed((unsigned int)time(NULL));
	//SetRandomClearStyle(m_effectDraw);
	SetDrawStyle(m_effectDraw, 15);

	::Draw(m_effectDraw);



	return 0;
}
