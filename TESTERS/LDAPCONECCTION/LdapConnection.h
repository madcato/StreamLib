// LdapConnection.h: interface for the CLdapConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LDAPCONNECTION_H__1FA9C07B_6065_45D0_B699_273DFF9F5347__INCLUDED_)
#define AFX_LDAPCONNECTION_H__1FA9C07B_6065_45D0_B699_273DFF9F5347__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Stream
{
	namespace Exceptions
	{
	class LdapException : public StreamException
	{
	public:
		LdapException();
		LdapException(unsigned long result);
		virtual ~LdapException()
		{
			
		}
	};
	} // namespace Exceptions

enum ELdapScope
{
	LS_BASE,
	LS_ONELEVEL,
	LS_SUBTREE
};

class CLdapResponse
{
public:
	CMultiBolsaPropiedades<std::string,std::string> m_propStrings;
	CMultiBolsaPropiedades<std::string,Stream::Blob<char> > m_propBlobs;

	virtual ~CLdapResponse(){}

};
class CLdapConnection  
{
public:
	
	CLdapConnection(const std::string& server, const std::string& port);
	CLdapConnection::CLdapConnection(const std::string& server, const std::string& port,const std::string& login, std::string& password, long secTimeOut = -1);
	virtual ~CLdapConnection();

	std::auto_ptr<std::list<CLdapResponse> > search(const std::string& filter,const std::string& baseDN, ELdapScope scope = LS_SUBTREE,char* listAttr[] = 0,bool attrOnly = false);


private:
	LDAP* m_ldap;

	std::string m_server;
	std::string m_port;

	void PrepareConnection(const std::string& server, const std::string& port);
	void OpenConnection(long secTimeOut);
	unsigned long StreamScope2WinScope(ELdapScope ls);
};

} // namespace Stream
#endif // !defined(AFX_LDAPCONNECTION_H__1FA9C07B_6065_45D0_B699_273DFF9F5347__INCLUDED_)
