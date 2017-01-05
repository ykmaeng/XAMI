#ifndef XAMI_ACTION_H_INCLUDED
#define XAMI_ACTION_H_INCLUDED

//#include "xami.h"

typedef wxString amiActionID;

class wxAMI;
class AmiSession;

// 하나의 액션 응답에 대한 맵
WX_DECLARE_STRING_HASH_MAP(wxString, ActionResponseMap);

// 사용자 지정 Action 변수 맵
WX_DECLARE_STRING_HASH_MAP(wxString, ActionVariableMap);

class AmiActionResponse
{
    private:
        wxString m_plaintext;
        ActionResponseMap m_responseMap;
        AmiSession* m_sessionPtr;

    public:
        ActionResponseMap& GetResponseMap() { return m_responseMap; }
        AmiSession* GetSessionPtr() { return m_sessionPtr; }
        wxString& GetPlaintext() { return m_plaintext; }

        void SetPlaintext(const wxString& str) { m_plaintext = str; }
        void SetSessionPtr(AmiSession* ptr) { m_sessionPtr = ptr; }

};

class AmiActionItem
{
    public:
        AmiActionItem();
        virtual ~AmiActionItem();

        const wxString& GetAction() { return m_action; }
        const wxString& GetPrivilege() { return m_privilege; }
        const wxString& GetSynopsis() { return m_synopsis; }
        const wxString& GetDescription() { return m_description; }
        const ActionVariableMap& GetActionVariableMap() { return m_actionVariableMap; }

    private:
        void SetAction(wxString action) { m_action = action; }
        void SetPrivilege(wxString privilege) { m_privilege = privilege; }
        void SetSynopsis(wxString synopsis) { m_synopsis = synopsis; }
        void SetDescription(wxString description) { m_description = description; }

    private:
        //Action command specificatoin
        wxString m_action;
        wxString m_privilege;
        wxString m_synopsis;
        wxString m_description;

        //Action variable list(using wxHashMap)
        ActionVariableMap m_actionVariableMap;
};

///
/// AMI Action Commands
///
class AmiAction
{
    private:
        wxCriticalSection m_actionQueueCriticalSection;
        wxArrayString m_actionQueue; // 액션 큐
        AmiSession* m_currSessionPtr;

    protected:
        // 액션 큐 핸들 얻기
        wxArrayString& GetActionQueue() { return m_actionQueue; }

        // 액션 큐에 메시지 넣기
        wxInt8 PostAction(wxString& actionStr)
        {
            wxCriticalSectionLocker locker(m_actionQueueCriticalSection);
            return m_actionQueue.Add(actionStr);
        }

        // 액션에 대한 ActionID 기본값 얻기([세션호스트명]_[시분초랜덤숫자3자리])
        wxString GetActionId();

    public:
        AmiAction(AmiSession* currSessionPtr) : m_currSessionPtr(currSessionPtr) {}
        virtual ~AmiAction() {}

        amiActionID ActionLogin(const wxString& Username,
                                const wxString& Secret,
                                const wxString& AuthType = _(""),
                                wxString ActionID = _(""));

