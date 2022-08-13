#include "views/view.hpp"

namespace big
{
	void view_sub::tab_misc()
	{
		ImGui::Checkbox(xorstr_("Optimize session loading"), &g_config.protection.other.optimize_loading);

		ImGui::Checkbox(xorstr_("Terminate loading screens"), &g_config.protection.other.terminate_loading_screens);

		ImGui::Checkbox(xorstr_("Modder detection"), &g_config.protection.other.modder_detection);

		ImGui::Checkbox(xorstr_("Uncensor chat"), &g_config.protection.other.uncensor_chat);
	}
}