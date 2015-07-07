// HTTPControllerManager.cpp: implementation of the HTTPControllerManager class.
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
#include "HTTPServerConnection.h"
#include "HTMLTPage.h"

#include "HTTPControllerManager.h"

#include "FileUtil.h"
#include "HTMLIncluder.h"
#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "BLOBInputStream.h"
#include "BLOBOutputStream.h"
#include "FileData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace net
namespace net
{

std::auto_ptr<HTTPResponse> HTTPControllerManager::constructNotFoundResponse()
{
	std::auto_ptr<HTTPResponse> response(new HTTPResponse);
	response->status = HTTP_STATUS_FILE_NOT_FOUND;

	response->serverMsg = "";//File Not Found";
	util::Properties prop;
	prop.setProperty("Content-Type","text/html");
	
	response->headers = prop;
	
	util::ref_count_ptr<io::Blob<char> > blob;
	blob->setData("\r\n<html><head><meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\"><title>404 - Object not found. File not found in this server.</title><meta name=\"description\" content=\"404 - Object not found. File not found in this server.\"></head><body><H1>Object Not Found</H1><br><br>The requested file was not found in this server. Please contact system administrador to report this fail. <br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br></body></html>\r\n");
	response->body = std::auto_ptr<io::IData>(new io::BLOBData<char>(blob));

	return response;
}

std::auto_ptr<HTTPResponse> requestRangeNotSatisfiable(const std::string& range)
{
	std::auto_ptr<HTTPResponse> response(new HTTPResponse);
	response->status = HTTP_STATUS_RANGE_NOT_SATISFIABLE;

	response->serverMsg = "";//File Not Found";
	util::Properties prop;
	prop.setProperty("Content-Type","text/html");
	
	response->headers = prop;
	
	util::ref_count_ptr<io::Blob<char> > blob;
	blob->setData("\r\n<html><head><meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\"><title>416 - Requested range not satisfiable. Range specification invalid or not satisfiable</title><meta name=\"description\" content=\"416 - Requested range not satisfiable. Range specification invalid or not satisfiable.\"></head><body><H1>Request range not satisfiable</H1><br><br>The requested range was not satisfiable or invalid Please contact system administrador to report this fail. <br><br>" + range + "<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br></body></html>\r\n");
	response->body = std::auto_ptr<io::IData>(new io::BLOBData<char>(blob));

	return response;
}		
	
HTTPControllerManager::HTTPControllerManager(IHTTPController* defaultController)
{
	m_defaultController = defaultController;
}

HTTPControllerManager::~HTTPControllerManager()
{

}

void HTTPControllerManager::addController(std::auto_ptr<IHTTPController> controller)
{
	m_mapControllers[controller->getUrl()] = controller;
}

std::auto_ptr<HTTPResponse> HTTPControllerManager::executeQuery(std::auto_ptr<HTTPRequest> query)
{
	try
	{
		std::map<std::string,std::auto_ptr<IHTTPController> >::iterator it = m_mapControllers.find(query->partialUrl());

		if(it != m_mapControllers.end())
		{
			return it->second->executeQuery(query);
		}

		if(m_defaultController)
		{
			return m_defaultController->executeQuery(query);
		}

		return constructNotFoundResponse();

	}catch(std::exception* e)
	{
		std::auto_ptr<HTTPResponse> response(new HTTPResponse);
		response->status = HTTP_STATUS_INTERNAL_SERVER_ERROR;

		response->serverMsg = "Internal Server Error";

		util::ref_count_ptr<io::Blob<char> > blob;
		blob->setData(std::string("\r\n<html><head><meta HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\"><title>500 - Internal server error. Stream Exception.</title><meta name=\"description\" content=\"500 - Internal server error. Stream Exception..\"></head><body><H1>Stream Exception</H1><br><br>") + e->what() + ". <br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br></body></html>\r\n");
		response->body = std::auto_ptr<io::IData>(new io::BLOBData<char>(blob));

		return response;
	}
}

FileAccessController::FileAccessController(const std::string& basePath,const std::string& baseUrl,const std::string& defaultFileName)
{
	m_basePath = basePath;
	m_baseUrl = baseUrl;
	m_defaultFileName = defaultFileName;
}

std::auto_ptr<HTTPResponse> FileAccessController::executeQuery(std::auto_ptr<HTTPRequest> query)
{
	util::sstring url = query->url;
	if(url.endsWith("/"))
	{
		// Añadimos el nombre de fichero por defecto.
		url += m_defaultFileName;
	}
	std::string filePath = url2Path(url,m_basePath,m_baseUrl);

	std::auto_ptr<HTTPResponse> response(new HTTPResponse);

	response->sessionData = query->sessionData;

	if(!util::FileUtil::fileExists(filePath))
	{
			
		return HTTPControllerManager::constructNotFoundResponse();
	}

	response->status = HTTP_STATUS_OK;
	response->serverMsg  = "file";

	response->headers.setProperty("Accept-Ranges", "bytes");

	util::sstring range = query->headers.getProperty("Range");

	long fileSize = util::FileUtil::FileSize(filePath);
	long ini_position = 0;
	long end_position = fileSize;

	if(range != "")
	{
		std::vector<std::string> vectorRanges = util::StringUtil::split(range.split("=")[1],"-,",util::Tokenizer::FULL);
		
		
		if(vectorRanges[1] == "-")
		{
			ini_position = util::StringUtil::longValue(vectorRanges[0]);
			if(vectorRanges.size() == 3)
			{
				end_position = util::StringUtil::longValue(vectorRanges[2]);
				end_position++;
			}
			else
			{
				end_position = fileSize;
			}
		}
		else
		{
			if(vectorRanges[0] == "-")
			{
				long end_size = util::StringUtil::longValue(vectorRanges[1]);
				if(end_size == 0)
				{
					return requestRangeNotSatisfiable(range);
				}

				end_position = fileSize;
				ini_position = fileSize - end_size >= 0 ? fileSize - end_size : 0;
			}
			else
			{
				return requestRangeNotSatisfiable(range);
			}
			
		}

		if(ini_position >= fileSize)
		{
			return requestRangeNotSatisfiable(range);
		}

		response->headers.setProperty("Content-Range", "bytes " + util::sstring(ini_position) + "-" + util::sstring(end_position - 1) + "/" + util::sstring(end_position - ini_position));
	}

	

	response->body = std::auto_ptr<io::IData>(new io::FileData(filePath,ini_position,end_position));

	return response;
}

std::string FileAccessController::getUrl()
{
	return m_baseUrl;
}

void FileAccessController::setUrl(const std::string& url)
{
	m_baseUrl = url;
}


std::string FileAccessController::url2Path(const std::string& url,const std::string& pathBase,const std::string& urlBase)
{
	std::string finalPath;
	
	finalPath = pathBase;

	util::FileUtil::PutFinalSlashInPath(finalPath);

	if(url.find(urlBase) == std::string::npos)
	{
		return "";
	}

	std::string url_ext = url.substr(urlBase.length());

	util::FileUtil::replaceSlash(url_ext);

	finalPath += url_ext;

	return finalPath;
}

GenericController::GenericController()
{

}

std::auto_ptr<HTMLTPage> GenericController::loadHTMLT(const std::string& fileName,bool makeIncludes)
{
	std::string content = (std::string)util::FileUtil::File2Buffer(m_basePath + fileName);

	if(makeIncludes)
	{
		content = HTMLIncluder::makeIncludes(content,m_basePath);
	}

	std::auto_ptr<HTMLTPage> page(new HTMLTPage(content));

	return page;
}

std::string GenericController::getUrl()
{
	return m_baseUrl;
}

} // namespace net

} // namespace stream