// 欧阳承风
#pragma once

#include "List.h"

typedef struct UserData{
	long long PhoneNumber;
	// 1xx - xxxx - xxx
	char name[31];
	// 1 ~ 10 个字符
	char password[21];
	// 1 ~ 20 个英文字符
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
	List message;
}UserData;

UserData CreateUser(long long, char*, char*, int, int, int);
