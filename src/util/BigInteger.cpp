// BigInteger.cpp: implementation of the BigInteger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"

#include "BigInteger.h"

#include "Tokenizer.h"
#include "Date.h"
#include "stringUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

BigInteger::BigInteger()
{
	m_length = 0;
	m_buffer = 0;
}

BigInteger::BigInteger(int bytes)
{
	m_length = bytes;
	m_buffer = new unsigned char[m_length];

	memset(m_buffer,0,m_length);
	/* Prueba
	for(unsigned int i = 0 ; i < m_length ; i++)
	{
		m_buffer[i] = i;
	}*/
	
}

BigInteger::~BigInteger()
{
	if(m_buffer)
		delete[] m_buffer;
}


BigInteger::BigInteger(BigInteger& copy)
{
	m_length = copy.m_length;
	m_buffer = new unsigned char[m_length];
	memcpy(m_buffer,copy.m_buffer,m_length);
}


BigInteger& BigInteger::operator=(BigInteger& b)
{
	if(m_buffer)
	delete[] m_buffer;

	
	m_buffer = new unsigned char[b.m_length];
	

	m_length = b.m_length;
	
	memcpy(m_buffer,b.m_buffer,m_length);

	return *this;
}


BigInteger BigInteger::operator+(BigInteger& b)
{

	int length = m_length > b.m_length ? m_length : b.m_length;


	BigInteger ret(length + 1);

	unsigned int acarreo = 0;

	
	unsigned int paso;
	for(int i = 0 ; i < length ; i++)
	{
		paso = (unsigned int)(*this)[i] + (unsigned int)b[i] + acarreo;
		acarreo = 0;
		if(paso >> 8)
		{
			acarreo = paso >> 8;
		}
		ret.m_buffer[i] = paso & 0x0000000FF;
	}

	ret.m_buffer[i] = acarreo;
	ret.trim();
	return ret;
}

unsigned char& BigInteger::operator[](unsigned int index)
{
	if(index >= m_length)
	{
		m_temp = 0;
		return m_temp;
	}

	return m_buffer[index];
}

unsigned char BigInteger::operator[](unsigned int index) const
{
	if(index >= m_length)
		return 0;

	return m_buffer[index];
}

BigInteger BigInteger::operator-(BigInteger& b)
{
	int length = m_length > b.m_length ? m_length : b.m_length;

	BigInteger ret(length + 1);

	int acarreo = 0;

	int paso;
	for(int i = 0 ; i < length ; i++)
	{
	
		paso = (unsigned int)(*this)[i] - (unsigned int)b[i] + acarreo;

		acarreo = 0;
		if(paso >> 8)
		{
			acarreo = paso >> 8;
		}
		ret.m_buffer[i] = paso & 0x0000000FF;
	}
	ret.m_buffer[i] = acarreo;
	ret.trim();
	return ret;
}

BigInteger BigInteger::operator*(BigInteger& b)
{
	int length = m_length + 1;

	BigInteger ret(length);

	for(unsigned int i = 0 ; i < b.m_length ; i++)
	{
		ret = ret + ((*this * b[i]).Desplaza(i));
	}


	return ret;
}


BigInteger BigInteger::operator*(unsigned char b)
{
	BigInteger ret(m_length + 1);
	int acarreo = 0;

	int paso;
	for(unsigned int i = 0 ; i < m_length ; i++)
	{
		paso = (unsigned int)(*this)[i] * b + acarreo;
		acarreo = 0;
		if(paso >> 8)
		{
			acarreo = paso >> 8;
		}
		ret.m_buffer[i] = paso & 0x0000000FF;
	}
	ret.m_buffer[i] = acarreo;
	return ret;
}


BigInteger& BigInteger::Desplaza(int nBytes)
{
	if(nBytes <= 0)
		return *this;

	int length = m_length + nBytes;

	unsigned char* buffer = new unsigned char[length];
	memset(buffer,0,nBytes);
	memcpy(buffer + nBytes,m_buffer,m_length);


	delete[] m_buffer;

	m_buffer = buffer;
	m_length = length; 


	return *this;
}

