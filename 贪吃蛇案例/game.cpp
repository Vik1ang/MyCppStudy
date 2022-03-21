#include "game.h"

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned>(time(nullptr)));

	Wall wall;
	wall.init_wall();

	Snake snake(wall);
	snake.init();

	Food food(wall);
	food.set_food();

	wall.draw_wall();

	return EXIT_SUCCESS;
}