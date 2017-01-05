#ifndef XAMI_EVENT_H_INCLUDED
#define XAMI_EVENT_H_INCLUDED

///
/// AMI Event Classes
///

class AmiSession;

// 하나의 이벤트에 대한 맵
WX_DECLARE_STRING_HASH_MAP(wxString, AmiEventMap);

/// 이벤트에 대한 공통정보
class AmiEventInfo
{
    private:
        wxString m_plaintext;
        AmiSession* m_sessionPtr;
        AmiEventMap m_eventMap;
        void* m_item;

    public:
        AmiEventInfo() {}
        ~AmiEventInfo() {}

        void* Item() { return m_item; }

        AmiEventMap& GetEventMap() { return m_eventMap; }
        wxString& GetPlaintext() { return m_plaintext; }

        void SetEventItems (void* ptr) { m_item = ptr; }
        void SetPlaintext(const wxString& str) { m_plaintext = str; }
        void SetSessionPtr(AmiSession* ptr) { m_sessionPtr = ptr; }
};

class AmiEvent
{
    public:
        AmiEvent() {}
        virtual ~AmiEvent() {}

    protected:
        /// Log Event
        virtual void OnActionLog(wxString& str) {}
        virtual void OnEventLog(wxString& str) {}

        /// Action Response Event
        virtual void OnActionResponse(AmiActionResponse& r) {}

        /// Temporary Event Handler
        virtual void OnAmiEvent(AmiEventInfo& e) {}

        /// Agent Status Events
        virtual void OnAgentCallbackLogin(AmiEventInfo& e) {}
        virtual void OnAgentCallbackLogoff(AmiEventInfo& e) {}
        virtual void OnAgentCalled(AmiEventInfo& e) {}
        virtual void OnAgentComplete(AmiEventInfo& e) {}
        virtual void OnAgentConnect(AmiEventInfo& e) {}
        virtual void OnAgentDump(AmiEventInfo& e) {}
        virtual void OnAgentLogin(AmiEventInfo& e) {}
        virtual void OnAgentLogoff(AmiEventInfo& e) {}
        virtual void OnQueueMemberPaused(AmiEventInfo& e) {}
        virtual void OnQueueMemberStatus(AmiEventInfo& e) {}

        /// CommandS Status Events
        // <none>

        /// Call Status Events
        virtual void OnCdr(AmiEventInfo& e) {}
        virtual void OnDial(AmiEventInfo& e) {}
        virtual void OnExtensionStatus(AmiEventInfo& e) {}
        virtual void OnHangup(AmiEventInfo& e) {}
        virtual void OnMusicOnHold(AmiEventInfo& e) {}
        virtual void OnJoin(AmiEventInfo& e) {}
        virtual void OnLeave(AmiEventInfo& e) {}
        virtual void OnLink(AmiEventInfo& e) {}
        virtual void OnMeetmeLeave(AmiEventInfo& e) {}
        virtual void OnMeetmeTalking(AmiEventInfo& e) {}
        virtual void OnMessageWaiting(AmiEventInfo& e) {}
        virtual void OnNewCallerId(AmiEventInfo& e) {}
        virtual void OnNewChannel(AmiEventInfo& e) {}
        virtual void OnNewExten(AmiEventInfo& e) {}
        virtual void OnParkedCall(AmiEventInfo& e) {}
        virtual void OnRename(AmiEventInfo& e) {}
        virtual void OnSetCdrUserField(AmiEventInfo& e) {}
        virtual void OnUnlink(AmiEventInfo& e) {}
        virtual void OnUnParkedCall(AmiEventInfo& e) {}

        /// Log Status Events
        // <none>

        /// System Status Events
        virtual void OnAlarm(AmiEventInfo& e) {}
        virtual void OnAlarmClear(AmiEventInfo& e) {}
        virtual void OnDndState(AmiEventInfo& e) {}
        virtual void OnLogChannel(AmiEventInfo& e) {}
        virtual void OnPeerStatus(AmiEventInfo& e) {}
        virtual void OnRegistry(AmiEventInfo& e) {}
        virtual void OnReload(AmiEventInfo& e) {}
        virtual void OnShutdown(AmiEventInfo& e) {}

        /// User Status Events
        virtual void OnUserEvent(AmiEventInfo& e) {}

        /// Verbose Status Events
        // <none>

        /// Unformatted and Undocumented
        virtual void OnNewState(AmiEventInfo& e) {}
        virtual void OnParkedCallsComplete(AmiEventInfo& e) {}
        virtual void OnQueueParams(AmiEventInfo& e) {}
        virtual void OnQueueMember(AmiEventInfo& e) {}
        virtual void OnQueueStatusEnd(AmiEventInfo& e) {}
        virtual void OnStatusComplete(AmiEventInfo& e) {}
        virtual void OnZapShowChannels(AmiEventInfo& e) {}
        virtual void OnZapShowChannelsComplete(AmiEventInfo& e) {}
};