bool BigInteger::operator<(const BigInteger& b)
{
	int i = 0;
	if(m_length > b.m_length)
	{
		for(i = m_length - 1 ; ((i >= b.m_length)&&(i >=0)) ; i--)
		{
			if(m_buffer[i] > 0)
			{
				return false;
			}
			if(m_buffer[i] < 0)
			{
				return true;
			}
		}
	}
	else
	{
		for(i = b.m_length - 1 ; ((i >= m_length)&&(i >=0)) ; i--)
		{
			if(b.m_buffer[i] > 0)
			{
				return true;
			}
			if(b.m_buffer[i] < 0)
			{
				return false;
			}
		}
	}

	for( ; i >= 0 ; i--)
	{
		if(m_buffer[i] > b.m_buffer[i])
		{
			return false;
		}
		if(m_buffer[i] < b.m_buffer[i])
		{
			return true;
		}
	}


	return false;
}

bool BigInteger::operator==(const BigInteger& b)
{

	int i = 0;
	if(m_length > b.m_length)
	{
		for(i = m_length -1 ; ((i >= b.m_length)&&(i >=0)) ; i--)
		{
			if(m_buffer[i] != 0)
			{
				return false;
			}			
		}
	}
	else
	{
		for(i = b.m_length - 1 ; ((i >= m_length)&&(i >= 0)) ; i--)
		{
			if(b.m_buffer[i] != 0)
			{
				return false;
			}
		}
	}

	for( ; i >= 0 ; i--)
	{
		if(m_buffer[i] != b.m_buffer[i])
		{
			return false;
		}		
	}


	return true;
}

bool BigInteger::operator>(const BigInteger& b)
{
	return !((*this < b) || (*this == b));
}

bool BigInteger::operator<=(const BigInteger& b)
{
	return !(*this > b);
}

bool BigInteger::operator>=(const BigInteger& b)
{
	return !(*this < b);
}

BigInteger BigInteger::top(unsigned long l)
{
	if(l >= m_length)
	{
		BigInteger big(*this);

		return big;
	}
	
	BigInteger number(l);


	for(int i = 0, t = this->m_length - l ; i < l ; i++, t++)
	{
		number[i] = (*this)[t];
	}

	return number;

}

BigInteger BigInteger::bottom(unsigned long l)
{
	if(l >= m_length)
	{
		BigInteger big(*this);

		return big;
	}
	
	BigInteger number(l);


	for(int i = 0, t = 0 ; i < l ; i++, t++)
	{
		number[i] = (*this)[t];
	}

	return number;

}

BigInteger BigInteger::concat(const BigInteger& mostSignificant)
{
	int newLength = mostSignificant.m_length + this->m_length;


	BigInteger number(newLength);

	for(int i = 0 ; i < this->m_length ; i++)
	{
		number[i] = (*this)[i];
	}

	for(int t = 0 ; t < mostSignificant.m_length ; t++,i++)
	{
		number[i] = mostSignificant[t];
	}

	return number;

}

void BigInteger::trim()
{
	long numberOfZeros = 0;
	for(int i = this->m_length - 1 ; i >= 0 ; i--)
	{
		if(m_buffer[i] != 0)
			break;


		numberOfZeros++;
	}

	if(numberOfZeros != 0)
	{

		BigInteger number(this->m_length - numberOfZeros);

		for(i = 0 ; i < (this->m_length - numberOfZeros) ; i++)
		{
			number[i] = (*this)[i];
		}

		*this = number;
	}
}

BigInteger::operator unsigned long()
{
	unsigned long ret = 0;

	trim();

	if(m_length > 4)
		throw exceptions::BigIntegerException(-1,"Invalid cast operation (ulong).");


	for(int i = m_length - 1 ; i >= 0 ; i--)
	{
		ret = ret * 256 + m_buffer[i];
	}

	return ret;
}

