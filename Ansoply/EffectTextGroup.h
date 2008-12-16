#pragma once
#include "ansoplyobject.h"
#include <list>

using namespace std;

class CEffectTextEx;

class CEffectTextGroup :
	public CAnsoplyObject
{
public:
	CEffectTextGroup(void);
	~CEffectTextGroup(void);

	virtual void Draw();

	void AddText(CEffectTextEx * pEffectText);
	void InsertText(ULONG uWhere, CEffectTextEx * pEffectText);

	list<CEffectTextEx*> m_effectextlist;
	list<CEffectTextEx*>::iterator m_iter;
	CRITICAL_SECTION m_cs;

	BOOL m_bPlay;
};
