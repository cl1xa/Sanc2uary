#include "menu/views/view.hpp"
#include "util/recovery.hpp"

namespace big
{
    void view_sub::tab_recovery()
    {
        ImGui::Text(xorstr_("Cayo Perico Heist"));

        queue_button(xorstr_("Cayo one"), []
            {
                recovery::cayo::oneClickCayoSetup(424340);

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup one triggered"));
            });

        ImGui::SameLine();


        queue_button(xorstr_("Cayo two"), []
            {
                recovery::cayo::oneClickCayoSetup(930000);

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup two triggered"));
            });

        ImGui::SameLine();


        queue_button(xorstr_("Cayo three"), []
            {
                recovery::cayo::oneClickCayoSetup(1030000);

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup three triggered"));
            });

        ImGui::SameLine();

        queue_button(xorstr_("Cayo four"), []
            {
                recovery::cayo::oneClickCayoSetup(1185000);

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup four triggered"));
            });

        queue_button(xorstr_("Clear cayo cooldown"), []
            {
                recovery::cayo::clearCayoCooldown();

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo heist cooldown cleared"));
            });

        ImGui::Separator();

        ImGui::Text(xorstr_("Diamond Casino Heist"));

        queue_button(xorstr_("Instant casino setup"), []
            {
                recovery::casino::setupCasino();

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Instantly set up casino heist"));
            });

        queue_button(xorstr_("Clear casino cooldown"), []
            {
                recovery::casino::clearCasinoCooldown();

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Cleared casino heist cooldown"));
            });

        ImGui::Separator();

        ImGui::Text(xorstr_("Doomsday 1"));

        queue_button(xorstr_("Clear casino cooldown"), []
            {
                recovery::doomsday::setupDoomsday1();

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday one triggered"));
            });

        ImGui::SameLine();

        queue_button(xorstr_("Doomsday 2"), []
            {
                recovery::doomsday::setupDoomsday2();

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday two triggered"));
            });

        ImGui::SameLine();


        queue_button(xorstr_("Doomsday 3"), []
            {
                recovery::doomsday::setupDoomsday3();

                g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday three triggered"));
            });
    }
}