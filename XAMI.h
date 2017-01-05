#ifndef MYAMI_H_INCLUDED
#define MYAMI_H_INCLUDED

#include <wx/socket.h>
#include <wx/list.h>
#include <wx/hashmap.h>

#include "xami_action.h"
#include "xami_event.h"

const wxInt8 AMI_SUCCESS = 0;
const wxInt8 AMI_FAIL = -1;
const static wxChar* AMI_CRLF = _("\r\n");

//class AmiActionItem;
//WX_DECLARE_LIST(AmiActionItem, AmiActionItemList);

class AmiSession;
WX_DEFINE_ARRAY_PTR(AmiSession*, AmiSessionArray);
WX_DEFINE_ARRAY_PTR(AmiEventInfo*, AmiEventArray);
WX_DEFINE_ARRAY_PTR(AmiActionResponse*, AmiResponseArray);

typedef wxInt32 amiResult;
typedef wxInt8 amiSessionId;
typedef AmiSession* amiSessionPtr;

///
/// AMI procedure class
///
class wxAMI : public AmiEvent
{
    friend class AmiSession;
    friend class AmiEvent;
    friend class AmiAction;
    friend class AmiMessageProc;

    /// Member Variables
    private:
        bool m_exitAmi;

        wxWindow* m_parentWndPtr;

        AmiSessionArray m_amiSessions; // 세션 리스트
        AmiEventArray m_eventQueue; // 이벤트 큐
        AmiResponseArray m_responseQueue; // 응답 큐

        AmiMessageProc* m_messageProcPtr; // 메시지(이벤트/액션응답) 처리 클래스

        wxCriticalSection m_eventCriticalSection;
        wxCriticalSection m_reponseCriticalSection;

    /// Member Functions
    private:
        /// 이벤트 큐 관련
        // 이벤트 큐 얻기
        AmiEventArray& GetEventQueue() { return m_eventQueue; }
        // 이벤트 정보 추가
        void AddEvent(AmiEventInfo* amiEventInfoPtr)
        {
            wxCriticalSectionLocker locker(m_eventCriticalSection);
            m_eventQueue.Add(amiEventInfoPtr);
        }

        /// 응답 큐 관련
        // 응답 큐 얻기
        AmiResponseArray& GetResponseQueue() { return m_responseQueue; }
        // 응답 정보 추가
        void AddResponse(AmiActionResponse* amiResponsePtr)
        {
            wxCriticalSectionLocker locker(m_reponseCriticalSection);
            m_responseQueue.Add(amiResponsePtr);
        }

        /// 메시지 처리 클래스 관련
        AmiMessageProc* GetMessageProcPtr() { return m_messageProcPtr; }
        wxString GetMsgItemValue(const wxString& refStr,
                                 const wxChar* itemStr);
        template <typename T> void SetMsgItemMap(T& map, wxString& ref);

    protected:
        wxAMI(wxWindow* parentWndPtr = NULL);
        virtual ~wxAMI();

        amiResult AmiInit();
        void AmiClose();

        bool AmiIsExit() { return m_exitAmi; }

        AmiSession *AmiCreateSession(wxString& hostname,
                                     wxString& service);
        AmiSessionArray& AmiGetSessionArray() { return m_amiSessions; }

        amiSessionPtr AmiGetSessionPtr(wxString& hostname);

        virtual void OnSessionCreated(amiSessionPtr ptr) {}
        virtual void OnSessionDestroyed(amiSessionPtr ptr) {}
        virtual void OnCreateSessionFailed(amiSessionPtr ptr) {}

        /// Action Response
        virtual void OnActionResponse(AmiActionResponse& res) {}
};

class AmiSession : public AmiAction,
                   public wxThread
{
    private:
        wxAMI* m_ami;

        bool m_exitSession;

        // AMI 서버 정보
        wxString m_hostname;
        wxString m_service;

        // 클라이언트 소켓
        wxSocketClient* m_sockClient;

        // 동기화를 위한 정의
        wxCriticalSection m_criticalSection;

    public:
        AmiSession(wxAMI* ami,
                   wxString& hostname,
                   wxString& service)
                   : AmiAction(this), m_ami(ami), m_hostname(hostname), m_service(service)
        {
            m_exitSession = false;
            m_sockClient = new wxSocketClient();
        }
        virtual ~AmiSession() {}

        wxString& GetHostname() { return m_hostname; }
        wxString& GetService() { return m_service; }

        wxSocketClient* GetSockClient() { return m_sockClient; }
        bool IsConnected() { return m_sockClient->IsConnected(); }
        bool IsDisconnected() { return m_sockClient->IsDisconnected(); }
        void ExitSession() { m_exitSession = true; }

    private:
        // thread execution starts here
        virtual void *Entry();
        // called when the thread exits - whether it terminates normally or is
        // stopped with Delete() (but not when it is Kill()ed!)
        virtual void OnExit();

    private:
        amiResult Connect();
        amiResult ReadMessage();
};

class AmiMessageProc : public wxThread
{
    friend class wxAMI;

    private:
        wxAMI* m_ami;
        bool m_bExitMessageProc;

    public:
        AmiMessageProc(wxAMI* ami) : m_ami(ami) {}
        ~AmiMessageProc() {}

    private:
        // thread execution starts here
        virtual void *Entry();
        // called when the thread exits - whether it terminates normally or is
        // stopped with Delete() (but not when it is Kill()ed!)
        virtual void OnExit();
};

#endif // MYAMI_H_INCLUDED
