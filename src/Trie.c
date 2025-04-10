// 欧阳承风
#include "Trie.h"
#include <stdlib.h>
#include <string.h>
#include "UserData.h"

Trie Trie_Create(){
	Trie trie;
	trie.root = NULL;
	return trie;
}

TrieNode *TrieNode_Create(){
	TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode) );
	node->child[0] = node->child[1] = NULL;
	node->data = NULL;
	return node;
}

int Trie_Insert(Trie *trie, long long PhoneNumber, const void *data, const size_t siz){
	if(trie == NULL) return -1;
	if(trie->root == NULL){
		trie->root = TrieNode_Create();
	}
	TrieNode *p = trie->root;
	for(int index = 33; index >= 0; --index){
		int bit = PhoneNumber >> index & 1;
		if(p->child[bit] == NULL){
			p->child[bit] = TrieNode_Create();
		}
		p = p->child[bit];
	}
	if(p->data == NULL) p->data = (void *)malloc(siz);
	if(data == NULL){
		if(p->data != NULL) free(p->data);
		p->data = NULL;
	}else memcpy(p->data, data, siz);
	return 0;
}

void *Trie_Find(Trie *trie, long long PhoneNumber){
	if(trie->root == NULL) return NULL;
	TrieNode *p = trie->root;
	for(int index = 33; index >= 0; --index){
		int bit = PhoneNumber >> index & 1;
		if(p->child[bit] == NULL){
			return NULL;
		}
		p = p->child[bit];
	}
	return p->data;
}

void Trie_User_Destroy(TrieNode *p){
	if(p == NULL){
		return;
	}
	if(p->child[0] != NULL) Trie_User_Destroy(p->child[0]);
	if(p->child[1] != NULL) Trie_User_Destroy(p->child[1]);
	if(p->data != NULL){
		UserData *data = (UserData *)p->data;
		List_Destroy(&data->package);
		List_Destroy(&data->message);
		List_Destroy(&data->vehicle);
		free(p->data);
	}
	free(p); 
}
