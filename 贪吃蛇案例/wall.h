#ifndef WALL_HEAD

#define WALL_HEAD
#include <iostream>

class Wall
{
public:
	enum
	{
		ROW = 26,
		COL = 26
	};

	void init_wall();
	void draw_wall();
	void set_wall(int x, int y, char c);
	char get_wall(int x, int y);
private:
	char game_array[ROW][COL];
};

#endif
