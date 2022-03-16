#include "Monster.h"

Monster::Monster() : m_name("比克"), m_atk(70), m_def(40), m_hp(300), m_hold(false)
{
}

void Monster::attack(Hero* hero) const
{
	if (this->m_hold)
	{
		std::cout << "怪物" << this->m_name << "被定身了, 本回合无法攻击" << std::endl;
	}

	int damage = this->m_atk - hero->m_def > 0 ? this->m_atk - hero->m_def : 1;

	hero->m_hp -= damage;

	std::cout << "怪物" << this->m_name << "攻击了英雄" << this->m_name << "造成了伤害" << damage << std::endl;
}