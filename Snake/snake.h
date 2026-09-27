#pragma once
#include<graphics.h>
#include<deque>
#include"timer.h"
#include<Ctime>
#include<random>

class Food;

extern const int WIN_WIDTH; // 窗口宽度  单位像素
extern const int WIN_HEIGHT; // 窗口高度  单位像素
extern const int GRID; //一个格子的大小  单位像素
extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子

extern Food *food;

class Snake
{
private:
	std::deque<POINT> snake_body;//蛇的身体

	int snake_color = RED;//蛇的颜色，默认RED；

	bool is_snake_alive = true;//蛇的存活状态，默认蛇活着
	bool is_snake_in_dead = false; // 蛇是否处在即将死亡的状态
	Timer snake_enter_dead_timer; // 蛇死亡计时器

	float snake_speed = 5; // 蛇移动的速度 grid/s
	bool is_snake_accelerate = false;

	int snake_move_timer = 0; // 蛇的移动计时器

	enum Direction;// 先声明一下
	Direction snake_move_current_direction = Up; // 蛇移动方向，在构造函数里采用随机的方式进行赋值
	std::deque<Direction> snake_move_direction_deque{ Invalid,Invalid,Invalid,Invalid }; // 方向队列 

public:
	Snake(POINT pos, int color)//蛇的初始位置，蛇的颜色
	{
		//初始化蛇的身体
		for (int i = 0; i < 3; i++)
		{
			snake_body.push_back(POINT(pos.x + i, pos.y));
		}
		

		//初始化蛇的颜色
		snake_color = color;

		//初始化蛇的存活状态
		is_snake_alive = true;

		//初始化蛇的移动速度
		snake_speed = 5;

		//初始化蛇的移动方向
		snake_move_current_direction = Up;

		//初始化蛇死亡计时器
		snake_enter_dead_timer.set_callback([&]() {
			if (this->isCollisionWall() || this->isCollosionSnake() || this->isCollisionObstacle())
			{
				is_snake_alive = false;
			}
			});
		snake_enter_dead_timer.set_one_shot(true);
		snake_enter_dead_timer.set_wait_time(400);

	}
	~Snake() = default;

	enum Direction
	{
		Up,Down,Left,Right,Invalid
	};

	//获取蛇头位置
	POINT getSnakeHeadPosition()
	{
		return this->snake_body[0];
	}

	//获取蛇身体的长度
	int getSnakeLenth()
	{
		return snake_body.size();
	}

	POINT getSnakeIndexBodyPosition(int index)
	{
		return snake_body[index];
	}

	//改变蛇的颜色
	void changeSnakeColor(int color)//RGB(x,y,z)
	{
		this->snake_color = color;
	}

	//蛇的身体变长+1
	void snakeAddBody()
	{
		POINT head = getSnakeHeadPosition();
		
		if (snake_move_direction_deque[0] != Invalid)
			snake_move_current_direction = snake_move_direction_deque[0];
		
		snake_move_direction_deque.pop_front();

		switch (snake_move_current_direction)
		{
		case Up:
			snake_body.push_front(POINT(head.x, head.y - 1));
			break;

		case Down:
			snake_body.push_front(POINT(head.x, head.y + 1));
			break;

		case Left:
			snake_body.push_front(POINT(head.x - 1, head.y));
			break;

		case Right:
			snake_body.push_front(POINT(head.x + 1, head.y));
			break;

		default:
			break;
		}
	}

	void snakeCutBody()
	{
		snake_body.pop_back();
	}

	//蛇移动
	void snakeMove(int delta)
	{
		snake_move_timer += delta;
		if (snake_move_timer >= 1 / (snake_speed * 1000))
		{
			snake_move_timer = 0;
			snakeAddBody();
			snakeCutBody();
		}
	}

	//数据更新
	virtual void on_update(int delta)
	{
		//移动
		snakeMove(delta);
		
		snake_enter_dead_timer.on_update(delta);

		if (!is_snake_in_dead)
		{
			//死亡碰撞检测
			if (isSnakeDead())
			{
				snakeEnterDead();
			}
			//吃食物碰撞检测
			if (isCollisionFood(food))
			{
				snakeAddBody();
			}
		}				
	}

