#include "backend.hpp"
#include "common.hpp"
#include "script_mgr.hpp"
#include "fiber_pool.hpp"
#include "script_global.hpp"

namespace big
{
	void backend_vehicle::vehicle_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_vehicle::vehicle_god();
			backend_vehicle::automatic_repair();
			backend_vehicle::horn_boost();

		} QUEUE_JOB_END_CLAUSE
	}

	void backend_vehicle::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				backend_vehicle::vehicle_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}
