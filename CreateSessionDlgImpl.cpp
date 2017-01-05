#include "CreateSessionDlgImpl.h"

CreateSessionDlgImpl::CreateSessionDlgImpl( wxWindow* parent )
:
CreateSessionDlg( parent )
{

}

///
/// Getter Functions
///
wxString CreateSessionDlgImpl::GetHostname()
{
    return m_textHostname->GetLineText(0);
}

wxString CreateSessionDlgImpl::GetPort()
{
    return m_textServicePort->GetLineText(0);
}

wxString CreateSessionDlgImpl::GetAmiId()
{
    return m_textAmiId->GetLineText(0);
}

wxString CreateSessionDlgImpl::GetAmiPw()
{
    return m_textAmiSecret->GetLineText(0);
}

wxString CreateSessionDlgImpl::GetExten()
{
    return m_textExten->GetLineText(0);
}

///
/// Setter Funtions
///
void CreateSessionDlgImpl::SetHostname(const wxString& str)
{
    m_textHostname->Clear();
    m_textHostname->AppendText(str);
}

void CreateSessionDlgImpl::SetPort(const wxString& str)
{
    m_textServicePort->Clear();
    m_textServicePort->AppendText(str);
}

void CreateSessionDlgImpl::SetAmiId(const wxString& str)
{
    m_textAmiId->Clear();
    m_textAmiId->AppendText(str);
}

void CreateSessionDlgImpl::SetAmiPw(const wxString& str)
{
    m_textAmiSecret->Clear();
    m_textAmiSecret->AppendText(str);
}

void CreateSessionDlgImpl::SetExten(const wxString& str)
{
    m_textExten->Clear();
    m_textExten->AppendText(str);
}

