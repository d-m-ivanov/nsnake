#pragma once
#ifndef _SNAKE_H
#define _SNAKE_H
#include <ncurses.h>
#include <utility>
#include <vector>

class Snake {
private:
  // Speed vector
  // speed.first -- x coordinate
  // speed.second -- y coordinate
  std::pair<int, int> speed = std::make_pair(1, 0);
  int game_field_width = 0;
  int game_field_height = 0;

public:
  // Snake is a vector of pairs
  // each pairs is a point on the field
  // point.first -- x coordinate
  // point.second -- y coordinate
  std::vector<std::pair<int, int>> snake_points;
  Snake(int, int, int);
  ~Snake(){};
  void snake_update();
  void snake_speed_update(int, int);
  void grow(std::pair<int, int>);
};

#endif
