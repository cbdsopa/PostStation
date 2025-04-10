// 吉庆喆
#pragma once
#include"UserData.h"
#include "FileManage.h"
#include "Trie.h"
#include"PackageData.h"
void save_user_info(UserData*);
void save_user_package(UserData*);
void save_user_message(UserData*);
void file_user_save(int t, TrieNode *p);