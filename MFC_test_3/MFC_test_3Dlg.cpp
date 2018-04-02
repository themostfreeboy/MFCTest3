
// MFC_test_3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_test_3.h"
#include "MFC_test_3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_test_3Dlg 对话框




CMFC_test_3Dlg::CMFC_test_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_test_3Dlg::IDD, pParent)
	, EditValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_test_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, EditControl);
	DDX_Text(pDX, IDC_EDIT1, EditValue);
}

BEGIN_MESSAGE_MAP(CMFC_test_3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC_test_3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFC_test_3Dlg::OnBnClickedCancel)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMFC_test_3Dlg 消息处理程序

BOOL CMFC_test_3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->DragAcceptFiles(TRUE);
	GetDlgItem(IDC_EDIT1)->DragAcceptFiles(TRUE);
	//DropFileFix();
	ChangeWndMessageFilter( WM_DROPFILES, TRUE );
	ChangeWndMessageFilter( 0x0049, TRUE );
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
    ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_test_3Dlg::OnPaint()
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
HCURSOR CMFC_test_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_test_3Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	exit(0);
}


void CMFC_test_3Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	exit(0);
}


void CMFC_test_3Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	AfxMessageBox(_T("hello!!!"),MB_OK,NULL);
    if(hDropInfo)
    {
        int nDrag;//拖拽文件的数量
        nDrag = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
        if(nDrag == 1)
        {
            TCHAR Path[MAX_PATH+1] = {0};//被拖拽的文件的文件名
			DragQueryFile(hDropInfo, 0, Path, MAX_PATH);
            //SetWindowText(Path);//把文件名显示出来
			//UpdateData(FALSE);
			//SetDlgItemText(IDC_EDIT1,Path);
			EditValue.Format(_T("%s"),Path);
			UpdateData(TRUE);
			AfxMessageBox(_T("hello"),MB_OK,NULL);
        }
        else
        {
            AfxMessageBox(_T("只能拖拽一个文件！！"),MB_OK,NULL);
        }
    }

	CDialogEx::OnDropFiles(hDropInfo);
}


// 放行文件拖放相关事件消息，仅对win7有效，以解决win7中文件拖放失效的问题//
//ChangeWndMessageFilter( WM_DROPFILES, TRUE );
//ChangeWndMessageFilter( 0x0049, TRUE ); // 0x0049 - WM_COPYGLOBALDATA

BOOL CMFC_test_3Dlg::ChangeWndMessageFilter( UINT uMessage, BOOL bAllow )
{
	typedef BOOL (WINAPI* ChangeWindowMessageFilterFn)( UINT, DWORD );
	HMODULE hUserMod = NULL;
	BOOL bResult = FALSE;
	hUserMod = LoadLibrary( _T("user32.dll") );
	if ( hUserMod == NULL )
	{
		return FALSE;
	}

    // 获取ChangeWindowMessageFilter函数接口指针
	ChangeWindowMessageFilterFn pfnChangeWindowMessageFilter = (ChangeWindowMessageFilterFn)GetProcAddress( hUserMod, "ChangeWindowMessageFilter" );
	if ( pfnChangeWindowMessageFilter == NULL )
	{
		FreeLibrary( hUserMod );
		return FALSE;
	}

	bResult = pfnChangeWindowMessageFilter( uMessage, bAllow?1:2 ); // 1-MSGFLT_ADD, 2-MSGFLT_REMOVE
	FreeLibrary( hUserMod );
	return bResult;
}