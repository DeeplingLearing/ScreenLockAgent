#pragma once


// CPasswordDlg ��ȭ �����Դϴ�.

class CPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(int nStatus=_CHECK_PASSWORD, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPasswordDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

protected:
	int		m_nStatus;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	CString m_strPassword;
};
