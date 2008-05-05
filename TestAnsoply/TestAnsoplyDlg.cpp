// TestAnsoplyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestAnsoply.h"
#include "TestAnsoplyDlg.h"
#include ".\testansoplydlg.h"
#include <comutil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestAnsoplyDlg 对话框



CTestAnsoplyDlg::CTestAnsoplyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestAnsoplyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestAnsoplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO, m_Video);
	DDX_Control(pDX, IDC_ANSOPLYINTERFACE2, m_ansoply);
	DDX_Control(pDX, IDC_GROUP_LIST, m_groupList);
	DDX_Control(pDX, IDC_VIDEO_LIST, m_videoList);
	DDX_Control(pDX, IDC_BITMAPLIST, m_bitmapList);
	DDX_Control(pDX, IDC_TEXT_LIST, m_textList);
}

BEGIN_MESSAGE_MAP(CTestAnsoplyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnBnClickedButton14)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_GROUP_LIST, OnLvnItemchangedGroupList)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CTestAnsoplyDlg 消息处理程序

BOOL CTestAnsoplyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_groupList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_groupList.InsertColumn(0, "GroupID", LVCFMT_LEFT, 60);
	m_groupList.InsertColumn(1, "PlayType", LVCFMT_LEFT, 80);
	m_groupList.InsertColumn(2, "PlayRate", LVCFMT_LEFT, 80);
	m_groupList.InsertColumn(3, "Alpha", LVCFMT_LEFT, 60);
	m_groupList.InsertColumn(4, "cX", LVCFMT_LEFT, 60);
	m_groupList.InsertColumn(5, "cY", LVCFMT_LEFT, 60);
	m_groupList.InsertColumn(6, "Width", LVCFMT_LEFT, 60);
	m_groupList.InsertColumn(7, "Height", LVCFMT_LEFT, 60);

	m_videoList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_videoList.InsertColumn(0, "ObjectID", LVCFMT_LEFT, 80);
	m_videoList.InsertColumn(1, "FilePath", LVCFMT_LEFT, 280);

	m_bitmapList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_bitmapList.InsertColumn(0, "BitmapID", LVCFMT_LEFT, 60);
	m_bitmapList.InsertColumn(1, "FilePath", LVCFMT_LEFT, 180);
	m_bitmapList.InsertColumn(2, "Alpha", LVCFMT_LEFT, 80);
	m_bitmapList.InsertColumn(3, "TransColor", LVCFMT_LEFT, 60);
	m_bitmapList.InsertColumn(4, "cX", LVCFMT_LEFT, 60);
	m_bitmapList.InsertColumn(5, "cY", LVCFMT_LEFT, 60);

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CTestAnsoplyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestAnsoplyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CTestAnsoplyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestAnsoplyDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_ansoply.CreateVideoGroup(&m_uGroupID);

	// test select group by coordinate.
//	ULONG uX = 0;
//	ULONG uY = 0;
//	ULONG width = 320;
//	ULONG height = 240;
//	m_ansoply.SetVideoPosAndSize(m_uGroupID, uX, uY, width, height);

	m_groupList.DeleteAllItems();

	try 
	{
		LONG uGroupID = 0;
		m_ansoply.GetFirstVideoGroupID(&uGroupID);

		while( uGroupID != -1 ) 
		{
			CString sGroupID;
			sGroupID.Format("%d", uGroupID);
			int nItem = m_groupList.InsertItem(0xff, sGroupID);

			ULONG uAlpha, cX, cY, uWidth, uHeight;
			DOUBLE dRate;
			m_ansoply.GetVideoAlpha(uGroupID, &uAlpha);
			m_ansoply.GetVideoPositionAndSize(uGroupID, &cX, &cY, &uWidth, &uHeight);

			CString sText;
			sText.Format("%d", uAlpha);
			m_groupList.SetItemText(nItem, 3, sText);
			sText.Format("%d", cX);
			m_groupList.SetItemText(nItem, 4, sText);
			sText.Format("%d", cY);
			m_groupList.SetItemText(nItem, 5, sText);
			sText.Format("%d", uWidth);
			m_groupList.SetItemText(nItem, 6, sText);
			sText.Format("%d", uHeight);
			m_groupList.SetItemText(nItem, 7, sText);		

			m_ansoply.GetNextVideoGroupID(&uGroupID);
		}
	}
	catch(...)
	{

	}
}

void CTestAnsoplyDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	RECT rt;
	m_Video.GetClientRect( &rt );
	m_ansoply.Init((LONG)m_Video.m_hWnd, rt.right, rt.bottom);
}

void CTestAnsoplyDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal() == IDOK)
	{
		CString name = fileDlg.GetPathName();
		m_ansoply.AddVideoFile(m_uGroupID, name, &m_uFileID);
	}
}

void CTestAnsoplyDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	m_ansoply.SetVideoPosAndSize(m_uGroupID, 0, 0, 400, 300);
	//m_ansoply.SetDefaultVideoSize(m_uGroupID, 0, 0);
	m_ansoply.SetVideoAlpha(m_uGroupID, 0xFF);
	m_ansoply.Play(m_uGroupID);
}

void CTestAnsoplyDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here

	ULONG id;
	static int i = 0;
	m_ansoply.SetText(50 + i, 50 + i, "宋体", "宋体\0", 0, 0, 0, 100, 100, RGB(255, 255, 0), &m_uTextID);
	i += 50;
}

void CTestAnsoplyDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal() == IDOK)
	{
		CString name = fileDlg.GetPathName();
		ULONG id;
		m_ansoply.SetBitmap(&m_uBitmapID, name, 0xFF, 0xFFFF00, 0, 0, 500, 500, 1);
	}
}

void CTestAnsoplyDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	//m_ansoply.SavePlayList("c:\\abc.xml");
//	m_ansoply.Previous(m_uGroupID);
//	m_ansoply.DelVideoFile(m_uGroupID, m_uFileID);
//	m_ansoply.SetPlayRate(m_uGroupID, 2.0);
	m_ansoply.SelectObject(m_uBitmapID, 0xFFFFFF00);
}

void CTestAnsoplyDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	ULONG id = 0;
	m_ansoply.SetDynamicBitmap(&id, "f:\\pic.bmp;f:\\shopflag.jpg;", 0xA0, RGB(255, 255, 0), 0, 0, 100, 100, 1, 1000);
}

void CTestAnsoplyDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	//m_ansoply.DelBitmap(m_uBitmapID);
//	m_ansoply.CreateVideoGroup(&m_uGroupID);
	m_ansoply.SelectObject(m_uGroupID, 0xFFFFFF00);
}

void CTestAnsoplyDlg::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
//	m_ansoply.SetDefaultVideoSize(m_uGroupID, 0, 0);
	m_ansoply.SetMediaFilePath("c:\\");
	m_ansoply.LoadPlayList("D:\\Ansoply Project\\abc2.xml");
/*
	LONG videoGroupFirstGroupID = 0;
	LONG videoGroupNextGroupID = 0;

	ULONG uGroupCount = 0;
	m_ansoply.GetVideoGroupCount(&uGroupCount);

	if (uGroupCount > 0)
	{
		m_ansoply.GetFirstVideoGroupID(&videoGroupFirstGroupID);
		videoGroupNextGroupID = videoGroupFirstGroupID;

		LoadVideoObject(videoGroupFirstGroupID);

		for (int i = 1; i < uGroupCount; i++)
		{
			m_ansoply.GetNextVideoGroupID(&videoGroupNextGroupID);
			LoadVideoObject(videoGroupNextGroupID);
		}
	}*/
}

void  CTestAnsoplyDlg::LoadVideoObject(LONG groupID)
{
	ULONG videoFileCount = 0;
	ULONG videoFileFirstFileID = 0;
	ULONG videoFileNextFileID = 0;
	m_ansoply.GetVideoObjectCount(groupID, &videoFileCount);

	if (videoFileCount > 0)
	{
		m_ansoply.GetFirstVideoObjectID(groupID, &videoFileFirstFileID);
		videoFileNextFileID = videoFileFirstFileID;

		BSTR fileName;
		m_ansoply.GetVideoObjectFileName(groupID, videoFileFirstFileID, &fileName);

		for (int i = 1; i < videoFileCount; i++)
		{
			m_ansoply.GetNextVideoObjectID(groupID, &videoFileNextFileID);

			BSTR fileName2;
			m_ansoply.GetVideoObjectFileName(groupID, videoFileNextFileID, &fileName2);
		}
	}
}

void CTestAnsoplyDlg::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
	m_ansoply.SetDefaultVideoSize(m_uGroupID, 0, 0);
}

void CTestAnsoplyDlg::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here
//	m_ansoply.SetPlayRate(m_uGroupID, 1.50);
//	m_ansoply.BringUp(m_uGroupID);
	ULONG uID = 0;
	ULONG uType = 0;
	m_ansoply.SelectObjectByCoordinate(&uID, &uType, 10, 10, 0xFFFFFF00);
}

void CTestAnsoplyDlg::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here
/*
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 320;
	rect.bottom = 240;
	m_Video.MoveWindow(&rect);
	m_ansoply.SetVideoPosAndSize(m_uGroupID, 0, 0, rect.right, rect.bottom);
*/
//	ULONG uFileID = m_uFileID;
//	m_ansoply.DelVideoFile(m_uGroupID, uFileID);
//	m_ansoply.Pause(m_uGroupID);
//	m_ansoply.SelectVideoGroup(m_uGroupID, 0xFF006E7F);
//	m_ansoply.DelBitmap(m_uBitmapID);
//	m_ansoply.BringUp(m_uGroupID);
	m_ansoply.BringUp(m_uGroupID);
}

void CTestAnsoplyDlg::OnBnClickedButton14()
{
//	BSTR a;
//	_com_util::ConvertBSTRToString(a);
//	m_ansoply.Stop(m_uGroupID);
	m_ansoply.BringUp(m_uBitmapID);
}

void CTestAnsoplyDlg::OnLvnItemchangedGroupList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_videoList.DeleteAllItems();

	char szID[16];
	m_groupList.GetItemText(pNMLV->iItem, 0, szID, 16);
	
	int nGroupID = atoi(szID);
	
	ULONG uCount = 0;
	ULONG uFileID = 0;
	m_ansoply.GetVideoObjectCount(nGroupID, &uCount);
	if (uCount > 0)
	{
		m_ansoply.GetFirstVideoObjectID(nGroupID, &uFileID);
		do
		{
//			CHAR fileName[MAX_PATH] = {0};
			BSTR fileName;
			m_ansoply.GetVideoObjectFileName(nGroupID, uFileID, &fileName);
			CString sFileName;
			CString sFileID;
			sFileName = fileName;
			sFileID.Format("%d", uFileID);
			int nItem = m_videoList.InsertItem(0xff, sFileID);
			m_videoList.SetItemText(nItem, 1, sFileName);
			m_ansoply.GetNextVideoObjectID(nGroupID, &uFileID);
		} while( uFileID > 0 );
	}

	*pResult = 0;
}

void CTestAnsoplyDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_ansoply.Close();
	OnCancel();
}
