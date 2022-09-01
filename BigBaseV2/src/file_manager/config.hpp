#pragma once

namespace big
{
	class config
	{
	public:
		static bool save(std::string file);
		static bool load(std::string file);

		struct
		{
			struct
			{
				bool script = false;
				bool game = false;

				bool action = false;

			}events;

			struct
			{
				bool script_world_state = false;
				bool task_vehicle_temp_action = false;

			}crash;

			struct 
			{
				bool check_nodes = false;
				bool check_mismatch = false;
				bool check_bounds = false;
				bool validate_models = false;

			}sync;

			struct
			{
				bool idle = false;
				bool vote = false; 
				bool rate_limit = false;
				bool stat_increment = false;
				bool host_desync = false;

			}other;

		}protection;

		struct
		{
			bool modder_detection = false;
			bool optimize_loading = false;
			bool terminate_loading_screens = false;
			bool uncensor_chat = false;

		}misc;

		struct
		{
			struct
			{
				bool player_god = false;
				bool keep_player_clean = false;
				bool no_police = false;
				bool infinite_ammo = false;

			}player;

			struct
			{
				bool vehicle_god = false;
				bool automatic_repair = false;
				bool horn_boost = false;

			}vehicle;

		}cheats;

		struct
		{
			bool notify_players = false;
			bool notify_debug = false;
			bool notify_scripts = false;
			bool script_event_logger = false;

		}settings;
	};

	inline config g_config;
}