typedef struct {
    wxString Event;
    wxString Agent;
    wxString Loginchan;
    wxString Uniqueid;
} EVENT_AGENT_CALLBACK_LOGIN;

typedef struct {
    wxString Event;
    wxString Agent;
    wxString Loginchan;
    wxString Logintime;
    wxString Reason;
    wxString Uniqueid;
} EVENT_AGENT_CALLBACK_LOGOFF;

typedef struct {
    wxString Event;
    wxString AgentCalled;
    wxString ChannelCalling;
    wxString CallerID;
    wxString Context;
    wxString Extension;
    wxString Priority;
} EVENT_AGENT_CALLED;

typedef struct {
    wxString Event;
    wxString Queue;
    wxString Uniqueid;
    wxString Channel;
    wxString Member;
    wxString MemberName;
    wxString HoldTime;
    wxString TalkTime;
    wxString Reason;
} EVENT_AGENT_COMPLETE;

typedef struct {
    wxString Event;
    wxString Queue;
    wxString Uniqueid;
    wxString Channel;
    wxString Member;
    wxString MemberName;
    wxString Holdtime;
    wxString BridgedChannel;
} EVENT_AGENT_CONNECT;

typedef struct {
    wxString Event;
    wxString Queue;
    wxString Uniqueid;
    wxString Channel;
    wxString Member;
    wxString MemberName;
} EVENT_AGENT_DUMP;

typedef struct {
    wxString Event;
    wxString Agent;
    wxString Channel;
    wxString Uniqueid;
} EVENT_AGENT_LOGIN;

typedef struct {
    wxString Event;
    wxString Agent;
    wxString Logintime;
    wxString Uniqueid;
} EVENT_AGENT_LOGOFF;

typedef struct {
    wxString Event;
    wxString Location;
    wxString Membership;
    wxString Penalty;
    wxString CallsTaken;
    wxString LastCall;
    wxString Status;
    wxString Paused;
} EVENT_QUEUE_MEMBER_ADDED;

typedef struct {
    wxString Event;
    wxString Location;
    wxString MemberName;
    wxString Paused;
} EVENT_QUEUE_MEMBER_PAUSED;

typedef struct {
    wxString Event;
    wxString Queue;
    wxString Location;
    wxString MemberName;
    wxString Penalty;
    wxString CallsTaken;
    wxString LastCall;
    wxString Status;
    wxString Paused;
} EVENT_QUEUE_MEMBER_STATUS;

typedef struct {
    wxString Event;
    wxString AccountCode;
    wxString Source;
    wxString Destination;
    wxString DestinationContext;
    wxString CallerID;
    wxString Channel;
    wxString DestinationChannel;
    wxString LastApplication;
    wxString LastData;
    wxString StartTime;
    wxString AnswerTime;
    wxString EndTime;
    wxString Duration;
    wxString BillableSeconds;
    wxString Disposition;
    wxString AMAFlags;
    wxString UniqueID;
    wxString UserField;
} EVENT_CDR;

typedef struct {
    wxString Event;
    wxString Privilege;
    wxString Source;
    wxString Destination;
    wxString CallerID;
    wxString CallerIDName;
    wxString SrcUniqueID;
    wxString DestUniqueID;
} EVENT_DIAL;

typedef struct {
    wxString Event;
    wxString Exten;
    wxString Context;
    wxString Status;
} EVENT_EXTENSION_STATUS;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Uniqueid;
    wxString Cause;
} EVENT_HANGUP;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString State;
    wxString Uniqueid;
} EVENT_MUSIC_ON_HOLD;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString CallerID;
    wxString Queue;
    wxString Position;
    wxString Count;
} EVENT_JOIN;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Queue;
    wxString Count;
} EVENT_LEAVE;

typedef struct {
    wxString Event;
    wxString Channel1;
    wxString Channel2;
    wxString Uniqueid1;
    wxString Uniqueid2;
} EVENT_LINK;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Uniqueid;
    wxString Meetme;
    wxString Usernum;
} EVENT_MEETME_JOIN;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Uniqueid;
    wxString Meetme;
    wxString Usernum;
} EVENT_MEETME_LEAVE;

typedef struct {
    wxString Event;
    wxString Privilege;
    wxString Channel;
    wxString Uniqueid;
    wxString Meetme;
    wxString Usernum;
} EVENT_MEETME_STOP_TALKING;

