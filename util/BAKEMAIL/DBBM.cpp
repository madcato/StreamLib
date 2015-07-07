// DBBM.cpp: implementation of the DBBM class.
//
//////////////////////////////////////////////////////////////////////


#include "DBBM.h"

#include <iostream>
#import "C:\Archivos de Programa\Archivos Comunes\SYSTEM\ADO\MSADO15.DLL" no_namespace rename("EOF", "adoEOF" )

inline void TESTHR(HRESULT x) {if FAILED(x) _com_issue_error(x);};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

std::string prepareString(const std::string& str)
{
	std::string resultStr;

	for(int i = 0 ; i < str.length() ; i++)
	{
		switch(str[i])
		{
		case 0:
			resultStr += "\\0";
			break;
		case '\'':
			resultStr += "\\'";
			break;
		case '"':
			resultStr += "\\\"";
			break;
		case '\b':
			resultStr += "\\b";
			break;
		case '\n':
			resultStr += "\\n";
			break;
		case '\r':
			resultStr += "\\r";
			break;
		case '\t':
			resultStr += "\\t";
			break;
		case 26: // Ctrl+z
			resultStr += "\\Z";
			break;
		case '\\':
			resultStr += "\\\\";
			break;
		case '%':
			resultStr += "\\%";
			break;
		case '_':
			resultStr += "\\_";
			break;
		default:
			resultStr += str[i];
			break;
		}
	}

	return resultStr;
}

DBBM::DBBM()
{
	
}

DBBM::~DBBM()
{

}

_ConnectionPtr m_pConnection = 0;

void DBBM::Init(const std::string& conf)
{
	try
	{
		TESTHR(m_pConnection.CreateInstance(__uuidof(Connection)));
		m_pConnection->Open(conf.c_str(),"","",adConnectUnspecified);
	}
	catch(_com_error e)
	{
		std::cerr << "ErrorMessage: " << e.ErrorMessage() << std::endl;
		std::cerr << "Description: " << (char*)e.Description() << std::endl;
		std::cerr << "Source: " << (char*)e.Source() << std::endl;
	}

}

std::list<Account> DBBM::ListAccounts()
{
	std::list<Account> listAccounts;

	_RecordsetPtr adoRs = 0;

	try
	{
		_variant_t InVar;

		TESTHR(adoRs.CreateInstance(__uuidof(Recordset)));
		adoRs->Open( "select * from servers WHERE check1 = 2",					
					_variant_t((IDispatch *)m_pConnection,true),
					adOpenForwardOnly, adLockReadOnly, adCmdText );

		
		
		while(!adoRs->adoEOF)
		{
			Account a;

			a.m_id_server = (_bstr_t)adoRs->Fields->GetItem("id_server")->Value;
			a.m_server = (_bstr_t)adoRs->Fields->GetItem("server")->Value;
			a.m_port = (_bstr_t)adoRs->Fields->GetItem("port")->Value;
			a.m_user = (_bstr_t)adoRs->Fields->GetItem("user")->Value;
			a.m_password= (_bstr_t)adoRs->Fields->GetItem("password")->Value;
			a.m_eliminar = (long)adoRs->Fields->GetItem("eliminar")->Value;

			
			listAccounts.push_back(a);

			adoRs->MoveNext();

		}

		adoRs->Close();
	}
	catch(_com_error e)
	{
		std::cerr << "ErrorMessage: " << e.ErrorMessage() << std::endl;
		std::cerr << "Description: " << (char*)e.Description() << std::endl;
		std::cerr << "Source: " << (char*)e.Source() << std::endl;
		if(adoRs)
		{
			adoRs->Close();
			adoRs = NULL;
		}

	

	}

	return listAccounts;
}

bool DBBM::CheckDownloaded(const std::string& id_server,const std::string& uidl)
{
	_RecordsetPtr adoRs = 0;
	try
	{
		_variant_t InVar;

		TESTHR(adoRs.CreateInstance(__uuidof(Recordset)));
		adoRs->Open( (std::string("SELECT id_down FROM downloaded WHERE "
					"uidl LIKE '") + uidl + "' AND id_server = " + id_server).c_str(),
					_variant_t((IDispatch *)m_pConnection,true),
					adOpenForwardOnly, adLockReadOnly, adCmdText );

		
		
		if(adoRs->adoEOF)
		{
			adoRs->Close();
			return false;
		}
		else
		{
			adoRs->Close();
			return true;
		}
	}
	catch(_com_error e)
	{
		std::cerr << "ErrorMessage: " << e.ErrorMessage() << std::endl;
		std::cerr << "Description: " << (char*)e.Description() << std::endl;
		std::cerr << "Source: " << (char*)e.Source() << std::endl;
		if(adoRs)
		{
			adoRs->Close();
			adoRs = NULL;
		}

	//m_spObjectContext->SetAbort();

	}

	return false;
}


void DBBM::InsertDownloaded(const std::string& id_server,const std::string& uidl,const std::string& path)
{
	_RecordsetPtr adoRs = 0;
	try
	{
		_variant_t InVar;

		TESTHR(adoRs.CreateInstance(__uuidof(Recordset)));
		adoRs->Open( (std::string("INSERT INTO downloaded VALUES(0,") + id_server + ",'" + uidl + "','"+ prepareString(path) +"',CURRENT_DATE(),10)").c_str(),
					_variant_t((IDispatch *)m_pConnection,true),
					adOpenForwardOnly, adLockPessimistic, adCmdText );

	}
	catch(_com_error e)
	{
		std::cerr << "ErrorMessage: " << e.ErrorMessage() << std::endl;
		std::cerr << "Description: " << (char*)e.Description() << std::endl;
		std::cerr << "Source: " << (char*)e.Source() << std::endl;
	//m_spObjectContext->SetAbort();

	}


}

void DBBM::DeleteUidls(const std::string& id_server,const std::list<std::string>& listUidl)
{
	_RecordsetPtr adoRs = 0;
	try
	{
		_variant_t InVar;

		std::list<std::string>::const_iterator it = listUidl.begin();

		while(it != listUidl.end())
		{
			TESTHR(adoRs.CreateInstance(__uuidof(Recordset)));
			adoRs->Open( (std::string("DELETE FROM downloaded WHERE "
					"uidl LIKE '") + *it + "' AND id_server = " + id_server).c_str(),
					_variant_t((IDispatch *)m_pConnection,true),
					adOpenForwardOnly, adLockPessimistic, adCmdText );

			it++;
		}
	}
	catch(_com_error e)
	{
		std::cerr << "ErrorMessage: " << e.ErrorMessage() << std::endl;
		std::cerr << "Description: " << (char*)e.Description() << std::endl;
		std::cerr << "Source: " << (char*)e.Source() << std::endl;
	//m_spObjectContext->SetAbort();

	}


}
