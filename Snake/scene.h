#pragma once

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {} //进入场景时初始化
	virtual void on_update() {} //数据更新
	virtual void on_draw() {} //绘图
	virtual void on_input() {} //处理输入
	virtual void on_exit() {} // 退出场景时卸载
};