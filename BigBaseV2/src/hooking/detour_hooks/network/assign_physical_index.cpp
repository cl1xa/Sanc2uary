#include "hooking/hooking.hpp"
#include "services/player_service.hpp"
#include "util/notify.hpp"

namespace big
{
	//Session switching optimization #3
	void* hooks::assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index)
	{
		auto returnResult = g_hooking->m_assign_physical_index_hook.get_original<decltype(&hooks::assign_physical_index)>()(netPlayerMgr, player, new_index);

		if (new_index == 0xFF) //0XFF = Nearest empty memory region
		{
			g_player_service->player_leave(player);

			if (const rage::rlGamerInfo* net_player_data = player->get_net_data(); net_player_data)
			{
				if (g_config.settings.notify_players)
					g_notification_service->push(xorstr_("Player left"), fmt::format(xorstr_("[{}] {} left"), net_player_data->m_peer_id_2, net_player_data->m_name));
			}

			return returnResult;
		}

		g_player_service->player_join(player);

		if (const rage::rlGamerInfo* net_player_data = player->get_net_data(); net_player_data)
		{
			notify::above_map(fmt::format(xorstr_("<C>{}</C> joined."), net_player_data->m_name));

			if (g_config.settings.notify_players)
				g_notification_service->push(xorstr_("Player joined"), fmt::format(xorstr_("[{}/{}] {} joined"), (int)player->m_player_id, net_player_data->m_peer_id_2, net_player_data->m_name));
		}

		return returnResult;
	}
}