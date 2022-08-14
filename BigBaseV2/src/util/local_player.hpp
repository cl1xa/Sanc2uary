#pragma once
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big::local_player
{
	int character_slot = 1;

	inline void get_active_character_slot(int* character_slot)
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), character_slot, true);
	}

	inline std::string get_mp_prefix()
	{
		/*get_active_character_slot(&character_slot);
		return "MP" + std::to_string(character_slot) + "_";*/

		return "MP0_";
	}
}