        amiActionID ActionAbsoluteTimeout(const wxString& Channel,
                                          const wxString& Timeout,
                                          wxString ActionID = _(""));
        amiActionID ActionChangeMonitor(const wxString& Channel,
                                        const wxString& File,
                                        wxString ActionID = _(""));
        amiActionID ActionCommand(const wxString& Command,
                                  wxString ActionID = _(""));
        amiActionID ActionDBGet(const wxString& Family,
                                const wxString& Key,
                                wxString ActionID = _(""));
        amiActionID ActionDBPut(const wxString& Family,
                                const wxString& Key,
                                const wxString& Value,
                                wxString ActionID = _(""));
        amiActionID ActionEvents(const wxString& EventMask);
        amiActionID ActionExtensionState(const wxString& Exten,
                                         const wxString& Context,
                                         wxString ActionID = _(""));
        amiActionID ActionGetConfig(const wxString& Filename,
                                    wxString ActionID = _(""));
        amiActionID ActionGetVar(const wxString& Channel,
                                 const wxString& Variable,
                                 wxString ActionID = _(""));
        amiActionID ActionHangup(const wxString& Channel,
                                 wxString ActionID = _(""));
        amiActionID ActionIAXnetstats(wxString ActionID = _(""));
        amiActionID ActionIAXpeers(wxString ActionID = _(""));
        amiActionID ActionListCommands(wxString ActionID = _(""));
        amiActionID ActionLogoff(wxString ActionID = _(""));
        amiActionID ActionMailboxCount(const wxString& Mailbox,
                                       wxString ActionID = _(""));
        amiActionID ActionMailboxStatus(const wxString& Mailbox,
                                        wxString ActionID = _(""));
        amiActionID ActionMeetmeMute(const wxString& Meetme,
                                     const wxString& Usernum,
                                     wxString ActionID = _(""));
        amiActionID ActionMeetmeUnmute(const wxString& Meetme,
                                       const wxString& Usernum,
                                       wxString ActionID = _(""));
        amiActionID ActionMonitor(const wxString& Channel,
                                  const wxString& File="",
                                  const wxString& Format="",
                                  const wxString& Mix="",
                                  wxString ActionID = _(""));
        amiActionID ActionOriginate(const wxString& Channel,
                                    const wxString& Exten,
                                    const wxString& Context,
                                    const wxString& Priority,
                                    const wxString& Application="",
                                    const wxString& Data="",
                                    const wxString& Timeout="",
                                    const wxString& CallerID="",
                                    const wxString& Variable="",
                                    const wxString& Account="",
                                    const wxString& Async="",
                                    wxString ActionID = _(""));
        amiActionID ActionPark(const wxString& Channel,
                               const wxString& Channel2,
                               const wxString& Timeout="",
                               wxString ActionID = _(""));
        amiActionID ActionParkedCalls(wxString ActionID = _(""));
        amiActionID ActionPauseMonitor(const wxString& Channel,
                                       wxString ActionID = _(""));
        amiActionID ActionPlayDTMF(const wxString& Channel,
                                   const wxString& Digit,
                                   wxString ActionID = _(""));
        amiActionID ActionQueueAdd(const wxString& Queue,
                                   const wxString& Interface,
                                   const wxString& Penalty="",
                                   const wxString& Pause="",
                                   wxString ActionID = _(""));
        amiActionID ActionQueuePause(const wxString& Queue,
                                     const wxString& Interface,
                                     const wxString& Paused="",
                                     wxString ActionID = _(""));
        amiActionID ActionQueueRemove(const wxString& Queue,
                                      const wxString& Interface,
                                      wxString ActionID = _(""));
        amiActionID ActionQueues(wxString ActionID = _(""));
        amiActionID ActionQueueStatus(wxString ActionID = _(""));
        amiActionID ActionRedirect(const wxString& Channel,
                                   const wxString& Exten,
                                   const wxString& Context,
                                   const wxString& Priority,
                                   const wxString& ExtraChannel="",
                                   wxString ActionID = _(""));
        amiActionID ActionSetCDRUserField(const wxString& UserField,
                                          const wxString& Channel,
                                          const wxString& Append,
                                          wxString ActionID = _(""));
        amiActionID ActionSetVar(const wxString& Channel,
                                 const wxString& Variable,
                                 const wxString& Value,
                                 wxString ActionID = _(""));
        amiActionID ActionSIPpeers(wxString ActionID = _(""));
        amiActionID ActionSIPshowpeer(const wxString& Peer,
                                      wxString ActionID = _(""));
        amiActionID ActionStatus(const wxString& Channel,
                                 wxString ActionID = _(""));
        amiActionID ActionStopMonitor(const wxString& Channel,
                                      wxString ActionID = _(""));
        amiActionID ActionUnpauseMonitor(const wxString& Channel,
                                         wxString ActionID = _(""));
        amiActionID ActionUpdateConfig(const wxString& SrcFilename,
                                       const wxString& DstFilename,
                                       const wxString& Reload,
                                       const wxString& Action_XXXXXX,
                                       const wxString& Cat_XXXXXX,
                                       const wxString& Value_XXXXXX,
                                       const wxString& Match_XXXXXX,
                                       wxString ActionID = _(""));
        amiActionID ActionUserEvent(const wxString& UserEvent,
                                    const wxArrayString& Headers,
                                    wxString ActionID = _(""));
        amiActionID ActionWaitEvent(const wxString& Timeout,
                                    wxString ActionID = _(""));
        amiActionID ActionZapDialOffhook(const wxString& ZapChannel,
                                         const wxString& Number,
                                         wxString ActionID = _(""));
        amiActionID ActionZapDNDoff(const wxString& ZapChannel,
                                    wxString ActionID = _(""));
        amiActionID ActionZapDNDon(const wxString& ZapChannel,
                                   wxString ActionID = _(""));
        amiActionID ActionZapHangup(const wxString& ZapChannel,
                                    wxString ActionID = _(""));
        amiActionID ActionZapRestart(wxString ActionID = _(""));
        amiActionID ActionZapShowChannels(wxString ActionID = _(""));
        amiActionID ActionZapTransfer(const wxString& ZapChannel,
                                      wxString ActionID = _(""));

        //사용자가 직접 변수(값)을 지정하여 액션수행
        amiActionID DoAction(ActionVariableMap& actionVariableMap);
};

#endif // XAMI_ACTION_H_INCLUDED
