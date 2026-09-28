#pragma once
#include<functional>

class Timer
{
private:
	int pass_time = 0;//已过时间
	int wait_time = 0; //等待时间
	bool paused = false; // 是否暂停
	bool shotted = false; // 是否触发
	bool one_shot = false; // 是否单次触发

	std::function<void()> callback; // 回调函数

public:
	Timer();
	~Timer();

	//重置定时器
	void resart();

	void set_wait_time(int val);

	void set_one_shot(bool flag);

	void set_callback(std::function<void()> call);

	void pause();

	void resume();

	void on_update(int delta);

};