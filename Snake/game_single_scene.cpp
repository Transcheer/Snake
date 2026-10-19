#pragma once
#include"item.h"
#include"snake.h"
#include"scene.h"
#include"game_single_scene.h"
#include<iostream>

extern const int WIN_WIDTH; // 窗口宽度  单位像素
extern const int WIN_HEIGHT; // 窗口高度  单位像素
extern const int GRID; //一个格子的大小  单位像素
extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子
extern Snake* snake1;
extern Snake* snake2;
extern Item* food;


GameSingleScene::GameSingleScene() = default;
GameSingleScene::~GameSingleScene() = default;

void GameSingleScene::on_enter()  //进入场景时初始化
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkcolor(RGB(137, 207, 240));
	setlinecolor(WHITE - 100);
	food = new Item(Item::Food, 5, RGB(144, 238, 144));
	snake1 = new Snake(POINT(WIN_HEIGHT_BOARD / 2, WIN_WIDTH_BOARD / 4), RED, 10);

}

void GameSingleScene::on_update(int delta)  //数据更新
{
	//std::cout << "snake1->isCollisionObstacle(): " << snake1->isCollisionObstacle() << "\n";
	//std::cout << "snake1->isCollisionWall(): " << snake1->isCollisionWall() << "\n";
	//std::cout << "snake1->isCollosionSnake(): " << snake1->isCollosionSnake() << "\n";
	//std::cout << "snake1->isShouldSnakeDead(): " << snake1->isShouldSnakeDead() << "\n";
	//std::cout << "snake1->isSnakeAlive(): " << snake1->isSnakeAlive() << "\n";
	snake1->on_update(delta);
	food->on_update(delta);
}

void GameSingleScene::on_draw()  //绘图
{


	//绘制网格
	//从下往上绘制
	//先横线在竖线
	for (int i = WIN_HEIGHT_BOARD; i >= 0; i--)
	{
		line(0, i * GRID, WIN_HEIGHT, i * GRID);
	}
	for (int i = 0; i <= WIN_WIDTH_BOARD; i++)
	{
		line(i * GRID, WIN_HEIGHT, i * GRID, WIN_HEIGHT - WIN_HEIGHT_BOARD * i);
	}

	//for (int i = 0; i <= WIN_WIDTH_BOARD; i++)
	//{
	//	line(i * GRID, 0, i * GRID, WIN_HEIGHT);
	//}
	//for (int i = 0; i <= WIN_HEIGHT_BOARD; i++)
	//{
	//	line(0, i * GRID, WIN_WIDTH, i * GRID);
	//}
	snake1->on_draw();
	food->on_draw();
}

void GameSingleScene::on_input(ExMessage& msg)  //处理输入
{
	snake1->on_input(msg);
}

void GameSingleScene::on_exit()  // 退出场景时卸载
{

}
