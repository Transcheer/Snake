#include"snake.h"
#include"item.h"
#include"common.h"
#include<graphics.h>
#include<deque>
#include"timer.h"
#include<Ctime>
#include<random>
#include<iostream>


class Item;
extern Item* food;
extern std::vector<Snake*> global_snake_list;
//extern std::vector<Snake*> global_snake_list;
//extern const int WIN_HEIGHT_STATUS; //窗口上方的状态栏的高度   单位像素
//extern const int WIN_WIDTH; // 窗口宽度  单位像素
//extern const int WIN_HEIGHT; // 窗口高度  单位像素
//extern const int GRID; //一个格子的大小  单位像素
//extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
//extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子





Snake::Snake(POINT pos, int color, float speed)//蛇的初始位置，蛇的颜色
{
	//初始化蛇的身体
	for (int i = 0; i < 3; i++)
	{
		snake_body.push_back(POINT(pos.x, pos.y - i));
	}


	//初始化蛇的颜色
	snake_color = color;

	//初始化蛇的存活状态
	is_snake_alive = true;

	//初始化蛇的无敌状态
	is_snake_Invincibility = true;

	//初始化蛇的移动速度
	snake_speed = speed;

	//初始化蛇的移动方向
	snake_move_current_direction = Up;

	//初始化蛇无敌时间计时器
	snake_Invincibility_timer.set_callback([&]()
		{
			is_snake_Invincibility = false;
		});
	snake_Invincibility_timer.set_one_shot(false);
	snake_Invincibility_timer.set_wait_time(3000);

	//初始化蛇死亡计时器
	//snake_enter_dead_timer.set_callback([&]() {
	//	//std::cout << "snake_enter_dead_timer trigger!!!\n";
	//	is_snake_in_dead = false;
	//	if (isShouldSnakeDead())
	//	{
	//		is_snake_alive = false;
	//		return;
	//		//std::cout << "snake is " << (is_snake_alive ? "alive" : "dead") << "!!!\n";
	//	}
	//	is_snake_alive = true;
	//	});
	//snake_enter_dead_timer.set_one_shot(false);
	//snake_enter_dead_timer.set_wait_time(400);

}

Snake::Snake()//蛇的初始位置，蛇的颜色
{
	POINT pos = POINT(WIN_HEIGHT_BOARD / 2, WIN_WIDTH_BOARD / 4);
	//初始化蛇的身体
	for (int i = 0; i < 3; i++)
	{
		snake_body.push_back(POINT(pos.x, pos.y - i));
	}


	//初始化蛇的颜色
	snake_color = RED;

	//初始化蛇的存活状态
	is_snake_alive = true;

	//初始化蛇的移动速度
	snake_speed = 8;

	//初始化蛇的移动方向
	snake_move_current_direction = Up;

	//初始化蛇无敌时间计时器
	snake_Invincibility_timer.set_callback([&]()
		{
			is_snake_Invincibility = false;
		});
	snake_Invincibility_timer.set_one_shot(false);
	snake_Invincibility_timer.set_wait_time(3000);

	//初始化蛇死亡计时器
	//snake_enter_dead_timer.set_callback([&]() {
	//	//std::cout << "snake_enter_dead_timer trigger!!!\n";
	//	is_snake_in_dead = false;
	//	if (isShouldSnakeDead())
	//	{
	//		is_snake_alive = false;
	//		return;
	//		//std::cout << "snake is " << (is_snake_alive ? "alive" : "dead") << "!!!\n";
	//	}
	//	is_snake_alive = true;		
	//	});
	//snake_enter_dead_timer.set_one_shot(false);
	//snake_enter_dead_timer.set_wait_time(400);

}
Snake::~Snake() = default;


//获取蛇头位置
POINT Snake::getSnakeHeadPosition()
{
	return this->snake_body[0];
}

//获取蛇身体的长度
int Snake::getSnakeLenth()
{
	return snake_body.size();
}

POINT Snake::getSnakeIndexBodyPosition(int index)
{
	return snake_body[index];
}

