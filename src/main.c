// 欧阳承风

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#include <string.h>

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
#include "userfile.h"
#include "PackageArrive.h"

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
	char buf[20];
	scanf("%2s%*[^\n]", buf); 
	while((buf[0] != '0' && buf[0] != '1') || strlen(buf) > 1){
		printf("输入有误，请重新输入读入方式 (0 键盘 / 1 文件)\n");
		scanf("%2s%*[^\n]", buf);
	}
	InputType = atoi(buf);
	STDIN = InputType ? fopen("../data/system/input.txt", "r") : stdin; 
	STDOUT = InputType ? fopen("../data/system/log.txt", "w") : stdout;
	STDERR = fopen("../data/system/error_log.txt", "w");
	if(InputType){
		system("cls");
		printf("运行中...\n");
	}

	if(!InputType) system("cls");
	printf("要清空保存的数据吗？(0 否 / 1 是)\n");
	fscanf(STDIN, "%2s%*[^\n]", buf); 
	while((buf[0] != '0' && buf[0] != '1') || strlen(buf) > 1){
		fprintf(STDOUT, "输入有误，请重新输入读入方式 (0 键盘 / 1 文件)\n");
		scanf("%2s%*[^\n]", buf);
	}
	int ClearOrNot = atoi(buf);
	if(ClearOrNot){
		delete_all_files("..\\data\\user");
		delete_all_files("..\\data\\warehouse");
		printf("已清空。\n");
		if(!InputType) system("pause");
	}

	/* 初始化 */

	srand(time(0) + clock() );
	
	UserManager = Trie_Create();
	ManagerAvailable = List_Create();
	// 加载用户信息

	FILE *userlist = fopen("../data/user/userlist.txt", "r");
	while(1){
		long long phone; 
		if(fscanf(userlist, "%lld", &phone) == EOF) break;
		UserOutClean(phone);

		char path[60];
		sprintf(path, "../data/user/%lld_data.txt", phone);
		FILE *userdata = fopen(path, "r");
		UserData data;
		memset(&data, 0, sizeof(data) );
		data.message = List_Create();
		data.package = List_Create();
		data.vehicle = List_Create();
		fscanf(userdata, "%lld", &data.PhoneNumber);
		fscanf(userdata, "%s", data.name);
		fscanf(userdata, "%s", data.password);
		fscanf(userdata, "%d", &data.UserStatus);
		fscanf(userdata, "%d", &data.TransStatus);
		fscanf(userdata, "%d", &data.TransSize);
		fscanf(userdata, "%d", &data.PackageCount);
		fscanf(userdata, "%d", &data.level);
		fclose(userdata);

		sprintf(path, "../data/user/%lld_package.txt", phone);
		userdata = fopen(path, "r");
		while(1){
			PackageData package;
			memset(&package, 0, sizeof(package) );
			if(fscanf(userdata, "%lld", &package.PhoneNumber) == EOF)
				break;
			fscanf(userdata, "%s", package.name);
			fscanf(userdata, "%d", &package.distance);
			fscanf(userdata, "%d", &package.volume);
			fscanf(userdata, "%d", &package.weight);
			fscanf(userdata, "%s", package.PlaceFrom);
			fscanf(userdata, "%s", package.PlaceTo);
			fscanf(userdata, "%d", &package.status);
			fscanf(userdata, "%d", &package.posID);
			fscanf(userdata, "%s", package.PackageCode);
			List_Insert(&data.package, &package, sizeof(package) );
		}
		fclose(userdata);

		sprintf(path, "../data/user/%lld_vehicle.txt", phone);
		userdata = fopen(path, "r");
		while(1){
			PackageData package;
			memset(&package, 0, sizeof(package) );
			if(fscanf(userdata, "%lld", &package.PhoneNumber) == EOF)
				break;
			fscanf(userdata, "%s", package.name);
			fscanf(userdata, "%d", &package.distance);
			fscanf(userdata, "%d", &package.volume);
			fscanf(userdata, "%d", &package.weight);
			fscanf(userdata, "%s", package.PlaceFrom);
			fscanf(userdata, "%s", package.PlaceTo);
			fscanf(userdata, "%d", &package.status);
			fscanf(userdata, "%d", &package.posID);
			fscanf(userdata, "%s", package.PackageCode);
			List_Insert(&data.vehicle, &package, sizeof(package) );
		}
		fclose(userdata);

		sprintf(path, "../data/user/%lld_message.txt", phone);
		userdata = fopen(path, "r");
		while(1){
			char mes[100];
			if(fscanf(userdata, "%s", mes) == EOF) break;
			List_Insert(&data.message, mes, sizeof(mes) );
		}
		fclose(userdata);
		Trie_Insert(&UserManager, phone, &data, sizeof(data) );
		if(data.UserStatus & 16) List_Insert(&ManagerAvailable, &data, sizeof(data) );
	}
	fclose(userlist);

	if(ManagerAvailable.count == 0){
		UserData data;
		memset(&data, 0, sizeof(data) );
		data.PhoneNumber = 10000000000ll;
		strcpy(data.name, "Admin");
		strcpy(data.password, "114514");
		data.UserStatus = 16;
		data.TransStatus = 0;
		data.TransSize = 0;
		data.PackageCount = 0;
		data.level = 1;
		data.package = List_Create();
		data.vehicle = List_Create();
		data.message = List_Create();
		Trie_Insert(&UserManager, data.PhoneNumber, &data, sizeof(data) );
		List_Insert(&ManagerAvailable, &data, sizeof(data) );
	}

	WarePackage = List_Create();
	// 加载仓库货物信息
	char path[60];
	sprintf(path, "../data/warehouse/package_data.txt");
	FILE *packdata = fopen(path, "r");
	while(1){
		PackageData data;
		memset(&data, 0, sizeof(data) );
		if(fscanf(packdata, "%lld", &data.PhoneNumber) == EOF)
			break;
		fscanf(packdata, "%s", data.name);
		fscanf(packdata, "%d", &data.distance);
		fscanf(packdata, "%d", &data.volume);
		fscanf(packdata, "%d", &data.weight);
		fscanf(packdata, "%s", data.PlaceFrom);
		fscanf(packdata, "%s", data.PlaceTo);
		fscanf(packdata, "%d", &data.status);
		fscanf(packdata, "%d", &data.posID);
		fscanf(packdata, "%s", data.PackageCode);
		List_Insert(&WarePackage, &data, sizeof(data) );
	}
	fclose(packdata);

	WarePosition = List_Create();
	// 加载仓库货架信息
	sprintf(path, "../data/warehouse/position_data.txt");
	FILE *postdata = fopen(path, "r");
	while(1){
		WarePostionData data;
		memset(&data, 0, sizeof(data) );
		if(fscanf(postdata, "%d", &data.ID) == EOF)
			break;
		fscanf(postdata, "%d", &data.SizeType);
		fscanf(postdata, "%d", &data.empty);
		if(!data.empty){
			fscanf(packdata, "%lld", &data.package.PhoneNumber);
			fscanf(postdata, "%s", data.package.name);
			fscanf(postdata, "%d", &data.package.distance);
			fscanf(postdata, "%d", &data.package.volume);
			fscanf(postdata, "%d", &data.package.weight);
			fscanf(postdata, "%s", data.package.PlaceFrom);
			fscanf(postdata, "%s", data.package.PlaceTo);
			fscanf(postdata, "%d", &data.package.status);
			fscanf(postdata, "%d", &data.package.posID);
			fscanf(postdata, "%s", data.package.PackageCode);
		}
		List_Insert(&WarePosition, &data, sizeof(data) );
	}
	fclose(postdata);

	if(WarePosition.count == 0){
		for(int index = 0; index <= 3; ++index){	
			WarePostionData data;
			memset(&data, 0, sizeof(data) );
			data.ID = index + 1;
			data.empty = 1;
			data.SizeType = index;
			List_Insert(&WarePosition, &data, sizeof(data) );
		}
	}

	/* 用户操作 */
	while(1){
		/* 登录和注册 */
		if(!InputType) system("cls");
		fprintf(STDOUT, "您好！想要退出(0)？登录(1)？注册(2)?\n");
		fscanf(STDIN, "%2s%*[^\n]", buf); 
		while((buf[0] != '0' && buf[0] != '1' && buf[0] != '2') || strlen(buf) > 1){
			fprintf(STDOUT, "输入不合法，请再次输入\n想要退出(0)？登录(1)？注册(2)?\n");
			fscanf(STDIN, "%2s%*[^\n]", buf);
		}
		int Oper = atoi(buf);
		if(Oper == 0) break;
		UserData *user;
		if(Oper == 1){
			user = user_login();
			if(!InputType) system("pause");
			if(user == NULL){
				continue;
			}
		}
		if(Oper == 2){
			user = user_register(); 
			if(!InputType) system("pause");
			if(user == NULL){
				continue;
			}
		}
		FILE* userfile = UserOutput(user->PhoneNumber);
		
		if(!InputType) system("cls");
		fprintf(STDOUT, "欢迎回来！%s\n", user->name);
		fprintf(userfile, "欢迎回来！%s\n", user->name);
		if(!InputType) system("pause");

		/* 具体操作 */
		while(1){
			if(!InputType) system("cls");
			fprintf(STDOUT, "请输入想进行操作的对应标号：\n");
			fprintf(userfile, "请输入想进行操作的对应标号：\n");
			fprintf(STDOUT, "0.登出\n1.取货\n2.发货\n3.查看未读信息(%d)\n4.查询未领包裹\n5.修改忙碌状态\n", user->message.count);
			fprintf(userfile, "0.登出\n1.取货\n2.发货\n3.查看未读信息(%d)\n4.查询未领包裹\n5.修改忙碌状态\n", user->message.count);
			if(user->UserStatus & 16){
				fprintf(STDOUT, "6.增减货架\n");
				fprintf(userfile, "6.增减货架\n");
			}
			if(user->UserStatus & 32){
				fprintf(STDOUT, "7.货物运输\n8.异常重发\n9.货物运达\n");
				fprintf(userfile, "7.货物运输\n8.异常重发\n9.货物运达\n");
			}
			fprintf(STDOUT, "10.退出并注销\n");
			fprintf(userfile, "10.退出并注销\n");

			int opt;
			fscanf(STDIN, "%3s%*[^\n]", buf); opt = atoi(buf);
			while(
				!isdigit(buf[0]) || (strlen(buf) == 2 ? !isdigit(buf[1]) : 0) || strlen(buf) > 2 ||
				opt > 10 || opt < 0 || (!(user->UserStatus & 16) && opt == 6) || 
				(!(user->UserStatus & 32) && (7 <= opt && opt <= 9) )
			){
				fprintf(STDOUT, "输入不合法，请重新输入想进行操作的对应标号：\n");
				fprintf(userfile, "输入不合法，请重新输入想进行操作的对应标号：\n");
				fscanf(STDIN, "%3s%*[^\n]", buf); opt = atoi(buf);
			}
			if(opt == 0){
				fprintf(STDOUT, "已退出账号\n");
				fprintf(userfile, "已退出账号\n");
				if(!InputType) system("pause");
				break;
			}
			if(opt == 10){
				fprintf(STDOUT, "确定要注销吗？(0 否 / 1 是)\n");
				fprintf(userfile, "确定要注销吗？(0 否 / 1 是)\n");
				fscanf(STDIN, "%2s%*[^\n]", buf); 
				while((buf[0] != '0' && buf[0] != '1') || strlen(buf) > 1){
					fprintf(STDOUT, "请输入 0 或 1\n");
					fprintf(userfile, "请输入 0 或 1\n");
					fscanf(STDIN, "%2s%*[^\n]", buf);
				}
				opt = atoi(buf);
				if(opt == 1){
					user_logout(user);
					if(!InputType) system("pause");
					break;
				}else{
					fprintf(STDOUT, "已取消\n");
					fprintf(userfile, "已取消\n");
					if(!InputType) system("pause");
				}
				continue;
			}
			if((user->UserStatus & 64) && opt != 5){
				fprintf(STDOUT, "请先取消忙碌状态再进行操作。\n");
				fprintf(userfile, "请先取消忙碌状态再进行操作。\n");
				if(!InputType) system("pause");
				continue;
			}

			if(opt == 1){
				user_packageout(user); 
				if(!InputType) system("pause");
			}
			if(opt == 2){
				OutPut(user); 
				if(!InputType) system("pause");
			}
			if(opt == 3){
				user_message(user);
				if(!InputType) system("pause");
			}
			if(opt == 4){
				user_check(user); 
				if(!InputType) system("pause");
			}
			if(opt == 5){
				if(user->PhoneNumber == 10000000000ll){
					fprintf(STDOUT, "默认管理员无法设置忙碌。\n");
					fprintf(userfile, "默认管理员无法设置忙碌。\n");
					if(!InputType) system("pause");
					continue;
				}
				ChangeStatus(user);
				if(!InputType) system("pause");
			}
			if(opt == 6){
				IncreaseRack(user); 
				if(!InputType) system("pause");
			}
			if(opt == 7){
				PackageData package = goodtrans(user); 
				if(package.PhoneNumber != -1)
					List_Insert(&user->vehicle, &package, sizeof(package) );
				if(!InputType) system("pause");
			}
			if(opt == 8){
				reputout(user);
				if(!InputType) system("pause");
			}
			if(opt == 9){
				PackageArrive(user);
				if(!InputType) system("pause");
			}
		}
		fflush(STDOUT);
		fflush(userfile);
		fflush(STDERR);
		fclose(userfile);
	}

	/* 保存数据 */

	userlist = fopen("../data/user/userlist.txt", "w");
	fclose(userlist);
	fprintf(stdout, "正在保存数据\n");
	foreachpro(33, UserManager.root);
	file_user_save(33, UserManager.root);

	PackageSave();
	PositionSave();

	fprintf(stdout, "数据保存完成\n");

	fprintf(stdout, "正在释放内存\n");

	Trie_User_Destroy(UserManager.root);
	List_Destroy(&ManagerAvailable);
	List_Destroy(&WarePackage);
	List_Destroy(&WarePosition);

	fprintf(stdout, "内存释放完成\n");

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
