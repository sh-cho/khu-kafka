
// MessageViewer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMessageViewerApp:
// �� Ŭ������ ������ ���ؼ��� MessageViewer.cpp�� �����Ͻʽÿ�.
//

class CMessageViewerApp : public CWinApp
{
public:
	CMessageViewerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMessageViewerApp theApp;