// TestState.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "FLineParser.h"

class TestState: public StateMachine
{
public:
	TestState(std::auto_ptr<IInputStream> data):StateMachine(data)
	{
	}

DECLARE_NOTIFY_MAP()
	NOTIFY("S1",Estado1)
	NOTIFY("S2",Estado2)
	NOTIFY("S3",Estado3)
END_NOTIFY_MAP()

DECLARE_TRAN_MAP()
	TRAN("S1+V2",Tran1);
END_TRAN_MAP()

DECLARE_EVENT_MAP()
	EVENT("V2",Event1)
END_EVENT_MAP()
protected:
	void doError(const std::string& currentState, const std::string& lastEvent)
	{
		int a = 0;
	}

private:
	void Estado1()
	{
		int a = 0;
	}
	void Estado2()
	{
		int a = 0;
	}
	void Estado3()
	{
		int a = 0;
	}
	void Tran1()
	{
		int a = 0;
	}
	void Event1()
	{
		int a = 0;
	}
};


int main(int argc, char* argv[])
{


	FLineParser fl("E1:tipo:int(2),E2:codigoMoneda:int(2),E3:NIF:nif(10),E4:texto:str(20),E5:referencia:int(10),E6:codigoRetencion:int(2)");
	fl.parse("0304123456789G       Hola Texto 12000000000003");




	IInputStreamPtr data = IInputStreamPtr(new FileInputStream("states.txt")) ;



	TestState t(data);

	t.event("V2");	

	t.event("V1");
	
	t.event("V2");

	t.event("V1");

	t.event("V2");

	return 0;
}
