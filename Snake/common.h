#ifndef COMMON_H
#define COMMON_H

//全局变量
constexpr int WIN_HEIGHT_STATUS = 150; //窗口上方的状态栏的高度   单位像素
constexpr int GRID = 20; //一个格子的大小  单位像素
constexpr int WIN_WIDTH_BOARD = 30; //窗口宽度  单位格子
constexpr int WIN_HEIGHT_BOARD = 30; // 窗口高度  单位格子
inline const int WIN_WIDTH = WIN_WIDTH_BOARD * GRID; // 窗口宽度  单位像素
inline const int WIN_HEIGHT = WIN_HEIGHT_BOARD * GRID + WIN_HEIGHT_STATUS; // 窗口高度  单位像素

#endif // !COMMON_H
