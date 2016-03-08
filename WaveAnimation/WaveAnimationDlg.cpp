
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
//	ON_WM_CREATE()
//	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CWaveAnimationDlg ��Ϣ�������

BOOL CWaveAnimationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CPictureHolder tmpPic;
	tmpPic.CreateFromBitmap(IDB_BITMAP_CAT);
	m_renderSrc.Create32BitFromPicture(&tmpPic, 440, 440);
	m_renderDest.Create32BitFromPicture(&tmpPic, 440, 440);

	m_waterEffect.Create(440, 440);
	SetTimer(ID_EFFECTTIMER, 30, NULL);
	SetTimer(ID_DROPTIMER, 1500, NULL);

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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWaveAnimationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWaveAnimationDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == ID_EFFECTTIMER)
	{
		m_waterEffect.Render((DWORD*)m_renderSrc.GetDIBits(), (DWORD*)m_renderDest.GetDIBits());
		CClientDC dc(this);
		CPoint ptOrigin(15, 20);
		m_renderDest.Draw(&dc, ptOrigin);
	}

	if (nIDEvent == ID_DROPTIMER)
	{
		static CRect r;
		r.left = 15;
		r.top = 20;
		r.right = r.left + m_renderSrc.GetWidth();
		r.bottom = r.top + m_renderSrc.GetHeight();
		m_waterEffect.Blob(random(r.left, r.right), random(r.top, r.bottom), 5, 800, m_waterEffect.m_iHpage);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CWaveAnimationDlg::OnClose()
{
	KillTimer(ID_EFFECTTIMER);
	KillTimer(ID_DROPTIMER);

	CDialogEx::OnClose();
}


void CWaveAnimationDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	static CRect r;
	r.left = 15;
	r.top = 20;
	r.right = r.left + m_renderSrc.GetWidth();
	r.bottom = r.top + m_renderSrc.GetHeight();

	if (r.PtInRect(point) == TRUE)
	{
		// dibs are drawn upside down...
		point.y -= 20;
		point.y = 440 - point.y;

		if (nFlags & MK_LBUTTON)
			m_waterEffect.Blob(point.x - 15, point.y, 10, 800, m_waterEffect.m_iHpage);
		else
			m_waterEffect.Blob(point.x - 15, point.y, 5, 400, m_waterEffect.m_iHpage);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
