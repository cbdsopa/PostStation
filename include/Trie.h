#pragma once
#include <stdlib.h>

typedef struct{
	TrieNode *child[2];
	void *data;
}TrieNode;

typedef struct{
	TrieNode *root;
	int count;
}Trie;

int Trie_Init(Trie *);
int Trie_Insert(Trie *, long long, const void *, const size_t);
void *Trie_Find(Trie *, long long);
