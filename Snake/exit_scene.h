#pragma once
#include"scene.h"
#include"timer.h"

class ExitScene :public Scene
{
public:
	ExitScene() = default;
	ExitScene(LPCTSTR exit_bk_path);
	~ExitScene() = default;

	void on_enter(); //进入场景时初始化
	void on_update(int delta); //数据更新
	void on_draw(); //绘图
	void on_input(ExMessage& msg); //处理输入
	void on_exit(); // 退出场景时卸载

private:
	Timer game_exit_timer; // 游戏结束倒计时，结束游戏主循环终止
	IMAGE exit_background_image;
	bool is_background_image_loaded = false;
};