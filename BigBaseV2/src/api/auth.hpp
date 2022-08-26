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

						std::filesystem::path cheatpath = std::getenv(xorstr_("appdata"));
						cheatpath /= xorstr_("GamingHard/jwt.txt");

						std::string line;
						std::string jwt;
						std::ifstream jwtFile(cheatpath);

						if (jwtFile.good())
						{
							while (std::getline(jwtFile, line))
							{
								jwt = line;
							}
						}
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
						std::string hwid = std::to_string(userNumb);

						LOG(INFO) << xorstr_("Checking user validity");

						//Check #1?
						if (uinfo["sub_left"] == std::string("0"))
						{
							LOG(WARNING) << "No time left!";
							exit(0);
						}
						has_logged = true;

						LOG(INFO) << "User authentication complete";
					}

					nlohmann::json uinfo = api::auth::refresh();
					DWORD userNumb;
					GetVolumeInformation(0, nullptr, 0, &userNumb, nullptr, nullptr, nullptr, 0);
					std::string hwid = std::to_string(userNumb);

					//Check #2?
					if (uinfo["sub_left"] == std::string("0"))
					{
						LOG(WARNING) << "No time left!";
						exit(0);
					}
					std::this_thread::sleep_for(1s);
				}
			});
		//} QUEUE_JOB_END_CLAUSE
	}
}