#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/listimpl.cpp>
#include "xami.h"

// the only requirement for the rest is to be AFTER the full declaration of
// MyListElement (for WX_DECLARE_LIST forward declaration is enough), but
// usually it will be found in the source file and not in the header
//WX_DEFINE_LIST(AmiActionItemList);

wxAMI::wxAMI(wxWindow* parentWndPtr)
{
    m_parentWndPtr = parentWndPtr;
    m_messageProcPtr = NULL;
    m_exitAmi = false;
}

wxAMI::~wxAMI()
{
    //wxMessageBox(_("~wxAMI() -> OK."));
}

int wxAMI::AmiInit()
{
    if(!m_messageProcPtr) {
        m_messageProcPtr = new AmiMessageProc(this);
        if(m_messageProcPtr->Create() != wxTHREAD_NO_ERROR) {
            wxMessageBox(_("Can't create AmiMessageProc thread!"));
            goto MessageProcError;
        }
        else {
            if(m_messageProcPtr->Run() != wxTHREAD_NO_ERROR) {
                wxMessageBox(_("Can't start AmiMessageProc thread!"));
                goto MessageProcError;
            }
        }
    }
    return 0;

MessageProcError:
    if(m_messageProcPtr) {
        delete m_messageProcPtr;
        m_messageProcPtr = NULL;
    }
    return -1;
}

void wxAMI::AmiClose()
{
    m_exitAmi = true;

    if(m_messageProcPtr) {
        m_messageProcPtr->Delete();
        while(!m_messageProcPtr->m_bExitMessageProc) {
            Sleep(10L);
        }
        m_messageProcPtr = NULL;
    }

    /// 모든 세션이 종료될 때까지 기다린다.
    while(!m_amiSessions.IsEmpty()) {
        Sleep(10L);
    }

    wxUint16 i;
    /// 이벤트 큐 자원 해제
    for(i = 0; i < GetEventQueue().GetCount(); i++) {
        delete GetEventQueue().Item(i);
    }
    GetEventQueue().Clear();

    /// 액션 큐 자원 해제
    for(i = 0; i < GetResponseQueue().GetCount(); i++) {
        delete GetResponseQueue().Item(i);
    }
    GetResponseQueue().Clear();

    //wxMessageBox(_("wxAMI::amiClose() -> OK."));
}

AmiSession *wxAMI::AmiCreateSession(wxString& hostname,
                                    wxString& service)
{
    /// Checks exist connections for a new session.
    for(wxInt8 i = 0; (unsigned)i < m_amiSessions.Count(); i++) {
        if(m_amiSessions.Item(i)->GetHostname().IsSameAs(hostname))
            return NULL;
    }

    AmiSession *sessionPtr = new AmiSession(this, hostname, service);

    if(sessionPtr->Create() != wxTHREAD_NO_ERROR) {
        wxMessageBox(_("Can't create session thread!"));
        delete sessionPtr;
        return NULL;
    }
    m_amiSessions.Add(sessionPtr);

    /// Runs the new thread.
    if(sessionPtr->Run() != wxTHREAD_NO_ERROR) {
        wxMessageBox(_("Can't start session thread!"));
        delete sessionPtr;
        return NULL;
    }

    return sessionPtr;
}

amiSessionPtr wxAMI::AmiGetSessionPtr(wxString& hostname)
{
    for(wxInt8 i = 0; (unsigned)i < m_amiSessions.Count(); i++) {
        if(m_amiSessions.Item(i)->GetHostname().IsSameAs(hostname))
            return m_amiSessions.Item(i);
    }
    return NULL;
}

wxString wxAMI::GetMsgItemValue(const wxString& refStr,
                                const wxChar* itemStr)
{
    wxInt16 pos1 = 0, pos2 = 0;
    if((pos1 = refStr.Find(itemStr)) != wxNOT_FOUND) {
        pos2 = refStr.find(_("\r\n"), (pos1 += wxString(itemStr).Length()));
        if(pos2 != wxNOT_FOUND) {
            return refStr.Mid(pos1, pos2-pos1);
        }
    }
    return _("");
}

