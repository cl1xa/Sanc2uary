#include "hooking/hooking.hpp"

namespace big
{
	void hooks::received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int unk, rage::datBitBuffer* buffer)
	{
		const char* sender_name = source_player->get_name();

		uint16_t _event_id = event_id;

		const auto event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);

		//Session switching optimization #2
		if (g_config.misc.optimize_loading)
		{
			if (
				_event_id > 91u
				|| event_name == nullptr
				|| source_player == nullptr
				|| source_player->m_player_id < 0
				|| source_player->m_player_id >= 32)
			{

				LOG(G3LOG_DEBUG) << fmt::format(xorstr_("Cleaned protocol data from: {} [{} : {} : {} : {}]"), sender_name, _event_id,
					event_name,
					fmt::ptr(source_player),
					source_player->m_player_id);

				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
		}

		switch (static_cast<eNetworkEvents>(event_id))
		{ //Begin switch case

		case eNetworkEvents::NETWORK_TRAIN_REPORT_EVENT:
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return;

			//Modder detection
		case eNetworkEvents::REPORT_CASH_SPAWN_EVENT:
		case eNetworkEvents::NETWORK_CHECK_CODE_CRCS_EVENT:
		case eNetworkEvents::REPORT_MYSELF_EVENT:
			if (g_config.misc.modder_detection)
			{
				g_notification_service->push_warning(xorstr_("Modder detection"), fmt::format(xorstr_("{} was flagged as a modder: {}"), sender_name, event_name));

				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return; //Only block event, do not send back to them. We want to remain invisible to modders.
			}
			break;

			//Script event handler
		case eNetworkEvents::SCRIPTED_GAME_EVENT:
		{
			const auto scripted_game_event = make_unique<CScriptedGameEvent>();

			buffer->ReadDword(&scripted_game_event->m_args_size, 32);

			if (scripted_game_event->m_args_size - 1 <= 0x1AF)
				buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

			const auto args = scripted_game_event->m_args;
			const auto hash = static_cast<eRemoteEvent>(args[0]);

			//For debugging
			if (g_config.settings.script_event_logger)
			{
				LOG(G3LOG_DEBUG) << xorstr_("===");
				LOG(G3LOG_DEBUG) << fmt::format(xorstr_("PLAYER: {} | EVENT: {}"), source_player->get_name(), int(hash));

				for (size_t i = 1; i < sizeof(args); i++)
					LOG(G3LOG_DEBUG) << fmt::format(xorstr_("Arg #{} : {}"), i, args[i]);

				LOG(G3LOG_DEBUG) << xorstr_("===");
			}

			if (g_config.protection.events.script)
			{
				//If the user sends us an unwanted script event
				if (hooks::scripted_game_event(scripted_game_event.get(), source_player))
				{
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

					buffer->Seek(0);
					return;
				}
			}

			buffer->Seek(0);
		}
		break;

		//Stat event detection
		case eNetworkEvents::NETWORK_INCREMENT_STAT_EVENT:
			if (g_config.protection.other.stat_increment)
			{
				const auto increment_stat_event = make_unique<CNetworkIncrementStatEvent>();

				buffer->ReadDword(&increment_stat_event->m_stat, 0x20);
				buffer->ReadDword(&increment_stat_event->m_amount, 0x20);

				if (hooks::increment_stat_event(increment_stat_event.get(), source_player))
				{
					g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent stat: {}"), sender_name, fmt::ptr(increment_stat_event.get())));

					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

					buffer->Seek(0);
					return; //Block stat increment
				}

				buffer->Seek(0);
			}
			break;

			// TASK_VEHICLE_TEMP_ACTION patch
		case eNetworkEvents::SCRIPT_ENTITY_STATE_CHANGE_EVENT:
			if (g_config.protection.crash.task_vehicle_temp_action)
			{
				uint16_t entity;
				buffer->ReadWord(&entity, 13);
				uint32_t type;
				buffer->ReadDword(&type, 4);
				uint32_t unk;
				buffer->ReadDword(&unk, 32);

				if (type == 6)
				{
					uint16_t unk2;
					buffer->ReadWord(&unk2, 13);
					uint32_t action;
					buffer->ReadDword(&action, 8);

					if (action >= 15 && action <= 18)
					{
						g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent: TASK_VEHICLE_TEMP_ACTION crash"), sender_name));

						g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

						buffer->Seek(0);
						return;
					}

					buffer->Seek(0);
				}

				buffer->Seek(0);
			}
			break;

			//Vote kick detection
		case eNetworkEvents::KICK_VOTES_EVENT:
			if (g_config.protection.other.vote)
			{
				g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent: vote kick"), sender_name));

				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
			break;

#pragma region Unwanted game event protection
		case eNetworkEvents::REQUEST_CONTROL_EVENT: //Need to fix false positive spam
		case eNetworkEvents::RAGDOLL_REQUEST_EVENT:

		case eNetworkEvents::NETWORK_CLEAR_PED_TASKS_EVENT:
		case eNetworkEvents::NETWORK_START_PED_ARREST_EVENT:
		case eNetworkEvents::NETWORK_START_PED_UNCUFF_EVENT:

		case eNetworkEvents::NETWORK_PTFX_EVENT:

		case eNetworkEvents::GIVE_WEAPON_EVENT:
		case eNetworkEvents::REMOVE_WEAPON_EVENT:
		case eNetworkEvents::REMOVE_ALL_WEAPONS_EVENT:

			if (g_config.protection.events.game)
			{
				g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent game event: {}"), sender_name, event_name));

				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
			break;
#pragma endregion

#pragma region Action event protection
		case eNetworkEvents::WEAPON_DAMAGE_EVENT:
		case eNetworkEvents::FIRE_EVENT:
		case eNetworkEvents::EXPLOSION_EVENT:
		case eNetworkEvents::BLOW_UP_VEHICLE_EVENT:
		case eNetworkEvents::UPDATE_PLAYER_SCARS_EVENT:
		case eNetworkEvents::INFORM_SILENCED_GUNSHOT_EVENT:
		case eNetworkEvents::PED_PLAY_PAIN_EVENT:
			if (g_config.protection.events.action)
			{
				g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent action event: {}"), sender_name, event_name));

				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
			break;
#pragma endregion

			//Not sure if I should do this? Doing it anyway.
		default:
			break;

		} //End switch case

		return g_hooking->m_received_event_hook.get_original<decltype(&received_event)>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, unk, buffer);
	}
}