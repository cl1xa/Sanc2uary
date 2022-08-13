#include "hooking.hpp"
#include "gta_util.hpp"
#include "gta/enums.hpp"

namespace big
{
	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		const auto args = scripted_game_event->m_args;

		const auto hash = static_cast<eRemoteEvent>(args[0]);

		const auto player_name = player->get_name();

		switch (hash)
		{
		case eRemoteEvent::IDK1:
		case eRemoteEvent::IDK2:
		case eRemoteEvent::IDK3:
		case eRemoteEvent::IDK4:
		case eRemoteEvent::IDK5:
		case eRemoteEvent::IDK6:
		case eRemoteEvent::IDK7:
		case eRemoteEvent::IDK8:
		case eRemoteEvent::IDK9:
		case eRemoteEvent::IDK10:
		case eRemoteEvent::IDK11:
		case eRemoteEvent::IDK12:
		case eRemoteEvent::IDK13:
		case eRemoteEvent::IDK14:
		case eRemoteEvent::IDK15:
		case eRemoteEvent::IDK16:
		case eRemoteEvent::IDK17:
		case eRemoteEvent::IDK18:
		case eRemoteEvent::IDK19:
		case eRemoteEvent::IDK20:
		case eRemoteEvent::IDK21:
		case eRemoteEvent::IDK22:
		case eRemoteEvent::IDK23:
			//These send lots of false positives. They spam and I only want them logged to the console
			//I will figure out something better later
			LOG(G3LOG_DEBUG) << fmt::format(xorstr_("{} potentially unwanted event: {}"), player_name, (int)hash);
			return true;

		case eRemoteEvent::RotateCam:
		{
			bool blocked = false;

			if (args[2] == 537560473)
				blocked = true;

			if (CNetworkPlayerMgr* player_mgr = gta_util::get_network_player_mgr(); player_mgr != nullptr)
				if (args[2] == player_mgr->m_local_net_player->m_player_id)
					blocked = true;

			if (blocked)
			{
				//These send lots of false positives. They spam and I only want them logged to the console
				//I will figure out something better later
				LOG(G3LOG_DEBUG) << fmt::format(xorstr_("{} sent camra event: {}"), player_name, (int)hash);
				return true;
			}

			break; //Someone tell me if this is wrong. Better safe than sorry?
		}

		case eRemoteEvent::SendToLocation:
		{
			bool known_location = false;

			if (args[2] == 0 && args[3] == 0)
			{
				if (args[4] == 4 && args[5] == 0)
				{
					known_location = true;

					return true;
				}
				else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
				{
					known_location = true;

					return true;
				}
			}

			if (!known_location)
			{
				g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent telport event: {}"), player_name, (int)hash));
				return true;
			}

			break; //Someone tell me if this is wrong. Better safe than sorry?
		}

		case eRemoteEvent::Bounty:
		case eRemoteEvent::CeoBan:
		case eRemoteEvent::CeoKick:
		case eRemoteEvent::CeoMoney:
		case eRemoteEvent::ClearWantedLevel:
		case eRemoteEvent::FakeDeposit:
		case eRemoteEvent::ForceMission:
		case eRemoteEvent::GtaBanner:
		case eRemoteEvent::MCTeleport:
		case eRemoteEvent::PersonalVehicleDestroyed:
		case eRemoteEvent::RemoteOffradar:
		case eRemoteEvent::SendToCayoPerico:
		case eRemoteEvent::SendToCutscene:
		case eRemoteEvent::SoundSpam:
		case eRemoteEvent::Spectate:
		case eRemoteEvent::Teleport:
		case eRemoteEvent::TransactionError:
		case eRemoteEvent::VehicleKick:
		case eRemoteEvent::ForceMission2:
			g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent script event: {}"), player_name, (int)hash));
			return true;
			
		case eRemoteEvent::SHKick:
		case eRemoteEvent::NetworkBail:
		case eRemoteEvent::Crash:
		case eRemoteEvent::Crash2:
			g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent script crash: {}"), player_name, (int)hash));
			return true;

		default:
			break;
		}

		return false;
	}
}