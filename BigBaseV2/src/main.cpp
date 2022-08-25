#include "common.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "thread_pool.hpp"

#include "api/api.hpp"
#include "native_hooks/native_hooks.hpp"

#include "services/player_service.hpp"
#include "services/notification_service.hpp"

#include "backend/backend.hpp"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;



	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;

		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
			{
				BOOL API_CALLS = true;
				while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
					std::this_thread::sleep_for(1s);

				std::filesystem::path base_dir = std::getenv(xorstr_("appdata"));
				base_dir /= xorstr_("Sanctuary");

				auto file_manager_instance = std::make_unique<file_manager>(base_dir);

				auto logger_instance = std::make_unique<logger>(
					xorstr_("Sanctuary"),
					file_manager_instance->get_project_file(xorstr_("./sanctuary.log"))
					);

				try
				{
					auto pointers_instance = std::make_unique<pointers>();

					auto renderer_instance = std::make_unique<renderer>();

					auto fiber_pool_instance = std::make_unique<fiber_pool>(10);

					auto hooking_instance = std::make_unique<hooking>();

					g_config.load("default.sanctuary");

					auto thread_pool_instance = std::make_unique<thread_pool>();

					auto notification_service_instance = std::make_unique<notification_service>();
					auto player_service_instance = std::make_unique<player_service>();

					g_script_mgr.add_script(std::make_unique<script>(&backend_engine::engine_loop));
					g_script_mgr.add_script(std::make_unique<script>(&backend_player::player_loop));
					g_script_mgr.add_script(std::make_unique<script>(&backend_vehicle::vehicle_loop));

					g_script_mgr.add_script(std::make_unique<script>(&gui::script_func));

					auto native_hooks_instance = std::make_unique<native_hooks>();

					g_hooking->enable();

					g_running = true;
					if (API_CALLS)
					{
						g_thread_pool->push([]
							{
								bool has_logged = false;
								while (g_running)
								{
									if (!has_logged)
									{
										LOG(INFO) << "Checking for JWT";
										std::filesystem::path cheatpath = std::getenv("appdata");
										cheatpath /= "GamingHard/jwt.txt";
										std::string line;
										std::string jwt;
										std::ifstream jwtFile(cheatpath);
										if (jwtFile.good()) {
											while (std::getline(jwtFile, line))
											{
												jwt = line;

											}
										}
										else {
											LOG(INFO) << "JWT file bad";
											jwtFile.close();
											remove(cheatpath);
											exit(0);
										}
										jwtFile.close();
										remove(cheatpath);
										LOG(INFO) << "Getting UINFO";
										nlohmann::json uinfo = api::auth::sign_in(jwt);

										LOG(INFO) << "Getting HWID";
										DWORD userNumb;
										GetVolumeInformation(0, nullptr, 0, &userNumb, nullptr, nullptr, nullptr, 0);
										std::string hwid = std::to_string(userNumb);
										LOG(INFO) << "Checking user validity";
										if (uinfo["sub_left"] == std::string("0"))
										{
											exit(0);
										}
										has_logged = true;
										LOG(INFO) << "user authentication complete";
									}
									nlohmann::json uinfo = api::auth::refresh();
									nlohmann::json uinfo = api::auth::refresh();
									DWORD userNumb;
									GetVolumeInformation(0, nullptr, 0, &userNumb, nullptr, nullptr, nullptr, 0);
									std::string hwid = std::to_string(userNumb);
									if (uinfo["sub_left"] == std::string("0"))
									{
										exit(0);
									}
									std::this_thread::sleep_for(1s);
								}
							});
					}
					while (g_running)
					{
						g_config.save(xorstr_("default.sanctuary"));

						std::this_thread::sleep_for(500ms);
					}

					g_hooking->disable();

					native_hooks_instance.reset();

					g_script_mgr.remove_all_scripts();

					player_service_instance.reset();

					notification_service_instance.reset();

					// Make sure that all threads created don't have any blocking loops
					// otherwise make sure that they have stopped executing
					thread_pool_instance->destroy();

					thread_pool_instance.reset();

					hooking_instance.reset();

					fiber_pool_instance.reset();

					renderer_instance.reset();

					pointers_instance.reset();

				}
				catch (std::exception const& ex)
				{
					LOG(WARNING) << ex.what();
				}

				logger_instance->destroy();
				logger_instance.reset();
				file_manager_instance.reset();

				CloseHandle(g_main_thread);
				FreeLibraryAndExitThread(g_hmodule, 0);

			}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}
