#pragma once
#include "common.hpp"
#include "globals.hpp"

#include "scripts/script_global.hpp"
#include "scripts/script_mgr.hpp"
#include "scripts/fiber_pool.hpp"

#include "util/vehicle.hpp"
#include "util/entity.hpp"

namespace big
{
	class features_engine
	{
	public:
		static void update_globals();
		static void update_pointers();
		static void hud_transition_state();
		static void no_idle_kick();

		static void engine_calls();
		static void engine_loop();
	};

	class features_player
	{
	public:
		static void player_god();
		static void keep_player_clean();
		static void infinite_ammo();
		static void no_police();

		static void player_calls();
		static void player_loop();
	};

	class features_vehicle
	{
	public:
		static void vehicle_god();
		static void automatic_repair();
		static void horn_boost();

		static void vehicle_calls();
		static void vehicle_loop();
	};
}
