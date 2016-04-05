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
//#include "ImageStudioMDI1View.h"

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// 构造
public:
	CPropertiesWnd();

	void AdjustLayout();

// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	//CComboBox m_wndObjectCombo;
	//CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

// 实现
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	//CMFCPropertyGridProperty  * m_filename;
	CMFCPropertyGridProperty*  m_pSize;

	//CMFCPropertyGridProperty*	m_gridxy;    // Pointer to the PropertyList window
	//CMFCPropertyGridProperty*	m_gridlatlng;     // Parent property (NULL for top-level properties)
	//CMFCPropertyGridProperty*   m_gridband;//
	//CMFCPropertyGridProperty*  m_pWidth;
	//CMFCPropertyGridProperty*  m_pHeight;

	CMFCPropertyGridProperty* m_filename;
	CMFCPropertyGridProperty* pProp_w;
	CMFCPropertyGridProperty* pProp_h;
	

	

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	CImgDC	m_imgStat;
	void DrawMyHist(void);//绘制直方图,并设置各个属性
	void AddNewPropertyGroup(CString file_name,BOOL xxs,double value_xxs,
		BOOL snr,double value_snr,
		BOOL mag,double value_mag,
		BOOL gray,double value_gray,
		BOOL iac,double value_iac,
		BOOL sar,double value_sar,
		BOOL eme,double value_eme,
		BOOL sjbzd,double value_sjbzd);// 添加新属性组
	

	CMFCPropertyGridProperty*	m_XXS	;
	CMFCPropertyGridProperty*	m_SNR	;
	CMFCPropertyGridProperty*	m_MAG	;
	CMFCPropertyGridProperty*	m_GRAY	;
	CMFCPropertyGridProperty*	m_IAC	;
	CMFCPropertyGridProperty*	m_SAR	;
	CMFCPropertyGridProperty*	m_EME	;
	CMFCPropertyGridProperty*	m_TMQI ;

	virtual void PreSubclassWindow();
};

