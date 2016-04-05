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

#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
	AFX_WM_CHANGE_ACTIVE_TAB=0;

}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建输出窗格:
	const DWORD dwStyle =  WS_CHILD | WS_VISIBLE  ;//LBS_NOINTEGRALHEIGHT ,,,,,,,,,,,, || WS_HSCROLL | WS_VSCROLL ;
	m_wndPreview.Create(dwStyle, rectDummy, this, 2);
	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	// 选项卡控件应覆盖整个工作区:
	m_wndPreview.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);	
}

//构造
COutputList::COutputList()
{
}
//析构
COutputList::~COutputList()
{
}
BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


void COutputList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CListBox::OnPaint()
	RECT rect;
	GetClientRect(&rect);
	//CreateSolidBrush(RGB(255, 0, 0));

	//去掉,缩略图会变成黑白的
	CBrush brush(RGB(213,228,242)); //创建画刷
	dc.FillRect(&rect,&brush);	
	dc.SetBkMode(TRANSPARENT);
	CString msg;
	SetStretchBltMode((HDC)dc.m_hDC,COLORONCOLOR);
		
	for(int i=0;i<m_imglist.size();i++)
	{
		IMGITEM * item=m_imglist[i];
		rect.left=2+105*i;
		rect.right=rect.left+100;
		StretchBlt((HDC)dc.m_hDC, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, (HDC)item->imgdc.GetDC(), 0, 0, item->imgdc.GetWidth(), item->imgdc.GetHeight(), SRCCOPY); //显示缩略图
	}

	for(int i=0;i<m_imglist.size();i++)
	{//画选中框
		if(!m_imglist[i]->show_flag){
			continue;
		}
		rect.left=2+105*i;
		rect.right=rect.left+100;
		CPen pen;
		pen.CreatePen(PS_SOLID,2,RGB(0,255,0));
		CPen *poldpen=dc.SelectObject(&pen ); 
		dc.SelectStockObject(NULL_BRUSH);   
		dc.Rectangle(&rect);			
		dc.SelectObject(poldpen);
		pen.DeleteObject();
	}
	
}

void COutputList::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		//清空list
		for(int i=0;i<m_imglist.size();i++){
			delete m_imglist[i];
		}
		m_imglist.erase(m_imglist.begin(), m_imglist.end());
		//更新list
		this->UpdateList();
		this->Invalidate();
	}

}

int COutputList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	//sthis->SetScrollInfo
	// TODO:  在此添加您专用的创建代码
	this->ModifyStyle(0,LBS_NOSEL);
	SetTimer(1,1000,NULL);
	return 0;
}


void COutputList::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	int sel_id=point.x/105;
	CImageBaseView* view=(CImageBaseView*) ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveFrame()->GetActiveView();  //获得活动视图
	if(!view || sel_id>=view->mVecGwnd.size()){
		return;
	}
	m_imglist[sel_id]->show_flag=!m_imglist[sel_id]->show_flag;
	this->Invalidate();

	view->mVecGwnd[sel_id]->ShowWindow(m_imglist[sel_id]->show_flag);
	view->Invalidate();
}


void COutputList::OnSize(UINT nType, int cx, int cy)
{
	//CListBox::OnSize(nType, cx, cy);
	this->Invalidate();//窗口重画
}


void COutputList::UpdateList(){
	RECT rect;
	rect.left=0;
	rect.top=0;
	rect.bottom=100;
	rect.right=100;		

	CImageBaseView* view=(CImageBaseView*) ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveFrame()->GetActiveView();  //获得活动视图
	if(!view){return;}//view 非空
	CImageBaseDoc* doc = view->GetDocument();//获得活动文档
	
	for(int i=0;i<doc->mVecGimg.size();i++){
		IMGITEM  * item=new IMGITEM;
		item->pimg=doc->mVecGimg[i];
		item->pimg->GetThumbImage(item->imgdc, rect);
		this->m_imglist.push_back(item);
		item->show_flag=view->mVecGwnd[i]->IsShow();
	}
}


void COutputList::OnSetFocus(CWnd* pOldWnd)//获得焦点
{
	this->Invalidate();
}


void COutputList::OnKillFocus(CWnd* pNewWnd)//失去焦点
{
	this->Invalidate();
}