//改变蛇的颜色
void Snake::changeSnakeColor(int color)//RGB(x,y,z)
{
	this->snake_color = color;
}

//蛇的身体变长+1
void Snake::snakeAddBody()
{
	POINT head = getSnakeHeadPosition();

	if (!snake_move_direction_deque.empty())
	{
		snake_move_current_direction = snake_move_direction_deque.front();
		snake_move_direction_deque.pop_front();
	}

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

void Snake::snakeCutBody()
{
	snake_body.pop_back();
}

//蛇移动
void Snake::snakeMove(int delta)
{
	snake_move_timer += delta;

	if (is_snake_accelerate)
	{
		if (snake_move_timer >= 1 / (snake_speed * 2.5 / 1000))
		{

			snakeAddBody();
			snakeCutBody();
			snake_move_timer = 0;
		}
	}
	else
	{
		if (snake_move_timer >= 1.0 / (snake_speed / 1000))
		{

			snakeAddBody();
			snakeCutBody();
			snake_move_timer = 0;
		}
	}

}

//数据更新
void Snake::on_update(int delta)
{
	//float current_speed = is_snake_accelerate ? snake_speed * 2.5f : snake_speed;
	//float move_interval = 1000.0f / current_speed;

	//// 只在速度变化时输出
	//static float last_interval = 0;
	//if (abs(move_interval - last_interval) > 1.0f)
	//{
	//	std::cout << "Speed: " << current_speed
	//		<< ", Interval: " << move_interval << "ms\n";
	//	last_interval = move_interval;
	//}


	//if (isShouldSnakeDead())
	//{

	//	std::cout << "丸蛋惹，要死了喵！	current time: " << GetTickCount() << "\n";
	//}

	//snake_enter_dead_timer.on_update(delta);
	snake_Invincibility_timer.on_update(delta);

	if (!is_snake_Invincibility)
		//if (!is_snake_in_dead)
	{
		//死亡碰撞检测
		if (isShouldSnakeDead(global_snake_list))
		{
			//snakeEnterDead();
			is_snake_alive = false;
		}

	}

	if (is_snake_alive)
	{
		//吃食物碰撞检测
		if (isCollisionFood(food))
		{
			int beColliFood = food->getBeCollisionItemIndex(this);
			food->deleteItem(beColliFood);
			snakeAddBody();
		}
		//移动
		snakeMove(delta);
	}


	static int pass_time = 0;
	pass_time += delta;
	if (pass_time >= 500)
	{
		std::cout << "sanke is " << (is_snake_alive ? "alive" : "dead") << "!!!\n";
		pass_time = 0;
	}

}

//绘制蛇
void Snake::on_draw()
{
	//if (is_snake_alive)
	{
		setfillcolor(snake_color + 50);

		POINT head = getSnakeHeadPosition();

		for (POINT point : snake_body)
		{
			solidroundrect(point.x * GRID, point.y * GRID + WIN_HEIGHT_STATUS, (point.x + 1) * GRID, (point.y + 1) * GRID + WIN_HEIGHT_STATUS, GRID * 0.4, GRID * 0.4);
		}
		setfillcolor(snake_color);
		solidroundrect(head.x * GRID, head.y * GRID + WIN_HEIGHT_STATUS, (head.x + 1) * GRID, (head.y + 1) * GRID + WIN_HEIGHT_STATUS, GRID * 0.4, GRID * 0.4);
	}

}

//处理输入
void Snake::on_input(const ExMessage& msg)
{
	Direction last_dir = snake_move_current_direction;
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case 0x41://'A'
			last_dir = Left;
			break;

		case 0x44://'D'
			last_dir = Right;
			break;

		case 0x57://'W'
			last_dir = Up;
			break;

		case 0x53://'S' 
			last_dir = Down;
			break;

		case 0x4A://'J'
			is_snake_accelerate = true;
			break;
		default:

			break;
		}
		if (canChangeDirection(last_dir))
		{
			updateSnakeMoveDirectionDeque(last_dir);
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		if (msg.vkcode == 0x4A)
		{
			is_snake_accelerate = false;
		}
	}

}

