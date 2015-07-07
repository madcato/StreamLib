// zlibTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include "IInputStream.h"
#include "gz_exceptions.h"
#include "GZInputStream.h"

#include "IOutputStream.h"

#include "GZOutputStream.h"

using namespace std;
using namespace Stream;

int main(int argc, char* argv[])
{

	std::string buffer = "En esta carpeta se encuentran los códigos de testeo de las diferentes clases de la librería Stream.\
Cada carpeta tiene el mismo nombre que la clase que testea.";

	GZOutputStream out("d:\\temp\\file.gz");

	out.write((unsigned char*)buffer.c_str(),buffer.length()+1);

	out.close();

	GZInputStream in("d:\\temp\\file.gz");

	char inBuffer[2000];
	int readed = 0;
	
	while((readed = in.read((unsigned char*)inBuffer,100)) != 0){}

	in.close();
	return 0;
}
