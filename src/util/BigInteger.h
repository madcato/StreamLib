// BigInteger.h: interface for the BigInteger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIGINTEGER_H__72EA1EB8_BA48_479C_822E_42569CB86D64__INCLUDED_)
#define AFX_BIGINTEGER_H__72EA1EB8_BA48_479C_822E_42569CB86D64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{
	/// namespace exceptions
	namespace exceptions
	{
		class BigIntegerException : public StreamException
		{
		public:
			BigIntegerException(char code,std::string str):StreamException(code,str){}
		};
	} // namespace exceptions


/// namespace util
namespace util
{

/**
	Variable precision integer class. Can fit integers with 1024 bits or more.
	<i>It's not optimized</i>.
*/
class BigInteger  
{
public:
	/**
		Default constructor.
	*/
	BigInteger();
	/**
		Constructor.
		@param bytes Precision in bytes of the data to hold.
	*/
	BigInteger(int bytes);
	/**
		Copy constructor.
	*/
	BigInteger(BigInteger& copy);
	/**
		Destructor.
	*/
	virtual ~BigInteger();

	/**
		Extract operator.
	*/
	unsigned char& operator[](unsigned int index);
	/**
		Const extract operator.
	*/
	unsigned char operator[](unsigned int index) const;

	/**
		Asigment operator.
	*/
	BigInteger& operator=(BigInteger& b);
	/**
		Sumatory operator.
	*/
	BigInteger operator+(BigInteger& b);
	/**
		Substraction operator.
	*/
	BigInteger operator-(BigInteger& b);	
	/**
		Multiplication operator.
	*/
	BigInteger operator*(BigInteger& b);
	/**
		Division operator.
	*/
	BigInteger operator/(BigInteger& b);
	/**
		Module operator.
	*/
	BigInteger operator%(BigInteger& b);
	
	/**
		Multiplication operator.
	*/
	BigInteger operator*(unsigned char b);

	/**
		Less to operator.
	*/
	bool operator<(const BigInteger& b);
	/**
		Equals operator.
	*/
	bool operator==(const BigInteger& b);

	/**
		Greater to operator.
	*/
	bool operator>(const BigInteger& b);
	/**
		Less or equal to operator.
	*/
	bool operator<=(const BigInteger& b);
	/**
		Greater or equal to operator.
	*/
	bool operator>=(const BigInteger& b);

	/**
		@param l number of bytes to return
		@return the 'l' first bytes of this BigInteger(most significant) or a copy of this BigInteger if 'l' is greater than this.m_length
	*/
	BigInteger top(unsigned long l);

	/**
		@param l number of bytes to return
		@return the 'l' last bytes of this BigInteger(less significant) or a copy of this BigInteger if 'l' is greater than this.m_length
	*/
	BigInteger bottom(unsigned long l);

	/**
		@param mostSignificant BigInteger 
		@return a new big integer concatenating the 'mostSignificant' BigInteger with this BigInteger
	*/
	BigInteger concat(const BigInteger& mostSignificant);

	/**
		Remove left-side zoeroes.
		@return a copy of this object but removes all the left zeroes
	*/
	void trim();

	/**
		Cast to unsigned long. Throws an exception if data is to huge to fit in a 32 bit unsigned long.
		return An unsigned long.
	*/
	operator unsigned long();

	/**
		Converts a buffer to a decimal encoded string.
		@param buffer Data to convert.
		@param bufferLength Data length.
		@return a string
	*/
	static std::string encodeDecimal(unsigned char* buffer, unsigned long bufferLength);

	/**
		Converts to a decimal encoded string.
		@return a string
	*/
	std::string encodeDecimal();

	/**
		Decodes the buffer and sets the bin data to this object.
	*/
	void decodeDecimal(const std::string& str);
	
private:
	unsigned int m_length;
	unsigned char* m_buffer;
	BigInteger& Desplaza(int nBytes);

	unsigned char m_temp;
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_BIGINTEGER_H__72EA1EB8_BA48_479C_822E_42569CB86D64__INCLUDED_)

