#include "Knife.h"

Knife::Knife()
{
	this->m_base_damage = 10;
	this->m_weapon_name = "ะกตถ";
}

int Knife::get_base_damage()
{
	return this->m_base_damage;
}

int Knife::get_suck_blood()
{
	return 0;
}

bool Knife::get_hold()
{
	return false;
}

bool Knife::get_critical()
{
	return false;
}