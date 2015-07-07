// Service.h: interface for the Service class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICE_H__9E8F18A7_67FF_423C_AFFF_1EBBBB73C185__INCLUDED_)
#define AFX_SERVICE_H__9E8F18A7_67FF_423C_AFFF_1EBBBB73C185__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

class Service : public Application
{
public:
	Service();
	virtual ~Service();

	void run();

	enum ServiceState
	{
		INITIALIZING,
		WAITING,
		RUNNING,
	};
private:
	ServiceState m_state;




	
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_SERVICE_H__9E8F18A7_67FF_423C_AFFF_1EBBBB73C185__INCLUDED_)
