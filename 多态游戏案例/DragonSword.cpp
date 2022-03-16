#include "DragonSword.h"

DragonSword::DragonSword() : suck_rate(20), hold_rate(30), critical_rate(35)
{
	this->m_base_damage = 20;
	this->m_weapon_name = "屠龙宝刀";
}

int DragonSword::get_base_damage()
{
	return m_base_damage;
}

int DragonSword::get_suck_blood()
{
	if (is_trigger(suck_rate))
	{
		return this->m_base_damage * 0.5;
	}
	return 0;
}

bool DragonSword::get_hold()
{
	if (is_trigger(hold_rate))
	{
		return true;
	}
	return false;
}

bool DragonSword::get_critical()
{
	if (is_trigger(critical_rate))
	{
		return true;
	}
	return false;
}

bool DragonSword::is_trigger(const int rate)
{
	const int num = rand() % 100 + 1;
	if (num < rate)
	{
		return true;
	}
	return false;
}