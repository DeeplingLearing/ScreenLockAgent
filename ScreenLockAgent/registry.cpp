#include "stdafx.h"
#include "registry.h"

void SetRegValue(HKEY hKey,CString str_hkey,CString str_childkey,
				 DWORD childkeyvalue)
{
	HKEY childkey = 0;
	DWORD dispos;

	RegCreateKeyEx(hKey,(LPCTSTR)str_hkey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&childkey,&dispos);
	RegSetValueEx(childkey,(LPCTSTR)str_childkey,0,REG_DWORD,(const BYTE*)&childkeyvalue,sizeof(DWORD));
	RegCloseKey(childkey);

}

void SetRegValue(HKEY hKey,CString str_hkey,CString str_childkey,
				 CString childkeyvalue)

{
	HKEY childkey = 0;
	DWORD dispos;

	RegCreateKeyEx(hKey,(LPCTSTR)str_hkey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&childkey,&dispos);
	RegSetValueEx(childkey,(LPCTSTR)str_childkey,0,REG_SZ,(const BYTE*)(LPCTSTR)childkeyvalue,childkeyvalue.GetLength());
	RegCloseKey(childkey);
}

