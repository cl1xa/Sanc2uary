#include "backend/backend.hpp"

namespace big
{
	void backend_playercheats::player_god() { ENTITY::SET_ENTITY_INVINCIBLE(globals::local_ped, g_config.cheats.player.player_god); }
}