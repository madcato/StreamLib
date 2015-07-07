// PreparedStatement.h: interface for the PreparedStatement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREPAREDSTATEMENT_H__44F33EBA_9E43_40E4_84E1_660FE87E9A69__INCLUDED_)
#define AFX_PREPAREDSTATEMENT_H__44F33EBA_9E43_40E4_84E1_660FE87E9A69__INCLUDED_

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
	An object that represents a precompiled SQL statement.

  	<h3>Example code</h3>
<code>
	try<br>
	{<br>
		...<br>
		&nbsp;&nbsp;auto_ptr&lt;PreparedStatement&gt; statement = connection->prepareStatement("SELECT * FROM servers WHERE id_server >= ?");<br>
<br>
		&nbsp;&nbsp;statement->setLong(1,3);<br>
<br>
		&nbsp;&nbsp;auto_ptr&lt;ResultSet&gt; result = statement->executeQuery();<br>
		...<br>
		<br>
	}catch(exceptions::SQLException* e)<br>
	{<br>
		&nbsp;&nbsp;cout << e->what() << endl;<br>
	}<br>
</code>

*/
class PreparedStatement
{
public:
	PreparedStatement();
	virtual ~PreparedStatement();

	/**
		Executes the SQL statement in this PreparedStatement object, which may be any kind of SQL statement 
		that doesn't require to query data.
		@return The number of rows affected.
	*/
	virtual long execute();

	/**
		Executes the SQL statement in this PreparedStatement object, which may be any kind of SQL statement 
		that query data.
	*/
	virtual	std::auto_ptr<ResultSet> executeQuery();

	/**
		Sets the designated parameter to the given long value.
	*/
	void setLong(int index, long value);

	/**
		Sets the designated parameter to the given long value.
	*/
	void setString(int index, const std::string& value);
	
	/**
		Sets the designated parameter to the given blob.
	*/
	void setMySqlBLOB(int index, const io::Blob<char>& value);
	

protected:
	util::PrepareCommand m_command;
};

/**
	PreparedStatement automatic pointer.
*/
typedef std::auto_ptr<PreparedStatement> PreparedStatementPtr;

} // namespace sql

} // namespace stream

#endif // !defined(AFX_PREPAREDSTATEMENT_H__44F33EBA_9E43_40E4_84E1_660FE87E9A69__INCLUDED_)
