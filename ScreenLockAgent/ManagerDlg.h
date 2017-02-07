#pragma once


// CManagerDlg 대화 상자입니다.

class CManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CManagerDlg)

public:
	CManagerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManagerDlg();

	static void Load ();
	static void Save ();
	static void ChangePassword (LPCTSTR lpszPassword);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
