#pragma once

#include "List.h"

typedef struct{
	long long PhoneNumber;
	// 1xx - xxxx - xxx
	char name[20];
	// 1 ~ 20 个字符
	char password[20];
	// 1 ~ 20 个字符
	int UserStatus;
	/*
		1 学生
		2 老人
		4 退役军人
		8 会员
		16 管理员
		32 快递员
		64 忙碌
	*/
	int TransStatus;
	/*
		1 冷藏
		2 飞机
	*/
	int TransSize;
	// 0 | 1 ~ 500
	int PackageCount;
	// 超过 30 后不再计数
	int level;
	// 1 ~ 3 
	List package;
	List vehicle;
}UserData;

UserData CreateUser(long long, char*, char*, int, int, int);
