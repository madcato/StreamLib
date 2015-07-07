#ifndef ___ILOGG____H
#define ___ILOGG____H


namespace stream
{

namespace exceptions
{

	class LogException : StreamException
	{
	public:
		LogException(int errCode,const std::string& errDesc):StreamException(errCode,errDesc)
		{}
	};

} // namespace exceptions

namespace util
{

enum eOpenType
{
	CONTINUE_LOG,
	CREATE_NEW_LOG
};

/**
	This class represents a log output. It can be a file output or a console output.
*/
class ILog
{
public:
	ILog(){}
	virtual ~ILog(){}

	virtual void trace(const std::string& logLine) = 0;
	virtual void traceOn(const std::string& fileName, const eOpenType& openType) = 0;
	virtual void traceOff() = 0;

};

} // namespace util

} // namespace stream

#endif ___ILOGG____H