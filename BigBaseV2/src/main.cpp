#include "common.hpp"
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
					auto pointers_instance = std::make_unique<pointers>();
					LOG(G3LOG_DEBUG) << xorstr_("Pointers initialized");

					auto renderer_instance = std::make_unique<renderer>();
					LOG(G3LOG_DEBUG) << xorstr_("Renderer initialized");

					auto fiber_pool_instance = std::make_unique<fiber_pool>(11);
					LOG(G3LOG_DEBUG) << xorstr_("Fiber pool initialized");

					auto hooking_instance = std::make_unique<hooking>();
					LOG(G3LOG_DEBUG) << xorstr_("Hooking initialized");

					g_config.load(xorstr_("default.sanctuary"));
					LOG(G3LOG_DEBUG) << xorstr_("Settings Loaded");

					auto thread_pool_instance = std::make_unique<thread_pool>();
					LOG(G3LOG_DEBUG) << xorstr_("Thread pool initialized");

					auto notification_service_instance = std::make_unique<notification_service>();
					auto player_service_instance = std::make_unique<player_service>();
					LOG(G3LOG_DEBUG) << xorstr_("Registered service instances");

					g_script_mgr.add_script(std::make_unique<script>(&menu::script_func, "GUI", false));
					LOG(G3LOG_DEBUG) << xorstr_("Menu registered");

					g_script_mgr.add_script(std::make_unique<script>(&features_engine::engine_loop, xorstr_("ENGINE", false)));
					g_script_mgr.add_script(std::make_unique<script>(&features_player::player_loop, xorstr_("PLAYER", false)));
					g_script_mgr.add_script(std::make_unique<script>(&features_vehicle::vehicle_loop, xorstr_("VEHICLE", false)));
					LOG(G3LOG_DEBUG) << xorstr_("Scripts registered");

					auto native_hooks_instance = std::make_unique<native_hooks>();
					LOG(G3LOG_DEBUG) << xorstr_("Dynamic native hooker initialized");

					g_hooking->enable();
					LOG(G3LOG_DEBUG) << xorstr_("Hooking enabled");

					LOG(G3LOG_DEBUG) << xorstr_("Successfully injected");

					g_running = true;

					while (g_running)
					{
						//api::auth_loop();

						g_config.save(xorstr_("default.sanctuary"));

						std::this_thread::sleep_for(500ms);
					}

					g_hooking->disable();
					LOG(G3LOG_DEBUG) << xorstr_("Hooking disabled");

					native_hooks_instance.reset();
					LOG(G3LOG_DEBUG) << xorstr_("Dynamic native hooker uninitialized");

					g_script_mgr.remove_all_scripts();
					LOG(G3LOG_DEBUG) << xorstr_("Scripts unregistered");

					// Make sure that all threads created don't have any blocking loops
					// otherwise make sure that they have stopped executing
					thread_pool_instance->destroy();
					LOG(G3LOG_DEBUG) << xorstr_("Destroyed thread pool");

					thread_pool_instance.reset();
					LOG(G3LOG_DEBUG) << xorstr_("Thread pool uninitialized");

					notification_service_instance.reset();
					player_service_instance.reset();
					LOG(G3LOG_DEBUG) << xorstr_("Services uninitialized");

					hooking_instance.reset();
					LOG(G3LOG_DEBUG) << xorstr_("Hooking uninitialized");

					fiber_pool_instance.reset();
					LOG(G3LOG_DEBUG) << xorstr_("Fiber pool uninitialized");

					renderer_instance.reset();
					LOG(G3LOG_DEBUG) << xorstr_("Renderer uninitialized");

					pointers_instance.reset();
					LOG(G3LOG_DEBUG) << xorstr_("Pointers uninitialized");
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
