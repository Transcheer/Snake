#pragma once
#include<graphics.h>
#include<deque>

class Snake
{
private:
	std::deque<POINT> snake_body;//蛇的身体
	POINT snake_head;//蛇的头位置

	int color = RED;//蛇的颜色，默认RED；

	bool snake_alive = true;//蛇的存活状态，默认蛇活着

public:
	Snake() = default;
	~Snake() = default;

	//蛇的身体变长
	void snakeAddlength();

	//蛇移动
	void snakeMove();

	//数据更新
	void on_update(int delta);

	//绘制蛇
	void on_draw();

	//判断是否撞到墙
	bool isCollisionWall();

	//判断是否撞到蛇
	bool isCollosionSnake();
	
	//判断是否撞到食物
	bool isCollisionFood();
	
	//判断是否撞到障碍物
	bool isCollisionObstacle();
	
	//判断蛇是否死亡
	bool isSnakeDead();

	//蛇进入死亡死亡状态
	void snakeInDead();
	
};