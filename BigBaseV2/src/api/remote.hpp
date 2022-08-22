#pragma once
#include "api/http_request.hpp"

namespace big::remote
{
	inline std::string get_etag_from_headers(std::vector<std::string> headers)
	{
		std::string remote_etag = "";

		for (auto& header : headers)
		{
			if (header.rfind("ETag", 0) == 0)
			{
				remote_etag = header;
				break;
			}
		}

		return remote_etag;
	}


	inline bool update_binary(const std::string_view file_url, const std::filesystem::path& file_location, const std::filesystem::path& etag_location)
	{
		

		return false;
	}
}