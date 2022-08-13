#include "hooking.hpp"

namespace big
{
	int64_t hooks::received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, uint16_t sync_type, uint16_t obj_id, rage::datBitBuffer* buffer, uint16_t unk, uint32_t timestamp)
	{
		auto sync_tree = g_pointers->m_get_sync_tree_for_type(mgr, sync_type);
		auto tree_name = g_pointers->m_get_sync_type_info(sync_type, 0);
		auto net_obj = g_pointers->m_get_net_object(mgr, obj_id, true);
		bool invalidsync = false;

		if (!net_obj)
			net_obj = g_pointers->m_get_net_object_for_player(mgr, obj_id, src, true);

		if (!net_obj)
			return 2;

		if (!sync_tree || sync_type < 0 || sync_type > 14)
			invalidsync = true;

		if (net_obj->m_object_type != sync_type)
			invalidsync = true;

		if (invalidsync && g_config.protection.sync.clone_sync)
		{
			g_notification_service->push_warning("Protection", fmt::format(xorstr_("{} sent invalid sync type: {} in sync tree: {}"), src->get_name(), sync_type, tree_name));

			return 2;
		}

		auto result = g_hooking->m_received_clone_sync_hook.get_original<decltype(&received_clone_sync)>()(mgr, src, dst, sync_type, obj_id, buffer, unk, timestamp);

		return result;

	}
}