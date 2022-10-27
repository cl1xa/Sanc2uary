#include "menu/views/view.hpp"
#include "services/player_service.hpp"
#include "util/toxic.hpp"

namespace big
{
	void view_main::selected_player()
	{
		ImGui::SetNextWindowSize({ 520, 325 }, ImGuiCond_FirstUseEver);

		if (ImGui::BeginPopupModal(xorstr_("Player selection menu")))
		{
			auto selected = g_player_service->get_selected();
			const char* name = selected->get_name();

			ImGui::Text(fmt::format(xorstr_("{}[{}] {}"), (selected->is_host() ? xorstr_("[H]") : xorstr_("")), selected->id(), name).c_str());

			ImGui::Separator();

			if (rage::rlGamerInfo* net_player_data = selected->get_net_data(); net_player_data != nullptr)
			{
				ImGui::Text(xorstr_("Rockstar ID: %d"), net_player_data->m_peer_id);

				ImGui::Text(
					xorstr_("IP Address: %d.%d.%d.%d:%d"),
					net_player_data->m_external_ip.m_field1,
					net_player_data->m_external_ip.m_field2,
					net_player_data->m_external_ip.m_field3,
					net_player_data->m_external_ip.m_field4,
					net_player_data->m_external_port
				);
			}

			queue_button(xorstr_("Dsync player"), []
			{
				toxic::desync_target();
			});

			ImGui::Separator();

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.0f, 0.0f, 1.f));

			//Does not need to be queued
			if (ImGui::Button(xorstr_("EXIT")))
				ImGui::CloseCurrentPopup();

			ImGui::PopStyleColor();

			ImGui::EndPopup();
		}
	}
}