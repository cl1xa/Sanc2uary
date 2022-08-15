#pragma once

namespace big::teleport
{
	inline bool get_blip_location(Vector3& location, int sprite, int color = -1)
	{
		Blip blip;

		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite); HUD::DOES_BLIP_EXIST(blip) && color != -1 && HUD::GET_BLIP_COLOUR(blip) != color; blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite));

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color))
			return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}

	inline bool get_objective_location(Vector3& location)
	{
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission) ||
			get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission2) ||
			get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Mission) ||
			get_blip_location(location, (int)BlipIcons::RaceFinish, (int)BlipColors::None) ||
			get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Green) ||
			get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Blue) ||
			get_blip_location(location, (int)BlipIcons::CrateDrop))
		{
			return true;
		}

		static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };

		for (const auto& blip : blips)
		{
			if (get_blip_location(location, blip, 5))
				return true;
		}

		return false;
	}

	inline bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		const uint8_t attempts = 10;

		for (uint8_t i = 0; i < attempts; i++)
		{
			for (uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, (float)z);

				script::get_current()->yield();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				return true;
			}

			script::get_current()->yield();
		}

		location.z = 1000.f;

		return false;
	}

	inline void to_coords(Vector3 location)
	{
		PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), location.x, location.y, location.z + 1.f);
	}

	inline bool to_blip(int sprite, int color = -1)
	{
		Vector3 location;

		if (!get_blip_location(location, sprite, color))
			return false;

		if (sprite == (int)BlipIcons::Waypoint)
			load_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), location.x, location.y, location.z);

		return true;
	}

	inline bool to_waypoint()
	{
		if (!to_blip((int)BlipIcons::Waypoint))
		{
			g_notification_service->push_warning(xorstr_("Waypoint"), xorstr_("Failed to gather waypoint info"));

			return false;
		}
		return true;
	}

	inline bool to_objective()
	{
		Vector3 location;

		if (!get_objective_location(location))
		{
			g_notification_service->push_warning(xorstr_("Objective"), xorstr_("Failed to gather objective info"));

			return false;
		}

		PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), location.x, location.y, location.z);

		return false;
	}
}