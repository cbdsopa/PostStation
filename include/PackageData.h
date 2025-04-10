// 欧阳承风

#pragma once

#include <stddef.h>

typedef struct PackageData{
	long long PhoneNumber;
	// 1xx - xxxx - xxx
	char name[31];
	// 1 - 10 个字符
	int distance;
	// * 100 后 | (0, 10000] km
	int volume;
	/*
		* 100 后 |
		(0, 120000] cm ^ 3
		(0, 36000] cm ^ 3 为小型货物
		(36000, 60000] cm ^ 3 为中型货物
		(60000, 120000] cm ^ 3 为大型货物
	*/
	int weight;
	// * 100 后 | (0, 200] kg ，大于 100 kg 算超重
	char PlaceFrom[61], PlaceTo[61];
	// 1 - 20 个字符
	int status;
	/*
		1 贵重
		2 需要保鲜
		4 紧急
	*/
	int posID;
	char PackageCode[9];
	// 8 个字符，由英文大小写字符和数字组成
}PackageData;

PackageData CreatePackage(long long, char*, int, int, int, char*, char*, int);
