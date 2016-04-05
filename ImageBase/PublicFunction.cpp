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
	if(!SRJORInitialize()){
		return;
	}
	int upscale=3;
	CString imgfile=".\\testdata\\license.jpg";
	mwArray mw_path(imgfile);
	mwArray mw_upscale(1,1,mxDOUBLE_CLASS);
	mw_upscale.SetData(&upscale,1);
	mwArray mw_outfile(".\\testdata\\result\\t9.bmp");
	SuperResolutionJOR(mw_path,mw_upscale,mw_outfile);
}