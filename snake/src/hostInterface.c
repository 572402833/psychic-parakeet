#include "../include/head.h"

// ��¼��
int x_annal = 615, y_annal = 20;

// �����ʼ��
void game_init_interface()
{
	head = link_init();
	// ��ʼ����Ϸ��Ļ
	show_bmp(0, 0, "./bmp/pingmu.bmp");
	// ��ʾ��Ļ��ť
	screen_button();
	// ��ȡ��Ļ����
	while (1)
	{
		// �ж��Ƿ񰴶�λ��
		if ((x > 610 && x < 760) && (y > 10 && y < 85))
		{
			// ��ʼ��Ϸ
			game_start(head);
			x = y = 0;
		}
		if ((x > 610 && x < 760) && (y > 95 && y < 170))
		{
			// ������Ϸ
			game_reset(head);
			x = y = 0;
		}
	}
}

// ��ʾ���������ť
void screen_button()
{
	// ��ʼ�����ã���ͣ
	show_bmp(600, 10, "./bmp/kaishi.bmp");
	show_bmp(600, 120, "./bmp/shuaxin.bmp");
	show_bmp(700, 120, "./bmp/zanting.bmp");

	// �������Ұ�ť
	show_bmp(670, 360, "./jiantou/shang.bmp");
	show_bmp(610, 420, "./jiantou/zuo.bmp");
	show_bmp(670, 420, "./jiantou/xia.bmp");
	show_bmp(730, 420, "./jiantou/you.bmp");
}

// ����
void game_reset(node *head)
{
	char *str = "��	��";
	x_annal = 615, y_annal = 20;
	// ���������
	link_free(head);
	dataType top = {.x = 5, .y = 5, .filename = "./bmp/tou.bmp"};
	dataType body = {.x = 4, .y = 5, .filename = "./bmp/body.bmp"};
	dataType end = {.x = 3, .y = 5, .filename = "./bmp/wei.bmp"};
	link_add_tail2(head, top);
	link_add_tail2(head, body);
	link_add_tail2(head, end);
	show_bmp(0, 0, "./bmp/pingmu.bmp");
	// ��ʾ�ַ��� ���� ����ɫ����
	Display_characterX(600, 230, str, 0x00ffffff, 2);
	show_bmp(650, 300, "./bmp/fsfg.bmp");
	show_bmp(top.x * 15, top.y * 12, top.filename);
	show_bmp(body.x * 15, body.y * 12, body.filename);
	show_bmp(end.x * 15, end.y * 12, end.filename);
}

