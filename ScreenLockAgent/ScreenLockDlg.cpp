// ScreenLockDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ScreenLockAgent.h"
#include "ScreenLockDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
//#include "ManagerDlg.h"

// CScreenLockDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CScreenLockDlg, CDialog)

CScreenLockDlg::CScreenLockDlg(BOOL bPrimary, CWnd* pParent /*=NULL*/)
	: CDialog(CScreenLockDlg::IDD, pParent)
	, m_bPrimary (TRUE)
{
	m_pParentDlg = pParent;
	m_bPrimary = bPrimary;
	m_strInputPassword = _T("");
}

CScreenLockDlg::~CScreenLockDlg()
{
}

void CScreenLockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strInputPassword);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CScreenLockDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CScreenLockDlg 메시지 처리기입니다.

BOOL CScreenLockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	long style = ::GetWindowLong (this->m_hWnd,GWL_STYLE);
	style &= ~WS_CAPTION;
	::SetWindowLong (this->m_hWnd,GWL_STYLE,style);

	if (!m_bPrimary)
	{
		// 주제어 모니터가 아닐 경우, 컨트롤 박스 제거
		GetDlgItem (IDC_EDIT_PASSWORD)->ShowWindow (SW_HIDE);
		GetDlgItem (IDOK)->ShowWindow (SW_HIDE);
	}

	GotoDlgCtrl (GetDlgItem(IDC_EDIT_PASSWORD));

	return FALSE;
}

void CScreenLockDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

BOOL CScreenLockDlg::PreTranslateMessage(MSG* pMsg)
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

void CScreenLockDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer (nIDEvent);

	this->SetWindowPos (&wndTopMost, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE);

	CDialog::OnTimer(nIDEvent);
}

void CScreenLockDlg::OnShow ()
{
	CRect rcBase, rcInput, rcButton;
	int nControlWidth, nControlHeight;
	int nX, nY;
	const int nOffsetX = 20, nOffsetY = 53;

	// 주제어 모니터일 경우 비밀번호 입력 창 화면 중앙으로 배치
	if (m_bPrimary)
	{
		this->GetWindowRect (&rcBase);
		GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowRect (&rcInput);
		GetDlgItem(IDOK)->GetWindowRect (&rcButton);

		nControlWidth = rcInput.Width() + rcButton.Width() + 5;
		nControlHeight = rcInput.Height() + rcButton.Height();

		nX = (rcBase.Width() / 2) - (nControlWidth / 2) + nOffsetX;
		nY = (rcBase.Height() / 2) - (nControlHeight / 2) + nOffsetY;

		rcInput.right = nX + rcInput.Width();
		rcInput.left = nX;
		rcInput.bottom = nY + rcInput.Height();
		rcInput.top = nY;

		nX = rcInput.right + 5;

		rcButton.right = nX + rcButton.Width();
		rcButton.left = nX;
		rcButton.bottom = nY + rcButton.Height();
		rcButton.top = nY;

		GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow (&rcInput);
		GetDlgItem(IDOK)->MoveWindow (&rcButton);

		SetTimer (_TIMER_TOPMOST, 100, NULL);
	}

	this->ShowWindow (SW_SHOW);
}

void CScreenLockDlg::OnHide ()
{
	KillTimer (_TIMER_TOPMOST);
	this->ShowWindow (SW_HIDE);
}

void CScreenLockDlg::OnBnClickedOk()
{
	UpdateData (TRUE);

	if (m_strPassword != m_strInputPassword)
	{
		MessageBox (TEXT("비밀번호가 일치하지 않습니다!!"), _WARNING);
		return;
	}

	if (m_pParentDlg != NULL)
	{
		((CMainFrame*)m_pParentDlg)->GetScreenFunction()->OnCancleScreen ();
	}

	m_strInputPassword = "";
	UpdateData (FALSE);

	CDialog::OnOK();
}
