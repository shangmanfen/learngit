
// 串口V2.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C串口V2App: 
// 有关此类的实现，请参阅 串口V2.cpp
//

class C串口V2App : public CWinApp
{
public:
	C串口V2App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C串口V2App theApp;