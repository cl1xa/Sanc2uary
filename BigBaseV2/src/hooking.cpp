#include "common.hpp"
#include "function_types.hpp"
#include "misc/logger.hpp"
#include "gta/array.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "memory/module.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "scripts/script_mgr.hpp"

#include <MinHook.h>

namespace big
{
	hooking::hooking() :
		m_swapchain_hook(*g_pointers->m_swapchain, hooks::swapchain_num_funcs),

		m_run_script_threads_hook("Script Hook", g_pointers->m_run_script_threads, &hooks::run_script_threads),

		m_gta_thread_start_hook("GTA Thead Start", g_pointers->m_gta_thread_start, &hooks::gta_thread_start),
		m_gta_thread_kill_hook("GTA Thread Kill", g_pointers->m_gta_thread_kill, &hooks::gta_thread_kill),

		m_is_dlc_present_hook("Is DLC Present", g_pointers->m_is_dlc_present, &hooks::is_dlc_present),

		m_assign_physical_index_hook("Assign Physical Index", g_pointers->m_assign_physical_index, &hooks::assign_physical_index),

		m_network_player_mgr_init_hook("Network Player Mgr Init", g_pointers->m_network_player_mgr_init, &hooks::network_player_mgr_init),
		m_network_player_mgr_shutdown_hook("Network Player Mgr Shutdown", g_pointers->m_network_player_mgr_shutdown, &hooks::network_player_mgr_shutdown),

		m_network_group_override_hook("Network Group Override", g_pointers->m_network_group_override, &hooks::network_group_override),

		m_received_event_hook("Received Event", g_pointers->m_received_event, &hooks::received_event),

		m_receive_net_message_hook("Receive Net Message", g_pointers->m_receive_net_message, &hooks::receive_net_message),
		m_get_network_event_data_hook("Get Network Event Data", g_pointers->m_get_network_event_data, &hooks::get_network_event_data),

		m_received_clone_sync_hook("Received Clone Sync", g_pointers->m_received_clone_sync, &hooks::received_clone_sync),

		m_censor_chat_text_hook("Censor Chat Text", g_pointers->m_censor_chat_text, &hooks::censor_chat_text)
	{
		m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
		m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_hook.enable();
		m_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hooks::wndproc)));

		m_run_script_threads_hook.enable();

		m_gta_thread_start_hook.enable();
		m_gta_thread_kill_hook.enable();

		m_is_dlc_present_hook.enable();
		
		m_assign_physical_index_hook.enable();

		m_network_player_mgr_init_hook.enable();
		m_network_player_mgr_shutdown_hook.enable();

		m_network_group_override_hook.enable();

		m_received_event_hook.enable();

		m_receive_net_message_hook.enable();
		m_get_network_event_data_hook.enable();

		//m_received_clone_sync_hook.enable();

		m_censor_chat_text_hook.enable();

		MH_ApplyQueued();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		m_censor_chat_text_hook.disable();

		//m_received_clone_sync_hook.disable();

		m_get_network_event_data_hook.disable();
		m_receive_net_message_hook.disable();

		m_received_event_hook.disable();

		m_network_group_override_hook.disable();

		m_network_player_mgr_shutdown_hook.disable();
		m_network_player_mgr_init_hook.disable();

		m_is_dlc_present_hook.disable();

		m_assign_physical_index_hook.disable();

		m_gta_thread_kill_hook.disable();
		m_gta_thread_start_hook.disable();

		m_run_script_threads_hook.disable();

		MH_ApplyQueued();

		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_hook.disable();
	}

	minhook_keepalive::minhook_keepalive()
	{
		MH_Initialize();
	}

	minhook_keepalive::~minhook_keepalive()
	{
		MH_Uninitialize();
	}

	bool hooks::run_script_threads(uint32_t ops_to_execute)
	{
		TRY_CLAUSE
		{
			if (g_running)
				g_script_mgr.tick();

		return g_hooking->m_run_script_threads_hook.get_original<functions::run_script_threads>()(ops_to_execute);

		} EXCEPT_CLAUSE

		return false;
	}

	HRESULT hooks::swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
				g_renderer->on_present();

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);

		} EXCEPT_CLAUSE

		return NULL;
	}

	HRESULT hooks::swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->pre_reset();

				auto result = g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
					(this_, buffer_count, width, height, new_format, swapchain_flags);

				if (SUCCEEDED(result))
					g_renderer->post_reset();

				return result;
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
				(this_, buffer_count, width, height, new_format, swapchain_flags);

		} EXCEPT_CLAUSE

		return NULL;
	}

	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		TRY_CLAUSE
		{
			if (g_running)
				g_renderer->wndproc(hwnd, msg, wparam, lparam);

			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);

		} EXCEPT_CLAUSE

		return NULL;
	}
}
