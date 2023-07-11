#include "../include/head.h"

// ��ʼ��
node *link_init()
{
	node *p = malloc(sizeof(node));
	// �жϴ����Ƿ�ɹ�
	if (!p)
	{
		printf("malloc full\n");
		return NULL;
	}
	// ��������ָ����ĳ�ʼ��
	bzero(&p->data, sizeof(dataType));
	p->prev = p;
	p->next = p;
	return p;
}

// ͷ�巨
void link_add(node *head, dataType new_data)
{
	node *new = link_init();
	// ����λ��ʼ��
	new->data = new_data;

	// �½ڵ��ǰ��ָ����ָ��ǰ���ڵ�
	new->prev = head;
	// �½ڵ�ĺ��ָ����ָ��ǰ���ڵ����һ���ڵ�
	new->next = head->next;
	// ǰ���ڵ����һ���ڵ��ǰ��ָ����ָ���½ڵ�
	head->next->prev = new;
	// ǰ���ڵ�ĺ��ָ����ָ���½ڵ�
	head->next = new;
}

// ͷ�巨2
void link_add2(node *head, dataType new_data)
{
	node *new = link_init();
	// ����λ��ʼ��
	new->data = new_data;
	node *top = head->next;

	// �½ڵ��ǰ��ָ����ָ��ǰ���ڵ�
	new->prev = top;
	// �½ڵ�ĺ��ָ����ָ��ǰ���ڵ����һ���ڵ�
	new->next = top->next;
	// ǰ���ڵ����һ���ڵ��ǰ��ָ����ָ���½ڵ�
	top->next->prev = new;
	// ǰ���ڵ�ĺ��ָ����ָ���½ڵ�
	top->next = new;
}

// β�巨2
void link_add_tail2(node *head, dataType new_data)
{
	link_add(head->prev, new_data);
}

// �������
void link_show(node *head)
{
	node *pos;
	// ����������
	for (pos = head->next; pos != head; pos = pos->next)
		printf("%d, %d, %s ", pos->data.x, pos->data.y, pos->data.filename);
	printf("\n");
}

// ǰ�����
void link_show_prev(node *head)
{
	node *pos;
	for (pos = head->prev; pos != head; pos = pos->prev)
		printf("%d ", pos->data);
	printf("\n");
}

// �������
void link_free(node *head)
{
	// �ж������Ƿ�Ϊ��
	if (head->next == head)
	{
		perror("head is fount!!");
		return;
	}
	node *pos = head->prev;
	while (pos != head)
	{
		node *temp = pos->prev;
		free(pos);
		pos = temp;
	}
	head->next = head;
	head->prev = head;
}
