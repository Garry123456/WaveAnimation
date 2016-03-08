
// WaveAnimationDlg.h : 头文件
//

#pragma once

#define ID_EFFECTTIMER 1111
#define ID_DROPTIMER 1112

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
	CWaterEffect m_waterEffect;
	CDib m_renderSrc;
	CDib m_renderDest;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
