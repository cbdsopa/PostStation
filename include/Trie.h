#pragma once
#include <stdlib.h>
#include <List.h>

typedef struct TrieNode{
	struct TrieNode *child[2];
	void *data;
	List buf;
}TrieNode;

typedef struct Trie{
	struct TrieNode *root;
}Trie;

Trie Trie_Create();
int Trie_Insert(Trie *, long long, const void *, const size_t);
// 传入用户手机号、对应数据及其大小，将对应用户加入其中
void *Trie_Find(Trie *, long long);
void Trie_User_Destroy(TrieNode *);

extern Trie UserManager;