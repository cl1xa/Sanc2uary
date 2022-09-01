#include "hooking/hooking.hpp"
#include "services/player_service.hpp"
#include <gta/natives.hpp>

namespace big
{
	bool get_msg_type(rage::eNetMessage& msgType, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};

		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1)) 
		{
			msgType = rage::eNetMessage::CMsgInvalid;

			return false;
		}

		length = extended ? 16 : 8;

		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit), length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
			return true;
		else
			return false;
	}

	bool hooks::receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame)
	{
		if (g_config.protection.other.host_desync)
		{
			if (frame->get_type() == 4)
			{
				rage::datBitBuffer buffer((uint8_t*)frame->m_data, frame->m_length);

				buffer.m_flagBits = 1;

				rage::eNetMessage msgType;

				const auto player = g_player_service->get_by_msg_id(frame->m_msg_id);

				if (player && get_msg_type(msgType, buffer))
				{
					switch (msgType)
					{
						//Desync Kick #1
					case rage::eNetMessage::CMsgNetComplaint:
					{
						uint64_t hostToken;

						buffer.ReadQWord(&hostToken, 0x40);
						buffer.Seek(0);

						player_ptr sender = g_player_service->get_by_host_token(hostToken);

						sender->get_net_game_player()->m_complaints = USHRT_MAX; //Sender

						g_notification_service->push_warning(xorstr_("Protections"), (string)player->get_name() + " sent: desync kick #1");

						buffer.Seek(0);
						return false;
					}

						//Desync Kick #2
					case rage::eNetMessage::CMsgScriptMigrateHost:
					{
						if (chrono::system_clock::now() - player->m_last_transition_msg_sent < 200ms)
						{
							if (player->m_num_failed_transition_attempts++ == 20)
								g_notification_service->push_warning(xorstr_("Protections"), (string)player->get_name() + " sent: desync kick #2");

							return true;
						}
						else
						{
							player->m_last_transition_msg_sent = chrono::system_clock::now();
							player->m_num_failed_transition_attempts = 0;
						}
						break;
					}

					}
				}
			}
		}

		return g_hooking->m_receive_net_message_hook.get_original<decltype(&hooks::receive_net_message)>()(netConnectionManager, a2, frame);
	}
}