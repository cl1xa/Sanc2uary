#include "hooking/hooking.hpp"
#include "services/player_service.hpp"

namespace big
{
	void hooks::network_player_mgr_init(CNetworkPlayerMgr* _this, uint64_t a2, uint32_t a3, uint32_t a4[4])
	{
		if (g_config.settings.notify_debug)
		{
			if (g_config.settings.notify_players)
				g_notification_service->push(xorstr_("Session found"), xorstr_("Entering new multiplayer session"), true);
		}

		g_hooking->m_network_player_mgr_init_hook.get_original<decltype(&hooks::network_player_mgr_init)>()(_this, a2, a3, a4);

		g_player_service->player_join(_this->m_local_net_player);
	}

	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		g_player_service->do_cleanup();

		if (g_config.settings.notify_debug)
		{
			if (g_config.settings.notify_players)
				g_notification_service->push(xorstr_("Session lost"), xorstr_("Connection to the session was terminated"), true);
		}

		g_hooking->m_network_player_mgr_shutdown_hook.get_original<decltype(&hooks::network_player_mgr_shutdown)>()(_this);
	}
}