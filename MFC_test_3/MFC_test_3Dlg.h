
// MFC_test_3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFC_test_3Dlg �Ի���
class CMFC_test_3Dlg : public CDialogEx
{
// ����
public:
	CMFC_test_3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_TEST_3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit EditControl;
	CString EditValue;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	BOOL ChangeWndMessageFilter( UINT uMessage, BOOL bAllow );
};