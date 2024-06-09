
// PenghitungIPS.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPenghitungIPSApp:
// See PenghitungIPS.cpp for the implementation of this class
//

class CPenghitungIPSApp : public CWinApp
{
public:
	CPenghitungIPSApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPenghitungIPSApp theApp;
