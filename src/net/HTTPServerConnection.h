// HTTPServerConnection.h: interface for the HTTPServerConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPSERVERCONNECTION_H__E192E3C3_B74B_4116_B443_2A8E568BA5EF__INCLUDED_)
#define AFX_HTTPSERVERCONNECTION_H__E192E3C3_B74B_4116_B443_2A8E568BA5EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/**
Provides the classes for implementing networking applications. 
*/
namespace net
{

class HTTPServerConnection;

/// Size of the data packets send to the socket.
const long PACKET_LENGTH = 5 * 1024; // bytes

/**
Query from a http client
*/
class HTTPRequest
{
public:
	/// GET or POST
	std::string method;
	/// Url of the query
	std::string url;
	/// http headers
	util::Properties headers;
	/// http session data
	util::Properties sessionData;
	/// Content of the message.
	io::Blob<char> body;

	/**
		Calling parameters of the query.
		Example: http://www.server.com/service?param1=45&param2=hola. Return two properties: param1 and param2.
		Return GET parameters and POST parameters.
		@return The calling parameters values.
	*/
	util::Properties getParameters() const;

	/**
		@return The url without the final params (everything after the character '?' is removed.
	*/
	std::string partialUrl() const;

private:
	/// Session properties
	HTTPServerConnection* connection;


};


/**
	HTTP server.
*/
class HTTPServerConnection
{
public:
	HTTPServerConnection(io::IInputStream* input, io::IOutputStream* output, bool sessions = false);
	virtual ~HTTPServerConnection();

	/**
		This class reads the input stream for a client query.
		Waits till a query reach this server.
	*/
	std::auto_ptr<HTTPRequest> getQuery();

	/**
		Send the response to the output stream.
	*/
	void sendResponse(std::auto_ptr<HTTPResponse> response);

private:
	io::IInputStream* m_input;
	io::IOutputStream* m_output;

	bool m_useSessions;
	util::Properties m_sessionData;



};

/**
	HTTPRequest automatic pointer.
*/
typedef std::auto_ptr<HTTPRequest> HTTPRequestPtr;
} // namespace net

} // namespace stream

#endif // !defined(AFX_HTTPSERVERCONNECTION_H__E192E3C3_B74B_4116_B443_2A8E568BA5EF__INCLUDED_)
