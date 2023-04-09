#include "game.h"
#include <string>

GameManager::GameManager(WINDOW *game_field_window, WINDOW *score_field_window, Snake *snake_istance)
{
	this->game_field = game_field_window;
	this->score_window = score_field_window;
	this->snake = snake_istance;
}

bool GameManager::check_game_over()
{
	// Get border max X and Y coords
	int maxX = game_field->_maxx;
	int maxY = game_field->_maxy;

	// Get snake head coords
	int headX = snake->snake_points.back().first;
	int headY = snake->snake_points.back().second;

	// Check if head of the snake collides with borders
	if(headX == 0 || headY == 0 || headX == maxX || headY == maxY)
		return true;

	// Check if head of the snake collides with body
	// Need to skip head itself; Is there exists smart way to do this check?
	for(unsigned int i = 0; i < (snake->snake_points.size() - 1); ++i) {
			if(snake->snake_points[i].first == headX && snake->snake_points[i].second == headY) {
				return true;
		}
	}

	// Otherwise return false
	return false;
}

void GameManager::print_game_over()
{
	std::string message = "GAME OVER!!! Press any button to exit!";
	wclear(this->game_field);
	box(this->game_field, 0, 0);
	mvwprintw(this->game_field, this->game_field->_maxy / 2, (this->game_field->_maxx - message.length())/2, message.c_str());
	wrefresh(this->game_field);
	// Enable blocking to hold on game over screan
	timeout(-1);
}
