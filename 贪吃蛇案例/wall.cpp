#include "wall.h"

void Wall::init_wall()
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1)
			{
				game_array[i][j] = '*';
			}
			else
			{
				game_array[i][j] = ' ';
			}
		}
	}
}

void Wall::draw_wall()
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			std::cout << game_array[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Wall::set_wall(int x, int y, char c)
{
	game_array[x][y] = c;
}

char Wall::get_wall(int x, int y)
{
	return game_array[x][y];
}