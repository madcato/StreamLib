// DynamicClass.cpp: implementation of the DynamicClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "PropertyBag.h"
#include "Properties.h"

#include "DynamicClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

DynamicClass::DynamicClass()
{

}

DynamicClass::~DynamicClass()
{

}

void DynamicClass::invoke(const std::string& methodId, const Properties& inputParameters,Properties& outputParameters)
{
	invoke_internal(methodId,inputParameters,outputParameters);
}

} // namespace util

} // namespace stream
