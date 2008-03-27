#pragma once

class CAnsoplyObject
{
public:
	CAnsoplyObject();
	virtual ~CAnsoplyObject(void);

	ULONG GetObjectID();
	virtual void Draw() { }
protected:
	ULONG m_uObjectID;

	RECT  m_rect;
	ULONG m_uAlpha;
};

inline ULONG CAnsoplyObject::GetObjectID()
{
	return m_uObjectID;
}
