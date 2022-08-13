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
		///*case eRemoteEvent::IDK1:
		//case eRemoteEvent::IDK2:
		//case eRemoteEvent::IDK3:
		//case eRemoteEvent::IDK4:
		//case eRemoteEvent::IDK5:
		//case eRemoteEvent::IDK6:
		//case eRemoteEvent::IDK7:
		//case eRemoteEvent::IDK8:
		//case eRemoteEvent::IDK9:
		//case eRemoteEvent::IDK10:
		//case eRemoteEvent::IDK11:
		//case eRemoteEvent::IDK12:
		//case eRemoteEvent::IDK13:
		//case eRemoteEvent::IDK14:
		//case eRemoteEvent::IDK15:
		//case eRemoteEvent::IDK16:
		//case eRemoteEvent::IDK17:
		//case eRemoteEvent::IDK18:
		//case eRemoteEvent::IDK19:
		//case eRemoteEvent::IDK20:
		//case eRemoteEvent::IDK21:
		//case eRemoteEvent::IDK22:
		//case eRemoteEvent::IDK23:
		//	return true;*/

		//case eRemoteEvent::Bounty:
		//case eRemoteEvent::CeoBan:
		//case eRemoteEvent::CeoKick:
		//case eRemoteEvent::CeoMoney:
		//case eRemoteEvent::ClearWantedLevel:
		//case eRemoteEvent::Crash:
		//case eRemoteEvent::Crash2:
		//case eRemoteEvent::FakeDeposit:
		//case eRemoteEvent::ForceMission:
		//case eRemoteEvent::GtaBanner:
		//case eRemoteEvent::MCTeleport:
		//case eRemoteEvent::NetworkBail:
		//case eRemoteEvent::PersonalVehicleDestroyed:
		//case eRemoteEvent::RemoteOffradar:
		//case eRemoteEvent::SendToCayoPerico:
		//case eRemoteEvent::SendToCutscene:
		//case eRemoteEvent::SoundSpam:
		//case eRemoteEvent::Spectate:
		//case eRemoteEvent::Teleport:
		//case eRemoteEvent::TransactionError:
		//case eRemoteEvent::VehicleKick:
		//case eRemoteEvent::ForceMission2:
		//case eRemoteEvent::SHKick:
		//	return true;

		//case eRemoteEvent::RotateCam:
		//	if (args[2] == 537560473)
		//		return true;

		//	if (CNetworkPlayerMgr* player_mgr = gta_util::get_network_player_mgr(); player_mgr != nullptr)
		//		if (args[2] == player_mgr->m_local_net_player->m_player_id)
		//			return true;

		//	break; //Someone tell me if this is wrong. Better safe than sorry?

		//case eRemoteEvent::SendToLocation:
		//{
		//	bool known_location = false;

		//	if (args[2] == 0 && args[3] == 0)
		//	{
		//		if (args[4] == 4 && args[5] == 0)
		//		{
		//			known_location = true;

		//			return true;
		//		}
		//		else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
		//		{
		//			known_location = true;

		//			return true;
		//		}
		//	}

		//	if (!known_location)
		//		return true;

		//	break; //Someone tell me if this is wrong. Better safe than sorry?
		//}

		default:
			break;
		}

		return false;
	}
}