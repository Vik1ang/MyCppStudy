#pragma once
#include <string>

#include "Monster.h"
#include "Weapon.h"

class Monster;

class Hero
{
public:
	Hero();

	std::string m_name;
	int m_atk;
	int m_def;
	int m_hp;
	Weapon* weapon;
	void equip_weapon(Weapon* weapon);
	void attack(Monster* monster);
};
