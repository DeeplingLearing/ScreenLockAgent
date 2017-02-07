
#include "stdafx.h"
#include "ScreenLockDlg.h"

namespace ScreenLock {
	enum {
		_PRIMARY_MONITOR=1,
		_OTHER_MONITOR=2,

		_MAX_MONITOR_CNT=10,

		_REGISTRY_STATUS_HIDE=1,
		_REGISTRY_STATUS_SHOW=0
	};

	typedef struct {
		int nType;
		int nX;
		int nY;
		int nWidth;
		int nHeight;
	} MONITOR_INFO_T;
}

class CScreenLock {
public:
	CScreenLock ();
	~CScreenLock ();

	BOOL	OnInit (CWnd* pParent);
	BOOL	OnLockScreen (LPCTSTR lpszPassword);
	BOOL	OnCancleScreen ();

	CString	GetLastErrorMsg () { return m_strLastErrorMsg; }

protected:
	void SetLockScreenDlg ();
	BOOL CheckPassword (LPCTSTR lpszPassword);
	void SetRegistry (int nStatus = ScreenLock::_REGISTRY_STATUS_SHOW);

protected:
	CWnd		*m_pParentDlg;
	HINSTANCE	m_hHookInst;

	typedef int (WINAPI *FInstallHook) (HWND hwnd);
	typedef BOOL (WINAPI *FUninstallHook) ();

	FInstallHook	m_fnInstallHook;
	FUninstallHook	m_fnUninstallHook;

	CScreenLockDlg	*m_pLockDlgList[ScreenLock::_MAX_MONITOR_CNT];
	CPtrList		m_MonitorList;

	CString			m_strLastErrorMsg;
};
