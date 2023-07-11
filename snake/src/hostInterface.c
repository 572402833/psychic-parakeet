#include "../include/head.h"

// 记录点
int x_annal = 615, y_annal = 20;

// 界面初始化
void game_init_interface()
{
	head = link_init();
	// 初始会游戏屏幕
	show_bmp(0, 0, "./bmp/pingmu.bmp");
	// 显示屏幕按钮
	screen_button();
	// 获取屏幕坐标
	while (1)
	{
		// 判断是否按对位置
		if ((x > 610 && x < 760) && (y > 10 && y < 85))
		{
			// 开始游戏
			game_start(head);
			x = y = 0;
		}
		if ((x > 610 && x < 760) && (y > 95 && y < 170))
		{
			// 重置游戏
			game_reset(head);
			x = y = 0;
		}
	}
}

// 显示各项操作按钮
void screen_button()
{
	// 开始和重置，暂停
	show_bmp(600, 10, "./bmp/kaishi.bmp");
	show_bmp(600, 120, "./bmp/shuaxin.bmp");
	show_bmp(700, 120, "./bmp/zanting.bmp");

	// 上下左右按钮
	show_bmp(670, 360, "./jiantou/shang.bmp");
	show_bmp(610, 420, "./jiantou/zuo.bmp");
	show_bmp(670, 420, "./jiantou/xia.bmp");
	show_bmp(730, 420, "./jiantou/you.bmp");
}

// 重置
void game_reset(node *head)
{
	char *str = "分	数";
	x_annal = 615, y_annal = 20;
	// 将链表清空
	link_free(head);
	dataType top = {.x = 5, .y = 5, .filename = "./bmp/tou.bmp"};
	dataType body = {.x = 4, .y = 5, .filename = "./bmp/body.bmp"};
	dataType end = {.x = 3, .y = 5, .filename = "./bmp/wei.bmp"};
	link_add_tail2(head, top);
	link_add_tail2(head, body);
	link_add_tail2(head, end);
	show_bmp(0, 0, "./bmp/pingmu.bmp");
	// 显示字符串 分数 ，白色字体
	Display_characterX(600, 230, str, 0x00ffffff, 2);
	show_bmp(650, 300, "./bmp/fsfg.bmp");
	show_bmp(top.x * 15, top.y * 12, top.filename);
	show_bmp(body.x * 15, body.y * 12, body.filename);
	show_bmp(end.x * 15, end.y * 12, end.filename);
}

