#pragma once

#include "food.h"
#include "wall.h"
#include <Windows.h>

class Snake
{
public:
	Snake(Wall& temp_wall, Food& temp_food);

	enum {
		UP = 'w',
		DOWN = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};

	struct Point
	{
		// 数据域
		int x;
		int y;

		// 指针域
		Point* next;
	};

	void init();
	void add_point(int x, int y);
	void delete_point() const;
	void destroy_point();
	bool move(char key);
	int get_sleep_time() const;
	int get_snake_length() const;
	int get_score() const;

	Point* p_head;
	Wall& wall;
	Food& food;

	bool is_loop;
};
