// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

#pragma once
//#include "MyTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口



extern GImage * g_activeimg;
class COutputList : public CListBox
{
typedef struct _IMGITEM{
	CImgDC	imgdc;
	GImage * pimg;
	bool    show_flag;
}IMGITEM;
// 构造
public:
	COutputList();
// 实现
public:
	virtual ~COutputList();
	void UpdateList();

protected:
	vector<IMGITEM *> m_imglist;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

class COutputWnd : public CDockablePane
{
// 构造
public:
	COutputWnd();
	UINT AFX_WM_CHANGE_ACTIVE_TAB;

// 特性
protected:
	COutputList m_wndPreview;

protected:

// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

