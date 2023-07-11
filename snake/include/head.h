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

// ��lcd
int lcd_fd;
// ��ӳ��
int *lcd_map;
// ��Ļ�ṹ��
struct input_event ts_buf;
// ����ṹ��
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
// �Ƿ���в�����־λ
// int flage;
// �򿪴���
int ts_fd;
// ����
int x, y;
// ʳ������
int x_eat, y_eat;
// ʳ���־λ
int food;

// �򿪴���
void ts_open(void);
// ����Ļ
void lcd_open(void);
// ��ʾͼƬ
int show_bmp(int x0, int y0, char *pathname);
// ��ȡ����
int get_xy();
// ��ʼ��ͷ�ڵ�
node *head;


// �ڵ��ʼ��
node *link_init();
// ͷ�巨
void link_add(node *head, dataType new_data);
// ͷ�巨2
void link_add2(node *head, dataType new_data);
// β�巨2
void link_add_tail2(node *head, dataType new_data);
// �������
void link_show(node *head);
// ǰ�����
void link_show_prev(node *head);
// �������
void link_free(node *head);


// ��Ϸ��ʼ������
void game_init_interface();
// ��Ϸ��ʼ
void game_start(node *head);
// ��ʾ���������ť
void screen_button();
// ����
void game_reset(node *head);
// ��
int up_move(node *head);
//��
int down_move(node *head);
// ��
int left_move(node *head);
// ��
int right_move(node *head);
// ���ƶ�
int node_move(node *head);
// ʳ������
void generate_food(node *head);
// ��
int eat(node *head);
// ֹͣ
void stop();


// ��ʼ���߳�
void thread_init();
// �߳̿�ʼ
void *thread_start(void *arg);

#endif