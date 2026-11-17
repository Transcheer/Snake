#include"exit_scene.h"

extern bool is_game_running;

ExitScene::ExitScene(LPCTSTR exit_bk_path)
{
	if (!is_background_image_loaded)
		loadimage(&exit_background_image, exit_bk_path);
	is_background_image_loaded = exit_background_image.getwidth() > 0;
}
void ExitScene::on_enter()
{
	game_exit_timer.set_callback([&] {is_game_running = false; });
	game_exit_timer.set_one_shot(true);
	game_exit_timer.set_wait_time(2000);
}
void ExitScene::on_update(int delta)
{
	game_exit_timer.on_update(delta);
}
void ExitScene::on_draw()
{
	putimage(0, 0, &exit_background_image);
}
void ExitScene::on_input(ExMessage& msg)
{

}
void ExitScene::on_exit()
{
	game_exit_timer.resume();
}