#include "stdafx.h"

#define HKLM			HKEY_LOCAL_MACHINE
#define HKCU			HKEY_CURRENT_USER

#define SYSTEM_PATH					"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"
#define DISABLE_TASK				"DisableTaskMgr"
#define DISABLE_CHANGE_PASSWORD		"DisableChangePassword"
#define DISABLE_LOCK_WORKSTATION	"DisableLockWorkstation"
#define DISABLE_USER_CHANGE			"HideFastUserSwitching"

#define EXPLORER_PATH	"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"
#define	DISABLE_LOGOFF	"NoLogoff"
#define	DISABLE_CLOSE	"NoClose"

void SetRegValue(HKEY hKey,CString str_hkey,CString str_childkey,
				 DWORD childkeyvalue);

void SetRegValue(HKEY hKey,CString str_hkey,CString str_childkey,
				 CString childkeyvalue);
