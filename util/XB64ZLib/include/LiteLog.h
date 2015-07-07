// LITELOG.h: interface for the LiteLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LITELOG_H__12527D8C_886D_4C74_A41F_1F3F738167CD__INCLUDED_)
#define AFX_LITELOG_H__12527D8C_886D_4C74_A41F_1F3F738167CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

//	Log severities
const long LOG_ALL = 15;
const long LOG_NONE = 0;

const long LOG_ERROR = 1;
const long LOG_WARNING = 2;
const long LOG_INFO = 4;
const long LOG_TRACE = 8;

class LiteLog
{
public:
	LiteLog();

	virtual ~LiteLog();

	void traceOn(const std::string& fileName, const std::string& appInfo,const long logLevel);
	void trace(const long severity,const std::string& logLine);
	void traceOff();

	static LiteLog* getInstance();

	/**
		Converts a string representation of levels to long value that can be used in the traceOn function.
		This converter is able to read this formats:
			LOG_ERROR (Single value)<br>
			LOG_ERROR | LOG_WARNING (value list with '|' separator)<br>
			LOG_ALL | ~LOG_TRACE (value list with '|' separator and a negation)<br>

		@param str String to convert
		@return the long value. If the string is malformed, LOG_NONE is returned.
	*/
	static long stringToId(const std::string& str);
private:
	std::auto_ptr<ILog> m_log;

	static std::auto_ptr<LiteLog> m_instance;

	long m_logLevel;
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_LITELOG_H__12527D8C_886D_4C74_A41F_1F3F738167CD__INCLUDED_)
