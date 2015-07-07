// SMTPSender.cpp: implementation of the SMTPSender class.
//
//////////////////////////////////////////////////////////////////////

//********************************************************************
/*
  Fast & Simple SMTP Class

  Author:
    christopher w. backen <immortal@cox.net>    
  Purpose:
    Simple smtp class with handy local ip and hostname functions
  ToDo:
    Attachments & UUEncode/Decode
*/
//********************************************************************
//*** Change History
//*** DEVELOPER             DATE        MODIFICATION
//*** 
//*** christopher w. backen 09.05.2002    Misc. updates and corrections
//*** christopher w. backen    08.28.2001    Bug fixes & code changes
//*** christopher w. backen    04.12.2001    Release
//***
//*** http://www.codeproject.com/internet/zsmtp.asp
//***
//********************************************************************



#include "stdafx.h"

#include "IInputStream.h"
#include "IOutputStream.h"
#include "PrintWriter.h"

#include "SMTPSender.h"


/// namespace stream
namespace stream
{

/// namespace net
namespace net
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


SMTPSender::SMTPSender(io::IInputStream* input, io::IOutputStream* output):m_input(input),m_output(output),m_printer(output)
{
}

SMTPSender::~SMTPSender()
{

}

bool SMTPSender::addRecipient(const std::string& email,const std::string& name)
{
    

    if(email == "")
		return false;

	std::auto_ptr<CRecipient> pRec = std::auto_ptr<CRecipient>(new CRecipient());

    pRec->setEmail(email);
	pRec->setName(name);

    Recipients.insert(Recipients.end(), pRec);

    return true;    
}


bool SMTPSender::disconnect()
{
    
    BYTE        sReceiveBuffer[4096];
    int            iLength = 0;
    int            iEnd = 0;


	m_printer.println("QUIT");
    
	iLength = m_input->read((uchar*)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd);
    
	iEnd += iLength;
    sReceiveBuffer[iEnd] = '\0';

    return true;
}

bool SMTPSender::send()
{
// verify sender email
    if (m_pcFromEmail == "") {
        
        return false;
    }

    BYTE        sReceiveBuffer[4096];
    int            iLength = 0;
    int            iEnd = 0;
    char        buf[4096];
	
    
// start
    strcpy(buf, "MAIL FROM: <");
    strcat(buf, m_pcFromEmail.c_str());
    
	m_printer.println(buf);
    
	iLength = m_input->read((uchar*)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd);
    
	iEnd += iLength;
    sReceiveBuffer[iEnd] = '\0';
// create message receipts

    for(unsigned int i=0;i<Recipients.size();i++) {
        
        strcpy(buf, "RCPT TO: <");
        strcat(buf, Recipients.at(i)->getEmail().c_str());
		strcat(buf, ">");
        
		
		m_printer.println(buf);

        iLength = m_input->read((uchar*)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd);

        iEnd += iLength;
        sReceiveBuffer[iEnd] = '\0';
    }
// init data
	m_printer.println("DATA");	
    iLength = m_input->read((uchar*)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd);
    
	iEnd += iLength;
    sReceiveBuffer[iEnd] = '\0';
// send header
	
    
// send body
	m_output->write((uchar*)m_pcMsgBody.c_str(), m_pcMsgBody.length());
    
// signal end    
	m_printer.println("");
	m_printer.println(".");
	
    
	iLength = m_input->read((uchar*)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd);
    
	iEnd += iLength;
    sReceiveBuffer[iEnd] = '\0';

    


    return true;

}

bool SMTPSender::connect()
{
   BYTE        sReceiveBuffer[4096];
    int            iLength = 0;
    int            iEnd = 0;
    

	iLength = m_input->read((uchar*)sReceiveBuffer+iEnd,sizeof(sReceiveBuffer)-iEnd);

	return true;
}


//**********************************************************************************
//*** Properties
//**********************************************************************************


std::string SMTPSender::getMessageBody() 
{
    return m_pcMsgBody;
}

unsigned const int SMTPSender::getRecipientCount()
{
    return (Recipients.size());
}


std::string SMTPSender::getSenderEmail() 
{

    return (m_pcFromEmail);
}

void SMTPSender::setMessageBody(const std::string& body)
{
    m_pcMsgBody = body;
}


void SMTPSender::setSenderEmail(const std::string& email)
{
    m_pcFromEmail = email;  
}


} /// namesapce net

} /// namespace stream
