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

// ImageBaseView.cpp : CImageBaseView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ImageBase.h"
#endif

#include "MainFrm.h"
#include "ImageBaseDoc.h"
#include "ImageBaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "PublicFunction.h"

// CImageBaseView

IMPLEMENT_DYNCREATE(CImageBaseView, CView)

BEGIN_MESSAGE_MAP(CImageBaseView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageBaseView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_R_BTN_SUPERRES, &CImageBaseView::OnRBtnSuperres)
	ON_COMMAND(ID_R_BTN_OPEN_ANOTHER, &CImageBaseView::OnRBtnOpenAnother)
	ON_UPDATE_COMMAND_UI(ID_R_CHECK_SYNC, &CImageBaseView::OnUpdateRCheckSync)
	ON_COMMAND(ID_R_CHECK_SYNC, &CImageBaseView::OnRCheckSync)
	ON_COMMAND(ID_TEST_SHOW_PROCESS, &CImageBaseView::OnTestShowProcess)
	ON_COMMAND(ID_TEST_HIDE_PROCESS, &CImageBaseView::OnTestHideProcess)
END_MESSAGE_MAP()

// CImageBaseView ����/����

CImageBaseView::CImageBaseView()
{
	// TODO: �ڴ˴���ӹ������

}

CImageBaseView::~CImageBaseView()
{
}

BOOL CImageBaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

#pragma region CImageBaseView ����
//  ����
void CImageBaseView::_Layout(){
	int width=0;
	if(this->mVecGwnd.size()>0){
		RECT rect;
		this->GetClientRect(&rect);		

		int img_show_size=0;	//Ҫ��ʾ��ͼƬ������
		vector<int> img_show_index;
		for(int i=0;i<this->mVecGwnd.size();i++){
			if(this->mVecGwnd[i]->IsShow()){
				img_show_size++;
				img_show_index.push_back(i);
			}
		}

		if(img_show_size == 0){
			return;
		}
		int width=(rect.right/img_show_size)-1;							//ÿ��Gimage �Ŀ��
		for(int i=0;i<img_show_index.size();i++){
			GWindow * pwin=this->mVecGwnd[img_show_index[i]];
			pwin->MoveWindow(width*i,0,width*(i+1)-1,rect.bottom);	//��ʾͼ��
		}
	}
}
void CImageBaseView::OnDraw(CDC* /*pDC*/)
{
	CImageBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	this->_Layout();
}
#pragma endregion 

// CImageBaseView ��ӡ


void CImageBaseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageBaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImageBaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImageBaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CImageBaseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageBaseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CImageBaseView::OpenImgFile(CString img_file)
{
	if (!img_file.IsEmpty())
	{
		GImage*  Gimg_another = new GImage();
		Gimg_another->EnablePyramid(false);

		if(Gimg_another->Open(img_file.GetBuffer(MAX_PATH)))
		{
			GWindow*  Gwnd_another;
			Gimg_another->EnablePyramid(false);
			Gwnd_another = Gimg_another->CreateGWindow((unsigned long)this->GetSafeHwnd());
			Gwnd_another->ShowWindow(true);
			this->GetDocument()->mVecGimg.push_back(Gimg_another);
			this->mVecGwnd.push_back(Gwnd_another);
		}//end if
	}
	this->Invalidate();
	this->UpdateWindow();
}
// CImageBaseView ���

#ifdef _DEBUG
void CImageBaseView::AssertValid() const
{
	CView::AssertValid();
}

void CImageBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageBaseDoc* CImageBaseView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageBaseDoc)));
	return (CImageBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageBaseView ��Ϣ�������


void CImageBaseView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	for(int i=0;i<this->GetDocument()->mVecGimg.size();i++){
		GWindow* gwnd=this->GetDocument()->mVecGimg[i]->CreateGWindow((unsigned long)this->GetSafeHwnd());
		this->mVecGwnd.push_back(gwnd);
	}
	this->Invalidate();
}


void CImageBaseView::OnRBtnSuperres()
{
	// TODO: �ڴ���������������
	CPublicFunction::SR_JOR();
}


void CImageBaseView::OnRBtnOpenAnother()
{
	// ����һ��ͼ��
	CString          another_file;
	CFileDialog      dlg_open_another(TRUE);
	dlg_open_another.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST  ;
	dlg_open_another.m_ofn.lpstrFilter = "����֧��ͼ��ĸ�ʽ\0*.tif;*.tiff;*.bmp;*.jpg;*.png;*.gif;*.raw\0�����ļ�\0*.*\0\0";
	if(dlg_open_another.DoModal() == IDOK)
	{		
		another_file = dlg_open_another.GetPathName();
	}
	this->OpenImgFile(another_file);
}

#pragma region ͬ�����
void CImageBaseView::OnUpdateRCheckSync(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	
	pCmdUI->SetCheck(this->mSyncFlag);
	if(this->mSyncFlag && this->mVecGwnd.size()>1)//ͬ�����
	{
		GWindow::SyncGWindow(this->mVecGwnd);
	}
}
void CImageBaseView::OnRCheckSync()
{
	// TODO: �ڴ���������������
	this->mSyncFlag=!(this->mSyncFlag);
}
#pragma endregion 

void CImageBaseView::OnTestShowProcess()
{
	// TODO: �ڴ���������������
	CMainFrame* mainFrame=(CMainFrame*)theApp.GetMainWnd();
	mainFrame->ChangeProcessBar(true);
}


void CImageBaseView::OnTestHideProcess()
{
	// TODO: �ڴ���������������
	CMainFrame* mainFrame=(CMainFrame*)theApp.GetMainWnd();
	mainFrame->ChangeProcessBar(false);
}
