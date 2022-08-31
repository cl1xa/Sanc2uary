#pragma once
#include "misc/gta_util.hpp"
#include "services/player_service.hpp"

namespace big::toxic
{
	inline void desync_target()
	{
		gta_util::get_network_player_mgr()->RemovePlayer(g_player_service->get_selected()->get_net_game_player());
	}
}