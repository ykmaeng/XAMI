#include "SetupDlgImpl.h"

SetupDlgImpl::SetupDlgImpl( wxWindow* parent )
:
SetupDlg( parent )
{

}

wxString SetupDlgImpl::GetExten()
{
    return m_textExten->GetLineText(0);
}

wxString SetupDlgImpl::GetRecFileForm()
{
    return m_textRecFile->GetLineText(0);
}

void SetupDlgImpl::SetExten(const wxString& str)
{
    m_textExten->Clear();
    m_textExten->AppendText(str);
}

void SetupDlgImpl::SetRecForm(const wxString& str)
{
    m_textRecFile->Clear();
    m_textRecFile->AppendText(str);
}
