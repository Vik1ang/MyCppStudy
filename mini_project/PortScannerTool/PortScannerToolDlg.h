
// PortScannerToolDlg.h: 头文件
//

#pragma once


// CPortScannerToolDlg 对话框
class CPortScannerToolDlg : public CDialogEx
{
// 构造
public:
	CPortScannerToolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PORTSCANNERTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	CIPAddressCtrl m_IP;
	CStatic m_promot;
	CProgressCtrl m_progress;
	CListCtrl m_IPList;
	CEdit m_SinglePort;
	CEdit m_PortFrom;
	CEdit m_Port_To;
	CEdit m_Thread_Num;
	afx_msg void OnBnClickedButtonStart();
};
