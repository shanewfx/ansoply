#pragma once
#include "ansoplyobject.h"
#include "project.h"
#include <list>
#include <string>
#include <vector>

using namespace std;

class CDynamicBitmap :
	public CAnsoplyObject
{
public:
	CDynamicBitmap(void);
	~CDynamicBitmap(void);

	void SetSurface(IDirectDrawSurface7* pSurface);
	IDirectDrawSurface7* GetSurface();

	LONG SetDynamicBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uMilli);

	void  SetAlphaBlt(CAlphaBlt * pAlphaBlt)
	{
		m_pAlphaBlt = pAlphaBlt;
	}
	virtual void Draw();

public:
	IDirectDrawSurface7 * m_pDDS;

	list<BitmapType> m_BitmapList;
	ULONG m_uAlpha;
	ULONG m_uTransparentColor;
	ULONG m_uX; 
	ULONG m_uY;
	ULONG m_uWidth;
	ULONG m_uHeight;
	ULONG m_uOriginalSize;

	DWORD m_dwRender;

	ULONG           m_MilliSec;
	vector<CString> m_bitmapFileArray;
	CAlphaBlt *     m_pAlphaBlt;
//	CStringArray  m_bitmapFileArray;
};
