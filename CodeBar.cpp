// CodeBar.cpp: implementation of the CodeBar class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CodeBar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool CodeBar::m_initialized = false;
std::map<char,int> CodeBar::m_caseA;
std::map<char,int> CodeBar::m_caseB;
std::map<std::string,int> CodeBar::m_caseC;
std::vector<std::string> CodeBar::m_patterns;

std::string CodeBar::QuietZone = "\x0A"; // 10 blancos seguidos
const int CodeBar::StopChar = 106; // Final


CodeBar::CodeBar()
{
	init();
}

CodeBar::~CodeBar()
{

}


std::vector<std::string> CodeBar::generate(const std::string& text, BarType type)
{
	std::vector<std::string> result;
	result.push_back(QuietZone); //Inserts quiet zone.

	std::map<char,int> m_vec;
	int checkSum = 0;
	switch(type)
	{
	case TypeA:
		m_vec = m_caseA;
		result.push_back(m_patterns[TypeA]); // Inserts start character
		checkSum = TypeA;
		break;
	case TypeB:
		m_vec = m_caseB;
		result.push_back(m_patterns[TypeB]); // Inserts start character
		checkSum = TypeB;
		break;
	}


	if(type != TypeC)
	{
		for(int i = 0 ; i < text.length() ; i++)
		{
			int index = m_vec[text[i]];
			checkSum += (i+1)*index;
			result.push_back(m_patterns[index]); // inserts data
		}
	}
	else
	{
		
		result.push_back(m_patterns[TypeC]); // Inserts start character
		checkSum = TypeC;
		std::string twoDigit = "  ";
		int length = text.length();
		/*if(length % 2)
			throw new StreamException(-1,"Barcode. Invalid string length for TypeC encoding: must be odds");
*/
		for(int i = 0 ; i < length ; i+=2)
		{
			twoDigit[0] = text[i];
			twoDigit[1] = text[i+1];
			int index = m_caseC[twoDigit];
			
			long value = 0;
			sscanf(twoDigit.c_str(),"%d",&value);
			checkSum += (i/2+1)*value;

			result.push_back(m_patterns[index]); // Inserts data

		}

	}

	result.push_back(m_patterns[checkSum%103]);  // Check digit
	result.push_back(m_patterns[StopChar]); // Inserts stop character
	result.push_back(QuietZone); //Inserts quiet zone.

	return result;
}



















