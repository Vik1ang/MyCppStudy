#include "Hero.h"

Hero::Hero() : m_name("法师"), m_atk(50), m_def(50), m_hp(500), weapon(nullptr)
{
}

void Hero::equip_weapon(Weapon* weapon)
{
	this->weapon = weapon;
	std::cout << "英雄: " << this->m_name << "装备了武器" << this->weapon->m_weapon_name << std::endl;
}

void Hero::attack(Monster* monster)
{
	int damage = 0;
	int add_hp = 0;
	bool is_hold = false;
	bool is_critical = false;

	if (this->weapon == nullptr)
	{
		damage = this->m_atk;
	}
	else
	{
		damage = this->m_atk + this->weapon->get_base_damage();
		add_hp = this->weapon->get_suck_blood();
		is_hold = this->weapon->get_hold();
		is_critical = this->weapon->get_critical();
	}

	if (is_critical)
	{
		damage *= 2;
		std::cout << "英雄的武器触发了暴击效果, 怪物受到双倍的伤害, 伤害值: " << damage << std::endl;
	}
	if (is_hold)
	{
		std::cout << "英雄的武器触发了定身效果, 怪物停止攻击一回合" << std::endl;
	}
	if (add_hp > 0)
	{
		std::cout << "英雄的武器触发了吸血效果, 英雄增加的血量为: " << add_hp << std::endl;
	}

	monster->m_hold = is_hold;
	const int true_damage = (damage - monster->m_def) > 0 ? damage - monster->m_def : 1;
	monster->m_hp -= true_damage;
	this->m_hp += add_hp;

	std::cout << "英雄" << this->m_name << "攻击了敌人" << monster->m_name << "造成了伤害" << true_damage << std::endl;
}