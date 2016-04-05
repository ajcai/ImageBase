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

	// �����������:
	const DWORD dwStyle =  WS_CHILD | WS_VISIBLE  ;//LBS_NOINTEGRALHEIGHT ,,,,,,,,,,,, || WS_HSCROLL | WS_VSCROLL ;
	m_wndPreview.Create(dwStyle, rectDummy, this, 2);
	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	// ѡ��ؼ�Ӧ��������������:
	m_wndPreview.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);	
}

//����
COutputList::COutputList()
{
}
//����
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CListBox::OnPaint()
	RECT rect;
	GetClientRect(&rect);
	//CreateSolidBrush(RGB(255, 0, 0));

	//ȥ��,����ͼ���ɺڰ׵�
	CBrush brush(RGB(213,228,242)); //������ˢ
	dc.FillRect(&rect,&brush);	
	dc.SetBkMode(TRANSPARENT);
	CString msg;
	SetStretchBltMode((HDC)dc.m_hDC,COLORONCOLOR);
		
	for(int i=0;i<m_imglist.size();i++)
	{
		IMGITEM * item=m_imglist[i];
		rect.left=2+105*i;
		rect.right=rect.left+100;
		StretchBlt((HDC)dc.m_hDC, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, (HDC)item->imgdc.GetDC(), 0, 0, item->imgdc.GetWidth(), item->imgdc.GetHeight(), SRCCOPY); //��ʾ����ͼ
	}

	for(int i=0;i<m_imglist.size();i++)
	{//��ѡ�п�
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1)
	{
		//���list
		for(int i=0;i<m_imglist.size();i++){
			delete m_imglist[i];
		}
		m_imglist.erase(m_imglist.begin(), m_imglist.end());
		//����list
		this->UpdateList();
		this->Invalidate();
	}

}

int COutputList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	//sthis->SetScrollInfo
	// TODO:  �ڴ������ר�õĴ�������
	this->ModifyStyle(0,LBS_NOSEL);
	SetTimer(1,1000,NULL);
	return 0;
}


void COutputList::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	int sel_id=point.x/105;
	CImageBaseView* view=(CImageBaseView*) ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveFrame()->GetActiveView();  //��û��ͼ
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
	this->Invalidate();//�����ػ�
}


void COutputList::UpdateList(){
	RECT rect;
	rect.left=0;
	rect.top=0;
	rect.bottom=100;
	rect.right=100;		

	CImageBaseView* view=(CImageBaseView*) ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveFrame()->GetActiveView();  //��û��ͼ
	if(!view){return;}//view �ǿ�
	CImageBaseDoc* doc = view->GetDocument();//��û�ĵ�
	
	for(int i=0;i<doc->mVecGimg.size();i++){
		IMGITEM  * item=new IMGITEM;
		item->pimg=doc->mVecGimg[i];
		item->pimg->GetThumbImage(item->imgdc, rect);
		this->m_imglist.push_back(item);
		item->show_flag=view->mVecGwnd[i]->IsShow();
	}
}


void COutputList::OnSetFocus(CWnd* pOldWnd)//��ý���
{
	this->Invalidate();
}


void COutputList::OnKillFocus(CWnd* pNewWnd)//ʧȥ����
{
	this->Invalidate();
}
