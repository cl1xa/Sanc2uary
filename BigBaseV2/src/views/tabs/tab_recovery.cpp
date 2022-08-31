#include "views/view.hpp"
#include "util/recovery.hpp"

namespace big
{
    void view_sub::tab_recovery()
    {
        ImGui::Text(xorstr_("Cayo Perico Heist"));

        if (ImGui::Button(xorstr_("Cayo one")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(424340);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup one triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button(xorstr_("Cayo two")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(930000);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup two triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button(xorstr_("Cayo three")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(1030000);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup three triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button(xorstr_("Cayo four")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(1185000);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup four triggered"));
        }

        if (ImGui::Button(xorstr_("Clear cayo cooldown")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::clearCayoCooldown();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo heist cooldown cleared"));
        }

        ImGui::Separator();

        ImGui::Text(xorstr_("Diamond Casino Heist"));

        if (ImGui::Button(xorstr_("Instant casino setup")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::casino::setupCasino();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Instantly set up casino heist"));
        }

        if (ImGui::Button(xorstr_("Clear casino cooldown")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::casino::clearCasinoCooldown();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cleared casino heist cooldown"));
        }

        ImGui::Separator();

        ImGui::Text(xorstr_("Doomsday Heist"));

        if (ImGui::Button(xorstr_("Doomsday 1")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::doomsday::setupDoomsday1();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday one triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button(xorstr_("Doomsday 2")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::doomsday::setupDoomsday2();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday two triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button(xorstr_("Doomsday 3")))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::doomsday::setupDoomsday3();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday three triggered"));
        }
    }
}