// TestB64.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void DumBlob(stream::io::Blob<unsigned char>& blob)
{
	for(int i = 0 ; i < blob.length() ; i++)
	{
		cout << blob[i];
	}
}

int main(int argc, char* argv[])
{
	int capacity = 10090;
	int rest = capacity % 4096;
	if(rest)
		capacity += 4096 - (rest);

	rest = capacity % 4096;
	if(rest)
		capacity += 4096 - (rest);



	std::string path = "c:\\temp\\htmlt\\";
	

	io::Blob<char> finalBlob;
	finalBlob.setData(HTMLIncluder::makeIncludes(FileUtil::File2Buffer(path + "base.htmlt").toString(),path));


	FileUtil::Buffer2File(finalBlob,path + "final.html");

	/*std::string str = stream::net::HTTPResponse::unscape("http://labs.google.com/personalized/search?q=prueba&tid=1&in=58%2C61%2C1222%2C62%2C64%2C65&hm=file%253A%2F%2F%2FC%253A%2FDocuments%252520and%252520Settings%2Fvelad%2FMis%252520documentos%2Fhome.htm");


	stream::net::HTTPQuery query;

	query.url = "http://labs.google.com/personalized/search?q=prueba&tid=1&in=58%2C61%2C1222%2C62%2C64%2C65&hm=file%253A%2F%2F%2FC%253A%2FDocuments%252520and%252520Settings%2Fvelad%2FMis%252520documentos%2Fhome.htm";

	util::Properties prop = query.getParameters();


	std::vector<std::string> vec = prop.propertyNames();

	std::vector<std::string>::iterator it = vec.begin();

	while(it != vec.end())
	{
		cout << *it << ": " << prop.getProperty(*it) << endl;
		it++;
	}*/

	


/*	B64 b64(OPEN_FOR_ENCODING);

	unsigned char* buffer = new unsigned char[10];

	strcpy((char*)buffer,"Hola pepe23");

	b64.Init();
	stream::Blob<unsigned char> blob = b64.Update(buffer,strlen((char*)buffer) - 4);
	cout << blob.get();
	blob = b64.Update(buffer + (strlen((char*)buffer) - 4),4);
	cout << blob.get();
	blob = b64.Finish();
	cout << blob.get() << endl;

	B64 b64d(OPEN_FOR_DECODING);

	b64d.Init();
	blob = b64d.Update((unsigned char*)"SG9sYSBQZXBlMTI=",strlen("SG9sYSBQZXBlMTI=")-6);
	DumBlob(blob);	
	blob = b64d.Update((unsigned char*)"SG9sYSBQZXBlMTI=" + strlen("SG9sYSBQZXBlMTI=")-6,6);
	DumBlob(blob);	
	blob = b64d.Finish();
	DumBlob(blob);
	cout << endl;

	

	B64OutputStream b64(OPEN_FOR_ENCODING,auto_ptr<IOutputStream>(new ConsoleOutputStream()));
*/

/*	io::FilterOutputStream b64(auto_ptr<io::IDataProcessor>(new io::B64(io::OPEN_FOR_ENCODING)),new io::ConsoleOutputStream());

	b64.write('H');
	b64.write('o');
	b64.write('l');
	b64.write('a');
	b64.close();


	
/*
	B64OutputStream b64d(OPEN_FOR_DECODING,auto_ptr<IOutputStream>(new ConsoleOutputStream()));


	b64d.write('S');
	b64d.write('G');
	b64d.write('9');
	b64d.write('s');
	b64d.close();

	/*
	B64OutputStream b64d2(OPEN_FOR_DECODING,auto_ptr<IOutputStream>(new ConsoleOutputStream()));


	b64d2.write((unsigned char*)"SG9",3);
	b64d2.write((unsigned char*)"sYSBwZ",6);
	b64d2.write((unsigned char*)"XBlMj",5);
	b64d2.write('M');
	b64d2.write('=');
	b64d2.close();
*/

/*	io::FilterInputStream b64input(auto_ptr<io::IDataProcessor>(new io::B64(io::OPEN_FOR_DECODING)),new io::FileInputStream("c:\\_NavCClt.Log.b64"));


	util::auto_array_ptr<unsigned char> buffer(1000);

	while(b64input.available())
	{
		cout << (char)b64input.read();
	}

/*
	

	B64InputStream b64input2(OPEN_FOR_ENCODING,auto_ptr<IInputStream>(new FileInputStream("c:\\hola.txt")));


	readed = b64input2.read(buffer.get(),1000);
	blob2.setData(buffer,readed);

	DumBlob(blob2);
	readed = b64input2.read(buffer.get(),1000);
	blob2.setData(buffer,readed);

	DumBlob(blob2);
*/	
	return 0;
}
