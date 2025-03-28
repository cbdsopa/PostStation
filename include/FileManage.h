#pragma once

#include <stdio.h>

extern int InputType;
extern FILE *STDIN, *STDOUT, *STDERR;

FILE *UserOutput(long long);
int UserOutClean(long long);
FILE *UserInfoSave(long long);
int UserInfoClean(long long);
FILE *UserPackageInfoSave(long long);
int UserPackageInfoClear(long long);
FILE *UserVehicleInfoSave(long long);
int UserVehicleInfoClear(long long);
FILE *UserMessageInfoSave(long long);
int UserMessageInfoClear(long long);
FILE *WarePostionSave();
int WarePositionClear();
FILE *WarePackageSave();
int WarePackageClear();
