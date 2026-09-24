#include<graphics.h>
#include<vector>
#include"snake.h"

class Food
{
private:
	std::vector<POINT> food_position;//食物的位置
	int color = RED;//食物颜色

public:
	Food() = default;
	~Food() = default;

	//随机生成食物
	void createFood();

	//食物的更新
	void on_update();

	//食物的绘制
	void on_draw();

	//移除index位置上的食物
	void deleteFood(int index);

	//更改食物颜色
	void resetFoodColor();

	//判断食物是否被吃
	bool isFoodBeCollision(const Snake *snake, const Food *food);

};