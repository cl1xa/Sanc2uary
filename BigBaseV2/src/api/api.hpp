#pragma once
#include "http/http_request.hpp"
#include "http/httplib.hpp"
#include <exception>

//Not sure if I should xor encrypt this

namespace big::api
{
	const std::string domain = "api.gaminghard.xyz:80";
	inline std::string session_id;

	namespace util
	{
		static std::string authorization_header() { return std::string("Authorization: ") + api::session_id; }

		static nlohmann::json parse_body(std::string res)
		{
			LOG(INFO) << xorstr_("Parsing body");

			return nlohmann::json::parse(res.begin(), res.end());
		}

		static bool signed_in() { return !session_id.empty(); }
	}

	namespace auth
	{
		static std::string token;
		static std::string refresh_token;

		static nlohmann::json sign_in(std::string passed_refresh_token)
		{
			httplib::Client cli(domain);

			httplib::Headers headers = { { "Authorization", "Bearer " + passed_refresh_token } };

			httplib::Result res = cli.Get("/refresh", headers);
			nlohmann::json json = nlohmann::json::parse(res->body.c_str());

			token = json["access_token"];
			refresh_token = json["refresh_token"];

			return json["uinfo"];
		}

		static nlohmann::json refresh()
		{
			httplib::Client cli(domain);

			httplib::Headers headers = { { "Authorization", "Bearer " + token } };
			httplib::Result res = cli.Get("/logout", headers);

			headers = { { "Authorization", "Bearer " + refresh_token } };

			res = cli.Get("/refresh", headers);

			nlohmann::json json = nlohmann::json::parse(res->body.c_str());

			token = json["access_token"];
			refresh_token = json["refresh_token"];

			return json["uinfo"];
		}

		static bool create_session() { return false; }
	}
}