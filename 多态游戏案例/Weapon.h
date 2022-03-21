#pragma once

#include <iostream>
#include <string>

// ³éÏóÀà
class Weapon
{
public:
	virtual int get_base_damage() = 0;
	virtual int get_suck_blood() = 0;
	virtual bool get_hold() = 0;
	virtual bool get_critical() = 0;

	std::string m_weapon_name;
	int m_base_damage;
};
