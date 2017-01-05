/***************************************************************
 * Name:      MyFirstWxApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Xeny Maeng (wifnavor@gmail.com)
 * Created:   2009-02-19
 * Copyright: Xeny Maeng (www.fineapplications.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MyFirstWxApp.h"
#include "MyFirstWxMain.h"

IMPLEMENT_APP(MyFirstWxApp);

bool MyFirstWxApp::OnInit()
{
    MyFirstWxFrame* frame = new MyFirstWxFrame(0L);
    frame->SetIcon(wxICON(ICO_XAMI)); // To Set App Icon
    frame->Show();

    return true;
}
