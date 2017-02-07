
// ScreenLockAgentView.cpp : CScreenLockAgentView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CScreenLockAgentView ����/�Ҹ�

CScreenLockAgentView::CScreenLockAgentView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CScreenLockAgentView::~CScreenLockAgentView()
{
}

BOOL CScreenLockAgentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.style |= LVS_REPORT | WS_BORDER | WS_TABSTOP;

	return CListView::PreCreateWindow(cs);
}

void CScreenLockAgentView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CString strTitle;

	// TODO: GetListCtrl()�� ȣ���Ͽ� �ش� list ��Ʈ���� ���� �׼��������ν�
	//  ListView�� �׸����� ä�� �� �ֽ��ϴ�.
	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.InsertColumn(0, _T("�߻��Ͻ�"), LVCFMT_LEFT);

	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT;
	col.pszText = _T("�α�");
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



// CScreenLockAgentView ����

#ifdef _DEBUG
void CScreenLockAgentView::AssertValid() const
{
	CListView::AssertValid();
}

void CScreenLockAgentView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CScreenLockAgentDoc* CScreenLockAgentView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScreenLockAgentDoc)));
	return (CScreenLockAgentDoc*)m_pDocument;
}
#endif //_DEBUG


// CScreenLockAgentView �޽��� ó����
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