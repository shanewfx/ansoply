// TestAnsoply.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CTestAnsoplyApp:
// �йش����ʵ�֣������ TestAnsoply.cpp
//

class CTestAnsoplyApp : public CWinApp
{
public:
	CTestAnsoplyApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestAnsoplyApp theApp;
