
// ScreenLockAgentView.h : CScreenLockAgentView Ŭ������ �������̽�
//

#pragma once


class CScreenLockAgentView : public CListView
{
protected: // serialization������ ��������ϴ�.
	CScreenLockAgentView();
	DECLARE_DYNCREATE(CScreenLockAgentView)

// Ư���Դϴ�.
public:
	CScreenLockAgentDoc* GetDocument() const;
	CListCtrl*		GetViewListCtrl() { return &GetListCtrl(); }
	void			AddLogToList (LPCTSTR lpszDate, LPCTSTR lpszLog);

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CScreenLockAgentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ScreenLockAgentView.cpp�� ����� ����
inline CScreenLockAgentDoc* CScreenLockAgentView::GetDocument() const
   { return reinterpret_cast<CScreenLockAgentDoc*>(m_pDocument); }
#endif