template <typename T>
void wxAMI::SetMsgItemMap(T& map, wxString& ref)
{
    wxUint16 startPos = 0;
    wxUint16 targetPos = 0;
    wxUint16 i = 0;
    wxChar spaceChar = ' ';
    wxChar colonChar = ':';

    wxString keyStr;
    wxString valueStr;

    while(true) {
        /// 라인단위로 문자열을 가져온다.
        wxString lineStr = ref.Mid(startPos, (targetPos = ref.find(_("\r\n"), startPos))-startPos);
        /// 만약 라인이 없거나, 시작점이 CRLF이면 while 루틴을 종료한다.
        if(lineStr.Length() == 0 || startPos == targetPos) break;

        for(i = 0; i < lineStr.Length(); i++) {
            if(lineStr.GetChar(i) == spaceChar) {
                if(i > 0 && lineStr.GetChar(i-1) == colonChar) {
                    keyStr = lineStr.Mid(0, i-1); // 시작지점부터 콜론 전까지를 Key로 세팅
                    valueStr = lineStr.Mid(i+1); // 공백 다음부터 CRLF 전까지를 Key에 대한 Value로 세팅
                    map[keyStr] = valueStr; // Map에 Key와 Value 세팅
                    startPos = targetPos + 2; // 시작지점을 CRLF 다음으로 지정
                    break;
                }
                /// 공백이지만 앞에 콜론(:)이 없는 경우
                else {
                    /// 만약 앞에 세팅된 키 값이 있다면 그 키에 Value를 추가한다.
                    if(keyStr.Length() > 0) {
                        map[keyStr].Append(_("\r\n"));
                        map[keyStr].Append(lineStr);
                        startPos = targetPos + 2; // 시작지점을 CRLF 다음으로 지정
                        break;
                    }
                }
            }
        }
        /// 공백이 없는 경우
        if(i > 0 && i >= lineStr.Length()) {
            /// 앞에 세팅된 키 값이 있다면 그 키에 Value를 추가(appending)한다.
            if(keyStr.Length() > 0) {
                map[keyStr].Append(_("\r\n"));
                map[keyStr].Append(lineStr);
                startPos = targetPos + 2; // 시작지점을 CRLF 다음으로 지정
            }
            /// 아니면 무시한다. (이런 경우는 없다.)
            else {
                continue;
            }
        }
    }
}


/// ///////////////////////////////////////////////////////
///
/// AmiSession Class's Member Functions
/// AMI 세션 처리
///
/// ///////////////////////////////////////////////////////

void* AmiSession::Entry()
{
    if(Connect() == AMI_SUCCESS) {
        ReadMessage();
    }

    return NULL;
}

// called when the thread exits - whether it terminates normally or is
// stopped with Delete() (but not when it is Kill()ed!)
void AmiSession::OnExit()
{
    wxCriticalSectionLocker locker(m_criticalSection);

    if(m_sockClient) {
        m_sockClient->Destroy();
        m_sockClient = NULL;
    } //delete m_sockClient; //m_sockClient->Destory() 가 delete를 대신한다.

    AmiSessionArray& amiSessions = m_ami->AmiGetSessionArray();
    amiSessions.Remove(this);

    // 세션종료 이벤트 호출
    m_ami->OnSessionDestroyed(this);
    //wxMessageBox(_("AmiSockTrhead::OnExit() -> OK."));
}

amiResult AmiSession::Connect()
{
    wxIPV4address addr;
    addr.Hostname(m_hostname);
    addr.Service(m_service);

    m_sockClient->Connect(addr, false);
    m_sockClient->WaitOnConnect(10);

    if (m_sockClient->IsConnected()) {
        m_sockClient->SetFlags(wxSOCKET_NOWAIT);
        m_ami->OnSessionCreated(this);
        return 0;
    }
    else
    {
        m_ami->OnCreateSessionFailed(this);
        m_sockClient->Close();
        return -1;
    }
}

