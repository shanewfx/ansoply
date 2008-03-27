#pragma once

class IDGenerator
{
public:
	~IDGenerator(void);
	static IDGenerator& GetInstance();
	ULONG GenID();
protected:
	IDGenerator(void);
protected:
	ULONG m_uID;
};

inline ULONG IDGenerator::GenID()
{
	InterlockedIncrement( (LONG*) &m_uID );
	return m_uID;
}
