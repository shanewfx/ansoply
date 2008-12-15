#pragma once
#include "ansoplyobject.h"
#include <list>

using namespace std;

class CEffectBitmapEx;

class CDynaEfBmpGroup :
	public CAnsoplyObject
{
public:
	CDynaEfBmpGroup(void);
	~CDynaEfBmpGroup(void);

	virtual void Draw();

	void AddBitmap(CEffectBitmapEx * pEffectBitmap);
	void InsertBitmap(ULONG uWhere, CEffectBitmapEx * pEffectBitmap);

	list<CEffectBitmapEx*> m_effectbmplist;
	list<CEffectBitmapEx*>::iterator m_iter;
	CRITICAL_SECTION m_cs;
};
