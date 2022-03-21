#pragma once

#include "Weapon.h"

class DragonSword : public Weapon
{
public:
	DragonSword();
	int get_base_damage() override;
	int get_suck_blood() override;
	bool get_hold() override;
	bool get_critical() override;

	int suck_rate;
	int hold_rate;
	int critical_rate;

	static bool is_trigger(int rate);
};
