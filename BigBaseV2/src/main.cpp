﻿#include "common.hpp"
#include "scripts/fiber_pool.hpp"
#include "menu/menu.hpp"
#include "logger.hpp"
#include "hooking/hooking.hpp"
#include "hooking/pointers.hpp"
#include "menu/renderer.hpp"
#include "scripts/script_mgr.hpp"
#include "scripts/thread_pool.hpp"

#include "api/api.hpp"
#include "api/auth.hpp"
#include "hooking/native_hooks/native_hooks.hpp"

#include "services/player_service.hpp"
#include "services/notification_service.hpp"

#include "features/features.hpp"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;

	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;

		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
			{
				while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
					std::this_thread::sleep_for(1s);

				std::filesystem::path base_dir = getenv(xorstr_("appdata"));
				base_dir /= xorstr_("Sanctuary");

				auto file_manager_instance = make_unique<file_manager>(base_dir);

				auto logger_instance = make_unique<logger>(
					xorstr_("Sanctuary"),
					file_manager_instance->get_project_file(xorstr_("./sanctuary.log"))
					);

				try
				{
					auto pointers_instance = make_unique<pointers>();

					auto renderer_instance = make_unique<renderer>();

					auto fiber_pool_instance = make_unique<fiber_pool>(10);

					auto hooking_instance = make_unique<hooking>();

					g_config.load(xorstr_("default.sanctuary"));

					auto thread_pool_instance = make_unique<thread_pool>();

					auto notification_service_instance = make_unique<notification_service>();
					auto player_service_instance = make_unique<player_service>();

					g_script_mgr.add_script(make_unique<script>(&features_engine::engine_loop));
					//g_script_mgr.add_script(make_unique<script>(&backend_player::player_loop));
					//g_script_mgr.add_script(make_unique<script>(&backend_vehicle::vehicle_loop));

					g_script_mgr.add_script(make_unique<script>(&menu::script_func));

					auto native_hooks_instance = make_unique<native_hooks>();

					g_hooking->enable();

					g_running = true;

					while (g_running)
					{
						//api::auth_loop();

						g_config.save(xorstr_("default.sanctuary"));

						this_thread::sleep_for(500ms);
					}

					g_hooking->disable();

					native_hooks_instance.reset();

					g_script_mgr.remove_all_scripts();

					// Make sure that all threads created don't have any blocking loops
					// otherwise make sure that they have stopped executing
					thread_pool_instance->destroy();
					thread_pool_instance.reset();

					player_service_instance.reset();

					notification_service_instance.reset();

					hooking_instance.reset();

					fiber_pool_instance.reset();

					renderer_instance.reset();

					pointers_instance.reset();

				}
				catch (exception const& ex)
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
