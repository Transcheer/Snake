#pragma once
#include"scene.h"
#include"snake.h"
#include"item.h"
#include"common.h"

//extern const int WIN_WIDTH; // 窗口宽度  单位像素
//extern const int WIN_HEIGHT; // 窗口高度  单位像素
//extern const int GRID; //一个格子的大小  单位像素
//extern const int WIN_WIDTH_BOARD; //窗口宽度  单位格子
//extern const int WIN_HEIGHT_BOARD; // 窗口高度  单位格子
//extern Snake* snake1;
//extern Snake* snake2;
//extern Item* food;


class GameSingleScene:public Scene
{
private:
	

public:

	GameSingleScene();
	~GameSingleScene();

	virtual void on_enter(); //进入场景时初始化

	virtual void on_update(int delta); //数据更新

	virtual void on_draw();  //绘图

	virtual void on_input(ExMessage& msg);  //处理输入

	virtual void on_exit();  // 退出场景时卸载

};