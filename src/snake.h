#ifndef _SNAKE_H
#define _SNAKE_H
#include <vector>
#include <utility>
#include <ncurses.h>

class Snake
{
	std::pair<int, int> speed;
	WINDOW *window;
	public:
		std::vector<std::pair<int,int>> snake_points;
		Snake(int, WINDOW *);
		void snake_update();
		void snake_speed_update(int, int);
		void snake_print();
};

#endif
