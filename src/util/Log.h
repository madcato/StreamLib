// Log.h: interface for the Log class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__6C450A6F_4400_4B60_AAB1_A9302DB41203__INCLUDED_)
#define AFX_LOG_H__6C450A6F_4400_4B60_AAB1_A9302DB41203__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

class ILogOutput
{
public:
	virtual void trace(const std::string& logLine) = 0;
	virtual void traceOn(const std::string& fileName, const eOpenType& openType) = 0;
	virtual void traceOff() = 0;
};


class Log : public ILog
{
public:
	Log();
	virtual ~Log();

	void trace(const std::string& logLine);
	void traceOn(const std::string& fileName, const eOpenType& openType);
	void traceOff();

private:
	
	bool m_started;

	std::auto_ptr<ILogOutput> m_output;

	sync::CriticalSection m_threadControl;
	
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_LOG_H__6C450A6F_4400_4B60_AAB1_A9302DB41203__INCLUDED_)
