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
	int ch;
	// Initialize ncurses screen.
	initscr();
	// Create a ncurses game field.
	WINDOW *game_field = newwin(height, width, offset, offset);
	// Create a ncurses score field.
	WINDOW *score_field = newwin(height_score, width_score, offset, width + offset + 1);
	// Create snake
	Snake *snake = new Snake(10, game_field);
	// Create GameManager
	GameManager *game_manager = new GameManager(game_field, score_field, snake);
	// Suppress the automatic echoing of typed characters.
	noecho();
	// Without linebreack.
	cbreak();
	// Invisivle cursor
	curs_set(0);
	snake->snake_print();

	while(true) {
		timeout(500);
		ch = getch();
		switch(ch) {
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
				delete game_manager;
				delete snake;
				endwin();
				return 0;
			default:
				break;
		}
		if(game_manager->check_game_over())
			break;
		snake->snake_update();
		snake->snake_print();
		// Main part of program.
	}
	// Restore terminal settings and dealloc ncurses memory.
	game_manager->print_game_over();
	getch();
	delete game_manager;
	delete snake;
	endwin();
	return 0;
}
