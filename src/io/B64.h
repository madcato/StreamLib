// B64.h: interface for the B64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_B64_H__50881CFC_34D3_436F_8013_303F8C7406FD__INCLUDED_)
#define AFX_B64_H__50881CFC_34D3_436F_8013_303F8C7406FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/**
 namespace io.
 Provides for system input and output through data streams, serialization and the file system. 
*/
namespace io
{

/**
	Type of processing. Encode/Decode BASE64
*/
enum EProcessType
{
	/// Encode BASE64
	OPEN_FOR_ENCODING,
	/// Decode BASE64
	OPEN_FOR_DECODING
};
/**
	This class encodes/decodes data to/from BASE64.
*/
class B64 : public IDataProcessor
{
public:
	B64(EProcessType type,size_t bufferLength = 4096);
	virtual ~B64();


	/**
		Includes new data to the encoding/decoding proccess.
		This method doesn´t finalice the process: call Finish
		@param buffer New data
		@param size Size of the buffer
		@return The already encoded/decoded proccess.
	*/
	Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
	/**
		This method finishes the proccess.
		@return The final data encoded or decoded.
	*/
	Blob<unsigned char> Finish();
	/**
		@return The size of the data ready to be read.
	*/
	size_t available();
	/**
		@return true if the proccess has been finished.
	*/
	bool finished();

private:
	bool m_finished;

	class B64Encoder : public IDataProcessor
	{
	public:
		B64Encoder(size_t bufferLength);

		Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
		Blob<unsigned char> Finish();
		size_t available();
	private:
		char m_tempBucket[4];
		long m_state;
		Blob<unsigned char> m_buffer;
		
		void DumpData();

		size_t m_bufferLength;
		void InitBuffer();
	};
	class B64Decoder : public IDataProcessor
	{
	public:
		B64Decoder(size_t bufferLength);

		Blob<unsigned char> Update(unsigned char* buffer,unsigned long size);
		Blob<unsigned char> Finish();
		size_t available();
	private:
		char m_tempBucket[3];
		
		Blob<unsigned char> m_buffer;
		
		void DumpData();
		bool _IsBadMimeChar(char nData);

		size_t m_bufferLength;
		int m_state;

		void InitDecodingTable();
		static char m_DecodeTable[256];
		static bool m_initDecodingTable;
		void InitBuffer();
	};

	std::auto_ptr<IDataProcessor> m_processor;
};

} // namespace io

} // namespace stream

#endif // !defined(AFX_B64_H__50881CFC_34D3_436F_8013_303F8C7406FD__INCLUDED_)
