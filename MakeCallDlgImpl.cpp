#include "MakeCallDlgImpl.h"

MakeCallDlgImpl::MakeCallDlgImpl( wxWindow* parent )
:
MakeCallDlg( parent )
{

}

wxString MakeCallDlgImpl::GetSourceNum()
{
    return m_textSourceNum->GetLineText(0);
}

wxString MakeCallDlgImpl::GetDestNum()
{
    return m_textDestNum->GetLineText(0);
}

void MakeCallDlgImpl::SetSourceNum(const wxString& str)
{
    m_textSourceNum->AppendText(str);
}
