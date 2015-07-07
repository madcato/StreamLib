// Connection.cpp: implementation of the Connection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "PrepareCommand.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "ResultSet.h"
#include "PreparedStatement.h"

#include "Connection.h"

#include "IDataProcessor.h"
#include "B64.h"
#include "HexBin.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "ADOimpl.inl"

/// namespace stream
namespace stream
{
/// namespace sql
namespace sql
{



Connection::Connection()
{
	
}

Connection::~Connection()
{

}

std::auto_ptr<Connection> Connection::createConnection(const std::string& connectionString)
{
	std::auto_ptr<Connection> returnValue(new ADOConnection(connectionString));

	return returnValue;
}

} // namespace sql

} // namespace stream