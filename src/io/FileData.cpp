// FileData.cpp: implementation of the FileData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "IData.h"

#include "FileData.h"

#include "Exceptions.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace io
namespace io
{

FileData::FileData(const std::string& fileName,long ini_position, long end_position):m_fileName(fileName)
{
	m_ini_position = ini_position;
	m_end_position = end_position;
}

FileData::~FileData()
{

}

std::auto_ptr<IInputStream> FileData::getInputStream()
{
	return new FileInputStream(m_fileName,m_ini_position,m_end_position);
}

std::auto_ptr<IOutputStream> FileData::getOutputStream()
{
	return new FileOutputStream(m_fileName);
}

} // namespace io

} // namespace stream
