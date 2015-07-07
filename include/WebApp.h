// WebApp.h: interface for the WebApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBAPP_H__9FF8A349_54E1_4C3A_AD7B_CD388DC93C9E__INCLUDED_)
#define AFX_WEBAPP_H__9FF8A349_54E1_4C3A_AD7B_CD388DC93C9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace net
{

class WebSession;

class WebApp  
{
public:
	WebApp();
	virtual ~WebApp();

	void run();

	void stop();

	void restart();

private:
	void configure();
	void configureControllers();

	util::PersistentProperties m_properties;

	static std::auto_ptr<HTTPControllerManager> m_manager;
	static std::auto_ptr<FileAccessController> m_fac;

	friend class WebSession;

	bool m_run;
	bool m_restart;
	ServerSocketPtr m_server;
};


class WebSession : public sync::Thread
{
public:
	WebSession(SocketPtr socket):m_socket(socket)
	{
	}

	void run();

private:
	SocketPtr m_socket;
};

} // namespace net

} // namespace stream

#endif // !defined(AFX_WEBAPP_H__9FF8A349_54E1_4C3A_AD7B_CD388DC93C9E__INCLUDED_)
