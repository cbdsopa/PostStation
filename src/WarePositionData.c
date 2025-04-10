// 欧阳承风
#include "WarePositionData.h"
#include <string.h>

WarePostionData WarePositionCreate(int ID, int SizeType, int empty, PackageData package){
	WarePostionData ware;
	memset(&ware, 0, sizeof(ware) );
	ware.ID = ID;
	ware.SizeType = SizeType;
	ware.empty = empty;
	ware.package = package;
	return ware;
}