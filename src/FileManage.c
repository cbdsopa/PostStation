#include "FileManage.h"
#include <stdio.h>

FILE *UserOutput(long long PhoneNumber){
	char path[30];
	sprintf(path, "data/user/%lld/log.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's log open failed.\n", PhoneNumber);
		return -1;
	}
	return file;
}

int UserOutClean(long long PhoneNumber){
	char path[30];
	sprintf(path, "data/user/%lld/log.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's log open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserInfoSave(long long PhoneNumber){
	char path[30];
	sprintf(path, "data/user/%lld/data.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's data open failed.\n", PhoneNumber);
		return -1;
	}
	return file;
}

int UserInfoClean(long long PhoneNumber){
	char path[30];
	sprintf(path, "data/user/%lld/data.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(stderr, "Error: file %lld's data open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}