typedef struct {
    wxString Event;
    wxString Privilege;
    wxString Channel;
    wxString Uniqueid;
    wxString Meetme;
    wxString Usernum;
} EVENT_MEETME_TALKING;

typedef struct {
    wxString Event;
    wxString Mailbox;
    wxString Waiting;
    wxString New;
    wxString Old;
} EVENT_MESSAGE_WAITING;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Callerid;
    wxString Uniqueid;
} EVENT_NEW_CALLERID;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString State;
    wxString Callerid;
    wxString Uniqueid;
} EVENT_NEW_CHANNEL;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Context;
    wxString Extension;
    wxString Priority;
    wxString Application;
    wxString AppData;
    wxString Uniqueid;
} EVENT_NEW_EXTEN;

typedef struct {
    wxString Event;
    wxString Exten;
    wxString Channel;
    wxString From;
    wxString Timeout;
    wxString CallerID;
} EVENT_PARKED_CALL;

typedef struct {
    wxString Event;
    wxString Oldname;
    wxString Newname;
    wxString Uniqueid;
} EVENT_RENAME;

typedef struct {
    wxString Event;
} EVENT_SET_CDR_USER_FIELD;

typedef struct {
    wxString Event;
    wxString Channel1;
    wxString Channel2;
    wxString Uniqueid1;
    wxString Uniqueid2;
} EVENT_UNLINK;

typedef struct {
    wxString Event;
} EVENT_UNPARKED_CALL;

typedef struct {
    wxString Event;
    wxString Alarm;
    wxString Channel;
} EVENT_ALARM;

typedef struct {
    wxString Event;
    wxString Channel;
} EVENT_ALARM_CLEAR;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Status;
} EVENT_DND_STATE;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Enabled;
    wxString Reason;
} EVENT_LOG_CHANNEL;

typedef struct {
    wxString Event;
    wxString Peer;
    wxString PeerStatus;
    wxString Cause;
    wxString Time;
} EVENT_PEER_STATUS;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Domain;
    wxString Status;
} EVENT_REGISTRY;

typedef struct {
    wxString Event;
    wxString Message;
} EVENT_RELOAD;

typedef struct {
    wxString Event;
    wxString Shutdown;
    wxString Restart;
} EVENT_SHUTDOWN;

typedef struct {
    wxString Event;
    wxString Channel;
    wxString Uniqueid;
} EVENT_USER_EVENT;
/*
enum {
    UNALLOCATED = 1,
    NO ROUTE TRANSIT NET = 2,
    NO_ROUTE_DESTINATION = 3,
    CHANNEL_UNACCEPTABLE = 6,
    CALL_AWARDED_DELIVERED = 7,
    NORMAL_CLEARING = 16,
    USER_BUSY = 17,
    NO USER RESPONSE = 18,
    NO ANSWER = 19,
    CALL REJECTED = 21,
    NUMBER CHANGED = 22,
    DESTINATION OUT OF ORDER = 27,
    INVALID NUMBER FORMAT = 28,
    FACILITY REJECTED = 29,
    RESPONSE TO STATUS ENQUIRY = 30,
    NORMAL UNSPECIFIED = 31,
    NORMAL CIRCUIT CONGESTION = 34,
    NETWORK OUT OF ORDER = 38,
    NORMAL TEMPORARY FAILURE = 41,
    SWITCH CONGESTION = 42,
    ACCESS INFO DISCARDED = 43,
    REQUESTED CHAN UNAVAIL = 44,
    PRE EMPTED = 45,
    FACILITY NOT SUBSCRIBED = 50,
    OUTGOING CALL BARRED = 52,
    INCOMING CALL BARRED = 54,
    BEARERCAPABILITY NOTAUTH = 57,
    BEARERCAPABILITY NOTAVAIL = 58,
    BEARERCAPABILITY NOTIMPL = 65,
    CHAN NOT IMPLEMENTED = 66,
    FACILITY NOT IMPLEMENTED = 69,
    INVALID CALL REFERENCE = 81,
    INCOMPATIBLE DESTINATION = 88,
    INVALID MSG UNSPECIFIED = 95,
    MANDATORY IE MISSING = 96,
    MESSAGE TYPE NONEXIST = 97,
    WRONG MESSAGE = 98,
    IE NONEXIST = 99,
    INVALID IE CONTENTS = 100,
    WRONG CALL STATE = 101,
    RECOVERY ON TIMER EXPIRE = 102,
    MANDATORY IE LENGTH ERROR = 103,
    PROTOCOL ERROR = 111,
    INTERWORKING = 127,
    NOT DEFINED = 0,
};
*/

#endif // XAMI_EVENT_H_INCLUDED
