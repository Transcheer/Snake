#pragma once
#include"food.h"
#include"snake.h"
#include"scene.h"

extern const int WIN_WIDTH; // 窗口宽度  单位像素
extern const int WIN_HEIGHT; // 窗口高度  单位像素
extern const int GRID; //一个格子的大小  单位像素
extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子
extern Snake *snake;
extern Food *food;

class GameSingleScene:public Scene
{
private:
	

public:

	virtual void on_enter()  //进入场景时初始化
	{
		initgraph(WIN_HEIGHT, WIN_WIDTH);
		setbkcolor(RGB(137, 207, 240));
		setlinecolor(WHITE-100);

		

	}

	virtual void on_update(int delta)  //数据更新
	{
		snake->on_update(delta);
	}

	virtual void on_draw()  //绘图
	{
		

		//绘制网格
		for (int i = 0; i <= WIN_WIDTH_BOARD; i++)
		{
			line(i * GRID, 0, i * GRID, WIN_HEIGHT);
		}
		for (int i = 0; i <= WIN_HEIGHT_BOARD; i++)
		{
			line(0, i * GRID, WIN_WIDTH, i * GRID);
		}
		snake->on_draw();
	}

	virtual void on_input(ExMessage &msg)  //处理输入
	{
		snake->on_input(msg);
	}

	virtual void on_exit()  // 退出场景时卸载
	{

	}

};