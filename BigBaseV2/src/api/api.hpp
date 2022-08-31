#pragma once
#include "http/httplib.hpp"
#include <exception>

//Not sure if I should xor encrypt this

namespace big::api
{
	const string domain = xorstr_("api.gaminghard.xyz:80");
	inline string session_id;

	namespace auth
	{
		static string token;
		static string refresh_token;

		static nlohmann::json sign_in(string passed_refresh_token)
		{
			httplib::Client cli(domain);

			httplib::Headers headers = { { xorstr_("Authorization"), xorstr_("Bearer ") + passed_refresh_token } };

			httplib::Result res = cli.Get(xorstr_("/refresh"), headers);
			nlohmann::json json = nlohmann::json::parse(res->body.c_str());

			token = json[xorstr_("access_token")];
			refresh_token = json[xorstr_("refresh_token")];

			return json[xorstr_("uinfo")];
		}

		static nlohmann::json refresh()
		{
			httplib::Client cli(domain);

			httplib::Headers headers = { { xorstr_("Authorization"), xorstr_("Bearer ") + token } };
			httplib::Result res = cli.Get(xorstr_("/logout"), headers);

			headers = { { xorstr_("Authorization"), xorstr_("Bearer ") + refresh_token } };

			res = cli.Get(xorstr_("/refresh"), headers);

			nlohmann::json json = nlohmann::json::parse(res->body.c_str());

			token = json[xorstr_("access_token")];
			refresh_token = json[xorstr_("refresh_token")];

			return json[xorstr_("uinfo")];
		}

		static bool create_session() { return false; }
	}
}