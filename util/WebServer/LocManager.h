// LocManager.h: interface for the LocManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCMANAGER_H__8203B60B_9FC5_4067_A3A6_864EE5E89A07__INCLUDED_)
#define AFX_LOCMANAGER_H__8203B60B_9FC5_4067_A3A6_864EE5E89A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LocManager : public GenericController
{
public:
	LocManager();
	virtual ~LocManager();

	static std::string classId(){ return "LocManager";}
	
	virtual std::auto_ptr<HTTPResponse> executeQuery(std::auto_ptr<HTTPRequest> query);
};

class LocManager1 : public GenericController
{
public:
	LocManager1();
	virtual ~LocManager1();

	static std::string classId(){ return "LocManager1";}
	
	virtual std::auto_ptr<HTTPResponse> executeQuery(std::auto_ptr<HTTPRequest> query);
};

class LocManager2 : public GenericController
{
public:
	LocManager2();
	virtual ~LocManager2();

	static std::string classId(){ return "LocManager2";}
	
	virtual std::auto_ptr<HTTPResponse> executeQuery(std::auto_ptr<HTTPRequest> query);
};



#endif // !defined(AFX_LOCMANAGER_H__8203B60B_9FC5_4067_A3A6_864EE5E89A07__INCLUDED_)
