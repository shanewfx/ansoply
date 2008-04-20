// TestAnsoplyDlg.h : 头文件
//

#pragma once
#include "ansoplyinterface1.h"
#include "afxwin.h"
#include "afxcmn.h"


// CTestAnsoplyDlg 对话框
class CTestAnsoplyDlg : public CDialog
{
// 构造
public:
	CTestAnsoplyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTANSOPLY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	ULONG m_uGroupID;
	ULONG m_uFileID;

	ULONG m_uBitmapID;

	ULONG m_uTextID;

	void  LoadVideoObject(LONG groupID);

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CStatic m_Video;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CAnsoplyinterface1 m_ansoply;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
protected:
	CListCtrl m_groupList;
	CListCtrl m_videoList;
public:
	afx_msg void OnBnClickedButton14();
	afx_msg void OnLvnItemchangedGroupList(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_bitmapList;
	CListCtrl m_textList;
	afx_msg void OnBnClickedCancel();
};
