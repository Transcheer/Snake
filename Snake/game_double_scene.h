#pragma once
#include"item.h"
#include"snake.h"
#include"scene.h"

class GameDoubleScene :public Scene
{
private:

public:
	GameDoubleScene() = default;
	~GameDoubleScene() = default;
	GameDoubleScene(const GameDoubleScene&) = delete;
	GameDoubleScene& operator=(const GameDoubleScene&) = delete;

	void on_enter(); //进入场景时初始化
	void on_update(int delta); //数据更新
	void on_draw(); //绘图
	void on_input(ExMessage& msg); //处理输入
	void on_exit(); // 退出场景时卸载
};