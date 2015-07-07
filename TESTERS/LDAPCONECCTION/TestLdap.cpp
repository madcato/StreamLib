// TestLdap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "Blob.h"
#include "BolsaPropiedades.h"
#include "LdapConnection.h"
#include "FileUtil.h"

using namespace Stream;
using namespace std;

int Run1()
{
	try
	{
		CLdapConnection ldap("ldapscr.registradores.org","389");

		std::auto_ptr<std::list<CLdapResponse> > lista;
		


		lista = ldap.search(string("(cn=Daniel*)"),string("O=Servicio de Certificacion del Colegio de Registradores (SCR),C=es"),LS_SUBTREE);

		if(lista->size() <= 0)
		{
			cerr << "FAIL TEST: 1" << endl;
		}

		std::list<CLdapResponse>::iterator it = lista->begin();

		while(it != lista->end())
		{
			it->m_propStrings.get("cn").begin()->c_str();
			it++;
		}

		try
		{
			CLdapConnection ldap2("ldapssadcr.reasdgistradores.org","389");
			lista = ldap2.search(string("(cn=Daniel*)"),string("O=Servicio de Certificacion del Colegio de Registradores (SCR),C=es"),LS_SUBTREE);
			cerr << "FAIL TEST: 2" << endl;
			return -1;
		}catch(Exceptions::LdapException e)
		{
			string err = e.what();
			if(err != "Servidor inactivo")
			{
				cerr << "FAIL TEST: 10" << endl;
			}
		}

		try
		{
			CLdapConnection ldap2("","");
			lista = ldap2.search(string("(cn=Daniel*)"),string("O=Servicio de Certificacion del Colegio de Registradores (SCR),C=es"),LS_SUBTREE);
			cerr << "FAIL TEST: 7" << endl;
			return -1;
		}catch(Exceptions::LdapException e)
		{
			string err = e.what();
			if(err != "Servidor inactivo")
			{
				cerr << "FAIL TEST: 11" << endl;
			}
		}

		try
		{
			CLdapConnection ldap2("ldapscr.registradores.org","389");
			lista = ldap2.search(string(""),string("O=Servicio de Certificacion del Colegio de Registradores (SCR),C=es"),LS_SUBTREE);
			cerr << "FAIL TEST: 8" << endl;
			return -1;
		}catch(Exceptions::LdapException e)
		{
			string err = e.what();
			if(err != "Error de filtro")
			{
				cerr << "FAIL TEST: 12" << endl;
			}
		}

		try
		{
			CLdapConnection ldap3("ldapscr.registradores.org","380");
			lista = ldap3.search(string("(cn=Daniel*)"),string(""),LS_SUBTREE);
			cerr << "FAIL TEST: 9" << endl;
			return -1;
		}catch(Exceptions::LdapException e)
		{
			string err = e.what();
			if(err != "Servidor inactivo")
			{
				cerr << "FAIL TEST: 13" << endl;
			}
		}

		try
		{
			CLdapConnection ldap3("ldapscr.registradores.org","380");
			lista = ldap3.search(string("(cn=Daniel*)"),string("O=Servicio de Certificacion del Colegio de Registradores (SCR),C=es"),LS_SUBTREE);
			cerr << "FAIL TEST: 3" << endl;
			return -1;
		}catch(Exceptions::LdapException e)
		{
			string err = e.what();
			if(err != "Servidor inactivo")
			{
				cerr << "FAIL TEST: 13" << endl;
			}
		}
		cout << "TEST LDAP 1: OK" << endl;
	}catch(Exceptions::LdapException e)
	{
		cerr << "FAIL TEST: 6 " << e.what() << endl;
	}
	return 0;
}

int Run2()
{

try
{
	CLdapConnection ldap("ldapscr.registradores.org","389");

	std::auto_ptr<std::list<CLdapResponse> > lista;

	char* attributes[2] = {"usercertificate;binary",0};
	lista = ldap.search(string("(serialnumber=1042534547)"), // (serialnumber=1042534547)
		string("CN=Toño Muñoz Cañete-----25442761T,ST=Registro Mercantil de Pruebas,OU=Certificado Personal,OU=Certificado Externo,O=Servicio de Certificacion del Colegio de Registradores (SCR),C=es"),
		LS_SUBTREE,
		attributes);

	//
	if(lista->size() > 0)
	{

		Stream::Blob<char> blob = *(lista->begin()->m_propBlobs.get("usercertificate;binary").begin());

		std::string path = "d:\\temp\\certificate.cer";
		FileUtil::Buffer2File(blob,path);

		cout << "TEST LDAP 2: OK" << endl;
	}
	else
	{
		cerr << "FAIL TEST: 4 Certificate not found" << endl;
	}
}catch(Exceptions::StreamException e)
{
	cerr << "FAIL TEST: 5 " << e.what() << endl;
}

	return 0;
}

int main(int argc, char* argv[])
{
	 Run1();

	return Run2();
}