//bool判断是否可以转向
bool Snake::canChangeDirection(Direction next_dir)
{
	if (snake_move_direction_deque.empty())
	{
		switch (snake_move_current_direction)
		{
		case Up:
			return next_dir != Down;
		case Down:
			return next_dir != Up;
		case Left:
			return next_dir != Right;
		case Right:
			return next_dir != Left;
		}
	}
	else
	{
		switch (snake_move_direction_deque.back())
		{
		case Up:
			return next_dir != Down;
		case Down:
			return next_dir != Up;
		case Left:
			return next_dir != Right;
		case Right:
			return next_dir != Left;
		}
	}
	return true;
}

//更新方向队列
void Snake::updateSnakeMoveDirectionDeque(Direction dir)
{
	snake_move_direction_deque.push_back(dir);
	if (snake_move_direction_deque.size() >= snake_move_direction_deque_maxsize)
	{
		snake_move_direction_deque.pop_front();
	}
}

//判断是否撞到墙
bool Snake::isCollisionWall()
{
	POINT head = getSnakeHeadPosition();
	if (head.x <= 0 || head.x >= WIN_WIDTH_BOARD - 1 || head.y <= 0 || head.y >= WIN_HEIGHT_BOARD - 1)
	{
		return true;
	}
	return false;
}

//判断是否撞到蛇
bool Snake::isCollosionSnake(std::vector<Snake*> snake_list)
{
	POINT thishead = this->getSnakeHeadPosition();
	for (int i = 1; i < this->getSnakeLenth(); i++)
	{
		if (this->getSnakeIndexBodyPosition(i).x == thishead.x && this->getSnakeIndexBodyPosition(i).y == thishead.y)
		{
			return true;
		}
	}
	for (auto snake : snake_list)
	{
		if (snake != this)
		{
			for (int i = 0; i < snake->getSnakeLenth(); i++)
			{
				if (thishead.x == snake->getSnakeIndexBodyPosition(i).x && thishead.y == snake->getSnakeIndexBodyPosition(i).y)
				{
					return true;
				}
			}
		}

	}

	return false;
}
////判断是否撞到自己
//bool Snake::isCollosionSnake()
//{
//	POINT head = getSnakeHeadPosition();
//	for (int i = 1; i < this->getSnakeLenth(); i++)
//	{
//		if (this->getSnakeIndexBodyPosition(i).x == head.x && this->getSnakeIndexBodyPosition(i).y == head.y)
//		{
//			return true;
//		}
//	}
//	return false;
//}

//判断是否撞到食物
bool Snake::isCollisionFood(Item* food)
{
	POINT food_pos;
	POINT snakehead = this->getSnakeHeadPosition();
	for (int i = 0; i < food->getItemCount(); i++)
	{
		food_pos = food->getItemIndexPosition(i);

		if (food_pos.x == snakehead.x && food_pos.y == snakehead.y)
		{
			return true;
		}

	}
	return false;
}


//判断是否撞到障碍物
bool Snake::isCollisionObstacle()
{
	return false;
}

//判断蛇是否应该死亡
//bool Snake::isShouldSnakeDead()
//{
//	return (isCollisionWall() || isCollosionSnake() || isCollisionObstacle());
//}
bool Snake::isShouldSnakeDead(std::vector<Snake*> snake_list)
{
	//return false;
	//return isCollisionWall();
	//return isCollisionObstacle();
	//return isCollosionSnake(snake_list);
	return (isCollisionWall() || isCollisionObstacle() || isCollosionSnake(snake_list));
}

//蛇是否已经死亡
bool Snake::isSnakeAlive()
{
	return is_snake_alive;
}

//蛇进入死亡死亡状态
//void Snake::snakeEnterDead()
//{
//	snake_enter_dead_timer.resart();
//	is_snake_in_dead = true;
//}
