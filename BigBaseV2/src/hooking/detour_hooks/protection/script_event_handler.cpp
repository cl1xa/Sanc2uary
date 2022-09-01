#include "hooking/hooking.hpp"
#include "misc/gta_util.hpp"

namespace big
{
	static void format_string(CNetGamePlayer* player, string type, bool notify = true)
	{
		if (notify)
			g_notification_service->push_warning(xorstr_("Protection"), (string)player->get_name() + " sent unwanted event: " + type);
	}

	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		const auto args = scripted_game_event->m_args;
		const auto hash = static_cast<eRemoteEvent>(args[0]);

		switch (hash)
		{
		case eRemoteEvent::GiveCollectible:
			format_string(player, xorstr_("Give collectible"));
			break;

		case eRemoteEvent::ChangeMCRole:
			format_string(player, xorstr_("Change MC role"));
			break;

		case eRemoteEvent::DisableRecording:
			format_string(player, xorstr_("Disable recording"));
			break;

			//Do more testing with these events
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
			format_string(player, xorstr_("Script crash #7"), false); //Do not log. Very spammy. Annoying.
			return true;

		case eRemoteEvent::NetworkBail:
			format_string(player, xorstr_("Network bail #1"));
			return true;

		case eRemoteEvent::SHKick:
			format_string(player, xorstr_("Network bail #2"));
			return true;

		case eRemoteEvent::Crash:
			format_string(player, xorstr_("Script crash #1"));
			return true;

		case eRemoteEvent::Crash2:
			format_string(player, xorstr_("Script crash #2"));
			return true;

		case eRemoteEvent::Bounty:
			format_string(player, xorstr_("Bounty"));
			return true;

		case eRemoteEvent::CeoBan:
			format_string(player, xorstr_("CEO Ban"));
			return true;

		case eRemoteEvent::CeoKick:
			format_string(player, xorstr_("CEO Kick"));
			return true;

		case eRemoteEvent::CeoMoney:
			format_string(player, xorstr_("CEO Money"));
			return true;

		case eRemoteEvent::ClearWantedLevel:
			format_string(player, xorstr_("Clear wanted level"));
			return true;

		case eRemoteEvent::Notification:
			switch (static_cast<eRemoteEvent>(args[2]))
			{
			case eRemoteEvent::NotificationMoneyBanked:
			case eRemoteEvent::NotificationMoneyRemoved:
			case eRemoteEvent::NotificationMoneyStolen:
				format_string(player, xorstr_("Fake deposit"));
				return true;
			}
			break;

		case eRemoteEvent::GtaBanner:
			format_string(player, xorstr_("GTA Banner"));
			return true;

		case eRemoteEvent::PersonalVehicleDestroyed:
			format_string(player, xorstr_("Destroy vehicle"));
			return true;

		case eRemoteEvent::RemoteOffradar:
			format_string(player, xorstr_("Off radar"));
			return true;

		case eRemoteEvent::TSECommand:
			if (static_cast<eRemoteEvent>(args[2]) == eRemoteEvent::TSECommandRotateCam)
			{
				format_string(player, xorstr_("Rotate camera"));
				return true;
			}
			break;

		case eRemoteEvent::SendToCutscene:
			format_string(player, xorstr_("Force cutscene"));
			return true;

		case eRemoteEvent::MCTeleport:
			if (args[3] <= 32)
			{
				format_string(player, xorstr_("Force teleport #1"));
				return true;
			}
			else if (args[3] > 32)
			{
				format_string(player, xorstr_("Script crash #3"));
				return true;
			}
			break;

		case eRemoteEvent::SendToCayoPerico:
			format_string(player, xorstr_("Force teleport #2"));
			return true;

		case eRemoteEvent::SendToLocation:
		{
			bool known_location = false;

			if (args[2] == 0 && args[3] == 0)
			{
				if (args[4] == 4 && args[5] == 0)
				{
					known_location = true;

					format_string(player, xorstr_("Force teleport #3"));
					return true;
				}
				else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
				{
					known_location = true;

					format_string(player, xorstr_("Force teleport #4"));
					return true;
				}
			}

			if (!known_location)
			{
				format_string(player, xorstr_("Script crash #4"));
				return true;
			}
			break;
		}

		case eRemoteEvent::Teleport:
			format_string(player, xorstr_("Force teleport #5"));
			return true;

		case eRemoteEvent::TeleportToWarehouse:
			format_string(player, xorstr_("Force teleport #6"));
			return true;

		case eRemoteEvent::ForceMission:
			format_string(player, xorstr_("Force mission"));
			return true;

		case eRemoteEvent::ForceMission2:
			format_string(player, xorstr_("Force mission #2"));
			return true;

		case eRemoteEvent::SoundSpam:
			format_string(player, xorstr_("Sound spam"));
			return true;

		case eRemoteEvent::Spectate:
			format_string(player, xorstr_("Remote spectate"));
			return true;

		case eRemoteEvent::TransactionError:
			format_string(player, xorstr_("Transaction error"));
			return true;

		case eRemoteEvent::VehicleKick:
			format_string(player, xorstr_("Vehicle kick"));
			return true;

		case eRemoteEvent::StartActivity:
			eActivityType activity = static_cast<eActivityType>(args[2]);
			if (activity == eActivityType::Survival || activity == eActivityType::Mission || activity == eActivityType::Deathmatch || activity == eActivityType::BaseJump || activity == eActivityType::Race)
			{
				format_string(player, xorstr_("Script crash #5"));
				return true;
			}
			else if (activity == eActivityType::Tennis)
			{
				format_string(player, xorstr_("Script crash #6"));
				return true;
			}
			else if (activity == eActivityType::Darts)
			{
				format_string(player, xorstr_("Send to darts"));
				return true;
			}
			else if (activity == eActivityType::PilotSchool)
			{
				format_string(player, xorstr_("Send to flight school"));
				return true;
			}
			else if (activity == eActivityType::ImpromptuDeathmatch)
			{
				format_string(player, xorstr_("Force deathmatch"));
				return true;
			}
			else if (activity == eActivityType::DefendSpecialCargo || activity == eActivityType::GunrunningDefend || activity == eActivityType::BikerDefend)
			{
				format_string(player, xorstr_("Force business raid"));
				return true;
			}
			break;
		}

		return false;
	}
}