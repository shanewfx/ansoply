#include "StdAfx.h"
#include "ansoplyobject.h"
#include "IDGenerator.h"

CAnsoplyObject::CAnsoplyObject()
{
	m_objectType = none;
	m_uAlpha    = 0;
	m_uObjectID = IDGenerator::GetInstance().GenID();
	SetRect(&m_rect, 0, 0, 0, 0);
}

CAnsoplyObject::~CAnsoplyObject(void)
{
}

void CAnsoplyObject::SetObjectType(AnsoplyObjectType type)
{
	m_objectType = type;
}
