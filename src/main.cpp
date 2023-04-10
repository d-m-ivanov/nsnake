#include <ncurses.h>
#include "snake.h"
#include "game.h"


int main()
{
	const int width = 50;
	const int height = 25;
	const int width_score = 20;
	const int height_score = 3;
	const int offset = 2;
	// Initialize ncurses screen.
	initscr();
	// Create a ncurses game field.
	WINDOW *game_field = newwin(height, width, offset, offset);
	// Create a ncurses score field.
	WINDOW *score_field = newwin(height_score, width_score, offset, width + offset + 1);
	// Create snake
	Snake *snake = new Snake(3, game_field);
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
