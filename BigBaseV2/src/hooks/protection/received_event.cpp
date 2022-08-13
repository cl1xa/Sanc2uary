#include "gta/enums.hpp"
#include "gta/structs.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"

namespace big
{
	void hooks::received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int unk, rage::datBitBuffer* buffer)
	{
		//const char* sender_name = source_player->get_name();

		//uint16_t _event_id = event_id;

		//const auto event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);

		////Session switching optimization #2
		//if (g_config.protection.misc.optimize_loading) 
		//{
		//	if (
		//		_event_id > 91u
		//		|| event_name == nullptr
		//		|| source_player == nullptr
		//		|| source_player->m_player_id < 0
		//		|| source_player->m_player_id >= 32)
		//	{

		//		LOG(G3LOG_DEBUG) << fmt::format(xorstr_("Cleaned protocol garbage from: {} [{} : {} : {} : {}]"), sender_name, _event_id,
		//			event_name,
		//			fmt::ptr(source_player),
		//			source_player->m_player_id);

		//		g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//		return;
		//	}
		//}

		//switch (static_cast<eNetworkEvents>(event_id))
		//{ //Begin switch case

		//case eNetworkEvents::CNetworkTrainReportEvent:
		//case eNetworkEvents::CNetworkTrainRequestEvent:
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//	return;

		//	//Modder detection
		//case eNetworkEvents::CReportCashSpawnEvent:
		//case eNetworkEvents::CNetworkCheckCodeCrcsEvent:
		//case eNetworkEvents::CUpdateFxnEvent:
		//	if (g_config.protection.misc.modder_detection)
		//	{
		//		g_notification_service->push_warning(xorstr_("Modder detection"), fmt::format(xorstr_("{} was flagged as a modder: {}"), sender_name, name_network_event[event_id]));

		//		g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//		return; //Only block event, do not send back to them. We want to remain invisible to modders.
		//	}
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//	break;

		//	//Script event handler
		//case eNetworkEvents::CScriptedGameEvent:
		//{
		//	const auto scripted_game_event = make_unique<CScriptedGameEvent>();

		//	buffer->ReadDword(&scripted_game_event->m_args_size, 32);

		//	if (scripted_game_event->m_args_size - 1 <= 0x1AF)
		//		buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

		//	const auto args = scripted_game_event->m_args;
		//	const auto hash = static_cast<eRemoteEvent>(args[0]);

		//	//For debugging
		//	if (g_config.settings.script_event_logger)
		//	{
		//		LOG(G3LOG_DEBUG) << xorstr_("===");
		//		LOG(G3LOG_DEBUG) << fmt::format(xorstr_("PLAYER: {} | EVENT: {}"), source_player->get_name(), int(hash));

		//		for (size_t i = 1; i < sizeof(args); i++)
		//			LOG(G3LOG_DEBUG) << fmt::format(xorstr_("Arg #{} : {}"), i, args[i]);

		//		LOG(G3LOG_DEBUG) << xorstr_("===");
		//	}

		//	if (g_config.protection.events.script)
		//	{
		//		//If the user sends us an unwanted script event
		//		if (hooks::scripted_game_event(scripted_game_event.get(), source_player))
		//		{
		//			g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent script event: {}"), sender_name, (int)hash));

		//			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//			return;
		//		}

		//		buffer->Seek(0);
		//	}
		//}
		//g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//break;

		//	//Stat event detection
		//case eNetworkEvents::CNetworkIncrementStatEvent:
		//	if (g_config.protection.other.stat_increment)
		//	{
		//		const auto increment_stat_event = std::make_unique<CNetworkIncrementStatEvent>();

		//		buffer->ReadDword(&increment_stat_event->m_stat, 0x20);
		//		buffer->ReadDword(&increment_stat_event->m_amount, 0x20);

		//		if (hooks::increment_stat_event(increment_stat_event.get(), source_player))
		//		{
		//			g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent stat: {}"), sender_name, fmt::ptr(increment_stat_event.get())));

		//			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//			return; //Block stat increment
		//		}

		//		buffer->Seek(0);
		//	}
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//	break;

		//	// TASK_VEHICLE_TEMP_ACTION patch
		//case eNetworkEvents::CScriptEntityStateChangeEvent:
		//	if (g_config.protection.crash.task_vehicle_temp_action)
		//	{
		//		uint16_t entity;
		//		buffer->ReadWord(&entity, 13);
		//		uint32_t type;
		//		buffer->ReadDword(&type, 4);
		//		uint32_t unk;
		//		buffer->ReadDword(&unk, 32);

		//		if (type == 6)
		//		{
		//			uint16_t unk2;
		//			buffer->ReadWord(&unk2, 13);
		//			uint32_t action;
		//			buffer->ReadDword(&action, 8);

		//			if (action >= 15 && action <= 18)
		//			{
		//				g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent: TASK_VEHICLE_TEMP_ACTION crash"), sender_name));

		//				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//				return;
		//			}

		//			buffer->Seek(0);
		//		}
		//	}
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//	break;

		//	//Vote kick detection
		//case eNetworkEvents::CKickVotesEvent:
		//{
		//	if (g_config.protection.events.game)
		//	{
		//		std::uint32_t player_bitfield;

		//		buffer->ReadDword(&player_bitfield, 32);

		//		if (player_bitfield & 1 << target_player->m_player_id)
		//		{
		//			g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent: vote kick"), sender_name));

		//			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//		}

		//		buffer->Seek(0);

		//		return;
		//	}
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//	break;
		//}

		//	//Common game event protection
		//case eNetworkEvents::CNetworkClearPedTasksEvent:
		//case eNetworkEvents::CRequestControlEvent:
		//case eNetworkEvents::CNetworkStartPedArrestEvent:
		//case eNetworkEvents::CNetworkStartPedUncuffEvent:
		//case eNetworkEvents::CNetworkPtfxEvent:
		//case eNetworkEvents::CGiveWeaponEvent:
		//case eNetworkEvents::CRemoveWeaponEvent:
		//case eNetworkEvents::CRemoveAllWeaponsEvent:
		//case eNetworkEvents::CRagdollRequestEvent:
		//case eNetworkEvents::CAlterWantedLevelEvent:
		//	if (g_config.protection.events.game)
		//	{
		//		g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent game event: {}"), sender_name, name_network_event[event_id]));

		//		g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//		return;
		//	}
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//	break;

		//	//Action event protection
		////case eNetworkEvents::UPDATE_PROJECTILE_TARGET_EVENT:
		//case eNetworkEvents::START_PROJECTILE_EVENT:
		//case eNetworkEvents::FIRE_EVENT:
		//case eNetworkEvents::EXPLOSION_EVENT:
		//case eNetworkEvents::BLOW_UP_VEHICLE_EVENT:
		//case eNetworkEvents::INFORM_SILENCED_GUNSHOT_EVENT:
		//case eNetworkEvents::UPDATE_PLAYER_SCARS_EVENT:
		//case eNetworkEvents::CBreakProjectileTargetLockEvent:
		//case eNetworkEvents::CUpdateProjectileTargetEvent:
		//case eNetworkEvents::CFireEvent:
		//case eNetworkEvents::CExplosionEvent:
		//case eNetworkEvents::CBlowUpVehicleEvent:
		//case eNetworkEvents::CInformSilencedGunshotEvent:
		//case eNetworkEvents::CUpdatePlayerScarsEvent:
		//	if (g_config.protection.events.action)
		//	{
		//		g_notification_service->push_warning(xorstr_("Protection"), fmt::format(xorstr_("{} sent action event: {}"), sender_name, name_network_event[event_id]));

		//		g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//		return;
		//	}
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
		//	break;

		//#pragma endregion

		//	//Not sure if I should do this? Doing it anyway.
		//default:
		//	g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

		//	break;

		//} //End switch case

		return g_hooking->m_received_event_hook.get_original<decltype(&received_event)>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, unk, buffer);
	}
}