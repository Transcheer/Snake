#pragma once
#include"scene.h"
#include"scene_manage.h"

class Button
{
public:
	enum ButtonStatus
	{
		Idle,
		Hover,
		Push
	};


	Button() = default;
	~Button() = default;
	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;

	bool initialize_button(RECT rect, SceneManage::SceneType button_type, LPCTSTR idle_path, LPCTSTR hover_path, LPCTSTR push_path);

	void reset();

	void on_input(const ExMessage& msg); // 接受输入更新状态
	//SceneManage::SceneType click_button(ExMessage& msg);
	bool is_clicked() const { return is_button_clicked; }
	SceneManage::SceneType next_scene_type() const { return button_next_scene_type; }

	void set_next_scene_button_type(SceneManage::SceneType button_type);
	//设置当前按钮位置
	void set_button_pos(RECT rect);
	//设置按钮图片
	bool set_button_image(LPCTSTR idle_path, LPCTSTR hover_path, LPCTSTR push_path);

	//绘制
	void on_draw();

private:
	RECT button_rect{ 0,0,0,0 };// 按钮位置
	ButtonStatus button_status = ButtonStatus::Idle;

	IMAGE button_image_idle{}; // 按钮默认图片
	IMAGE button_image_hover{}; // 按钮悬停图片
	IMAGE button_image_push{};  // 按钮按下图片
	//bool is_button_hover = false; // 按钮是否悬停
	//bool is_button_push = false; // 按钮是否按下
	bool is_button_clicked = false;

	SceneManage::SceneType button_next_scene_type{ SceneManage::SceneType::Menu }; // 下一个场景类型

	bool is_button_mouse_in_region(int x, int y) const; // 判断当前鼠标位置是否有效
};

class MenuScene :public Scene
{
public:
	MenuScene();
	MenuScene(LPCTSTR menu_bk_path);
	~MenuScene();

	void on_enter(); //进入场景时初始化
	void on_update(int delta); //数据更新
	void on_draw(); //绘图
	void on_input(ExMessage& msg); //处理输入
	void on_exit(); // 退出场景时卸载

private:

	IMAGE menu_background;
	Button bt_single_mode; // 单人模式按钮
	Button bt_double_mode; // 双人模式
	Button bt_exit_game; // 直接退出游戏
};

