#include "menu/views/view.hpp"
#include "services/player_service.hpp"

namespace big
{
	void view_main::selected_player()
	{
		ImGui::SetNextWindowSize({ 520, 325 }, ImGuiCond_FirstUseEver);

		if (ImGui::BeginPopupModal(xorstr_("Player selection menu")))
		{
			ImGui::Text(fmt::format(xorstr_("{}[{}] {}"), (g_player_service->get_selected()->is_host() ? xorstr_("[H]") : xorstr_("")), g_player_service->get_selected()->id(), g_player_service->get_selected()->get_name()).c_str());

			ImGui::Separator();

			if (rage::netPlayerData* net_player_data = g_player_service->get_selected()->get_net_data(); net_player_data != nullptr)
			{
				ImGui::Text(xorstr_("Rockstar ID: %d"), net_player_data->m_rockstar_id);

				ImGui::Text(
					xorstr_("IP Address: %d.%d.%d.%d:%d"),
					net_player_data->m_external_ip.m_field1,
					net_player_data->m_external_ip.m_field2,
					net_player_data->m_external_ip.m_field3,
					net_player_data->m_external_ip.m_field4,
					net_player_data->m_external_port
				);
			}

			ImGui::Separator();

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.0f, 0.0f, 1.f));

			if (ImGui::Button(xorstr_("EXIT")))
				ImGui::CloseCurrentPopup();

			ImGui::PopStyleColor();

			ImGui::EndPopup();
		}
	}
}