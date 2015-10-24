#include "file.h"

#include "General.h"
#include "_libs/error/ErrorManager.h"

#include <limits>
#include <ctime>
#include <algorithm>

#include <windows.h>
#include <tchar.h>
#include <stdio.h>


File::File(const char* path)
	: File(std::string(path))
{ }

File::File(std::string path)
	: infoInitialized(false),
	inStream(0),
	outStream(0)
{
	int size = path.size();
	this->path = new char[size + 1];
	char* p = const_cast<char*>(this->path);
	
	for(int i = 0; i < size; i++)
		p[i] = path.c_str()[i];
	p[size] = '\0';
}

const char* File::getPath()
{
	return path;
}

static const char mimeTypes[][2][128] = 
{     
	{"***",		"application/octet-stream"},
	{"CSV",		"text/csv"},
	{"TSV",		"text/tab-separated-values"},
	{"TAB",		"text/tab-separated-values"},
	{"HTML",	"text/html"},
	{"HTM",		"text/html"},
	{"DOC",		"application/msword"},
	{"DOCX",	"application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
	{"ODS",		"application/x-vnd.oasis.opendocument.spreadsheet"},
	{"ODT",		"application/vnd.oasis.opendocument.text"},
	{"RTF",		"application/rtf"},
	{"SXW",		"application/vnd.sun.xml.writer"},
	{"TXT",		"text/plain"},
	{"XLS",		"application/vnd.ms-excel"},
	{"XLSX",	"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
	{"PDF",		"application/pdf"},
	{"PPT",		"application/vnd.ms-powerpoint"},
	{"PPS",		"application/vnd.ms-powerpoint"}, 
	{"PPTX",	"application/vnd.openxmlformats-officedocument.presentationml.presentation"},
	{"WMF",		"image/x-wmf"},
	{"ATOM",	"application/atom+xml"},
	{"XML",		"application/xml"},
	{"JSON",	"application/json"},
	{"JS",		"application/javascript"},
	{"OGG",		"application/ogg"},
	{"PS",		"application/postscript"},
	{"WOFF",	"application/x-woff"},
	{"XHTML",	"application/xhtml+xml"},
	{"XHT",		"application/xhtml+xml"},
	{"ZIP",		"application/zip"},
	{"GZ",		"application/x-gzip"},
	{"RAR",		"application/rar"},
	{"RM",		"application/vnd.rn-realmedia"},
	{"RMVB",	"application/vnd.rn-realmedia-vbr"},
	{"SWF",		"application/x-shockwave-flash"},
	{"AU",		"audio/basic"},
	{"SND",		"audio/basic"},
	{"MID",		"audio/mid"},
	{"RMI",		"audio/mid"},
	{"MP3",		"audio/mpeg"},
	{"AIF",		"audio/x-aiff"},
	{"AIFC",	"audio/x-aiff"},
	{"AIFF",	"audio/x-aiff"},
	{"M3U",		"audio/x-mpegurl"},
	{"RA",		"audio/vnd.rn-realaudio"},
	{"RAM",		"audio/vnd.rn-realaudio"},
	{"WAV",		"audio/x-wave"},
	{"WMA",		"audio/x-ms-wma"},
	{"M4A",		"audio/x-m4a"},
	{"BMP",		"image/bmp"},
	{"GIF",		"image/gif"},
	{"JPE",		"image/jpeg"},
	{"JPEG",	"image/jpeg"},
	{"JPG",		"image/jpeg"},
	{"JFIF",	"image/jpeg"},
	{"PNG",		"image/png"},
	{"SVG",		"image/svg+xml"},
	{"TIF",		"image/tiff"},
	{"TIFF",	"image/tiff"},
	{"ICO",		"image/vnd.microsoft.icon"},
	{"CSS",		"text/css"},
	{"BAS",		"text/plain"},
	{"C",		"text/plain"},
	{"H",		"text/plain"},
	{"RTX",		"text/richtext"},
	{"MP2",		"video/mpeg"},
	{"MPA",		"video/mpeg"},
	{"MPE",		"video/mpeg"},
	{"MPEG",	"video/mpeg"},
	{"MPG",		"video/mpeg"},
	{"MPV2",	"video/mpeg"},
	{"MOV",		"video/quicktime"},
	{"QT",		"video/quicktime"},
	{"LSF",		"video/x-la-asf"},
	{"LSX",		"video/x-la-asf"},
	{"ASF",		"video/x-ms-asf"},
	{"ASR",		"video/x-ms-asf"},
	{"ASX",		"video/x-ms-asf"},
	{"AVI",		"video/x-msvideo"},
	{"3GP",		"video/3gpp"},
	{"3GPP",	"video/3gpp"},
	{"3G2",		"video/3gpp2"},
	{"MOVIE",	"video/x-sgi-movie"},
	{"MP4",		"video/mp4"},
	{"WMV",		"video/x-ms-wmv"},
	{"WEBM",	"video/webm"},
	{"M4V",		"video/x-m4v"},
	{"FLV",		"video/x-flv"}
};

const char* File::getFileName()
{
	const char* end = path + strlen(path);
	
	char seek[] = "/";
	const char* found = std::find_end(path, end, seek, seek + 1);
	
	if(found == end)
		found = path;
	
	seek[0] = '\\';
	const char* found2 = std::find_end(found, end, seek, seek + 1);
	
	if(found2 == end)
		found2 = found;
	
	if(found2[0] == '/' || found2[0] == '\\')
		found2++;
	
	return found2;
}

const char* File::getExtension()
{
	const char* end = path + strlen(path);
	
	char limiter[] = ".";
	const char* ext = std::find_end(path, end, limiter, limiter + 1);
	
	if(ext == end)
		ext = path;
	else
		ext++;
	
	return ext;
}
const char* File::getMimeType()
{
	if(isDir())
		return "inode/directory";
	
	const char* ext = getExtension();
	
	int len = strlen(ext);
	char extMaj[len + 1];
	std::transform(ext, ext + len, extMaj, ::toupper);
	extMaj[len] = '\0';

	for (int i = 0; i < sizeof(mimeTypes) / sizeof(mimeTypes[0]); i++) 
	{
		if(len != strlen(mimeTypes[i][0]))
			continue;
		
		if(::strcmp(mimeTypes[i][0], extMaj) == 0)
			return mimeTypes[i][1];
	}  
	return mimeTypes[0][1];
}

std::vector<IFile*> File::listFiles() throw(int)
{
	std::vector<IFile*> vect;
	std::string parentPath;
	parentPath += path;
	parentPath += '/';
	
	#if OS == WIN
		std::string parentPathPattern;
		parentPathPattern += parentPath;
		parentPathPattern += '*';
		
		WIN32_FIND_DATA data;
		HANDLE hd;

		hd = ::FindFirstFile(parentPathPattern.c_str(), &data);
		if (hd == INVALID_HANDLE_VALUE)
		{
			int error = ::getErrorNo();
			throw error;
		}
		else
		{
			do
			{
				int nbNameChar = strlen(data.cFileName);
				if(nbNameChar >= 1 && data.cFileName[0] == '.')
				{
					if(nbNameChar == 2)
					{
						if(data.cFileName[1] == '.')
							continue;
					}
					else
						continue;
				}
				
				std::string fl;
				fl += parentPath;
				fl += data.cFileName;
				
				vect.push_back(new File(fl));
			} while(::FindNextFile(hd, &data));
			::FindClose(hd);
		}
	#elif OS == LINUX
		DIR* dir;
		if((dir = ::opendir(path)) == 0)
		{
			int error = ::getErrorNo();
			throw error;
		}

		struct dirent* child;
		while(child = ::readdir(dir))
		{
			std::string fl;
			fl += parentPath;
			fl += child->d_name;
			
			vect.push_back(new File(fl));
		}
		::closedir(dir);
	#endif
	
	return vect;
}


struct stat& File::getInfo()
{
	if(!infoInitialized)
	{
		exist = ::stat(path, &info) == 0;
		infoInitialized = true;
	}
	
	return info;
}

struct tm File::getLastModifiedTime()
{
	return *::gmtime(&getInfo().st_mtime);
}
struct tm File::getLastStatusChangedTime()
{
	return *::gmtime(&getInfo().st_ctime);
}
struct tm File::getLastAccessTime()
{
	return *::gmtime(&getInfo().st_atime);
}

off_t File::getSize()
{
	return getInfo().st_size;
}

off_t File::getMaxSize()
{
	return std::numeric_limits<off_t>::max();
}



bool File::exists()
{
	getInfo();
	return exist;
}

bool File::isDir()
{
	return getInfo().st_mode & S_IFDIR;
}
bool File::isFile()
{
	return !isDir();
}
	
bool File::open() throw(FileNotFoundException)
{
	if(!exists())
		throw FileNotFoundException(path);
	
	inStream = new std::ifstream(path);
	return this->isOpen();
}

char File::readChar()
{
	char data;
	inStream->get(data);
	return data;
}
void File::readChar(char* charPtr)
{
	inStream->get(*charPtr);
}

bool File::isEndOfFile()
{
	if(inStream)
		return inStream->eof();
	if(outStream)
		return inStream->eof();
	return false;
}

bool File::isOpen()
{
	if(inStream)
		return inStream->is_open();
	if(outStream)
		return outStream->is_open();
	return false;
}

void File::close()
{
	if(inStream)
	{
		inStream->close();
		inStream = 0;
	}
	if(outStream)
	{
		outStream->close();
		outStream = 0;
	}
}


int File::read(char* buffer, int max)
{
	int i;
	for(i = 0; i < max && !isEndOfFile(); i++)
		readChar(buffer + i);
	return i;
}

