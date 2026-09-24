//头文件
#include<graphics.h>


//全局变量


int main()
{
	initgraph(680, 680);

	ExMessage msg;
	BeginBatchDraw();
	while (1)
	{
		while (peekmessage(&msg))
		{

		}
		cleardevice();

		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();

	return 0;
}