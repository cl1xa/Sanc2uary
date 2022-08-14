#include "backend.hpp"
namespace big
{
	void backend_vehicle::vehicle_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_vehicle::vehicle_god();
			backend_vehicle::horn_boost();

		} QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE() //This needs to be queued separate, otherwise it clogs the queue
		{
			backend_vehicle::automatic_repair();

		} QUEUE_JOB_END_CLAUSE
	}

	void backend_vehicle::vehicle_loop()
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