	//绘制蛇
	void on_draw()
	{
		setfillcolor(snake_color);
		for (POINT point : snake_body)
		{
			fillroundrect(point.x * GRID, point.y * GRID, (point.x + 1) * GRID, (point.y + 1) * GRID, GRID * 0.2, GRID * 0.2);
		}
	}

	//处理输入
	virtual void on_input(const ExMessage& msg)
	{
		Direction pre_dir = Invalid;
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case 0x41://'A'
				pre_dir = Left;
				if (snake_move_direction_deque[snake_move_direction_deque.size() - 1] != Right)
				{
					snake_move_direction_deque.pop_front();
					snake_move_direction_deque.push_back(pre_dir);
				}

				break;

			case 0x44://'D'
				pre_dir = Right;
				if (snake_move_direction_deque[snake_move_direction_deque.size() - 1] != Left)
				{
					snake_move_direction_deque.pop_front();
					snake_move_direction_deque.push_back(pre_dir);
				}
				break;

			case 0x57://'W'
				pre_dir = Up;
				if (snake_move_direction_deque[snake_move_direction_deque.size() - 1] != Down)
				{
					snake_move_direction_deque.pop_front();
					snake_move_direction_deque.push_back(pre_dir);
				}
				break;
			
			case 0x53://'S' 
				pre_dir = Down;
				if (snake_move_direction_deque[snake_move_direction_deque.size() - 1] != Up)
				{
					snake_move_direction_deque.pop_front();
					snake_move_direction_deque.push_back(pre_dir);
				}
				break;

			case 0x4A://'J'
				is_snake_accelerate = true;
				break;
			default:
				break;
			}
		}
	}

	//判断是否撞到墙
	bool isCollisionWall()
	{
		POINT head = getSnakeHeadPosition();
		if (head.x <= 0 || head.x >= WIN_WIDTH_BOARD - 1 || head.y <= 0 || head.y >= WIN_HEIGHT_BOARD - 1)
		{
			return true;
		}
		return false;
	}

	//判断是否撞到其他蛇
	bool isCollosionSnake(Snake* snake)
	{
		for (int i = 0; i < this->getSnakeLenth(); i++)
		{
			for (int j = 0; j < snake->getSnakeLenth(); j++)
			{
				if (this->getSnakeIndexBodyPosition(i).x == snake->getSnakeIndexBodyPosition(j).x && this->getSnakeIndexBodyPosition(i).y == snake->getSnakeIndexBodyPosition(j).y)
				{
					return false;
				}
			}
		}
		return true;
	}
	//判断是否撞到自己
	bool isCollosionSnake()
	{
		POINT head = getSnakeHeadPosition();
		for (int i = 0; i < this->getSnakeLenth(); i++)
		{
			if (this->getSnakeIndexBodyPosition(i).x == head.x && this->getSnakeIndexBodyPosition(i).y == head.y)
			{
				return false;
			}
		}
		return true;
	}
	
	//判断是否撞到食物
	bool isCollisionFood(Food* food)
	{
		POINT food_pos;
		POINT snake_pos;
		for (int i = 0; i < food->getFoodCount(); i++)
		{
			food_pos = food->getFoodIndexPosition(i);
			for (int j = 0; j < this->getSnakeLenth(); j++)
			{
				snake_pos = this->getSnakeIndexBodyPosition(j);
				if (food_pos.x == snake_pos.x && food_pos.y == snake_pos.y)
				{
					return true;
				}
			}
		}
		return false;
	}
	
	//判断是否撞到障碍物
	bool isCollisionObstacle()
	{
		return false;
	}
	
	//判断蛇是否应该死亡
	bool isSnakeDead()
	{
		return isCollisionWall() || isCollosionSnake() || isCollisionObstacle();
	}

	//蛇进入死亡死亡状态
	void snakeEnterDead()
	{
		snake_enter_dead_timer.resart();
	}
	
};