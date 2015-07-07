// HTTPConnection.cpp: implementation of the HTTPConnection class.
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
#include "BLOBData.h"

#include "HTTPConnection.h"

#include "BufferedReader.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "BLOBInputStream.h"
#include "BLOBOutputStream.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace stream
{

/// namespace net
namespace net
{
using namespace util;
using namespace io;


const ulong HTTP_STATUS_FILE_NOT_FOUND = 404;
const ulong HTTP_STATUS_OK = 200;
const ulong HTTP_STATUS_RANGE_NOT_SATISFIABLE = 416;
const ulong HTTP_STATUS_INTERNAL_SERVER_ERROR = 500;

std::string HTTPResponse::unscape(const std::string& str)
{
	std::string finalValue = "";
	for(int i = 0 ; i < str.length() ; i++)
	{
		if(str[i] != '%')
		{
			if(str[i] == '+')
			{
				finalValue += ' ';
			}
			else
			{
				finalValue += str[i];
			}
		}
		else
		{
			char paso[10];
			paso[0] = str[i+1];
			paso[1] = str[i+2];
			paso[2] = '\0';

			char value;
			sscanf(paso,"%02x",&value);

			finalValue += value;

			i += 2;
		}
	}

	return finalValue;
}

HTTPConnection::HTTPConnection(IInputStream* input, IOutputStream* output):m_input(input),m_output(output)
{

}

HTTPConnection::~HTTPConnection()
{

}

std::auto_ptr<HTTPResponse> HTTPConnection::doGet(std::string url,Properties& headers)
{

	std::string packet = "GET " + url + " HTTP/1.1\r\n";

	constructPacket(packet,headers);
	
	
	packet += "\r\n";
	

	
	m_output->write((unsigned char*)packet.c_str(),packet.length());

	return getResponse();
}

std::auto_ptr<HTTPResponse> HTTPConnection::doPost(std::string url,Properties& headers,const io::Blob<char>& body)
{

	std::string packet = "POST " + url + " HTTP/1.1\r\n";

	if(body.length() != 0)
	{
		headers.setProperty("Content-Length", sstring(body.length()));
	}

	constructPacket(packet,headers);

	packet += "\r\n";
	m_output->write((unsigned char*)packet.c_str(),packet.length());	

	m_output->write((unsigned char*)body.get(),body.length());

	return getResponse();
}

std::auto_ptr<HTTPResponse> HTTPConnection::getResponse()
{

	BufferedReader reader(m_input);

	std::string responseLine = reader.readLine();

	std::vector<std::string> vec = ((sstring)responseLine).split(" ");

	std::auto_ptr<HTTPResponse> httpResponse(new HTTPResponse);

	if(vec.size() < 2)
		throw new exceptions::HTTPException(-1,"Invalid HTTP Response");

	httpResponse->status = (unsigned long)((sstring)vec[1]);
	httpResponse->serverMsg = vec[2];

	responseLine = reader.readLine();

	while(responseLine != "")
	{
		vec = ((sstring)responseLine).split(":");

		
		std::string value = "";
		for(int i = 1 ; i < vec.size() ; i++)
		{
			value += vec[i];

			if((i + 1) != vec.size())
			{
				value += ":";
			}
		}
		
		httpResponse->headers.setProperty(((sstring)vec[0]).trim(),((sstring)value).trim());
		
		responseLine = reader.readLine();
	}

	sstring contenLength = httpResponse->headers.getProperty("Content-Length","");

	if(contenLength != "")
	{
		unsigned long ulContenLength = (unsigned long)contenLength;

		util::ref_count_ptr<io::Blob<char> > blob;

		blob->resize(ulContenLength);
		blob->setLength(ulContenLength);

		int pos = 0;
		while(ulContenLength > 0)
		{
			long readed = reader.read((unsigned char*)blob->get(pos),ulContenLength);
			ulContenLength -= readed;
			pos += readed;
		}

		

		httpResponse->body = std::auto_ptr<io::IData>(new BLOBData<char>(blob));
		
	}
	else
	{
		// no hay Content-Length.
		// Se lee mientras haya datos disponbles
		unsigned char buffer[1000];

		try
		{
			util::ref_count_ptr<io::Blob<char> > blob;

			httpResponse->body = std::auto_ptr<io::IData>(new BLOBData<char>(blob));

			std::auto_ptr<IOutputStream> output = httpResponse->body->getOutputStream();
			unsigned int readed = 0;
			do
			{
				readed = reader.read(buffer,1000);

				output->write(buffer,readed);
			}while(readed != 0);
		}catch(...){}
	}

	return httpResponse;
}

void HTTPConnection::constructPacket(std::string& packet,util::Properties& headers)
{
	std::vector<std::string> propertyNames = headers.propertyNames();

	for(int i = 0 ; i < propertyNames.size(); i++)
	{
		packet += propertyNames[i];
		packet += ": ";
		packet += headers.getProperty(propertyNames[i]);
		packet += "\r\n";		
	}
}

} // namespace net

} // namespace stream