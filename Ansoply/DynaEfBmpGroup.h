#pragma once
#include "ansoplyobject.h"
#include <list>

using namespace std;

class CEffectBitmap;

class CDynaEfBmpGroup :
	public CAnsoplyObject
{
public:
	CDynaEfBmpGroup(void);
	~CDynaEfBmpGroup(void);

	virtual void Draw();

	void AddBitmap(CEffectBitmap * pEffectBitmap);

	list<CEffectBitmap*> m_effectbmplist;
	list<CEffectBitmap*>::iterator m_iter;
	CRITICAL_SECTION m_cs;
};
