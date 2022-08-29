#pragma once
#include "api/http/http_request.hpp"

namespace big::remote
{
	inline string get_etag_from_headers(vector<string> headers)
	{
		string remote_etag = "";

		for (auto& header : headers)
		{
			if (header.rfind(xorstr_("ETag"), 0) == 0)
			{
				remote_etag = header;
				break;
			}
		}

		return remote_etag;
	}
}