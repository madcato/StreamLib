// DBBM.h: interface for the DBBM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_H__677E6FB9_205E_448F_A8FD_88F7D72679F7__INCLUDED_)
#define AFX_DB_H__677E6FB9_205E_448F_A8FD_88F7D72679F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <list>


class Account
{
public:
	std::string m_id_server;
	std::string m_server;
	std::string m_port;
	std::string m_user;
	std::string m_password;
	long m_eliminar;
};

class DBBM  
{
public:
	DBBM();
	virtual ~DBBM();

	static void Init(const std::string&);

	static std::list<Account> ListAccounts();
	static bool CheckDownloaded(const std::string& id_server,const std::string& uidl);	
	static void InsertDownloaded(const std::string& id_server,const std::string& uidl,const std::string& path);
	static void DeleteUidls(const std::string& id_server,const std::list<std::string>& listUidl);

private:

};

#endif // !defined(AFX_DB_H__677E6FB9_205E_448F_A8FD_88F7D72679F7__INCLUDED_)
