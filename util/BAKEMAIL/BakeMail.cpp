// BakeMail.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DBBM.h"

class BakedProperties : public Entry2
{
public:
	BakedProperties()
	{
		m_error = false;
	}
	bool Trata(std::string parametro,std::string value)
	{
		if(parametro == "s")
		{
			m_mapBakedProperties["server"] = value;

			return true;
		}

		if(parametro == "p")
		{
			m_mapBakedProperties["port"] = value;

			return true;
		}

		if(parametro == "u")
		{
			m_mapBakedProperties["user"] = value;

			return true;
		}

		if(parametro == "a")
		{
			m_mapBakedProperties["password"] = value;

			return true;
		}

		if(parametro == "d")
		{
			m_mapBakedProperties["out_dir"] = value;

			return true;
		}

		if(parametro == "rm")
		{
			m_mapBakedProperties["remove"] = "true";

			return true;
		}

		if(parametro == "h")
		{
			cout << "First create a new database with the following script:"<<endl;
			cout << "**************************************************" << endl;
			cout << "# phpMyAdmin MySQL-Dump" <<endl
<< "# version 2.2.6" <<endl
<< "# http://phpwizard.net/phpMyAdmin/" <<endl
<< "# http://www.phpmyadmin.net/ (download page)" <<endl
<< "#" <<endl
<< "# servidor: localhost" <<endl
<< "# Tiempo de Generacion: 04-08-2004 a les 12:42:41" <<endl
<< "# Version del Servidor: 3.23.51" <<endl
<< "# Version del PHP: 4.2.1" <<endl
<< "# Base De Datos : `CheckServ`" <<endl
<< "# --------------------------------------------------------" <<endl
<< "" <<endl
<< "#" <<endl
<< "# Estructura de tabla para tabla `downloaded`" <<endl
<< "#" <<endl
<< "" <<endl
<< "CREATE TABLE downloaded (" <<endl
<< "  id_down int(11) NOT NULL auto_increment," <<endl
<< "  id_server int(11) NOT NULL default '0'," <<endl
<< "  uidl varchar(100) NOT NULL default ''," <<endl
<< "  datecreation date NOT NULL default '2005-06-02'," <<endl
<< "  estado int(11) NOT NULL default '10'," <<endl
<< "  KEY id_down (id_down)" <<endl
<< ") TYPE=MyISAM;" <<endl
<< "# --------------------------------------------------------" <<endl
<< "" <<endl
<< "#" <<endl
<< "# Estructura de tabla para tabla `servers`" <<endl
<< "#" <<endl
<< "" <<endl
<< "CREATE TABLE servers (" <<endl
<< "  id_server int(11) NOT NULL auto_increment," <<endl
<< "  server varchar(100) default NULL," <<endl
<< "  port varchar(6) default NULL," <<endl
<< "  user varchar(100) default NULL," <<endl
<< "  password varchar(100) default NULL," <<endl
<< "  check1 int(11) default '0'," <<endl
<< "  eliminar tinyint(1) NOT NULL default '0'," <<endl
<< "  KEY id_server (id_server)" <<endl
<< ") TYPE=MyISAM;" <<endl
<< "" <<endl<<endl;
			cout << "**************************************************" << endl <<endl;

			cout << "MySql ODBC 3.51 driver REQUIRED." << endl << endl;
			return true;
		}


		if(parametro == ERROR_TRATAMIENTO)
		{
			std::cout << value;
		}


		if(parametro == "i")
		{
			m_mapBakedProperties["id_server"] = value;

			return true;
		}


		return false;
	}

	std::string GetError()
	{
		if((getProperty("out_dir") != "")&&!m_error)
			return "";


		return "eMail back-up utility. \r\nUsage: BakeMail -d <out_dir> [-rm][-h]\r\n\r\n-d <out_dir> output directory where will be stored the emails\r\n-h help and installation instructions\r\n\r\n";
	}


	static std::string getProperty(std::string name)
	{
		return m_mapBakedProperties[name];
	}

private:
	static std::map<std::string,std::string> m_mapBakedProperties;
	bool m_error;
};

std::map<std::string,std::string> BakedProperties::m_mapBakedProperties;


