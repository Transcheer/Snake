#pragma once
#include<graphics.h>
#include<deque>
#include"timer.h"

class Food;

class Snake
{
private:
	std::deque<POINT> snake_body;//蛇的身体
	POINT snake_head;//蛇的头位置

	int snake_color = RED;//蛇的颜色，默认RED；

	bool snake_alive = true;//蛇的存活状态，默认蛇活着

	float snake_speed = 5; // 蛇移动的速度 grid/s

public:
	Snake() = default;
	~Snake() = default;

	enum Direction
	{
		Up,Down,Left,Right
	};

	//改变蛇的颜色
	void changeSnakeColor(int color)//RGB(x,y,z)
	{
		this->snake_color = color;
	}

	//蛇的身体变长+1
	void snakeAddlength()
	{

	}

	//蛇移动
	void snakeMove()
	{

	}

	//数据更新
	void on_update(int delta)
	{

	}

	//绘制蛇
	void on_draw()
	{

	}

	//处理输入
	void on_input(ExMessage& msg)
	{

	}

	//判断是否撞到墙
	bool isCollisionWall()
	{

	}

	//判断是否撞到蛇
	bool isCollosionSnake(const Snake* snake)
	{

	}
	
	//判断是否撞到食物
	bool isCollisionFood(const Food* food)
	{

	}
	
	//判断是否撞到障碍物
	bool isCollisionObstacle()
	{

	}
	
	//判断蛇是否死亡
	bool isSnakeDead()
	{

	}

	//蛇进入死亡死亡状态
	void snakeInDead()
	{

	}
	
};