
// ScreenLockAgentView.cpp : CScreenLockAgentView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ScreenLockAgent.h"
#endif

#include "ScreenLockAgentDoc.h"
#include "ScreenLockAgentView.h"
#include "GlobalFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScreenLockAgentView

IMPLEMENT_DYNCREATE(CScreenLockAgentView, CListView)

BEGIN_MESSAGE_MAP(CScreenLockAgentView, CListView)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CScreenLockAgentView::OnNMRClick)
END_MESSAGE_MAP()

// CScreenLockAgentView 생성/소멸

CScreenLockAgentView::CScreenLockAgentView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CScreenLockAgentView::~CScreenLockAgentView()
{
}

BOOL CScreenLockAgentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style |= LVS_REPORT | WS_BORDER | WS_TABSTOP;

	return CListView::PreCreateWindow(cs);
}

void CScreenLockAgentView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CString strTitle;

	// TODO: GetListCtrl()을 호출하여 해당 list 컨트롤을 직접 액세스함으로써
	//  ListView를 항목으로 채울 수 있습니다.
	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.InsertColumn(0, _T("발생일시"), LVCFMT_LEFT);

	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT;
	col.pszText = _T("로그");
	col.fmt = LVCFMT_LEFT;
	theCtrl.InsertColumn(1, &col);

	theCtrl.SetColumnWidth(0, 150);
	theCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	theCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// Start Log
	AfxGetMainWnd()->GetWindowText (strTitle);
	AddLog (_SHOW, _INFO, TEXT("%s"), strTitle);
}

void CScreenLockAgentView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	CPoint point;
	CMenu	muTemp, *pContextMenu;

	GetCursorPos(&point);

	muTemp.LoadMenu(IDR_MENU_LIST_RCLICK);
	pContextMenu = muTemp.GetSubMenu(0);
	if (pContextMenu != NULL)
	{
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd());
	}

	*pResult = 0;
}



// CScreenLockAgentView 진단

#ifdef _DEBUG
void CScreenLockAgentView::AssertValid() const
{
	CListView::AssertValid();
}

void CScreenLockAgentView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CScreenLockAgentDoc* CScreenLockAgentView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScreenLockAgentDoc)));
	return (CScreenLockAgentDoc*)m_pDocument;
}
#endif //_DEBUG


// CScreenLockAgentView 메시지 처리기
void CScreenLockAgentView::AddLogToList (LPCTSTR lpszDate, LPCTSTR lpszLog)
{
	int			nIdx=0;
	CListCtrl	*List = GetViewListCtrl();
	if(List != NULL)
	{
		if(List->GetItemCount() >= _MAX_LOG_COUNT)
			List->DeleteItem(_MAX_LOG_COUNT);

		List->InsertItem(nIdx, lpszDate);
		List->SetItemText(nIdx, 1, lpszLog);

		List->EnsureVisible(nIdx, FALSE);
	}
}