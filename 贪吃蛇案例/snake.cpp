#include "snake.h"

void gotoxy1(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

HANDLE h_out1 = GetStdHandle(STD_OUTPUT_HANDLE);

Snake::Snake(Wall& temp_wall, Food& temp_food) : p_head(nullptr), wall(temp_wall), food(temp_food), is_loop(false) {}

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
		gotoxy1(h_out1, p_head->y * 2, p_head->x);
		std::cout << "=";
	}
	n_point->next = p_head;

	p_head = n_point; // 更新头部

	wall.set_wall(p_head->x, p_head->y, '@');
	gotoxy1(h_out1, p_head->y * 2, p_head->x);
	std::cout << "@";
}

void Snake::delete_point() const
{
	if (p_head == nullptr || p_head->next == nullptr)
	{
		return;
	}

	Point* p_curr = p_head->next;
	Point* p_pre = p_head;

	while (p_curr->next != nullptr)
	{
		p_pre = p_pre->next;
		p_curr = p_curr->next;
	}

	wall.set_wall(p_curr->x, p_curr->y, ' ');
	gotoxy1(h_out1, p_curr->y * 2, p_curr->x);
	std::cout << " ";

	delete p_curr;
	p_curr = nullptr;
	p_pre->next = nullptr;
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

bool Snake::move(char key)
{
	int x = p_head->x;
	int y = p_head->y;

	switch (key)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	// 碰到尾巴
	Point* p_curr = p_head->next;
	Point* p_pre = p_head;
	while (p_curr->next != nullptr)
	{
		p_pre = p_pre->next;
		p_curr = p_curr->next;
	}
	if (p_curr->x == x && p_curr->y == y)
	{
		is_loop = true;
	}
	else
	{
		if (wall.get_wall(x, y) == '*' || wall.get_wall(x, y) == '=')
		{
			add_point(x, y);
			delete_point();
			system("cls");
			wall.draw_wall();
			std::cout << "GAME OVER" << std::endl;
			std::cout << "最终得分: " << get_score() << std::endl;
			return false;
		}
	}

	if (wall.get_wall(x, y) == '#')
	{
		add_point(x, y);
		food.set_food();
	}
	else
	{
		add_point(x, y);
		delete_point();
		if (is_loop)
		{
			wall.set_wall(x, y, '@');
			gotoxy1(h_out1, y * 2, x);
			std::cout << "@";
		}
	}

	return true;
}

int Snake::get_sleep_time() const
{
	int sleep_time;
	const int size = get_snake_length();

	if (size < 5)
	{
		sleep_time = 300;
	}
	else if (size >= 5 && size <= 10)
	{
		sleep_time = 200;
	}
	else
	{
		sleep_time = 100;
	}

	return sleep_time;
}

int Snake::get_snake_length() const
{
	int size = 0;
	Point* curr = p_head;
	while (curr != nullptr)
	{
		size++;
		curr = curr->next;
	}

	return size;
}

int Snake::get_score() const
{
	const int size = get_snake_length();
	return (size - 3) * 100;
}