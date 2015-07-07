// TestClass.h: interface for the TestClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCLASS_H__0CA659C4_AB93_4223_BB80_077302B8845E__INCLUDED_)
#define AFX_TESTCLASS_H__0CA659C4_AB93_4223_BB80_077302B8845E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TestClass : public GenericController
{
public:
	TestClass();
	virtual ~TestClass();

	static std::string classId(){ return "TestClass";}
	
	virtual std::auto_ptr<HTTPResponse> executeQuery(std::auto_ptr<HTTPRequest> query);

};

#endif // !defined(AFX_TESTCLASS_H__0CA659C4_AB93_4223_BB80_077302B8845E__INCLUDED_)
