#include "Hero.h"
#include "Monster.h"
#include "Knife.h"
#include "DragonSword.h"

void play()
{
	Monster* monster = new Monster;
	Hero* hero = new Hero;

	Weapon* knife = new Knife;
	Weapon* dragon_sword = new DragonSword;

	std::cout << "请选择武器: " << std::endl;
	std::cout << "1. 赤手空拳" << std::endl;
	std::cout << "2. 小刀" << std::endl;
	std::cout << "3. 屠龙宝刀" << std::endl;

	int choice;
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		std::cout << "选择赤手空拳" << std::endl;
		break;
	case 2:
		hero->equip_weapon(knife);
		break;
	case 3:
		hero->equip_weapon(dragon_sword);
		break;
	default:
		break;
	}

	getchar();

	int round = 1;

	while (true)
	{
		getchar();
		system("cls");

		std::cout << "------当前是第" << round << "回合开始------" << std::endl;
		if (hero->m_hp <= 0)
		{
			std::cout << "英雄" << hero->m_name << "已挂, 游戏结束";
			break;
		}

		hero->attack(monster);
		if (monster->m_hp < 0)
		{
			std::cout << "怪物" << monster->m_name << "已挂, 顺利通关" << std::endl;
			break;
		}
		monster->attack(hero);
		if (hero->m_hp <= 0)
		{
			std::cout << "英雄" << hero->m_name << "已挂, 游戏结束";
			break;
		}

		std::cout << "英雄" << hero->m_name << "剩余血量" << hero->m_hp << std::endl;
		std::cout << "怪物" << monster->m_name << "剩余血量" << monster->m_hp << std::endl;

		round++;
	}

	delete monster;
	delete hero;
	delete knife;
	delete dragon_sword;
}

int main(int argc, char* argv[])
{
	play();
	return EXIT_SUCCESS;
}