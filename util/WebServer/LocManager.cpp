// LocManager.cpp: implementation of the LocManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LocManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

REGISTER_CLASS(LocManager);

LocManager::LocManager()
{

}

LocManager::~LocManager()
{

}

std::auto_ptr<HTTPResponse> LocManager::executeQuery(std::auto_ptr<HTTPRequest> query)
{
	std::auto_ptr<HTTPResponse> res(new HTTPResponse);

	// Carga del fichero plantilla
	std::auto_ptr<HTMLTPage> page = GenericController::loadHTMLT("LocList.htmlt",true);

	vector<vector<string> > tabla = DB::queryTable("SELECT * FROM loc WHERE idLocParent IS NULL");
	// Asignación de valores a la plantilla
	page->setValue("PADRE","");
	page->setSequence("LISTA",tabla);
	page->setFlag("PONER_INPUT",false);

	// Preparación de la respuesta.
	res->status = 200;
	res->setBody(page->getPage());


	return res;
}


REGISTER_CLASS(LocManager1);

LocManager1::LocManager1()
{

}

LocManager1::~LocManager1()
{

}

std::auto_ptr<HTTPResponse> LocManager1::executeQuery(std::auto_ptr<HTTPRequest> query)
{
	std::auto_ptr<HTTPResponse> res(new HTTPResponse);

	// Carga del fichero plantilla
	std::auto_ptr<HTMLTPage> page = GenericController::loadHTMLT("LocList.htmlt",true);

	string id = query->getParameters().getProperty("id");
	vector<vector<string> > tabla = DB::queryTable("SELECT * FROM loc WHERE idLocParent = '" + id + "'");
	// Asignación de valores a la plantilla
	page->setSequence("LISTA",tabla);
	page->setFlag("PONER_INPUT",true);

	page->setValue("id",id);

	string locMain = "";
	do
	{
		if(locMain != "")
			locMain = "-" + locMain;
		vector<string> row = DB::queryRow("SELECT id,idLoc,idLocParent FROM loc WHERE id = '"+ id + "'");
		locMain = row[1] + locMain;
		id = row[2];
	}while(id != "{NULL}");
	
	page->setValue("PADRE",locMain);

	// Preparación de la respuesta.
	res->status = 200;
	res->setBody(page->getPage());


	return res;
}


REGISTER_CLASS(LocManager2);

LocManager2::LocManager2()
{

}

LocManager2::~LocManager2()
{

}

HTTPResponsePtr LocManager2::executeQuery(std::auto_ptr<HTTPRequest> query)
{
	std::auto_ptr<HTTPResponse> res(new HTTPResponse);

	// Insertar valor en la tabla

	string insert = "INSERT INTO loc VALUES('','"+query->getParameters().getProperty("newLoc") +
		"','" + query->getParameters().getProperty("parentLoc") + "')";

	DB::execute(insert);

	// Carga del fichero plantilla
	std::auto_ptr<HTMLTPage> page = GenericController::loadHTMLT("LocList.htmlt",true);

	string id = query->getParameters().getProperty("parentLoc");
	vector<vector<string> > tabla = DB::queryTable("SELECT * FROM loc WHERE idLocParent = '" + id + "'");
	// Asignación de valores a la plantilla
	page->setSequence("LISTA",tabla);

	page->setValue("id",id);

	string locMain = "";
	do
	{
		if(locMain != "")
			locMain = "-" + locMain;
		vector<string> row = DB::queryRow("SELECT id,idLoc,idLocParent FROM loc WHERE id = '"+ id + "'");
		locMain = row[1] + locMain;
		id = row[2];
	}while(id != "{NULL}");

	page->setFlag("PONER_INPUT",true);
	page->setValue("PADRE",locMain);

	// Preparación de la respuesta.
	res->status = 200;
	res->setBody(page->getPage());


	return res;
}