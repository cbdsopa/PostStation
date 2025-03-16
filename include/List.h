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
