#pragma once
#include"item.h"
#include"snake.h"
#include"scene.h"
#include"game_single_scene.h"
#include"common.h"
#include<iostream>

//extern const int WIN_HEIGHT_STATUS;   //窗口上方的状态栏的高度   单位像素
//extern const int GRID; //一个格子的大小  单位像素
//extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
//extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子
//extern const int WIN_WIDTH; // 窗口宽度  单位像素
//extern const int WIN_HEIGHT; // 窗口高度  单位像素
extern std::vector<Snake*> global_snake_list;
//extern Snake* snake1;
//extern Snake* snake2;
extern Item* food;


GameSingleScene::GameSingleScene() = default;
GameSingleScene::~GameSingleScene() = default;

void GameSingleScene::on_enter()  //进入场景时初始化
{
	//initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkcolor(RGB(137, 207, 240));
	setlinecolor(WHITE - 100);

	global_snake_list.push_back(new Snake(POINT(WIN_HEIGHT_BOARD / 2, WIN_WIDTH_BOARD / 4), RED, 4));
	food = new Item(Item::Food, 5, RGB(144, 238, 144));
	//snake1 = new Snake(POINT(WIN_HEIGHT_BOARD / 2, WIN_WIDTH_BOARD / 4), RED, 4);
	//for (auto snake : global_snake_list)
	//{
	//	std::cout << (unsigned)snake << "\n";
	//}
	////std::cout << (unsigned)global_snake_list.back() << "\n";
	//while (1);

}

void GameSingleScene::on_update(int delta)  //数据更新
{
	//std::cout << "snake1->isCollisionObstacle(): " << snake1->isCollisionObstacle() << "\n";
	//std::cout << "snake1->isCollisionWall(): " << snake1->isCollisionWall() << "\n";
	//std::cout << "snake1->isCollosionSnake(): " << snake1->isCollosionSnake() << "\n";
	//std::cout << "snake1->isShouldSnakeDead(): " << snake1->isShouldSnakeDead() << "\n";
	//std::cout << "snake1->isSnakeAlive(): " << snake1->isSnakeAlive() << "\n";
	global_snake_list.front()->on_update(delta);
	//snake1->on_update(delta);
	food->on_update(delta);
}

void GameSingleScene::on_draw()  //绘图
{


	//绘制网格
	//从下往上绘制
	//先横线在竖线
	//留出上方状态栏
	for (int i = WIN_HEIGHT_BOARD; i >= 0; i--)
	{
		line(0, i * GRID + WIN_HEIGHT_STATUS, WIN_WIDTH, i * GRID + WIN_HEIGHT_STATUS);
	}
	for (int i = 0; i <= WIN_WIDTH_BOARD; i++)
	{
		line(i * GRID, WIN_HEIGHT_STATUS, i * GRID, WIN_HEIGHT);
	}

	//for (int i = 0; i <= WIN_WIDTH_BOARD; i++)
	//{
	//	line(i * GRID, 0, i * GRID, WIN_HEIGHT);
	//}
	//for (int i = 0; i <= WIN_HEIGHT_BOARD; i++)
	//{
	//	line(0, i * GRID, WIN_WIDTH, i * GRID);
	//}
	global_snake_list.front()->on_draw();
	//snake1->on_draw();
	food->on_draw();

	//绘制蛇的分数

	static TCHAR str[64];
	_stprintf_s(str, _T("Score:%d"), global_snake_list.front()->getSnakeLenth());
	settextcolor(LIGHTBLUE);
	outtextxy(0, 0, str);
}

void GameSingleScene::on_input(ExMessage& msg)  //处理输入
{
	global_snake_list.front()->on_input(msg);
	//snake1->on_input(msg);
}

void GameSingleScene::on_exit()  // 退出场景时卸载
{
	//delete(snake1);
	delete(food);
	for (auto snake : global_snake_list)
	{
		delete snake;
	}
	global_snake_list.clear();
	if (food != nullptr)
		delete food;
	food = nullptr;
}
