// HTTPServerConnection.cpp: implementation of the HTTPServerConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "IInputStream.h"
#include "IOutputStream.h"
#include "PropertyBag.h"
#include "Properties.h"
#include "memory_stream.h"
#include "BLOB.h"
#include "IData.h"
#include "BLOBInputStream.h"
#include "BLOBOutputStream.h"
#include "BLOBData.h"
#include "HTTPConnection.h"

#include "HTTPServerConnection.h"

#include "BufferedReader.h"
#include "PrintWriter.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "UniqueID.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/**
Provides the classes for implementing networking applications. 
*/
namespace net
{

util::Properties HTTPRequest::getParameters() const
{
	util::Properties params;

	// Volcamos todos los headers en los parametros.
	//params.add(this->headers);
	

	util::sstring paramsStr = "";

	if(util::sstring(this->method) ^= "GET")
	{
		std::vector<std::string> vec = util::sstring(this->url).split("?");

		if(vec.size() < 2)
		{
			// No hay parametros
			return params;
		}

		paramsStr = vec[1];

	}
	else
	{
		// Los valores estarán en el body
		paramsStr = this->body.get();
	}




	std::vector<std::string> pair = paramsStr.split("&");

	for(int i = 0 ; i < pair.size() ; i++)
	{
		std::vector<std::string> paramValue = util::sstring(pair[i]).split("=");

		if(paramValue.size() == 2)
		{
			// Escapar los parametros antes de meterlos en el objeto propiedades.
			params.setProperty(HTTPResponse::unscape(paramValue[0]),HTTPResponse::unscape(paramValue[1]));
		}
	}

	return params;
}

std::string HTTPRequest::partialUrl() const
{
	std::vector<std::string> vec = util::sstring(this->url).split("?");

	return vec[0];	
}

HTTPServerConnection::HTTPServerConnection(io::IInputStream* input, io::IOutputStream* output,bool sessions):m_input(input),m_output(output),m_useSessions(sessions)
{

}

HTTPServerConnection::~HTTPServerConnection()
{

}

std::auto_ptr<HTTPRequest> HTTPServerConnection::getQuery()
{

	std::auto_ptr<HTTPRequest> query(new HTTPRequest);

	io::BufferedReader reader(m_input);

	std::string queryLine = reader.readLine();

	std::vector<std::string> vec = ((util::sstring)queryLine).split(" ");

	if(vec.size() < 2)
		throw new exceptions::HTTPException(-1,"Invalid HTTP Query");

	query->method = vec[0];
	query->url = vec[1];

	queryLine = reader.readLine();

	while(queryLine != "")
	{
		vec = ((util::sstring)queryLine).split(":");

		
		std::string value = "";
		for(int i = 1 ; i < vec.size() ; i++)
		{
			value += vec[i];

			if((i + 1) != vec.size())
			{
				value += ":";
			}
		}
		
		query->headers.setProperty(((util::sstring)HTTPResponse::unscape(vec[0])).trim(),((util::sstring)HTTPResponse::unscape(value)).trim());
		
		queryLine = reader.readLine();
	}

	util::sstring contenLength = query->headers.getProperty("Content-Length","");

	if(query->method == "POST")
	{
		if(contenLength != "")
		{
			unsigned long ulContenLength = (unsigned long)contenLength;

			query->body.resize(ulContenLength);
			query->body.setLength(ulContenLength);

			int pos = 0;
			while(ulContenLength > 0)
			{
				long readed = reader.read((unsigned char*)query->body.get(pos),ulContenLength);
				ulContenLength -= readed;
				pos += readed;
			}


			
		}
		else
		{
			// no hay Content-Length.
			// Se lee mientras haya datos disponbles
			unsigned char buffer[1000];

			try
			{
				while(true)
				{
					unsigned int readed = reader.read(buffer,1000);

					query->body.attach((char*)buffer,readed);
				}
			}catch(...){ }
		}
	}

	if(m_useSessions)
	{
		query->sessionData = m_sessionData;
	}

	return query;

}

void HTTPServerConnection::sendResponse(std::auto_ptr<HTTPResponse> response)
{
	
	if(m_useSessions)
	{
		m_sessionData = response->sessionData;
	}


	std::string packet = "";

	packet += std::string("HTTP/1.1 ") + util::sstring(response->status) + std::string(" ") + response->serverMsg + "\r\n";

	// Comprobamos que si hay un body que enviar, existe la cabecera content-length.
	// Si no existe, la incluimos

	if(response->body.get())
	{
		std::auto_ptr<io::IInputStream> bodyInput = response->body->getInputStream();
		long length = bodyInput->available();
		if(length != 0)
		{
			response->headers.setProperty("Content-Length", util::sstring(length));
		}
	}

	// enviamos cabeceras.
	std::vector<std::string> headerNames = response->headers.propertyNames();

	std::vector<std::string>::iterator it = headerNames.begin();

	while(it != headerNames.end())
	{
		packet += *it + ": " + response->headers.getProperty(*it) + "\r\n";		
		it++;
	}

	packet += "\r\n";
	
	m_output->write((unsigned char*)packet.c_str(),packet.length());

	if(response->body.get())
	{
		std::auto_ptr<io::IInputStream> bodyInput = response->body->getInputStream();
		long length = bodyInput->available();
		int send = 0;
		unsigned char dataBuffer[PACKET_LENGTH];
		while(send < length)
		{
			int readed = bodyInput->read(dataBuffer,PACKET_LENGTH);
			m_output->write(dataBuffer,readed);
			send += readed;
		}
	}	

}

} // namespace net

} // namespace stream
