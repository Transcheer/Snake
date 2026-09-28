#pragma once
#include<graphics.h>
#include<vector>
#include<Ctime>
#include<random>
#include"snake.h"
#include"timer.h"

class Snake;
extern Snake* snake1;
extern Snake* snake2;

extern const int WIN_WIDTH; // 窗口宽度  单位像素
extern const int WIN_HEIGHT; // 窗口高度  单位像素
extern const int GRID; //一个格子的大小  单位像素
extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子

//!!!!食物的生成不能在边界上

class Item
{
private:
	std::vector<POINT> item_position_list;//食物的位置
	int item_max_count = 5;//食物的最大数量

	int item_color = GREEN;//食物颜色

	enum ItemType;
	ItemType item_type; // 物品类型，构造函数内赋值

	Timer item_create_timer; // 物品生成时间计时器

public:
	Item(ItemType item,int max_counte, int color)
	{
		//给物品类型复制
		this->item_type = item;

		//给物品最大数量赋值
		this->item_max_count = max_counte;
		
		//初始化物品生成计时器
		item_create_timer.set_callback([&]() {
			this->createItem();
			});
		item_create_timer.set_one_shot(false);
		switch (item)
		{
		case Food:
			item_create_timer.set_wait_time(5000);
			break;
		case Obstacle:
			item_create_timer.set_wait_time(10000);
		}

		//给物品颜色赋值
		this->item_color = color;

	}
	Item()
	{
		item_type = Food;

		item_create_timer.set_callback([&]() {
			this->createItem();
			});
		item_create_timer.set_one_shot(false);
		item_create_timer.set_wait_time(5000);
	}
	~Item() = default;

	//物品类型
	enum ItemType
	{
		Food,
		Obstacle
	};

	//随机生成食物
	void createItem()
	{
		std::default_random_engine e(time(0)); // 使用当前时间作为种子
		std::uniform_int_distribution<int> x(2, WIN_WIDTH_BOARD-2); // 定义一个2到20之间的均匀分布
		std::uniform_int_distribution<int> y(2, WIN_HEIGHT_BOARD-2); // 定义一个2到20之间的均匀分布
		
		POINT pos = POINT(x(e), y(e));
		if (canCreateItem(snake1, pos))
		{
			if (this->getItemCount() < this->item_max_count)
			{
				item_position_list.push_back(pos);
			}
		}

	}

	//食物的更新
	void on_update(int delta)
	{
		this->item_create_timer.on_update(delta);
	}

	//食物的绘制
	void on_draw()
	{
		setfillcolor(item_color);

		for (POINT point : item_position_list)
		{
			solidroundrect(point.x * GRID, point.y * GRID, (point.x + 1) * GRID, (point.y + 1) * GRID, GRID * 0.4, GRID * 0.4);
		}
	}

	//移除index位置上的食物
	void deleteItem(int index)
	{
		if (index > -1 && index < this->getItemCount())
			this->item_position_list.erase(this->item_position_list.begin() + index);
	}

	//更改食物颜色
	void resetItemColor(int color)
	{
		this->item_color = color;
	}

	//返回食物被吃的索引
	int getBeCollisionItemIndex(Snake* snake)
	{
		POINT snake_head_pos = snake->getSnakeHeadPosition(); 
		for (int i = 0; i < this->getItemCount(); i++)
		{
			POINT item_pos = this->getItemIndexPosition(i);
			if (snake_head_pos.x == item_pos.x && snake_head_pos.y == item_pos.y)
			{
				return i;
			}
		}
		return -1;
	}

	//判断当前位置能不能生成食物
	bool canCreateItem(Snake* snake, POINT pos)
	{
		POINT item_pos;
		//有蛇的地方不行
		for (int i = 0; i < snake->getSnakeLenth(); i++)
		{
			item_pos = snake->getSnakeIndexBodyPosition(i);
			if (pos.x == item_pos.x && pos.y == item_pos.y)
			{
				return false;
			}
		}
		//本来就有东西的地方也不行
		for (int i = 0; i < this->getItemCount(); i++)
		{
			item_pos = this->getItemIndexPosition(i);
			if (pos.x == item_pos.x && pos.y == item_pos.y)
			{
				return false;
			}
		}
	}
	bool canCreateItem(Snake* snake, POINT pos, Item* other_item)
	{
		POINT item_pos;
		//有蛇的地方不行
		for (int i = 0; i < snake->getSnakeLenth(); i++)
		{
			item_pos = snake->getSnakeIndexBodyPosition(i);
			if (pos.x == item_pos.x && pos.y == item_pos.y)
			{
				return false;
			}
		}
		//本来就有东西的地方也不行
		for (int i = 0; i < other_item->getItemCount(); i++)
		{
			item_pos = other_item->getItemIndexPosition(i);
			if (pos.x == item_pos.x && pos.y == item_pos.y)
			{
				return false;
			}
		}
		for (int i = 0; i < this->getItemCount(); i++)
		{
			item_pos = this->getItemIndexPosition(i);
			if (pos.x == item_pos.x && pos.y == item_pos.y)
			{
				return false;
			}
		}
	}

	//获取食物的总数
	int getItemCount()
	{
		return item_position_list.size();
	}

	POINT getItemIndexPosition(int index)
	{
		if (index > -1 && index < this->getItemCount())
			return item_position_list[index];
		return POINT(-1, -1);
	}

};