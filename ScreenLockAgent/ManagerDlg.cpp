// ManagerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ScreenLockAgent.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "GlobalFunction.h"

// CManagerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManagerDlg, CDialog)

CONFIG_INFO_T CManagerDlg::m_ConfigInfo;

CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManagerDlg::IDD, pParent)
{
	m_strPassword = _T("");
	m_strPasswordCheck = _T("");
	m_strCurrentPassword = _T("");
	m_strAlertText = _T("");
}

CManagerDlg::~CManagerDlg()
{
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_CHECK, m_strPasswordCheck);
	DDX_Text(pDX, IDC_EDIT_CURRENT_PASSWORD, m_strCurrentPassword);
	DDX_Check(pDX, IDC_CHECK_USE_CONFIG_LOCK, m_bUseQuestionPwd);
}


BEGIN_MESSAGE_MAP(CManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PW_CHANGE, OnBnClickedButtonPwChange)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CManagerDlg 메시지 처리기입니다.


void CManagerDlg::Load ()
{
	TCHAR	strTemp[512];
	CString strConfigPath;

	::ZeroMemory (&m_ConfigInfo, sizeof(CONFIG_INFO_T));

	strConfigPath.Format (TEXT("%s%s.cfg"), GetExePath(), _PROGRAM_NAME);

	GetPrivateProfileString (_CONFIG, _PASSWORD, "", strTemp, sizeof(strTemp), strConfigPath);
	_tcsncpy (m_ConfigInfo.strPassword, strTemp, sizeof(m_ConfigInfo.strPassword));
}

void CManagerDlg::Save ()
{
	CString	strTemp;
	CString strConfigPath;

	strConfigPath.Format (TEXT("%s%s.cfg"), GetExePath(), _PROGRAM_NAME);

	strTemp.Format (TEXT("%d"), m_ConfigInfo.nQuestionPwd);
	WritePrivateProfileString (_CONFIG, _QUESTION_PWD, strTemp, strConfigPath);
}

void CManagerDlg::ChangePassword (LPCTSTR lpszPassword)
{
	TCHAR	strTemp[512];
	CString strConfigPath;

	_tcsncpy (m_ConfigInfo.strPassword, lpszPassword, sizeof(m_ConfigInfo.strPassword));

	strConfigPath.Format (TEXT("%s%s.cfg"), GetExePath(), _PROGRAM_NAME);
	WritePrivateProfileString (_CONFIG, _PASSWORD, m_ConfigInfo.strPassword, strConfigPath);
}

BOOL CManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	::memcpy (&m_ConfigChangeInfo, &m_ConfigInfo, sizeof(CONFIG_INFO_T));

	if (m_ConfigChangeInfo.strPassword[0] == 0)
	{
		GetDlgItem (IDC_EDIT_CURRENT_PASSWORD)->EnableWindow (FALSE);
		GetDlgItem (IDC_CHECK_USE_CONFIG_LOCK)->EnableWindow (FALSE);
	}

	m_bUseQuestionPwd = m_ConfigChangeInfo.nQuestionPwd;

	UpdateData (FALSE);

	return TRUE;
}

BOOL CManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	if( (pMsg->wParam == VK_ESCAPE) || (pMsg->wParam == VK_RETURN) )
	{
        return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CManagerDlg::OnBnClickedButtonPwChange()
{
	CString str;

	UpdateData ();

	if (m_ConfigInfo.strPassword[0] != 0)
	{
		if (m_strCurrentPassword != m_ConfigInfo.strPassword)
		{
			MessageBox (TEXT("현재 비밀번호가 일치하지 않습니다."), _ERROR);
			return;
		}
	}

	if (m_strPassword.IsEmpty())
	{
		MessageBox (TEXT("새 비밀번호를 입력하십시오!"), _ERROR);
		return;
	}

	if (m_strPasswordCheck.IsEmpty())
	{
		MessageBox (TEXT("비밀번호 확인을 입력하십시오!"), _ERROR);
		return;
	}

	if( (m_strPassword.Find(TEXT(" ")) != -1) || (m_strPasswordCheck.Find(TEXT(" ")) != -1) )
	{
		MessageBox (TEXT("비밀번호에 공백은 사용 할 수 없습니다."), _ERROR);
		return;
	}

	if (m_strPassword != m_strPasswordCheck)
	{
		MessageBox (TEXT("새 비밀번호와 비밀번호 확인이 일치하지 않습니다."), _ERROR);
		return;
	}

	if (OnCheckPassword (m_strPassword) != 0)
	{
		str.Format (TEXT("비밀번호 길이는 %d ~ %d 자이며, 특수문자가 포함되어야 합니다."), _MIN_PASSWORD_LEN, _MAX_PASSWORD_LEN);
		MessageBox (str, _ERROR);
		return;
	}

	ChangePassword (m_strPassword);
	_tcsncpy (m_ConfigChangeInfo.strPassword, m_strPassword, sizeof(m_ConfigInfo.strPassword));

	m_strCurrentPassword = m_strPassword = m_strPasswordCheck = TEXT("");
	UpdateData (FALSE);

	AddLog (_SHOW, _INFO, TEXT("비밀번호 변경 완료"));
	MessageBox (TEXT("비밀번호 변경 완료"), _INFO);

	GetDlgItem (IDC_EDIT_CURRENT_PASSWORD)->EnableWindow (TRUE);
	GetDlgItem (IDC_CHECK_USE_CONFIG_LOCK)->EnableWindow (TRUE);
}

void CManagerDlg::OnBnClickedOk()
{
	UpdateData ();

	m_ConfigChangeInfo.nQuestionPwd = m_bUseQuestionPwd;

	if (::memcmp (&m_ConfigInfo, &m_ConfigChangeInfo, sizeof(CONFIG_INFO_T)) != 0)
	{
		::memcpy (&m_ConfigInfo, &m_ConfigChangeInfo, sizeof(CONFIG_INFO_T));
		Save ();

		AddLog (_SHOW, _INFO, TEXT("설정 변경 완료"));
		MessageBox (TEXT("설정 변경 완료"), _INFO);
	}
	
	CDialog::OnOK();
}
