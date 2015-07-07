// W3CLog1.h: interface for the W3CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_W3CLOG1_H__12527D8C_886D_4C74_A41F_1F3F738167CD__INCLUDED_)
#define AFX_W3CLOG1_H__12527D8C_886D_4C74_A41F_1F3F738167CD__INCLUDED_

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
	This class generates a log with the W3C format. http://www.w3.org/TR/WD-logfile.html
	<br>This class is a Singleton.
	<p>Example:</p>
<code><br>
&nbsp;// CREATE OUTPUT LOG
&nbsp;std::auto_ptr<ILog> log(new Log());<br>
<br>
&nbsp;log->traceOn("w3ctest.log",CREATE_NEW_LOG);<br>
<br>
<br>
&nbsp;W3CLog* w3c8 = W3CLog::getInstance();<br>
&nbsp;<br>
&nbsp; // INITIALIZE W3C LOG TO OUTPUT ONLY THOSE VARIABLES <br>
&nbsp;w3c8->traceOn(log,"W3CLogTester v1","date time cs-uri x-status x-error");<br>
<br>
&nbsp; // INITIALIZE THE PROPERTIES OBJECT WITH THE VALUES TO OUTPUT<br>
&nbsp;Properties prop;<br>
<br>
&nbsp;prop.setProperty("x-status-s","OK");<br>
&nbsp;prop.setProperty("x-error-s","");<br>
&nbsp;prop.setProperty("cs-uri-s","/Archiving/prueba.html");<br>
&nbsp;prop.setProperty("s-ip","192.168.0.12"); // THIS VALUE WILL NOT BE DUMPED<br>
<br>
&nbsp; // OUTPUTS THE VALUES<br>
&nbsp;w3c8->trace(prop);<br>
<br>
&nbsp;w3c8->traceOff();<br>
</code>
<p>This expample outputs the following log file:</p>
<code>
#Software: W3CLogTester v1<br>
#Version: 1.0<br>
#Date: 10/13/04 10:58:10<br>
#Start-Date: 10/13/04 10:58:10<br>
#Fields: date time cs-uri-s x-status-s x-error-s<br>
10/13/04 10:58:10 "/Archiving/prueba.html" "OK" ""<br>
#End-Date: 10/13/04 10:58:10<br>
</code>
*/
class W3CLog  
{
public:
	W3CLog();
	virtual ~W3CLog();

	/**
		Initialize the W3C log.
		@param log Phisical log for the output. All the traces will be redirected to this object after being formated.
		@param appInfo This string will be output to the line that starts with "#Software:"
		@param format List of the variable names that will be output. If the variable name ends with '-s', this value will be enclosed between "\"" on output.
	*/
	void traceOn(std::auto_ptr<ILog> log,const std::string& appInfo, const std::string& format = "");
	/**
		Outputs a new line.
		@param prop Bag of variables. Only those that were configutared will be output.
	*/
	void trace(const Properties& prop);	
	/**
		Ends the trace. A "#End-Date:" is write. Outputs will not be permited after the call to this method. 
	*/
	void traceOff();

	/**
		Return the instance to this object. Singleton.
	*/
	static W3CLog* getInstance();
	
private:
	std::auto_ptr<ILog> m_log;

	static std::auto_ptr<W3CLog> m_instance;

	std::vector<std::string> m_format;

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_W3CLOG1_H__12527D8C_886D_4C74_A41F_1F3F738167CD__INCLUDED_)
