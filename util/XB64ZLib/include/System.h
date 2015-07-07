// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_System_H__B41CD4F8_BD66_4429_9188_88F61FB5D361__INCLUDED_)
#define AFX_System_H__B41CD4F8_BD66_4429_9188_88F61FB5D361__INCLUDED_

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
	System information static class
*/
class System  
{
public:
	System();
	virtual ~System();

	/**
		@return The name, version, type and service pack number of the operating system.
	*/
	static std::string getOperatingSystemId();

	/**
		@return The user agent of the Internet Explorer installed.
	*/
	static std::string getIEAgent();

	/**
		@return The computer name.
	*/
	static std::string getComputerName();

	/**
		Load a dll or exe file and read the version information of it.
		@return The file version info. Digits are separated with dots ("1.1.0.43")
	*/
	static std::string getFileVersion(const std::string& path);

	/** 
		Get the temporal path of the system.
		@return The temp path.
	*/
	static std::string getTempPath();

	/**
		@return The complete path of the currente executable module
	*/
	static std::string getExecutablePath();

	/**
		Reads a string value form the registry.
		@param path Path of the key name to the value to read. Example "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\IEXPLORE.EXE"
		@return The value string.
	*/
	static std::string readRegistryString(const std::string& path);

	/**
		@return The version of the Internet Explorer installed.
	*/
	static std::string getIEVersion();

	/**
		This method opens the system default application that is registered to execute de command.
		Examples: If as command sets "http://www.microsoft.com", the Internet Explorer will be opened to show tah web page.
		If as command sets a path to a file, the default associated application will be launch
		@param command Commnad to open. It can be file path, url's and every thing that could be executed in the Windows Explorer "Start->Run" option.
	*/
	static void openShell(const std::string& command);

	/**
		Current procces Id.
		@return the current process Id.
	*/
	static long getProcessId();

	/**
		Show a message box with an alert icon.
		@param message Text to show.
	*/
	static void alert(const std::string& message);

	/**
		Ask a question.
		@param message Text to show.
		@retrun true if the user press the 'OK' button.
	*/
	static bool question(const std::string& message);

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_System_H__B41CD4F8_BD66_4429_9188_88F61FB5D361__INCLUDED_)
