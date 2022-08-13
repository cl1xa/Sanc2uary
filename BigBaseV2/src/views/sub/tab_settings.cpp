#include "views/view.hpp"
#include "fiber_pool.hpp"

namespace big
{
	void view_sub::tab_settings()
	{
		ImGui::Checkbox(xorstr_("Notify players"), &g_config.settings.notify_players);
		ImGui::Checkbox(xorstr_("Notify debug"), &g_config.settings.notify_debug);
		ImGui::Checkbox(xorstr_("Notify scripts"), &g_config.settings.notify_scripts);
		ImGui::Checkbox(xorstr_("Script event logger"), &g_config.settings.script_event_logger);

		if (ImGui::Button("Force exit GTA Online"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				NETWORK::NETWORK_BAIL(16, 0, 0);

			} QUEUE_JOB_END_CLAUSE
		}

		if (ImGui::Button(xorstr_("Unload Sanctuary")))
			g_running = false;
	}
}