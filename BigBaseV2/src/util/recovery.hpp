#pragma once
#include "util/local_player.hpp"
#include "gta/joaat.hpp"

namespace big::recovery
{
	namespace stat
	{
		void setInt(std::string stat, int val)
		{
			string mpPrefix = local_player::get_mp_prefix();
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + stat), val, true);
		}
	}

	namespace doomsday
	{
		using namespace stat;

		void setupDoomsday1()
		{
			setInt("GANGOPS_FLOW_MISSION_PROG", 503);
			setInt("GANGOPS_HEIST_STATUS", 229383);
			setInt("GANGOPS_FLOW_NOTIFICATIONS", 1557);
		}
		void setupDoomsday2()
		{
			setInt("GANGOPS_FLOW_MISSION_PROG", 503);
			setInt("GANGOPS_HEIST_STATUS", 229383);
			setInt("GANGOPS_FLOW_NOTIFICATIONS", 1557);
		}
		void setupDoomsday3()
		{
			setInt("GANGOPS_FLOW_MISSION_PROG", 503);
			setInt("GANGOPS_HEIST_STATUS", 229383);
			setInt("GANGOPS_FLOW_NOTIFICATIONS", 1557);
		}
	}

	namespace casino
	{
		using namespace stat;

		void setupCasino()
		{
			setInt("H3OPT_BITSET1", 0);
			setInt("H3OPT_BITSET0", 0);
			setInt("H3OPT_APPROACH", 1);
			setInt("H3OPT_TARGET", 3);
			setInt("H3OPT_POI", -1);
			setInt("H3OPT_ACCESSPOINTS", -1);
			setInt("H3OPT_BITSET1", -1);
			setInt("H3OPT_DISRUPTSHIP", 3);
			setInt("H3OPT_KEYLEVELS", 2);
			setInt("H3OPT_CREWWEAP", 5);
			setInt("H3OPT_CREWDRIVER", 5);
			setInt("H3OPT_CREWHACKER", 5);
			setInt("H3OPT_VEHS", 3);
			setInt("H3OPT_WEAPS", 1);
			setInt("H3OPT_BITSET0", -1);
		}

		void clearCasinoCooldown()
		{
			setInt("H3_COMPLETEDPOSIX", -1);
		}
	}
	
	namespace cayo
	{
		using namespace stat;

		void clearCayoCooldown()
		{
			setInt("H4_TARGET_POSIX", 1659429119);
			setInt("H4_COOLDOWN", 0);
			setInt("H4_COOLDOWN_HARD", 0);
		}

		void oneClickCayoSetup(int goodsValue)
		{
			setInt("H3OPT_BITSET1", 0);
			setInt("H3OPT_BITSET0", 0);
			setInt("H4CNF_BS_GEN", 131071);
			setInt("H4CNF_BS_ENTR", 63);
			setInt("H4CNF_BS_ABIL", 63);
			setInt("H4CNF_WEAPONS", 2);
			setInt("H4CNF_WEP_DISRP", 3);
			setInt("H4CNF_ARM_DISRP", 3);
			setInt("H4CNF_HEL_DISRP", 3);
			setInt("H4CNF_TARGET", 5);
			setInt("H4CNF_BOLTCUT", 4424);
			setInt("H4CNF_UNIFORM", 5256);
			setInt("H4CNF_GRAPPEL", 5156);
			setInt("H4CNF_TROJAN", 1);
			setInt("H4CNF_APPROACH", -1);
			setInt("H4LOOT_GOLD_V", goodsValue);
			setInt("H4LOOT_PAINT_V", goodsValue);
			setInt("H4LOOT_CASH_I", 0);
			setInt("H4LOOT_CASH_C", 0);
			setInt("H4LOOT_WEED_I", 0);
			setInt("H4LOOT_WEED_C", 0);
			setInt("H4LOOT_COKE_I", 0);
			setInt("H4LOOT_COKE_C", 0);
			setInt("H4LOOT_GOLD_I", -1);
			setInt("H4LOOT_GOLD_C", -1);
			setInt("H4LOOT_PAINT", -1);
			setInt("H4_PROGRESS", 126823);
			setInt("H4LOOT_CASH_I_SCOPED", 0);
			setInt("H4LOOT_CASH_C_SCOPED", 0);
			setInt("H4LOOT_WEED_I_SCOPED", 0);
			setInt("H4LOOT_WEED_C_SCOPED", 0);
			setInt("H4LOOT_COKE_I_SCOPED", 0);
			setInt("H4LOOT_COKE_C_SCOPED", 0);
			setInt("H4LOOT_GOLD_I_SCOPED", -1);
			setInt("H4LOOT_GOLD_C_SCOPED", -1);
			setInt("H4LOOT_PAINT_SCOPED", -1);
			setInt("H4_MISSIONS", 65535);
			setInt("H4_PLAYTHROUGH_STATUS", 4000);
		}
	}
}