

namespace AGENT_DEFINE {

enum CUSTOM_TYPE {
	_HIDE=0,
	_SHOW=1,

	_EMPTY_PASSWORD = (WM_USER + 0x100),
	_CHECK_PASSWORD,
	_INVALID_PASSWORD,
	_LOCK_PASSWORD,

	_CUSTOM_TIMER = (WM_USER + 0x200),
	_TIMER_TOPMOST,

	WM_ICON_NOTIFY = (WM_USER + 0x300),

	_MIN_PASSWORD_LEN = 4,
	_MAX_PASSWORD_LEN = 12,
	_MAX_LOG_COUNT = 100
};

typedef struct {
	TCHAR	strPassword[64];
	int		nQuestionPwd;
} CONFIG_INFO_T;

const CString _PROJECT		= TEXT("ScreenLock");
const CString _PROGRAM_NAME	= TEXT("ScreenLockAgent");

const CString _CONFIG			= TEXT("Config");
const CString _PASSWORD			= TEXT("Password");
const CString _QUESTION_PWD		= TEXT("QuestionPwd");
const CString _SHOW_ICON		= TEXT("ShowIcon");
const CString _ALERT_TEXT		= TEXT("AlertText");

const CString _INFO			= TEXT("정보");
const CString _WARNING		= TEXT("경고");
const CString _ERROR		= TEXT("오류");

const CString _CTIME_CURRENT_FORMAT = TEXT("%Y-%m-%d %H:%M:%S");
const CString _FRAUD_PREVENTION_TEXT = TEXT("부정 사용 금지");
}
