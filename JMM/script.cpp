/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#include "script.h"

#include <string>
#include <ctime>

#pragma warning(disable : 4244 4305) // double <-> float conversions

bool get_key_pressed(int nVirtKey)
{
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}

void draw_text(char *text, float x, float y, float scale)
{
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(scale, scale);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(2, 2, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(y, x);
}

void main()
{
	DWORD key_pause = 0;
	bool use_mph = false;

	while (true)
	{
		if (get_key_pressed(VK_DIVIDE) && GetTickCount() > key_pause + 250) {
			key_pause = GetTickCount();
			use_mph = !use_mph;
		}

		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) {
			WAIT(0);
			continue;
		}

		if (PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			// speed is in m/s, convert it to km/h
			float speed = ENTITY::GET_ENTITY_SPEED(veh) * 3.6;

			if (use_mph) {
				speed /= 1.60934;
			}

			char speed_text[50];
			sprintf_s(speed_text, "Speed (%s): %.1f", use_mph ? "mph" : "kph", speed);

			draw_text(speed_text, 0.78, 0.01, 0.3);
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
