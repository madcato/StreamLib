#ifndef __STREAMS_EXCEPTIONS_H
#define __STREAMS_EXCEPTIONS_H

/// namespace stream
namespace stream
{
/**
	Group of exception classes used by the stream classes
*/
namespace exceptions
{

/**
	Base class of the stream exceptions
*/
class StreamException : public std::exception
{
public:
	
	StreamException(int id_code,std::string desc = "");
	virtual ~StreamException(){}
	/**
		@return The description string.
	*/
	std::string GetDesc(){ return m_desc;}
	/**
		@return The error identificator.
	*/
	int GetIdError(){ return m_err_code;}
	/**
		@return The description string.
	*/
	virtual const char* what() const;
	

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
#define STREAM_TRACE(X,Y) throw new LogLine(X,Y,__FILE__,__LINE__);



/**
	This class checks for the GetLastError() Win32 function to retrive the error code produced.
	After this gets the error description from the system.
*/
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


#define BEGIN_TRY_CATCH() try {
#define END_TRY_CATCH() 	}catch(exceptions::StreamException* e){csout << e->what() << endln;}

} // namespace exceptions
} // namespace stream

#endif __STREAMS_EXCEPTIONS_H