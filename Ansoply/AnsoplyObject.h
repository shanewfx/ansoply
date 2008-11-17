#pragma once


typedef enum _PLAY_TYPE_
{
	PLAY_NONE = 0,
	PLAY_THROUGH,
	PLAY_PAUSE,
	PLAY_LOOP,
	PLAY_PREVIOUS,
	PLAY_NEXT,
	PLAY_TERMINATE
}PLAY_TYPE;

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

	PLAY_TYPE   m_playType;
	ULONG       m_uPlayTimes;
	ULONG       m_uPlayBeginTime;  // 当设置次数时,初始化为0

	ULONG       m_StopTimeExpire;
	BOOL        m_bVisibility;
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
