// TestClass.cpp: implementation of the TestClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

REGISTER_CLASS(TestClass);

TestClass::TestClass()
{

}

TestClass::~TestClass()
{

}

std::auto_ptr<HTTPResponse> TestClass::executeQuery(std::auto_ptr<HTTPRequest> query)
{
	std::auto_ptr<HTTPResponse> res(new HTTPResponse);

	// Carga del fichero plantilla
	std::auto_ptr<HTMLTPage> page = GenericController::loadHTMLT("TestClass.htmlt",true);

	// Asignación de valores a la plantilla
	page->setValue("VARIABLE",query->getParameters().getProperty("nombre"));

	// Preparación de la respuesta.
	res->status = 200;
	res->setBody(page->getPage());


	return res;
}