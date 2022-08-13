#include "backend/backend.hpp"

namespace big
{
	void backend_player::no_police()
	{
		if (g_local_player == nullptr 
			|| g_local_player->m_player_info == nullptr 
			|| !g_config.cheats.player.no_police) 
			return;

		const auto playerInfo = g_local_player->m_player_info;

		playerInfo->m_wanted_level = 0;
	}
}