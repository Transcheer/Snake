#include"scene_manage.h"

extern Scene* game_double_scene;
extern Scene* game_single_scene;
extern Scene* finish_scene;
extern Scene* menu_scene;

//设置当前场景
void SceneManage::set_current_scene(Scene* scene)
{
	current_scene = scene;
	current_scene->on_enter();
}

//转换场景
void SceneManage::switch_to(SceneType type)
{
	current_scene->on_exit();
	switch (type)
	{
	case SceneType::Finish:
		set_current_scene(finish_scene);
		break;
	case SceneType::Game_Double:
		set_current_scene(game_double_scene);
		break;
	case SceneType::Game_Single:
		set_current_scene(game_single_scene);
		break;
	case SceneType::Menu:
		set_current_scene(menu_scene);
		break;
	default:
		break;
	}
}

//
void SceneManage::on_update(int delta)
{
	current_scene->on_update(delta);
}

void SceneManage::on_draw()
{
	current_scene->on_draw();
}

void SceneManage::on_input(ExMessage& msg)
{
	current_scene->on_input(msg);
}