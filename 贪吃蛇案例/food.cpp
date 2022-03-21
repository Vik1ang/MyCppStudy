#include "food.h"


Food::Food(Wall& temp_wall):wall(temp_wall){}

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
			break;
		}
	}
}