BigInteger BigInteger::operator/(BigInteger& b)
{
	b.trim();
	BigInteger ret(1);//(m_length > b.m_length?m_length:b.m_length)*8);
	ret[0] = 0;

	int numbers = 1;
	
	BigInteger partialDivisor = this->top(numbers++);
	BigInteger dividendo(*this);

	while(dividendo > b)
	{
		
		while(partialDivisor < b)
		{
			partialDivisor = dividendo.top(numbers++);
			
		}

		BigInteger restPartialDivisor = dividendo.bottom(dividendo.m_length - (numbers - 1));
		
		

		do
		{
			partialDivisor = partialDivisor - b;
			ret[0]++;
		}while(partialDivisor >= b);	

		ret.Desplaza(1);
		ret[0] = 0;

		/*if(dividendo.m_length < numbers)
		{
			dividendo = partialDivisor;
		}
		else
		{
			dividendo = restPartialDivisor.concat(partialDivisor);
		}*/
		dividendo = restPartialDivisor.concat(partialDivisor);
		numbers = 1;
	}

	ret = ret.top(ret.m_length - 1);
	ret.trim();
	return ret;
}

BigInteger BigInteger::operator%(BigInteger& b)
{
	b.trim();
	BigInteger ret(1);//(m_length > b.m_length?m_length:b.m_length)*8);
	ret[0] = 0;

	int numbers = 1;
	
	BigInteger partialDivisor = this->top(numbers++);
	BigInteger dividendo(*this);

	while(dividendo > b)
	{
		
		while(partialDivisor < b)
		{
			partialDivisor = dividendo.top(numbers++);
			
		}

		BigInteger restPartialDivisor = dividendo.bottom(dividendo.m_length - (numbers - 1));
		
		

		do
		{
			partialDivisor = partialDivisor - b;
			ret[0]++;
		}while(partialDivisor >= b);	

		ret.Desplaza(1);
		ret[0] = 0;

		/*if(dividendo.m_length < numbers)
		{
			dividendo = partialDivisor;
		}
		else
		{
			dividendo = restPartialDivisor.concat(partialDivisor);
		}*/
		dividendo = restPartialDivisor.concat(partialDivisor);
		numbers = 1;
	}
	dividendo.trim();
	return dividendo;
}

std::string BigInteger::encodeDecimal(unsigned char* buffer, unsigned long bufferLength)
{
	int indiceDeSeguridad = 2048; // Para no entrar en un bucle infonito.
	BigInteger hexserial(bufferLength);
	memcpy(hexserial.m_buffer, buffer,bufferLength);
	
	BigInteger base10(1);

	base10[0] = 0x0A;

	BigInteger cero(1);
	cero[0] = 0;

	char b[100];
	std::string decimalStr = "";

	while((!(hexserial == cero))&&(indiceDeSeguridad--))
	{
		long resto = hexserial % base10;
		hexserial = hexserial / base10;
		ltoa(resto,b,10);
		decimalStr = std::string(b) + decimalStr;
	}


	return decimalStr;
}

std::string BigInteger::encodeDecimal()
{
	return encodeDecimal(m_buffer,m_length);
}

void BigInteger::decodeDecimal(const std::string& str)
{
	int strLength = str.length();

	for(int i = 0 ; i < strLength  ; i++)
	{
		if((str[i] < 48)||(str[i] > 57))
			throw new exceptions::BigIntegerException(-1,"BigInteger::decodeDecimal() bad string format.");
	}

	
	BigInteger paso(1);	
	paso[0] = 0;
	BigInteger sumando(4);
	BigInteger diez(1);
	diez[0] = 10;
	for(i = 0 ; i < strLength - 1 ; i++)
	{
		unsigned long l = (unsigned long)sstring(str[i] - 48);
		sumando.m_buffer = (unsigned char*)&l;
		sumando.m_length = 4;

		paso = paso + sumando;
		paso = paso * diez;		

		sumando.m_buffer = 0;
	}

	unsigned long l = (unsigned long)sstring(str[strLength - 1] - 48);
	sumando.m_buffer = (unsigned char*)&l;
	sumando.m_length = 4;

	paso = paso + sumando;

	sumando.m_buffer = 0;

	*this = paso;
}

} // namespace util

} // namespace stream
