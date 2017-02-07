
#include "stdafx.h"
#include "GlobalFunction.h"

#include "MainFrm.h"
#include "ScreenLockAgentDoc.h"
#include "ScreenLockAgentView.h"

CString GetExePath()
{
	TCHAR Path[MAX_PATH];
	TCHAR *ext;
	CString strPath;

	 /* Get Module Path */
	GetModuleFileName(NULL, Path, MAX_PATH);
	ext = Path + _tcslen(Path);
	while (ext != Path && *ext != TEXT('\\') && *ext != TEXT(':'))
		*ext-- = 0;

	strPath.Format (_T("%s"), Path);

	return strPath;
}

CString GetSelfLogPath()
{
	CString strPath;

	strPath.Format(TEXT("%slog\\"), GetExePath());

	return strPath;
}

int OnCheckPassword (LPCTSTR lpszPassword)
{
	int nLen;

	nLen = _tcslen (lpszPassword);
	if( (nLen < _MIN_PASSWORD_LEN) || (nLen > _MAX_PASSWORD_LEN) )
	{
		return -1;
	}

	return 0;
}

void AddLog (BOOL nShow, LPCTSTR lpszStatus, char *str, ...)
{
	TCHAR		temp[MAX_PATH+1];
	va_list		pvar;

	CFile	file;
	CString	strLogFile, strLogDate, strLogMsg;
	CTime	t = CTime::GetCurrentTime ();

	CMainFrame		*pMain;
	CScreenLockAgentView	*pView;

	memset(temp, 0x0, sizeof(temp));

	va_start(pvar, str);
#ifndef WIN32
	vsnprintf(temp, MAX_PATH, str, pvar);
#else
	_vsnprintf(temp, MAX_PATH, str, pvar);
#endif
	va_end(pvar);

	if(temp[strlen(temp)-1] == 10)	// ÁÙ¹Ù²Þ Á¦°Å
		temp[strlen(temp)-1] = 0;

	strLogFile.Format(TEXT("%s%s_%04d%02d%02d.log"), 
		GetSelfLogPath(), _PROGRAM_NAME, t.GetYear(), t.GetMonth(), t.GetDay());

	if(file.Open(strLogFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyNone))
	{
		strLogDate = t.Format(_CTIME_CURRENT_FORMAT);
		strLogMsg.Format(TEXT("%s;%s;%s\n"), strLogDate, lpszStatus, temp);
			
		file.SeekToEnd();
		file.Write(strLogMsg, strLogMsg.GetLength());
		file.Close();
	}

	if(nShow)
	{
		pMain = (CMainFrame*)AfxGetMainWnd();
		if(pMain == NULL)	return;
	
		pView = (CScreenLockAgentView*)pMain->GetActiveView();
		if(pView == NULL) return;

		//CString	*pstrPageText = new CString(temp);
		pView->AddLogToList (strLogDate, temp);
	}
}

bool GetFolder(CString &folderpath, const TCHAR* szCaption, HWND hOwner)
{
   bool retVal = false;

   // The BROWSEINFO struct tells the shell 
   // how it should display the dialog.
   BROWSEINFO bi;
   memset(&bi, 0, sizeof(bi));

   bi.ulFlags   = 0;//BIF_USENEWUI;
   bi.hwndOwner = hOwner;
   bi.lpszTitle = szCaption;

   // must call this if using BIF_USENEWUI
   ::OleInitialize(NULL);

   // Show the dialog and get the itemIDList for the 
   // selected folder.
   LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);

   if(pIDL != NULL)
   {
      // Create a buffer to store the path, then 
      // get the path.
      TCHAR buffer[_MAX_PATH] = {'\0'};
      if(::SHGetPathFromIDList(pIDL, buffer) != 0)
      {
         // Set the string value.
         folderpath = buffer;
         retVal = true;
      }

      // free the item id list
      CoTaskMemFree(pIDL);
   }

   ::OleUninitialize();

   return retVal;
}

bool GetFile(CString &filepath)
{
	bool retVal = false;
	char szFilter[] = "Image (*.JPG, *.PNG) | *.JPG;*.PNG||";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		filepath = dlg.GetPathName();
		retVal = true;
	}

	return retVal;
}