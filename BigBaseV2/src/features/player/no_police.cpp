#include "features/features.hpp"

namespace big
{
	void features_player::no_police()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr)
			return;

		const auto playerInfo = g_local_player->m_player_info;

		if (!g_config.cheats.player.no_police)
			return;

		playerInfo->m_wanted_level = 0;
	}
}