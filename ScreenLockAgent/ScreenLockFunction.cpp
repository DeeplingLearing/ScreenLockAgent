
#include "stdafx.h"
#include "ScreenLockFunction.h"
#include "ScreenLockDlg.h"
#include "registry.h"

using namespace ScreenLock;

CScreenLock::CScreenLock ()
{
	for (int i=0; i< _MAX_MONITOR_CNT; i++)
	{
		m_pLockDlgList[i] = NULL;
	}
}

CScreenLock::~CScreenLock ()
{
	for (int i=0; i< _MAX_MONITOR_CNT; i++)
	{
		if (m_pLockDlgList[i] != NULL)
		{
			delete m_pLockDlgList[i];
			m_pLockDlgList[i] = NULL;
		}
	}

	SetRegistry (_REGISTRY_STATUS_SHOW);
}

BOOL CScreenLock::OnInit (CWnd* pParent)
{
	m_pParentDlg = pParent;

#ifdef _DEBUG
	m_hHookInst = LoadLibrary("HookLibD.dll");
#else
	m_hHookInst = LoadLibrary("HookLib.dll");
#endif
	if (m_hHookInst == NULL)
	{
		return FALSE;
	}
	
	m_fnInstallHook = (FInstallHook)GetProcAddress (m_hHookInst, TEXT("SetLockHook"));
	m_fnUninstallHook = (FUninstallHook)GetProcAddress (m_hHookInst, TEXT("RemoveLockHook"));

	SetLockScreenDlg ();

	return TRUE;
}

BOOL CALLBACK MonitorEnumProc (HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    // 정보를 저장하기위해서 넘긴 리스트박스의 주소를 사용가능한 형태로 캐스팅한다.
	CPtrList *pList = (CPtrList*)dwData;
 
    // 모니터 정보를 가져올 구조체
    MONITORINFOEX mi;
    mi.cbSize = sizeof(MONITORINFOEX);

    // 모니터 핸들을 사용하여 해당 모니터 정보를 가져온다.
    GetMonitorInfo(hMonitor, &mi);

	MONITOR_INFO_T *pInfo;

	pInfo = new MONITOR_INFO_T;
	if (pInfo == NULL) return FALSE;
 
    CString str;
    // 주모니터로 설정된 모니터 정보인지를 체크한다.
    if(mi.dwFlags & MONITORINFOF_PRIMARY) 
	{
		pInfo->nType = _PRIMARY_MONITOR;
		
        str.Format("hMonitor = %X,  좌표 : [ ( %04d, %04d ) - ( %04d, %04d ) ], < Primary-Monitor > %s",
            hMonitor, lprcMonitor->left,lprcMonitor->top,lprcMonitor->right,lprcMonitor->bottom, mi.szDevice);
    } else 
	{
		pInfo->nType = _OTHER_MONITOR;

        str.Format("hMonitor = %X,  좌표 : [ ( %04d, %04d ) - ( %04d, %04d ) ], %s",
            hMonitor, lprcMonitor->left,lprcMonitor->top,lprcMonitor->right,lprcMonitor->bottom, mi.szDevice);
    }

	pInfo->nX = lprcMonitor->left;
	pInfo->nY = lprcMonitor->top;
	pInfo->nWidth = lprcMonitor->right - lprcMonitor->left;
	pInfo->nHeight = lprcMonitor->bottom - lprcMonitor->top;

	if (pList != NULL)
	{
		pList->AddTail (pInfo);
	}
 
    return TRUE;
}

