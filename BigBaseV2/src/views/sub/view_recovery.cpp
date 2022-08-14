#include "views/view.hpp"
#include "util/recovery.hpp"
#include "fiber_pool.hpp"

namespace big
{
    void view_sub::tab_recovery()
    {
        ImGui::Text("Cayo Perico Heist");

        if (ImGui::Button("Cayo one"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(424340);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup one triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button("Cayo two"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(930000);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup two triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button("Cayo three"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(1030000);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup three triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button("Cayo four"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::oneClickCayoSetup(1185000);

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo setup four triggered"));
        }

        if (ImGui::Button("Clear cayo cooldown"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::cayo::clearCayoCooldown();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cayo heist cooldown cleared"));
        }

        ImGui::Separator();

        ImGui::Text("Diamond Casino Heist");

        if (ImGui::Button("Instant casino setup"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::casino::setupCasino();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Instantly set up casino heist"));
        }

        if (ImGui::Button("Clear casino cooldown"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::casino::clearCasinoCooldown();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Cleared casino heist cooldown"));
        }

        ImGui::Separator();

        ImGui::Text("Doomsday Heist");

        if (ImGui::Button("Doomsday 1"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::doomsday::setupDoomsday1();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday one triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button("Doomsday 2"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::doomsday::setupDoomsday2();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday two triggered"));
        }

        ImGui::SameLine();

        if (ImGui::Button("Doomsday 3"))
        {
            QUEUE_JOB_BEGIN_CLAUSE()
            {
                recovery::doomsday::setupDoomsday3();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday three triggered"));
        }

        /*if (ImGui::Button("Instant 750k"))
        {
            QUEUE_JOB_BEGIN_CLAUSE(= )
            {
                script_global(262145).at(23114).as<int>() = 750000;
                script_global(1963962).as<int>() = 2;

                script::get_current()->yield();

            }QUEUE_JOB_END_CLAUSE

            g_notification_service->push(xorstr_("Recovery"), xorstr_("Doomsday three triggered"));
        }*/
    }
}