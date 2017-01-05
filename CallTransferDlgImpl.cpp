#include "CallTransferDlgImpl.h"

CallTransferDlgImpl::CallTransferDlgImpl( wxWindow* parent )
:
CallTransferDlg( parent )
{

}

wxString CallTransferDlgImpl::GetDestNum()
{
    return m_textDestNum->GetLineText(0);
}
