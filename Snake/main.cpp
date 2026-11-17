//头文件
#include<graphics.h>
#include"game_single_scene.h"
#include"snake.h"
#include"item.h"
#include"scene.h"
#include"menu_scene.h"
#include"exit_scene.h"
#include"scene_manage.h"
#include"timer.h"
#include<iostream>
#include<vector>
#include"common.h"

//全局变量
//const int WIN_HEIGHT_STATUS = 150; //窗口上方的状态栏的高度   单位像素
//const int GRID = 20; //一个格子的大小  单位像素
//const int WIN_WIDTH_BOARD = 30; //窗口宽度  单位格子
//const int WIN_HEIGHT_BOARD = 30; // 窗口高度  单位格子
//const int WIN_WIDTH = WIN_WIDTH_BOARD * GRID; // 窗口宽度  单位像素
//const int WIN_HEIGHT = WIN_HEIGHT_BOARD * GRID + WIN_HEIGHT_STATUS; // 窗口高度  单位像素


//Scene* global_game_single_scene = nullptr;
std::vector<Snake*> global_snake_list;

Snake* snake1 = nullptr;
Snake* snake2 = nullptr;
Item* food = nullptr;

Scene* game_double_scene = nullptr;
Scene* game_single_scene = nullptr;
Scene* finish_scene = nullptr;
Scene* menu_scene = nullptr;
Scene* exit_scene = nullptr;

SceneManage scene_manage;
bool is_game_running = true;
int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	//global_game_single_scene = new GameSingleScene();
	menu_scene = new MenuScene(_T("resource/background.png"));
	exit_scene = new ExitScene(_T("resource/background.png"));
	game_single_scene = new GameSingleScene();
	game_double_scene = new GameDoubleScene();
	//global_game_single_scene->on_enter();

	scene_manage.set_current_scene(menu_scene);

	ExMessage msg;

	int FPS = 60;

	BeginBatchDraw();
	while (is_game_running)
	{
		DWORD frame_start_time = GetTickCount();
		while (peekmessage(&msg))
		{
			//输入处理
			scene_manage.on_input(msg);
			//global_game_single_scene->on_input(msg);
		}
		//逻辑处理
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		//逻辑更新
		scene_manage.on_update(delta_tick);
		//global_game_single_scene->on_update(delta_tick);
		
		last_tick_time = current_tick_time;


		cleardevice();
		//画面处理
		scene_manage.on_draw();
		//global_game_single_scene->on_draw();
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