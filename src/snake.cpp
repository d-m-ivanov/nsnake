#include "snake.h"

// snake_len -- begin snake length
// window_width -- game_field width
// window_height -- game_field height
Snake::Snake(int snake_len, int window_width, int window_height) {
  int game_field_width = window_width;
  int game_field_height = window_height;

  // Snake first point x coordinate
  int _start_position = (game_field_width - snake_len) / 2;
  // Generate snake vector
  for (int i = 0; i < snake_len; i++) {
    std::pair<int, int> point =
        std::make_pair(_start_position + i, game_field_height / 2);
    snake_points.push_back(point);
  }
}

// Move snake in the direction of speed vector
// Movement steps:
// 1. Delete tail
// 2. Add point to the beginning of the snake in the direction of speed vector
void Snake::snake_update() {
  if (!snake_points.empty()) {
    std::pair<int, int> point =
        std::make_pair(snake_points.back().first + speed.first,
                       snake_points.back().second + speed.second);
    snake_points.erase(snake_points.begin());
    snake_points.push_back(point);
  }
}

void Snake::snake_speed_update(int x, int y) {
  if (speed.first == -x)
    return;
  if (speed.second == -y)
    return;
  speed.first = x;
  speed.second = y;
}

// Grow is simply add new point in the direction of the speed
void Snake::grow(std::pair<int, int> newTail) {
  if (!snake_points.empty()) {
    // Iterator that points to beginning of snake vector
    // In the beginning we are storing the snake tail
    auto tail = snake_points.begin();
    // Insert new point in the beginning of the snake vector
    snake_points.insert(tail, newTail);
  }
}
