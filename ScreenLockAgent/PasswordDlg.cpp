// PasswordDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ScreenLockAgent.h"
#include "PasswordDlg.h"
#include "afxdialogex.h"
#include "GlobalFunction.h"
#include "ManagerDlg.h"


// CPasswordDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialog)

CPasswordDlg::CPasswordDlg(int nStatus, CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
	, m_nStatus (_CHECK_PASSWORD)
{
	m_nStatus = nStatus;
	m_strPassword = _T("");
}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPasswordDlg 메시지 처리기입니다.


BOOL CPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_nStatus == _EMPTY_PASSWORD)
	{
		MessageBox (TEXT("비밀번호를 설정하십시오!"), _INFO);
	}

	GotoDlgCtrl(GetDlgItem(IDC_EDIT_PASSWORD));

	return FALSE;
}

BOOL CPasswordDlg::PreTranslateMessage(MSG* pMsg)
{
	if( (pMsg->wParam == VK_ESCAPE) || (pMsg->wParam == VK_SPACE))
	{
        return TRUE;
	}
	else if (pMsg->wParam == VK_RETURN)
	{
		GetDlgItem (IDOK)->SendMessage (BN_CLICKED);
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CPasswordDlg::OnBnClickedOk()
{
	CString str;

	UpdateData ();

	if (m_nStatus == _EMPTY_PASSWORD)
	{
		if (OnCheckPassword (m_strPassword) != 0)
		{
			str.Format (TEXT("비밀번호 길이는 %d ~ %d 자이며, 특수문자가 포함되어야 합니다."), _MIN_PASSWORD_LEN, _MAX_PASSWORD_LEN);
			MessageBox (str, _ERROR);
			return;
		}

		CManagerDlg::ChangePassword (m_strPassword);
	}
	else
	{
		if (m_strPassword != CManagerDlg::m_ConfigInfo.strPassword)
		{
			MessageBox (TEXT("비밀번호가 일치하지 않습니다."), _ERROR);
			m_strPassword = TEXT("");
			UpdateData (FALSE);
			return;
		}
	}
	
	CDialog::OnOK();
}
