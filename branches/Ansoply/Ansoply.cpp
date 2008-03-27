// Ansoply.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{C972C363-8914-44AD-B197-5EE3561D95BF}", 
		 name = "Ansoply", 
		 helpstring = "Ansoply 1.0 Type Library",
		 resource_name = "IDR_ANSOPLY") ]
class CAnsoplyModule
{
public:
// Override CAtlDllModuleT members
};
