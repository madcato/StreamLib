// Connection.h: interface for the Connection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Connection_H__8ED6FD39_22A4_4F38_AAA8_BEDEF6F24DF6__INCLUDED_)
#define AFX_Connection_H__8ED6FD39_22A4_4F38_AAA8_BEDEF6F24DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

namespace exceptions
{
	class SQLException : public StreamException
	{
	public:
		SQLException(const std::string& error):StreamException(-1,error){}
	};
}
/**
 Provides the classes for accessing and processing data stored in a data source 
 using the C++ programming language. 
*/
namespace sql
{

/**
	A connection (session) with a specific database. 
	SQL statements are executed and results are returned within the context of a connection. 

	<h3>Example code</h3>
<code>
	try<br>
	{<br>
		&nbsp;&nbsp;auto_ptr&lt;Connection&gt; connection = Connection::createConnection("DSN=BakeMail");<br>
<br>
		.....<br>
	}catch(exceptions::SQLException* e)<br>
	{<br>
		&nbsp;&nbsp;cout << e->what() << endl;<br>
	}<br>
</code>
*/
class Connection  
{
public:
	virtual ~Connection();

	/**
		Creates a new connection.
		@param connectionString ODBC connection string.
		@return The new connection object.
	*/
	static std::auto_ptr<Connection> createConnection(const std::string& connectionString);

	/**
		Creates a new PreparedStatement object.
		@param sql SQL query.
		@return The new PreparedStatement object.
	*/
	virtual std::auto_ptr<PreparedStatement> prepareStatement(const std::string& sql) = 0;

	/**
		Closes this connection.
	*/
	virtual void close() = 0;

	/**
		Starts a new transaction
	*/
	virtual void startTransaction() = 0;

	/**
		Commits a transaction
	*/
	virtual void commit() = 0;

	/**
		Rollbacks a transaction
	*/
	virtual void rollback() = 0;

protected:

	/**
		Protected constructor.
		To create a new object, call createConnection method.
	*/
	Connection();
	
};

/**
	Connection automatic pointer.
*/
typedef std::auto_ptr<Connection> ConnectionPtr;

} // namespace sql

} // namespace stream
#endif // !defined(AFX_Connection_H__8ED6FD39_22A4_4F38_AAA8_BEDEF6F24DF6__INCLUDED_)