int RunDownload();
int DownloadAccount(const std::string& path,const Account& account);
int CreateOutPath(std::string& m_outputPath, const std::string& path, const std::string& server, const std::string& user);

int main(int argc, char* argv[])
{
	CoInitialize(NULL);
	cout << endl << endl << "START: " << Time::today();
	int retCode = 0;
	try
	{

		DBBM::Init("DRIVER={MySQL ODBC 3.51 Driver};"
						"SERVER=localhost;"
						"DATABASE=CheckServ;"
						"USER=;"
						"PASSWORD=;"
						"OPTION=3;");


		Parseador2 parser;
		BakedProperties p;
		
		parser.SetValueEntry("d",&p);	
		//parser.SetEmptyEntry("rm",&p);	
		parser.SetEmptyEntry("h",&p);	
		parser.SetErrorEntry(&p);


		if(parser.ParseParams(argc,argv))
		{
			retCode = RunDownload();
		}
	}catch(exceptions::StreamException* e)
	{
		cout << e->what() << endl;
	}

	cout << "END: " << Time::today() << endl << endl;
	CoUninitialize();
	return retCode;
}


int RunDownload()
{

	std::list<Account> listAccounts = DBBM::ListAccounts();

	std::string m_path = BakedProperties::getProperty("out_dir");

	FileUtil::PutFinalSlashInPath(m_path);

	std::list<Account>::iterator it = listAccounts.begin();

	while(it != listAccounts.end())
	{
		try
		{
			int retcode = 0;
			retcode = DownloadAccount(m_path,*it);

			if(retcode != 0)
				return retcode;
		}catch(exceptions::StreamException* e)
		{
			cout << e->what() << endl;
		}
		
		it++;
	}

	return 0;
}

