#pragma once
#include "effectbitmap.h"
#include <list>
#include <vector>

using namespace std;

class CDynamicEffectBitmap :
	public CEffectBitmap
{
public:
	CDynamicEffectBitmap(void);
	~CDynamicEffectBitmap(void);

	virtual void Draw();

	void ChangeBitmap();

	LONG SetDynamicEffectBitmap(LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle);

	list<BitmapType> m_BitmapList;

	ULONG m_uOriginalSize;

	std::list<BitmapType>::iterator m_iter;

//	ULONG           m_MilliSec;
	vector<CString> m_bitmapFileArray;
	CRITICAL_SECTION  m_CS;
	CMultiSAP * m_pMultiSAP;
};
