// DB.cpp: implementation of the DB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Exceptions.h"
#include "memory_stream.h"
#include "Blob.h"
#include "ResultSet.h"
#include "PrepareCommand.h"
#include "PreparedStatement.h"
#include "Connection.h"
#include "CriticalSection.h"

#include "DB.h"

#include "FLineParser.h"
#include "IOutputStream.h"
#include "IInputStream.h"
#include "PrintWriter.h"
#include "BufferedReader.h"
#include "FileOutputStream.h"
#include "FileInputStream.h"
#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"
#include "ILog.h"
#include "Socket.h"
#include "Log.h"
#include "LiteLog.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace sql
namespace sql
{

std::auto_ptr<Connection> DB::m_connection;
std::auto_ptr<sync::CriticalSection> DB::m_cs;

DB::DB()
{

}

DB::~DB()
{

}

void DB::init(const std::string& connectionString)
{
	m_cs = std::auto_ptr<sync::CriticalSection>(new sync::CriticalSection);
	m_connection = Connection::createConnection(connectionString);

}

std::vector<std::vector<std::string> > DB::queryTable(const std::string& command,bool returnColumnNames)
{

	DBLOCK
	util::LLOG(util::LOG_DB,command);
	std::vector<std::vector<std::string> > table;
	std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);

	std::auto_ptr<ResultSet> result = statement->executeQuery();

	if(result->eof())
	{
		
		return table;
	}

	result->moveFirst();


	if(returnColumnNames)
	{
		std::vector<std::string> firstRow;

		long columnCount = result->getColumnCount(); 
		for(int i = 0 ; i < columnCount ; i++)
		{
			firstRow.push_back(result->getColumnName(i));
		}

		table.push_back(firstRow);
	}

	while(!result->eof())
	{
		std::vector<std::string> row;

		int cn = result->getColumnCount();

		for(int i = 0 ; i < cn ; i++)
		{
			row.push_back(result->getString(i));
		}

		table.push_back(row);

		result->moveNext();
	}

	return table;
}

std::vector<std::vector<std::string> > DB::queryNamedTable(const std::string& command)
{
	return queryTable(command,true);
}

std::vector<std::string> DB::queryRow(const std::string& command)
{

	DBLOCK
	util::LLOG(util::LOG_DB,command);
	std::vector<std::string> row;
	std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);

	std::auto_ptr<ResultSet> result = statement->executeQuery();

	if(result->eof())
	{
		
		return row;
	}

	result->moveFirst();

		

	int cn = result->getColumnCount();

	for(int i = 0 ; i < cn ; i++)
	{
		row.push_back(result->getString(i));
	}

	return row;
}

std::map<std::string,std::string> DB::queryNamedRow(const std::string& command)
{

	DBLOCK
	util::LLOG(util::LOG_DB,command);
	std::map<std::string,std::string> mapa;
	std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);

	std::auto_ptr<ResultSet> result = statement->executeQuery();

	if(result->eof())
	{
		
		return mapa;
	}

	result->moveFirst();

	
		

	int cn = result->getColumnCount();

	for(int i = 0 ; i < cn ; i++)
	{
		mapa.insert(std::pair<std::string,std::string>(result->getColumnName(i),result->getString(i)));
	}
	

	return mapa;
}

void DB::insertRow(const std::string& command,const std::vector<std::string>& values)
{

	DBLOCK
	util::LLOG(util::LOG_DB,command);
	std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);

	for(int i = 0 ; i < values.size() ; i++)
	{
		statement->setString(i,values[i]);
	}

	statement->execute();

}

void DB::insertNamedRow(const std::string& tableName,const std::map<std::string,std::string>& data)
{

	DBLOCK
	
	std::string command = "";

	command = "INSERT INTO " + tableName + "(";

	std::map<std::string,std::string>::const_iterator it;

	for(it = data.begin() ; it != data.end() ; it++)
	{
		if(it != data.begin())
			command += ",";

		command += it->first;
	}

	command += ") VALUES(";


	for(it = data.begin() ; it != data.end() ; it++)
	{
		if(it != data.begin())
			command += ",";

		command += "'" + it->second + "'";
	}

	command += ")";

	util::LLOG(util::LOG_DB,command);
	std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);

	statement->execute();

}

std::map<std::string,std::string> DB::queryPairMap(const std::string& command)
{


	DBLOCK
	util::LLOG(util::LOG_DB,command);
	std::vector<std::vector<std::string> > table = DB::queryTable(command);

	std::map<std::string,std::string> m;
	if(table.size() == 0)
	{
		
		return m;
	}

	if(table[0].size() != 2)
	{
		throw new exceptions::SQLException("DB::queryPairMap(). El comando \"" + command + "\" debe devolver dos columnas");
	}

	std::vector<std::vector<std::string> >::iterator it;
	
	for(it = table.begin() ; it != table.end() ; it++)
	{
		m[(*it)[0]] = (*it)[1];
	}


	return m;

}

