/***************************************************************
 * Name:      MyFirstWxMain.cpp
 * Purpose:   Code for Application Frame
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

#include "MyFirstWxMain.h"
#include "CreateSessionDlgImpl.h"
#include "MakeCallDlgImpl.h"
#include "SetupDlgImpl.h"
#include "CallPopupDlgImpl.h"
#include "CallTransferDlgImpl.h"
//#include "xami.xpm"
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


MyFirstWxFrame::MyFirstWxFrame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Welcome to Xeny's Asterisk Manager Interface!"), 0);
    //statusBar->SetStatusText(_("좋은 하루 되세요.^^"), 1);
    //statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif

    /// wxSQLite3 초기화
    wxSQLite3Database::InitializeSQLite();
    m_dbPtr = new wxSQLite3Database();
    m_dbPtr->Open(wxString::Format(_("%s\\xami.db"), wxStandardPaths::Get().GetDataDir().wx_str()));

    /// 환경설정 클래스 초기화
    m_setupVarsPtr = new SetupVars(m_dbPtr, _("APP_SETUP_VARS"), _("SV_GROUP"), _("SV_VARIABLE"), _("SV_VALUE"));

    /// 툴바 초기화
    InitMainToolbar();
    InitActionToolbar();
    InitActionProperty();

    /// 팝업창 초기화
    SetupVariableMap setupVarMap;
    long x, y, width, height;
    m_setupVarsPtr->GetVars(setupVarMap, _("POPUP"));
    setupVarMap[_("XPOS")].ToLong(&x);
    setupVarMap[_("YPOS")].ToLong(&y);
    setupVarMap[_("WIDTH")].ToLong(&width);
    setupVarMap[_("HEIGHT")].ToLong(&height);
    m_popupDlgPtr = new CallPopupDlgImpl(NULL);
    if(width && height) {
        m_popupDlgPtr->SetSize(x, y, width, height);
    }

    /// 통화중 여부
    m_isLinked = false;

    /// AMI 초기화
    AmiInit();

    m_taskBarIconPtr = new MyTaskBarIcon(this);
    if (!m_taskBarIconPtr->SetIcon(wxICON(ICO_XAMI), wxT("wAMI")))
        wxMessageBox(wxT("아이콘 파일을 열지 못했습니다."));
}

MyFirstWxFrame::~MyFirstWxFrame()
{
    if(!m_dbPtr) {
        m_dbPtr->Close();
        delete m_dbPtr;
    }

    if(m_popupDlgPtr) {
        m_popupDlgPtr->Destroy();
    }

    if(m_setupVarsPtr) {
        delete m_setupVarsPtr;
    }

    if(m_taskBarIconPtr) {
        delete m_taskBarIconPtr;
    }

    wxSQLite3Database::ShutdownSQLite();
    //wxMessageBox(_("MyFirstWxFrame::~MyFirstWxFrame() -> OK."));
}

void MyFirstWxFrame::InitMainToolbar()
{
    // 툴바 Tool 비트맵 지정
    m_toolbarMain->SetToolNormalBitmap(wxID_TOOL_CREATESESSION, wxBITMAP(BMP_TOOL_NEWSESSION));
    m_toolbarMain->SetToolNormalBitmap(wxID_TOOL_DESTROYSESSION, wxBITMAP(BMP_TOOL_DESTROYSESSION));
    m_toolbarMain->SetToolNormalBitmap(wxID_TOOL_SETUP, wxBITMAP(BMP_TOOL_SETUP));

    // 툴바 Tool 상태 지정
    m_toolbarMain->EnableTool(wxID_TOOL_CREATESESSION, true);
    m_toolbarMain->EnableTool(wxID_TOOL_DESTROYSESSION, false);
    m_toolbarMain->EnableTool(wxID_TOOL_SETUP, false);
}

void MyFirstWxFrame::InitActionToolbar()
{
    m_toolbarAnalyzer->SetToolNormalBitmap(wxID_TOOL_DOACTION, wxBITMAP(BMP_TOOL_DOACTION));
    m_toolbarAnalyzer->SetToolNormalBitmap(wxID_TOOL_MAKECALL, wxBITMAP(BMP_TOOL_MAKECALL));
    m_toolbarAnalyzer->SetToolNormalBitmap(wxID_TOOL_HANGUP, wxBITMAP(BMP_TOOL_HANGUP));
    m_toolbarAnalyzer->SetToolNormalBitmap(wxID_TOOL_TRANSFER, wxBITMAP(BMP_TOOL_TRANSFER));
    m_toolbarAnalyzer->SetToolNormalBitmap(wxID_TOOL_RECSTART, wxBITMAP(BMP_TOOL_RECSTART));
    m_toolbarAnalyzer->SetToolNormalBitmap(wxID_TOOL_RECSTOP, wxBITMAP(BMP_TOOL_RECSTOP));

    m_toolbarAnalyzer->Enable(false);
}

void MyFirstWxFrame::InitActionProperty()
{
    /// Action List 세팅하기
    wxTreeItemId rootId
        = m_treeActionList->AddRoot(wxString::Format(
            _("Action List (%d개)"),
            m_dbPtr->ExecuteScalar(_("SELECT COUNT(*) FROM AMI_ACTION_LIST"))));

	wxSQLite3ResultSet rs
        = m_dbPtr->ExecuteQuery(_("SELECT AL_NAME, AL_ID FROM AMI_ACTION_LIST ORDER BY AL_NAME"));

    AmiActionItemData* actionItemDataPtr;
	wxUint8 recordCnt = 0;

	while(rs.NextRow()) {
	    actionItemDataPtr = new AmiActionItemData();
	    actionItemDataPtr->SetAction(rs.GetAsString(0));
	    actionItemDataPtr->SetId(rs.GetInt(1));
	    //actionItemDataArray.Add(actionItemDataPtr);
	    m_treeActionList->AppendItem(rootId, rs.GetAsString(0), -1, -1, actionItemDataPtr);
		recordCnt++;
	}
	m_treeActionList->ExpandAll();

    m_pgActionVars->Append( new wxPropertyCategory(wxT("액션 정보")) );
    m_pgActionVars->Append( new wxStringProperty(wxT("권한          ")) );
    m_pgActionVars->Append( new wxStringProperty(wxT("개요          ")) );
    m_pgActionVars->Append( new wxStringProperty(wxT("설명          ")) );
    m_pgActionVars->Append( new wxPropertyCategory(wxT("액션 변수")) );
}

void MyFirstWxFrame::OnIconize(wxIconizeEvent& event)
{
    if(IsIconized()) {
        Show(false);
    }
}

void MyFirstWxFrame::OnClose(wxCloseEvent &event)
{
    SetupVariableMap setupVarMap;
    setupVarMap[_("XPOS")] = wxString::Format(_("%d"), m_popupDlgPtr->GetPosition().x);
    setupVarMap[_("YPOS")] =  wxString::Format(_("%d"), m_popupDlgPtr->GetPosition().y);
    setupVarMap[_("WIDTH")] = wxString::Format(_("%d"), m_popupDlgPtr->GetSize().GetWidth());
    setupVarMap[_("HEIGHT")] = wxString::Format(_("%d"), m_popupDlgPtr->GetSize().GetHeight());
    m_setupVarsPtr->SetVars(setupVarMap);

    AmiClose();
    Destroy();
}

void MyFirstWxFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void MyFirstWxFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    //wxMessageBox(msg, _("Welcome to..."));
}

void MyFirstWxFrame::OnToolClicked_DoAction(wxCommandEvent& event)
{
    if(event.GetId() == wxID_TOOL_DOACTION) {
        wxPGProperty* propPtr = m_pgActionVars->GetProperty(_("액션 변수"));
        wxPropertyGridIterator it = m_pgActionVars->GetIterator(wxPG_ITERATE_DEFAULT, propPtr);
        ActionVariableMap varMap;
        while(it.GetProperty()) {
            varMap[m_pgActionVars->GetPropertyName(*it)]
                = m_pgActionVars->GetPropertyValueAsString(*it);
            it++;
        }
        if(varMap.size() > 0) {
            m_sessionPtr->DoAction(varMap);
        }
    }
}

void MyFirstWxFrame::OnTreeSelChanged_ActionList(wxTreeEvent& event)
{
    wxTreeItemId itemId = event.GetItem();
    AmiActionItemData *item = (AmiActionItemData *)m_treeActionList->GetItemData(itemId);
    if(item) {
        wxSQLite3ResultSet rs = m_dbPtr->ExecuteQuery(
            wxString::Format(
                _("SELECT AL_PRIVILEGE, AL_SYNOPSIS, AL_DESCRIPTION FROM AMI_ACTION_LIST WHERE AL_ID = %d"),
                 item->GetId()));

        if(rs.NextRow()) {
            m_pgActionVars->SetPropertyValue(m_pgActionVars->GetProperty(_("권한          ")), rs.GetAsString(0));
            m_pgActionVars->SetPropertyValue(m_pgActionVars->GetProperty(_("개요          ")), rs.GetAsString(1));
            m_pgActionVars->SetPropertyValue(m_pgActionVars->GetProperty(_("설명          ")), rs.GetAsString(2));
        }
        rs.Finalize();

        rs = m_dbPtr->ExecuteQuery(
            wxString::Format(
                _("SELECT AV_NAME, AV_REQUIRED, AV_DESCRIPTION FROM AMI_ACTION_VARS WHERE AL_ID = %d"),
                item->GetId()));

        wxPGProperty* propVarParentPtr;
        wxPGProperty* propVarPtr ;
        m_pgActionVars->DeleteProperty(m_pgActionVars->GetProperty(_("액션 변수")));
        propVarParentPtr = m_pgActionVars->Append( new wxPropertyCategory(wxT("액션 변수")) );
        propVarPtr = m_pgActionVars->AppendIn(propVarParentPtr, new wxStringProperty(wxT("Action"), wxPG_LABEL, item->GetAction()));
        m_pgActionVars->SetPropertyBackgroundColour(propVarPtr, wxColour::wxColour(255,220,220));

        while(rs.NextRow()) {
            propVarPtr = m_pgActionVars->AppendIn(propVarParentPtr, new wxStringProperty(rs.GetAsString(0)));
            if(rs.GetAsString(1).IsSameAs(_("Y"))) {
                /// Property 배경색 지정
                m_pgActionVars->SetPropertyBackgroundColour(propVarPtr, wxColour::wxColour(255,220,220));
                // Property Cell을 지정하여 문자열 또는 색깔 지정
                //m_pgActionVars->SetPropertyCell(propVarPtr, 1, wxEmptyString, wxNullBitmap, wxColour::wxColour(200,0,0));
            }
            m_pgActionVars->SetPropertyHelpString(propVarPtr, rs.GetAsString(2));
        }
        rs.Finalize();
    }
}


void MyFirstWxFrame::OnToolClicked_CreateSession(wxCommandEvent& event)
{
    SetupVariableMap setupVarMap;
    m_setupVarsPtr->GetVars(setupVarMap, _("SESSION"), true);
    m_setupVarsPtr->GetVars(setupVarMap, _("USER"));

    CreateSessionDlgImpl sessionDlg(this);

    sessionDlg.SetHostname(setupVarMap[_("HOSTNAME")]);
    if(!setupVarMap[_("PORT")].Length()) setupVarMap[_("PORT")] = _("5038");
    sessionDlg.SetPort(setupVarMap[_("PORT")]);
    sessionDlg.SetAmiId(setupVarMap[_("AMIID")]);
    sessionDlg.SetExten(setupVarMap[_("EXTEN")]);

    if(sessionDlg.ShowModal() == wxID_OK) {
        setupVarMap[_("HOSTNAME")] = sessionDlg.GetHostname();
        setupVarMap[_("PORT")] = sessionDlg.GetPort();
        setupVarMap[_("AMIID")] = sessionDlg.GetAmiId();
        setupVarMap[_("AMIPW")] = sessionDlg.GetAmiPw();
        m_myExten = setupVarMap[_("EXTEN")] = sessionDlg.GetExten();

        if(setupVarMap[_("HOSTNAME")].Length() < 8 || setupVarMap[_("PORT")].Length() < 4) {
            wxMessageBox(_("서버주소와 포트를 정확하게 입력해주세요."), _("알려드립니다."));
            //m_popupDlgPtr->ShowMessage(_("서버주소와 포트를 정확하게 입력해주세요."));
            return;
        } else if(setupVarMap[_("AMIID")].Length() == 0 || setupVarMap[_("AMIPW")].Length() == 0) {
            wxMessageBox(_("AMI 인증 정보를 정확하게 입력주세요."), _("알려드립니다."));
            //m_popupDlgPtr->ShowMessage(_("AMI 인증 정보를 정확하게 입력주세요."));
            return;
        }

        m_sessionPtr = AmiCreateSession(setupVarMap[_("HOSTNAME")], setupVarMap[_("PORT")]);

        /// 세션이 만들어지면 인증 시도
        if(m_sessionPtr) {
            if(setupVarMap[_("AMIID")].Length() > 0 && setupVarMap[_("AMIPW")].Length() > 0)
                /// 사용자 인증
                m_loginActionId = m_sessionPtr->ActionLogin(setupVarMap[_("AMIID")], setupVarMap[_("AMIPW")]);
        }

        setupVarMap.erase(_("AMIPW"));
        m_setupVarsPtr->SetVars(setupVarMap);
    } else {
        //wxMessageBox(_("CANCEL"));
    }
}

void MyFirstWxFrame::OnToolClicked_DestroySession(wxCommandEvent& event)
{
    m_sessionPtr->ExitSession();
}

void MyFirstWxFrame::OnToolClicked_Setup( wxCommandEvent& event )
{
    SetupDlgImpl setupDlg(this);
    setupDlg.SetExten(m_myExten);
    if(!m_myRecForm.Length()) m_myRecForm = _("년월일_시분초_발_수_향");
    setupDlg.SetRecForm(m_myRecForm);

    if(setupDlg.ShowModal() == wxID_OK) {
        if(!setupDlg.GetExten().IsSameAs(m_myExten)) {
            m_myExten = setupDlg.GetExten();
            ActionVariableMap varMap;
            varMap[_("action")] = _("sipshowpeer");
            varMap[_("peer")] = m_myExten;
            m_sipShowPeerActionId = m_sessionPtr->DoAction(varMap);
        }
        if(!setupDlg.GetRecFileForm().IsSameAs(m_myRecForm)) {
            m_myRecForm = setupDlg.GetRecFileForm();
            m_setupVarsPtr->SetVar(_("RECFORM"), m_myRecForm);
        }
    }
}

void MyFirstWxFrame::OnToolClicked_MakeCall(wxCommandEvent& event)
{
    if(!m_sessionPtr) return;

    MakeCallDlgImpl makeCallDlg(this);
    makeCallDlg.SetSourceNum(m_myExten); // "어디서" 항목에 나의 내선번호 지정

    if(makeCallDlg.ShowModal() == wxID_OK) {
        if(makeCallDlg.GetSourceNum().Length() > 0 && makeCallDlg.GetDestNum().Length() > 0) {
            m_callerId = makeCallDlg.GetSourceNum();
            m_calledId = makeCallDlg.GetDestNum();

            ActionVariableMap varMap;
            varMap[_("action")] = _("originate");
            varMap[_("channel")] = wxString::Format(_("sip/%s"), m_callerId.wx_str());
            varMap[_("exten")] = makeCallDlg.GetDestNum();
            varMap[_("context")] = m_mySipMap[_("Context")];
            varMap[_("priority")] = _("1");
            varMap[_("callerid")] = m_callerId.wx_str();
            m_sessionPtr->DoAction(varMap);
        }
    }
}

void MyFirstWxFrame::OnToolClicked_Hangup(wxCommandEvent& event)
{
    if(!m_sessionPtr) return;

    ActionVariableMap varMap;
    varMap[_("action")] = _("hangup");
    varMap[_("channel")] = m_myChannel;
    m_sessionPtr->DoAction(varMap);
}

void MyFirstWxFrame::OnToolClicked_RecStart(wxCommandEvent& event)
{
    if(!m_sessionPtr) return;
    if(m_myChannel.Length() == 0) return;

    wxString filename = m_myRecForm;
    filename.Replace(_("년"), _("%Y"));
    filename.Replace(_("월"), _("%m"));
    filename.Replace(_("일"), _("%d"));
    filename.Replace(_("시"), _("%H"));
    filename.Replace(_("분"), _("%M"));
    filename.Replace(_("초"), _("%S"));
    filename.Replace(_("향"), wxString(m_currDirection));
    filename.Replace(_("발"), (m_currDirection == '1') ? m_myExten : m_callerId);
    filename.Replace(_("수"), (m_currDirection == '2') ? m_myExten : m_calledId);

    m_currRecFile = wxDateTime::Now().Format(filename);

    ActionVariableMap varMap;
    varMap[_("action")] = _("monitor");
    varMap[_("channel")] = m_myChannel;
    varMap[_("file")] = m_currRecFile;
    varMap[_("format")] = _("wav");
    varMap[_("mix")] = _("1");
    m_monitorActionId = m_sessionPtr->DoAction(varMap);
}

void MyFirstWxFrame::OnToolClicked_Transfer( wxCommandEvent& event )
{
    if(!m_sessionPtr) return;
    if(m_myChannel.Length() == 0) return;

    CallTransferDlgImpl xferDlg(this);
    if(xferDlg.ShowModal() == wxID_OK) {
        if(xferDlg.GetDestNum().Length() > 0) {
            ActionVariableMap varMap;
            varMap[_("action")] = _("redirect");
            varMap[_("channel")] = (m_currDirection == '1' ? m_destChannel : m_sourceChannel);
            varMap[_("exten")] = xferDlg.GetDestNum();
            varMap[_("context")] = m_mySipMap[_("Context")];
            varMap[_("priority")] = _("1");
            m_sessionPtr->DoAction(varMap);
        }
    }
}

void MyFirstWxFrame::OnToolClicked_RecStop(wxCommandEvent& event)
{
    if(!m_sessionPtr) return;
    if(m_myChannel.Length() == 0) return;

    ActionVariableMap varMap;
    varMap[_("action")] = _("stopmonitor");
    varMap[_("channel")] = m_myChannel;
    m_stopMonitorActionId = m_sessionPtr->DoAction(varMap);
}

void MyFirstWxFrame::OnSessionCreated(amiSessionPtr ptr)
{
    if(ptr == m_sessionPtr) {
        wxMessageBox(_("성공적으로 연결되었습니다."), _("즐거운 시간 되세요^^"));
        m_toolbarMain->EnableTool(wxID_TOOL_CREATESESSION, false);
        m_toolbarMain->EnableTool(wxID_TOOL_DESTROYSESSION, true);
        m_toolbarMain->EnableTool(wxID_TOOL_SETUP, true);
        m_toolbarAnalyzer->Enable(true);
        m_toolbarAnalyzer->Refresh(true);
    }
}

void MyFirstWxFrame::OnCreateSessionFailed(amiSessionPtr ptr)
{
    if(ptr == m_sessionPtr) {
        wxMessageBox(_("서버에 연결할 수 없습니다. 연결 정보를 확인해주세요."), _("죄송합니다."));
        m_toolbarMain->EnableTool(wxID_TOOL_CREATESESSION, true);
        m_toolbarMain->EnableTool(wxID_TOOL_DESTROYSESSION, false);
        m_toolbarMain->EnableTool(wxID_TOOL_SETUP, false);
        m_toolbarAnalyzer->Enable(false);
        m_toolbarAnalyzer->Refresh(true);
    }
}

void MyFirstWxFrame::OnSessionDestroyed(amiSessionPtr ptr)
{
    if(AmiIsExit()) return;

    if(ptr == m_sessionPtr) {
        wxMessageBox(_("서버와의 연결이 해제되었습니다."), _("알려드립니다."));
        m_toolbarMain->EnableTool(wxID_TOOL_CREATESESSION, true);
        m_toolbarMain->EnableTool(wxID_TOOL_DESTROYSESSION, false);
        m_toolbarMain->EnableTool(wxID_TOOL_SETUP, false);
        m_toolbarAnalyzer->Enable(false);
        m_toolbarAnalyzer->Refresh(true);

        m_isLoggedIn = false;
        m_sessionPtr = NULL;
    }
}

void MyFirstWxFrame::OnEventLog(wxString& str)
{
    if(m_textOutputLog->GetLastPosition() >= (10000))
        m_textOutputLog->Clear();

    m_textOutputLog->AppendText(str);
}

void MyFirstWxFrame::OnActionLog(wxString& str)
{
    if(m_textInputLog->GetLastPosition() >= (3000)) {
        m_textInputLog->Clear();
    }
    m_textInputLog->AppendText(str);
}

void MyFirstWxFrame::OnActionResponse(AmiActionResponse& r)
{
    ActionResponseMap& resMap = r.GetResponseMap();

    /// login 액션에 대한 응답인 경우
    if(resMap[_("ActionID")].IsSameAs(m_loginActionId)) {
        /// 인증 성공
        if(resMap[_("Response")].IsSameAs(_("Success"))) {
            m_isLoggedIn = true; // 멤버변수에 인증성공 세팅

            /// 지정한 내선번호가 있다면 해당 SIP 정보를 가져오도록 Action을 보낸다.
            if(m_myExten.Length() > 0) {
                ActionVariableMap varMap;
                varMap[_("action")] = _("sipshowpeer");
                varMap[_("peer")] =  m_myExten;
                m_sipShowPeerActionId = m_sessionPtr->DoAction(varMap);
            }
        }
        /// 인증 실패
        else {
            wxMessageBox(_("인증정보가 올바르지 않습니다."), _("알려드립니다."));
        }
    }
    /// SIP 정보를 받는다.
    else if(resMap[_("ActionID")].IsSameAs(m_sipShowPeerActionId)) {
        if(resMap[_("Response")].IsSameAs(_("Success"))) {
            m_mySipMap = resMap;
            /// DB에 내선정보 저장
            //m_dbPtr->ExecuteUpdate(wxString::Format(_("UPDATE APP_TEMP_SETUP SET TS_EXTEN = %s"), m_myExten.wx_str()));
            m_setupVarsPtr->SetVar(_("EXTEN"), m_myExten);
        } else {
            wxMessageBox(_("지정한 내선에 대한 정보가 없습니다.\n"), _("알려드립니다."));
            //m_sessionPtr->ExitSession(); // 세션을 끊는다.
            m_myExten.Clear();
        }
    }
    else if(resMap[_("ActionID")].IsSameAs(m_monitorActionId)) {
        if(resMap[_("Response")].IsSameAs(_("Success"))) {
            m_popupDlgPtr->ShowMessage(_("녹음을 시작합니다."), m_currRecFile);
            statusBar->SetStatusText(wxString::Format(_("녹음중..(%s.wav)"), m_currRecFile.wx_str()));
        } else {
            wxMessageBox(resMap[_("ActionID")]);
            wxMessageBox(_("녹음에 실패하였습니다!"), _("알려드립니다."));
        }
    }
    else if(resMap[_("ActionID")].IsSameAs(m_stopMonitorActionId)) {
        if(resMap[_("Response")].IsSameAs(_("Success"))) {
            //wxMessageBox(_("녹음을 성공적으로 마쳤습니다."), _("알려드립니다."));
            m_popupDlgPtr->ShowMessage(_("녹음을 완료하였습니다."), m_currRecFile);
            statusBar->SetStatusText(_("녹음을 성공적으로 마쳤습니다."));
        }
    }

    if(m_myExten.Length() > 0) {
        /// 상태바에 정보 표시
        statusBar->SetStatusText(wxString::Format(_("Server: %s  Exten: %s  Callerid: %s"),
            m_sessionPtr->GetHostname().wx_str(), m_myExten.wx_str(), m_mySipMap[_("Callerid")].wx_str()), 1);
    } else {
        statusBar->SetStatusText(_("▶▶▶ 내선을 지정하여 주세요."), 1);
    }
}

void MyFirstWxFrame::OnAmiEvent(AmiEventInfo& e)
{
    AmiEventMap& eventMap = e.GetEventMap();
    wxString eventStr = eventMap[_("Event")];

    /// 전화가 발/수신
    if(eventStr.IsSameAs(_("Dial"))) {
        m_sourceChannel = eventMap[_("Source")];
        m_destChannel = eventMap[_("Destination")];
        m_callerId = eventMap[_("CallerID")];
        m_callerName = eventMap[_("CallerIDName")];

        /// 발신
        if(m_sourceChannel.Find(wxString::Format(_("SIP/%s-"), m_myExten.wx_str())) != wxNOT_FOUND) {
            m_myChannel = m_sourceChannel;
            m_currDirection = '1';
        }
        /// 수신
        else if(m_destChannel.Find(wxString::Format(_("SIP/%s-"), m_myExten.wx_str())) != wxNOT_FOUND) {
            m_myChannel = m_destChannel;
            m_currDirection = '2';
            m_popupDlgPtr->ShowMessage(
                wxString::Format(_("발신자 : %s <%s>"), eventMap[_("CallerID")].wx_str(), eventMap[_("CallerIDName")].wx_str()),
                _("전화가 왔습니다."));
        }
    }
    /// CallerID 수신
    else if(eventStr.IsSameAs(_("Newcallerid"))) {
        m_calledId = eventMap[_("CallerID")];
        m_calledName = eventMap[_("CallerIDName")];
        /// 발신 때 수신자번호 추출
        if(m_currDirection == '1' && eventMap[_("Channel")].IsSameAs(m_destChannel)) {
            m_popupDlgPtr->ShowMessage(
                wxString::Format(_("전화번호 : %s"), m_calledId.wx_str()), _("전화를 걸고 있습니다.."));
        }
    }
    /// 전화 연결됨(중요: 내가 걸면 Channel1에, 내가 받을땐 Channel2에 myChannel 값이 있다.)
    /// Link가 두번 오는 경우가 있기 때문에 굉장히 중요하다.
    else if(eventStr.IsSameAs(_("Link"))) {
        /// 위의 (중요:)경우를 만족하기 위한 조건
        if((m_currDirection == '1' && m_myChannel.IsSameAs(eventMap[_("Channel1")]))
            || (m_currDirection == '2' && m_myChannel.IsSameAs(eventMap[_("Channel2")])))
        {
            m_callStartTime = wxDateTime::Now();
            m_isLinked = true;

            m_popupDlgPtr->ShowMessage(_("전화가 연결되었습니다!"),
                wxString::Format(_("발신 : %s  수신 : %s"), (m_currDirection == '1' ? m_myExten.wx_str() : m_callerId.wx_str()),
                                 (m_currDirection == '2' ? m_myExten.wx_str() : m_calledId.wx_str())));
            statusBar->SetStatusText(_("전화가 연결되었습니다! 기분 좋은 통화 되세요^^"));
        }
    }
    /// 전화 끊김(중요: 내 채널이 끊겨야 실제로 끊겨진 것이다.)
    /// 실제로 Hangup 이벤트가 무수히 오는걸 목격했다. 전화 거는 중에도.. 안끊겼어요..-_-;
    else if(eventStr.IsSameAs(_("Hangup"))) {
        if(eventMap[_("Channel")].IsSameAs(m_myChannel)) {
            m_myChannel.Clear();
            m_sourceChannel.Clear();
            m_destChannel.Clear();

            wxUint8 callMinutes = 0;
            wxUint8 callSeconds = 0;

            if(m_isLinked) {
                m_callEndTime = wxDateTime::Now();
                wxTimeSpan timeSpan = m_callEndTime.Subtract(m_callStartTime);
                callMinutes = timeSpan.GetSeconds().ToLong() / 60;
                callSeconds = timeSpan.GetSeconds().ToLong() % 60;
            }
            m_popupDlgPtr->ShowMessage(
                wxString::Format(_("통화시간 : %d분 %d초"), callMinutes, callSeconds), _("전화가 끊겼습니다."));
            statusBar->SetStatusText(_("전화가 끊겼습니다."));

            m_isLinked = false;
        }
    }
}


/// ///////////////////////////////////////////////////////
///
/// SetupVars Class's Member Functions
///
/// ///////////////////////////////////////////////////////

template <typename T>
void SetupVars::GetVars(T& varMap,
                        const wxString& groupStr,
                        bool clear)
{
    if(clear) {
        varMap.clear();
    }

    wxString queryStr =
        wxString::Format(_("select %s, %s from %s"),
                         m_variableColStr.wx_str(),
                         m_valueColStr.wx_str(),
                         m_tableStr.wx_str());

    if(groupStr.Length() > 0) {
        queryStr.Append(wxString::Format(_(" where %s='%s'"),
                                         m_groupColStr.wx_str(),
                                         groupStr.wx_str()));
    }

    wxSQLite3ResultSet rs = m_dbPtr->ExecuteQuery(queryStr);
    while(rs.NextRow()) {
        varMap[rs.GetAsString(0)] = rs.GetAsString(1);
    }
}

wxString SetupVars::GetVar(const wxString& varStr,
                           const wxString& groupStr)
{
    wxString queryStr;

    if(groupStr.Length() > 0) {
        queryStr =
            wxString::Format(_("select %s from %s where %s='%s' and %s='%s' limit 1"),
                             m_valueColStr.wx_str(),
                             m_tableStr.wx_str(),
                             m_groupColStr.wx_str(),
                             groupStr.wx_str(),
                             m_variableColStr.wx_str(),
                             varStr.wx_str());
    } else {
        queryStr =
            wxString::Format(_("select %s from %s where %s='%s' limit 1"),
                             m_valueColStr.wx_str(),
                             m_tableStr.wx_str(),
                             m_variableColStr.wx_str(),
                             varStr.wx_str());
    }

    wxSQLite3ResultSet rs = m_dbPtr->ExecuteQuery(queryStr);
    if(rs.NextRow()) {
        return rs.GetAsString(0);
    } else {
        return _("");
    }
}

template <typename T>
wxUint8 SetupVars::SetVars(T& varMap)
{
    wxUint8 resultCnt = 0;
    typename T::iterator it;

    for(it = varMap.begin(); it != varMap.end(); ++it) {
        if(!it->first.Length()) continue;

         wxString query =
            wxString::Format(_("update %s set %s='%s' where %s='%s'"),
                             m_tableStr.wx_str(),
                             m_valueColStr.wx_str(),
                             it->second.wx_str(),
                             m_variableColStr.wx_str(),
                             it->first.wx_str());

        resultCnt += m_dbPtr->ExecuteUpdate(query);
    }
    return resultCnt;
}

wxUint8 SetupVars::SetVar(const wxString& varStr,
                          const wxString& valueStr)
{
    if(!varStr.Length()) return 0;

    wxString query =
        wxString::Format(_("update %s set %s='%s' where %s='%s'"),
                         m_tableStr.wx_str(),
                         m_valueColStr.wx_str(),
                         valueStr.wx_str(),
                         m_variableColStr.wx_str(),
                         varStr.wx_str());
    return m_dbPtr->ExecuteUpdate(query);
}


/// ///////////////////////////////////////////////////////
///
/// MyTaskBarIcon Class's Member Functions
///
/// ///////////////////////////////////////////////////////

enum {
    PU_RESTORE = 10001,
    PU_EXIT,
    PU_MENU_MAKECALL,
    PU_MENU_HANGUP,
    PU_MENU_RECSTART,
    PU_MENU_RECSTOP
};


BEGIN_EVENT_TABLE(MyTaskBarIcon, wxTaskBarIcon)
    EVT_MENU(PU_RESTORE, MyTaskBarIcon::OnMenuRestore)
    EVT_MENU(PU_EXIT,    MyTaskBarIcon::OnMenuExit)
    EVT_TASKBAR_LEFT_DCLICK  (MyTaskBarIcon::OnLeftButtonDClick)
    EVT_MENU(PU_MENU_MAKECALL, MyTaskBarIcon::OnMenuMakeCall)
    EVT_MENU(PU_MENU_HANGUP, MyTaskBarIcon::OnMenuHangup)
    EVT_MENU(PU_MENU_RECSTART, MyTaskBarIcon::OnMenuRecStart)
    EVT_MENU(PU_MENU_RECSTOP, MyTaskBarIcon::OnMenuRecStop)
END_EVENT_TABLE()

void MyTaskBarIcon::OnMenuRestore(wxCommandEvent& )
{
    m_wndPtr->Show(true);
    ((wxTopLevelWindow*)m_wndPtr)->Maximize(false);
}

void MyTaskBarIcon::OnMenuExit(wxCommandEvent& )
{
    m_wndPtr->Close(true);
}

void MyTaskBarIcon::OnMenuMakeCall(wxCommandEvent& e)
{
    ((MyFirstWxFrame*)m_wndPtr)->OnToolClicked_MakeCall(e);
}

void MyTaskBarIcon::OnMenuHangup(wxCommandEvent& e)
{
    ((MyFirstWxFrame*)m_wndPtr)->OnToolClicked_Hangup(e);
}

void MyTaskBarIcon::OnMenuRecStart(wxCommandEvent& e)
{
    ((MyFirstWxFrame*)m_wndPtr)->OnToolClicked_RecStart(e);
}

void MyTaskBarIcon::OnMenuRecStop(wxCommandEvent& e)
{
    ((MyFirstWxFrame*)m_wndPtr)->OnToolClicked_RecStop(e);
}

// Overridables
wxMenu *MyTaskBarIcon::CreatePopupMenu()
{
    // Try creating menus different ways
    // TODO: Probably try calling SetBitmap with some XPMs here
    wxMenu *menu = new wxMenu;
    menu->Append(PU_RESTORE, _T("AMI 분석기"));
    menu->AppendSeparator();
    menu->Append(PU_MENU_MAKECALL, _T("전화걸기"));
    menu->Append(PU_MENU_HANGUP, _T("전화끊기"));
    menu->AppendSeparator();
    menu->Append(PU_MENU_RECSTART, _T("녹음시작"));
    menu->Append(PU_MENU_RECSTOP, _T("녹음종료"));
#ifndef __WXMAC_OSX__ /*Mac has built-in quit menu*/
    menu->AppendSeparator();
    menu->Append(PU_EXIT,    _T("끝내기"));
#endif
    return menu;
}

void MyTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
    //((wxTopLevelWindow*)m_wndPtr)->Maximize(false);
    m_wndPtr->Show(true);
}
