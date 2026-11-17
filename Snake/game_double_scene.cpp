#include"game_double_scene.h"
#include"scene_manage.h"
#include"common.h"
#include"snake.h"
#include"snake_2p.h"

extern std::vector<Snake*> global_snake_list;
extern Item* food;
extern SceneManage scene_manage;

void GameDoubleScene::on_enter()
{
	setbkcolor(RGB(137, 207, 240));
	setlinecolor(WHITE - 100);
	global_snake_list.push_back(new Snake(POINT(WIN_WIDTH_BOARD / 4, WIN_HEIGHT_BOARD / 2), RED, 4));
	global_snake_list.push_back(new Snake2P(POINT(WIN_WIDTH_BOARD - WIN_WIDTH_BOARD / 4, WIN_HEIGHT_BOARD / 2), GREEN, 4));
	food = new Item(Item::Food, 5, RGB(144, 238, 144));
}

void GameDoubleScene::on_update(int delta)
{
	food->on_update(delta);
	
	for (auto snake : global_snake_list)
	{
		snake->on_update(delta);
	}

}

void GameDoubleScene::on_draw()
{
	for (int i = WIN_HEIGHT_BOARD; i >= 0; i--)
	{
		line(0, i * GRID + WIN_HEIGHT_STATUS, WIN_WIDTH, i * GRID + WIN_HEIGHT_STATUS);
	}
	for (int i = 0; i <= WIN_WIDTH_BOARD; i++)
	{
		line(i * GRID, WIN_HEIGHT_STATUS, i * GRID, WIN_HEIGHT);
	}
	food->on_draw();
	
	for (auto snake : global_snake_list)
	{
		snake->on_draw();
	}

}

void GameDoubleScene::on_input(ExMessage& msg)
{
	
	for (auto snake : global_snake_list)
	{
		snake->on_input(msg);
	}
	if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
	{
		scene_manage.switch_to(SceneManage::SceneType::Menu);
	}
}

void GameDoubleScene::on_exit()
{
	for (auto snake : global_snake_list)
	{
		delete snake;
	}
	global_snake_list.clear();
}