// IFilterOutputStream.cpp: implementation of the IFilterOutputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOutputStream.h"
#include "IFilterOutputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
using namespace io;
IFilterOutputStream::IFilterOutputStream(IOutputStream* output):m_output(output)
{

}

IFilterOutputStream::~IFilterOutputStream()
{

}
} // namespace stream