#pragma once

#include "PackageData.h"

typedef struct WarePostionData{
	int ID;
	int SizeType;
	// 0-小 1-中 2-大 3-贵重
	int empty;
	// 是否为空
	PackageData package;
	// 存储的包裹
}WarePostionData;

WarePostionData WarePositionCreate(int, int, int, PackageData);