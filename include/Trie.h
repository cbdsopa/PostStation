#pragma once
#include <stdlib.h>

struct TrieNode{
	struct TrieNode *child[2];
	void *data;
};

struct Trie{
	struct TrieNode *root;
	int count;
};

struct Trie Trie_Create();
int Trie_Insert(struct Trie *, long long, const void *, const size_t);
void *Trie_Find(struct Trie *, long long);
