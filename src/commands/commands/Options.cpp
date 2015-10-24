#include "Options.h"

namespace cmds
{
	HttpResponseBuilder* Options::compute(ConnectionEnv* env, HttpRequest* request)
	{
		return &HttpResponse::create()
				.setCode(200)
				.setMessage("OK")
				.addHeader("Allow", "OPTIONS, PROPFIND")
				.addHeader("Content-type", "text/xml; charset=\"utf-8\"");
	}
}

