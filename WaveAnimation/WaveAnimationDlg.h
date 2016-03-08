
// WaveAnimationDlg.h : ͷ�ļ�
//

#pragma once


// CWaveAnimationDlg �Ի���
class CWaveAnimationDlg : public CDialogEx
{
// ����
public:
	CWaveAnimationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAVEANIMATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CDC *m_BackBuffer;
	CBitmap	*m_Bitmap;
	CBitmap	*m_OldBitmap;
	CString m_title;
	CFont m_fontTitle;
	CSize m_szClient;	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};
