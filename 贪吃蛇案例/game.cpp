#include "game.h"

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned>(time(nullptr)));

	bool is_dead = false;

	char pre_key = NULL;

	Wall wall;
	wall.init_wall();
	wall.draw_wall();

	Food food(wall);
	food.set_food();

	Snake snake(wall, food);
	snake.init();

	gotoxy(h_out, 0, Wall::ROW);
	std::cout << "得分: " << snake.get_score() << std::endl;

	while (!is_dead)
	{
		char key = _getch();

		if (pre_key == NULL && key == snake.LEFT)
		{
			continue;
		}

		do
		{
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				if (
					key == snake.LEFT && pre_key == snake.RIGHT ||
					key == snake.RIGHT && pre_key == snake.LEFT ||
					key == snake.UP && pre_key == snake.DOWN ||
					key == snake.DOWN && pre_key == snake.UP
					)
				{
					key = pre_key;
				}
				else
				{
					pre_key = key;
				}
				if (snake.move(key))
				{
					//system("cls");
					//wall.draw_wall();
					gotoxy(h_out, 0, Wall::ROW);
					std::cout << "得分: " << snake.get_score() << std::endl;
					Sleep(snake.get_sleep_time());
				}
				else
				{
					is_dead = true;
					break;
				}
			}
			else
			{
				key = pre_key;
			}
		} while (!_kbhit());
	}

	return EXIT_SUCCESS;
}