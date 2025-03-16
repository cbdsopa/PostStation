#include "List.h"
#include <stdlib.h>

int List_Init(List *list){
	if(list == NULL) return 1;
	list->head = NULL;
	list->count = 0;
	return 0;
}
int List_Insert(List *list, const void *data, const size_t siz){
	if(list == NULL) return -1;
	if(data == NULL) return -2;
	ListNode *newnode = (ListNode *)malloc(sizeof(ListNode) );
	newnode->data = (void *)malloc(siz);
	memcpy(newnode->data, data, siz);
	if(list->head == NULL){
		newnode->next = NULL;
		list->head = newnode;
	}else{
		newnode->next = list->head;
		list->head = newnode;
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
