// WebApp.cpp: implementation of the WebApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "Exceptions.h"
#include "PropertyBag.h"
#include "Properties.h"
#include "PersistentProperties.h"
#include "Thread.h"
#include "Socket.h"
#include "FileInputStream.h"
#include "ServerSocket.h"
#include "memory_stream.h"
#include "blob.h"
#include "IData.h"
#include "BLOBInputStream.h"
#include "BLOBOutputStream.h"
#include "BLOBData.h"
#include "HTTPConnection.h"
#include "HTTPServerConnection.h"
#include "HTMLTPage.h"
#include "HTTPControllerManager.h"
#include "ILog.h"
#include "LiteLog.h"
#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"
#include "CW3CLog.h"
#include "CriticalSection.h"
#include "Log.h"
#include "ClassFactory.h"

#include "WebApp.h"

#include "System.h"
#include "FileUtil.h"
#include "Thread.h"
#include "NetCommandServer.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace net
{


std::auto_ptr<HTTPControllerManager> WebApp::m_manager;
std::auto_ptr<FileAccessController> WebApp::m_fac;

class Control : public sync::Thread
{
public:
	Control(const std::string& listen_port,WebApp* app):m_listenPort(listen_port),m_app(app)
	{
	}

	void run()
	{
		NetCommandServer controlServer(m_listenPort,"localhost");
		
		bool salir = false;
		util::LiteLog* log = util::LiteLog::getInstance();
		log->trace(util::LOG_TRACE,"Control::run() start");
		do
		{
			std::string command = controlServer.waitForCommand();
			
			log->trace(util::LOG_INFO,"Control command: " + command);
			
			if(command == "SHUTDOWN")
			{
				salir = true;
				m_app->stop();
			}
			if(command == "RESTART")
			{
				salir = true;
				m_app->restart();				
			}
			if(command == "NOOP")
			{				
			}
		}while(!salir);

		log->trace(util::LOG_TRACE,"Control::run() end");
	}

private:
	std::string m_listenPort;
	WebApp* m_app;
};

WebApp::WebApp()
{
	
}

WebApp::~WebApp()
{

}




void WebApp::run()
{
do
{
	m_restart = false;
	try
	{
		m_run = true;
		configure();

		Control control(m_properties.getProperty("control_port"),this);

		control.start();

		util::LiteLog* log = util::LiteLog::getInstance();
		log->trace(util::LOG_TRACE,"WebApp::run() start");


		log->trace(util::LOG_INFO,"Process Id: " + util::sstring(util::System::getProcessId()));

		
		m_server = ServerSocketPtr(new ServerSocket(m_properties.getProperty("server_port"),m_properties.getProperty("server_ip")));

		do
		{
			SocketPtr socket(m_server->accept());

			WebSession* ws = new WebSession(socket);

			ws->start();

		}while(m_run);
	}catch(exceptions::StreamException* e)
	{
		util::LiteLog::getInstance()->trace(util::LOG_ERROR,e->what());
	}
}
while(m_restart);

	util::LiteLog::getInstance()->trace(util::LOG_TRACE,"WebApp::run() end");
}

void WebApp::stop()
{
	m_run = false;
	m_server->close();
}

void WebApp::restart()
{
	m_restart = true;
	m_server->close();	
}

void WebApp::configure()
{
	m_run = true;
	try
	{
		m_properties.load(std::auto_ptr<io::IInputStream>(new io::FileInputStream(".\\conf\\webapp.conf")));
	}catch(...)
	{
		util::System::alert("Inaccesible file: .\\conf\\webapp.conf");
		exit(-1);
	}

	std::string logFile = m_properties.getProperty("log_file");
	std::string errorFile = m_properties.getProperty("error_file");

	util::LiteLog* log = util::LiteLog::getInstance();
	if(errorFile != "")
	{		
		log->traceOn(errorFile,"WebApp",util::LiteLog::stringToId(m_properties.getProperty("error_level")),util::CONTINUE_LOG);
	}

	util::W3CLog* wlog = util::W3CLog::getInstance();
	if(logFile != "")
	{
		std::auto_ptr<util::ILog> l = std::auto_ptr<util::ILog>(new util::Log);
		l->traceOn(logFile,util::CONTINUE_LOG);

		wlog->traceOn(l,"WebApp",m_properties.getProperty("log_format"));
	}

	m_fac = std::auto_ptr<FileAccessController>(new FileAccessController(m_properties.getProperty("base_path")));
	
	m_manager = std::auto_ptr<HTTPControllerManager>(new HTTPControllerManager(m_fac.get()));	

	configureControllers();

	log->trace(util::LOG_TRACE,"WebApp::configure() End");
}

void WebApp::configureControllers()
{
	util::LiteLog* log = util::LiteLog::getInstance();
	log->trace(util::LOG_TRACE,"WebApp::configureControllers() start");

	util::PersistentProperties properties;

	std::string controllersFile = m_properties.getProperty("controller_conf_file");

	if(controllersFile == "")
	{
		log->trace(util::LOG_WARNING,"No controller configuration file is especified in the main conf file.");
		return;
	}

	properties.load(std::auto_ptr<io::IInputStream>(new io::FileInputStream(controllersFile)));

	std::vector<std::string> vec = properties.propertyNames();

	std::vector<std::string>::iterator it;
	
	for(it = vec.begin() ; it != vec.end() ; it++)
	{
		
		try
		{
			std::auto_ptr<IHTTPController> con = std::auto_ptr<IHTTPController>((IHTTPController*)util::ClassFactory::createObject(*it));
		
			std::string url = properties.getProperty(*it);

			con->setUrl(url);
			std::string basePath = m_properties.getProperty("include_path");
			util::FileUtil::PutFinalSlashInPath(basePath);
			con->setBasePath(basePath);

			log->trace(util::LOG_INFO,"AddController: " + *it + " " + url);

			m_manager->addController(con);
		}catch(exceptions::ClassFactoryException* e)
		{
			log->trace(util::LOG_ERROR,e->what());
		}
	}

	log->trace(util::LOG_TRACE,"WebApp::configureControllers() end");
}

void WebSession::run()
{
	util::LiteLog* log = util::LiteLog::getInstance();
	log->trace(util::LOG_TRACE,"WebSession::run() start");

	HTTPServerConnection serverConnection(m_socket->getInputStream(),m_socket->getOutputStream(),true);

	try
	{
		do
		{

			log->trace(util::LOG_TRACE,"start waiting for request");
			util::Properties prop;

			prop.setProperty("c-ip",m_socket->getInetAddress());

			HTTPRequestPtr request = serverConnection.getQuery();
			prop.setProperty("cs-uri",request->url);
			prop.setProperty("cs-mehtod",request->method);
			prop.setProperty("cs-bodylength",util::sstring(request->body.length()));

			log->trace(util::LOG_TRACE,"request received");
			HTTPResponsePtr response = WebApp::m_manager->executeQuery(request);
			prop.setProperty("x-status",util::sstring(response->status));
			prop.setProperty("sc-serverMsg-s",response->serverMsg);
			
			log->trace(util::LOG_TRACE,"request finished");
			serverConnection.sendResponse(response);
			log->trace(util::LOG_TRACE,"response send");

			util::W3CLog::getInstance()->trace(prop);
		}while(true);
	}catch(exceptions::StreamException* e)
	{
		log->trace(util::LOG_ERROR,e->what());
	}	

}

} // namespace net

} // namespace stream
