// Service.cpp: implementation of the Service class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Exceptions.h"
#include "CriticalSection.h"
#include "memory_stream.h"
#include "Blob.h"
#include "FileUtil.h"
#include "System.h"
#include "ResourceManager.h"
#include "IInputStream.h"
#include "GZInputStream.h"
#include "IOutputStream.h"
#include "TarWriter.h"
#include "Tar.h"
#include "ILog.h"
#include "Socket.h"
#include "Log.h"
#include "LiteLog.h"
#include "PropertyBag.h"
#include "Properties.h"
#include "DynamicClass.h"
#include "Thread.h"

#include "Application.h"

#include "Service.h"


/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Service::Service()
{

}

Service::~Service()
{

}

void Service::run()
{

	// Inicializar 


	// INI

	// Comprobar si hemos recibido señal de finalización.

	do
	{
		Sleep(10000);
		
	}while(true);

	// Comprobar la fecha de ejecución de última ejecución y ver si ha pasado el periodo.

	// Guardar la fecha/hora de inicio de ejecución

	// Ejecutar

	// Guardar la fecha/hora de fin de ejecución

	// Volver a INI


	
}


} // namespace util

} // namespace stream
