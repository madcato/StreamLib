#ifndef __TOKENIZAR_DAN_
#define __TOKENIZAR_DAN_

namespace stream
{

/// namespace stream
namespace exceptions
{
	/**
	Exception thrown by class Tokenizer when an error occurs.
	*/
	class TokenizerException : public StreamException
	{
	public:
		/**
			Constructor 
			@param code Error code
		*/
		TokenizerException(long code):StreamException(code,"TokenizerException: NextToken() called when no more tokens where available"){}

		
		
	};

} // namespace exceptions

/// namespace util
namespace util
{

class Tokenizer
{
public:
	enum modes{MODE_ZERO = 0, WITHOUT_BLANCKS = 1, RETURN_DELIMITERS = 2, FULL = 3};
	Tokenizer(std::string cad,modes m = MODE_ZERO);
	Tokenizer(std::string cad,std::string delim,modes m = MODE_ZERO);
	~Tokenizer();

	int CountTokens();
	bool HasMoreTokens();
	std::string NextToken() throw(exceptions::TokenizerException);

	
		// MODE: WITHOUT_BLANKCS if two delimiters are beside each one the empty string between them is eliminated.

private:
	std::list<std::string> m_vectorTokens;
	std::list<std::string>::iterator m_posActual;	

	// Default tokens "\t\n\r"
	void Init(std::string cad,std::string delim);

	modes m_mode;

};

} // namespace util

} // namespace stream

#endif __TOKENIZAR_DAN_