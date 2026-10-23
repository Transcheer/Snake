#pragma once
#include<graphics.h>
#include<deque>
#include"timer.h"
#include"common.h"

class Item;
extern Item* food;
//extern const int WIN_WIDTH; // 窗口宽度  单位像素
//extern const int WIN_HEIGHT; // 窗口高度  单位像素
//extern const int GRID; //一个格子的大小  单位像素
//extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
//extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子


class Snake
{
private:
	std::deque<POINT> snake_body;//蛇的身体

	int snake_color = RED;//蛇的颜色，默认RED；

	bool is_snake_alive = true;//蛇的存活状态，默认蛇活着
	//bool is_snake_in_dead = false; // 蛇是否处在即将死亡的状态
	//Timer snake_enter_dead_timer; // 蛇死亡计时器

	float snake_speed = 100; // 蛇移动的速度 grid/s
	bool is_snake_accelerate = false;

	float snake_move_timer = 0; // 蛇的移动计时器

	enum Direction;// 先声明一下
	Direction snake_move_current_direction = Up; // 蛇移动方向，在构造函数里采用随机的方式进行赋值
	std::deque<Direction> snake_move_direction_deque; // 方向队列 
	const int snake_move_direction_deque_maxsize = 4;

public:
	Snake(POINT pos, int color, float speed);//蛇的初始位置，蛇的颜色

	Snake(); //蛇的初始位置，蛇的颜色
	~Snake();

	enum Direction
	{
		Up, Down, Left, Right
	};

	//获取蛇头位置
	POINT getSnakeHeadPosition();

	//获取蛇身体的长度
	int getSnakeLenth();

	POINT getSnakeIndexBodyPosition(int index);

	//改变蛇的颜色
	void changeSnakeColor(int color);//RGB(x,y,z)

	//蛇的身体变长+1
	void snakeAddBody();

	void snakeCutBody();

	//蛇移动
	void snakeMove(int delta);

	//数据更新
	virtual void on_update(int delta);

	//绘制蛇
	void on_draw();

	//处理输入
	virtual void on_input(const ExMessage& msg);

	//bool判断是否可以转向
	bool canChangeDirection(Direction next_dir);

	//更新队列
	void updateSnakeMoveDirectionDeque(Direction dir);

	//判断是否撞到墙
	bool isCollisionWall();

	//判断是否撞到其他蛇
	bool isCollosionSnake(Snake* snake);
	//判断是否撞到自己
	bool isCollosionSnake();

	//判断是否撞到食物
	bool isCollisionFood(Item* food);

	//判断是否撞到障碍物
	bool isCollisionObstacle();

	//判断蛇是否应该死亡
	bool isShouldSnakeDead();
	bool isShouldSnakeDead(Snake* snake);

	bool isSnakeAlive();

	//蛇进入死亡死亡状态
	//void snakeEnterDead();

};