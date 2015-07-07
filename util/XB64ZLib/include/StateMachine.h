// StateMachine.h: interface for the StateMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATEMACHINE_H__0C5117E6_39E4_41FD_B95B_3CA34262754D__INCLUDED_)
#define AFX_STATEMACHINE_H__0C5117E6_39E4_41FD_B95B_3CA34262754D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

	/// namespace exceptions
	namespace exceptions
	{

		/**
		util exception.
		*/
		class StateMachineException : public StreamException
		{
		public:
			StateMachineException(int id_code,std::string desc = ""):StreamException(id_code,desc)
			{
			}
		};
	} // namespace exceptions

/// namespace util
namespace util
{

class StateMachine  
{
public:
	StateMachine(std::auto_ptr<io::IInputStream> configurationStream);
	virtual ~StateMachine();

	void event(const std::string& eventStr);

protected:
	virtual void doNotification() = 0;
	virtual void doTran(const std::string&) = 0;
	virtual void doEvent(const std::string&) = 0;
	virtual void doError(const std::string& currentState, const std::string& lastEvent) = 0;
	std::string m_currentState;
private:
	

	std::map<std::string,std::string> m_mapaTransiciones; // <state+event,nextState>
};

#define DECLARE_NOTIFY_MAP() void doNotification(){

#define END_NOTIFY_MAP() }

#define NOTIFY(x,y) if(m_currentState == ##x){y();return;}

#define DECLARE_TRAN_MAP() void doTran(const std::string& stateEvent){

#define END_TRAN_MAP() }

#define TRAN(x,y) if(stateEvent == ##x){y();return;}

#define DECLARE_EVENT_MAP() void doEvent(const std::string& event){

#define END_EVENT_MAP() }

#define EVENT(x,y) if(event == ##x){y();return;}

} // namespace util

} // namespace stream

#endif // !defined(AFX_STATEMACHINE_H__0C5117E6_39E4_41FD_B95B_3CA34262754D__INCLUDED_)
