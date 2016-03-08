
// WaveAnimationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WaveAnimation.h"
#include "WaveAnimationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWaveAnimationDlg 对话框



CWaveAnimationDlg::CWaveAnimationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WAVEANIMATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaveAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWaveAnimationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CWaveAnimationDlg 消息处理程序

BOOL CWaveAnimationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_title.LoadString(IDS_STRING_TITLE);
	m_fontTitle.CreateFont(25, 14, 0, 0, 16, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("楷体"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWaveAnimationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		m_BackBuffer->BitBlt(0, 0, m_szClient.cx, m_szClient.cy, nullptr, 0, 0, WHITENESS);
		static CRect txtRect(10, 10, 200, 50);
		auto oldM = m_BackBuffer->SetBkMode(TRANSPARENT);
		auto oldF = m_BackBuffer->SelectObject(m_fontTitle);
		auto oldC = m_BackBuffer->SetTextColor(RGB(200, 14, 57));
		m_BackBuffer->DrawText(m_title, txtRect, DT_LEFT);
		m_BackBuffer->SetTextColor(oldC);
		m_BackBuffer->SelectObject(oldF);
		m_BackBuffer->SetBkMode(oldM);
		dc.BitBlt(0, 0, m_szClient.cx, m_szClient.cy, m_BackBuffer, 0, 0, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWaveAnimationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CWaveAnimationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_BackBuffer = CDC::FromHandle(::CreateCompatibleDC(nullptr));
	CDC *dc = GetDC();
	CRect rt;
	GetClientRect(rt);
	m_szClient = rt.Size();
	m_Bitmap = CBitmap::FromHandle(::CreateCompatibleBitmap(dc->m_hDC, m_szClient.cx, m_szClient.cy));
	ReleaseDC(dc);
	m_OldBitmap = m_BackBuffer->SelectObject(m_Bitmap);

	return 0;
}


void CWaveAnimationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_BackBuffer->SelectObject(m_OldBitmap);
	m_BackBuffer->DeleteDC();
	m_BackBuffer = nullptr;
	m_Bitmap->DeleteObject();
	m_Bitmap = nullptr;

	PostQuitMessage(0);
}
