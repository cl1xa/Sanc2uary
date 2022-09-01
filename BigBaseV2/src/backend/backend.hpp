#pragma once
#include "common.hpp"
#include "globals.hpp"

#include "scripts/script_global.hpp"
#include "scripts/script_mgr.hpp"
#include "scripts/fiber_pool.hpp"

#include "util/vehicle.hpp"

namespace big
{
	class backend_engine
	{
	public:
		static void update_globals();
		static void update_pointers();
		static void hud_transition_state();
		static void no_idle_kick();

		static void engine_calls();
		static void engine_loop();
	};

	class  backend_playercheats
	{
	public:
		static void player_god();
		static void infinite_ammo();
		static void no_police();

		static void keep_player_clean();
		static void no_ragdoll();

		static void player_calls();
		static void player_loop();
	};

	class  backend_vehiclecheats
	{
	public:
		static void vehicle_god();
		static void automatic_repair();
		static void horn_boost();

		static void vehicle_calls();
		static void vehicle_loop();
	};

	class backend_utility
	{
	public:
		static void keep_player_clean();
		static void no_ragdoll();

		static void utility_calls();
		static void utility_loop();
	};
}
