#include "../include/head.h"

// 初始化
node *link_init()
{
	node *p = malloc(sizeof(node));
	// 判断创建是否成功
	if (!p)
	{
		printf("malloc full\n");
		return NULL;
	}
	// 数据域与指针域的初始化
	bzero(&p->data, sizeof(dataType));
	p->prev = p;
	p->next = p;
	return p;
}

// 头插法
void link_add(node *head, dataType new_data)
{
	node *new = link_init();
	// 数据位初始化
	new->data = new_data;

	// 新节点的前驱指针域指向前驱节点
	new->prev = head;
	// 新节点的后继指针域指向前驱节点的下一个节点
	new->next = head->next;
	// 前驱节点的下一个节点的前驱指针域指向新节点
	head->next->prev = new;
	// 前驱节点的后继指针域指向新节点
	head->next = new;
}

// 头插法2
void link_add2(node *head, dataType new_data)
{
	node *new = link_init();
	// 数据位初始化
	new->data = new_data;
	node *top = head->next;

	// 新节点的前驱指针域指向前驱节点
	new->prev = top;
	// 新节点的后继指针域指向前驱节点的下一个节点
	new->next = top->next;
	// 前驱节点的下一个节点的前驱指针域指向新节点
	top->next->prev = new;
	// 前驱节点的后继指针域指向新节点
	top->next = new;
}

// 尾插法2
void link_add_tail2(node *head, dataType new_data)
{
	link_add(head->prev, new_data);
}

// 后序遍历
void link_show(node *head)
{
	node *pos;
	// 遍历数据域
	for (pos = head->next; pos != head; pos = pos->next)
		printf("%d, %d, %s ", pos->data.x, pos->data.y, pos->data.filename);
	printf("\n");
}

// 前序遍历
void link_show_prev(node *head)
{
	node *pos;
	for (pos = head->prev; pos != head; pos = pos->prev)
		printf("%d ", pos->data);
	printf("\n");
}

// 链表清空
void link_free(node *head)
{
	// 判断链表是否为空
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
