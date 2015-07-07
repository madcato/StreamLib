// FileUtil.h: interface for the FileUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEUTIL_H__2FB18438_793C_4173_AE2C_0B472CB28469__INCLUDED_)
#define AFX_FILEUTIL_H__2FB18438_793C_4173_AE2C_0B472CB28469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/// namespace stream
namespace stream
{


/// Grupo de excepciones de la librería stream
namespace exceptions
{


	/**
		FileUtil exception.
	*/
	class FileUtilException : public StreamException
	{
	public:
		FileUtilException(int id_code,std::string desc = ""):StreamException(id_code,desc)
		{
		}
	};

	/**
		DirectoryNotFound exception
	*/
	class DirectoryNotFoundStreamException : public FileUtilException
	{
	public:
		DirectoryNotFoundStreamException(int id_code,std::string desc = ""):FileUtilException(id_code,desc)
		{
		}
	};



} // namespace Exception

/// namespace util
namespace util
{

/**
	File utilities class.
	This class has only static methods.
*/
class FileUtil  
{
public:
	FileUtil();
	virtual ~FileUtil();

	/**
		Recursively remove a directory: files and subfolders.
		@param path Directory path
		@return <B>true</B> when the directory is completely removed, returns <B>false</B> when
		any file or subdirectory haven't been removed; probably read-only attributes.
	*/
	static bool RecursiveRemoveDirectory(const std::string path) throw(exceptions::DirectoryNotFoundStreamException*);

	/**
		Check file size
		@param path File path
		@return file size in bytes or <B>-1</B> if file cannot be opened.
		
	*/
	static long FileSize(const std::string& path);

	/** 
		Check for file existence
		@param path File path
		@return <B>true</B> if the file exits
	*/
	static bool fileExists(const std::string& path);

	/**
		This method puts a back slash <B>\</B> in <B>path</B>, only if it doesn't exists
		@param path Directory path
		@return <B>-1</B> if path is empty. 
	*/
	static long PutFinalSlashInPath(std::string& path);

	/** 
		Creates a new directory.
		@param path Directory path
		@param failOnExistence If set to <B>true</B> and directory already exists, then a exceptions::FileUtilException
				is thrown
		@return <B>-1</B> if directory creation fails.
	*/
	static long createDirectory(const std::string& path,bool failOnExistence = false);

	/** 
		
		This enum sets the type of check for a the file time:
		@see DeleteOldFiles
		<br>
			<lu>
			<li>CREATION_TIME</li>
			<li>LAST_ACCESS_TIME</li>
			<li>LAST_WRITE_TIME</li>
			</lu>
		
	*/
	enum FILE_TIME_TYPE
	{
		CREATION_TIME,
		LAST_ACCESS_TIME,
		LAST_WRITE_TIME
	};
	/**
		Delete old files in a path. This method checks for file time who time of creation, modification or acces is less than actual time minus 'miliseconds_old'
		@param path Directory path
		@param miliseconds_old time in miliseconds of th antiquity of files.
		@param ftt file time type of check.
		@return <B>-1</B> if drectory cannot be accessed.
		@see FILE_TIME_TYPE
	*/
	static long DeleteOldFiles(const std::string& path, long miliseconds_old, enum FILE_TIME_TYPE ftt) throw(exceptions::FileUtilException*);


	/**
		Create a file name formated with the actual date and time, and an optional extension.
		Format: YYYYMMDDHHMMSS[.ext]
		File name es concatenated to a path.
		This method doesn't create the file.
		@param path Directory path
		@param extension Optional. If this param is set, is concatenated to the end of the file name like an extension(with a dot)
		@return <B>-1</B> if method fails
	*/
	static std::string  getDatedFileName(const std::string& path, const std::string& extension = "") throw(exceptions::FileUtilException*);

	/**
		Create a file name formated with the actual date and time, and an optional extension.
		Format: YYYYMMDD[.ext]
		File name es concatenated to a path.
		This method doesn't create the file.
		@param path Directory path
		@param extension Optional. If this param is set, is concatenated to the end of the file name like an extension(with a dot)
		@return <B>-1</B> if method fails
	*/
	static std::string  getDailyDatedFileName(const std::string& path, const std::string& extension = "") throw(exceptions::FileUtilException*);
	

	/**
		@return the directory size including subdirectories.
	*/
	static long getDirectorySize(const std::string& directory);

	/**
		Extract the file name from the end of a path.
		@param path file path		
		@return A file name
	*/
	static std::string ExtractFileNameFromPath(std::string path);

	/**
		Remove the file name from the end of a path.
		@param path file path		
		@return A directory name
	*/
	static std::string RemoveFileNameFromPath(std::string path);

	/**
		Replace the special folder chars (Win32) with a new char.
		Special folders chars are: \/:"<>|*
		@param str string to be manipulated.
		@param newChar new char.
		@return the new string without the special folders.
	*/
	static std::string ReplaceSpecialFolderChars(const std::string& str,char newChar);


	/**
		Checks if the caracter is a special folder character.
		@param newChar new char.
		@return true if newChar is a special folder character.
	*/
	static bool isSpecialFolderChar(char newChar);

	/**
		Check if it's a valid file name. Don't pass the complete path: a path it isn't a valid name
		@param name File name to check.
		@return true if none of the name characters is a special folder path.
	*/
	static bool FileUtil::isValidFileName(std::string& name);

	/**
		Read a file and returns its content.
		@param filePath Path of the file.
		@return A buffer with the content of the file.
	*/
	static io::Blob<char> File2Buffer(const std::string& filePath);

	/** 
		Write a buffer into a file.
		@param blob Buffer to dump in the file.
		@param filePath Path of the file.
	*/
	static void Buffer2File(const io::Blob<char>& blob,const std::string& filePath);

	/**
		Replace all the slash('/') of the path
	*/
	static void replaceSlash(std::string& path);

	/**
		Replace all the backslash('\\') of the path
	*/
	static void replaceBackSlash(std::string& path);

	static std::string binToHex(const io::Blob<unsigned char>& blob);
	static io::Blob<unsigned char> hexToBin(const std::string& hex);

	/**
		Delete File
	*/
	static void deleteFile(const std::string& filename);

	/**
		Converts a path("C:\proyectos\entidades.htm") to a URI("file:///C:/proyectos/entidades.htm");
	*/
	static std::string pathToUri(const std::string& path);

	/**
		Returns a unique file name(that doesn't exists) in the user temp path.
		@return a complete path to file.
	*/
	static std::string FileUtil::getTempFileName();

	/**
		Searchs for files in a directory
		@param filesWildcard Search Pattern. Example: "D:\files\*.txt"
		@return A vector with the files found.
	*/
	std::vector<std::string> listFiles(const std::string& filesWildcard);

	/**
		Searchs for subdirectories in a directory
		@param dirWildcard Search Pattern. Example: "D:\files\*.txt"
		@return A vector with the directories found.
	*/
	std::vector<std::string> listDirs(const std::string& dirsWildcard);
};

} // namespace util

} //namespace stream
#endif // !defined(AFX_FILEUTIL_H__2FB18438_793C_4173_AE2C_0B472CB28469__INCLUDED_)
