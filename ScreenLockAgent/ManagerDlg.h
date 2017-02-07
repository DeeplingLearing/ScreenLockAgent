#pragma once


// CManagerDlg ��ȭ �����Դϴ�.

class CManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CManagerDlg)

public:
	CManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CManagerDlg();

	static void Load ();
	static void Save ();
	static void ChangePassword (LPCTSTR lpszPassword);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonPwChange();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	static CONFIG_INFO_T m_ConfigInfo;
	
protected:
	CONFIG_INFO_T	m_ConfigChangeInfo;

	CString m_strCurrentPassword;
	CString m_strPassword;
	CString m_strPasswordCheck;
	BOOL	m_bUseQuestionPwd;
	BOOL	m_bShowIcon;
	CString m_strAlertText;
};
