
#define		_KEY_INSTALL		(1)		// Ű���� ��ŷ�� ��ġ �Ǿ� ����
#define		_KEY_INSTALL_FAIL	(2)
#define		_MOUSE_INSTALL		(3)		// ���콺 ��ŷ�� ��ġ �Ǿ� ����
#define		_MOUSE_INSTALL_FAIL	(4)

#define		WM_HOOK_KEYBOARD		(WM_USER+0x098)
#define		WM_HOOK_MOUSE			(WM_USER+0x099)

typedef struct _KEYINFO
{
	unsigned repeatCnt:16; // �ݺ� Ƚ��
	unsigned scanCode:8; // ��ĵ �ڵ�
	unsigned extended:1; // Ȯ�� Ű
	unsigned reserved:4; // �����
	unsigned alt:1; // Alt
	unsigned prevPressed:1; // ���� Ű ����
	unsigned notPressed:1; // ���� Ű ����
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
