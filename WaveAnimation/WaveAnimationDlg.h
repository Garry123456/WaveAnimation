
// WaveAnimationDlg.h : 头文件
//

#pragma once


// CWaveAnimationDlg 对话框
class CWaveAnimationDlg : public CDialogEx
{
// 构造
public:
	CWaveAnimationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAVEANIMATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CDC *m_BackBuffer;
	CBitmap	*m_Bitmap;
	CBitmap	*m_OldBitmap;
	CString m_title;
	CFont m_fontTitle;
	CSize m_szClient;	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};
