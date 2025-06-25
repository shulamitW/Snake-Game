// Snake_Runner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h> 
#include <windows.h>  
#include <conio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../Snake_Lib/snake.h"

int main()
{
	snake_t snake = create_snake(5, 5);		
	size_t snake_size = 1;
	uint8_t food[] = { 10,10 };				
	direction_t current_direction = RIGHT;
	bool is_game_time = true;
	draw_borders();
	int snake_file_num = 0;
	int score = 0;
	while (is_game_time)
	{
		draw_snake(snake, snake_size);
		draw_food(food);
		Sleep(150);
		erase_snake_tail(snake, snake_size);

		if (_kbhit()) {
			int key = _getch();
			int requested_direction = INVALID_DIRECTION;

			switch (key)
			{
			case 72: requested_direction = UP; break;
			case 80: requested_direction = DOWN; break;
			case 75: requested_direction = LEFT; break;
			case 77: requested_direction = RIGHT; break;
			case 'q': is_game_time = false; break;
			}
			if (requested_direction != INVALID_DIRECTION)
			{
				if (can_snake_move_in_direction(current_direction, requested_direction))
					current_direction = requested_direction;
			}
		}
		if (will_snake_collide_border_on_next_move(snake, snake_size, current_direction))
		{
			is_game_time = false;
			printf("Game Over!! snake bumped into border, Your score is %d", score);
			continue;
		}
		if (will_snake_collide_with_itself_on_next_move(snake, snake_size, current_direction))
		{
			is_game_time = false;
			printf("Game Over!! snake bumped into itself, Your score is %d", score);
			continue;
		}
		bool should_grow = will_snake_reach_food_on_next_move(snake, snake_size, food, current_direction);
		if (should_grow)
		{
			snake_size = grow_snake(&snake, snake_size, current_direction);
			set_new_food_location(snake, snake_size, food);
			score += 10;
		}
		else
		{
			move_snake(snake, snake_size, current_direction);
		}
	}
	free_snake(snake, snake_size);
}