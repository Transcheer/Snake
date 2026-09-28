//头文件
#include<graphics.h>
#include"game_single_scene.h"
#include"timer.h"
#include<iostream>

//全局变量
const int WIN_WIDTH = 840; // 窗口宽度  单位像素
const int WIN_HEIGHT = 840; // 窗口高度  单位像素
const int GRID = 20; //一个格子的大小  单位像素
const int WIN_WIDTH_BOARD = WIN_WIDTH / GRID; //窗口宽度  单位格子
const int WIN_HEIGHT_BOARD = WIN_HEIGHT / GRID; // 窗口高度  单位格子

Scene* game_single_scene = nullptr;
Snake * snake = nullptr;
Food* food = nullptr;

int main()
{
	game_single_scene = new GameSingleScene();
	snake = new Snake(POINT(WIN_HEIGHT_BOARD / 2, WIN_WIDTH_BOARD / 4), RED, 15);
	food = new Food();

	game_single_scene->on_enter();

	ExMessage msg;

	int FPS = 60;

	BeginBatchDraw();
	while (1)
	{
		DWORD frame_start_time = GetTickCount();
		while (peekmessage(&msg))
		{
			//输入处理
			game_single_scene->on_input(msg);
		}
		//逻辑处理
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		//逻辑更新
		game_single_scene->on_update(delta_tick);
		
		last_tick_time = current_tick_time;


		cleardevice();
		//画面处理
		game_single_scene->on_draw();
		FlushBatchDraw();

		//控制帧率
		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
		{
			Sleep(1000 / FPS - frame_delta_time);
		}

	}
	EndBatchDraw();
	closegraph();

	return 0;
}