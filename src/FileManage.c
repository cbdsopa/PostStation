#include "FileManage.h"
#include <stdio.h>

FILE *UserOutput(long long PhoneNumber){
	char path[33];
	sprintf(path, "../data/user/%lld/log.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's log open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}

int UserOutClean(long long PhoneNumber){
	char path[33];
	sprintf(path, "../data/user/%lld/log.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's log open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserInfoSave(long long PhoneNumber){
	char path[33];
	sprintf(path, "../data/user/%lld/data.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's data open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}

int UserInfoClean(long long PhoneNumber){
	char path[33];
	sprintf(path, "../data/user/%lld/data.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's data open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserPackageInfoSave(long long PhoneNumber){
	char path[36];
	sprintf(path, "../data/user/%lld/package.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's data open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}
int UserPackageInfoClear(long long PhoneNumber){
	char path[36];
	sprintf(path, "../data/user/%lld/package.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's package open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserVehicleInfoSave(long long PhoneNumber){
	char path[36];
	sprintf(path, "../data/user/%lld/vehicle.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's data open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}

int UserVehicleInfoClear(long long PhoneNumber){
	char path[36];
	sprintf(path, "../data/user/%lld/vehicle.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's vehicle open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *WarehouseInfoSave(){
	char path[36];
	sprintf(path, "../data/warehouse/data.txt");
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(stderr, "Error: file warehouse data open failed.\n");
		return NULL;
	}
	return file;
}

int WarehouseInfoClear(){
	char path[36];
	sprintf(path, "../data/warehouse/data.txt");
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(stderr, "Error: file warehouse data open failed.\n");
		return -1;
	}
	fclose(file);
	return 0;
}