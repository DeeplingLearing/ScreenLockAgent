#pragma once

#include "resource.h"

// CScreenLockDlg 대화 상자입니다.

class CScreenLockDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenLockDlg)

public:
	CScreenLockDlg(BOOL bPrimary, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScreenLockDlg();

	BOOL	IsPrimary () { return m_bPrimary; }
	void	SetPassword (LPCTSTR lpszPassword) { m_strPassword = lpszPassword; }

	void	OnShow ();
	void	OnHide ();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SCREENLOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
