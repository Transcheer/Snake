#pragma once
#include"game_single_scene.h"
#include"game_double_scene.h"

class SceneManage
{
public:
	//场景枚举
	enum SceneType
	{
		Game_Double,//双人游戏
		Game_Single,//单人游戏
		Menu,//菜单
		Finish//结算界面
	};

	//设置当前场景
	void set_current_scene(Scene* scene);

	//转换场景
	void switch_to(SceneType type);

	//
	void on_update(int delta);

	void on_draw();

	void on_input(ExMessage& msg);

private:
	Scene* current_scene = nullptr;
};