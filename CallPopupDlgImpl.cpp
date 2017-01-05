#include "CallPopupDlgImpl.h"
#include "MyFirstWxMain.h"
//#include <wx/timer.h>

BEGIN_EVENT_TABLE(CallPopupDlgImpl, CallPopupDlg)
    EVT_TIMER(2, CallPopupDlgImpl::OnTimerEvent)
END_EVENT_TABLE()

CallPopupDlgImpl::CallPopupDlgImpl( wxWindow* parent )
:
CallPopupDlg( parent )
{
    m_parentPtr = parent;
    m_timerCnt = 0;
    m_isActiveMsg = false;

    //SetTransparent(0);
    m_timer.SetOwner(this, 2);
    m_timer.Stop();
    m_timer.Start(1000);
}

void CallPopupDlgImpl::OnClose( wxCloseEvent& event )
{
    m_timer.Stop();
    ((MyFirstWxFrame*)m_parentPtr)->m_popupDlgPtr = NULL;

	Destroy();
}

void CallPopupDlgImpl::OnInitDialog( wxInitDialogEvent& event )
{
    //wxMessageBox(_("CallPopupDlgImpl::OnInitDialog() -> Call"));
}

void CallPopupDlgImpl::OnLeftDown( wxMouseEvent& event )
{
    SetTransparent(0);
    m_isActiveMsg = false;
    Show(false);
}

void CallPopupDlgImpl::ShowDialog()
{
    Show(true);
    wxUint8 transLevel = 0;
    while(transLevel < 240) {
        SetTransparent(transLevel+=10);
        Sleep(10);
    }
    SetTransparent(255);
}

void CallPopupDlgImpl::HideDialog()
{
    wxUint8 transLevel = 255;
    while(transLevel > 10) {
        SetTransparent(transLevel-=10);
        Sleep(10);
    }
    SetTransparent(0);
    Show(false);
}

void CallPopupDlgImpl::OnTimerEvent(wxTimerEvent& event)
{
    if(++m_timerCnt < 5 || !m_isActiveMsg) return;

    HideDialog();
    m_isActiveMsg = false;
}

void CallPopupDlgImpl::ShowMessage(const wxString& msg, const wxString& title)
{
    SetTitle(title);
    m_staticMsg->SetLabel(msg);

    ShowDialog();
    m_isActiveMsg = true;
    m_timerCnt = 0;
}
