#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "FileManage.h"
#include "UserData.h"
#include "Trie.h"
#include "List.h"

int InputType;
FILE *STDIN, *STDOUT;
Trie UserManager;
List ManagerAvailable, WarePackage, WarePostion;

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

	/* 初始化 */

	srand(time(0) + clock() );
	
	UserManager = Trie_Create();
	// 加载用户信息


	ManagerAvailable = List_Create();
	// 加载管理员信息


	WarePackage = List_Create();
	// 加载仓库货物信息


	WarePostion = List_Create();
	// 加载仓库货架信息


	/* 用户操作 */
	while(1){
		/* 登录和注册 */
		if(!InputType) system("cls");
		fprintf(STDOUT, "您好！想要退出(0)？登录(1)？注册(2)?\n");
		int Oper; fscanf(STDIN, "%d", &Oper);
		while(Oper != 0 && Oper != 1 && Oper != 2){
			fprintf(STDOUT, "输入不合法，请再次输入\n想要退出(0)？登录(1)？注册(2)?\n");
			fscanf(STDIN, "%d", &Oper);
		}
		if(Oper == '0') break;
		UserData user;



		FILE* userfile = UserOutput(user.PhoneNumber);
		
		if(!InputType) system("cls");
		fprintf(STDOUT, "欢迎回来！%s！\n", user.name);
		fprintf(userfile, "欢迎回来！%s！\n", user.name);
		Sleep(1000);

		/* 具体操作 */
		while(1){
			if(!InputType) system("cls");
			fprintf(STDOUT, "请输入想进行的操作：\n");
			fprintf(userfile, "请输入想进行的操作：\n");


		}
		

	}

	/* 保存数据 */




	if(InputType){
		fclose(STDIN);
		fclose(STDOUT);
	}
	system("cls");
	printf("运行终了\n");
	return 0;
}
