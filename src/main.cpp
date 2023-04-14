#include "game.h"
#include "snake.h"
#include <ncurses.h>

int main() {
  const int width = 30;
  const int height = 15;
  const int width_score = 20;
  const int height_score = 3;
  int termX;
  int termY;
  int offsetX;
  int offsetY;
  // Initialize ncurses screen.
  initscr();
  // Get terminal cols and rows
  getmaxyx(stdscr, termY, termX);
  // Calculate offset
  offsetX = (termX - width) / 2;
  offsetY = (termY - height) / 2;
  // Create a ncurses game field.
  WINDOW *game_field = newwin(height, width, offsetY, offsetX);
  // Create a ncurses score field.
  WINDOW *score_field =
      newwin(height_score, width_score, offsetY, width + offsetX + 1);
  // Create snake
  Snake *snake = new Snake(3, width, height);
  // Create GameManager
  GameManager *game_manager = new GameManager(game_field, score_field, snake);
  // Suppress the automatic echoing of typed characters.
  game_manager->run_game();

  getch();
  delete snake;
  delete game_manager;
  endwin();
  return 0;
}
