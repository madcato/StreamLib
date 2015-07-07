// PreparedStatement.cpp: implementation of the PreparedStatement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PrepareCommand.h"
#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "ResultSet.h"

#include "PreparedStatement.h"

#include "Tokenizer.h"
#include "Date.h"
#include "StringUtil.h"
#include "IDataProcessor.h"
#include "B64.h"
#include "HexBin.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{
/// namespace sql
namespace sql
{

PreparedStatement::PreparedStatement()
{

}

PreparedStatement::~PreparedStatement()
{

}

long PreparedStatement::execute()
{
	return -1;
}

std::auto_ptr<ResultSet> PreparedStatement::executeQuery()
{
	std::auto_ptr<ResultSet> result;

	return result;
}

void PreparedStatement::setLong(int index, long value)
{
	m_command.set(index,util::StringUtil::toString(value));
}

void PreparedStatement::setString(int index, const std::string& value)
{
	m_command.set(index,value);
}

void PreparedStatement::setMySqlBLOB(int index, const io::Blob<char>& value)
{
	std::string hexValue = "0x";

	io::HexBin hexBin(io::OPEN_FOR_ENCODING,false);

	io::Blob<unsigned char> data = hexBin.Update((unsigned char*)value.get(),value.length());
	
	hexValue += (std::string)data;

	
	m_command.set(index,hexValue);
}

} // namespace sql

} // namespace stream