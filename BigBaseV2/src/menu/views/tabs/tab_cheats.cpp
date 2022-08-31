#include "menu/views/view.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view_sub::tab_cheats()
	{
		if (ImGui::BeginTabBar(xorstr_("##cheats_tabbar")))
		{
			if (ImGui::BeginTabItem(xorstr_("Player")))
			{
				ImGui::Checkbox(xorstr_("Player godmode"), &g_config.cheats.player.player_god);
				ImGui::Checkbox(xorstr_("Keep player clean"), &g_config.cheats.player.keep_player_clean);
				ImGui::Checkbox(xorstr_("No police"), &g_config.cheats.player.no_police);
				ImGui::Checkbox(xorstr_("Infinite ammo"), &g_config.cheats.player.infinite_ammo);

				queue_button(xorstr_("Teleport to waypoint"), []
					{
						teleport::to_waypoint();
					});

				queue_button(xorstr_("Teleport to objective"), []
					{
						teleport::to_objective();
					});

				queue_button(xorstr_("Clear weather"), []
					{
						MISC::SET_OVERRIDE_WEATHER(xorstr_("EXTRASUNNY"));

						g_notification_service->push(xorstr_("Player cheats"), xorstr_("Cleared local weather"));
					});

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Vehicle")))
			{
				ImGui::Checkbox(xorstr_("Vehicle godmode"), &g_config.cheats.vehicle.vehicle_god);
				ImGui::Checkbox(xorstr_("Automatic repair"), &g_config.cheats.vehicle.automatic_repair);
				ImGui::Checkbox(xorstr_("Horn boost"), &g_config.cheats.vehicle.horn_boost);

				queue_button(xorstr_("MM Fix all"), []
					{
						int amount_fixed = vehicle::fix_all();
					});

				// This is broken and ghetto. Replace this with the personal vehicle list.
				queue_button(xorstr_("Bring personal vehicle"), []
					{
						const Vehicle vehicle = vehicle::get_personal_vehicle();

						int amount_fixed = vehicle::fix_all();

						vehicle::bring(vehicle, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false));

						vehicle::go_into_personal_vehicle();
					});

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}