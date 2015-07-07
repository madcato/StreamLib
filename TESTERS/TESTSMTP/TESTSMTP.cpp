// TESTSMTP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	try
	{
		Socket sock("smtp.ochoa.es","25");

		

		SMTPSender sender(sock.getInputStream(),sock.getOutputStream());
		
		sender.connect();

		// Send first email
		sender.addRecipient("dvela@ochoa.es","Daniel");
		sender.addRecipient("MadCat@0z0ne.com","MadCat");

		Blob<char> blob = FileUtil::File2Buffer("C:\\me.eml");

		sender.setMessageBody(blob);

		sender.setSenderEmail("dvela@ochoa.es");
		
		sender.send();


		// Send second email
		sender.addRecipient("dvela@ochoa.es","Daniel");
		sender.addRecipient("MadCat@0z0ne.com","MadCat");

		blob = FileUtil::File2Buffer("C:\\me2.eml");

		sender.setMessageBody(blob);

		sender.setSenderEmail("dvela@ochoa.es");
		
		sender.send();

		sender.disconnect();
	}catch(stream::exceptions::StreamException* e)
	{
		cerr << e->what() << endl;
	}

	return 0;
}
