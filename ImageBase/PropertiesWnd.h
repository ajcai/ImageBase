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
// ����
public:
	CPropertiesWnd();

	void AdjustLayout();

// ����
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

// ʵ��
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
	void DrawMyHist(void);//����ֱ��ͼ,�����ø�������
	void AddNewPropertyGroup(CString file_name,BOOL xxs,double value_xxs,
		BOOL snr,double value_snr,
		BOOL mag,double value_mag,
		BOOL gray,double value_gray,
		BOOL iac,double value_iac,
		BOOL sar,double value_sar,
		BOOL eme,double value_eme,
		BOOL sjbzd,double value_sjbzd);// �����������
	

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

