#pragma once
#include<graphics.h>
class Scene
{
public:
	Scene();
	~Scene();

	virtual void on_enter(); //进入场景时初始化
	virtual void on_update(int delta); //数据更新
	virtual void on_draw(); //绘图
	virtual void on_input(ExMessage& msg); //处理输入
	virtual void on_exit(); // 退出场景时卸载
};