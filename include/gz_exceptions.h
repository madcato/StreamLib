

#ifndef __GZ_EXCEPTIONS__H__
#define __GZ_EXCEPTIONS__H__


namespace stream
{
/**
	Group of exception classes used by the stream classes
*/
namespace exceptions
{

class GZException : public std::exception
{
public:
	GZException(gzFile file)
	{
		m_desc = gzerror(file,&m_idError);

		if(m_idError == Z_ERRNO)
		{
			m_idError = errno;
			m_desc = "";
		}
	}
	GZException(std::string msg)
	{
		m_desc = msg;
		m_idError = -1;
	}
	virtual ~GZException(){}

	std::string GetDesc(){ return m_desc;}
	int GetIdError(){ return m_idError;}

	/**
		@return Returns error description. One error can be produced:
	*/
	virtual const char *what() const throw()
	{
		return m_desc.c_str();
	}

private:
	std::string m_desc;
	int m_idError;
};

} // namespace exceptions

} // namespace stream


#endif // __GZ_EXCEPTIONS__H__