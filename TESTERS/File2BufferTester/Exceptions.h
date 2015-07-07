#ifndef __STREAMS_EXCEPTIONS_H
#define __STREAMS_EXCEPTIONS_H


namespace Stream
{
/**
	Group of exception classes used by the Stream classes
*/
namespace Exceptions
{

/**
	Base class of the Stream exceptions
*/
class StreamException : public exception
{
public:
	
	StreamException(int id_code,std::string desc = "");
	virtual ~StreamException(){}
	std::string GetDesc(){ return m_desc;}
	int GetIdError(){ return m_err_code;}

	

protected:
	StreamException()
	{
		m_err_code = 0;
		m_desc = "";
	}

	int m_err_code;
	std::string m_desc;
};



class LogLine : public StreamException
{
public:
	
	LogLine(int id_code,std::string desc = "",std::string file = "",std::string line = ""):StreamException(id_code,desc.c_str()),m_line(line),m_file(file)
	{
		
	}

	std::string GetLocation()
	{
		std::string buf = "";
		buf += m_file;
		buf += ":";
		buf += m_line;

		return buf;
	}

protected:	

	std::string m_file;
	std::string m_line;
};
#define STREAM_TRACE(X,Y) throw LogLine(X,Y,__FILE__,__LINE__);




class Win32ErrorException : public StreamException
{
public:
	Win32ErrorException(const std::string& file,long line);
	virtual ~Win32ErrorException();

	virtual const char* what() const;

private:
	std::string m_message;
	long m_idError;
	std::string m_file;
	long m_line;

	std::string m_finalMessage;
};

} // namespace Exceptions
} // namespace Stream

#endif __STREAMS_EXCEPTIONS_H