void CScreenLock::SetLockScreenDlg ()
{
	int			i;
	BOOL		bPrimary = FALSE;
	POSITION	pos;
	MONITOR_INFO_T *pMonitor;

	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&m_MonitorList);
	if (m_MonitorList.GetCount () > 0)
	{
		i = 0;
		pos = m_MonitorList.GetHeadPosition ();
		while (pos != NULL)
		{
			pMonitor = (MONITOR_INFO_T*)m_MonitorList.GetNext (pos);
			if (pMonitor == NULL)	continue;

			if (pMonitor->nType == _PRIMARY_MONITOR)
				bPrimary = TRUE;
			else
				bPrimary = FALSE;

			m_pLockDlgList[i] = new CScreenLockDlg (bPrimary, m_pParentDlg);
			if (m_pLockDlgList[i] != NULL)
			{
				if (bPrimary)
				{
					m_pLockDlgList[i]->Create (IDD_DIALOG_SCREENLOCK, CWnd::GetDesktopWindow());
				}
				else
				{
					m_pLockDlgList[i]->Create (IDD_DIALOG_SCREENLOCK);
				}
				m_pLockDlgList[i]->SetWindowPos (&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE);
				m_pLockDlgList[i]->MoveWindow (pMonitor->nX, pMonitor->nY, pMonitor->nWidth, pMonitor->nHeight);
#ifdef _DEBUG
				break;
#endif
			}

			i++;
			if (i >= _MAX_MONITOR_CNT)
				break;
		}
	}
}

BOOL CScreenLock::CheckPassword (LPCTSTR lpszPassword)
{
	CString strPassword;
	int nLen = 0;

	strPassword = lpszPassword;
	if (strPassword.IsEmpty())
	{
		m_strLastErrorMsg.Format(TEXT("Screen Lock 해제 비밀번호를 입력하십시오!!"));
		return FALSE;
	}

	nLen = strPassword.GetLength ();
	if( (nLen < 4) || (nLen > 12) )
	{
		m_strLastErrorMsg.Format(TEXT("Screen Lock 해제 비밀번호 길이가 올바르지 않습니다(4~12 자리)!!"));
		return FALSE;
	}

	return TRUE;
}

void CScreenLock::SetRegistry (int nStatus)
{
	SetRegValue(HKLM, SYSTEM_PATH, DISABLE_TASK, nStatus);
	SetRegValue (HKCU, SYSTEM_PATH, DISABLE_TASK, nStatus);

	SetRegValue (HKCU, EXPLORER_PATH, DISABLE_LOGOFF, nStatus);
	SetRegValue (HKCU, EXPLORER_PATH, DISABLE_CLOSE, nStatus);

	SetRegValue (HKCU, SYSTEM_PATH, DISABLE_CHANGE_PASSWORD, nStatus);
	SetRegValue (HKCU, SYSTEM_PATH, DISABLE_LOCK_WORKSTATION, nStatus);
	
	SetRegValue (HKLM, SYSTEM_PATH, DISABLE_USER_CHANGE, nStatus);
}

//////////////
// Run
BOOL CScreenLock::OnLockScreen (LPCTSTR lpszPassword)
{
	int i, nRet = -1;

	if (m_fnInstallHook == NULL)
	{
		m_strLastErrorMsg.Format(TEXT("API Install 실패!!"));
		return FALSE;
	}

	if (CheckPassword (lpszPassword) == FALSE)
	{
		return FALSE;
	}

	nRet = m_fnInstallHook (AfxGetMainWnd()->m_hWnd);
	if (nRet == 0)
	{
		SetRegistry (_REGISTRY_STATUS_HIDE);

		for (i=0; i< ScreenLock::_MAX_MONITOR_CNT; i++)
		{
			if (m_pLockDlgList[i] != NULL)
			{
				if (m_pLockDlgList[i]->IsPrimary ())
				{
					m_pLockDlgList[i]->SetPassword (lpszPassword);
				}
				m_pLockDlgList[i]->OnShow ();
			}
		}
	}

	return TRUE;
}

BOOL CScreenLock::OnCancleScreen ()
{
	int i;

	if (m_fnUninstallHook == NULL)
	{
		m_strLastErrorMsg.Format(TEXT("API Uninstall 실패!!"));
		return FALSE;
	}

	SetRegistry (_REGISTRY_STATUS_SHOW);

	m_fnUninstallHook ();

	for (i=0; i< ScreenLock::_MAX_MONITOR_CNT; i++)
	{
		if (m_pLockDlgList[i] != NULL)
		{
			m_pLockDlgList[i]->OnHide ();
		}
	}

	return TRUE;
}
