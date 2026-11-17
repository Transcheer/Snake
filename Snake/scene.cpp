#include<graphics.h>
#include"scene.h"
Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::on_enter() {} //进入场景时初始化
void Scene::on_update(int delta) {} //数据更新
void Scene::on_draw() {} //绘图
void Scene::on_input(ExMessage& msg) {} //处理输入
void Scene::on_exit() {} // 退出场景时卸载