#pragma once

#include <stdlib.h>

typedef struct{
	ListNode *next;
	void *data;
}ListNode;

typedef struct{
	ListNode *head;
	int count;
}List;

int List_Init(List *);
int List_Insert(List *, const void *, const size_t);
int List_Delete(List *, const void *, const size_t);
int List_Find(List *, const void *, const size_t);
int List_DeleteTheEarliest(List *);
int List_DeleteTheLatest(List *);
void *List_ShowTheEarliest(List *, int);
	// 返回数据指针，强制转换为对应类型后使用
void *List_ShowTheLatest(List *, int);
	// 返回数据指针，强制转换为对应类型后使用
