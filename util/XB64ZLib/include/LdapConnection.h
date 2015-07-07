// LdapConnection.h: interface for the LdapConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LDAPCONNECTION_H__1FA9C07B_6065_45D0_B699_273DFF9F5347__INCLUDED_)
#define AFX_LDAPCONNECTION_H__1FA9C07B_6065_45D0_B699_273DFF9F5347__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

	namespace exceptions
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
	} // namespace exceptions
/**
Provides the classes for implementing networking applications. 
*/
namespace net
{

enum ELdapScope
{
	LS_BASE,
	LS_ONELEVEL,
	LS_SUBTREE
};

/**
	Response form a query send to a ldap server.
*/
class LdapResponse
{
public:
	util::MultiPropertyBag<std::string,std::string> m_propStrings;
	util::MultiPropertyBag<std::string,stream::io::Blob<char> > m_propBlobs;

	virtual ~LdapResponse(){}

};

/**
	Connection to a ldap server.
	This class provides methods to send queries of data to a ldap server.
	<h3>Example of use</h3>
<code>
&nbsp;try<br>
&nbsp;{<br>
&nbsp;&nbsp;CLdapConnection ldap("ldapscr.registradores.org","389");<br>
<br>
&nbsp;&nbsp;std::auto_ptr<std::list<CLdapResponse> > lista;<br>
&nbsp;&nbsp;<br>
<br>
<br>
&nbsp;&nbsp;lista = ldap.search(string("(cn=Daniel*)"),string("O=Servicio de Certificacion del Colegio de Registradores (SCR),C=es"),LS_SUBTREE);<br>
<br>
&nbsp;&nbsp;if(lista->size() <= 0)<br>
&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;cerr << "FAIL LDAP:  << endl;<br>
&nbsp;&nbsp;}<br>
<br>
&nbsp;&nbsp;std::list<CLdapResponse>::iterator it = lista->begin();<br>
<br>
&nbsp;&nbsp;while(it != lista->end())<br>
&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;it->m_propStrings.get("cn").begin()->c_str();<br>
&nbsp;&nbsp;&nbsp;it++;<br>
&nbsp;&nbsp;}<br>
<br>
&nbsp;&nbsp;<br>
&nbsp;}catch(Exceptions::LdapException e)<br>
&nbsp;{<br>
&nbsp;&nbsp;cerr << "FAIL LDAP: " << e.what() << endl;<br>
&nbsp;}
</code>
*/
class LdapConnection  
{
public:
	/**
		Constructor. Opens a connection to the specified ldap server.
		@param server Name of the ldap server.
		@param port Port od the ldap server.
	*/
	LdapConnection(const std::string& server, const std::string& port);

	/**
		Constructor. Opens a connection to the specified ldap server with login.
		@param server Name of the ldap server.
		@param port Port od the ldap server.
		@param login Login name.
		@param password Password.
		@param secTimeOut Time out of the connection.
	*/
	LdapConnection(const std::string& server, const std::string& port,const std::string& login, std::string& password, long secTimeOut = -1);
	/**
		Destructor. Closes the connection.
	*/
	virtual ~LdapConnection();

	/**
		Perform a search.
		@param filter Atributtes to search.
		@param baseDB Distinguised Name that will be the base entry to search.
		@param scope Ldap scope.
		@param listAttr List of attributes that the server must return.
		@param attrOnly Set to true if it's not necessery to retrive the attibute values, only the attribute names. Default false.
		@return The data found.
	*/
	std::auto_ptr<std::list<LdapResponse> > search(const std::string& filter,const std::string& baseDN, ELdapScope scope = LS_SUBTREE,char* listAttr[] = 0,bool attrOnly = false);


private:
	LDAP* m_ldap;

	std::string m_server;
	std::string m_port;

	void PrepareConnection(const std::string& server, const std::string& port);
	void OpenConnection(long secTimeOut);
	unsigned long StreamScope2WinScope(ELdapScope ls);
};

} // namespace net

} // namespace stream
#endif // !defined(AFX_LDAPCONNECTION_H__1FA9C07B_6065_45D0_B699_273DFF9F5347__INCLUDED_)
