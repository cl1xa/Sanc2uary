#include "views/view.hpp"

namespace big
{
	void view_sub::tab_protection()
	{
		if (ImGui::BeginTabBar(xorstr_("##protex_tabbar")))
		{
			if (ImGui::BeginTabItem(xorstr_("Events")))
			{
				ImGui::Checkbox(xorstr_("Script event handler"), &g_config.protection.events.script);
				ImGui::Checkbox(xorstr_("Game event handler"), &g_config.protection.events.game);

				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.0f, 0.2f, 1.f));

				ImGui::Checkbox(xorstr_("Block action events"), &g_config.protection.events.action);

				ImGui::PopStyleColor();

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Patches")))
			{
				ImGui::Checkbox(xorstr_("SCRIPT_WORLD_STATE patch"), &g_config.protection.crash.script_world_state);
				ImGui::Checkbox(xorstr_("TASK_VEHICLE_TEMP_ACTION patch"), &g_config.protection.crash.task_vehicle_temp_action);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Sync")))
			{
				ImGui::Text(xorstr_("Object sync:"));
				ImGui::Checkbox(xorstr_("Clone"), &g_config.protection.sync.clone_sync);

				ImGui::Text(xorstr_("Network sync:"));
				ImGui::Checkbox(xorstr_("Host desync prevention"), &g_config.protection.sync.host_desync);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Other")))
			{
				ImGui::Checkbox(xorstr_("Idle kick prevention"), &g_config.protection.other.idle);

				ImGui::Checkbox(xorstr_("Vote kick prevention"), &g_config.protection.other.vote);

				ImGui::Checkbox(xorstr_("Rate limit prevention"), &g_config.protection.other.rate_limit);

				ImGui::Checkbox(xorstr_("Block stat increments"), &g_config.protection.other.stat_increment);

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}