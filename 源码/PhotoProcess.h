// PhotoProcess.h : PhotoProcess Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPhotoProcessApp:
// �йش����ʵ�֣������ PhotoProcess.cpp
//

class CPhotoProcessApp : public CWinApp
{
public:
	CPhotoProcessApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPhotoProcessApp theApp;