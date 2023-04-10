#include "game.h"

// Cunstruct GameManager
GameManager::GameManager(WINDOW *game_field_window, WINDOW *score_field_window, Snake *snake_istance)
{
	this->game_field = game_field_window;
	this->score_window = score_field_window;
	this->snake = snake_istance;
}

// Check game over conditions
// 1. Collizion with border
// 2. Collizion with body of the snake
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

// Print Game Over screan.
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

// Method for a fruit printing
void GameManager::print_fruit()
{
	mvwprintw(this->game_field, this->fruit.second, this->fruit.first, "F");
}

// Method for the snake printing
void GameManager::print_snake()
{
	for(auto &point : snake->snake_points)
	{
		if(point == snake->snake_points.back()) {
			mvwprintw(game_field, point.second, point.first, "@");
		}
		else {
			mvwprintw(game_field, point.second, point.first, "S");
		}
	}
}

// Print frame of the game field window
void GameManager::print_game_frame()
{
	wclear(this->game_field);
	box(this->game_field, 0, 0);
	this->print_snake();
	this->print_fruit();
	wrefresh(this->game_field);
}

void GameManager::update_fruit_position()
{
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
	int maxX = game_field->_maxx;
	int maxY = game_field->_maxy;
	std::uniform_int_distribution<int> uintX(1, maxX - 1);
	std::uniform_int_distribution<int> uintY(1, maxY - 1);
	while(true) {
		fruit.first = uintX(gen);
		fruit.second = uintY(gen);
		for(auto &point : snake->snake_points) {
			if(point.first == fruit.first && point.second == fruit.second)
				break;
			return;
		}
	}
}

bool GameManager::check_fruit_condition()
{
	int headX = this->snake->snake_points.back().first;
	int headY = this->snake->snake_points.back().second;
	if(fruit.first == headX && fruit.second == headY)
		return true;
	return false;
}

// Game main loop
void GameManager::run_game()
{
	// Variable to store pressed keys
	int ch;
	// Suppress the automatic echoing of typed characters.
	noecho();
	// Without linebreack.
	cbreak();
	// Invisible cursor
	curs_set(0);
	this->update_fruit_position();
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
				return;
			default:
				break;
		}
		if(this->check_game_over())
			break;
		if(this->check_fruit_condition()) {
			this->update_fruit_position();
			this->snake->grow();
		}
		snake->snake_update();
		this->print_game_frame();
	}

	this->print_game_over();
}
