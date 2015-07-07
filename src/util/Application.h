// Application.h: interface for the Application class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATION_H__31FE77DC_7EC4_40F6_8F81_1C8DAA0522CA__INCLUDED_)
#define AFX_APPLICATION_H__31FE77DC_7EC4_40F6_8F81_1C8DAA0522CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

/**
	Application related utilities.
*/
class Application  
{
public:
	Application();
	virtual ~Application();

	/**
		This method take the following actions:<br>
		- Load the resource form the current module. (see <a href="http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winui/winui/windowsuserinterface/resources/introductiontoresources/resourcereference/resourcefunctions/loadresource.asp">LoadResource</a>)<br>
			This resource must be a tar.gz file included in the resources of the project as RT_RCDATA (see <a href="http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winui/winui/windowsuserinterface/resources/introductiontoresources/resourcereference/resourcetypes.asp">Resource Types</a>)<br>
		- Uncompress the tar.gz file in the resourcePath.<br>

		<i>* The resource data file must be included in te project. You must set a 'Custom Build' for this resource file as:<br> 
		in 'Command'...<br>
		<code>
				zip -c -Y .\&lt;resource_input_directory&gt; <br>
				copy /Y &lt;resource_input_directory&gt;.tar.gz &lt;resource_data_file&gt; <br>
				del &lt;resource_input_directory&gt;.tar.gz <br>
		</code><br>
		... and in 'Outputs' set the name of the resource file data.</i>
		@param idResource Identificator of the resource.
		@param resourcePath Output path to copy the content of the resource.
	*/
	static void prepareResources(int idResource,const std::string& resourcePath);

	/**
		Initialize the log in the user temporary path.
		@param logFileName Name of the file log to create
	*/
	static void initTempLog(const std::string& logFileName = std::string("stream.log"),const std::string& module = std::string("stream"),int logLevel = LOG_ALL);

	/**
		Initialize the log.
		@param logFileName Name of the file log to create
	*/
	static void initLog(const std::string& logPath,const std::string& module,int logLevel);

	static void init();

	/**
		Initializes an application with a control socket to receive commands via telnet.
		@param listenPort Listen port.
		@param commandParser Object to receive the commands. Must implement the DynamicClass interface.
		@param listenIP Optional. Bind IP.
	*/
	static void initSocketService(const std::string& listenPort, ref_count_ptr<DynamicClass> commandParser, const std::string& listenIP = "");


private:
	class SocketThread : public sync::Thread
	{
	public:
		std::string m_listenPort;
		std::string m_listenIP;
		void run();
		
	
		net::SocketPtr m_socket;
		
	};
	class CommandThread : public sync::Thread
	{
	public:
		CommandThread(SocketThread* parent):m_parent(parent){}
		void run();
		
	private:
		SocketThread* m_parent;
		
	};

	static SocketThread m_appSocketThread;

	
	/*Service

Propiedades:
- DateStart. Fecha en la que empieza a ejecutarse. NULL si no importa
- DateEnd. Fecha en la que finaliza de ejecutarse. NULL si no importa
- HourStart. Hora en la que empieza a ejecutarse. NULL si no importa
- HourEnd. Hora en la que finaliza de ejecutarse. NULL si no importa
- RepeatN. Número de iteraciones que se ejecutarán. Por defecto sólo una.
- Interval. Número de segundos entre inicios de iteración. Por defecto 0 o NULL, significa que en cuanto finalice una iteración empieza la siguiente.


Si la iteración está en curso cuando llega la hora/dia de finalización, se permite la finalización de la misma sin forzar una parada.
*/
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_APPLICATION_H__31FE77DC_7EC4_40F6_8F81_1C8DAA0522CA__INCLUDED_)