int DownloadAccount(const std::string& path,const Account& account)
{
	cout << endl << "-----------------------"<<endl;
	cout << "ID: " << account.m_id_server << endl;
	cout << "Server: " << account.m_server << endl;
	cout << "Port: " << account.m_port << endl;
	cout << "User: " << account.m_user << endl;
	cout << "----"<<endl;
	

	std::string m_outputPath = "";
	
	Socket sock(account.m_server,account.m_port);

	IOutputStream* output = sock.getOutputStream();
	IInputStream* input = sock.getInputStream();

	unsigned char buff[1001];
	unsigned int readed = input->read(buff,1000);
	
	buff[readed] = '\0';
	
	if(memcmp(buff,"+OK",3))
	{
		cout << buff << endl;

		return -1;
	}

	
	string user = string("USER ") + account.m_user + string("\r\n");
	output->write((unsigned char*)user.c_str(),user.length());
	
	readed = input->read(buff,1000);

	buff[readed] = '\0';
	
	if(memcmp(buff,"+OK",3))
	{
		cout << buff << endl;

		return -2;
	}
	


	string pass = string("PASS ") + CCaesar::UnOfuscate(account.m_password) + string("\r\n");
	output->write((unsigned char*)pass.c_str(),pass.length());
	

	readed = input->read(buff,1000);

	buff[readed] = '\0';
	
	if(memcmp(buff,"+OK",3))
	{
		cout << buff << endl;

		return -3;
	}

	string stat = string("STAT") + string("\r\n");
	output->write((unsigned char*)stat.c_str(),stat.length());
	

	readed = input->read(buff,1000);

	buff[readed] = '\0';
	
	if(memcmp(buff,"+OK",3))
	{
		cout << buff << endl;

		return -4;
	}
	else
	{
		std::vector<std::string> m_vec = StringUtil::split(std::string((char*)buff)," ");

		long numberOfMails = StringUtil::longValue(m_vec[1]);

		std::list<std::string> listRemovedUidls;

		cout << "Email number: " << numberOfMails << endl;

		for(int i = 1 ; i <= numberOfMails ; i++)
		{
			string uidl = string("UIDL ") + StringUtil::toString(i) + string("\r\n");
			output->write((unsigned char*)uidl.c_str(),uidl.length());

			readed = input->read(buff,1000);

			buff[readed] = '\0';
			
			if(memcmp(buff,"+OK",3))
			{
				cout << buff << endl;

				return -5;
			}
			else
			{
				std::vector<std::string> m_vecUidl = StringUtil::split(std::string((char*)buff)," \r\n");

				if(!DBBM::CheckDownloaded(account.m_id_server,m_vecUidl[2]))
				{
					if(m_outputPath == "")
					{
						int retcode = CreateOutPath(m_outputPath,path,account.m_server,account.m_user);
						if(retcode != 0)
						{
							return retcode;
						}

						cout << "Create directory: " << m_outputPath << endl;
					}

					cout << "Downloading: " << m_vecUidl[2] << endl;
					// Si no ha sido previamente descargado, se descarga ahora.
					std::string finalFileName = FileUtil::ReplaceSpecialFolderChars(m_vecUidl[2],'_') + ".eml";

					FileOutputStream outFile((m_outputPath + finalFileName).c_str());

					// Consultar tamaño del fichero con el comando LIST.

					string list = string("LIST ") + StringUtil::toString(i) + string("\r\n");
					output->write((unsigned char*)list.c_str(),list.length());

					BufferedReader reader(input);

					std::string m_firstLine = reader.readLine();

					if(m_firstLine.find_first_of("+OK") == std::string::npos)
					{
						cout << m_firstLine << endl;

						return -9;
					}

					std::vector<std::string> m_vecSize = StringUtil::split(m_firstLine," \r\n");
			
					long fileSize = StringUtil::longValue(m_vecSize[2]);


					string retr = string("RETR ") + StringUtil::toString(i) + string("\r\n");
					output->write((unsigned char*)retr.c_str(),retr.length());

					

					m_firstLine = reader.readLine();
					
									
					if(m_firstLine.find_first_of("+OK") == std::string::npos)
					{
						cout << m_firstLine << endl;

						return -6;
					}

					
					string line = "";
					PrintWriter writer(&outFile);
					do
					{
						line = reader.readLine();

						if(line[0] == '.')
						{
							if(line.length() != 1)
							{
								line = line.substr(1);
							}
							else
							{
								break;
							}
						}
						
						writer.println(line);
						

						

					}while(true);


					writer.close();
					DBBM::InsertDownloaded(account.m_id_server,m_vecUidl[2],m_outputPath + finalFileName);

				}


				if(account.m_eliminar == 1)
				{
					string dele = string("DELE ") + StringUtil::toString(i) + string("\r\n");
					output->write((unsigned char*)dele.c_str(),dele.length());

					readed = input->read(buff,1000);

					buff[readed] = '\0';

					if(memcmp(buff,"+OK",3))
					{

						cout << buff << endl;
						return -7;
					}
					else
					{
						listRemovedUidls.push_back(m_vecUidl[2]);
					}

					cout << "Deleting: " << m_vecUidl[2] << endl;

				}

			}
		}
		

		string quit = string("QUIT") + string("\r\n");
		output->write((unsigned char*)quit.c_str(),quit.length());

		readed = input->read(buff,1000);

		buff[readed] = '\0';
		
		if(memcmp(buff,"+OK",3))
		{
			cout << buff << endl;

			return -8;
		}
		else
		{
			DBBM::DeleteUidls(account.m_id_server,listRemovedUidls);
		}
	}

	cout << "-----------------------"<<endl;
	return 0;
}


int CreateOutPath(std::string& m_outputPath, const std::string& path, const std::string& server, const std::string& user)
{

	m_outputPath = path + server;

	FileUtil::PutFinalSlashInPath(m_outputPath);

	if(FileUtil::createDirectory(m_outputPath,false))
	{
		std::cout << "Can't create output directory." << std::endl;
		return -11;
	}


	m_outputPath = FileUtil::getDailyDatedFileName(m_outputPath);

	FileUtil::PutFinalSlashInPath(m_outputPath);

	if(FileUtil::createDirectory(m_outputPath,false))
	{
		std::cout << "Can't create output directory." << std::endl;
		return -1;
	}

	m_outputPath += user;

	FileUtil::PutFinalSlashInPath(m_outputPath);
	
	if(FileUtil::createDirectory(m_outputPath,false))
	{
		std::cout << "Can't create output directory." << std::endl;
		return -10;
	}

	return 0;
}