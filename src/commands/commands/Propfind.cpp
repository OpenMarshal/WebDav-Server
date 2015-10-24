#include "Propfind.h"

#include <ctime>

namespace cmds
{
	static std::string o(const std::string str)
	{
		return "<DAV:" + str + ">";
	}
	static std::string c(const std::string str)
	{
		return "</DAV:" + str + ">";
	}
	
	static void set_href(::IFile* rsFile, int rootPathSize, std::string host, std::ostringstream& stream)
	{
		stream << o("href");
		stream << "http://" << host << '/' << (rsFile->getPath() + rootPathSize + 1);
		stream << c("href");
	}
	static void set_status(std::ostringstream& stream)
	{
		stream << o("status");
		stream << "HTTP/1.1 200 OK";
		stream << c("status");
	}
	
	static void set_creationDate(struct tm date, std::ostringstream& stream)
	{
		char data[20];
		
		stream << o("creationdate");
		strftime(data, 20, "%Y-%m-%dT%X", &date);
		stream << data << "-00:00"; // 1997-12-01T17:42:21-08:00
		stream << c("creationdate");
	}
	
	static void set_fileName(::IFile* rsFile, std::ostringstream& stream)
	{
		stream << o("displayname");
		stream << rsFile->getFileName();
		stream << c("displayname");
	}
	
	static void set_supportedLocks(::IFile* rsFile, std::ostringstream& stream)
	{
		stream << o("supportedlock");
		stream << o("lockentry");
		stream << o("lockscope");
		stream << "<DAV:exclusive/>";
		stream << c("lockscope");
		stream << o("locktype");
		stream << "<DAV:write/>";
		stream << c("locktype");
		stream << c("lockentry");
		stream << o("lockentry");
		stream << o("lockscope");
		stream << "<DAV:shared/>";
		stream << c("lockscope");
		stream << o("locktype");
		stream << "<DAV:write/>";
		stream << c("locktype");
		stream << c("lockentry");
		stream << c("supportedlock");
	}
	
	static void set_contentType(::IFile* rsFile, std::ostringstream& stream)
	{
		stream << o("getcontenttype");
		stream << rsFile->getMimeType();
		stream << c("getcontenttype");
	}
	
	static void set_contentLength(::IFile* rsFile, std::ostringstream& stream)
	{
		stream << o("getcontentlength");
		stream << rsFile->getSize();
		stream << c("getcontentlength");
	}
	
	static void set_eTag(::IFile* rsFile, std::ostringstream& stream)
	{
		stream << o("getetag");
		stream << "zzyzx";
		stream << c("getetag");
	}
	
	static void set_lastModified(struct tm date, std::ostringstream& stream)
	{
		char data[26];
		
		stream << o("getlastmodified");
		strftime(data, 26, "%a, %d %b %Y %X", &date);
		// Mon, 12 Jan 1998 09:25:56 GMT
		stream << data << " GMT";
		stream << c("getlastmodified");
	}
	
	void Propfind::getResourceInfo(::IFile* rsFile, int rootPathSize, std::string host, std::ostringstream& stream)
	{
		struct tm timeinfo = rsFile->getLastModifiedTime();
		
		stream << o("response");
		
		set_href(rsFile, rootPathSize, host, stream);
		
		stream << o("propstat");
		set_status(stream);
		
		stream << o("prop");
		
		set_creationDate(timeinfo, stream);
		set_fileName(rsFile, stream);
		set_supportedLocks(rsFile, stream);
		
		if(rsFile->isDir())
		{
			stream << o("resourcetype");
			stream << "<DAV:collection/>";
			stream << c("resourcetype");
		}
		else
		{
			stream << "<DAV:resourcetype/>";
			
			set_contentType(rsFile, stream);
			set_contentLength(rsFile, stream);
			set_eTag(rsFile, stream);
			set_lastModified(timeinfo, stream);
		
		}
		
		stream << c("prop");
		
		stream << c("propstat");
		
		stream << c("response");
	}
	
	
	
	
	HttpResponseBuilder* Propfind::compute(ConnectionEnv* env, HttpRequest* request) throw(FileNotFoundException)
	{
		::IFile* rs = env->getFileFromPath(request);
		
		int rootLen = env->getRoot().size();
		
		if(!rs->exists())
			throw FileNotFoundException(rs->getPath());
		
		std::string host = request->getHeader("host", "");
		
		if(host.empty())
			host = std::string("");
		
		host = ::trim(host);
		
		const char v = host.back();
		if(v == '/' || v == '\\')
			host.pop_back();
		
		std::string depth = ::trim(request->getHeader("depth", "0"));
		
		std::ostringstream content;
		content << o("multistatus");
		
		getResourceInfo(rs, rootLen, host, content);
		
		if(depth.c_str()[0] == '0')
		{ // depth = 0
		}
		else
		{ // depth = 1
			if(rs->isDir())
			{
				for(::IFile* f : rs->listFiles())
					getResourceInfo(f, rootLen, host, content);
			}
		}
		content << c("multistatus");
		
		return &HttpResponse::create()
				.setCode(207)
				.setMessage("Multi-Status")
				.addHeader("Content-type", "text/xml; charset=\"utf-8\"")
				.setContent(content.str());
	}
}