amiResult AmiSession::ReadMessage()
{
    enum AMI_MSG {
        AMI_NONE,
        AMI_RESPONSE,
        AMI_EVENT
    };

    wxUint32 rlen = 0;
    wxUint32 wlen = 0;
    //char recvBuf[1024+1];
    char recvChar;
    wxString recvStr;
    wxString foundStr;

    wxInt32 pos = 0;
    wxUint8 actionCnt = 0;
    wxUint8 msgType = AMI_NONE;

    while(!m_ami->AmiIsExit() && !m_exitSession) {
        rlen = m_sockClient->Read(&recvChar, 1).LastCount();
        if(rlen > 0) {
            recvStr.Append(wxString::FromUTF8((const char*)&recvChar, rlen));
            if((pos = recvStr.Find(_("\r\n\r\n"))) != wxNOT_FOUND) {
                // 이벤트와 액션응답 구분
                if((pos = recvStr.Find(_("Response: "))) != wxNOT_FOUND) {
                    msgType = AMI_RESPONSE;
                }
                else if((pos = recvStr.Find(_("Event: "))) != wxNOT_FOUND) {
                    /// Action 응답이 이벤트 형태로 오는 것이 있어서
                    /// 처음엔 액션응답으로 분류했으나, 문제가 있어서 이벤트로 처리하기로 함.
                    /// 2009-04-08, Xeny
                    //if(recvStr.Find(_("ActionID: ")) != wxNOT_FOUND)
                    //    msgType = AMI_RESPONSE;
                    //else
                        msgType = AMI_EVENT;
                }
                else {
                    recvStr.Clear();
                    continue;
                }
                // 메시지를 해당 큐에 입력
                if(msgType == AMI_RESPONSE) {
                    AmiActionResponse* responsePtr = new AmiActionResponse();
                    responsePtr->SetPlaintext(recvStr.Mid(pos));
                    responsePtr->SetSessionPtr(this);
                    m_ami->AddResponse(responsePtr);
                } else if(msgType == AMI_EVENT) {
                    AmiEventInfo* eventPtr = new AmiEventInfo();
                    eventPtr->SetPlaintext(recvStr.Mid(pos));
                    eventPtr->SetSessionPtr(this);
                    m_ami->AddEvent(eventPtr);
                }
                recvStr.Clear();
            }
            // 쉬거나 다음 작업 실행하지 않고 계속 이벤트 수신
            continue;
        } else {
            if(m_sockClient->IsDisconnected()) {
                return -1;
            }
        }

        // 액션 전달 루틴
        while((actionCnt = GetActionQueue().GetCount())) {
            // 액션 큐에서 첫 번째 메시지를 하나 읽는다.
            wxString actionStr = GetActionQueue().Item(0);

            // 액션 메시지를 소켓에 기록한다.
            wlen = m_sockClient->Write(actionStr.ToUTF8(), strlen(actionStr.ToUTF8())).LastCount();
            if(wlen > 0) m_ami->OnActionLog(actionStr);

            // 읽었던 메시지를 큐에서 삭제한다.
            GetActionQueue().RemoveAt(0);

            // 쉬지 않고 바로 다음 작업을 실행한다.
            continue;
        }
        Sleep(100L);
    }
    if(m_exitSession) {
        return -2;
    }

    return AMI_SUCCESS;
}


/// ///////////////////////////////////////////////////////
///
/// AmiAction Class's Member Functions
/// AMI Action 처리
///
/// ///////////////////////////////////////////////////////

wxString AmiAction::GetActionId()
{
    static wxUint16 serial = 0;
    if(++serial > 999) serial = 0;

    wxString actionId(
        wxString::Format(_("%s_%s%03d"),
            m_currSessionPtr->GetHostname().wx_str(),
            wxDateTime::Now().Format(_("%H%M%S")).wx_str(),
            serial));

    return actionId;
}

amiActionID AmiAction::ActionLogin(const wxString& Username,
                                   const wxString& Secret,
                                   const wxString& AuthType,
                                   wxString ActionID)
{
    wxString actionStr;
    actionStr.Append(wxString::Format(_("action: login%s"), AMI_CRLF));
    actionStr.Append(wxString::Format(_("username: %s%s"), Username.wx_str(), AMI_CRLF));
    actionStr.Append(wxString::Format(_("secret: %s%s"), Secret.wx_str(), AMI_CRLF));
    actionStr.Append(wxString::Format(_("authtype: %s%s"), AuthType.wx_str(), AMI_CRLF));
    if(ActionID.Length() == 0) ActionID = GetActionId();
    actionStr.Append(wxString::Format(_("actionid: %s%s"), ActionID.wx_str(), AMI_CRLF));
    actionStr.Append(AMI_CRLF);
    PostAction(actionStr);
    return ActionID;
}

