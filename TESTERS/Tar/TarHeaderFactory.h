// TasHeaderFactory.h: interface for the TasHeaderFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASHEADERFACTORY_H__9425B06B_E771_4857_BEEF_CC2C10AD3645__INCLUDED_)
#define AFX_TASHEADERFACTORY_H__9425B06B_E771_4857_BEEF_CC2C10AD3645__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TarHeaderFactory  
{
public:
	TarHeaderFactory();
	virtual ~TarHeaderFactory();

	static void CreateFileHeader(TarHeader& tarHeader,const std::string& fileName,unsigned long size);
	static void CreateDirectoryHeader(TarHeader& tarHeader,const std::string& directoryName);

private:
	static void CreateDefaultHeader(TarHeader& tarHeader);
	static void SetChecksum(TarHeader& tarHeader);
	static unsigned long CalculateChecksum(TarHeader& tarHeader);
};

#endif // !defined(AFX_TASHEADERFACTORY_H__9425B06B_E771_4857_BEEF_CC2C10AD3645__INCLUDED_)
