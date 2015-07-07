

#ifndef __GZ_EXCEPTIONS__H__
#define __GZ_EXCEPTIONS__H__


namespace Stream
{
namespace Exceptions
{

class GZException : public exception
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
} // namespace Exceptions
} // namespace Stream


#endif // __GZ_EXCEPTIONS__H__