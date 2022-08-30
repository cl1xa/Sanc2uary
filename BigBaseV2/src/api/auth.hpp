#pragma once

namespace big::api
{
	bool has_logged = false;

	inline void auth_loop()
	{
		LOG(INFO) << "API ping";

		if (!has_logged)
		{
			LOG(INFO) << xorstr_("Checking for JWT");

			filesystem::path cheatpath = getenv(xorstr_("appdata"));
			cheatpath /= xorstr_("GamingHard/jwt.txt");

			string line;
			string jwt;

			ifstream jwtFile(cheatpath);

			if (jwtFile.good())
				while (getline(jwtFile, line)) { jwt = line; }
			else
			{
				LOG(WARNING) << xorstr_("JWT file bad!");

				jwtFile.close();
				remove(cheatpath);
				g_running = false;
			}
			jwtFile.close();

			remove(cheatpath);

			LOG(INFO) << xorstr_("Getting UINFO");

			nlohmann::json uinfo = api::auth::sign_in(jwt);

			LOG(INFO) << xorstr_("Getting HWID");

			DWORD userNumb;
			GetVolumeInformation(0, nullptr, 0, &userNumb, nullptr, nullptr, nullptr, 0);
			string hwid = to_string(userNumb);

			LOG(INFO) << xorstr_("Checking user validity");

			//Check #1?
			if (uinfo[xorstr_("sub_left")] == string(xorstr_("0")))
			{
				LOG(WARNING) << xorstr_("No time left!");

				g_running = false;
			}
			has_logged = true;

			LOG(INFO) << xorstr_("User authentication complete");
		}

		nlohmann::json uinfo = api::auth::refresh();

		DWORD userNumb;
		GetVolumeInformation(0, nullptr, 0, &userNumb, nullptr, nullptr, nullptr, 0);
		string hwid = to_string(userNumb);

		//Check #2?
		if (uinfo[xorstr_("sub_left")] == string(xorstr_("0")))
		{
			LOG(WARNING) << xorstr_("No time left!");

			g_running = false;
		}
	}
}