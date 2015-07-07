// HTTPControllerManager.h: interface for the HTTPControllerManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPControllerMANAGER_H__BDB9E90E_3261_4F0B_A8A7_F019274F09A9__INCLUDED_)
#define AFX_HTTPControllerMANAGER_H__BDB9E90E_3261_4F0B_A8A7_F019274F09A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace stream
{

/// namespace net
namespace net
{
/**
Interface for Controller objects
*/
class IHTTPController
{
public:
	IHTTPController(){}
	virtual ~IHTTPController(){}

	/**
		Executes the query.
		@param query HTTPRequest
		@return the HTTPResponse
	*/
	virtual std::auto_ptr<HTTPResponse> executeQuery(std::auto_ptr<HTTPRequest> query) = 0;

	/**
		Controller must return the url name that represents itself.
		If a Controller is placed in "http://server/fileManager/controller?run=1", the Controller must return "/fileManager/controller"
		@return The Controller url name.
	*/
	virtual std::string getUrl()
	{
		return m_baseUrl;
	}

	/**
		Sets the url of this controller
	*/
	virtual void setUrl(const std::string& url)
	{
		m_baseUrl = url;
	}

	/**
		Controller must return the url name that represents itself.
		If a Controller is placed in "http://server/fileManager/controller?run=1", the Controller must return "/fileManager/controller"
		@return The Controller url name.
	*/
	virtual std::string getBasePath()
	{
		return m_baseUrl;
	}

	/**
		Sets the url of this controller
	*/
	virtual void setBasePath(const std::string& path)
	{
		m_basePath = path;
	}

protected:
	std::string m_baseUrl;
	std::string m_basePath;
};


/**
	Controller ready for access file system an dreturn the files required.
*/
class FileAccessController : public IHTTPController
{
public:
	FileAccessController(const std::string& basePath,const std::string& baseUrl = "/",const std::string& defaultFileName = "index.html");
	~FileAccessController(){}

	std::auto_ptr<HTTPResponse> executeQuery(std::auto_ptr<HTTPRequest> query);

	std::string getUrl();

	void setUrl(const std::string& url);
	/**
		Converts a url to a path.
		@param url Queried url.
		@param pathBase Path where files and dirctories are stored.
		@param urlBase url base. Must end with "/".
		@return a file path.
	*/
	static std::string url2Path(const std::string& url,const std::string& pathBase,const std::string& urlBase);

private:
	std::string m_basePath;
	std::string m_baseUrl;
	std::string m_defaultFileName;
};

/**
	Controller ready for implement the controller of the application.
*/
class GenericController : public IHTTPController
{
public:
	GenericController();
	~GenericController(){}

	std::string getUrl();

protected:
	std::auto_ptr<HTMLTPage> loadHTMLT(const std::string& fileName,bool makeIncludes = true);


};

/**
	Controller manager. This class delivers the queries to the controllers that must resolve the petition.
*/
class HTTPControllerManager  
{
public:
	/**
		Constructor
	*/
	HTTPControllerManager(IHTTPController* defaultController);
	virtual ~HTTPControllerManager();

	/**
		Adds a new extensión object to this manager.
		@param name Name of the Controller.
		@param Controller The new Controller.
	*/
	void addController(std::auto_ptr<IHTTPController> controller);


	/**
		Executes the query.
		Searches for the HTTP Controller associated withd the url of the query and call the executeQuery of that Controller
		@param query HTTPRequest
		@return the HTTPResponse
	*/
	std::auto_ptr<HTTPResponse> executeQuery(std::auto_ptr<HTTPRequest> query);

	/**
		@return a not-found HTML response
	*/
	static std::auto_ptr<HTTPResponse> constructNotFoundResponse();

private:

	std::map<std::string,std::auto_ptr<IHTTPController> > m_mapControllers;
	IHTTPController* m_defaultController;
};

} // namespace net

} // namespace stream

#endif // !defined(AFX_HTTPControllerMANAGER_H__BDB9E90E_3261_4F0B_A8A7_F019274F09A9__INCLUDED_)
