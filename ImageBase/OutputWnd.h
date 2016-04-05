// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

#pragma once
//#include "MyTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// COutputList ����



extern GImage * g_activeimg;
class COutputList : public CListBox
{
typedef struct _IMGITEM{
	CImgDC	imgdc;
	GImage * pimg;
	bool    show_flag;
}IMGITEM;
// ����
public:
	COutputList();
// ʵ��
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
// ����
public:
	COutputWnd();
	UINT AFX_WM_CHANGE_ACTIVE_TAB;

// ����
protected:
	COutputList m_wndPreview;

protected:

// ʵ��
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

