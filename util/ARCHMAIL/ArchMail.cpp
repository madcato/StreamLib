// ArchMail.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	CoInitialize(NULL);
	cout << endl << endl << "START: " << Time::today();
	int retCode = 0;
	try
	{

		DB::init("DRIVER={MySQL ODBC 3.51 Driver};"
						"SERVER=localhost;"
						"DATABASE=CheckServ;"
						"USER=;"
						"PASSWORD=;"
						"OPTION=3;");

		vector<vector<string> > downloaded = DB::queryTable("SELECT * FROM servers,downloaded WHERE downloaded.id_server = servers.id_server AND estado=10");

		Socket socket("smtp.ya.com","25");

		SMTPSender sender(socket.getInputStream(),socket.getOutputStream());
		sender.connect();

		for(int line = 0 ; line < downloaded.size() ; line++)
		{
			string id_server1 = downloaded[line][0];
			string server = downloaded[line][1];
			string port = downloaded[line][2];
			string user = downloaded[line][3];
			string password = downloaded[line][4];
			string check1 = downloaded[line][5];
			string id_down = downloaded[line][6];
			string id_server2 = downloaded[line][7];
			string uidl = downloaded[line][8];
			string path = downloaded[line][9];
			string datecreation = downloaded[line][10];
			string estado = downloaded[line][11];

			
			Blob<char> data = FileUtil::File2Buffer(path.c_str());

			CMimeMessage message;

			message.Load(data);

			cout << sstring(message.GetFrom()) << endl;
			cout << sstring(message.GetTo()) << endl;
			cout << sstring(message.GetCc()) << endl;
			cout << sstring(message.GetBcc()) << endl;
			cout << sstring(message.GetSubject()) << endl;
			cout << sstring(message.GetDate()) << endl;


			
			// AQUÍ SE TRATARIA EL FICHERO

			// Todos se reenvían a la misma cuenta

			
			
			
			sender.addRecipient("madcat@ya.com");
			sender.setMessageBody((string)data);
			sender.setSenderEmail("archmail@ya.com");
			sender.send();

			DB::execute("UPDATE `downloaded` SET `estado` = '20' WHERE `id_down` ="+ id_down);

			

		}

		sender.disconnect();

	}catch(exceptions::StreamException* e)
	{
		cout << e->what() << endl;
	}

	cout << "END: " << Time::today() << endl << endl;
	CoUninitialize();


	return 0;
}
