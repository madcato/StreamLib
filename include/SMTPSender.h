// SMTPSender.h: interface for the Smtp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMTP_H__C66CDD0A_4F6F_4465_BAD6_8FA531785B5D__INCLUDED_)
#define AFX_SMTP_H__C66CDD0A_4F6F_4465_BAD6_8FA531785B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/// namespace stream
namespace stream
{

/// namespace net
namespace net
{

const int DEFAULT_PROTOCOL = 0;
const int NO_FLAGS = 0;

/**
	Utility for sending emails

	Example code:<br>
<code>
	try<br>
	{<br>
		Socket sock("smtp.ochoa.es","25");<br>
<br>
		SMTPSender sender(sock.getInputStream(),sock.getOutputStream());<br>
<br>
		sender.connect();<br>
<br>
<br>
		// Send first email<br>
		sender.addRecipient("dvela@ochoa.es","Daniel");<br>
		sender.addRecipient("MadCat@0z0ne.com","MadCat");<br>
<br>
		Blob<char> blob = FileUtil::File2Buffer("C:\\me.eml");<br>
<br>
		sender.setMessageBody(blob);<br>
<br>
		sender.setSenderEmail("dvela@ochoa.es");<br>
<br>
		sender.send();<br>
<br>
<br>
		// Send second email<br>
		sender.addRecipient("dvela@ochoa.es","Daniel");<br>
		sender.addRecipient("MadCat@0z0ne.com","MadCat");<br>
<br>
		blob = FileUtil::File2Buffer("C:\\me2.eml");<br>
<br>
		sender.setMessageBody(blob);<br>
<br>
		sender.setSenderEmail("dvela@ochoa.es");<br>
<br>
		sender.send();<br>
<br>
		sender.disconnect();<br>
	}catch(stream::exceptions::StreamException* e)<br>
	{<br>
		cerr << e->what() << endl;<br>
	}<br>
</code>
*/
class SMTPSender  
{
public:        
    SMTPSender(io::IInputStream* input, io::IOutputStream* m_output);
    virtual ~SMTPSender();
    bool    addRecipient(const std::string& email,const std::string& name = "");
    
	const unsigned int    getRecipientCount();    
	std::string getMessageBody();    
    std::string getSenderEmail();
    std::string getSenderName();
    
	bool connect();
    bool    send();
	bool disconnect();
    void    setMessageBody(const std::string& body);
    
    void    setSenderEmail(const std::string& email);    
    
    

private:
    class CRecipient
    {
    public:
        CRecipient() 
        { 
            m_pcEmail = "";
        };
        CRecipient& operator=(const CRecipient& src)
        {
            
            m_pcEmail = src.m_pcEmail;
            
            return (*this);
        }
        virtual ~CRecipient()
        {
            
        }
		std::string getEmail()
        {
            return m_pcEmail;
        }
        void setEmail(const std::string& email)
        {   
            m_pcEmail = email;            
        }
		std::string getName()
        {
            return m_pcName;
        }
        void setName(const std::string& name)
        {   
            m_pcName = name;
        }
    private:
		std::string m_pcEmail;
		std::string m_pcName;
    };

	

    
	std::string m_pcFromEmail;
    std::string m_pcSubject;
    std::string m_pcMsgBody;

    std::vector<std::auto_ptr<CRecipient> > Recipients;
    
	io::IInputStream* m_input;
	io::IOutputStream* m_output;
	io::PrintWriter m_printer;
};

} /// namesapce net

} /// namespace stream

#endif // !defined(AFX_SMTP_H__C66CDD0A_4F6F_4465_BAD6_8FA531785B5D__INCLUDED_)
