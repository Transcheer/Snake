#include"menu_scene.h"
#include"scene_manage.h"
#include"common.h"
#include<iostream>

extern SceneManage scene_manage;

MenuScene::MenuScene() = default;
MenuScene::~MenuScene() = default;
MenuScene::MenuScene(LPCTSTR menu_bk_path)
{
	loadimage(&menu_background, menu_bk_path, WIN_WIDTH, WIN_HEIGHT);
}

void MenuScene::on_enter() //进入场景时初始化
{
	int left = WIN_WIDTH / 2 - 96;
	int right = WIN_WIDTH / 2 + 96;
	int heigh = 195 - 120;
	int gap = 50;
	bt_single_mode.initialize_button(RECT(left, 250, right, 250 + heigh), SceneManage::SceneType::Game_Single,
		_T("resource/ui_start_idle.png"), _T("resource/ui_start_hovered.png"), _T("resource/ui_start_pushed.png"));
	bt_double_mode.initialize_button(RECT(left, 250 + heigh + gap, right, 250 + heigh + gap + heigh), SceneManage::SceneType::Game_Double,
		_T("resource/ui_start_idle.png"), _T("resource/ui_start_hovered.png"), _T("resource/ui_start_pushed.png"));
	bt_exit_game.initialize_button(RECT(left, 250 + heigh + gap + heigh + gap, right, 250 + heigh + gap + heigh + gap + heigh), SceneManage::SceneType::Exit,
		_T("resource/ui_start_idle.png"), _T("resource/ui_start_hovered.png"), _T("resource/ui_start_pushed.png"));

	bt_single_mode.reset();
	bt_double_mode.reset();
	bt_exit_game.reset();

	//std::cout << "ON_ENTER trigger!\n";
}

void MenuScene::on_update(int delta) //数据更新
{

}

void MenuScene::on_draw() //绘图
{
	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &menu_background, 0, 0);
	bt_single_mode.on_draw();
	bt_double_mode.on_draw();
	bt_exit_game.on_draw();
}

void MenuScene::on_input(ExMessage& msg) //处理输入
{
	if (msg.message != WM_MOUSEMOVE && msg.message != WM_LBUTTONDOWN && msg.message != WM_LBUTTONUP)
		return;

	bt_single_mode.on_input(msg);
	bt_double_mode.on_input(msg);
	bt_exit_game.on_input(msg);

	if (bt_single_mode.is_clicked())
		scene_manage.switch_to(bt_single_mode.next_scene_type());
	else if (bt_double_mode.is_clicked())
		scene_manage.switch_to(bt_double_mode.next_scene_type());
	else if (bt_exit_game.is_clicked())
		scene_manage.switch_to(bt_exit_game.next_scene_type());
}


void MenuScene::on_exit() // 退出场景时卸载
{

}

bool Button::initialize_button(RECT rect, SceneManage::SceneType button_type, LPCTSTR idle_path, LPCTSTR hover_path, LPCTSTR push_path)
{
	//按钮类型
	set_next_scene_button_type(button_type);
	//位置
	set_button_pos(rect);
	//图片
	return set_button_image(idle_path, hover_path, push_path);
}

void Button::reset()
{

}

void Button::on_input(const ExMessage& msg)
{
	is_button_clicked = false;
	const bool inside = is_button_mouse_in_region(msg.x, msg.y);

	switch (msg.message)
	{
	case WM_MOUSEMOVE:
		if (button_status != ButtonStatus::Push)
			button_status = inside ? ButtonStatus::Hover : ButtonStatus::Idle;
		break;
	case WM_LBUTTONDOWN:
		if (inside)
			button_status = ButtonStatus::Push;
		break;
	case WM_LBUTTONUP:
		if (inside && button_status == ButtonStatus::Push)
			is_button_clicked = true;
		button_status = inside ? ButtonStatus::Hover : ButtonStatus::Idle;
		break;
	default:
		break;
	}

}

//设置下一个场景类型
void Button::set_next_scene_button_type(SceneManage::SceneType button_type)
{
	button_next_scene_type = button_type;
}

//设置当前按钮位置
void Button::set_button_pos(RECT rect)
{
	button_rect = rect;
}

//设置按钮图片
bool Button::set_button_image(LPCTSTR idle_path, LPCTSTR hover_path, LPCTSTR push_path)
{
	if (is_button_img_loaded)
		return true;
	//loadimage(&button_image_idle, idle_path, (button_rect.right - button_rect.right), (button_rect.bottom - button_rect.top), true);
	//loadimage(&button_image_hover, hover_path, (button_rect.right - button_rect.right), (button_rect.bottom - button_rect.top), true);
	//loadimage(&button_image_push, push_path, (button_rect.right - button_rect.right), (button_rect.bottom - button_rect.top), true);

	loadimage(&button_image_idle, idle_path);
	loadimage(&button_image_hover, hover_path);
	loadimage(&button_image_push, push_path);
	is_button_img_loaded = button_image_idle.getwidth() > 0
		&& button_image_hover.getwidth() > 0
		&& button_image_push.getwidth() > 0;

	return is_button_img_loaded;
}

//绘制
void Button::on_draw()
{
	if (button_image_idle.getwidth() <= 0)return;

	IMAGE* img = &button_image_idle;
	int x = button_rect.left;
	int y = button_rect.top;
	switch (button_status)
	{
	case ButtonStatus::Hover:
		img = &button_image_hover;
		break;
	case ButtonStatus::Push:
		img = &button_image_push;
		break;
	default:
		break;
	}
	putimage(x, y, img);
}

// 判断当前鼠标位置是否有效
bool Button::is_button_mouse_in_region(int x, int y) const
{
	return PtInRect(&button_rect, POINT{ x,y }) != false;
}
