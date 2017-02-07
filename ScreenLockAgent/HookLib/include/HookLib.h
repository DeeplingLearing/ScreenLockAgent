
#define		_KEY_INSTALL		(1)		// 키보드 후킹이 설치 되어 있음
#define		_KEY_INSTALL_FAIL	(2)
#define		_MOUSE_INSTALL		(3)		// 마우스 후킹이 설치 되어 있음
#define		_MOUSE_INSTALL_FAIL	(4)

#define		WM_HOOK_KEYBOARD		(WM_USER+0x098)
#define		WM_HOOK_MOUSE			(WM_USER+0x099)

typedef struct _KEYINFO
{
	unsigned repeatCnt:16; // 반복 횟수
	unsigned scanCode:8; // 스캔 코드
	unsigned extended:1; // 확장 키
	unsigned reserved:4; // 예약됨
	unsigned alt:1; // Alt
	unsigned prevPressed:1; // 이전 키 상태
	unsigned notPressed:1; // 현재 키 상태
} KEYINFO, *PKEYINFO;

typedef struct
{
	int		Type ;
	WPARAM	wParam ;
	LPARAM	lParam ;
} HEVENT;

HINSTANCE GetDLLInstance();

int WINAPI SetLockHook (HWND hwnd);
//int WINAPI SetLockHook (HWND hwnd, int nX1, int nY1, int nX2, int nY2);
BOOL WINAPI RemoveLockHook ();
