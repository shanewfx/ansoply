#pragma once
#include "ansoplyobject.h"
#include <string>
using namespace std;

typedef enum _TRANSPARENT_TYPE_
{
	ALPHA_BLENDING,
	BACKGROUND_TRANSPARENT
}TRANSPARENT_TYPE;

class CBitmapObject :
	public CAnsoplyObject
{
public:
	CBitmapObject();
	virtual ~CBitmapObject(void);

	void SetSurface(IDirectDrawSurface7* pSurface);
	IDirectDrawSurface7* GetSurface();
	LONG SetBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize);

	void  SetAlphaBlt(CAlphaBlt * pAlphaBlt)
	{
		m_pAlphaBlt = pAlphaBlt;
	}
	virtual void Draw();
private:
	TRANSPARENT_TYPE m_TransparentType;
	CAlphaBlt* m_pAlphaBlt;
public:
	basic_string<TCHAR> m_sFilePath;
	IDirectDrawSurface7* m_pDDS;
	Bitmap* m_pBitmap;
	ULONG m_uAlpha;
	ULONG m_uTransparentColor;
	ULONG m_uX; 
	ULONG m_uY;
	ULONG m_uWidth;
	ULONG m_uHeight;
};
