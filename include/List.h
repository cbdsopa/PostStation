// 欧阳承风
#pragma once

#include <stdlib.h>

typedef struct ListNode{
	struct ListNode *next;
	void *data;
}ListNode;

typedef struct List{
	struct ListNode *head;
	int count;
}List;

List List_Create();
int List_Insert(List *, const void *, const size_t);
// 输入具体数据和数据的大小，插入对应的数据（<0异常）
int List_Delete(List *, const void *, const size_t);
// 输入具体数据和数据的大小，删除对应的数据（<0异常）
int List_Find(List *, const void *, const size_t);
int List_Find_Package(List *, const void *, const size_t);
// 输入具体数据和数据的大小，返回对应的数据是否存在（0不存在，1存在，<0异常）
int List_DeleteTheEarliest(List *);
// 输入位置索引 i，删除最早的第 i 位（<0异常）
int List_DeleteTheLatest(List *);
// 输入位置索引 i，删除最晚的第 i 位（<0异常）
void *List_ShowTheEarliest(List *, int);
// 输入位置索引 i，返回最早的第 i 位的数据指针，强制转换为对应类型后使用
void *List_ShowTheLatest(List *, int);
// 输入位置索引 i，返回最晚的第 i 位的数据指针，强制转换为对应类型后使用
void List_Destroy(List *);


extern List ManagerAvailable, WarePackage, WarePosition, OutPackage;
