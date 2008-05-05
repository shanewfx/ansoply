#pragma once

typedef enum _AnsoplyObjectType
{
	none,
	video,
	bitmap,
	dynamicbitmap,
	text
}AnsoplyObjectType;

class CAnsoplyObject
{
public:
	CAnsoplyObject();
	virtual ~CAnsoplyObject(void);

	ULONG GetObjectID();
	virtual void Draw() { }

	BOOL	SelectGroup(LONG cX, LONG cY);;

	void SetObjectType(AnsoplyObjectType type);
	AnsoplyObjectType GetObjectType();
protected:
	ULONG m_uObjectID;

	RECT  m_rect;
	ULONG m_uAlpha;

	ULONG m_uX; 
	ULONG m_uY;
	ULONG m_uWidth;
	ULONG m_uHeight;

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
