#include "backend/backend.hpp"
#include "misc/gta_util.hpp"

namespace big
{
	void backend_engine::update_pointers() { g_local_player = gta_util::get_local_ped(); }
}