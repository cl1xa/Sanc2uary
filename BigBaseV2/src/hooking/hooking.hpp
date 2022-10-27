#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/data/fwddec.hpp"
#include "gta/data/net_game_event.hpp"
#include "gta/data/script_thread.hpp"
#include "scripts/script_hook.hpp"
#include "vmt_hook.hpp"
#include "gta/data/enums.hpp"

namespace big
{
	struct hooks
	{
		static bool run_script_threads(uint32_t ops_to_execute);

		static constexpr auto swapchain_num_funcs = 19;
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;

		static HRESULT swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static GtaThread* gta_thread_start(unsigned int** a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);

		static void* assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index);

		static void network_player_mgr_init(CNetworkPlayerMgr* _this, uint64_t a2, uint32_t a3, uint32_t a4[4]);
		static void network_player_mgr_shutdown(CNetworkPlayerMgr* _this);
		
		//Not yet implemented
		//static bool send_net_info_to_lobby(rage::rlGamerInfo* player, int64_t a2, int64_t a3, DWORD* a4);

		static void network_group_override(int64_t a1, int64_t a2, int64_t a3);

		static bool is_dlc_present(Hash dlc_hash);

		static void received_event(
			rage::netEventMgr* event_manager,
			CNetGamePlayer* source_player,
			CNetGamePlayer* target_player,
			uint16_t event_id,
			int event_index,
			int event_handled_bitset,
			int buffersize,
			rage::datBitBuffer* bit_buffer
		);

		//These two aren't actually hooks, just helper functions for hooks
		static bool scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player);
		static bool increment_stat_event(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender);

		static bool receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
		static void get_network_event_data(int64_t unk, rage::CEventNetwork* net_event);
		
		static int censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text);

		//static int64_t received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eObjType sync_type, uint16_t obj_id, rage::datBitBuffer* bufer, uint16_t unk, uint32_t timestamp);
	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();

	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;

		WNDPROC m_og_wndproc = nullptr;

		detour_hook m_run_script_threads_hook;

		detour_hook m_gta_thread_start_hook;
		detour_hook m_gta_thread_kill_hook;

		detour_hook m_assign_physical_index_hook;

		detour_hook m_network_player_mgr_init_hook;
		detour_hook m_network_player_mgr_shutdown_hook;

		detour_hook m_network_group_override_hook;

		detour_hook m_is_dlc_present_hook;

		detour_hook m_received_event_hook;
		//detour_hook m_received_clone_sync_hook;

		detour_hook m_receive_net_message_hook;
		detour_hook m_get_network_event_data_hook;

		detour_hook m_censor_chat_text_hook;
	};

	inline hooking* g_hooking{};
}