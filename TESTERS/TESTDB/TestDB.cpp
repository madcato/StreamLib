// TestDB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{


	stream::zip::GZIP gzip(stream::zip::OPEN_FOR_COMPRESS);

	io::Blob<unsigned char> buffer;

	gzip.Init();

	FILE* file = fopen("C:\\pru.gz","wb");
	buffer = gzip.Update((unsigned char*)"Hoal chavalote",13);
	fwrite(buffer.get(),buffer.length(),1,file);
	buffer = gzip.Finish();
	fwrite(buffer.get(),buffer.length(),1,file);

	fclose(file);

	/*stream::zip::GZOutputStream fileOut("C:\\pru.gz");

	fileOut.write((unsigned char*)"Hoal chavalote",14);

	fileOut.close();*/



	/*io::Blob<char> buff = stream::util::FileUtil::File2Buffer("C:\\pru.gz");

	stream::zip::GZIP gzip2(stream::zip::OPEN_FOR_UNCOMPRESS);

	gzip2.Init();
	
	buffer = gzip2.Update((unsigned char*)buff.get(),buff.length()-10);
	buffer = gzip2.Update((unsigned char*)buff.get()+buff.length()-10,10);
	buffer = gzip2.Finish();*/


	io::FileInputStream fileIn("c:\\pru.gz");

	zip::GZIPInputStream gz(zip::OPEN_FOR_UNCOMPRESS,&fileIn);

	while(gz.available())
	{
		/*unsigned char buffer4[100];
		int readed = gz.read(buffer4,100);*/
		int c = gz.read();
	}



	/*

	CoInitialize(NULL);

	LiteLog* log = util::LiteLog::getInstance();
	
	
	
	log->traceOn("CON|HOla consola|5","Prueba");
	log->trace(string("CON|HOla consola|5"));


	std::string va = SystemInfo::getIEVersion();

	std::string s = SystemInfo::readRegistryString("HKEY_CURRENT_USER\\Software\\HermesWeb\\Configuracion\\PathDocs");
	try
	{
		auto_ptr<Connection> connection = Connection::createConnection("DSN=BakeMail");

		auto_ptr<PreparedStatement> statement = connection->prepareStatement("SELECT * FROM servers WHERE id_server >= ?");

		statement->setLong(1,3);


		auto_ptr<ResultSet> result = statement->executeQuery();

		result->moveFirst();

		while(!result->eof())
		{
			cout << result->getString("server") << endl;
			cout << result->getString("port") << endl;
			cout << result->getString("user") << endl;
			cout << result->getString("password") << endl;
			cout << result->getString("check2") << endl << endl;

			result->moveNext();
		}

		result->close();


		auto_ptr<PreparedStatement> statement2 = connection->prepareStatement("INSERT INTO servers VALUES('','servidor','puerto','usuario','password12','not check')");

		statement2->execute();


		auto_ptr<PreparedStatement> statement3 = connection->prepareStatement("INSERT INTO servers VALUES('','servidor','?','usuario','password12','not check')");
		for(int i = 30 ; i < 32 ; i++)
		{
			statement3->setLong(1,i);

			statement3->execute();
		}


		connection->close();
	}catch(exceptions::StreamException* e)
	{
		cout << e->what() << endl;
	}

	CoUninitialize();*/
	return 0;
}
