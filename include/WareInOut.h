// 欧阳承风

#pragma once

#include "UserData.h"
#include "PackageData.h"

PackageData WareIn(List *, PackageData, List *, List *);
//传入空闲管理员列表，入库包裹信息，仓库货架列表，仓库货物列表，返回包裹存放位置

int WareOut(List *, PackageData, List *, List *);
//传入空闲管理员列表，出库包裹信息，仓库货架列表，仓库货物列表