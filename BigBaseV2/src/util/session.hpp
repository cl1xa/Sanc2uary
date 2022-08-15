#pragma once
#include "gta/session_types.hpp"
#include "script_global.hpp"

namespace big::session
{
	void join_type(SessionType session)
	{
		*script_global(2726795).as<int*>() = (session.id == eSessionType::SC_TV ? 1 : 0); // If SC TV Then Enable Spectator Mode

		if (session.id == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).at(2).as<int*>() = -1;
		else
			*script_global(1575015).as<int*>() = (int)session.id;

		*script_global(1574589).as<int*>() = 1;

		script::get_current()->yield(200ms);

		*script_global(1574589).as<int*>() = 0;
	}
}