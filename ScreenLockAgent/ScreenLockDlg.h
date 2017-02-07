#pragma once

#include "resource.h"

// CScreenLockDlg ��ȭ �����Դϴ�.

class CScreenLockDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenLockDlg)

public:
	CScreenLockDlg(BOOL bPrimary, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CScreenLockDlg();

	BOOL	IsPrimary () { return m_bPrimary; }
	void	SetPassword (LPCTSTR lpszPassword) { m_strPassword = lpszPassword; }

	void	OnShow ();
	void	OnHide ();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_SCREENLOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

	CWnd	*m_pParentDlg;
	BOOL	m_bPrimary;
	CString	m_strPassword;

public:
	CString m_strInputPassword;
	CButton m_btnOK;
};
