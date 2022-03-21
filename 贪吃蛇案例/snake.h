#pragma once

#include "wall.h"

class Snake
{
public:
	Snake(Wall& temp_wall);

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
	void destroy_point();

	Point* p_head;
	Wall& wall;
};
