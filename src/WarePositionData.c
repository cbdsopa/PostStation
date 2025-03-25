#include "WarePositionData.h"

WarePostionData WarePositionCreate(int ID, int SizeType, int empty, PackageData package){
	WarePostionData ware;
	ware.ID = ID;
	ware.SizeType = SizeType;
	ware.empty = empty;
	ware.package = package;
	return ware;
}