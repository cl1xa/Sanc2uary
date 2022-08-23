#pragma once
#include "http_request.hpp"
#include "httplib.hpp"
#include <exception>
namespace big::api
{
	const std::string domain = "api.gaminghard.xyz:80";
	//const std::string domain = "";
	inline std::string session_id;

	namespace util
	{
		static std::string authorization_header()
		{
			return std::string("Authorization: ") + api::session_id;
		}

		static nlohmann::json parse_body(std::string res)
		{

				LOG(INFO) << "parsing body";
				return nlohmann::json::parse(res.begin(), res.end());

		}
		
		

		static bool signed_in()
		{
			return !session_id.empty();
		}
	}

	namespace auth
	{

		static std::string token;
		static std::string refresh_token;
		static nlohmann::json sign_in(std::string passed_refresh_token)
		{
			httplib::Client cli(domain);

			httplib::Headers headers = {
				 { "Authorization", "Bearer " + passed_refresh_token }
			};

			httplib::Result res = cli.Get("/refresh", headers);
			nlohmann::json json = nlohmann::json::parse(res->body.c_str());

			token = json["access_token"];
			refresh_token = json["refresh_token"];
			return json["uinfo"];
		}
		static nlohmann::json refresh()
		{
			httplib::Client cli(domain);

			httplib::Headers headers = {
				 { "Authorization", "Bearer " + token }
			};
			httplib::Result res = cli.Get("/logout", headers);


			headers = {
				 { "Authorization", "Bearer " + refresh_token }
			};
			res = cli.Get("/refresh", headers);

			nlohmann::json json = nlohmann::json::parse(res->body.c_str());

			token = json["access_token"];
			refresh_token = json["refresh_token"];

			return json["uinfo"];
		}
		static bool create_session()
		{
			return false;
		}
	}


	namespace vehicle
	{
		namespace handling
		{
			static bool create_profile(uint32_t handling_hash, const char* name, const char* description, nlohmann::json& handling_data, nlohmann::json& out)
			{
				return true;
			}

			static bool get_by_share_code(std::string share_code, nlohmann::json& out)
			{
				return true;
			}

			static bool get_my_handling(uint32_t handling_hash, nlohmann::json &out)
			{
				return true;
			}

			static bool get_saved_handling(uint32_t handling_hash, nlohmann::json& out)
			{
				return true;
			}

			static bool save_profile(std::string share_code)
			{
				return true;
			}

			static bool update(uint32_t handling_hash, const char* name, const char* description, std::string share_code, nlohmann::json &update)
			{
				return true;
			}
		}
	}
}