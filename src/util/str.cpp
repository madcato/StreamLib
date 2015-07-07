// str.cpp: implementation of the str class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"

#include "str.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{


str::str()
{
	m_data = new char[1];
	m_data[0] = 0;
	m_dataLength = 1;
}

str::str(const str& cpy)
{
	if(cpy.m_dataLength)
	{
		m_dataLength = cpy.m_dataLength;
		m_data = new char[m_dataLength];
		memcpy(m_data,cpy.m_data,m_dataLength);
	}
	else
	{
		m_data = new char[1];
		m_data[0] = 0;
		m_dataLength = 1;
	}
}

str::~str()
{
	if(m_data)
		delete[] m_data;

	m_dataLength = 0;
}

str str::operator+(const str& arg) const
{
	str result;

	result.m_dataLength = m_dataLength + arg.m_dataLength;

	if(result.m_dataLength == 0)
	{
		return result;
	}

	result.m_data = new char[result.m_dataLength];

	
	memcpy(result.m_data,m_data,m_dataLength - 1);

	memcpy(result.m_data + m_dataLength - 1,arg.m_data,arg.m_dataLength);


	return result;
}

bool str::operator==(const str& arg) const
{
	if(m_dataLength != arg.m_dataLength)
		return false;

	for(int i= 0 ; i < m_dataLength -1 ; i++)
	{
		if(m_data[i] != arg.m_data[i])
			return false;
	}

	return true;
}

str& str::operator+=(const str& arg)
{
	str result;

	result.m_dataLength = m_dataLength + arg.m_dataLength;

	if(result.m_dataLength == 0)
	{
		return *this;
	}

	result.m_data = new char[result.m_dataLength];

	
	memcpy(result.m_data,m_data,m_dataLength - 1);

	memcpy(result.m_data + m_dataLength - 1,arg.m_data,arg.m_dataLength);

	*this = result;

	return *this;
}

str& str::operator=(const str& arg)
{
	delete[] m_data;

	if(arg.m_dataLength)
	{		
		m_dataLength = arg.m_dataLength;
		m_data = new char[m_dataLength];
		memcpy(m_data,arg.m_data,m_dataLength);
	}
	else
	{
		m_data = new char[1];
		m_data[0] = 0;
		m_dataLength = 1;
	}

	return *this;
}

const char* str::c_str() const
{
	return m_data;
}

long str::length() const
{
	return m_dataLength - 1;
}

char& str::operator[](int i)
{
	return m_data[i];
}

char str::operator[](int i) const
{
	return m_data[i];
}


} // namespace util

} // namespace stream