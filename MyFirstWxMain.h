/***************************************************************
 * Name:      MyFirstWxMain.h
 * Purpose:   Defines Application Frame
 * Author:    Xeny Maeng (wifnavor@gmail.com)
 * Created:   2009-02-19
 * Copyright: Xeny Maeng (www.fineapplications.com)
 * License:
 **************************************************************/

#ifndef MYFIRSTWXMAIN_H
#define MYFIRSTWXMAIN_H

#include "MyFirstWxApp.h"
#include "GUIFrame.h"
#include <wx/wxsqlite3.h>
#include <wx/taskbar.h>

class CallPopupDlgImpl;
class SetupVars;

WX_DECLARE_STRING_HASH_MAP(wxString, SetupVariableMap);

class MyFirstWxFrame: public GUIFrame
{
    friend class MyTaskBarIcon;
    ///
    /// Member Variables
    ///
    private:
        amiSessionPtr m_sessionPtr;
        wxSQLite3Database* m_dbPtr;
        SetupVars* m_setupVarsPtr;

        bool m_isLoggedIn; // 세션성공?
        bool m_isLinked;

        wxChar m_currDirection;

        wxString m_myExten; // SIP 계정(내선번호)
        wxString m_myRecForm;
        wxString m_currRecFile;

        wxString m_callerId;
        wxString m_callerName;
        wxString m_calledId;
        wxString m_calledName;

        wxString m_myChannel;
        wxString m_sourceChannel;
        wxString m_destChannel;

        wxDateTime m_callStartTime;
        wxDateTime m_callEndTime;

        /// 각 액션별 ID 변수 선언
        wxString m_loginActionId; // Login
        wxString m_sipShowPeerActionId; // SipShowPeer
        wxString m_monitorActionId;
        wxString m_stopMonitorActionId;
        wxString m_redirectActionId;

        /// SIP Peer 정보 맵
        ActionResponseMap m_mySipMap;

        /// 환경변수 맵
        //SetupVarMap m_setupVarMap;

        /// TaskBarIcon 변수
        wxTaskBarIcon* m_taskBarIconPtr;

    public:
        /// Call 팝업 Modeless Dialog
        CallPopupDlgImpl *m_popupDlgPtr;

    ///
    /// Member Functions
    ///
    public:
        MyFirstWxFrame(wxFrame *frame);
        ~MyFirstWxFrame();

        void InitMainToolbar();
        void InitActionToolbar();
        void InitActionProperty();

    protected:
        /// AMI Session Handler
        virtual void OnSessionCreated(amiSessionPtr ptr);
        virtual void OnCreateSessionFailed(amiSessionPtr ptr);
        virtual void OnSessionDestroyed(amiSessionPtr ptr);

        /// AMI Event Handlers
        virtual void OnActionLog(wxString& str);
        virtual void OnEventLog(wxString& str);
        virtual void OnActionResponse(AmiActionResponse& r);
        virtual void OnAmiEvent(AmiEventInfo& e);

    private:
        virtual void OnIconize( wxIconizeEvent& event );
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);

        virtual void OnToolClicked_DoAction(wxCommandEvent& event);
        virtual void OnToolClicked_CreateSession(wxCommandEvent& event);
        virtual void OnToolClicked_DestroySession( wxCommandEvent& event );
        virtual void OnToolClicked_Setup( wxCommandEvent& event );
		virtual void OnToolClicked_MakeCall( wxCommandEvent& event );
		virtual void OnToolClicked_Hangup( wxCommandEvent& event );
		virtual void OnToolClicked_Transfer( wxCommandEvent& event );
		virtual void OnToolClicked_RecStart( wxCommandEvent& event );
		virtual void OnToolClicked_RecStop( wxCommandEvent& event );

		virtual void OnTreeSelChanged_ActionList( wxTreeEvent& event );
};

///
/// AMI action item data for wxTreeCtrl
///
class AmiActionItemData : public wxTreeItemData
{
    public:
        AmiActionItemData() {}
        virtual ~AmiActionItemData() {}

        const wxUint8& GetId() { return m_id; }
        const wxString& GetAction() { return m_action; }
        const wxString& GetPrivilege() { return m_privilege; }
        const wxString& GetSynopsis() { return m_synopsis; }
        const wxString& GetDescription() { return m_description; }
        const ActionVariableMap& GetActionVariableMap() { return m_actionVariableMap; }

    public:
        void SetId(wxUint8 id) { m_id = id; }
        void SetAction(wxString action) { m_action = action; }
        void SetPrivilege(wxString privilege) { m_privilege = privilege; }
        void SetSynopsis(wxString synopsis) { m_synopsis = synopsis; }
        void SetDescription(wxString description) { m_description = description; }

    private:
        //Action command specificatoin
        wxUint8 m_id;
        wxString m_action;
        wxString m_privilege;
        wxString m_synopsis;
        wxString m_description;

        //Action variable list(using wxHashMap)
        ActionVariableMap m_actionVariableMap;
};

class SetupVars
{
    private:
        wxSQLite3Database* m_dbPtr;
        wxString m_tableStr;
        wxString m_groupColStr;
        wxString m_variableColStr;
        wxString m_valueColStr;

    public:
        SetupVars(wxSQLite3Database* dbPtr,
                  const wxString& tableStr = _("SETUP_VARS"),
                  const wxString& groupColStr = _("GROUP"),
                  const wxString& variableColStr = ("VARIABLE"),
                  const wxString& valueColStr = _("VALUE"))
                  : m_dbPtr(dbPtr),
                  m_tableStr(tableStr),
                  m_groupColStr(groupColStr),
                  m_variableColStr(variableColStr),
                  m_valueColStr(valueColStr) {}

        template <typename T>
        void GetVars(T& varMap,
                     const wxString& groupStr = _(""),
                     bool clear = false);

        wxString GetVar(const wxString& varStr,
                        const wxString& groupStr = _(""));

        template <typename T>
        wxUint8 SetVars(T& varMap);

        wxUint8 SetVar(const wxString& varStr,
                       const wxString& valueStr = _(""));
};

class MyTaskBarIcon: public wxTaskBarIcon
{
    private:
        wxWindow* m_wndPtr;

    public:
        MyTaskBarIcon(wxWindow* ptr) : m_wndPtr(ptr) {}

        void OnLeftButtonDClick(wxTaskBarIconEvent&);
        void OnMenuRestore(wxCommandEvent&);
        void OnMenuExit(wxCommandEvent&);
        void OnMenuMakeCall(wxCommandEvent&);
        void OnMenuHangup(wxCommandEvent&);
        void OnMenuRecStart(wxCommandEvent&);
        void OnMenuRecStop(wxCommandEvent&);
        virtual wxMenu *CreatePopupMenu();

    DECLARE_EVENT_TABLE()
};

#endif // MYFIRSTWXMAIN_H
