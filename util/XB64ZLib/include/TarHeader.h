#ifndef __TAR_HEADER__H_
#define __TAR_HEADER__H_

/// namespace stream
namespace stream
{

/// namespace util
namespace util
{

const int blockSize = 512;

/**
	Header of each file or directory entry in a tar
*/
struct TarHeader
{
	///  File name without a / (slash)  
	char name[100]; 
	///  File mode  
	char mode[8];
	///  User ID  
	char uid[8]; 
	///  Group ID  
	char gid[8]; 
	///  Size in bytes  
	char size[12]; 
	///  Latest modification time  
	char mtime[12];
	///  File and header checksum  
	char cksum[8]; 
	///  File type  
	char typeflag; 
	///  Linked path name or file name  
	char linkname[100]; 
	///  Format representation for tar  
	char magic[6]; 
	///  Version representation for tar  
	char version[2]; 
	///  User name  
	char uname[32]; 
	///  Group name  
	char gname[32]; 
	 ///  Major device representation  
	char devmajor[8];
	///  Minor device representation  
	char devminor[8]; 
	///  Path name without trailing slashes  
	char prefix[155]; 
};

} // namespace util

} /// namespace stream








#endif __TAR_HEADER__H_