std::string DB::querySysValue(const std::string& valueName)
{

	DBLOCK
	
	std::string command = "SELECT strValue FROM sys WHERE idValue = '" 
		+ valueName + "'";

	util::LLOG(util::LOG_DB,command);
	std::vector<std::string> result = DB::queryRow(command);

	if(result.size() == 0)
	{
		throw new exceptions::SQLException("DB::querySysValue(). La variable \"" + valueName + "\" no existe en la tabla \"sys\"");
	}
	

	return result[0];
}

long DB::execute(const std::string& command)
{

	DBLOCK
	util::LLOG(util::LOG_DB,command);
	std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);
	
	long retCode = statement->execute();

	return retCode;
}

void DB::startTransaction()
{
	DBLOCK
	m_connection->startTransaction();
}

void DB::commit()
{
	DBLOCK
	m_connection->commit();
}

void DB::rollback()
{
	DBLOCK
	m_connection->rollback();
}

std::string DB::prepareString(const std::string& str)
{
	std::string resultStr;

	for(int i = 0 ; i < str.length() ; i++)
	{
		switch(str[i])
		{
		case 0:
			resultStr += "\\0";
			break;
		case '\'':
			resultStr += "\\'";
			break;
		case '"':
			resultStr += "\\\"";
			break;
		case '\b':
			resultStr += "\\b";
			break;
		case '\n':
			resultStr += "\\n";
			break;
		case '\r':
			resultStr += "\\r";
			break;
		case '\t':
			resultStr += "\\t";
			break;
		case 26: // Ctrl+z
			resultStr += "\\Z";
			break;
		case '\\':
			resultStr += "\\\\";
			break;
		case '%':
			resultStr += "\\%";
			break;
		case '_':
			resultStr += "\\_";
			break;
		default:
			resultStr += str[i];
			break;
		}
	}

	return resultStr;
}

void DB::unloadTableToFile(const std::string& tableName, const std::string& format, const std::string& fileName, bool empty)
{

	util::FLineParser lineParser(format);

	std::auto_ptr<io::IOutputStream> file(new io::FileOutputStream(fileName));
	io::PrintWriter printWriter(file.get());

	std::vector<util::FLineParser::FToken>::iterator it;
	std::string columnNames;
	for(it = lineParser.m_formatVec.begin() ; it < lineParser.m_formatVec.end() ; it++)
	{
		if(columnNames == "")
			columnNames += it->m_name;
		else
			columnNames +=  ","  + it->m_name;
	}
	
	
	
	std::vector<std::vector<std::string> > table = DB::queryTable("SELECT " + columnNames + " FROM " + tableName);

	ulong maxx = table.size();
	ulong maxy = maxx > 0 ? table[0].size() : 0;
	for(ulong x = 0 ; x < maxx ; x++)
	{
		util::sstring line = "";
		
		for(ulong y = 0 ; y < maxy ; y++)
		{
			int fieldLength = lineParser.m_formatVec[y].m_size;
			
			util::sstring field(fieldLength,' ');
			field = table[x][y] + field;
			field = field.substr(0,fieldLength);

			line += field;

		}
		printWriter.println(line);
	}

	if(empty)
		emptyTable(tableName);
}

void DB::loadFileToTable(const std::string& fileName,const std::string& tableName, const std::string& format, bool empty)
{
	if(empty)
		emptyTable(tableName);

	util::FLineParser lineParser(format);

	std::auto_ptr<io::IInputStream> file(new io::FileInputStream(fileName));
	io::BufferedReader bufferedReader(file.get());

	std::vector<util::FLineParser::FToken>::iterator it;
	std::string columnNames;
	for(it = lineParser.m_formatVec.begin() ; it < lineParser.m_formatVec.end() ; it++)
	{
		if(columnNames == "")
			columnNames += it->m_name;
		else
			columnNames +=  ","  + it->m_name;
	}
	
	util::sstring line = "";
	do
	{
		line = bufferedReader.readLine();

		if(line != "")
		{
			std::vector<util::FLineParser::FToken> vecTokens = lineParser.parse(line);

			util::sstring command = "INSERT INTO " + tableName + "(" + columnNames + ")  VALUES(";

			std::vector<util::FLineParser::FToken>::const_iterator it;

			for(it = vecTokens.begin() ; it != vecTokens.end() ; it++)
			{
				if(it != vecTokens.begin())
					command += ",";

				command += "'" + util::sstring(it->m_value).trim() + "'";
			}

			command += ")";

			std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);

			statement->execute();
		}
	}while(line != "");
}

void DB::emptyTable(const std::string& tableName)
{

	DBLOCK
	std::string command = "TRUNCATE TABLE " + tableName;
	util::LLOG(util::LOG_DB,command);
	std::auto_ptr<PreparedStatement> statement = m_connection->prepareStatement(command);

	statement->execute();

}

} // namespace sql

} // namespace stream