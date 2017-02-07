
// ScreenLockAgentView.h : CScreenLockAgentView 클래스의 인터페이스
//

#pragma once


class CScreenLockAgentView : public CListView
{
protected: // serialization에서만 만들어집니다.
	CScreenLockAgentView();
	DECLARE_DYNCREATE(CScreenLockAgentView)

// 특성입니다.
public:
	CScreenLockAgentDoc* GetDocument() const;
	CListCtrl*		GetViewListCtrl() { return &GetListCtrl(); }
	void			AddLogToList (LPCTSTR lpszDate, LPCTSTR lpszLog);

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CScreenLockAgentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ScreenLockAgentView.cpp의 디버그 버전
inline CScreenLockAgentDoc* CScreenLockAgentView::GetDocument() const
   { return reinterpret_cast<CScreenLockAgentDoc*>(m_pDocument); }
#endif

