#include "StdAfx.h"
#include "idgenerator.h"

IDGenerator::IDGenerator(void) :
	m_uID(0)
{
}

IDGenerator::~IDGenerator(void)
{
}

IDGenerator& IDGenerator::GetInstance()
{
	static IDGenerator g_idGen;
	return g_idGen;
}
