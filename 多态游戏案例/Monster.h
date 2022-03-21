#pragma once
#include <string>

#include "Hero.h"

class Hero;

class Monster
{
public:
	Monster();
	std::string m_name;
	int m_atk;
	int m_def;
	int m_hp;
	bool m_hold;
	void attack(Hero* hero) const;
};
