// TestBigInteger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{

/*	try
	{
	
		//Socket sock("zaz-velad","80");
		//std::auto_ptr<Socket> sock(new Socket("msdn.microsoft.com","80"));

		SocksifiedSocket proxy_sock("velad user agent");

		proxy_sock.SetProxy(SocksifiedSocket::PROXYTYPE_CONNECT,"zaz-sis-px01.tb-solutions.com","8080");
		
		proxy_sock.ConnectTo("msdn.microsoft.com","80");

		std::auto_ptr<Socket> sock = proxy_sock.releaseSocket();

		HTTPConnection http(sock->getInputStream(),sock->getOutputStream());

		Properties prop;
		prop.setProperty("Host", "msdn.microsoft.com");
	

		//auto_ptr<HTTPResponse> response = http.doGet("/fs-graphics/mysql.png",prop);
		auto_ptr<HTTPResponse> response = http.doGet("/library/toolbar/3.0/images/banners/msdn_masthead_ltr.gif",prop);
		
		if(response->status == 200)
		{
			FileUtil::Buffer2File(response->body,"C:\\msdn.gif");
		}
		else
		{
			response->body.attach((char*)"\0",1);
			cerr << response->body.get() << endl;
		}
	}catch(stream::Exceptions::StreamException* e)
	{
		cerr << e->what() << endl;
	}


  

	std::cout << stream::SystemInfo::getOperatingSystemId() << std::endl;
	std::cout << stream::SystemInfo::getIEVersion() << std::endl;
*/


	/*BigInteger integer1(16);
	BigInteger integer2(16);

	integer1[0] = 2;
	integer1[1] = 2;

	integer2[0] = 3;
	integer2[1] = 3;

	BigInteger integer3 = integer1 * integer2;

	int a = 514 * 771;

	int b = integer3[0] + integer3[1] * 256 + integer3[2] * 256 * 256 + integer3[3] * 256 * 256 * 256;



	BigInteger integer4 = integer3.split();

	b = (unsigned long)integer4;

	if(integer1 < integer2)
	{
		int ok = 1;
	}

	if(integer3 > integer2)
	{
		int ok = 1;
	}

	BigInteger integer5 = integer2 - integer1;

	a = 771 - 514;

	b = integer5[0] + integer5[1] * 256; //+ integer5[2] * 256 * 256 + integer5[3] * 256 * 256 * 256;

	b = (unsigned long)integer5;


	BigInteger integer6 = integer2 + integer1;

	a = 771 + 514;

	b = integer6[0] + integer6[1] * 256 + integer5[2] * 256 * 256; // + integer5[3] * 256 * 256 * 256;

	b = (unsigned long)integer6;

*/
	BigInteger integer1(2);
	BigInteger integer2(2);

	integer1[0] = 18;
	integer1[1] = 32;

	integer2[0] = 5;
	integer2[1] = 1;

	BigInteger integer3 = integer1 / integer2;
	BigInteger integer4 = integer1 % integer2;

	unsigned long a = (unsigned long)integer1;
	unsigned long b = (unsigned long)integer2;
	unsigned long c = (unsigned long)integer3;
	unsigned long d = (unsigned long)integer4;

	// 3c 7a 55 18

	BigInteger hexserial(4);

	hexserial[0] = 0x18;
	hexserial[1] = 0x55;
	hexserial[2] = 0x7A;
	hexserial[3] = 0x3C;

	BigInteger base10(1);
	BigInteger cero(1);

	base10[0] = 0x0A;


	char buffer[100];
	string decimalStr = "";

	while(hexserial >= base10)
	{
		long resto = hexserial % base10;
		hexserial = hexserial / base10;
		ltoa(resto,buffer,10);
		decimalStr = string(buffer) + decimalStr;
	}


	//0x33999EA3F1476F61 => 3718177394335903585
	unsigned char hex[8];
	hex[7] = 0x33;
	hex[6] = 0x99;
	hex[5] = 0x9E;
	hex[4] = 0xA3;
	hex[3] = 0xF1;
	hex[2] = 0x47;
	hex[1] = 0x6F;
	hex[0] = 0x61;

	string decimalStr2 = BigInteger::encodeDecimal(hex,8);

	
	//0x412da96852724d2a => 4696596251942210858

	hex[7] = 0x41;
	hex[6] = 0x2D;
	hex[5] = 0xA9;
	hex[4] = 0x68;
	hex[3] = 0x52;
	hex[2] = 0x72;
	hex[1] = 0x4D;
	hex[0] = 0x2A;

	string decimalStr3 = BigInteger::encodeDecimal(hex,8);

	BigInteger div1(8);
	div1[7] = 0x33;
	div1[6] = 0x99;
	div1[5] = 0x9E;
	div1[4] = 0xA3;
	div1[3] = 0xF1;
	div1[2] = 0x47;
	div1[1] = 0x6F;
	div1[0] = 0x61;

	BigInteger div2(6);
	div2[5] = 0xA9;
	div2[4] = 0x68;
	div2[3] = 0x52;
	div2[2] = 0x72;
	div2[1] = 0x4D;
	div2[0] = 0x2A;


	BigInteger div3 = div1 / div2;

	string str = div3.encodeDecimal();
	int t = 0;


	// 0x 33 99 9e a3 f1 47 6f 61 41 2d a9 68 52 72 4d 2a => 68588266813966652011120507592499154218

	BigInteger cert(16);
	cert[15] = 0x33;
	cert[14] = 0x99;
	cert[13] = 0x9E;
	cert[12] = 0xA3;
	cert[11] = 0xF1;
	cert[10] = 0x47;
	cert[9] = 0x6F;
	cert[8] = 0x61;
	cert[7] = 0x41;
	cert[6] = 0x2D;
	cert[5] = 0xA9;
	cert[4] = 0x68;
	cert[3] = 0x52;
	cert[2] = 0x72;
	cert[1] = 0x4D;
	cert[0] = 0x2A;


	string certSerial = cert.encodeDecimal();


	//0x412da96852724d2a => 4696596251942210858

	BigInteger bi;

	bi.decodeDecimal("4696596251942210858");


/*

	sstring hola;


	hola = "Hola pepe";


	std::string h2 = hola;


	hola.toUpper();

	hola = 34;


	hola = true;


	bool b = hola;


	stream::BLOB<unsigned char> blob;
	blob.resize(10);

	
	blob[0] = 12;
	blob[1] = 24;
	blob[2] = 48;
	blob[3] = 96;
	blob[4] = 3;

	blob.setLength(5);

	std::string hexCad = FileUtil::binToHex(blob);

	stream::BLOB<unsigned char> blob2 = FileUtil::hexToBin(hexCad);
*/
	return 0;
}

