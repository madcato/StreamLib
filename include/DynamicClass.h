// DynamicClass.h: interface for the DynamicClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNAMICCLASS_H__154FF870_D224_4BFB_BD81_204E09A37870__INCLUDED_)
#define AFX_DYNAMICCLASS_H__154FF870_D224_4BFB_BD81_204E09A37870__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace stream
{

	/// namespace exceptions
	namespace exceptions
	{

		/**
		util exception.
		*/
		class DynamicClassException : public StreamException
		{
		public:
			DynamicClassException(std::string desc = ""):StreamException(-1,desc)
			{
			}
		};
	} // namespace exceptions

	
/// namespace util
namespace util
{


/** 
	This class implement a system to perform dynamic method invocation.
	Derive from this class. Then call method <b>invoke</b> to call method.
	<br>
	Sample code:
	<code>
class TestClass : public DynamicClass<br>
{<br>
public:<br>
<br>
BEGIN_METHOD_MAP(TestClass)<br>
&nbsp;&nbsp;DECLARE_METHOD(run1)<br>
&nbsp;&nbsp;DECLARE_METHOD(run2)<br>
END_METHOD_MAP()<br>
<br>
&nbsp;&nbsp;void run1(const Properties& input,Properties& output)<br>
&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;&nbsp;csout << "Method run1 called" << endln;<br>
&nbsp;&nbsp;}<br>
<br>
&nbsp;&nbsp;void run2(const Properties& input,Properties& output)<br>
&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;&nbsp;csout << "Method run2 called" << endln;<br>
&nbsp;&nbsp;}<br>
};<br>
<br>
int main(int argc, char* argv[])<br>
{<br>
<br>
&nbsp;&nbsp;try<br>
&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;&nbsp;TestClass c;<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;Properties args;<br>
&nbsp;&nbsp;&nbsp;&nbsp;Properties oargs;<br>
<br>
&nbsp;&nbsp;&nbsp;&nbsp;c.invoke("run1",args,oargs);<br>
&nbsp;&nbsp;&nbsp;&nbsp;c.invoke("run2",args,oargs);<br>
&nbsp;&nbsp;&nbsp;&nbsp;c.invoke("run3",args,oargs); // <---- Method not delcared, exception is thrown.<br>
<br>
&nbsp;&nbsp;}catch(exceptions::StreamException* e)<br>
&nbsp;&nbsp;{<br>
&nbsp;&nbsp;&nbsp;&nbsp;csout << e->what() << endln;<br>
&nbsp;&nbsp;}<br>
&nbsp;&nbsp;return 0;<br>
}<br>
  </code>
  Output:
  <code>
Method run1 called<br>
Method run2 called<br>
Method 'run3' not declared in class 'TestClass'<br>
  </code>
*/
class DynamicClass
{
public:
	DynamicClass();
	virtual ~DynamicClass();

	/**
		Invoke a dynamic method.
		@param methodId Method name. The name of the function must be equal to its id.
		@param inputParameters Arguments values of the method.
		@param outputParameters Values returned by the method.
	*/
	void invoke(const std::string& methodId, const Properties& inputParameters,Properties& outputParameters);

	virtual std::string classId() = 0;
private:
	virtual void invoke_internal(const std::string& methodId, const Properties& inputParameters,Properties& outputParameters) = 0;
};

#define BEGIN_METHOD_MAP(className) virtual std::string classId() {return #className;} void invoke_internal(const std::string& methodId, const Properties& inputParameters,Properties& outputParameters) {

#define DECLARE_METHOD(x) if(methodId == #x) {x(inputParameters,outputParameters);return;}

#define END_METHOD_MAP() throw new exceptions::DynamicClassException("Method '" + methodId + "' not declared in class '" + classId() + "'"); }


/*
class MethodInvocation
{
string m_classId;
string m_methodId;
Properties* m_inputParameters;
Properties* m_outputParameters
};
*/
} // namespace util

} // namespace stream

#endif // !defined(AFX_DYNAMICCLASS_H__154FF870_D224_4BFB_BD81_204E09A37870__INCLUDED_)
