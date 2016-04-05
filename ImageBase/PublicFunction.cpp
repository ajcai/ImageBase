#include "StdAfx.h"
#include "PublicFunction.h"
#include "MainFrm.h"

CPublicFunction::CPublicFunction(void)
{
}


CPublicFunction::~CPublicFunction(void)
{
}


void CPublicFunction::SR_JOR(void){
	CMainFrame* mainFrame=(CMainFrame*)(AfxGetApp()->GetMainWnd());
	mainFrame->ChangeProcessBar(true);
	if(!SRJORInitialize()){
		return;
	}
	int upscale=3;
	CString imgfile="E:\\license.jpg";
	mwArray mw_path(imgfile);
	mwArray mw_upscale(1,1,mxDOUBLE_CLASS);
	mw_upscale.SetData(&upscale,1);
	mwArray mw_outfile("E:\\t9.bmp");
	SuperResolutionJOR(mw_path,mw_upscale,mw_outfile);
	mainFrame->ChangeProcessBar(false);
}