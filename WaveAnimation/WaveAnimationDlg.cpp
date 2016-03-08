
// WaveAnimationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WaveAnimation.h"
#include "WaveAnimationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWaveAnimationDlg �Ի���



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


// CWaveAnimationDlg ��Ϣ�������

BOOL CWaveAnimationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_title.LoadString(IDS_STRING_TITLE);
	m_fontTitle.CreateFont(25, 14, 0, 0, 16, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("����"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWaveAnimationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
