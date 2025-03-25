#include <stdio.h>
#include <windows.h>
#include "FileManage.h"

int InputType;
FILE *STDIN, *STDOUT;

int main(int argc, char **argv){
	system("chcp 65001 & cls");
	// 使终端支持 UTF-8
	system("cls");
	printf("请输入读入方式 (0 键盘 / 1 文件)\n");
	scanf("%d", &InputType);
	STDIN = InputType ? fopen("../data/system/input.txt", "r") : stdin; 
	STDOUT = InputType ? fopen("../data/system/log.txt", "w") : stdout;
	if(InputType){
		system("cls");
		printf("运行中...\n");
	}

	while(1){
		
	}

	if(InputType){
		fclose(STDIN);
		fclose(STDOUT);
	}
	system("cls");
	printf("运行终了\n");
	return 0;
}
