#include "food.h"

void gotoxy2(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

HANDLE h_out2 = GetStdHandle(STD_OUTPUT_HANDLE);

Food::Food(Wall& temp_wall) :wall(temp_wall) {}

void Food::set_food()
{
	while (true)
	{
		food_x = rand() % (Wall::ROW - 2) + 1;
		food_y = rand() % (Wall::ROW - 2) + 1;

		// 不能长在头和尾
		if (wall.get_wall(food_x, food_y) == ' ')
		{
			wall.set_wall(food_x, food_y, '#');
			gotoxy2(h_out2, food_y * 2, food_x);
			std::cout << "#";
			break;
		}
	}
}