// DB.h: interface for the DB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_H__366CB15F_9649_4D4F_8C52_3500DA7F6362__INCLUDED_)
#define AFX_DB_H__366CB15F_9649_4D4F_8C52_3500DA7F6362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace sql
namespace sql
{

/** 
	Generic access to data bases.
	Only creates a single connection. Every call to the static functions use
	the same db connection.
*/
class DB  
{
public:
	DB();
	virtual ~DB();

	/**
		Initializes the DB connection.
		@param connectionString Conenction string specifying the connection parameters.
		<dl>
		<dt>
			Example 1. MySQL:
		</dt>
		<dd>
			<code>
			DBBM::Init("DRIVER={MySQL ODBC 3.51 Driver};"<br>
							&nbsp;&nbsp;"SERVER=localhost;"<br>
							&nbsp;&nbsp;"DATABASE=CheckServ;"<br>
							&nbsp;&nbsp;"USER=;"<br>
							&nbsp;&nbsp;"PASSWORD=;"<br>
							&nbsp;&nbsp;"OPTION=3;");
			</code>
		</dd>
		<dt>
			Example 2. MS SQLServer:<br>
		</dt>
		<dd>
			<code>
			DBBM::Init("Provider=MSDASQL;"<br>
						&nbsp;&nbsp;"Driver={SQL Server};"<br>
						&nbsp;&nbsp;"Server=E520080NS;"<br>
						&nbsp;&nbsp;"Database=dbvia62;");
			</code><br>
		</dd>
		</dl>
	*/
	static void init(const std::string& connectionString);

	/**
		Querys a table.
		@param command Command that will be executed in the DB.
	*/
	static std::vector<std::vector<std::string> > queryTable(const std::string& command,bool returnColumnNames = false);

	/**
		Querys a table. First row returned has the name of the columns
		@param command Command that will be executed in the DB.
	*/
	static std::vector<std::vector<std::string> > queryNamedTable(const std::string& command);

	/**
		Querys a row.
		@param command Command that will be executed in the DB.
		@return A vector with the value of each column queried
	*/
	static std::vector<std::string> queryRow(const std::string& command);

	/**
		Querys a row.
		@param command Command that will be executed in the DB.
		@return A map with the columnName-value pairs.
	*/
	static std::map<std::string,std::string> queryNamedRow(const std::string& command);

	/**
		Inserts data.
		@param command Command that will be executed in the DB.
		@param data Data to be inserted.
	*/
	static void insertRow(const std::string& command,const std::vector<std::string>& data);

	/**
		Inserts data. This method construct the SQL commnad.
		@param tableName Name of the table where values must to be inserted.
		@param data Data to be inserted.
	*/
	static void insertNamedRow(const std::string& tableName,const std::map<std::string,std::string>& data);

	/**
		Querys for a set of pair values.
		The command must be an SQL that generates only two columns.
		The map is constructed using the first column as the index 
		for the map and the second column as the value for the map.
		Example: sys table.
		If the command doesn´t produce a two columns response, an exception is thrown.
	*/
	static std::map<std::string,std::string> queryPairMap(const std::string& command);

	/**
		Executes a command
		@param command Command that will be executed in the DB.
	*/
	static void execute(const std::string& command);

	/**
		Stars a new transaction.
	*/
	static void startTransaction();

	/**
		Commit a transaction.
	*/
	static void commit();

	/**
		Rollback a transaction.
	*/
	static void rollback();

	/**
		Prepare string to concatenate it in an SQL statement.
		@param str a string
		@return a prepared statement.
	*/
	static std::string prepareString(const std::string& str);

private:
	static std::auto_ptr<Connection> m_connection;
};


/**
	This class is used to initialize the COM objects.
*/
class COMInit
{
public:
	COMInit()
	{
		CoInitialize(NULL);
	}

	~COMInit()
	{
		CoUninitialize();
	}

};

#define INIT_COM() COMInit __cominit;

#define TOSQL DB::prepareStatement
} // namespace sql

} // namespace stream

#endif // !defined(AFX_DB_H__366CB15F_9649_4D4F_8C52_3500DA7F6362__INCLUDED_)