void CodeBar::init()
{
	if(!m_initialized)
	{
m_caseA.insert(std::pair<char,int>(' ' ,	0));
m_caseA.insert(std::pair<char,int>('!' ,	1));
m_caseA.insert(std::pair<char,int>('"' ,	2));
m_caseA.insert(std::pair<char,int>('#' ,	3));
m_caseA.insert(std::pair<char,int>('$' ,	4));
m_caseA.insert(std::pair<char,int>('%' ,	5));
m_caseA.insert(std::pair<char,int>('&' ,	6));
m_caseA.insert(std::pair<char,int>('\'' ,	7));
m_caseA.insert(std::pair<char,int>('(' ,	8));
m_caseA.insert(std::pair<char,int>(')' ,	9));
m_caseA.insert(std::pair<char,int>('*' ,	10));
m_caseA.insert(std::pair<char,int>('+' ,	11));
m_caseA.insert(std::pair<char,int>(',' ,	12));
m_caseA.insert(std::pair<char,int>('-' ,	13));
m_caseA.insert(std::pair<char,int>('.' ,	14));
m_caseA.insert(std::pair<char,int>('/' ,	15));
m_caseA.insert(std::pair<char,int>('0' ,	16));
m_caseA.insert(std::pair<char,int>('1' ,	17));
m_caseA.insert(std::pair<char,int>('2' ,18));
m_caseA.insert(std::pair<char,int>('3' ,	19));
m_caseA.insert(std::pair<char,int>('4' ,	20));
m_caseA.insert(std::pair<char,int>('5' ,	21));
m_caseA.insert(std::pair<char,int>('6' ,	22));
m_caseA.insert(std::pair<char,int>('7' ,	23));
m_caseA.insert(std::pair<char,int>('8' ,	24));
m_caseA.insert(std::pair<char,int>('9' ,	25));
m_caseA.insert(std::pair<char,int>(':' ,	26));
m_caseA.insert(std::pair<char,int>(';' ,	27));
m_caseA.insert(std::pair<char,int>('<' ,	28));
m_caseA.insert(std::pair<char,int>('=' ,	29));
m_caseA.insert(std::pair<char,int>('>' ,	30));
m_caseA.insert(std::pair<char,int>('?' ,	31));
m_caseA.insert(std::pair<char,int>('@' ,	32));
m_caseA.insert(std::pair<char,int>('A' ,	33));
m_caseA.insert(std::pair<char,int>('B' ,	34));
m_caseA.insert(std::pair<char,int>('C' ,	35));
m_caseA.insert(std::pair<char,int>('D' ,	36));
m_caseA.insert(std::pair<char,int>('E' ,	37));
m_caseA.insert(std::pair<char,int>('F' ,	38));
m_caseA.insert(std::pair<char,int>('G' ,	39));
m_caseA.insert(std::pair<char,int>('H' ,	40));
m_caseA.insert(std::pair<char,int>('I' ,	41));
m_caseA.insert(std::pair<char,int>('J' ,	42));
m_caseA.insert(std::pair<char,int>('K' ,	43));
m_caseA.insert(std::pair<char,int>('L',44));
m_caseA.insert(std::pair<char,int>('M' ,	45));
m_caseA.insert(std::pair<char,int>('N' ,	46));
m_caseA.insert(std::pair<char,int>('O' ,	47));
m_caseA.insert(std::pair<char,int>('P' ,	48));
m_caseA.insert(std::pair<char,int>('Q' ,	49));
m_caseA.insert(std::pair<char,int>('R' ,	50));
m_caseA.insert(std::pair<char,int>('S' ,	51));
m_caseA.insert(std::pair<char,int>('T' ,	52));
m_caseA.insert(std::pair<char,int>('U' ,	53));
m_caseA.insert(std::pair<char,int>('V' ,	54));
m_caseA.insert(std::pair<char,int>('W' ,	55));
m_caseA.insert(std::pair<char,int>('X' ,	56));
m_caseA.insert(std::pair<char,int>('Y' ,	57));
m_caseA.insert(std::pair<char,int>('Z' ,	58));
m_caseA.insert(std::pair<char,int>('[' ,	59));
m_caseA.insert(std::pair<char,int>('\\', 	60));
m_caseA.insert(std::pair<char,int>(']' ,	61));
m_caseA.insert(std::pair<char,int>('^' ,	62));
m_caseA.insert(std::pair<char,int>('_' ,	63));
m_caseA.insert(std::pair<char,int>('\x00' ,64)); //NUL
m_caseA.insert(std::pair<char,int>('\x01', 65)); //SOH
m_caseA.insert(std::pair<char,int>('\x02', 66)); //STX
m_caseA.insert(std::pair<char,int>('\x03', 67)); //ETX
m_caseA.insert(std::pair<char,int>('\x04', 68)); //EOT
m_caseA.insert(std::pair<char,int>('\x05', 69)); //ENQ
m_caseA.insert(std::pair<char,int>('\x06', 70)); //ACK
m_caseA.insert(std::pair<char,int>('\x07',71)); //BEL
m_caseA.insert(std::pair<char,int>('\x08', 	72)); //BS
m_caseA.insert(std::pair<char,int>('\x09' ,	73)); //BEL
m_caseA.insert(std::pair<char,int>('\x0a' ,	74)); //LF
m_caseA.insert(std::pair<char,int>('\x0b' ,	75)); //VT
m_caseA.insert(std::pair<char,int>('\x0c' ,	76)); //FF
m_caseA.insert(std::pair<char,int>('\x0d' ,	77)); //CR
m_caseA.insert(std::pair<char,int>('\x0e' ,	78)); //SO
m_caseA.insert(std::pair<char,int>('\x0f' ,	79)); //SI
m_caseA.insert(std::pair<char,int>('\x10', 80)); //DLE
m_caseA.insert(std::pair<char,int>('\x11', 81)); //DC1
m_caseA.insert(std::pair<char,int>('\x12', 82)); //DC2
m_caseA.insert(std::pair<char,int>('\x13', 83)); //DC3
m_caseA.insert(std::pair<char,int>('\x14', 84)); //DC4
m_caseA.insert(std::pair<char,int>('\x15', 85)); //NAK
m_caseA.insert(std::pair<char,int>('\x16', 86)); //SYN
m_caseA.insert(std::pair<char,int>('\x17', 87)); //ETB
m_caseA.insert(std::pair<char,int>('\x18', 88)); //CAN
m_caseA.insert(std::pair<char,int>('\x19' ,	89)); //EM
m_caseA.insert(std::pair<char,int>('\x1a', 90)); //SUB
m_caseA.insert(std::pair<char,int>('\x1b', 91)); //ESC
m_caseA.insert(std::pair<char,int>('\x1c' ,	92)); //FS
m_caseA.insert(std::pair<char,int>('\x1d' ,	93)); //GS
m_caseA.insert(std::pair<char,int>('\x1e' ,	94)); //RS
m_caseA.insert(std::pair<char,int>('\x1f', 	95)); //US
/*m_caseA.insert(std::pair<char,int>('FNC3',96));
m_caseA.insert(std::pair<char,int>('FNC2',	97));
m_caseA.insert(std::pair<char,int>('SHIFT',	98));
m_caseA.insert(std::pair<char,int>('CODE C'	99));
m_caseA.insert(std::pair<char,int>('CODE B',CODE B));
m_caseA.insert(std::pair<char,int>('FNC 4',CODE A));
m_caseA.insert(std::pair<char,int>('FNC 1',FNC 1));
m_caseA.insert(std::pair<char,int>('Start A',Start A));
m_caseA.insert(std::pair<char,int>('Start B',Start B));
m_caseA.insert(std::pair<char,int>('Start C',Start C));
m_caseA.insert(std::pair<char,int>('Stop',	Stop));

*/
m_caseB.insert(std::pair<char,int>(' ', 	0));
m_caseB.insert(std::pair<char,int>('!', 	1));
m_caseB.insert(std::pair<char,int>('"', 	2));
m_caseB.insert(std::pair<char,int>('#', 	3));
m_caseB.insert(std::pair<char,int>('$', 	4));
m_caseB.insert(std::pair<char,int>('%',	5));
m_caseB.insert(std::pair<char,int>('&',	6));
m_caseB.insert(std::pair<char,int>('\'', 	7));
m_caseB.insert(std::pair<char,int>('(' ,	8));
m_caseB.insert(std::pair<char,int>(')' ,	9));
m_caseB.insert(std::pair<char,int>('*' ,	10));
m_caseB.insert(std::pair<char,int>('+',	11));
m_caseB.insert(std::pair<char,int>(',' ,	12));
m_caseB.insert(std::pair<char,int>('-' ,	13));
m_caseB.insert(std::pair<char,int>('.' ,	14));
m_caseB.insert(std::pair<char,int>('/',	15));
m_caseB.insert(std::pair<char,int>('0' ,	16));
m_caseB.insert(std::pair<char,int>('1' ,	17));
m_caseB.insert(std::pair<char,int>('2' ,	18));
m_caseB.insert(std::pair<char,int>('3' ,	19));
m_caseB.insert(std::pair<char,int>('4' ,	20));
m_caseB.insert(std::pair<char,int>('5' ,	21));
m_caseB.insert(std::pair<char,int>('6' ,	22));
m_caseB.insert(std::pair<char,int>('7' ,	23));
m_caseB.insert(std::pair<char,int>('8' ,	24));
m_caseB.insert(std::pair<char,int>('9' ,	25));
m_caseB.insert(std::pair<char,int>(':' ,	26));
m_caseB.insert(std::pair<char,int>(';' ,	27));
m_caseB.insert(std::pair<char,int>('<' ,	28));
m_caseB.insert(std::pair<char,int>('=' ,	29));
m_caseB.insert(std::pair<char,int>('>' ,	30));
m_caseB.insert(std::pair<char,int>('?' ,	31));
m_caseB.insert(std::pair<char,int>('@' ,	32));
m_caseB.insert(std::pair<char,int>('A' ,	33));
m_caseB.insert(std::pair<char,int>('B' ,	34));
m_caseB.insert(std::pair<char,int>('C' ,	35));
m_caseB.insert(std::pair<char,int>('D' ,	36));
m_caseB.insert(std::pair<char,int>('E' ,	37));
m_caseB.insert(std::pair<char,int>('F' ,	38));
m_caseB.insert(std::pair<char,int>('G' ,	39));
m_caseB.insert(std::pair<char,int>('H' ,	40));
m_caseB.insert(std::pair<char,int>('I' ,	41));
m_caseB.insert(std::pair<char,int>('J' 	,42));
m_caseB.insert(std::pair<char,int>('K' ,	43));
m_caseB.insert(std::pair<char,int>('L' ,	44));
m_caseB.insert(std::pair<char,int>('M',	45));
m_caseB.insert(std::pair<char,int>('N', 	46));
m_caseB.insert(std::pair<char,int>('O', 	47));
m_caseB.insert(std::pair<char,int>('P', 	48));
m_caseB.insert(std::pair<char,int>('Q', 	49));
m_caseB.insert(std::pair<char,int>('R', 	50));
m_caseB.insert(std::pair<char,int>('S', 	51));
m_caseB.insert(std::pair<char,int>('T' ,	52));
m_caseB.insert(std::pair<char,int>('U' ,	53));
m_caseB.insert(std::pair<char,int>('V', 	54));
m_caseB.insert(std::pair<char,int>('W', 	55));
m_caseB.insert(std::pair<char,int>('X', 	56));
m_caseB.insert(std::pair<char,int>('Y', 	57));
m_caseB.insert(std::pair<char,int>('Z', 	58));
m_caseB.insert(std::pair<char,int>('[', 	59));
m_caseB.insert(std::pair<char,int>('\\' ,	60));
m_caseB.insert(std::pair<char,int>(']' 	,61));
m_caseB.insert(std::pair<char,int>('^' ,	62));
m_caseB.insert(std::pair<char,int>('_' ,	63));
m_caseB.insert(std::pair<char,int>('`', 	64));
m_caseB.insert(std::pair<char,int>('a', 	65));
m_caseB.insert(std::pair<char,int>('b', 	66));
m_caseB.insert(std::pair<char,int>('c', 	67));
m_caseB.insert(std::pair<char,int>('d', 	68));
m_caseB.insert(std::pair<char,int>('e', 	69));
m_caseB.insert(std::pair<char,int>('f', 	70));
m_caseB.insert(std::pair<char,int>('g', 	71));
m_caseB.insert(std::pair<char,int>('h', 	72));
m_caseB.insert(std::pair<char,int>('i', 	73));
m_caseB.insert(std::pair<char,int>('j', 	74));
m_caseB.insert(std::pair<char,int>('k', 	75));
m_caseB.insert(std::pair<char,int>('l', 	76));
m_caseB.insert(std::pair<char,int>('m', 	77));
m_caseB.insert(std::pair<char,int>('n', 	78));
m_caseB.insert(std::pair<char,int>('o', 	79));
m_caseB.insert(std::pair<char,int>('p', 	80));
m_caseB.insert(std::pair<char,int>('q', 	81));
m_caseB.insert(std::pair<char,int>('r', 	82));
m_caseB.insert(std::pair<char,int>('s', 	83));
m_caseB.insert(std::pair<char,int>('t' ,	84));
m_caseB.insert(std::pair<char,int>('u', 	85));
m_caseB.insert(std::pair<char,int>('v', 	86));
m_caseB.insert(std::pair<char,int>('w', 	87));
m_caseB.insert(std::pair<char,int>('x', 	88));
m_caseB.insert(std::pair<char,int>('y',	89));
m_caseB.insert(std::pair<char,int>('z', 	90));
m_caseB.insert(std::pair<char,int>('{', 	91));
m_caseB.insert(std::pair<char,int>('|', 	92));
m_caseB.insert(std::pair<char,int>('}', 	93));
m_caseB.insert(std::pair<char,int>('~', 	94));

/*
m_caseB.insert(std::pair<char,int>('DEL',	95));
m_caseB.insert(std::pair<char,int>('FNC3', 96));
m_caseB.insert(std::pair<char,int>('FNC 2', 	97));
m_caseB.insert(std::pair<char,int>('SHIFT', 	98));
m_caseB.insert(std::pair<char,int>('CODE C', 	99));
m_caseB.insert(std::pair<char,int>('FNC 4', 	CODE B));
m_caseB.insert(std::pair<char,int>('CODE A', 	CODE A));
m_caseB.insert(std::pair<char,int>('FNC 1', 	FNC 1));
m_caseB.insert(std::pair<char,int>('Start A', 	Start A));
m_caseB.insert(std::pair<char,int>('Start B', 	Start B));
m_caseB.insert(std::pair<char,int>('Start C', 	Start C));
m_caseB.insert(std::pair<char,int>('Stop',Stop));
*/


m_caseC.insert(std::pair<std::string,int>("00",0));
m_caseC.insert(std::pair<std::string,int>("01",1));
m_caseC.insert(std::pair<std::string,int>("02",2));
m_caseC.insert(std::pair<std::string,int>("03",3));
m_caseC.insert(std::pair<std::string,int>("04",4));
m_caseC.insert(std::pair<std::string,int>("05",5));
m_caseC.insert(std::pair<std::string,int>("06",6));
m_caseC.insert(std::pair<std::string,int>("07",7));
m_caseC.insert(std::pair<std::string,int>("08",8));
m_caseC.insert(std::pair<std::string,int>("09",9));
m_caseC.insert(std::pair<std::string,int>("10",10));
m_caseC.insert(std::pair<std::string,int>("11",11));
m_caseC.insert(std::pair<std::string,int>("12",12));
m_caseC.insert(std::pair<std::string,int>("13",13));
m_caseC.insert(std::pair<std::string,int>("14",14));
m_caseC.insert(std::pair<std::string,int>("15",15));
m_caseC.insert(std::pair<std::string,int>("16",16));
m_caseC.insert(std::pair<std::string,int>("17",17));
m_caseC.insert(std::pair<std::string,int>("18",18));
m_caseC.insert(std::pair<std::string,int>("19",19));
m_caseC.insert(std::pair<std::string,int>("20",20));
m_caseC.insert(std::pair<std::string,int>("21",21));
m_caseC.insert(std::pair<std::string,int>("22",22));
m_caseC.insert(std::pair<std::string,int>("23",23));
m_caseC.insert(std::pair<std::string,int>("24",24));
m_caseC.insert(std::pair<std::string,int>("25",25));
m_caseC.insert(std::pair<std::string,int>("26",26));
m_caseC.insert(std::pair<std::string,int>("27",27));
m_caseC.insert(std::pair<std::string,int>("28",28));
m_caseC.insert(std::pair<std::string,int>("29",29));
m_caseC.insert(std::pair<std::string,int>("30",30));
m_caseC.insert(std::pair<std::string,int>("31",31));
m_caseC.insert(std::pair<std::string,int>("32",32));
m_caseC.insert(std::pair<std::string,int>("33",33));
m_caseC.insert(std::pair<std::string,int>("34",34));
m_caseC.insert(std::pair<std::string,int>("35",35));
m_caseC.insert(std::pair<std::string,int>("36",36));
m_caseC.insert(std::pair<std::string,int>("37",37));
m_caseC.insert(std::pair<std::string,int>("38",38));
m_caseC.insert(std::pair<std::string,int>("39",39));
m_caseC.insert(std::pair<std::string,int>("40",40));
m_caseC.insert(std::pair<std::string,int>("41",41));
m_caseC.insert(std::pair<std::string,int>("42",42));
m_caseC.insert(std::pair<std::string,int>("43",43));
m_caseC.insert(std::pair<std::string,int>("44",44));
m_caseC.insert(std::pair<std::string,int>("45",45));
m_caseC.insert(std::pair<std::string,int>("46",46));
m_caseC.insert(std::pair<std::string,int>("47",47));
m_caseC.insert(std::pair<std::string,int>("48",48));
m_caseC.insert(std::pair<std::string,int>("49",49));
m_caseC.insert(std::pair<std::string,int>("50",50));
m_caseC.insert(std::pair<std::string,int>("51",51));
m_caseC.insert(std::pair<std::string,int>("52",52));
m_caseC.insert(std::pair<std::string,int>("53",53));
m_caseC.insert(std::pair<std::string,int>("54",54));
m_caseC.insert(std::pair<std::string,int>("55",55));
m_caseC.insert(std::pair<std::string,int>("56",56));
m_caseC.insert(std::pair<std::string,int>("57",57));
m_caseC.insert(std::pair<std::string,int>("58",58));
m_caseC.insert(std::pair<std::string,int>("59",59));
m_caseC.insert(std::pair<std::string,int>("60",60));
m_caseC.insert(std::pair<std::string,int>("61",61));
m_caseC.insert(std::pair<std::string,int>("62",62));
m_caseC.insert(std::pair<std::string,int>("63",63));
m_caseC.insert(std::pair<std::string,int>("64",64));
m_caseC.insert(std::pair<std::string,int>("65",65));
m_caseC.insert(std::pair<std::string,int>("66",66));
m_caseC.insert(std::pair<std::string,int>("67",67));
m_caseC.insert(std::pair<std::string,int>("68",68));
m_caseC.insert(std::pair<std::string,int>("69",69));
m_caseC.insert(std::pair<std::string,int>("70",70));
m_caseC.insert(std::pair<std::string,int>("71",71));
m_caseC.insert(std::pair<std::string,int>("72",72));
m_caseC.insert(std::pair<std::string,int>("73",73));
m_caseC.insert(std::pair<std::string,int>("74",74));
m_caseC.insert(std::pair<std::string,int>("75",75));
m_caseC.insert(std::pair<std::string,int>("76",76));
m_caseC.insert(std::pair<std::string,int>("77",77));
m_caseC.insert(std::pair<std::string,int>("78",78));
m_caseC.insert(std::pair<std::string,int>("79",79));
m_caseC.insert(std::pair<std::string,int>("80",80));
m_caseC.insert(std::pair<std::string,int>("81",81));
m_caseC.insert(std::pair<std::string,int>("82",82));
m_caseC.insert(std::pair<std::string,int>("83",83));
m_caseC.insert(std::pair<std::string,int>("84",84));
m_caseC.insert(std::pair<std::string,int>("85",85));
m_caseC.insert(std::pair<std::string,int>("86",86));
m_caseC.insert(std::pair<std::string,int>("87",87));
m_caseC.insert(std::pair<std::string,int>("88",88));
m_caseC.insert(std::pair<std::string,int>("89",89));
m_caseC.insert(std::pair<std::string,int>("90",90));
m_caseC.insert(std::pair<std::string,int>("91",91));
m_caseC.insert(std::pair<std::string,int>("92",92));
m_caseC.insert(std::pair<std::string,int>("93",93));
m_caseC.insert(std::pair<std::string,int>("94",94));
m_caseC.insert(std::pair<std::string,int>("95",95));
m_caseC.insert(std::pair<std::string,int>("96",96));
m_caseC.insert(std::pair<std::string,int>("97",97));
m_caseC.insert(std::pair<std::string,int>("98",98));
m_caseC.insert(std::pair<std::string,int>("99",99));
m_caseC.insert(std::pair<std::string,int>("100",100));
m_caseC.insert(std::pair<std::string,int>("101",101));
m_caseC.insert(std::pair<std::string,int>("102",102));
m_caseC.insert(std::pair<std::string,int>("103",103));
m_caseC.insert(std::pair<std::string,int>("104",104));
m_caseC.insert(std::pair<std::string,int>("105",105));
m_caseC.insert(std::pair<std::string,int>("106",106));





m_patterns.push_back("\x02\x01\x02\x02\x02\x02");
m_patterns.push_back("\x02\x02\x02\x01\x02\x02");
m_patterns.push_back("\x02\x02\x02\x02\x02\x01");
m_patterns.push_back("\x01\x02\x01\x02\x02\x03");
m_patterns.push_back("\x01\x02\x01\x03\x02\x02");
m_patterns.push_back("\x01\x03\x01\x02\x02\x02");
m_patterns.push_back("\x01\x02\x02\x02\x01\x03");
m_patterns.push_back("\x01\x02\x02\x03\x01\x02");
m_patterns.push_back("\x01\x03\x02\x02\x01\x02");
m_patterns.push_back("\x02\x02\x01\x02\x01\x03");
m_patterns.push_back("\x02\x02\x01\x03\x01\x02");
m_patterns.push_back("\x02\x03\x01\x02\x01\x02");
m_patterns.push_back("\x01\x01\x02\x02\x03\x02");
m_patterns.push_back("\x01\x02\x02\x01\x03\x02");
m_patterns.push_back("\x01\x02\x02\x02\x03\x01");
m_patterns.push_back("\x01\x01\x03\x02\x02\x02");
m_patterns.push_back("\x01\x02\x03\x01\x02\x02");
m_patterns.push_back("\x01\x02\x03\x02\x02\x01");
m_patterns.push_back("\x02\x02\x03\x02\x01\x01");
m_patterns.push_back("\x02\x02\x01\x01\x03\x02");
m_patterns.push_back("\x02\x02\x01\x02\x03\x01");
m_patterns.push_back("\x02\x01\x03\x02\x01\x02");
m_patterns.push_back("\x02\x02\x03\x01\x01\x02");
m_patterns.push_back("\x03\x01\x02\x01\x03\x01");
m_patterns.push_back("\x03\x01\x01\x02\x02\x02");
m_patterns.push_back("\x03\x02\x01\x01\x02\x02");
m_patterns.push_back("\x03\x02\x01\x02\x02\x01");
m_patterns.push_back("\x03\x01\x02\x02\x01\x02");
m_patterns.push_back("\x03\x02\x02\x01\x01\x02");
m_patterns.push_back("\x03\x02\x02\x02\x01\x01");
m_patterns.push_back("\x02\x01\x02\x01\x02\x03");
m_patterns.push_back("\x02\x01\x02\x03\x02\x01");
m_patterns.push_back("\x02\x03\x02\x01\x02\x01");
m_patterns.push_back("\x01\x01\x01\x03\x02\x03");
m_patterns.push_back("\x01\x03\x01\x01\x02\x03");
m_patterns.push_back("\x01\x03\x01\x03\x02\x01");
m_patterns.push_back("\x01\x01\x02\x03\x01\x03");
m_patterns.push_back("\x01\x03\x02\x01\x01\x03");
m_patterns.push_back("\x01\x03\x02\x03\x01\x01");
m_patterns.push_back("\x02\x01\x01\x03\x01\x03");
m_patterns.push_back("\x02\x03\x01\x01\x01\x03");
m_patterns.push_back("\x02\x03\x01\x03\x01\x01");
m_patterns.push_back("\x01\x01\x02\x01\x03\x03");
m_patterns.push_back("\x01\x01\x02\x03\x03\x01");
m_patterns.push_back("\x01\x03\x02\x01\x03\x01");
m_patterns.push_back("\x01\x01\x03\x01\x02\x03");
m_patterns.push_back("\x01\x01\x03\x03\x02\x01");
m_patterns.push_back("\x01\x03\x03\x01\x02\x01");
m_patterns.push_back("\x03\x01\x03\x01\x02\x01");
m_patterns.push_back("\x02\x01\x01\x03\x03\x01");
m_patterns.push_back("\x02\x03\x01\x01\x03\x01");
m_patterns.push_back("\x02\x01\x03\x01\x01\x03");
m_patterns.push_back("\x02\x01\x03\x03\x01\x01");
m_patterns.push_back("\x02\x01\x03\x01\x03\x01");
m_patterns.push_back("\x03\x01\x01\x01\x02\x03");
m_patterns.push_back("\x03\x01\x01\x03\x02\x01");
m_patterns.push_back("\x03\x03\x01\x01\x02\x01");
m_patterns.push_back("\x03\x01\x02\x01\x01\x03");
m_patterns.push_back("\x03\x01\x02\x03\x01\x01");
m_patterns.push_back("\x03\x03\x02\x01\x01\x01");
m_patterns.push_back("\x03\x01\x04\x01\x01\x01");
m_patterns.push_back("\x02\x02\x01\x04\x01\x01");
m_patterns.push_back("\x04\x03\x01\x01\x01\x01");
m_patterns.push_back("\x01\x01\x01\x02\x02\x04");
m_patterns.push_back("\x01\x01\x01\x04\x02\x02");
m_patterns.push_back("\x01\x02\x01\x01\x02\x04");
m_patterns.push_back("\x01\x02\x01\x04\x02\x01");
m_patterns.push_back("\x01\x04\x01\x01\x02\x02");
m_patterns.push_back("\x01\x04\x01\x02\x02\x01");
m_patterns.push_back("\x01\x01\x02\x02\x01\x04");
m_patterns.push_back("\x01\x01\x02\x04\x01\x02");
m_patterns.push_back("\x01\x02\x02\x01\x01\x04");
m_patterns.push_back("\x01\x02\x02\x04\x01\x01");
m_patterns.push_back("\x01\x04\x02\x01\x01\x02");
m_patterns.push_back("\x01\x04\x02\x02\x01\x01");
m_patterns.push_back("\x02\x04\x01\x02\x01\x01");
m_patterns.push_back("\x02\x02\x01\x01\x01\x04");
m_patterns.push_back("\x04\x01\x03\x01\x01\x01");
m_patterns.push_back("\x02\x04\x01\x01\x01\x02");
m_patterns.push_back("\x01\x03\x04\x01\x01\x01");
m_patterns.push_back("\x01\x01\x01\x02\x04\x02");
m_patterns.push_back("\x01\x02\x01\x01\x04\x02");
m_patterns.push_back("\x01\x02\x01\x02\x04\x01");
m_patterns.push_back("\x01\x01\x04\x02\x01\x02");
m_patterns.push_back("\x01\x02\x04\x01\x01\x02");
m_patterns.push_back("\x01\x02\x04\x02\x01\x01");
m_patterns.push_back("\x04\x01\x01\x02\x01\x02");
m_patterns.push_back("\x04\x02\x01\x01\x01\x02");
m_patterns.push_back("\x04\x02\x01\x02\x01\x01");
m_patterns.push_back("\x02\x01\x02\x01\x04\x01");
m_patterns.push_back("\x02\x01\x04\x01\x02\x01");
m_patterns.push_back("\x04\x01\x02\x01\x02\x01");
m_patterns.push_back("\x01\x01\x01\x01\x04\x03");
m_patterns.push_back("\x01\x01\x01\x03\x04\x01");
m_patterns.push_back("\x01\x03\x01\x01\x04\x01");
m_patterns.push_back("\x01\x01\x04\x01\x01\x03");
m_patterns.push_back("\x01\x01\x04\x03\x01\x01");
m_patterns.push_back("\x04\x01\x01\x01\x01\x03");
m_patterns.push_back("\x04\x01\x01\x03\x01\x01");
m_patterns.push_back("\x01\x01\x03\x01\x04\x01");
m_patterns.push_back("\x01\x01\x04\x01\x03\x01");
m_patterns.push_back("\x03\x01\x01\x01\x04\x01");
m_patterns.push_back("\x04\x01\x01\x01\x03\x01");
m_patterns.push_back("\x02\x01\x01\x04\x01\x02");
m_patterns.push_back("\x02\x01\x01\x02\x01\x04");
m_patterns.push_back("\x02\x01\x01\x02\x03\x02");
m_patterns.push_back("\x02\x03\x03\x01\x01\x01\x02");





	}
}























































































