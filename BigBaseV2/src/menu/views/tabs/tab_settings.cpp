#include "menu/views/view.hpp"

namespace big
{
	void view_sub::tab_settings()
	{
		ImGui::Checkbox(xorstr_("Notify players"), &g_config.settings.notify_players);

		ImGui::Checkbox(xorstr_("Notify debug"), &g_config.settings.notify_debug);

		ImGui::Checkbox(xorstr_("Notify scripts"), &g_config.settings.notify_scripts);

		ImGui::Checkbox(xorstr_("Script event logger"), &g_config.settings.script_event_logger);

		queue_button(xorstr_("Force exit GTA Online"), []
			{
				NETWORK::NETWORK_BAIL(16, 0, 0);

				g_notification_service->push(xorstr_("Session info"), xorstr_("Forced network termination"));
			});

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.0f, 0.0f, 1.f));

		//Does not need to be queued
		if (ImGui::Button(xorstr_("UNLOAD SANCTUARY")))
			g_running = false;

		ImGui::PopStyleColor();
	}
}