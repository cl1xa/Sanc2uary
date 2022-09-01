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

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}