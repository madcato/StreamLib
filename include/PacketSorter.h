// PacketSorter.h: interface for the PacketSorter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKETSORTER_H__016B42FB_288F_4FFD_A04A_7F30EA20B681__INCLUDED_)
#define AFX_PACKETSORTER_H__016B42FB_288F_4FFD_A04A_7F30EA20B681__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{


class PacketSorter  
{
public:
	PacketSorter(io::IInputStreamPtr configurationStream);
	virtual ~PacketSorter();

	std::string sort(const std::string& line);

private:
	void init(io::IInputStreamPtr configurationStream);

	class LinePattern
	{
	public:
		std::string m_id;
		long m_size;
		std::string m_pattern;

	};


	std::vector<LinePattern> m_vectorPatterns;

};

} // namespace util

} // namespace stream

#endif // !defined(AFX_PACKETSORTER_H__016B42FB_288F_4FFD_A04A_7F30EA20B681__INCLUDED_)
