#include "backend/backend.hpp"

namespace big
{
	int no_stars = 0;

	void backend_playercheats::no_police()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr)
			return;

		const auto playerInfo = g_local_player->m_player_info;

		if (!g_config.cheats.player.no_police)
			return;

		playerInfo->m_wanted_level = no_stars;
	}
}