// 欧阳承风

#include "FileManage.h"
#include <stdio.h>
#include <windows.h>

FILE *UserOutput(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_log.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's log open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}

int UserOutClean(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_log.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's log open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserInfoSave(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_data.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's data open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}

int UserInfoClean(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_data.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's data open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserPackageInfoSave(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_package.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's package open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}
int UserPackageInfoClear(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_package.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's package open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserVehicleInfoSave(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_vehicle.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's vehicle open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}

int UserVehicleInfoClear(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_vehicle.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's vehicle open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *UserMessageInfoSave(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_message.txt", PhoneNumber);
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's message open failed.\n", PhoneNumber);
		return NULL;
	}
	return file;
}
int UserMessageInfoClear(long long PhoneNumber){
	char path[512];
	sprintf(path, "../data/user/%lld_message.txt", PhoneNumber);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(STDERR, "Error: file %lld's message open failed.\n", PhoneNumber);
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *WarePostionSave(){
	char path[512];
	sprintf(path, "../data/warehouse/position_data.txt");
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(STDERR, "Error: file warehousePostion data open failed.\n");
		return NULL;
	}
	return file;
}

int WarePositionClear(){
	char path[512];
	sprintf(path, "../data/warehouse/position_data.txt");
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(STDERR, "Error: file warehousePostion data open failed.\n");
		return -1;
	}
	fclose(file);
	return 0;
}

FILE *WarePackageSave(){
	char path[512];
	sprintf(path, "../data/warehouse/package_data.txt");
	FILE *file = fopen(path, "a");
	if(file == NULL){
		fprintf(STDERR, "Error: file warehousePackage data open failed.\n");
		return NULL;
	}
	return file;
}

int WarePackageClear(){
	char path[512];
	sprintf(path, "../data/warehouse/package_data.txt");
	FILE *file = fopen(path, "w");
	if(file == NULL){
		fprintf(STDERR, "Error: file warehousePackage data open failed.\n");
		return -1;
	}
	fclose(file);
	return 0;
}


int delete_all_files(const char *dir_path) {
    WIN32_FIND_DATA find_data;
    HANDLE h_find;
    char search_path[512];
    snprintf(search_path, 512, "%s\\*", dir_path);
    h_find = FindFirstFile(search_path, &find_data);
    if(h_find == INVALID_HANDLE_VALUE){
        printf("无法打开目录 (错误码: %lu)\n", GetLastError());
        return 0;
    }
    do{
        if(strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0){
            continue;
        }
        char file_path[512];
        snprintf(file_path, 512, "%s\\%s", dir_path, find_data.cFileName);
        if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ){
            if (DeleteFile(file_path) == 0) {
                printf("删除文件失败 (错误码: %lu)\n", GetLastError() );
                FindClose(h_find);
                return 0;
            }
            //printf("已删除: %s\n", file_path);
        }
    }while(FindNextFile(h_find, &find_data) != 0);
    FindClose(h_find);
    return 1;
}
