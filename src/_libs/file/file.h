#ifndef _LIBS_FILE_H
#define	_LIBS_FILE_H

#include "FileNotFoundException.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <vector>

class IFile
{
public:
	virtual const char* getPath() = 0;
	
	virtual std::vector<IFile*> listFiles() throw(int) = 0;
	
	virtual bool exists() = 0;
	
	virtual bool isDir() = 0;
	virtual bool isFile() = 0;
	
	virtual char readChar() = 0;
	virtual void readChar(char* charPtr) = 0;
	virtual int read(char* buffer, int max) = 0;
	
	virtual bool isOpen() = 0;
	
	virtual bool open() throw(FileNotFoundException) = 0;
	virtual void close() = 0;
	
	virtual const char* getFileName() = 0;
	virtual const char* getExtension() = 0;
	virtual const char* getMimeType() = 0;
	
	virtual bool isEndOfFile() = 0;
	
	virtual struct tm getLastModifiedTime() = 0;
	virtual struct tm getLastStatusChangedTime() = 0;
	virtual struct tm getLastAccessTime() = 0;
	
	virtual off_t getSize() = 0;
};

class File : public IFile
{
public:
	File(const char* path);
	File(std::string path);
	
	const char* getPath();
	
	std::vector<IFile*> listFiles() throw(int);
	
	bool exists();
	
	bool isDir();
	bool isFile();
	
	char readChar();
	void readChar(char* charPtr);
	int read(char* buffer, int max);
	
	bool isOpen();
	
	bool open() throw(FileNotFoundException);
	void close();
	
	const char* getFileName();
	const char* getExtension();
	const char* getMimeType();
	
	bool isEndOfFile();
	
	struct tm getLastModifiedTime();
	struct tm getLastStatusChangedTime();
	struct tm getLastAccessTime();
	
	off_t getSize();
	static off_t getMaxSize();
	
private:
	struct stat info;
	bool infoInitialized;
	bool exist;
	
	std::ifstream* inStream;
	std::ofstream* outStream;
	
	const char* path;
	
	struct stat& getInfo();
};



#endif	/* _LIBS_FILE_H */

