// TestMIME.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{

	CMimeMessage mail;

    // Initialize message header
    mail.SetDate(); // set 'Date' field to the current time
    mail.SetVersion();
    mail.SetFrom("sender@local.com");
    mail.SetTo("recipient1@server1.com,Nick Name <recipient2@server1.com>,\"Nick Name\" <recipient3@server3.com>");
    mail.SetCc("recipient4@server4.com");
    mail.SetSubject("Test message");
    mail.SetFieldValue("X-Priority", "3 (Normal)"); // extended field
    mail.SetFieldValue("X-My-Field", "My value");   // user-defined field

    // Initialize body part header
    mail.SetContentType("multipart/mixed");
    // generate a boundary delimeter automatically
    // if the parameter is NULL
    mail.SetBoundary(NULL);

    // Add a text body part
    // Content-Type is not specified, so the default
    // value "text/plain" is implicitly used
    // Content-Transfer-Encoding is not specified
    // so the default value "7bit" is implicitly used
    /*CMimeBody* pBp = mail.CreatePart();
    pBp->SetText("Hi, there");  // set the content of the body part

    // Add a file attachment body part
    pBp = mail.CreatePart();
//    pBp->SetContentDescription("enclosed photo");
    pBp->SetTransferEncoding("base64");
    // if Content-Type is not specified, it'll be
    // set to "image/jpeg" by ReadFromFile()
    pBp->ReadFromFile("C:\\winzip.log"); */

    // Generate a simple message
    CMimeMessage mail2;
    mail2.SetFrom("abc@abc.com");
    mail2.SetTo("abc@abc.com");
    mail2.SetSubject("This is an attached message");
    mail2.SetText("Content of attached message.\r\n");

    // Attach the message
    CMimeBody* pBp = mail.CreatePart();
//    pBp->SetContentDescription("enclosed message");
    pBp->SetTransferEncoding("7bit");
    // if Content-Type is not specified, it'll be
    // set to "message/rfc822" by SetMessage()
    pBp->SetMessage(&mail2); 

    // Add an embeded multipart
    pBp = mail.CreatePart();
    pBp->SetContentType("multipart/alternative");
    pBp->SetBoundary("embeded_multipart_boundary");
    CMimeBody *pBpChild = pBp->CreatePart();
    pBpChild->SetText("Content of Part 1\r\n");
    pBpChild = pBp->CreatePart();
    pBpChild->SetText("Content of Part 2\r\n");

    // Store the message to buffer    
    // fold the long lines in the headers
    CMimeEnvironment::SetAutoFolding(true); 
    
    
    Blob<char> blob = mail.Store();

	FileUtil::Buffer2File(blob,"C:\\me.eml");
	

	return 0;
}
