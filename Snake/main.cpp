//头文件
#include<graphics.h>
#include"snake.h"
#include"food.h"
#include"timer.h"
#include<iostream>

//全局变量


int main()
{
	initgraph(680, 680);

	ExMessage msg;

	int FPS = 60;

	

	BeginBatchDraw();
	while (1)
	{
		DWORD frame_start_time = GetTickCount();
		while (peekmessage(&msg))
		{
			//输入处理

		}
		//逻辑处理
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		//逻辑更新
		
		
		last_tick_time = current_tick_time;


		cleardevice();
		//画面处理
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