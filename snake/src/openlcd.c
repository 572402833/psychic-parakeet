#include "../include/head.h"

// �򿪴���������
void ts_open(void)
{
	// 1.�򿪴�������
	ts_fd = open("/dev/input/event0", O_RDWR);
	if (ts_fd == -1)
	{
		perror("open ts failed!\n");
		return;
	}
}

// ����ʾ��
void lcd_open(void)
{
	// 1.��lcd
	lcd_fd = open("/dev/fb0", O_RDWR);
	if (lcd_fd == -1)
	{
		perror("open lcd failed!\n");
		return;
	}
	// 2.����Ļ�豸�����ڴ�ӳ��
	lcd_map = mmap(NULL,				   // ��ʼ��ַ
				   800 * 480 * 4,		   // �ڴ��С
				   PROT_READ | PROT_WRITE, // Ȩ��
				   MAP_SHARED,			   // ����
				   lcd_fd,				   // ��lcd�豸�����ڴ�ӳ��
				   0);					   // ƫ����
}

// ��ʾ��ʼλ��Ϊ��x0,y0����ͼƬ��pathnameΪͼƬ��·��
int show_bmp(int x0, int y0, char *pathname)
{
	// 2.��ͼƬ
	int bmp_fd = open(pathname, O_RDONLY);
	if (bmp_fd == -1)
	{
		perror("open bmp failed!\n");
		return -1;
	}
	// 3.��ȡͼƬ����������
	// 3.0 ƫ��ȥ��ͷ54�ֽڵķ�������Ϣ
	char head[54] = {0};
	read(bmp_fd, head, 54);
	// ͼƬ�Ŀ�͸���54�ֽڵ�ͷ��Ϣ�У����дӵ�18�ֽڿ�ʼ��22�ֽ��ǿ�
	int w = *((int *)&head[18]);
	int h = *((int *)&head[22]);
	// printf("w:%d, h:%d\n", w, h);

	// ����Windows���������ֵ
	int n_add; // ��Ҫ�����ֽ���(��)
	int add_a; // ����֮����ֽڣ��У�
	n_add = (4 - w * 3 % 4) % 4;
	add_a = n_add + w * 3; // ����֮���һ�г���(�ֽ�)

	char bmp_add[add_a * h]; // �洢����������ֵ��ͼƬ����
	read(bmp_fd, bmp_add, sizeof(bmp_add));

	// ���������ֵ
	char bmp_buf[w * h * 3];

	for (int j = 0; j < h; j++)
	{
		memcpy(&bmp_buf[w * 3 * j], &bmp_add[add_a * j], w * 3);
	}
	// 3.1 24λ����32λ
	int buf_32[w * h];
	for (int i = 0; i < w * h; i++)
	{
		// int (4�ֽ�) =  1�ֽ� B  λ��   1�ֽ� G   λ��   1�ֽ� R   λ��   1�ֽ� A
		buf_32[i] = bmp_buf[0 + i * 3] << 0 | bmp_buf[1 + i * 3] << 8 | bmp_buf[2 + i * 3] << 16 | 0x00 << 24;
	}

	// 3.2 ��ת,�������ݴ�ŵ�ӳ����ڴ���
	// int buf_fz[800*480] = {0};
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			lcd_map[800 * (y0 + y) + x0 + x] = buf_32[w * (h - 1 - y) + x];
		}
	}

	// 4.��ͼƬ����д��lcd
	// write(lcd_fd, buf_fz, sizeof(buf_fz));
	close(bmp_fd);
}

// ��ȡ����
int get_xy()
{
	while (1)
	{
		// 2.��ȡ����
		// ��սṹ��
		memset(&ts_buf, 0, sizeof(ts_buf));
		// ��ȡ�������ݣ��ŵ��ṹ�������
		read(ts_fd, &ts_buf, sizeof(ts_buf));
		if (ts_buf.type == EV_ABS && ts_buf.code == ABS_X) // ��������Ϊ�����������Ҿ����¼�����Ϊx����
		{
			x = ts_buf.value * 800 / 1024; // ��ȡx��ֵ��1024
		}
		if (ts_buf.type == EV_ABS && ts_buf.code == ABS_Y) // ��������Ϊ�����������Ҿ����¼�����Ϊx����
		{
			y = ts_buf.value * 480 / 600; // ��ȡy��ֵ��600
		}
		if (ts_buf.type == EV_KEY && ts_buf.code == BTN_TOUCH && ts_buf.value == 0)
			return 1; // �ɿ��˴�����
	}
}