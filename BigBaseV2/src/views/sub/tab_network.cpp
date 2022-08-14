#include "views/view.hpp"
#include "services/player_service.hpp"
#include "util/session.hpp"

namespace big
{
	void view_sub::tab_network()
	{
		if (ImGui::BeginTabBar(xorstr_("##network_tabbar")))
		{
			if (ImGui::BeginTabItem(xorstr_("Session")))
			{
				for (const SessionType& session_type : sessions)
				{
					if (ImGui::MenuItem(session_type.name))
					{
						QUEUE_JOB_BEGIN_CLAUSE(&)
						{
							session::join_type(session_type);

						}QUEUE_JOB_END_CLAUSE
					}
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Players")))
			{
				if (*g_pointers->m_is_session_started)
				{
					ImGui::Text(fmt::format(xorstr_("Total players: {}"), g_player_service->players().size() + 1).c_str());

					ImGui::Separator();

					if (ImGui::BeginListBox(xorstr_("##player_list"), { 620.f - ImGui::GetStyle().WindowPadding.x * 2 , 320 }))
					{
						for (const auto& [_, player] : g_player_service->players())
						{
							ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0, 0.5 });

							ImGui::PushID(player->id());

							ImGui::Text(player->get_name());

							ImGui::PopID();

							ImGui::PopStyleVar();
						}

						ImGui::EndListBox();
					}
				}
				else
					ImGui::Text(xorstr_("GTA Online is required in order to view the player list"));

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(xorstr_("Friends")))
			{
				if (*g_pointers->m_is_session_started)
				{
					if (ImGui::BeginListBox(xorstr_("##friends_list"), { 620.f - ImGui::GetStyle().WindowPadding.x * 2 , 348 }))
					{
						for (const auto& [_, player] : g_player_service->players())
						{
							ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0, 0.5 });

							ImGui::PushID(player->id());

							if (player->is_friend())
							{
								if (ImGui::MenuItem(player->get_name()))
								{
									ImGui::OpenPopup(xorstr_("Player selection menu"));
									g_player_service->set_selected(player);
								}

								if (g_player_service->get_selected()->is_host())
								{
									ImGui::SameLine();
									ImGui::Text("SESSION HOST");
								}

								view_main::selected_player();
							}

							ImGui::PopID();

							ImGui::PopStyleVar();
						}

						ImGui::EndListBox();
					}
				}
				else
					ImGui::Text(xorstr_("GTA Online is required in order to view the friends list"));

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}