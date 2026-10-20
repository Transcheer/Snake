#pragma once
#include"snake.h"
#include"timer.h"
#include"common.h"

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
	Item(ItemType item, int max_counte, int color);
	Item();
	~Item();

	//物品类型
	enum ItemType
	{
		Food,
		Obstacle
	};

	//随机生成食物
	void createItem();

	//食物的更新
	void on_update(int delta);

	//食物的绘制
	void on_draw();

	//移除index位置上的食物
	void deleteItem(int index);

	//更改食物颜色
	void resetItemColor(int color);

	//返回食物被吃的索引
	int getBeCollisionItemIndex(Snake* snake);

	//判断当前位置能不能生成食物
	bool canCreateItem(Snake* snake, POINT pos);
	bool canCreateItem(Snake* snake, POINT pos, Item* other_item);

	//获取食物的总数
	int getItemCount();

	POINT getItemIndexPosition(int index);

};