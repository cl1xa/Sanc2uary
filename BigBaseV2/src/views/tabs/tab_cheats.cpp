#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view_sub::tab_cheats()
	{
		ImGui::Text(xorstr_("Disabled for now"));

		/*if (ImGui::BeginTabBar(xorstr_("##cheats_tabbar")))
		{
			if (ImGui::BeginTabItem(xorstr_("Player")))
			{
				ImGui::Checkbox(xorstr_("Player godmode"), &g_config.cheats.player.player_god);
				ImGui::Checkbox(xorstr_("Keep player clean"), &g_config.cheats.player.keep_player_clean);
				ImGui::Checkbox(xorstr_("No police"), &g_config.cheats.player.no_police);
				ImGui::Checkbox(xorstr_("Infinite ammo"), &g_config.cheats.player.infinite_ammo);

				if (ImGui::Button(xorstr_("Teleport to waypoint")))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						teleport::to_waypoint();

					} QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button(xorstr_("Teleport to objective")))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						teleport::to_objective();

					} QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button(xorstr_("Clear weather")))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						MISC::SET_OVERRIDE_WEATHER(xorstr_("EXTRASUNNY"));
						                                                                                                                                                                                               
					}QUEUE_JOB_END_CLAUSE

					g_notification_service->push(xorstr_("Player cheats"), xorstr_("Cleared local weather"));                     
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Vehicle")))
			{
				ImGui::Checkbox(xorstr_("Vehicle godmode"), &g_config.cheats.vehicle.vehicle_god);
				ImGui::Checkbox(xorstr_("Automatic repair"), &g_config.cheats.vehicle.automatic_repair);
				ImGui::Checkbox(xorstr_("Horn boost"), &g_config.cheats.vehicle.horn_boost);

				if (ImGui::Button(xorstr_("MM Fix all")))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						int amount_fixed = vehicle::fix_all();

					} QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button(xorstr_("Enter personal vehicle")))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						const Vehicle vehicle = vehicle::get_personal_vehicle();

						int amount_fixed = vehicle::fix_all();

						vehicle::bring(vehicle, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false));

						vehicle::go_into_personal_vehicle();

					} QUEUE_JOB_END_CLAUSE
				}

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}*/
	}
}