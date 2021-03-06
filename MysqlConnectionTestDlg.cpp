
// MysqlConnectionTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MysqlConnectionTest.h"
#include "MysqlConnectionTestDlg.h"
#include "afxdialogex.h"
#include "Utility\mysql\MySQLConnector.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMysqlConnectionTestDlg 对话框



CMysqlConnectionTestDlg::CMysqlConnectionTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMysqlConnectionTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMysqlConnectionTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMysqlConnectionTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMysqlConnectionTestDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMysqlConnectionTestDlg 消息处理程序

BOOL CMysqlConnectionTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMysqlConnectionTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMysqlConnectionTestDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMysqlConnectionTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMysqlConnectionTestDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	MYSQL* m_sqlCon;
	m_sqlCon = mysql_init((MYSQL*) 0);
	char* query = NULL;
	int rt;
	CString string;
	// localhost:??? root????? test????? 3306???  
	try{
		if (mysql_real_connect(m_sqlCon, "localhost", "root", "admin000", "test", 3306, NULL, 0))
		{
			MessageBox(_T("connection ok!"));
			if (!mysql_select_db(m_sqlCon, "test"))
			{
				MessageBox(_T("Select successfully the database!\n"));

				m_sqlCon->reconnect = 1;

				query = "set names \'GBK\'";
				//mysql_query(con,"set names \'GBK\'"); 

				rt = mysql_real_query(m_sqlCon, query, strlen(query));
				if (rt)
				{
					MessageBox(_T("Error making query: %s !!!\n", mysql_error(m_sqlCon)));
				}
				else
				{
					MessageBox(_T("query %s succeed!\n", query));
					query = "select * from test.userinfo;";
					rt = mysql_real_query(m_sqlCon, query, strlen(query));
					MYSQL_RES *res;
					res = mysql_store_result(m_sqlCon);
					MYSQL_ROW row;
					while (row = mysql_fetch_row(res))
					{
						for (int t = 0; t < mysql_num_fields(res); t++)
						{
							
							string = row[t];
							MessageBox(string);
						}
					}

				}

			}
		}
		else{
			CString str;
			GetDlgItem(IDC_STATIC)->GetWindowTextW(str);
			MessageBox(_T("connection no!"));
		}
		mysql_close(m_sqlCon);
	}
	catch (MYSQL ex){

	}
}


HBRUSH CMysqlConnectionTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		GetDlgItem(IDC_STATIC)->SetWindowTextW(_T("I LOVE YOU"));
		//pDC->SetTextColor(RGB(0, 0, 250));
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