amiActionID AmiAction::DoAction(ActionVariableMap& varMap)
{
    wxString actionStr;
    ActionVariableMap::iterator it;

    if(varMap[_("actionid")].Length() == 0) {
        varMap[_("actionid")] = GetActionId();
    }

    for(it = varMap.begin(); it != varMap.end(); ++it) {
        if(it->second.Length() > 0 && !it->second.IsSameAs(_("(optional)"))) {
            actionStr.Append(wxString::Format(_("%s: %s"), it->first.wx_str(), it->second.wx_str()));
            actionStr.Append(AMI_CRLF);
        }
    }

    actionStr.Append(AMI_CRLF);
    PostAction(actionStr);

    return varMap[_("actionid")];
}


/// ///////////////////////////////////////////////////////
///
/// SetupVars Class's Member Functions
/// AMI 메시지(Response & Event) 처리 클래스
///
/// ///////////////////////////////////////////////////////

void* AmiMessageProc::Entry()
{
    m_bExitMessageProc = false;
    AmiEventArray& eventQueue = m_ami->GetEventQueue();
    AmiResponseArray& responseQueue = m_ami->GetResponseQueue();
    //wxUint16 i;

    while(!m_ami->AmiIsExit()) {
        // 이벤트 처리
        //for(i = 0; i < eventQueue.GetCount(); i++) {
        while(eventQueue.GetCount() > 0) {
            AmiEventInfo* eventPtr = eventQueue.Item(0);
            wxString eventStr = eventPtr->GetPlaintext();
            m_ami->OnEventLog(eventStr);

            AmiEventMap& eventMap = eventPtr->GetEventMap();
            m_ami->SetMsgItemMap(eventMap, eventStr);
            m_ami->OnAmiEvent(*eventPtr);
            /*if(eventMap[_("Event")].IsSameAs(_("Dial"))) {
                m_ami->OnDial(*eventPtr);
            }*/


            /*// Map 내용을 확인한다.
            AmiEventMap::iterator it;
            for(it = eventMap.begin(); it != eventMap.end(); ++it) {
                wxMessageBox(wxString::Format(_("key: %s, value: %s"), it->first.wx_str(), it->second.wx_str()));
            }*/

            delete eventPtr;
            eventQueue.RemoveAt(0);
            //eventQueue.Remove(eventInfoPtr);
        }
        //if(i > 0) { eventQueue.Clear(); }

        // 액션응답 처리
        //for(i = 0; i < responseQueue.GetCount(); i++) {
        while(responseQueue.GetCount() > 0) {
            AmiActionResponse* responsePtr = responseQueue.Item(0);
            wxString responseStr = responsePtr->GetPlaintext();
            m_ami->OnEventLog(responseStr);

            ActionResponseMap& responseMap = responsePtr->GetResponseMap();
            m_ami->SetMsgItemMap(responseMap, responseStr);
            m_ami->OnActionResponse(*responsePtr);

            /*// Map 내용을 확인한다.
            ActionResponseMap::iterator it;
            for(it = responseMap.begin(); it != responseMap.end(); ++it) {
                wxMessageBox(wxString::Format(_("key: %s, value: %s"), it->first.wx_str(), it->second.wx_str()));
            }*/

            delete responsePtr;
            responseQueue.RemoveAt(0);
            //responseQueue.Remove(actionResponsePtr);
        }
        //if(i > 0) { responseQueue.Clear(); }

        Sleep(100L);
    }

    m_bExitMessageProc = true;
    return NULL;
}

// called when the thread exits - whether it terminates normally or is
// stopped with Delete() (but not when it is Kill()ed!)
void AmiMessageProc::OnExit()
{
    //wxMessageBox(_("AmiMessageBoxProc::OnExit() -> OK."));
}
