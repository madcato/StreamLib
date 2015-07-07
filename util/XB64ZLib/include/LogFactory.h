// LogFactory.h: interface for the LogFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFACTORY_H__D5FFA6DD_44E1_40DF_9F49_7C810C0C0ABA__INCLUDED_)
#define AFX_LOGFACTORY_H__D5FFA6DD_44E1_40DF_9F49_7C810C0C0ABA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{
/// namespace util
namespace util
{


class LogFactory  
{
public:	
	virtual ~LogFactory();

	//static LogFactory*  getInstance();
	
	static std::auto_ptr<ILogOutput> getLog1(const sstring& logName);

private:
	LogFactory();

	class FileOutput : public ILogOutput
	{
	public:
		void trace(const std::string& logLine);
		void traceOn(const std::string& fileName, const eOpenType& openType);
		void traceOff();

	private:
		HANDLE m_fich;
	};

enum CONSOLE_TEXT_FORMAT
{
 CTF_FOREGROUND_BLUE =     0x0001, // text color contains blue.
 CTF_FOREGROUND_GREEN =    0x0002, // text color contains green.
 CTF_FOREGROUND_RED =      0x0004, // text color contains red.
 CTF_FOREGROUND_INTENSITY = 0x0008, // text color is intensified.
 CTF_BACKGROUND_BLUE =     0x0010, // background color contains blue.
 CTF_BACKGROUND_GREEN =    0x0020, // background color contains green.
 CTF_BACKGROUND_RED =      0x0040, // background color contains red.
 CTF_BACKGROUND_INTENSITY = 0x0080, // background color is intensified.
 CTF_COMMON_LVB_LEADING_BYTE =   0x0100, // Leading Byte of DBCS
 CTF_COMMON_LVB_TRAILING_BYTE =  0x0200, // Trailing Byte of DBCS
 CTF_COMMON_LVB_GRID_HORIZONTAL = 0x0400, // DBCS: Grid attribute: top horizontal.
 CTF_COMMON_LVB_GRID_LVERTICAL = 0x0800, // DBCS: Grid attribute: left vertical.
 CTF_COMMON_LVB_GRID_RVERTICAL = 0x1000, // DBCS: Grid attribute: right vertical.
 CTF_COMMON_LVB_REVERSE_VIDEO =  0x4000, // DBCS: Reverse fore/back ground attribute.
 CTF_COMMON_LVB_UNDERSCORE =     0x8000 // DBCS: Underscore.
};
	class ConsoleOutput : public ILogOutput
	{
	public:
		
		void trace(const std::string& logLine);
		/** 
			Init the output console
			@param fileName Format: CON|Title of the console|Text Format(@see CONSOLE_TEXT_FORMAT)
		*/
		void traceOn(const std::string& fileName, const eOpenType& openType);
		void traceOff();
	};

	class SocketOutput : public ILogOutput
	{
	public:
		void trace(const std::string& logLine);
		void traceOn(const std::string& fileName, const eOpenType& openType);
		void traceOff();
	private:
		std::auto_ptr<net::Socket> m_socket;
		io::IOutputStream* m_output;
	};

	class VoidOutput : public ILogOutput
	{
	public:
		void trace(const std::string& logLine);
		void traceOn(const std::string& fileName, const eOpenType& openType);
		void traceOff();
	};
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_LOGFACTORY_H__D5FFA6DD_44E1_40DF_9F49_7C810C0C0ABA__INCLUDED_)
