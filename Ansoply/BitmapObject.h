#pragma once
#include "ansoplyobject.h"
#include "project.h"
#include <string>
using namespace std;

typedef enum _TRANSPARENT_TYPE_
{
	ALPHA_BLENDING,
	BACKGROUND_TRANSPARENT
}TRANSPARENT_TYPE;

//class CAlphaBlt;
//class IDirectDrawSurface7;
//class Bitmap;

class CBitmapObject :
	public CAnsoplyObject
{
	friend class CMultiSAP;
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
protected:
	TRANSPARENT_TYPE m_TransparentType;
	CAlphaBlt* m_pAlphaBlt;
public:
	CMultiSAP * m_pMultiSAP;
	basic_string<TCHAR> m_sFilePath;
	IDirectDrawSurface7* m_pDDS;
	Bitmap* m_pBitmap;
	ULONG m_uAlpha;
	ULONG m_uTransparentColor;
	//ULONG m_uX; 
	//ULONG m_uY;
	//ULONG m_uWidth;
	//ULONG m_uHeight;
};
