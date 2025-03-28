#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

#include "FileManage.h"
#include "UserData.h"
#include "Trie.h"
#include "List.h"
#include "user.h"
#include "cost.h"
#include "WareInOut.h"
#include "WarePositionData.h"
#include "Transport.h"
#include "StorageRack.h"
#include "PackOut.h"
#include "UserStatus.h"
#include "restart.h"
#include "VehicleSave.h"

int InputType;
FILE *STDIN, *STDOUT, *STDERR;
Trie UserManager;
List ManagerAvailable, WarePackage, WarePosition;

int main(int argc, char **argv){
	setlocale(LC_ALL, "zh_CN.utf8");
	system("chcp 65001 & cls");
	// 使终端支持 UTF-8
	system("cls");
	printf("请输入读入方式 (0 键盘 / 1 文件)\n");
	scanf("%2d%*[^\n]", &InputType);
	while(InputType != 0 && InputType != 1){
		printf("输入有误，请重新输入读入方式 (0 键盘 / 1 文件)\n");
		scanf("%2d%*[^\n]", &InputType);
	}
	STDIN = InputType ? fopen("../data/system/input.txt", "r") : stdin; 
	STDOUT = InputType ? fopen("../data/system/log.txt", "w") : stdout;
	STDERR = fopen("../data/system/error_log.txt", "w");
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


	WarePosition = List_Create();
	// 加载仓库货架信息


	/* 用户操作 */
	while(1){
		/* 登录和注册 */
		if(!InputType) system("cls");
		fprintf(STDOUT, "您好！想要退出(0)？登录(1)？注册(2)?\n");
		int Oper; fscanf(STDIN, "%2d%*[^\n]", &Oper);
		while(Oper != 0 && Oper != 1 && Oper != 2){
			fprintf(STDOUT, "输入不合法，请再次输入\n想要退出(0)？登录(1)？注册(2)?\n");
			fscanf(STDIN, "%2d%*[^\n]", &Oper);
		}
		if(Oper == 0) break;
		UserData *user;
		if(Oper == 1){
			user = user_login();
			if(user == NULL){
				if(!InputType) Sleep(2000);
				continue;
			}
		}
		if(Oper == 2) user = user_register(); 
		/*
			password need to be fixed:
				1. can't too long
				2. can't have special character
		*/
		FILE* userfile = UserOutput(user->PhoneNumber);
		
		if(!InputType) system("cls");
		fprintf(STDOUT, "欢迎回来！%s\n", user->name);
		fprintf(userfile, "欢迎回来！%s\n", user->name);
		if(!InputType) Sleep(2000);

		/* 具体操作 */
		while(1){
			if(!InputType) system("cls");
			fprintf(STDOUT, "请输入想进行操作的对应标号：\n");
			fprintf(userfile, "请输入想进行操作的对应标号：\n");
			fprintf(STDOUT, "0.登出\n1.取货\n2.发货\n3.查看未读信息\n4.查询未领包裹\n5.修改忙碌状态\n");
			fprintf(userfile, "0.登出\n1.取货\n2.发货\n3.查看未读信息\n4.查询未领包裹\n5.修改忙碌状态\n");
			if(user->UserStatus & 16){
				fprintf(STDOUT, "6.增减货架\n");
				fprintf(userfile, "6.增减货架\n");
			}
			if(user->UserStatus & 32){
				fprintf(STDOUT, "7.货物运输\n8.异常重发\n9.货物运达\n10.发货接收\n");
				fprintf(userfile, "7.货物运输\n8.异常重发\n9.货物运达\n10.发货接收\n");
			}
			fprintf(STDOUT, "11.注销\n");
			fprintf(userfile, "11.注销\n");

			int opt;
			fscanf(STDIN, "%3d%*[^\n]", &opt);
			while(
				opt > 11 || opt < 0 || (!(user->UserStatus & 16) && opt == 6) || 
				(!(user->UserStatus & 32) && (7 <= opt && opt <= 10) )
			){
				fprintf(STDOUT, "输入不合法，请重新输入想进行操作的对应标号：\n");
				fprintf(userfile, "输入不合法，请重新输入想进行操作的对应标号：\n");
				fscanf(STDIN, "%3d%*[^\n]", &opt);
			}
			if(opt == 0){
				fprintf(STDOUT, "已退出账号\n");
				fprintf(userfile, "已退出账号\n");
				if(!InputType) Sleep(2000);
				break;
			}
			if(opt == 11){
				fprintf(STDOUT, "确定要注销吗？(0 否 / 1 是)\n");
				fprintf(userfile, "确定要注销吗？(0 否 / 1 是)\n");
				fscanf(STDIN, "%2d%*[^\n]", &opt);
				while(opt != 0 && opt != 1){
					fprintf(STDOUT, "请输入 0 或 1\n");
					fprintf(userfile, "请输入 0 或 1\n");
					fscanf(STDIN, "%2d%*[^\n]", &opt);
				}
				if(opt == 1){
					user_logout(user);
					if(!InputType) Sleep(2000);
					break;
				}else{
					fprintf(STDOUT, "已取消\n");
					fprintf(userfile, "已取消\n");
					if(!InputType) Sleep(2000);
				}
				continue;
			}
			if(user->UserStatus & 64 && opt != 5){
				fprintf(STDOUT, "请先取消忙碌状态再进行操作。\n");
				fprintf(userfile, "请先取消忙碌状态再进行操作。\n");
				if(!InputType) Sleep(2000);
				continue;
			}

			if(opt == 1){
				user_packageout(user); // need check
				if(!InputType) Sleep(2000);
			}
			if(opt == 2){
				OutPut(user); // need check
				if(!InputType) Sleep(2000);
			}
			if(opt == 3){
				
			}
			if(opt == 4){
				user_check(user); // need check
				if(!InputType) system("pause");
			}
			if(opt == 5){
				ChangeStatus(user);
				if(!InputType) Sleep(2000);
			}
			if(opt == 6){
				IncreaseRack(*user); // need check
				if(!InputType) Sleep(2000);
			}
			if(opt == 7){
				PackageData package = goodtrans(*user); // need check
				UserData *receiver; // buffer fix
				messagecost(*user, *receiver, package); // need check
				if(!InputType) Sleep(2000);
			}
			if(opt == 8){
				reputout(*user);
				if(!InputType) Sleep(2000);
			}
			if(opt == 9){

			}
			if(opt == 10){

			}
		}
		
		fclose(userfile);
	}

	/* 保存数据 */

	foreachpro(33, UserManager.root);

	Trie_User_Destroy(UserManager.root);

	if(InputType){
		fclose(STDIN);
		fclose(STDOUT);
	}
	fclose(STDERR);
	system("cls");
	printf("运行终了\n");
	system("pause");
	return 0;
}
