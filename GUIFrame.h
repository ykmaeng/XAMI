///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb  6 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFrame__
#define __GUIFrame__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#ifdef __VISUALC__
#include <wx/link_additions.h>
#endif //__VISUALC__
#include <wx/wxFlatNotebook/wxFlatNotebook.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include "xami.h"

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001
#define wxID_TOOL_CREATESESSION 1002
#define wxID_TOOL_DESTROYSESSION 1003
#define wxID_TOOL_SETUP 1004
#define wxID_NOTEBOOK 1005
#define wxID_PANEL_ANALYZER 1006
#define wxID_TREE_ACTIONLIST 1007
#define wxID_PROPGRID_ACTIONVARS 1008
#define wxID_TOOLBAR_ANALYZER 1009
#define wxID_TOOL_DOACTION 1010
#define wxID_TOOL_MAKECALL 1011
#define wxID_TOOL_HANGUP 1012
#define wxID_TOOL_TRANSFER 1013
#define wxID_TOOL_RECSTART 1014
#define wxID_TOOL_RECSTOP 1015
#define wxID_PANEL_XAMI 1016
#define wxID_DLG_CREATESESSION 1017
#define wxID_DLG_MAKECALL 1018
#define wxID_DLG_CALLTRANSFER 1019
#define wxID_STATIC_POPUPMSG 1020

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame, public wxAMI
{
	private:

	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxToolBar* m_toolbarMain;
		wxFlatNotebook* m_flatNotebook1;
		wxPanel* m_panelAnalyzer;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panel7;
		wxSplitterWindow* m_splitter5;
		wxPanel* m_panel10;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textInputLog;
		wxPanel* m_panel11;
		wxStaticText* m_staticText31;
		wxTextCtrl* m_textOutputLog;
		wxPanel* m_panel6;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel2;
		wxStaticText* m_staticText2;
		wxTreeCtrl* m_treeActionList;
		wxPanel* m_panel4;
		wxStaticText* m_staticText21;
		wxPropertyGrid* m_pgActionVars;
		wxToolBar* m_toolbarAnalyzer;
		wxPanel* m_panelXami;
		wxStaticText* m_staticText23;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnIconize( wxIconizeEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_CreateSession( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_DestroySession( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_Setup( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTreeSelChanged_ActionList( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_DoAction( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_MakeCall( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_Hangup( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_Transfer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_RecStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolClicked_RecStop( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Asterisk AMI 분석 툴  -  xAMI 0.1 beta2"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,700 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrame();
		void m_splitter3OnIdle( wxIdleEvent& )
		{
		m_splitter3->SetSashPosition( 287 );
		m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::m_splitter3OnIdle ), NULL, this );
		}

		void m_splitter5OnIdle( wxIdleEvent& )
		{
		m_splitter5->SetSashPosition( 0 );
		m_splitter5->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::m_splitter5OnIdle ), NULL, this );
		}

		void m_splitter1OnIdle( wxIdleEvent& )
		{
		m_splitter1->SetSashPosition( 235 );
		m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::m_splitter1OnIdle ), NULL, this );
		}


};

///////////////////////////////////////////////////////////////////////////////
/// Class CreateSessionDlg
///////////////////////////////////////////////////////////////////////////////
class CreateSessionDlg : public wxDialog
{
	private:

	protected:

		wxStaticText* m_staticText7;
		wxTextCtrl* m_textHostname;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textServicePort;
		wxStaticText* m_staticText71;
		wxTextCtrl* m_textAmiId;
		wxStaticText* m_staticText81;
		wxTextCtrl* m_textAmiSecret;
		wxStaticText* m_staticText9;
		wxTextCtrl* m_textExten;
		wxCheckBox* m_checkMd5;

		wxButton* m_buttonOk;
		wxButton* m_buttonCancel;


	public:

		CreateSessionDlg( wxWindow* parent, wxWindowID id = wxID_DLG_CREATESESSION, const wxString& title = wxT("AMI 세션 정보를 입력하세요^^"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 259,265 ), long style = wxCAPTION );
		~CreateSessionDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class MakeCallDlg
///////////////////////////////////////////////////////////////////////////////
class MakeCallDlg : public wxDialog
{
	private:

	protected:

		wxStaticText* m_staticText81;
		wxTextCtrl* m_textSourceNum;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textDestNum;

		wxButton* m_buttonOk;
		wxButton* m_buttonCancel;


	public:

		MakeCallDlg( wxWindow* parent, wxWindowID id = wxID_DLG_MAKECALL, const wxString& title = wxT("어디로 전화를 걸까요?"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 219,144 ), long style = wxCAPTION );
		~MakeCallDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CallTransferDlg
///////////////////////////////////////////////////////////////////////////////
class CallTransferDlg : public wxDialog
{
	private:

	protected:

		wxStaticText* m_staticText8;
		wxTextCtrl* m_textDestNum;

		wxButton* m_buttonOk;
		wxButton* m_buttonCancel;


	public:

		CallTransferDlg( wxWindow* parent, wxWindowID id = wxID_DLG_CALLTRANSFER, const wxString& title = wxT("호를 어디로 전달할까요?"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 237,111 ), long style = wxCAPTION );
		~CallTransferDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SetupDlg
///////////////////////////////////////////////////////////////////////////////
class SetupDlg : public wxDialog
{
	private:

	protected:

		wxStaticText* m_staticText81;
		wxTextCtrl* m_textExten;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textRecFile;

		wxButton* m_buttonOk;
		wxButton* m_buttonCancel;


	public:

		SetupDlg( wxWindow* parent, wxWindowID id = wxID_DLG_MAKECALL, const wxString& title = wxT("환경을 설정해주세요^^"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 268,145 ), long style = wxCAPTION );
		~SetupDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CallPopupDlg
///////////////////////////////////////////////////////////////////////////////
class CallPopupDlg : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticMsg;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }


	public:

		CallPopupDlg( wxWindow* parent, wxWindowID id = wxID_DLG_MAKECALL, const wxString& title = wxT("Message"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 268,113 ), long style = wxCAPTION|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxSIMPLE_BORDER );
		~CallPopupDlg();

};

#endif //__GUIFrame__
