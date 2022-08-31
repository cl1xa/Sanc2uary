#include "features/features.hpp"

namespace big
{
	void features_vehicle::vehicle_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			features_vehicle::vehicle_god();
			features_vehicle::horn_boost();
			
		} QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE() 
		{
			features_vehicle::automatic_repair();

		} QUEUE_JOB_END_CLAUSE
	}

	void features_vehicle::vehicle_loop()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				features_vehicle::vehicle_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}
