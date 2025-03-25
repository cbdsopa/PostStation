#include "Trie.h"
#include <stdlib.h>
#include <string.h>

Trie Trie_Create(){
	Trie trie;
	trie.root = NULL;
	trie.count = 0;
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
	if(data == NULL) return -2;
	if(trie->root == NULL){
		trie->count = 0;
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
	p->data = (void *)malloc(siz);
	memcpy(p->data, data, siz);
	++trie->count;
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
