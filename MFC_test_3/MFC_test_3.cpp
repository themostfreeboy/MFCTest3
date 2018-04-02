
// MFC_test_3.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MFC_test_3.h"
#include "MFC_test_3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_test_3App

BEGIN_MESSAGE_MAP(CMFC_test_3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC_test_3App ����

CMFC_test_3App::CMFC_test_3App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFC_test_3App ����

CMFC_test_3App theApp;


// CMFC_test_3App ��ʼ��

BOOL CMFC_test_3App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	ChangeWndMessageFilter( WM_DROPFILES, TRUE );

	CMFC_test_3Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


// �����ļ��Ϸ�����¼���Ϣ������win7��Ч���Խ��win7���ļ��Ϸ�ʧЧ������//
//ChangeWndMessageFilter( WM_DROPFILES, TRUE );
//ChangeWndMessageFilter( 0x0049, TRUE ); // 0x0049 - WM_COPYGLOBALDATA

BOOL CMFC_test_3App::ChangeWndMessageFilter( UINT uMessage, BOOL bAllow )
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
