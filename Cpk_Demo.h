
// Cpk_Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCpk_DemoApp: 
// �йش����ʵ�֣������ Cpk_Demo.cpp
//

class CCpk_DemoApp : public CWinApp
{
public:
	CCpk_DemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCpk_DemoApp theApp;