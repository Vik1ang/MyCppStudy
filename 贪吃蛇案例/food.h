#pragma once

#include <cstdlib>
#include "wall.h"

class Food
{
public:
	explicit Food(Wall& temp_wall);
	void set_food();

	int food_x{};
	int food_y{};
	Wall& wall;
};
