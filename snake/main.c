#include "./include/head.h"

int main(int argc, char const *argv[])
{
	// 1.��lcd
	lcd_open();
	// 2.�򿪴�����
	ts_open();
	// ��ʼ���ֿ�
	Init_Font();
	// �����߳�
	thread_init();

	// ��Ϸ��ʼ������
	game_init_interface();

	// �ر��ֿ�
	UnInit_Font();
	// �ر�lcd
	close(lcd_fd);
	// �رմ�����
	close(ts_fd);
	// ȡ���ڴ�ӳ��
	munmap(lcd_map, 800 * 480 * 4);
	return 0;
}
