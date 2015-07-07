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
		It queries for a set of pair values.
		The command must be an SQL that generates only two columns.
		The map is constructed using the first column as the index 
		for the map and the second column as the value for the map.
		Example: sys table.
		If the command doesn´t produce a two columns response, an exception is thrown.
	*/
	static std::map<std::string,std::string> queryPairMap(const std::string& command);

	/**
		It query for a value in a table called allways 'sys'
		@param valueName Name of the value to retrive.
		@return The value of the property.
	*/
	static std::string querySysValue(const std::string& valueName);

	/**
		Executes a command
		@param command Command that will be executed in the DB.
		@return The number of rows affected.
	*/
	static long execute(const std::string& command);

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

	/**
		Unload a table to a file. 
		@param tableName Table to dump.
		@param format Format of the file to create. The format specifies de name of the columns to dump and its length.
		@param fileName Path to the file.
		@param empty. If true, the table is drop after downloading data to the file.
	*/
	static void unloadTableToFile(const std::string& tableName, const std::string& format, const std::string& fileName,bool drop);

	/**
		Upload a file to a table. 
		@param fileName Path to the file.
		@param tableName Table to dump.
		@param format Format of the file to create. The format specifies de name of the columns to dump and its length.		
		@param empty. If true, the table is drop before uploading data. Pevious data will be lost.
	*/
	static void loadFileToTable(const std::string& fileName,const std::string& tableName, const std::string& format, bool drop);

	/**
		Empties a table.
		@param  tableName. Name of the table
	*/
	static void emptyTable(const std::string& tableName);

private:
	static std::auto_ptr<Connection> m_connection;
	static std::auto_ptr<sync::CriticalSection> m_cs;
};

/**
	This class control de lock of the critical section in each function.
*/
class CSControl
{
public:
	CSControl(sync::CriticalSection* cs):m_cs(cs)
	{
		m_cs->lock();
	}
	virtual ~CSControl()
	{
		m_cs->unlock();
	}
private:
	sync::CriticalSection* m_cs;
};

#define DBLOCK CSControl _localDBLock(m_cs.get());

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

/**
	This class works like a macro for formatting strings.
	Example:
	string data = StrF("SELECT ? FROM ? WHERE ?=?")["id"]["table"]["column1"]["value"];

	// data will be formatted as: "SELECT id FROM table WHERE column1=value

	The interrogant is the key charater used to identify the position where the substring will be placed
	The number of key characters can be lesser or greater than the number of substrings, but in this case an exception is thrown.

	The substrings can include the key character: they won't be used as key characters to replace.
*/
class StrF
{
public:
	StrF(char* str):m_index(0){m_str.setCommand(str);}
	StrF(const std::string& str):m_index(0){m_str.setCommand(str);}
	virtual ~StrF(){}

	operator std::string()
	{
		return m_str.getFinalCommand();
	}

	StrF& operator [](char* str)
	{
		m_str.set(m_index++,str);
		return *this;
	}

	StrF& operator [](const std::string& str)
	{
		m_str.set(m_index++,str);
		return *this;
	}


private:
	util::PrepareCommand m_str;
	ulong m_index;
};

#define INIT_COM() COMInit __cominit

#define TOSQL DB::prepareStatement
} // namespace sql

} // namespace stream

#endif // !defined(AFX_DB_H__366CB15F_9649_4D4F_8C52_3500DA7F6362__INCLUDED_)
