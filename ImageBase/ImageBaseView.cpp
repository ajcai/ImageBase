// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// ImageBaseView.cpp : CImageBaseView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CImageBaseView 构造/析构

CImageBaseView::CImageBaseView()
{
	// TODO: 在此处添加构造代码

}

CImageBaseView::~CImageBaseView()
{
}

BOOL CImageBaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

#pragma region CImageBaseView 绘制
//  绘制
void CImageBaseView::_Layout(){
	int width=0;
	if(this->mVecGwnd.size()>0){
		RECT rect;
		this->GetClientRect(&rect);		

		int img_show_size=0;	//要显示的图片的数量
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
		int width=(rect.right/img_show_size)-1;							//每个Gimage 的宽度
		for(int i=0;i<img_show_index.size();i++){
			GWindow * pwin=this->mVecGwnd[img_show_index[i]];
			pwin->MoveWindow(width*i,0,width*(i+1)-1,rect.bottom);	//显示图像
		}
	}
}
void CImageBaseView::OnDraw(CDC* /*pDC*/)
{
	CImageBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	this->_Layout();
}
#pragma endregion 

// CImageBaseView 打印


void CImageBaseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageBaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageBaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageBaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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
// CImageBaseView 诊断

#ifdef _DEBUG
void CImageBaseView::AssertValid() const
{
	CView::AssertValid();
}

void CImageBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageBaseDoc* CImageBaseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageBaseDoc)));
	return (CImageBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageBaseView 消息处理程序


void CImageBaseView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	for(int i=0;i<this->GetDocument()->mVecGimg.size();i++){
		GWindow* gwnd=this->GetDocument()->mVecGimg[i]->CreateGWindow((unsigned long)this->GetSafeHwnd());
		this->mVecGwnd.push_back(gwnd);
	}
	this->Invalidate();
}


void CImageBaseView::OnRBtnSuperres()
{
	// TODO: 在此添加命令处理程序代码
	CPublicFunction::SR_JOR();
}


void CImageBaseView::OnRBtnOpenAnother()
{
	// 打开另一幅图像
	CString          another_file;
	CFileDialog      dlg_open_another(TRUE);
	dlg_open_another.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST  ;
	dlg_open_another.m_ofn.lpstrFilter = "所有支持图像的格式\0*.tif;*.tiff;*.bmp;*.jpg;*.png;*.gif;*.raw\0所有文件\0*.*\0\0";
	if(dlg_open_another.DoModal() == IDOK)
	{		
		another_file = dlg_open_another.GetPathName();
	}
	this->OpenImgFile(another_file);
}

#pragma region 同步浏览
void CImageBaseView::OnUpdateRCheckSync(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	
	pCmdUI->SetCheck(this->mSyncFlag);
	if(this->mSyncFlag && this->mVecGwnd.size()>1)//同步浏览
	{
		GWindow::SyncGWindow(this->mVecGwnd);
	}
}
void CImageBaseView::OnRCheckSync()
{
	// TODO: 在此添加命令处理程序代码
	this->mSyncFlag=!(this->mSyncFlag);
}
#pragma endregion 

void CImageBaseView::OnTestShowProcess()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* mainFrame=(CMainFrame*)theApp.GetMainWnd();
	mainFrame->ChangeProcessBar(true);
}


void CImageBaseView::OnTestHideProcess()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* mainFrame=(CMainFrame*)theApp.GetMainWnd();
	mainFrame->ChangeProcessBar(false);
}
