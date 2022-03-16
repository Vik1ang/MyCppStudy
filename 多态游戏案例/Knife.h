#pragma once
#include <iostream>

#include "Weapon.h"

class Knife : public Weapon
{
public:
	Knife();
	int get_base_damage() override;
	int get_suck_blood() override;
	bool get_hold() override;
	bool get_critical() override;
};
