#include "hooking/hooking.hpp"

namespace big
{
	bool hooks::increment_stat_event(CNetworkIncrementStatEvent* net_event, CNetGamePlayer* sender)
	{
		switch (net_event->m_stat)
		{
		/*case RAGE_JOAAT("MPPLY_BAD_CREW_STATUS"):
		case RAGE_JOAAT("MPPLY_BAD_CREW_MOTTO"):
		case RAGE_JOAAT("MPPLY_BAD_CREW_NAME"):
		case RAGE_JOAAT("MPPLY_BAD_CREW_EMBLEM"):
		case RAGE_JOAAT("MPPLY_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_TC_HATE"):
		case RAGE_JOAAT("MPPLY_VC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_VC_HATE"):
		case RAGE_JOAAT("MPPLY_BECAME_CHEATER_NUM"):
		case RAGE_JOAAT("MPPLY_GRIEFING"):
		case RAGE_JOAAT("MPPLY_OFFENSIVE_LANGUAGE"):
		case RAGE_JOAAT("MPPLY_OFFENSIVE_TAGPLATE"):
		case RAGE_JOAAT("MPPLY_OFFENSIVE_UGC"):
		case RAGE_JOAAT("MPPLY_DM_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_DM_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_DM_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_RACE_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_RACE_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_RACE_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_MC_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_MC_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_MC_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_MGAME_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_MGAME_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_MGAME_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_VOTED_OUT"):
		case RAGE_JOAAT("MPPLY_VOTED_OUT_DELTA"):
		case RAGE_JOAAT("MPPLY_VOTED_OUT_QUIT"):
		case RAGE_JOAAT("MPPLY_CAP_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_CAP_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_CAP_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_SUR_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_SUR_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_SUR_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_LTS_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_LTS_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_LTS_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_PARA_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_PARA_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_PARA_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_FMEVN_CHEAT_START"):
		case RAGE_JOAAT("MPPLY_FMEVN_CHEAT_END"):
		case RAGE_JOAAT("MPPLY_FMEVN_CHEAT_QUIT"):
		case RAGE_JOAAT("MPPLY_ISPUNISHED"):
		case RAGE_JOAAT("MPPLY_OVERALL_CHEAT"):
		case RAGE_JOAAT("MPPLY_OVERALL_BADSPORT"):
			return true;*/

		default:
			break;
		}

		return false;
	}
}