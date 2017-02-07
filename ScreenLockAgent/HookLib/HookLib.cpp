// HookLib.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "stdio.h"
#include <HookLib.h>

#include <iostream>
using namespace std;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

//---------------------------------------------------
// Global Variables
// 공용 메모리
//---------------------------------------------------

#pragma data_seg(".HKT")
HINSTANCE g_Module = NULL ;     // DLL Handle 
HHOOK g_KeyHook = NULL ;		// Hook Handle
HHOOK g_MouseHook = NULL ;		// Hook Handle
HWND g_HwndServer = NULL ;      // Hook Server Window Handle
int	nCnt=0;
POINT g_Start, g_End;
#pragma data_seg()
#pragma comment (linker, "/SECTION:.HKT,RWS")

/*
const int VK_TAB = 0x09;
const int VK_ESCAPE = 0x1b;
const int VK_LWIN = 0x5b;
const int VK_RWIN = 0x5c;

// low level hook flags
const int KF_EXTENDED = 0x0100;
const int KF_ALTDOWN = 0x2000;
const int LLKHF_EXTENDED = (KF_EXTENDED >> 8);
const int LLKHF_ALTDOWN = (KF_ALTDOWN >> 8);
*/

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			g_Module = (HINSTANCE)hModule; // Save Dll Handle
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			RemoveLockHook ();
		}
		break;
	}

    return TRUE;
}

HINSTANCE GetDLLInstance()
{
	return g_Module;
}

//--------------------------------------------------------------
// Hook Procedure - Keyboard
//--------------------------------------------------------------
LRESULT CALLBACK KeyboardLLProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
	TCHAR	szMsg[MAX_PATH*2];

	TCHAR	szPath[MAX_PATH];
	TCHAR	*pFileName = NULL;

	if( nCode >= 0)
	{
		PKBDLLHOOKSTRUCT p = ( PKBDLLHOOKSTRUCT ) lParam;

		GetModuleFileName (NULL, szPath, MAX_PATH);
		pFileName = strrchr (szPath, '\\') + 1;
		
		sprintf(szMsg, "[%s] Hook Key : %0x(%d) Count : %d\n", pFileName, p->vkCode, p->flags, nCnt++);
		OutputDebugString (szMsg);

		if (
			((p->vkCode == VK_TAB) && (p->flags == LLKHF_ALTDOWN)) ||		// Alt + Tab
			((p->vkCode == VK_ESCAPE) && (p->flags == LLKHF_ALTDOWN)) ||	// Alt + Esc
			((p->vkCode == VK_ESCAPE) && (p->flags == 0)) ||				// Esc
			((p->vkCode == VK_LWIN) && (p->flags == LLKHF_EXTENDED)) ||
			((p->vkCode == VK_RWIN) && (p->flags == LLKHF_EXTENDED)) ||
			((true) && (p->flags == LLKHF_ALTDOWN))							// Alt
		)
		{
			return true;
		}
		else if(
			((p->vkCode == VK_RETURN) && (p->flags == LLKHF_EXTENDED)) ||	// Number Enter
			((p->vkCode == VK_RETURN) && (p->flags == 0))					// Enter
		)
		{
		}
		else if (p->flags == 0)
		{
			if ((p->vkCode >= VK_MULTIPLY) && (p->vkCode <= VK_F24))
			{
				return true;
			}
		}
	}

	// We must pass the all messages on to CallNextHookEx.
	return ::CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL bCheck = FALSE;

	if( nCode == HC_ACTION )
	{
		MOUSEHOOKSTRUCT* pMouse = (MOUSEHOOKSTRUCT*)lParam;

		if(wParam != WM_MOUSEMOVE)
		{
			switch (wParam)
			{
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_RBUTTONDBLCLK:
				bCheck = TRUE;
				break;
#if 0
			case WM_LBUTTONDOWN:
			case WM_LBUTTONDBLCLK:
				{
					if (
						(pMouse->pt.x < g_Start.x) || (pMouse->pt.x > g_End.x) ||
						(pMouse->pt.y < g_Start.y) || (pMouse->pt.y > g_End.y)
					)
					{
						//bCheck = TRUE;
					}
					else
					{
						bCheck = FALSE;
					}
				}
				break;
#endif
			default:
				bCheck = FALSE;
				break;
			}
		}
	}

	if (bCheck)
	{
		return 1;
	}

	if ((g_HwndServer != NULL) && (wParam != WM_MOUSEMOVE))
	{
		::SendMessage( g_HwndServer, WM_HOOK_MOUSE, wParam, lParam);
	}

	return ::CallNextHookEx(NULL, nCode, wParam, lParam);
}

//------------------------------------------------------------------
// Set Hook
//------------------------------------------------------------------
int SetKeyHook () 
{
	int nCode = -1;
	if (g_KeyHook == NULL)
	{
		g_KeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardLLProcedure, (HINSTANCE)g_Module, 0);
		if(g_KeyHook == NULL)
		{
			nCode = _KEY_INSTALL_FAIL;
		}
		else
		{
			nCode = 0;
		}

		return nCode;
	}
	
	return _KEY_INSTALL;
}

int SetMouseHook ()
{
	int nCode = -1;
	if (g_MouseHook == NULL)
	{
		g_MouseHook = SetWindowsHookEx( WH_MOUSE_LL, MouseProcedure, (HINSTANCE)g_Module, 0);
		if(g_MouseHook == NULL)
		{
			nCode = _MOUSE_INSTALL_FAIL;
		}
		else
		{
			nCode = 0;
		}

		return nCode;
	}

	return _MOUSE_INSTALL;
}

//-------------------------------------------------------
// Remove Hook
//------------------------------------------------------------------
BOOL RemoveKeyHook ()
{
	BOOL	bRet = FALSE;

	bRet = UnhookWindowsHookEx( g_KeyHook ) ;
	if (bRet)
	{
		g_KeyHook = NULL;
	}

	return bRet;
}

BOOL RemoveMouseHook ()
{
	BOOL	bRet = FALSE;

	bRet = UnhookWindowsHookEx( g_MouseHook ) ;
	if (bRet)
	{
		g_MouseHook = NULL;
	}

	return bRet;
}

//int WINAPI SetLockHook (HWND hwnd, int nX1, int nY1, int nX2, int nY2)
int WINAPI SetLockHook (HWND hwnd)
{
	int nKeyCode=0, nMouseCode=0;

	g_HwndServer = hwnd;
#if 0
	g_Start.x = nX1;
	g_Start.y = nY1;
	g_End.x = nX2;
	g_End.y = nY2;
#endif
	nKeyCode = SetKeyHook();
	nMouseCode = SetMouseHook();

	if ( (nKeyCode != 0) || (nMouseCode != 0) )
		return (nKeyCode + nMouseCode);

	return 0;
}

BOOL WINAPI RemoveLockHook ()
{
	if ( !RemoveKeyHook() || !RemoveMouseHook() )
		return FALSE;

	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif
