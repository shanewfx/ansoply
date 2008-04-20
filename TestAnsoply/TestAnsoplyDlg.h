// TestAnsoplyDlg.h : ͷ�ļ�
//

#pragma once
#include "ansoplyinterface1.h"
#include "afxwin.h"
#include "afxcmn.h"


// CTestAnsoplyDlg �Ի���
class CTestAnsoplyDlg : public CDialog
{
// ����
public:
	CTestAnsoplyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTANSOPLY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	ULONG m_uGroupID;
	ULONG m_uFileID;

	ULONG m_uBitmapID;

	ULONG m_uTextID;

	void  LoadVideoObject(LONG groupID);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
