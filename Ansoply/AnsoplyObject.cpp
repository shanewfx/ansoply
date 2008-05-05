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

BOOL CAnsoplyObject::SelectGroup(LONG cX, LONG cY)
{
	if (cX >= m_uX && cX <= m_uWidth + m_uX &&
		cY >= m_uY && cY <= m_uHeight + m_uY)
	{
		return TRUE;
	}
	return FALSE;
}