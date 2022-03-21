#include "snake.h"

Snake::Snake(Wall& temp_wall) : p_head(nullptr), wall(temp_wall) {}

void Snake::init()
{
	destroy_point();

	add_point(5, 3);
	add_point(5, 4);
	add_point(5, 5);
}

void Snake::add_point(const int x, const int y)
{
	// 创建新结点
	Point* n_point = new Point;
	n_point->x = x;
	n_point->y = y;
	n_point->next = nullptr;

	// 如果头不为空改为身子
	if (p_head != nullptr)
	{
		wall.set_wall(p_head->x, p_head->y, '=');
	}
	n_point->next = p_head;

	p_head = n_point; // 更新头部

	wall.set_wall(p_head->x, p_head->y, '@');
}

void Snake::destroy_point()
{
	Point* p_cur = p_head;
	while (p_head != nullptr)
	{
		p_cur = p_head->next;
		delete p_head;
		p_head = p_cur;
	}
}