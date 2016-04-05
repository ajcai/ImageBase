// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ImageBaseView.h : CImageBaseView ��Ľӿ�
//

#pragma once


class CImageBaseView : public CView
{
protected: // �������л�����
	CImageBaseView();
	DECLARE_DYNCREATE(CImageBaseView)

// ����
public:
	CImageBaseDoc* GetDocument() const;
	vector<GWindow*> mVecGwnd;
private:
	bool mSyncFlag;//ͬ�������־
// ����
public:
	void OpenImgFile(CString);//��gimage��ͼƬ��gwindow��ʾ
protected:
	void _Layout();
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImageBaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnRBtnSuperres();
	afx_msg void OnRBtnOpenAnother();
	afx_msg void OnUpdateRCheckSync(CCmdUI *pCmdUI);
	afx_msg void OnRCheckSync();
	afx_msg void OnTestShowProcess();
	afx_msg void OnTestHideProcess();
};

#ifndef _DEBUG  // ImageBaseView.cpp �еĵ��԰汾
inline CImageBaseDoc* CImageBaseView::GetDocument() const
   { return reinterpret_cast<CImageBaseDoc*>(m_pDocument); }
#endif

