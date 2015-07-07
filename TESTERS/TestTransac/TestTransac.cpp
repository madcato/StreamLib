// TestTransac.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static auto_ptr<Connection> connection;


class T1 : public Thread
{
public:
	void run()
	{

		auto_ptr<Connection> connection3 = Connection::createConnection("Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser");
		//connection->startTransaction();
		

		auto_ptr<PreparedStatement> statement2 = connection->prepareStatement("INSERT INTO projects(nombre,descripcion) VALUES('prpep','puerto')");

		statement2->execute();

		
		//connection->commit();


	}
};

class T2 : public Thread
{
public:
	void run()
	{
		auto_ptr<Connection> connection2 = Connection::createConnection("Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser");
		//connection->startTransaction();

		try
		{
			auto_ptr<PreparedStatement> statement3 = connection->prepareStatement("INSERT INTO projects(id,nombre,descripcion) VALUES('1','prpep2','puerto2')");
			statement3->execute();
		//	connection->commit();
		
			
		}catch(...)
		{
		//	connection->rollback();
		}

	}
};

void TestMultiThread()
{

	connection = Connection::createConnection("Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser");

	T1 t1;
	T2 t2;

	t1.start();
	t2.start();

	t1.join();
	t2.join();

	connection->close();

}


void Run()
{
	try
	{
		connection = Connection::createConnection("Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser");

		connection->startTransaction();

		auto_ptr<PreparedStatement> statement = connection->prepareStatement("SELECT * FROM projects");

		auto_ptr<ResultSet> result = statement->executeQuery();

		result->moveFirst();

		while(!result->eof())
		{
			cout << result->getString("id") << endl;
			cout << result->getString("nombre") << endl;
			cout << result->getString("descripcion") << endl;
			
			result->moveNext();
		}

		
		result->close();


		auto_ptr<PreparedStatement> statement2 = connection->prepareStatement("INSERT INTO projects(nombre,descripcion) VALUES('prpep','puerto')");

		statement2->execute();


		try
		{
			auto_ptr<PreparedStatement> statement3 = connection->prepareStatement("INSERT INTO projects(id,nombre,descripcion) VALUES('1','prpep2','puerto2')");
			statement3->execute();
			connection->commit();
		
			
		}catch(...)
		{
			connection->rollback();
		}

		connection->close();
		
		
		

		
	}catch(stream::exceptions::StreamException* e)
	{
		cout << e->what() << endl;
	}
}

int main(int argc, char* argv[])
{
CoInitialize(0);
	//Run();
	DiffTime a;

	a.start();
	auto_ptr<Connection> connection1 = Connection::createConnection("Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser");
	cout << sstring(a.finish()) << endl;

	connection1->close();
	delete connection1.release();
	a.start();
	auto_ptr<Connection> connection2 = Connection::createConnection("Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser");
	cout << sstring(a.finish()) << endl;

	connection2->close();
	delete connection2.release();
	a.start();
	auto_ptr<Connection> connection3 = Connection::createConnection("Provider=SQLOLEDB;Database=TODOlist;Server=localhost;uid=todouser;pwd=todouser");
	cout << sstring(a.finish()) << endl;

	connection3->close();
	delete connection3.release();
	a.start();
	Sleep(100);
	cout << sstring(a.finish()) << endl;


	TestMultiThread();

	delete connection.release();
CoUninitialize();
	return 0;
}
