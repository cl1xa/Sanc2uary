#pragma once

namespace big::api
{
	inline void auth_loop()
	{
		//QUEUE_JOB_BEGIN_CLAUSE {
		g_thread_pool->push([]
			{
				bool has_logged = false;
				while (g_running)
				{
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
							exit(0);
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
							exit(0);
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
						exit(0);
					}
					this_thread::sleep_for(1s);
				}
			});
		//} QUEUE_JOB_END_CLAUSE
	}
}