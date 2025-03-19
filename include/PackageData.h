#pragma once

typedef struct{
	long long PhoneNumber;
	// 1xx - xxxx - xxx
	char name[20];
	// 1 - 19 个字符
	double distance;
	// (0, 10000] km
	double volume;
	/*
		(0, 120000] cm ^ 3
		(0, 36000] cm ^ 3 为小型货物
		(36000, 60000] cm ^ 3 为中型货物
		(60000, 120000] cm ^ 3 为大型货物
	*/
	double weight;
	// (0, 200] kg ，大于 100 kg 算超重
	char PlaceFrom[20], *PlaceTo[20];
	// 1 - 19 个字符
	int status;
	/*
		1 贵重
		2 需要保鲜
		4 紧急
	*/

}PackageData;

PackageData CreatePackage(long long, char*, double, double, double, char*, char*, int);
