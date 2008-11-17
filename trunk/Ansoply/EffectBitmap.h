#pragma once
#include "BitmapObject.h"
#include "EffectDraw.h"

class CEffectBitmap :
	public CBitmapObject
{
public:
	CEffectBitmap(void);
	~CEffectBitmap(void);

	virtual void Draw();

	LONG SetBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawSytle, HWND hWnd);

private:
	HEFFECTDRAW m_effectDraw;
	ULONG m_uDrawStyle;
};
