#pragma once
#include"snake.h"

class Snake2P :public Snake
{
public:
	using Snake::Snake;
	void on_input(const ExMessage& msg);
};