
// WaveAnimation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWaveAnimationApp: 
// �йش����ʵ�֣������ WaveAnimation.cpp
//

class CWaveAnimationApp : public CWinApp
{
public:
	CWaveAnimationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWaveAnimationApp theApp;