/*


0 	SP 	SP 	00 	2 1 2 2 2 2
1 	! 	! 	01 	2 2 2 1 2 2
2 	" 	" 	02 	2 2 2 2 2 1
3 	# 	# 	03 	1 2 1 2 2 3
4 	$ 	$ 	04 	1 2 1 3 2 2
5 	% 	% 	05 	1 3 1 2 2 2
6 	& 	& 	06 	1 2 2 2 1 3
7 	' 	' 	07 	1 2 2 3 1 2
8 	( 	( 	08 	1 3 2 2 1 2
9 	) 	) 	09 	2 2 1 2 1 3
10 	* 	* 	10 	2 2 1 3 1 2
11 	+ 	+ 	11 	2 3 1 2 1 2
12 	, 	, 	12 	1 1 2 2 3 2
13 	- 	- 	13 	1 2 2 1 3 2
14 	. 	. 	14 	1 2 2 2 3 1
15 	/ 	/ 	15 	1 1 3 2 2 2
16 	0 	0 	16 	1 2 3 1 2 2
17 	1 	1 	17 	1 2 3 2 2 1
18 	2 	2 	18 	2 2 3 2 1 1
19 	3 	3 	19 	2 2 1 1 3 2
20 	4 	4 	20 	2 2 1 2 3 1
21 	5 	5 	21 	2 1 3 2 1 2
22 	6 	6 	22 	2 2 3 1 1 2
23 	7 	7 	23 	3 1 2 1 3 1
24 	8 	8 	24 	3 1 1 2 2 2
25 	9 	9 	25 	3 2 1 1 2 2
26 	: 	: 	26 	3 2 1 2 2 1
27 	; 	; 	27 	3 1 2 2 1 2
28 	< 	< 	28 	3 2 2 1 1 2
29 	= 	= 	29 	3 2 2 2 1 1
30 	> 	> 	30 	2 1 2 1 2 3
31 	? 	? 	31 	2 1 2 3 2 1
32 	@ 	@ 	32 	2 3 2 1 2 1
33 	A 	A 	33 	1 1 1 3 2 3
34 	B 	B 	34 	1 3 1 1 2 3
35 	C 	C 	35 	1 3 1 3 2 1
36 	D 	D 	36 	1 1 2 3 1 3
37 	E 	E 	37 	1 3 2 1 1 3
38 	F 	F 	38 	1 3 2 3 1 1
39 	G 	G 	39 	2 1 1 3 1 3
40 	H 	H 	40 	2 3 1 1 1 3
41 	I 	I 	41 	2 3 1 3 1 1
42 	J 	J 	42 	1 1 2 1 3 3
43 	K 	K 	43 	1 1 2 3 3 1
44 	L 	L 	44 	1 3 2 1 3 1
45 	M 	M 	45 	1 1 3 1 2 3
46 	N 	N 	46 	1 1 3 3 2 1
47 	O 	O 	47 	1 3 3 1 2 1
48 	P 	P 	48 	3 1 3 1 2 1
49 	Q 	Q 	49 	2 1 1 3 3 1
50 	R 	R 	50 	2 3 1 1 3 1
51 	S 	S 	51 	2 1 3 1 1 3
52 	T 	T 	52 	2 1 3 3 1 1
53 	U 	U 	53 	2 1 3 1 3 1
54 	V 	V 	54 	3 1 1 1 2 3
55 	W 	W 	55 	3 1 1 3 2 1
56 	X 	X 	56 	3 3 1 1 2 1
57 	Y 	Y 	57 	3 1 2 1 1 3
58 	Z 	Z 	58 	3 1 2 3 1 1
59 	[ 	[ 	59 	3 3 2 1 1 1
60 	\ 	\ 	60 	3 1 4 1 1 1
61 	] 	] 	61 	2 2 1 4 1 1
62 	^ 	^ 	62 	4 3 1 1 1 1
63 	_ 	_ 	63 	1 1 1 2 2 4
64 	NUL ` 	64 	1 1 1 4 2 2
65 	SOH a 	65 	1 2 1 1 2 4
66 	STX b 	66 	1 2 1 4 2 1
67 	ETX c 	67 	1 4 1 1 2 2
68 	EOT d 	68 	1 4 1 2 2 1
69 	ENQ e 	69 	1 1 2 2 1 4
70 	ACK f 	70 	1 1 2 4 1 2
71 	BEL g 	71 	1 2 2 1 1 4
72 	BS 	h 	72 	1 2 2 4 1 1
73 	HT 	i 	73 	1 4 2 1 1 2
74 	LF 	j 	74 	1 4 2 2 1 1
75 	VT 	k 	75 	2 4 1 2 1 1
76 	FF 	I 	76 	2 2 1 1 1 4
77 	CR 	m 	77 	4 1 3 1 1 1
78 	SO 	n 	78 	2 4 1 1 1 2
79 	SI 	o 	79 	1 3 4 1 1 1
80 	DLE p 	80 	1 1 1 2 4 2
81 	DC1 q 	81 	1 2 1 1 4 2
82 	DC2 r 	82 	1 2 1 2 4 1
83 	DC3 s 	83 	1 1 4 2 1 2
84 	DC4 t 	84 	1 2 4 1 1 2
85 	NAK u 	85 	1 2 4 2 1 1
86 	SYN v 	86 	4 1 1 2 1 2
87 	ETB w 	87 	4 2 1 1 1 2
88 	CAN x 	88 	4 2 1 2 1 1
89 	EM 	y 	89 	2 1 2 1 4 1
90 	SUB z 	90 	2 1 4 1 2 1
91 	ESC { 	91 	4 1 2 1 2 1
92 	FS 	| 	92 	1 1 1 1 4 3
93 	GS 	} 	93 	1 1 1 3 4 1
94 	RS 	~ 	94 	1 3 1 1 4 1
95 	US 	DEL	95 	1 1 4 1 1 3

96 	FNC3 FNC3 96 	1 1 4 3 1 1
97 	FNC2 	FNC 2 	97 	4 1 1 1 1 3
98 	SHIFT 	SHIFT 	98 	4 1 1 3 1 1
99 	CODE C 	CODE C 	99 	1 1 3 1 4 1
100 	CODE B 	FNC 4 	CODE B 	1 1 4 1 3 1
101 	FNC 4 	CODE A 	CODE A 	3 1 1 1 4 1
102 	FNC 1 	FNC 1 	FNC 1 	4 1 1 1 3 1
103 	Start A 	Start A 	Start A 	2 1 1 4 1 2
104 	Start B 	Start B 	Start B 	2 1 1 2 1 4
105 	Start C 	Start C 	Start C 	2 1 1 2 3 2
106 	Stop 	Stop 	Stop 	2 3 3 1 1 1 2


  */

