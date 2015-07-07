// TasEncoderTasDecoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include <Stream.h>

using namespace std;
using namespace Stream;

int main(int argc, char* argv[])
{
try
{
	CFileOutputStream file_out("d:\\temp\\tas\\file.tas.txt");

	CTasEncoder tasEncoder(&file_out);

	CFileInputStream file1("D:\\temp\\tas\\Stream.h");
	CFileInputStream file2("D:\\temp\\tas\\TasEncoder.cpp");

	tasEncoder.putData("D:\\temp\\tas\\Stream.h",&file1);
	tasEncoder.putData("D:\\temp\\tas\\TasEncoder.cpp",&file2);
	//tas.putFile("d:\\Persiguiendo_a_Amy (en castellano).avi");

	file_out.close();


	CFileInputStream file_in("d:\\temp\\tas\\file.tas.txt");
	CTasDecoder tasDecoder(&file_in);

	IInputStream* data;
	std::string identificator;
	
	auto_array_ptr<unsigned char> buffer(new unsigned char[65536]);
	while((identificator = tasDecoder.getData(data)) != "")
	{
		string path = FileUtil::RemoveFileNameFromPath(identificator);
		CFileOutputStream file_out((string("D:\\temp\\tas\\tas.out\\") + FileUtil::ExtractFileNameFromPath(identificator)).c_str());


		int readed = 0;
		while((readed = data->read(buffer.get(),65536)) > 0)
		{
			file_out.write(buffer.get(),readed);
		}

	}

}catch(Exceptions::StreamException* e)
{
	cerr << e->what() << endl;
}
	return 0;
}
