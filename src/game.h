#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <string>
#include <random>
#include "snake.h"

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

class GameManager
{
	// Current score.
	int score = 0;
	// Initialize fruit
	std::pair<int, int> fruit{0, 0};
	// Game window
	WINDOW *game_field;
	// Window to print score on.
	WINDOW *score_window;
	// Instanse of Snake object
	Snake *snake;
	public:
		GameManager(WINDOW *, WINDOW *, Snake *);
		~GameManager(){};
	public:
		void run_game();
	private:
		bool check_game_over();
		void print_game_over();
		void print_game_frame();
		void print_snake();
		void print_fruit();
		bool check_fruit_condition();
		void print_score_field();
		void update_score();
		void update_fruit_position();
};

#endif
