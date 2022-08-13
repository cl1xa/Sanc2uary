#pragma once
#include "common.hpp"

namespace big
{
	class backend_engine
	{
	public:
		static void update_pointers();
		static void hud_transition_state();
		static void no_idle_kick();

		static void engine_calls();
		static void script_func();
	};

	class backend_player
	{
	public:
		static void player_god();
		static void infinite_ammo();
		static void no_police();

		static void player_calls();
		static void script_func();
	};

	class backend_vehicle
	{
	public:
		static void vehicle_god();
		static void automatic_repair();
		static void horn_boost();

		static void vehicle_calls();
		static void script_func();
	};
}
