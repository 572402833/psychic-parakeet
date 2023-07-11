#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <pthread.h>
#include "font.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// 打开lcd
int lcd_fd;
// 打开映射
int *lcd_map;
// 屏幕结构体
struct input_event ts_buf;
// 链表结构体
typedef struct data
{
	int x, y;
	char filename[30];
	int fraction;
}dataType;
typedef struct node
{
	dataType data;
	struct node *prev;
	struct node *next;
}node;
// 是否进行操作标志位
// int flage;
// 打开触摸
int ts_fd;
// 坐标
int x, y;
// 食物坐标
int x_eat, y_eat;
// 食物标志位
int food;

// 打开触摸
void ts_open(void);
// 打开屏幕
void lcd_open(void);
// 显示图片
int show_bmp(int x0, int y0, char *pathname);
// 获取坐标
int get_xy();
// 初始化头节点
node *head;


// 节点初始化
node *link_init();
// 头插法
void link_add(node *head, dataType new_data);
// 头插法2
void link_add2(node *head, dataType new_data);
// 尾插法2
void link_add_tail2(node *head, dataType new_data);
// 后序遍历
void link_show(node *head);
// 前序遍历
void link_show_prev(node *head);
// 链表清空
void link_free(node *head);


// 游戏初始化界面
void game_init_interface();
// 游戏开始
void game_start(node *head);
// 显示各项操作按钮
void screen_button();
// 重置
void game_reset(node *head);
// 上
int up_move(node *head);
//下
int down_move(node *head);
// 左
int left_move(node *head);
// 右
int right_move(node *head);
// 蛇移动
int node_move(node *head);
// 食物生成
void generate_food(node *head);
// 吃
int eat(node *head);
// 停止
void stop();


// 初始化线程
void thread_init();
// 线程开始
void *thread_start(void *arg);

#endif