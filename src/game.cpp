#include "game.h"
#include <curses.h>
#include <string>

// GameManager Constructor
GameManager::GameManager(WINDOW *game_field_window, WINDOW *score_field_window,
                         Snake *snake_istance) {
  this->game_field = game_field_window;
  this->score_window = score_field_window;
  this->snake = snake_istance;

  // Ncurses call to get widths and heights of windows
  getmaxyx(game_field_window, game_field_height, game_field_width);
  getmaxyx(score_field_window, score_field_height, score_field_width);
}

// Check game over conditions
// 1. Collision with border
// 2. Collision with body of the snake
bool GameManager::check_game_over() {
  // Get border max X and Y coordinates
  int maxX = game_field_width - 1;
  int maxY = game_field_height - 1;

  // Get snake head coordinates
  int headX = snake->snake_points.back().first;
  int headY = snake->snake_points.back().second;

  // Check if head of the snake collides with borders
  if (headX == 0 || headY == 0 || headX == maxX || headY == maxY)
    return true;

  // Check if head of the snake collides with body
  // Need to skip head itself; Is there exists smart way to do this check?
  for (unsigned int i = 0; i < (snake->snake_points.size() - 1); ++i) {
    if (snake->snake_points[i].first == headX &&
        snake->snake_points[i].second == headY) {
      return true;
    }
  }

  // Otherwise return false
  return false;
}

// Print Game Over screen.
void GameManager::print_game_over() {
  int maxX;
  int maxY;

  // Geting rows and cols of terminal window
  getmaxyx(stdscr, maxY, maxX);

  std::string message = "GAME OVER!!! Press any button to exit!";
  std::string score_message = "Your score is: " + std::to_string(this->score);
  wclear(stdscr);
  mvwprintw(stdscr, maxY / 2, (maxX - message.length()) / 2, message.c_str());
  mvwprintw(stdscr, maxY / 2 + 1, (maxX - score_message.length()) / 2,
            score_message.c_str());
  wrefresh(stdscr);
  // Enable blocking to hold on game over screen
  timeout(-1);
}

// Method for a fruit printing
void GameManager::print_fruit() {
  mvwprintw(this->game_field, this->fruit.second, this->fruit.first, "F");
}

// Method for the snake printing
void GameManager::print_snake() {
  for (auto &point : snake->snake_points) {
    if (point == snake->snake_points.back()) {
      mvwprintw(game_field, point.second, point.first, "@");
    } else {
      mvwprintw(game_field, point.second, point.first, "S");
    }
  }
}

// Print frame of the game field window
void GameManager::print_game_frame() {
  wclear(this->game_field);
  box(this->game_field, 0, 0);
  this->print_snake();
  this->print_fruit();
  wrefresh(this->game_field);
}

void GameManager::print_score_field() {
  // Get border max X and Y coordinates
  int maxX = score_field_width - 1;
  std::string header = "SCORE";

  wclear(this->score_window);
  box(this->score_window, 0, 0);
  mvwprintw(this->score_window, 0, (maxX - header.length()) / 2,
            header.c_str());
  mvwprintw(this->score_window, 1, (maxX - 9) / 2, "%09d", this->score);
  wrefresh(this->score_window);
}

void GameManager::update_fruit_position() {
  std::random_device rd;
  std::mt19937 gen(rd());
  int maxX = game_field_width - 1;
  int maxY = game_field_height - 1;
  std::uniform_int_distribution<int> uintX(1, maxX - 1);
  std::uniform_int_distribution<int> uintY(1, maxY - 1);
  while (true) {
    fruit.first = uintX(gen);
    fruit.second = uintY(gen);
    for (auto &point : snake->snake_points) {
      if ((point.first == fruit.first) && (point.second == fruit.second))
        break;
      return;
    }
  }
}

bool GameManager::check_fruit_condition() {
  int headX = this->snake->snake_points.back().first;
  int headY = this->snake->snake_points.back().second;
  if (fruit.first == headX && fruit.second == headY) {
    consumed_fruits.push_back(fruit);
    return true;
  }
  return false;
}

void GameManager::update_score() { score += 10; }

bool GameManager::check_grow_condition() {
  // Get snake tail coordinates
  int tailX = snake->snake_points[0].first;
  int tailY = snake->snake_points[0].second;
  if (!consumed_fruits.empty()) {
    if (tailX == consumed_fruits[0].first &&
        tailY == consumed_fruits[0].second) {
      return true;
    }
  }
  return false;
}

// Game main loop
void GameManager::run_game() {
  // Variable to store pressed keys
  int ch;
  bool first_frame = true;
  // Suppress the automatic echoing of typed characters.
  noecho();
  // Without line break.
  cbreak();
  // Invisible cursor
  curs_set(0);
  this->update_fruit_position();
  this->print_score_field();
  while (true) {
    timeout(500);
    ch = getch();
    switch (ch) {
    case KEY_H:
      snake->snake_speed_update(-1, 0);
      break;
    case KEY_J:
      snake->snake_speed_update(0, 1);
      break;
    case KEY_K:
      snake->snake_speed_update(0, -1);
      break;
    case KEY_L:
      snake->snake_speed_update(1, 0);
      break;
    case KEY_Q:
      return;
    default:
      break;
    }
    if (this->check_game_over())
      break;
    if (this->check_fruit_condition()) {
      this->update_fruit_position();
      this->update_score();
      this->print_score_field();
    }
    if (this->check_grow_condition()) {
      this->snake->grow(consumed_fruits[0]);
      consumed_fruits.erase(consumed_fruits.begin());
    }
    if (first_frame) {
      this->print_score_field();
      first_frame = false;
    }
    snake->snake_update();
    this->print_game_frame();
  }

  this->print_game_over();
}
