// getk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/************************************************************************/
/* 
-- phpMyAdmin SQL Dump
-- version 2.6.1-pl3
-- http://www.phpmyadmin.net
-- 
-- Servidor: localhost
-- Tiempo de generación: 15-07-2005 a las 17:46:00
-- Versión del servidor: 4.0.21
-- Versión de PHP: 5.0.2
-- 
-- Base de datos: `recetas`
-- 

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `control`
-- 

CREATE TABLE `control` (
  `id` int(11) NOT NULL auto_increment,
  `first` int(11) NOT NULL default '0',
  `last` int(11) NOT NULL default '0',
  `done` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`id`)
) TYPE=MyISAM AUTO_INCREMENT=6 ;

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `sys`
-- 

CREATE TABLE `sys` (
  `id` varchar(255) NOT NULL default '',
  `strValue` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `textos`
-- 

CREATE TABLE `textos` (
  `id` int(11) NOT NULL auto_increment,
  `idJob` int(11) NOT NULL default '0',
  `texto` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`id`)
) TYPE=MyISAM AUTO_INCREMENT=328 ; 
*/
     
/************************************************************************/
vector<string> getIdsToRetrive()
{
	

	
	map<string,string> job = DB::queryNamedRow("SELECT * FROM control WHERE done = 'n'");

	vector<string> toReturn;

	for(ulong i = (ulong)(sstring)job["first"]; i <= (ulong)(sstring)job["last"]; i++)
	{
		toReturn.push_back(sstring(i));
	}


	return toReturn;
}

int main(int argc, char* argv[])
{

	INIT_COM();

	try
	{
		DB::init("DRIVER={MySQL ODBC 3.51 Driver};\
						SERVER=localhost;\
						DATABASE=recetas;\
						USER=root;\
						PASSWORD=;\
						OPTION=3;"
					);


		vector<string> toRetrive;

		map<string,string> job = DB::queryNamedRow("SELECT * FROM control WHERE done = 'n'");

		if(job.empty())
		{
			cout << "No hay trabajos" << endl;
			return 0;
		}
		for(ulong i = (ulong)(sstring)job["first"]; i <= (ulong)(sstring)job["last"]; i++)
		{
			toRetrive.push_back(sstring(i));
		}

		map<string,string> config = DB::queryPairMap("SELECT id,strValue FROM sys");


		
		string url = config["url"];
		ReplaceVariables urlReplacer(url);

		vector<string>::iterator it;

		// Conectar al servidor
		SocksifiedSocket ss;

		SocksifiedSocket::EProxyType type;
		if(config["HTTP_use_proxy"] == "yes")
			type = SocksifiedSocket::PROXYTYPE_CONNECT;
		else
			type = SocksifiedSocket::PROXYTYPE_NOPROXY;

		ss.setProxy(type,config["HTTP_server"],config["HTTP_port"],config["HTTP_user"],config["HTTP_password"]);

		if(!ss.connectTo(config["server"],config["port"]))
		{
			cerr << "Fallo HTTP proxy";
			return -1;
		}

		SocketPtr sock = ss.releaseSocket();

		for(it = toRetrive.begin() ; it != toRetrive.end() ; it++)
		{
			// Primero comprobamos si ya tenemos esta página en DB.

			vector<vector<string> > table = DB::queryTable("SELECT * FROM textos WHERE id = " + *it);
			if(!table.empty())
				continue;

			
			

			HTTPConnection connection(sock->getInputStream(),sock->getOutputStream());


			urlReplacer.init();
			
			urlReplacer.setVariable("id",*it);


			Properties headers;
			headers.setProperty("Host",config["server"]);
			HTTPResponsePtr response = connection.doGet(urlReplacer.getData(),headers);

			std::auto_ptr<IInputStream> iis = response->body->getInputStream();

			uchar buffer[500000];
			ulong l = iis->available();
			iis->read((uchar*)buffer,l);
			

			string path = config["basepath"];
			FileUtil::PutFinalSlashInPath(path);
			
			string filename = FileUtil::getDatedFileName(path,"html");
			FileOutputStream fout(filename);

			fout.write(buffer,l);


			
			
			map<string,string> values;

			values["id"] = *it;
			values["idJob"] = job["id"];
			values["texto"] = filename;

			DB::insertNamedRow("textos",values);

			Thread::sleep(100);
			
		}

		// Cambiamos el estado del job


		DB::execute("UPDATE control SET done = 'y' WHERE id = " + job["id"]);

	}catch(exception* e)
	{
		cerr << e->what() << endl;
	}
	
	return 0;
}
