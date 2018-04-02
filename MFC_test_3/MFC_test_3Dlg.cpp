
// MFC_test_3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_test_3.h"
#include "MFC_test_3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_test_3Dlg �Ի���




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


// CMFC_test_3Dlg ��Ϣ�������

BOOL CMFC_test_3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->DragAcceptFiles(TRUE);
	GetDlgItem(IDC_EDIT1)->DragAcceptFiles(TRUE);
	//DropFileFix();
	ChangeWndMessageFilter( WM_DROPFILES, TRUE );
	ChangeWndMessageFilter( 0x0049, TRUE );
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
    ChangeWindowMessageFilter(0x0049, MSGFLT_ADD); 

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_test_3Dlg::OnPaint()
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
HCURSOR CMFC_test_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_test_3Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	exit(0);
}


void CMFC_test_3Dlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	exit(0);
}


void CMFC_test_3Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	AfxMessageBox(_T("hello!!!"),MB_OK,NULL);
    if(hDropInfo)
    {
        int nDrag;//��ק�ļ�������
        nDrag = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
        if(nDrag == 1)
        {
            TCHAR Path[MAX_PATH+1] = {0};//����ק���ļ����ļ���
			DragQueryFile(hDropInfo, 0, Path, MAX_PATH);
            //SetWindowText(Path);//���ļ�����ʾ����
			//UpdateData(FALSE);
			//SetDlgItemText(IDC_EDIT1,Path);
			EditValue.Format(_T("%s"),Path);
			UpdateData(TRUE);
			AfxMessageBox(_T("hello"),MB_OK,NULL);
        }
        else
        {
            AfxMessageBox(_T("ֻ����קһ���ļ�����"),MB_OK,NULL);
        }
    }

	CDialogEx::OnDropFiles(hDropInfo);
}


// �����ļ��Ϸ�����¼���Ϣ������win7��Ч���Խ��win7���ļ��Ϸ�ʧЧ������//
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

    // ��ȡChangeWindowMessageFilter�����ӿ�ָ��
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