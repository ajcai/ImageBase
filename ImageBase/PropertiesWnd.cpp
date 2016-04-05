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

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar
extern GImage*	g_activeimg;
extern GWindow *	g_activegwindow;


CPropertiesWnd::CPropertiesWnd()
{

}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	//m_wndObjectCombo.GetWindowRect(&rectCombo);
	rectCombo.SetRect(0,0,0,200);
	int cyCmb = rectCombo.Size().cy;
	//int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

//	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	//m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	//m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	//m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + 200, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + 200 + 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);//+ cyTlb
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	

	AdjustLayout();
	
	
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::InitPropList()
{
	
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("图像属性"));//图像属性

	
	m_filename = new CMFCPropertyGridProperty(_T("文件名"), (_variant_t) _T(""), _T("文件名"));
	m_filename->AllowEdit(FALSE);
	pGroup1->AddSubItem(m_filename); 
	
	CMFCPropertyGridProperty* pGroupSize = new CMFCPropertyGridProperty(_T("图像大小"), 0, TRUE);
	pProp_w = new CMFCPropertyGridProperty(_T("高度"), _T(""));
	pProp_w ->AllowEdit(FALSE);
	pGroupSize->AddSubItem(pProp_w);

	pProp_h = new CMFCPropertyGridProperty( _T("宽度"), _T(""));
	pProp_h ->AllowEdit(FALSE);
	pGroupSize->AddSubItem(pProp_h);
	pGroupSize->AllowEdit(FALSE);
	pGroup1->AddSubItem(pGroupSize);


	m_XXS = new CMFCPropertyGridProperty( _T("信息熵"), _T(""));
	m_XXS ->AllowEdit(FALSE);
	m_XXS->Show(FALSE,TRUE);

	m_SNR = new CMFCPropertyGridProperty( _T("信噪比"), _T(""));
	m_SNR ->AllowEdit(FALSE);
	m_SNR->Show(FALSE,TRUE);

	m_MAG = new CMFCPropertyGridProperty( _T("平均梯度"), _T(""));
	m_MAG ->AllowEdit(FALSE);
	m_MAG->Show(FALSE,TRUE);

	m_GRAY = new CMFCPropertyGridProperty( _T("平均灰度"), _T(""));
	m_GRAY ->AllowEdit(FALSE);
	m_GRAY->Show(FALSE,TRUE);

	m_IAC = new CMFCPropertyGridProperty( _T("平均对比度"), _T(""));
	m_IAC ->AllowEdit(FALSE);
	m_IAC->Show(FALSE,TRUE);

	m_SAR = new CMFCPropertyGridProperty( _T("灰度方差"), _T(""));
	m_SAR ->AllowEdit(FALSE);
	m_SAR->Show(FALSE,TRUE);

	m_EME = new CMFCPropertyGridProperty( _T("图像增强测量"), _T(""));
	m_EME ->AllowEdit(FALSE);
	m_EME->Show(FALSE,TRUE);

	m_TMQI = new CMFCPropertyGridProperty( _T("色阶保真度"), _T(""));
	m_TMQI ->AllowEdit(FALSE);
	m_TMQI->Show(FALSE,TRUE);

	pGroup1->AddSubItem(m_XXS);
	pGroup1->AddSubItem(m_SNR);
	pGroup1->AddSubItem(m_MAG);
	pGroup1->AddSubItem(m_GRAY);
	pGroup1->AddSubItem(m_IAC);
	pGroup1->AddSubItem(m_SAR);
	pGroup1->AddSubItem(m_EME);
	pGroup1->AddSubItem(m_TMQI);

	m_wndPropList.AddProperty(pGroup1);

	
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
//	m_wndObjectCombo.SetFont(&m_fntPropList);
}


void CPropertiesWnd::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 10)
	{
		DrawMyHist();
	}
}


void CPropertiesWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDockablePane::OnPaint()
	//memset(m_imgStat.GetImage(),128,m_imgStat.GetHeight()*m_imgStat.GetWidthStep());

	RECT rect;
	GetClientRect(&rect);
	
	rect.bottom=200;
	CBrush brush(RGB(213,228,242));
	dc.FillRect(&rect,&brush);	
	 
	if(g_activegwindow&&m_imgStat.GetWidth()>0){
		rect.left+=2;
		rect.right+=2;
		rect.bottom-=2;
		rect.right-=2;
		dc.Rectangle(&rect);
		dc.SetStretchBltMode(COLORONCOLOR);	

		StretchBlt((HDC)dc.m_hDC, rect.left+2, rect.top+2, rect.right-rect.left-4, rect.bottom-rect.top-4, (HDC)m_imgStat.GetDC(), 0, 0, m_imgStat.GetWidth(), m_imgStat.GetHeight(), SRCCOPY);
	}

}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   绘制直方图,并设置各个属性   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void CPropertiesWnd::DrawMyHist(void)
{
	static GImage*  lastimg=NULL;
	
	if(g_activeimg!=lastimg)
	{
		lastimg=g_activeimg;
		if(g_activeimg)
		{	
		
			if(g_activegwindow)
			{
				CString current_name = g_activeimg->GetFileName().c_str();
				m_imgStat.Init(256,200);
				g_activegwindow->DrawHist(m_imgStat,213,228,242);
				
				this->m_filename->SetValue(PathFindFileName(current_name));


				CString w,h;
				w.Format("%d",g_activeimg->GetWidth());
				h.Format("%d",g_activeimg->GetHeight());
				this->pProp_w->SetValue(w);
				this->pProp_h->SetValue(h);

				this->Invalidate();
			}
			
		}
	}
}


// 添加新属性组
void CPropertiesWnd::AddNewPropertyGroup(CString file_name,
	BOOL xxs,double value_xxs,
	BOOL snr,double value_snr,
	BOOL mag,double value_mag,
	BOOL gray,double value_gray,
	BOOL iac,double value_iac,
	BOOL fc,double value_sar,
	BOOL eme,double value_eme,
	BOOL sjbzd,double value_sjbzd)
{
	if (file_name.IsEmpty())
	{
		this->MessageBox("文件名为空，请您重新选择");
	}
	else
	{
		CString img_name = PathFindFileName(file_name);
		CMFCPropertyGridProperty* group_new = new CMFCPropertyGridProperty(_T(img_name));
		CString value_tmp;
		if (xxs)
		{
			CMFCPropertyGridProperty* new_XXS	= new CMFCPropertyGridProperty(_T("信息熵"), _T(""));
			new_XXS	->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_xxs);
			new_XXS->SetValue(value_tmp);
			group_new->AddSubItem(new_XXS);
			
		}
		if (snr)
		{
			CMFCPropertyGridProperty* new_SNR	= new CMFCPropertyGridProperty(_T("信噪比"), _T(""));
			new_SNR	 ->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_snr);
			new_SNR->SetValue(value_tmp);
			group_new->AddSubItem(new_SNR);
			
		}
		if (mag)
		{
			CMFCPropertyGridProperty* new_MAG	= new CMFCPropertyGridProperty(_T("平均梯度"), _T(""));
			new_MAG	->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_mag);
			new_MAG->SetValue(value_tmp);
			group_new->AddSubItem(new_MAG);
			
		}
		if (gray)
		{
			CMFCPropertyGridProperty* new_GRAY	= new CMFCPropertyGridProperty(_T("平均亮度"), _T(""));
			new_GRAY->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_gray);
			new_GRAY->SetValue(value_tmp);
			group_new->AddSubItem(new_GRAY);
		}
		if (iac)
		{
			CMFCPropertyGridProperty* new_IAC	= new CMFCPropertyGridProperty(_T("平均对比度"), _T(""));
			new_IAC	->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_iac);
			new_IAC->SetValue(value_tmp);
			group_new->AddSubItem(new_IAC);
		}
		if (fc)
		{
			CMFCPropertyGridProperty* new_SAR	= new CMFCPropertyGridProperty(_T("方差"), _T(""));
			new_SAR	->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_sar);
			new_SAR->SetValue(value_tmp);
			group_new->AddSubItem(new_SAR);
		}
		if (eme)
		{
			CMFCPropertyGridProperty* new_EME	= new CMFCPropertyGridProperty(_T("图像增强测量"), _T(""));
			new_EME	->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_eme);
			new_EME->SetValue(value_tmp);
			group_new->AddSubItem(new_EME);
		}
		if (sjbzd)
		{
			CMFCPropertyGridProperty* new_SJBZD = new CMFCPropertyGridProperty(_T("色阶保真度"), _T(""));
			new_SJBZD ->AllowEdit(FALSE);
			value_tmp.Empty();
			value_tmp.Format("%fl",value_sjbzd);
			new_SJBZD->SetValue(value_tmp);
			group_new->AddSubItem(new_SJBZD);			
		}
		m_wndPropList.AddProperty(group_new);
	}//end else
	
}


void CPropertiesWnd::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	SetTimer(10,500,NULL);
	CDockablePane::PreSubclassWindow();
}