// ��Ϸ��ʼ
void game_start(node *head)
{
	int move, top_x, top_y;
	// �����ڵ�, �ƶ���ͷ
	node *pos, *top;
	// �ٴε����ʼ��������
	game_reset(head);
	x = y = 0;
	// ����ʳ��
	generate_food(head);
	while (1)
	{
		// �ж�ʳ���Ƿ񱻳Ե�
		if (food != 0)
		{
			food = 0;
			generate_food(head);
		}
		// ��ʾ����
		for (pos = head->next; pos != head; pos = pos->next)
			show_bmp(pos->data.x * 15, pos->data.y * 12, pos->data.filename);
		if ((x > 670 && x < 720) && (y > 360 && y < 410)) // ��
		{
			// ��ͷ���ϲ��ܵ�����°�ť
			if (move == DOWN)
			{
				x = 680, y = 430;
				continue;
			}
			// ��¼��ǰ��ͷָ��
			x_annal = x, y_annal = y;
			// �ж��Ƿ����
			if (!up_move(head))
			{
				// ����
				sleep(3);
				// ����һ����Ϸ����
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			// ��¼��ǰ��ͷָ��
			move = UP;
		}
		else if ((x > 670 && x < 720) && (y > 420 && y < 470)) // ��
		{
			if (move == UP)
			{
				x = 680, y = 380;
				continue;
			}
			x_annal = x, y_annal = y;

			if (!down_move(head))
			{
				// ����
				sleep(3);
				// ����һ����Ϸ����
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			move = DOWN;
		}
		else if ((x > 610 && x < 660) && (y > 420 && y < 470)) // ��
		{
			if (move == RIGHT)
			{
				x = 740, y = 430;
				continue;
			}
			x_annal = x, y_annal = y;
			if (!left_move(head))
			{
				// ����
				sleep(3);
				// ����һ����Ϸ����
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			move = LEFT;
		}
		else if ((x > 730 && x < 780) && (y > 420 && y < 480)) // ��
		{
			if (move == LEFT)
			{
				x = 630, y = 430;
				continue;
			}
			x_annal = x, y_annal = y;
			if (!right_move(head))
			{
				// ����
				sleep(3);
				// ����һ����Ϸ����
				show_bmp(0, 0, "./bmp/pingmu.bmp");
				break;
			}
			move = RIGHT;
		}
		else if ((x > 600 && x < 700) && (y > 120 && y < 220))
		{
			// ����
			game_reset(head);
			break;
		}
		else if ((x > 700 && x < 800) && (y > 120 && y < 220))
			stop();
		else if ((x > 610 && x < 760) && (y > 10 && y < 85)) // ��ʼ��Ϸ���ֵ�ǰ�ƶ�
		{
			move = RIGHT;
			// �Ӻ���ǰ��¼�ߵĸ�������
			node_move(head);
			// ���ƶ�
			head->next->data.x++;
			usleep(300000);
			if (head->next->data.x > 39)
			{
				show_bmp(300, 240, "./bmp/jieshu.bmp");
				break;
			}
		}
		else
			x = x_annal, y = y_annal; // ���ֵ�ǰ�ƶ�
	}
}

// ��
int up_move(node *head)
{
	if (node_move(head) == 0)
	{
		// �����ƶ�
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

// ��
int down_move(node *head)
{
	if (node_move(head) == 0)
	{
		// �ڵ��ƶ�
		node_move(head);
		// �����ƶ�
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

// ��
int left_move(node *head)
{
	if (node_move(head) == 0)
	{
		// �ڵ��ƶ�
		node_move(head);
		// ���ƶ�
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

// ��
int right_move(node *head)
{
	// �ڵ��ƶ�
	if (node_move(head) == 0)
	{
		// �����ƶ�
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

// ���ƶ�
int node_move(node *head)
{
	node *pos;
	if (eat(head) == 0)
	{
		// �Ӻ���ǰ��¼�ߵĸ������ݣ��ú󸲸�ǰ
		for (pos = head->prev; pos != head->next; pos = pos->prev)
		{
			pos->data.x = pos->prev->data.x;
			pos->data.y = pos->prev->data.y;
		}
		return 0;
	}
	return -1;
}

// ����ʳ��
void generate_food(node *head)
{
	if (food == 0)
	{
		// ��������
		node *pos;
		// ����0��10�������
		x_eat = rand() % 40;
		y_eat = rand() % 40;
		// �ж�ʳ���Ƿ�������������
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

// ��
int eat(node *head)
{
	node *pos;
	for (pos = head->next; pos != head->prev; pos = pos->next)
	{
		// ��ͷ�Ե�������������ͷ������������ͬ
		if (head->next->data.x == pos->next->data.x && head->next->data.y == pos->next->data.y)
		{
			return -1;
		}
	}
	// ��ͷ��ʳ���������ͬ
	dataType new = {0};
	char score[7] = {0};
	if (head->next->data.x == x_eat && head->next->data.y == y_eat)
	{
		// �Ե�������һ
		head->next->data.fraction++;
		// ת������
		sprintf(score, "%d", head->next->data.fraction);
		// �����ϴη���
		show_bmp(650, 300, "./bmp/fsfg.bmp");
		// �������
		Display_characterX(650, 300, score, 0x00ffffff, 1);
		food = 1;
		new.x = x_eat;
		new.y = y_eat;
		strcpy(new.filename, "./bmp/body.bmp");
		link_add2(head, new);
	}
	return 0;
}

// ֹͣ
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