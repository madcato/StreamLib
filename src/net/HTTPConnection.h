// HTTPConnection.h: interface for the HTTPConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPCONNECTION_H__94C9FCF5_F7D7_466B_B794_0C2FCEA78BF4__INCLUDED_)
#define AFX_HTTPCONNECTION_H__94C9FCF5_F7D7_466B_B794_0C2FCEA78BF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
	/// namespace exceptions
	namespace exceptions
	{
	class HTTPException : public StreamException
	{
	public:
		HTTPException(long result, const std::string& message):StreamException(result,message){}
		virtual ~HTTPException()
		{
			
		}
	};
	} // namespace exceptions

/**
Provides the classes for implementing networking applications. 
*/
namespace net
{

extern const ulong HTTP_STATUS_FILE_NOT_FOUND;
extern const ulong HTTP_STATUS_OK;
extern const ulong HTTP_STATUS_RANGE_NOT_SATISFIABLE;
extern const ulong HTTP_STATUS_INTERNAL_SERVER_ERROR;



/**
	Response from a HTTP server.
*/
class HTTPResponse
{

public:
	/// Status of the query.
	unsigned long status;
	/// Message from server.
	std::string serverMsg;
	/// http headers.
	util::Properties headers;
	/// http session data
	util::Properties sessionData;
	/// Content of the message.
	std::auto_ptr<io::IData> body;
	/// Unscapes url format. IE: "Hola%20Mundo" transforms to "Hola Mundo".
	static std::string unscape(const std::string& str);

	void setBody(const std::string& data)
	{
		util::ref_count_ptr<io::Blob<char> > blob(new io::Blob<char>);
		blob->setData(data);
		this->body = std::auto_ptr<io::IData>((io::IData*)(new io::BLOBData<char>(blob)));	
	}
};

/**
	This class provides two methods to communicate with an HTTP server. This methods are GET and POST.
*/
class HTTPConnection  
{
public:
	HTTPConnection(io::IInputStream* input, io::IOutputStream* output);
	virtual ~HTTPConnection();

	std::auto_ptr<HTTPResponse> doGet(std::string url,util::Properties& headers);
	std::auto_ptr<HTTPResponse> doPost(std::string url,util::Properties& headers,const io::Blob<char>& body);

private:
	io::IInputStream* m_input;
	io::IOutputStream* m_output;

	std::auto_ptr<HTTPResponse> getResponse();
	void sendHeaders(util::Properties headers);

	void constructPacket(std::string& packet,util::Properties& headers);
};

/**
	HTTPResponse automatic pointer.
*/
typedef std::auto_ptr<HTTPResponse> HTTPResponsePtr;

} // namespace net

} // namespace stream

#endif // !defined(AFX_HTTPCONNECTION_H__94C9FCF5_F7D7_466B_B794_0C2FCEA78BF4__INCLUDED_)
