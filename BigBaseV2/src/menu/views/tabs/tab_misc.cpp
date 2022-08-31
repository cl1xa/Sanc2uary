#include "menu/views/view.hpp"

namespace big
{
	void view_sub::tab_misc()
	{
		ImGui::Checkbox(xorstr_("Modder detection"), &g_config.misc.modder_detection);

		ImGui::Checkbox(xorstr_("Optimize session loading"), &g_config.misc.optimize_loading);

		ImGui::Checkbox(xorstr_("Terminate loading screens"), &g_config.misc.terminate_loading_screens);

		ImGui::Checkbox(xorstr_("Uncensor chat"), &g_config.misc.uncensor_chat);
	}
}