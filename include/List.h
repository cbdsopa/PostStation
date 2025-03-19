#pragma once

#include <stdlib.h>

struct ListNode{
	struct ListNode *next;
	void *data;
};

struct List{
	struct ListNode *head;
	int count;
};

struct List List_Create();
int List_Insert(struct List *, const void *, const size_t);
int List_Delete(struct List *, const void *, const size_t);
int List_Find(struct List *, const void *, const size_t);
int List_DeleteTheEarliest(struct List *);
int List_DeleteTheLatest(struct List *);
void *List_ShowTheEarliest(struct List *, int);
	// 返回数据指针，强制转换为对应类型后使用
void *List_ShowTheLatest(struct List *, int);
	// 返回数据指针，强制转换为对应类型后使用
