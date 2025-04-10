// 欧阳承风

#include "List.h"
#include <stdlib.h>
#include <string.h>
#include "PackageData.h"
#include "FileManage.h"

List List_Create(){
	List list;
	list.head = NULL;
	list.count = 0;
	return list;
}

int List_Insert(List *list, const void *data, const size_t siz){
	if(list == NULL) return -1;
	if(data == NULL) return -2;
	ListNode *newnode = (ListNode *)malloc(sizeof(ListNode) );
	newnode->data = (void *)malloc(siz);
	memcpy(newnode->data, data, siz);
	newnode->next = NULL;
	if(list->head == NULL){
		list->head = newnode;
	}else{
		ListNode *now = list->head;
		for(; now->next != NULL; now = now->next);
		now->next = newnode;
	}
	++list->count;
	return 0;
}

int List_Delete(List *list, const void *data, const size_t siz){
	if(list == NULL) return -1;
	if(data == NULL) return -2;
	ListNode *now = list->head, *last = NULL;
	while(now != NULL){
		if(memcmp(now->data, data, siz) == 0){
			if(last == NULL){
				--list->count;
				list->head = now->next;
				free(now);
				now = list->head;
			}else{
				last->next = now->next;
				free(now);
				now = last->next;
			}
		}else{
			last = now;
			now = now->next;
		}
	}
	return 0;
}

int List_Find(List *list, const void *data, const size_t siz){
	if(list == NULL) return -1;
	if(data == NULL) return -2;
	ListNode *now = list->head;
	while(now != NULL){
		if(memcmp(now->data, data, siz) == 0){
			return 1;
		}
		now = now->next;
	}
	return 0;
}

int List_Find_Package(List *list, const void *data, const size_t siz){
	if(list == NULL) return -1;
	if(data == NULL) return -2;
	ListNode *now = list->head;
	while(now != NULL){
		PackageData package1 = *(PackageData *)now->data;
		PackageData package2 = *(PackageData *)data;
		strcpy(package2.PackageCode, package1.PackageCode);
		if(memcmp(&package1, &package2, sizeof(PackageData) ) == 0){
			return 1;
		}
		now = now->next;
	}
	return 0;
}

int List_DeleteTheEarliest(List *list){
	if(list == NULL) return -1;
	if(list->count < 1) return 0;
	ListNode *temp = list->head;
	free(temp);
	list->head = list->head->next;
	return 1;
}

int List_DeleteTheLatest(List *list){
	if(list == NULL) return -1;
	if(list->count < 1) return 0;
	ListNode *now = list->head;
	while(now->next != NULL){
		now = now->next;
	}
	free(now->next);
	now->next = NULL;
	return 1;
}

void *List_ShowTheEarliest(List *list, int index){
	if(list == NULL) return NULL;
	if(list->count < index || index < 1) return NULL;
	ListNode *now = list->head;
	int count = 0;
	while(now != NULL){
		++count;
		if(count == index){
			return now->data;
		}
		now = now->next;
	}
	return NULL;
}

void *List_ShowTheLatest(List *list, int index){
	if(list == NULL) return NULL;
	if(list->count < index || index < 1) return NULL;
	ListNode *now = list->head;
	int count = 0;
	while(now != NULL){
		if(list->count - count == index){
			return now->data;
		}
		++count;
		now = now->next;
	}
	return NULL;
}
#include <stdio.h>
void List_Destroy(List *list){
	if(list == NULL) return;
	ListNode *now = list->head, *temp = NULL;
	while(now){
		temp = now;
		now = now->next;
		free(temp);
	}
	list->count = 0;
	list->head = NULL;
}
