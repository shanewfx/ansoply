#pragma once
#include "movie.h"
#include "ansoplyobject.h"

class CVideoObject : 
	public CAnsoplyObject,
	public CMovie
{
public:
	CVideoObject();
	virtual ~CVideoObject(void);

	virtual void Draw()	{ }
};