// 游戏开始
void game_start(node *head)
{
	int move, top_x, top_y;
	// 遍历节点, 移动蛇头
	node *pos, *top;
	// 再次点击开始，重置蛇
	game_reset(head);
	x = y = 0;
	// 生成食物
	generate_food(head);
	while (1)
	{
		// 判断食物是否被吃掉
		if (food != 0)
		{
			food = 0;
			generate_food(head);
		}
		// 显示蛇身
		for (pos = head->next; pos != head; pos = pos->next)
			show_bmp(pos->data.x * 15, pos->data.y * 12, pos->data.filename);
		if ((x > 670 && x < 720) && (y > 360 && y < 410)) // 上
		{
			// 蛇头向上不能点击向下按钮
			if (move == DOWN)
			{
				x = 680, y = 430;
				continue;
			}
			// 记录当前蛇头指向
			x_annal = x, y_annal = y;
			// 判断是否结束
			if (!up_move(head))
			{
				// 休眠
				sleep(3);
				// 将上一把游戏覆盖
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			// 记录当前蛇头指向
			move = UP;
		}
		else if ((x > 670 && x < 720) && (y > 420 && y < 470)) // 下
		{
			if (move == UP)
			{
				x = 680, y = 380;
				continue;
			}
			x_annal = x, y_annal = y;

			if (!down_move(head))
			{
				// 休眠
				sleep(3);
				// 将上一把游戏覆盖
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			move = DOWN;
		}
		else if ((x > 610 && x < 660) && (y > 420 && y < 470)) // 左
		{
			if (move == RIGHT)
			{
				x = 740, y = 430;
				continue;
			}
			x_annal = x, y_annal = y;
			if (!left_move(head))
			{
				// 休眠
				sleep(3);
				// 将上一把游戏覆盖
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			move = LEFT;
		}
		else if ((x > 730 && x < 780) && (y > 420 && y < 480)) // 右
		{
			if (move == LEFT)
			{
				x = 630, y = 430;
				continue;
			}
			x_annal = x, y_annal = y;
			if (!right_move(head))
			{
				// 休眠
				sleep(3);
				// 将上一把游戏覆盖
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			move = RIGHT;
		}
		else if ((x > 600 && x < 700) && (y > 120 && y < 220))
		{
			// 重置
			game_reset(head);
			break;
		}
		else if ((x > 700 && x < 800) && (y > 120 && y < 220))
			stop();
		else if ((x > 610 && x < 760) && (y > 10 && y < 85)) // 开始游戏保持当前移动
		{
			move = RIGHT;
			// 从后向前记录蛇的各个数据
			node_move(head);
			// 不移动
			head->next->data.x++;
			usleep(300000);
			if (head->next->data.x > 39)
			{
				show_bmp(300, 240, "./bmp/jieshu.bmp");
				break;
			}
		}
		else
			x = x_annal, y = y_annal; // 保持当前移动
	}
}

// 上
int up_move(node *head)
{
	if (node_move(head) == 0)
	{
		// 向上移动
		head->next->data.y--;
		usleep(300000);
		if (head->next->data.y <= 0)
		{
			show_bmp(300, 240, "./bmp/jieshu.bmp");
			return 0;
		}
		return 1;
	}
	show_bmp(300, 240, "./bmp/jieshu.bmp");
	return 0;
}

// 下
int down_move(node *head)
{
	if (node_move(head) == 0)
	{
		// 节点移动
		node_move(head);
		// 向下移动
		head->next->data.y++;

		// eat(head);
		usleep(300000);
		if (head->next->data.y >= 40)
		{
			show_bmp(300, 240, "./bmp/jieshu.bmp");
			return 0;
		}
		return 1;
	}
	show_bmp(300, 240, "./bmp/jieshu.bmp");
	return 0;
}

// 左
int left_move(node *head)
{
	if (node_move(head) == 0)
	{
		// 节点移动
		node_move(head);
		// 左移动
		head->next->data.x--;
		usleep(300000);
		if (head->next->data.x < 0)
		{
			show_bmp(300, 240, "./bmp/jieshu.bmp");
			return 0;
		}
		return 1;
	}
	show_bmp(300, 240, "./bmp/jieshu.bmp");
	return 0;
}

// 右
int right_move(node *head)
{
	// 节点移动
	if (node_move(head) == 0)
	{
		// 向右移动
		head->next->data.x++;
		// eat(head);
		usleep(300000);
		if (head->next->data.x > 40)
		{
			show_bmp(300, 240, "./bmp/jieshu.bmp");
			return 0;
		}
		return 1;
	}
	show_bmp(300, 240, "./bmp/jieshu.bmp");
	return 0;
}

// 蛇移动
int node_move(node *head)
{
	node *pos;
	if (eat(head) == 0)
	{
		// 从后向前记录蛇的各个数据，用后覆盖前
		for (pos = head->prev; pos != head->next; pos = pos->prev)
		{
			pos->data.x = pos->prev->data.x;
			pos->data.y = pos->prev->data.y;
		}
		return 0;
	}
	return -1;
}

// 生成食物
void generate_food(node *head)
{
	if (food == 0)
	{
		// 遍历链表
		node *pos;
		// 生成0到10的随机数
		x_eat = rand() % 40;
		y_eat = rand() % 40;
		// 判断食物是否生成在蛇身上
		for (pos = head->next; pos != head; pos = pos->next)
		{
			if (pos->data.x == x_eat && pos->data.y == y_eat)
			{
				x_eat = rand() % 40;
				y_eat = rand() % 40;
			}
			else
			{
				show_bmp(x_eat * 15, y_eat * 12, "./bmp/body.bmp");
			}
		}
	}
}

// 吃
int eat(node *head)
{
	node *pos;
	for (pos = head->next; pos != head->prev; pos = pos->next)
	{
		// 蛇头吃到了蛇身了蛇身，头和身子坐标相同
		if (head->next->data.x == pos->next->data.x && head->next->data.y == pos->next->data.y)
		{
			return -1;
		}
	}
	// 蛇头和食物的坐标相同
	dataType new = {0};
	char score[7] = {0};
	if (head->next->data.x == x_eat && head->next->data.y == y_eat)
	{
		// 吃到分数加一
		head->next->data.fraction++;
		// 转化分数
		sprintf(score, "%d", head->next->data.fraction);
		// 覆盖上次分数
		show_bmp(650, 300, "./bmp/fsfg.bmp");
		// 具体分数
		Display_characterX(650, 300, score, 0x00ffffff, 1);
		food = 1;
		new.x = x_eat;
		new.y = y_eat;
		strcpy(new.filename, "./bmp/body.bmp");
		link_add2(head, new);
	}
	return 0;
}

// 停止
void stop()
{
	while (1)
	{
		if (
			(x > 670 && x < 720) && (y > 360 && y < 410) || (x > 670 && x < 720) && (y > 420 && y < 470) || (x > 610 && x < 660) && (y > 420 && y < 470) || (x > 730 && x < 780) && (y > 420 && y < 480) || (x > 600 && x < 700) && (y > 120 && y < 220))
			return;
		else
			continue;
	}
}