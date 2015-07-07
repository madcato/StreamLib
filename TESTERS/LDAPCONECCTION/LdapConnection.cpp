// LdapConnection.cpp: implementation of the CLdapConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "memory_stream.h"
#include "Blob.h"
#include "BolsaPropiedades.h"

#include "LdapConnection.h"

#include <atlbase.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace Stream
{

namespace Exceptions
{
LdapException::LdapException():StreamException(LdapGetLastError(),ldap_err2string(LdapGetLastError()))
{
	
}
LdapException::LdapException(unsigned long result):StreamException(result,ldap_err2string(result))
{
	
}
} // namespace Exceptions
CLdapConnection::CLdapConnection(const std::string& server, const std::string& port)
{
	m_server = server;
	m_port = port;
	PrepareConnection(m_server,m_port);


}

CLdapConnection::CLdapConnection(const std::string& server, const std::string& port,const std::string& login, std::string& password, long secTimeOut)
{

	PrepareConnection(server,port);

	ULONG result = ldap_bind_s(m_ldap,const_cast<char*>(login.c_str()),const_cast<char*>(password.c_str()),LDAP_AUTH_SIMPLE);
  
	if(result != LDAP_SUCCESS)
		throw Exceptions::LdapException(result);

	OpenConnection(secTimeOut);

}


CLdapConnection::~CLdapConnection()
{
	ldap_unbind(m_ldap);
}

void CLdapConnection::OpenConnection(long secTimeOut)
{
	LDAP_TIMEVAL lt;
	lt.tv_sec = secTimeOut;
	lt.tv_usec = 0;
	ULONG result = ldap_connect(m_ldap,&lt);
  
	if(result != LDAP_SUCCESS)
		throw Exceptions::LdapException(result);

}
void CLdapConnection::PrepareConnection(const std::string& server, const std::string& port)
{
	USES_CONVERSION;
	m_ldap = 0;
	m_ldap = ldap_init((char*)A2W((server + ":" + port).c_str()),389);
	
  
	if(!m_ldap)
		throw Exceptions::LdapException();

}

unsigned long CLdapConnection::StreamScope2WinScope(ELdapScope ls)
{
	switch(ls)
	{
	case LS_BASE:
		return LDAP_SCOPE_BASE;
	case LS_ONELEVEL:
		return LDAP_SCOPE_ONELEVEL;
	case LS_SUBTREE:
		return LDAP_SCOPE_SUBTREE;
	};

	return 0;
}

std::auto_ptr<std::list<CLdapResponse> > CLdapConnection::search(const std::string& filter,const std::string& baseDN, ELdapScope scope,char* listAttr[],bool attrOnly)
{
	std::auto_ptr<std::list<CLdapResponse> > list_prop(new std::list<CLdapResponse>);
	

	// Initialize return value to 0.
	LDAPMessage *pMsg = 0;

	
	// Perform the search request.
	ULONG result = ldap_search_s (m_ldap,
			const_cast<char*>(baseDN.c_str()),
			StreamScope2WinScope(scope),
			const_cast<char*>(filter.c_str()),
			listAttr,
			attrOnly,
			&pMsg);

	// Convert error code and cleanup pMsg, if necessary.
	if (result != LDAP_SUCCESS)
	{

		if (pMsg != 0)
		  ldap_msgfree(pMsg);

		if(result != LDAP_SUCCESS)
			throw Exceptions::LdapException(result);
	}

	else
	{
		// Process the search results.
		LDAPMessage* ptMsg;
  
		/*if(ptMsg != 0)
		{
			do
			{
				CBolsaPropiedades prop;

			}while((ptMsg = ldap_next_entry(m_ldap,pMsg)) == 0);
		}*/

		char        *attribute, **values; 
		berval** binaryValues;
	    
		BerElement  *ber;
		


		for(ptMsg = ldap_first_entry( m_ldap, pMsg );
			ptMsg != 0;
			ptMsg = ldap_next_entry(m_ldap,ptMsg))
		{
				CLdapResponse prop;
			for (attribute = ldap_first_attribute(m_ldap,ptMsg,&ber);
				attribute != 0;
				attribute = ldap_next_attribute(m_ldap,ptMsg,ber))
			{
				if(strstr(attribute,";binary") == 0)
				{
					/* Get values.  Assumes all values are strings. */
					if ((values = ldap_get_values( m_ldap, ptMsg, attribute)) != 0 )
					{
						for (int i = 0; values[i] != 0; i++ )
							prop.m_propStrings.put(attribute,values[i]);
						ldap_value_free( values );
					}
				}
				else
				{


					/* Get values.  Assumes all values are binary data. */
					if ((binaryValues = ldap_get_values_len( m_ldap, ptMsg, attribute)) != 0 )
					{
						for (int i = 0; binaryValues[i] != 0; i++ )
						{
							Stream::Blob<char> blob;
							char* data = new char[binaryValues[i]->bv_len];
							memcpy(data,binaryValues[i]->bv_val,binaryValues[i]->bv_len);
							blob.setData(auto_array_ptr<char>(data,binaryValues[i]->bv_len),binaryValues[i]->bv_len);
							prop.m_propBlobs.put(attribute,blob);
						}
						ldap_value_free_len( binaryValues );
					}					
				}
				ldap_memfree( attribute );
			}
			ber_free(ber, 0);
			list_prop->push_back(prop);
		}



		// Free the results when complete.
		if (pMsg != 0) ldap_msgfree(pMsg);
	}


	return list_prop;
}


} // namespace Stream