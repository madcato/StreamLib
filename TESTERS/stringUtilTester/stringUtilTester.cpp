// stringUtilTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stringUtil.h"

int main(int argc, char* argv[])
{
	try
	{
		 std::string xml = "<XML>\r\n<ARCHiVING  attribute=\"cosa\"  >\r\n<FILE	>\r\n\
			<PaTH>/path_relativo/fichero.dat</PATH>\r\n<TYPE>PUBLIC</TYPE>\r\n</FILE><FILE>\
			 <PATH>/path_relativo/subdir/fichero2.dat</PATH>\r\n<TYPE>PRIVATE</TYPE>\r\n<RECIPIENTS>\r\n<RECIPIENT>recipient1</RECIPIENT>\r\n><RECIPIENT>recipient2</RECIPIENT>\
			 </RECIPIENTS>\r\n</FiLE>\r\n</ARcHiVING  >\r\n</XML>";

		if(Stream::stringUtil::GetXMLData(xml,"/ARCHIVING/FILE:1/PATH") != "/path_relativo/subdir/fichero2.dat")
		{
			std::cerr << "FAIL TEST: 1" << std::endl;
		}

		try
		{
			Stream::stringUtil::GetXMLData(xml,"/ARCHIVING/FILE:2/PATH");
			std::cerr << "FAIL TEST: 2" << std::endl;
		}
		catch(Stream::Exceptions::StreamException e)
		{
		}

		std::string final = Stream::stringUtil::replace("1.3.4.234","23423","hola");
		if(final != "1.3.4.234")
		{
			std::cerr << "FAIL TEST: 9";
		}

		final = Stream::stringUtil::replace("1.3.4.234","234","");
		if(final != "1.3.4.")
		{
			std::cerr << "FAIL TEST: 2";
		}

		final = Stream::stringUtil::replace("1.3.4.234",".",",");
		if(final != "1,3,4,234")
		{
			std::cerr << "FAIL TEST: 3";
		}

		final = Stream::stringUtil::replace("1.3.4.234","234","hola");
		if(final != "1.3.4.hola")
		{
			std::cerr << "FAIL TEST: 4";
		}

		final = Stream::stringUtil::replace("1.3.4.234","","hola");
		if(final != "1.3.4.234")
		{
			std::cerr << "FAIL TEST: 5";
		}

		final = Stream::stringUtil::replace("","234","hola");
		if(final != "")
		{
			std::cerr << "FAIL TEST: 6";
		}

		final = Stream::stringUtil::replace("1...3.4.234",".",",");
		if(final != "1,,,3,4,234")
		{
			std::cerr << "FAIL TEST: 7";
		}
		final = Stream::stringUtil::replace("Hola mundo","Hola mundo","Hola mundo");
		if(final != "Hola mundo")
		{
			std::cerr << "FAIL TEST: 8";
		}

		std::cout << "TEST utilString: OK" << std::endl;
	}catch(Stream::Exceptions::XMLException e)
	{
		std::cerr << "TEST utilString: " << e.what();
	}


	 return 0;
}
