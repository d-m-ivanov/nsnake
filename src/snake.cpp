#include "snake.h"

Snake::Snake(int snake_len, WINDOW *win) 
{
	int maxX = win->_maxx;
	int maxY = win->_maxy;
	// Set private fildes.
	window = win;
	speed = std::make_pair(1, 0);
	for(int i = 0; i < snake_len; i++)
	{
		std::pair<int, int> point = std::make_pair((maxX + i - snake_len) / 2, maxY / 2);
		snake_points.push_back(point);
	}
}

void Snake::snake_update()
{
	if(!snake_points.empty())
	{
		std::pair<int, int> point = std::make_pair(
			snake_points.back().first + speed.first,
			snake_points.back().second + speed.second
		);
		snake_points.erase(snake_points.begin());
		snake_points.push_back(point);
	}
}

void Snake::snake_speed_update(int x, int y)
{
	if(speed.first == -x)
		return;
	if(speed.second == -y)
		return;
	speed.first = x;
	speed.second = y;
}

// Grow is simply add new point in the direction of the speed
void Snake::grow()
{
	if(!snake_points.empty())
	{
		std::pair<int, int> point = std::make_pair(
			snake_points.back().first + speed.first,
			snake_points.back().second + speed.second
		);
		snake_points.push_back(point);
	}
}
