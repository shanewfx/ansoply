#pragma once

typedef enum _AnsoplyObjectType
{
	none,
	video,
	bitmap,
	text
}AnsoplyObjectType;

class CAnsoplyObject
{
public:
	CAnsoplyObject();
	virtual ~CAnsoplyObject(void);

	ULONG GetObjectID();
	virtual void Draw() { }

	void SetObjectType(AnsoplyObjectType type);
	AnsoplyObjectType GetObjectType();
protected:
	ULONG m_uObjectID;

	RECT  m_rect;
	ULONG m_uAlpha;

	AnsoplyObjectType m_objectType;
};

inline ULONG CAnsoplyObject::GetObjectID()
{
	return m_uObjectID;
}

inline AnsoplyObjectType CAnsoplyObject::GetObjectType()
{
	return m_objectType;
}
