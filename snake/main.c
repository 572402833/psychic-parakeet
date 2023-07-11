#include "./include/head.h"

int main(int argc, char const *argv[])
{
	// 1.打开lcd
	lcd_open();
	// 2.打开触摸屏
	ts_open();
	// 初始化字库
	Init_Font();
	// 开启线程
	thread_init();

	// 游戏初始化界面
	game_init_interface();

	// 关闭字库
	UnInit_Font();
	// 关闭lcd
	close(lcd_fd);
	// 关闭触摸屏
	close(ts_fd);
	// 取消内存映射
	munmap(lcd_map, 800 * 480 * 4);
	return 0;
}
