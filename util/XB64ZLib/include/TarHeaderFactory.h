// TarHeaderFactory.h: interface for the TarHeaderFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARHEADERFACTORY_H__9E530EA2_EA88_473B_9164_8BBF20EDA65B__INCLUDED_)
#define AFX_TARHEADERFACTORY_H__9E530EA2_EA88_473B_9164_8BBF20EDA65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

class TarHeaderFactory  
{
public:
	TarHeaderFactory();
	virtual ~TarHeaderFactory();

	static void CreateFileTarHeader(TarHeader& tarHeader, const std::string& path, unsigned long fileSize);
	static void CreateTarHeaderFromBuffer(unsigned char* buffer, TarHeader& tarHeader);
	static void CreateDirectoryTarHeader(TarHeader& tarHeader, const std::string& path);
	static void CreateLongLinkTarHeader(TarHeader& tarHeader, unsigned long pathSize);

private:
	static int CalculateCheckSum(TarHeader& tarHeader);
	static void CreateDefaultTarHeader(TarHeader& tarHeader);
};

} // namespace util

} // namespace stream

#endif // !defined(AFX_TARHEADERFACTORY_H__9E530EA2_EA88_473B_9164_8BBF20EDA65B__INCLUDED_)
