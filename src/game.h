#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "snake.h"
#include <ncurses.h>
#include <random>
#include <string>

// Define moving settings
// Left
#define KEY_H 104
// Down
#define KEY_J 106
// Up
#define KEY_K 107
// Right
#define KEY_L 108
// Quit
#define KEY_Q 113

class GameManager {
private:
  // Current score.
  int score = 0;
  // Initialize fruit
  std::pair<int, int> fruit = std::make_pair(0, 0);
  std::vector<std::pair<int, int>> consumed_fruits;
  // Game window
  WINDOW *game_field;
  // Game window width and height
  int game_field_width;
  int game_field_height;
  // Window to print score on.
  WINDOW *score_window;
  // Score window width and height
  int score_field_width;
  int score_field_height;
  // Instance of Snake object
  Snake *snake;

public:
  GameManager(WINDOW *, WINDOW *, Snake *);
  ~GameManager(){};

public:
  void run_game();

private:
  bool check_game_over();
  bool check_fruit_condition();
  bool check_grow_condition();
  void update_score();
  void update_fruit_position();

private:
  void print_consumed_fruit();
  void print_score_field();
  void print_game_over();
  void print_game_frame();
  void print_snake();
  void print_fruit();
};

#endif
