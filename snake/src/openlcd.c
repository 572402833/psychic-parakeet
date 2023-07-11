#include "../include/head.h"

// 打开触摸屏驱动
void ts_open(void)
{
	// 1.打开触摸驱动
	ts_fd = open("/dev/input/event0", O_RDWR);
	if (ts_fd == -1)
	{
		perror("open ts failed!\n");
		return;
	}
}

// 打开显示屏
void lcd_open(void)
{
	// 1.打开lcd
	lcd_fd = open("/dev/fb0", O_RDWR);
	if (lcd_fd == -1)
	{
		perror("open lcd failed!\n");
		return;
	}
	// 2.对屏幕设备进行内存映射
	lcd_map = mmap(NULL,				   // 起始地址
				   800 * 480 * 4,		   // 内存大小
				   PROT_READ | PROT_WRITE, // 权限
				   MAP_SHARED,			   // 共享
				   lcd_fd,				   // 对lcd设备进行内存映射
				   0);					   // 偏移量
}

// 显示起始位置为（x0,y0）的图片，pathname为图片的路径
int show_bmp(int x0, int y0, char *pathname)
{
	// 2.打开图片
	int bmp_fd = open(pathname, O_RDONLY);
	if (bmp_fd == -1)
	{
		perror("open bmp failed!\n");
		return -1;
	}
	// 3.获取图片的像素数据
	// 3.0 偏移去掉头54字节的非像素信息
	char head[54] = {0};
	read(bmp_fd, head, 54);
	// 图片的宽和高在54字节的头信息中，其中从第18字节开始到22字节是宽
	int w = *((int *)&head[18]);
	int h = *((int *)&head[22]);
	// printf("w:%d, h:%d\n", w, h);

	// 处理Windows补齐的垃圾值
	int n_add; // 需要补的字节数(行)
	int add_a; // 补齐之后的字节（行）
	n_add = (4 - w * 3 % 4) % 4;
	add_a = n_add + w * 3; // 补齐之后的一行长度(字节)

	char bmp_add[add_a * h]; // 存储包含了垃圾值的图片数据
	read(bmp_fd, bmp_add, sizeof(bmp_add));

	// 处理掉垃圾值
	char bmp_buf[w * h * 3];

	for (int j = 0; j < h; j++)
	{
		memcpy(&bmp_buf[w * 3 * j], &bmp_add[add_a * j], w * 3);
	}
	// 3.1 24位补齐32位
	int buf_32[w * h];
	for (int i = 0; i < w * h; i++)
	{
		// int (4字节) =  1字节 B  位或   1字节 G   位或   1字节 R   位或   1字节 A
		buf_32[i] = bmp_buf[0 + i * 3] << 0 | bmp_buf[1 + i * 3] << 8 | bmp_buf[2 + i * 3] << 16 | 0x00 << 24;
	}

	// 3.2 翻转,并将数据存放到映射的内存中
	// int buf_fz[800*480] = {0};
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			lcd_map[800 * (y0 + y) + x0 + x] = buf_32[w * (h - 1 - y) + x];
		}
	}

	// 4.将图片数据写入lcd
	// write(lcd_fd, buf_fz, sizeof(buf_fz));
	close(bmp_fd);
}

// 获取坐标
int get_xy()
{
	while (1)
	{
		// 2.获取坐标
		// 清空结构体
		memset(&ts_buf, 0, sizeof(ts_buf));
		// 读取触摸数据，放到结构体变量中
		read(ts_fd, &ts_buf, sizeof(ts_buf));
		if (ts_buf.type == EV_ABS && ts_buf.code == ABS_X) // 输入类型为触摸屏，并且具体事件描述为x方向
		{
			x = ts_buf.value * 800 / 1024; // 获取x的值，1024
		}
		if (ts_buf.type == EV_ABS && ts_buf.code == ABS_Y) // 输入类型为触摸屏，并且具体事件描述为x方向
		{
			y = ts_buf.value * 480 / 600; // 获取y的值，600
		}
		if (ts_buf.type == EV_KEY && ts_buf.code == BTN_TOUCH && ts_buf.value == 0)
			return 1; // 松开了触摸屏
	}
}