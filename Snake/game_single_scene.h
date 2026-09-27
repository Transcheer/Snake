#pragma once
#include"food.h"
#include"snake.h"
#include"scene.h"

extern Snake *snake;
extern Food *food;

class GameSingleScene:public Scene
{
private:
	

public:

	virtual void on_enter()  //进入场景时初始化
	{

	}

	virtual void on_update(int delta)  //数据更新
	{
		snake->on_update(delta);
	}

	virtual void on_draw()  //绘图
	{
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