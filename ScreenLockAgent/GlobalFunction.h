
#include "stdafx.h"

CString GetExePath();
CString GetSelfLogPath();
BOOL	OnCheckPassword (LPCTSTR lpszPassword);
void	AddLog (BOOL nShow, LPCTSTR lpszStatus, char *str, ...);
bool	GetFolder(CString &folderpath, const TCHAR* szCaption, HWND hOwner);
bool	GetFile(CString &filepath);