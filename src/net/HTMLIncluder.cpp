// HTMLIncluder.cpp: implementation of the HTMLIncluder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"

#include "HTMLIncluder.h"

#include "memory_stream.h"
#include "BLOB.h"
#include "FileUtil.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace exceptions
namespace net
{

HTMLIncluder::HTMLIncluder()
{
}

HTMLIncluder::~HTMLIncluder()
{

}

std::string HTMLIncluder::makeIncludes(const std::string& pageData,const std::string& pathBase)
{
	std::string page = pageData;
	int i = 0;
	while(true)
	{
		// Mientras encontremos '#include "..."' continuamos 
		size_t ini_position = page.find("#include");

		if(ini_position == std::string::npos)
		{
			return page;
		}

		size_t middle_position = page.find("\"",ini_position+1);
		if(middle_position == std::string::npos)
		{
			return page;
		}

		size_t end_position = page.find("\"",middle_position+1);

		if(end_position == std::string::npos)
		{
			return page;
		}


		std::string fileName = page.substr(middle_position + 1, (end_position - middle_position) - 1 );

		page.replace(ini_position,(end_position - ini_position) + 1,(std::string)util::FileUtil::File2Buffer(pathBase + fileName));

		if(i++ > 100)
		{
			// aquí evitamos las inserciones infinitas...lanzamos una excepción.

			throw new exceptions::HMTLException(-2,"<br><h2>Infinite includes in...</h2><br><br>" + page.substr(0,4000));
			return page;
		}

	}
}

} // namespace net

} // namespace stream
