
#ifndef IDATA_PROCESSOR___H__
#define IDATA_PROCESSOR___H__


namespace stream
{

namespace io
{

/**
	Generic interface to processing data.
*/
class IDataProcessor
{
public:
	virtual ~IDataProcessor(){}

	
	virtual io::Blob<unsigned char> Update(unsigned char* buffer,unsigned long size) = 0;
	virtual io::Blob<unsigned char> Finish() = 0;
	virtual size_t available() = 0;
};

} // namespace io

} // namespace stream

#endif IDATA_PROCESSOR___H__