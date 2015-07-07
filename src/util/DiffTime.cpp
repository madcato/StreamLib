// DiffTime.cpp: implementation of the DiffTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiffTime.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{

/// namespace util
namespace util
{

DiffTime::DiffTime()
{

}

DiffTime::~DiffTime()
{

}

void DiffTime::start()
{
	m_starting = clock();
}

ulong DiffTime::finish()
{
	return clock() - m_starting;
}

} // namespace util

} // namespace stream