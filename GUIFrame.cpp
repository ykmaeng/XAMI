///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb  6 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ), wxAMI(parent)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );

	mbar->Append( fileMenu, wxT("&File") );

	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );

	mbar->Append( helpMenu, wxT("&Help") );

	this->SetMenuBar( mbar );

	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_toolbarMain = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_HORZ_TEXT|wxTB_TEXT );
	m_toolbarMain->AddTool( wxID_TOOL_CREATESESSION, wxT("세션연결"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarMain->AddTool( wxID_TOOL_DESTROYSESSION, wxT("세션해제"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarMain->AddSeparator();
	m_toolbarMain->AddTool( wxID_TOOL_SETUP, wxT("환경설정"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarMain->Realize();

	bSizer5->Add( m_toolbarMain, 0, wxEXPAND, 5 );

	m_flatNotebook1 = new wxFlatNotebook(this, wxID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxFNB_DEFAULT_STYLE|wxFNB_NO_X_BUTTON|wxFNB_SMART_TABS|wxFNB_X_ON_TAB);

	m_flatNotebook1->SetCustomizeOptions( wxFNB_CUSTOM_ALL );
	m_flatNotebook1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );

	m_panelAnalyzer = new wxPanel( m_flatNotebook1, wxID_PANEL_ANALYZER, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelAnalyzer->SetToolTip( wxT("AMI 기능을 테스트합니다.") );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_splitter3 = new wxSplitterWindow( m_panelAnalyzer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::m_splitter3OnIdle ), NULL, this );
	m_panel7 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	m_splitter5 = new wxSplitterWindow( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter5->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::m_splitter5OnIdle ), NULL, this );
	m_panel10 = new wxPanel( m_splitter5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	m_staticText3 = new wxStaticText( m_panel10, wxID_ANY, wxT("액션 수행 로그"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText3->Wrap( -1 );
	bSizer16->Add( m_staticText3, 0, wxEXPAND, 5 );

	m_textInputLog = new wxTextCtrl( m_panel10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_textInputLog->SetMaxLength( 3096 );
	m_textInputLog->SetForegroundColour( wxColour( 224, 224, 224 ) );
	m_textInputLog->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	bSizer16->Add( m_textInputLog, 1, wxEXPAND, 5 );

	m_panel10->SetSizer( bSizer16 );
	m_panel10->Layout();
	bSizer16->Fit( m_panel10 );
	m_panel11 = new wxPanel( m_splitter5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	m_staticText31 = new wxStaticText( m_panel11, wxID_ANY, wxT("액션 응답 && 이벤트 수신 로그"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText31->Wrap( -1 );
	bSizer17->Add( m_staticText31, 0, wxEXPAND, 5 );

	m_textOutputLog = new wxTextCtrl( m_panel11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_textOutputLog->SetMaxLength( 10240 );
	m_textOutputLog->SetForegroundColour( wxColour( 224, 224, 224 ) );
	m_textOutputLog->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	bSizer17->Add( m_textOutputLog, 1, wxEXPAND, 5 );

	m_panel11->SetSizer( bSizer17 );
	m_panel11->Layout();
	bSizer17->Fit( m_panel11 );
	m_splitter5->SplitVertically( m_panel10, m_panel11, 0 );
	bSizer13->Add( m_splitter5, 1, wxEXPAND, 5 );

	m_panel7->SetSizer( bSizer13 );
	m_panel7->Layout();
	bSizer13->Fit( m_panel7 );
	m_panel6 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_splitter1 = new wxSplitterWindow( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::m_splitter1OnIdle ), NULL, this );
	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( m_panel2, wxID_ANY, wxT("액션 리스트"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText2->Wrap( -1 );
	bSizer51->Add( m_staticText2, 0, wxEXPAND, 5 );

	m_treeActionList = new wxTreeCtrl( m_panel2, wxID_TREE_ACTIONLIST, wxDefaultPosition, wxSize( -1,-1 ), wxTR_DEFAULT_STYLE );
	m_treeActionList->SetToolTip( wxT("AMI Action 명령 리스트입니다.") );

	bSizer51->Add( m_treeActionList, 1, wxEXPAND, 5 );

	m_panel2->SetSizer( bSizer51 );
	m_panel2->Layout();
	bSizer51->Fit( m_panel2 );
	m_panel4 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	m_staticText21 = new wxStaticText( m_panel4, wxID_ANY, wxT("액션 변수(Action Variables)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText21->Wrap( -1 );
	bSizer8->Add( m_staticText21, 0, wxEXPAND, 5 );

	m_pgActionVars = new wxPropertyGrid(m_panel4, wxID_PROPGRID_ACTIONVARS, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	m_pgActionVars->SetToolTip( wxT("입력후 반드시 '엔터'를 눌러주세요^^") );

	bSizer8->Add( m_pgActionVars, 1, wxEXPAND, 5 );

	m_toolbarAnalyzer = new wxToolBar( m_panel4, wxID_TOOLBAR_ANALYZER, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_HORZ_TEXT|wxTB_TEXT );
	m_toolbarAnalyzer->AddTool( wxID_TOOL_DOACTION, wxT("액션수행"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("액션을 수행합니다.") );
	m_toolbarAnalyzer->AddSeparator();
	m_toolbarAnalyzer->AddTool( wxID_TOOL_MAKECALL, wxT("전화걸기"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarAnalyzer->AddTool( wxID_TOOL_HANGUP, wxT("전화끊기"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarAnalyzer->AddTool( wxID_TOOL_TRANSFER, wxT("호전환"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarAnalyzer->AddTool( wxID_TOOL_RECSTART, wxT("녹음시작"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarAnalyzer->AddTool( wxID_TOOL_RECSTOP, wxT("녹음종료"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString );
	m_toolbarAnalyzer->Realize();

	bSizer8->Add( m_toolbarAnalyzer, 0, wxEXPAND, 5 );

	m_panel4->SetSizer( bSizer8 );
	m_panel4->Layout();
	bSizer8->Fit( m_panel4 );
	m_splitter1->SplitVertically( m_panel2, m_panel4, 235 );
	bSizer12->Add( m_splitter1, 1, wxEXPAND, 5 );

	m_panel6->SetSizer( bSizer12 );
	m_panel6->Layout();
	bSizer12->Fit( m_panel6 );
	m_splitter3->SplitHorizontally( m_panel7, m_panel6, 287 );
	bSizer4->Add( m_splitter3, 1, wxEXPAND, 5 );

	m_panelAnalyzer->SetSizer( bSizer4 );
	m_panelAnalyzer->Layout();
	bSizer4->Fit( m_panelAnalyzer );
	m_flatNotebook1->AddPage( m_panelAnalyzer, wxT("AMI 분석기"), true );
	m_panelXami = new wxPanel( m_flatNotebook1, wxID_PANEL_XAMI, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelXami->SetToolTip( wxT("프로그램 정보를 확인합니다.") );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_staticText23 = new wxStaticText( m_panelXami, wxID_ANY, wxT("버전 : 0.1 beta\n배포일 : 2009년 4월 7일 첫 배포\n\nxAMI를 이용해주셔서 감사합니다.\n이 프로그램은 Asterisk 사용자를 위한 AMI(Asterisk Manager Interface) 테스팅 도구입니다.\n이용하시면서 버그수정이나 개선이 필요한 사항은 아래로 연락 주시기 바랍니다.\n\n*특징\n - Asterisk 1.x 이상 지원합니다. (테스트는 1.4, 1.6에서만 했습니다.^^;)\n - AstManProxy는 Standard 포맷만 지원합니다.\n - 전화걸기/끊기, 콜팝업, 통화녹음 등을 지원합니다.\n - xAMI 엔진은 모든 액션과 이벤트를 처리할 수 있으며, 멀티세션을 지원합니다.\n\n*개발 정보\n - 개발 언어 : C++ (wxWidgets 2.8.9)\n - 개발 도구 : Code::Blocks 8.02, wxFormBuilder 3.1\n - 컴파일러 : GCC\n - 데이터베이스 : wxSQLite3 - 1.9.5\n - 구동환경 : MS Windows, Unix(GTK+, Motif), MacOS의 데스크탑 환경 (현재는 윈도우즈용만 배포)\n\n*라이센스\n - 누구나 자유롭게 사용하고 배포할 수 있습니다.\n\n*제작자 정보\n - 만든이 : 제니\n - 이메일 : winfavor@gmail.com\n - 모바일 : 010-5509-0072"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer9->Add( m_staticText23, 0, wxALL, 5 );

	m_panelXami->SetSizer( bSizer9 );
	m_panelXami->Layout();
	bSizer9->Fit( m_panelXami );
	m_flatNotebook1->AddPage( m_panelXami, wxT("프로그램정보"), false );

	bSizer5->Add( m_flatNotebook1, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer5 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( wxEVT_ICONIZE, wxIconizeEventHandler( GUIFrame::OnIconize ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Connect( wxID_TOOL_CREATESESSION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_CreateSession ) );
	this->Connect( wxID_TOOL_DESTROYSESSION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_DestroySession ) );
	this->Connect( wxID_TOOL_SETUP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_Setup ) );
	m_treeActionList->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIFrame::OnTreeSelChanged_ActionList ), NULL, this );
	this->Connect( wxID_TOOL_DOACTION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_DoAction ) );
	this->Connect( wxID_TOOL_MAKECALL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_MakeCall ) );
	this->Connect( wxID_TOOL_HANGUP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_Hangup ) );
	this->Connect( wxID_TOOL_TRANSFER, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_Transfer ) );
	this->Connect( wxID_TOOL_RECSTART, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_RecStart ) );
	this->Connect( wxID_TOOL_RECSTOP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_RecStop ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxEVT_ICONIZE, wxIconizeEventHandler( GUIFrame::OnIconize ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Disconnect( wxID_TOOL_CREATESESSION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_CreateSession ) );
	this->Disconnect( wxID_TOOL_DESTROYSESSION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_DestroySession ) );
	this->Disconnect( wxID_TOOL_SETUP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_Setup ) );
	m_treeActionList->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( GUIFrame::OnTreeSelChanged_ActionList ), NULL, this );
	this->Disconnect( wxID_TOOL_DOACTION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_DoAction ) );
	this->Disconnect( wxID_TOOL_MAKECALL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_MakeCall ) );
	this->Disconnect( wxID_TOOL_HANGUP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_Hangup ) );
	this->Disconnect( wxID_TOOL_TRANSFER, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_Transfer ) );
	this->Disconnect( wxID_TOOL_RECSTART, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_RecStart ) );
	this->Disconnect( wxID_TOOL_RECSTOP, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnToolClicked_RecStop ) );
}

CreateSessionDlg::CreateSessionDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );


	bSizer12->Add( 0, 5, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("서버주소"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText7->Wrap( -1 );
	fgSizer1->Add( m_staticText7, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxLEFT, 5 );

	m_textHostname = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), 0 );
	m_textHostname->SetMaxLength( 50 );
	fgSizer1->Add( m_textHostname, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("서비스포트"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxLEFT, 5 );

	m_textServicePort = new wxTextCtrl( this, wxID_ANY, wxT("5038"), wxDefaultPosition, wxSize( 160,-1 ), 0 );
	m_textServicePort->SetMaxLength( 5 );
	fgSizer1->Add( m_textServicePort, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText71 = new wxStaticText( this, wxID_ANY, wxT("AMI 계정"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	fgSizer1->Add( m_staticText71, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxLEFT, 5 );

	m_textAmiId = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), 0 );
	m_textAmiId->SetMaxLength( 20 );
	fgSizer1->Add( m_textAmiId, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText81 = new wxStaticText( this, wxID_ANY, wxT("AMI 비번"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	fgSizer1->Add( m_staticText81, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxLEFT, 5 );

	m_textAmiSecret = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), wxTE_PASSWORD );
	m_textAmiSecret->SetMaxLength( 20 );
	fgSizer1->Add( m_textAmiSecret, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("내선번호"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer1->Add( m_staticText9, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_textExten = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), 0 );
	m_textExten->SetMaxLength( 10 );
	fgSizer1->Add( m_textExten, 0, wxALL, 5 );

	bSizer12->Add( fgSizer1, 0, wxEXPAND, 5 );

	m_checkMd5 = new wxCheckBox( this, wxID_ANY, wxT("MD5 인증"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkMd5->Enable( false );

	bSizer12->Add( m_checkMd5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	m_buttonOk = new wxButton( this, wxID_OK, wxT("연결하기"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonOk->SetDefault();
	bSizer13->Add( m_buttonOk, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, wxT("그만두기"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALL, 5 );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	bSizer12->Add( bSizer13, 0, wxEXPAND, 5 );

	this->SetSizer( bSizer12 );
	this->Layout();
}

CreateSessionDlg::~CreateSessionDlg()
{
}

MakeCallDlg::MakeCallDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );


	bSizer12->Add( 0, 5, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText81 = new wxStaticText( this, wxID_ANY, wxT("어디서"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	fgSizer1->Add( m_staticText81, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxLEFT, 5 );

	m_textSourceNum = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0 );
	m_textSourceNum->SetMaxLength( 50 );
	fgSizer1->Add( m_textSourceNum, 0, wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("어디로"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_textDestNum = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0 );
	m_textDestNum->SetMaxLength( 50 );
	fgSizer1->Add( m_textDestNum, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	bSizer12->Add( fgSizer1, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	m_buttonOk = new wxButton( this, wxID_OK, wxT("전화걸기"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_buttonOk->SetDefault();
	bSizer13->Add( m_buttonOk, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, wxT("그만두기"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALL, 5 );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	bSizer12->Add( bSizer13, 0, wxEXPAND, 5 );

	this->SetSizer( bSizer12 );
	this->Layout();
}

MakeCallDlg::~MakeCallDlg()
{
}

CallTransferDlg::CallTransferDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );


	bSizer12->Add( 0, 5, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("어디로"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textDestNum = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 163,-1 ), 0 );
	m_textDestNum->SetMaxLength( 50 );
	fgSizer1->Add( m_textDestNum, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	bSizer12->Add( fgSizer1, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	m_buttonOk = new wxButton( this, wxID_OK, wxT("전달하기"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_buttonOk->SetDefault();
	bSizer13->Add( m_buttonOk, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, wxT("그만두기"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALL, 5 );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	bSizer12->Add( bSizer13, 0, wxEXPAND, 5 );

	this->SetSizer( bSizer12 );
	this->Layout();
}

CallTransferDlg::~CallTransferDlg()
{
}

SetupDlg::SetupDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );


	bSizer12->Add( 0, 5, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText81 = new wxStaticText( this, wxID_ANY, wxT("내선번호"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	fgSizer1->Add( m_staticText81, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxLEFT, 5 );

	m_textExten = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 184,-1 ), 0 );
	m_textExten->SetMaxLength( 10 );
	fgSizer1->Add( m_textExten, 0, wxTOP|wxRIGHT|wxLEFT, 5 );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("녹취파일"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	m_textRecFile = new wxTextCtrl( this, wxID_ANY, wxT("년월일_시분초_발_수_향"), wxDefaultPosition, wxSize( 184,-1 ), 0 );
	m_textRecFile->SetMaxLength( 50 );
	m_textRecFile->SetToolTip( wxT("형식예) \"년월일_시분초_발_수_향\" 인경우\n파일명) 20090407_133059_9000_01055090072_1.wav\n\n발 : 발신자번호\n수 : 수신자번호\n향 : 방향(Direction)으로서 인바운드는 '1', 아웃바운드는 '2'\n\n형식은 자유롭게 지정할 수 있습니다.\n예) [년-월-일]시분초_발_수_향") );

	fgSizer1->Add( m_textRecFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	bSizer12->Add( fgSizer1, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	m_buttonOk = new wxButton( this, wxID_OK, wxT("저장하기"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_buttonOk->SetDefault();
	bSizer13->Add( m_buttonOk, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_buttonCancel = new wxButton( this, wxID_CANCEL, wxT("그만두기"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonCancel, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALL, 5 );


	bSizer13->Add( 20, 0, 0, wxEXPAND, 5 );

	bSizer12->Add( bSizer13, 0, wxEXPAND, 5 );

	this->SetSizer( bSizer12 );
	this->Layout();
}

SetupDlg::~SetupDlg()
{
}

CallPopupDlg::CallPopupDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );

	wxBoxSizer* bSizer1v;
	bSizer1v = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer11h;
	bSizer11h = new wxBoxSizer( wxHORIZONTAL );

	m_staticMsg = new wxStaticText( this, wxID_STATIC_POPUPMSG, wxT("^^"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_NO_AUTORESIZE );
	m_staticMsg->Wrap( -1 );
	bSizer11h->Add( m_staticMsg, 1, wxALIGN_CENTER|wxALL, 5 );

	bSizer1v->Add( bSizer11h, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );

	this->SetSizer( bSizer1v );
	this->Layout();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CallPopupDlg::OnClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( CallPopupDlg::OnInitDialog ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CallPopupDlg::OnLeftDown ) );
	m_staticMsg->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CallPopupDlg::OnLeftDown ), NULL, this );
}

CallPopupDlg::~CallPopupDlg()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CallPopupDlg::OnClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( CallPopupDlg::OnInitDialog ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CallPopupDlg::OnLeftDown ) );
	m_staticMsg->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CallPopupDlg::OnLeftDown ), NULL, this );
}
