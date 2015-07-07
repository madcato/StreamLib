#ifndef __TAR_HEADER__H_
#define __TAR_HEADER__H_


namespace Stream
{

const int blockSize = 512;

struct TarHeader
{
	char name[100]; //  File name without a / (slash)  
	char mode[8]; //  File mode  
	char uid[8]; //  User ID  
	char gid[8]; //  Group ID  
	char size[12]; //  Size in bytes  
	char mtime[12]; //  Latest modification time  
	char cksum[8]; //  File and header checksum  
	char typeflag; //  File type  
	char linkname[100]; //  Linked path name or file name  
	char magic[6]; //  Format representation for tar  
	char version[2]; //  Version representation for tar  
	char uname[32]; //  User name  
	char gname[32]; //  Group name  
	char devmajor[8]; //  Major device representation  
	char devminor[8]; //  Minor device representation  
	char prefix[155]; //  Path name without trailing slashes  
};

} // namespace Stream








#endif __TAR_HEADER__H_