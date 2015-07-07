// IFilterInputStream.cpp: implementation of the IFilterInputStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IInputStream.h"
#include "IFilterInputStream.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace stream
{
using namespace io;
IFilterInputStream::IFilterInputStream(IInputStream* input):m_input(input)
{

}

IFilterInputStream::~IFilterInputStream()
{

}

} // namespace stream