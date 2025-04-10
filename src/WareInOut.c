// 欧阳承风
#include "WareInOut.h"
#include "WarePositionData.h"
#include "Trie.h"
#include "FileManage.h"
#include "UserData.h"
#include "string.h"

PackageData WareIn(List *Manager, PackageData package, List *WarePosition, List *WarePackage){
	int index = 1ll * rand() * rand() % Manager->count + 1;
	UserData *manager = (UserData *)List_ShowTheEarliest(Manager, index);
	FILE* managerfile = NULL;
	if(!InputType){
		fprintf(STDOUT, "管理员 %s (%lld) 已受理。管理员请输入密码：\n", manager->name, manager->PhoneNumber);
		managerfile = UserOutput(manager->PhoneNumber);
		fprintf(managerfile, "受理入库信息。请输入密码：\n");
	}else{
		fprintf(STDOUT, "管理员 %s (%lld) 已受理。管理员请输入密码：\n", "Admin", 10000000000ll);
	}

	char password[23];
	while(1)
	{
		fscanf(STDIN,"%20s%*[^\n]", password);
		if(InputType){
			if(strncmp("114514", password, 21) == 0){
				fprintf(STDOUT,"密码验证成功!\n");
				break;
			}else{
				fprintf(STDOUT,"密码验证错误,请重新输入:\n");
			}
		}
		if(strncmp(manager->password, password, 21) == 0)
		{
			fprintf(STDOUT,"密码验证成功!\n");
			fprintf(managerfile,"密码验证成功!\n");
			break;
		} 
		else if(strncmp(manager->password, password, 21) != 0)
		{
			fprintf(STDOUT,"密码验证错误,请重新输入:\n");
			fprintf(managerfile,"密码验证错误,请重新输入:\n");
		}
	}

	if(managerfile != NULL) fclose(managerfile);
	/* 寻找空的货架 */
	for(ListNode *now = WarePosition->head; now != NULL; now = now->next){
		WarePostionData *WarePos = (WarePostionData *)now->data;
		if(WarePos->empty == 0) continue;
		if(package.status & 1){
			if(WarePos->SizeType == 3){
				WarePos->empty = 0;
				package.posID = WarePos->ID;
				WarePos->package = package;
				return package;
			}
		}else{
			if(WarePos->SizeType == 0 && package.volume - 3600000 <= 0){
				WarePos->empty = 0;
				package.posID = WarePos->ID;
				WarePos->package = package;
				return package;
			}
			if(WarePos->SizeType == 1 && package.volume - 3600000 > 0 && package.volume - 6000000 <= 0){
				WarePos->empty = 0;
				package.posID = WarePos->ID;
				WarePos->package = package;
				return package;
			}
			if(WarePos->SizeType == 2 && package.volume - 6000000 > 0){
				WarePos->empty = 0;
				package.posID = WarePos->ID;
				WarePos->package = package;
				return package;
			}
		}
	}
	/* 无空位置，删除最早的包裹 */
	PackageData *package_delete;
	for(ListNode *now = WarePackage->head; now != NULL; now = now->next){
		PackageData *package_now = (PackageData *)now->data;
		if(package.status & 1){
			if(package_now->status & 1){
				package_delete = package_now;
			}
		}else{	
			if(package.volume - 3600000 <= 0 && package_now->volume - 3600000 <= 0){
				package_delete = package_now;
			}
			if(
				package.volume - 3600000 > 0 && package.volume - 6000000 <= 0 &&
				package_now->volume - 3600000 > 0 && package_now->volume - 6000000 <= 0
			){
				package_delete = package_now;
			}
			if(package.volume - 6000000 > 0 && package_now->volume - 6000000 > 0){
				package_delete = package_now;
			}
		}
	}
	/* 替换被删除包裹 */
	for(ListNode *now = WarePosition->head; now != NULL; now = now->next){
		WarePostionData *WarePos = (WarePostionData *)now->data;
		if(memcmp(&WarePos->package, package_delete, sizeof(PackageData) ) == 0){
			package.posID = WarePos->ID;
			WarePos->package = package;
			break;
		}
	}
	/* 删除被删除包裹的信息 */
	UserData *user = (UserData *)Trie_Find(&UserManager, package_delete->PhoneNumber);
	List_Delete(&user->package, package_delete, sizeof(PackageData) );
	char mes[] = "由于您的包裹太久未领取，已被发回。";
	List_Insert(&user->message, mes, sizeof(mes) );
	if(user->message.count > 10) List_DeleteTheEarliest(&user->message);
	List_Delete(WarePackage, package_delete, sizeof(PackageData) );
	return package;
}

int WareOut(List *Manager, PackageData package, List *WarePosition, List *WarePackage){
	int index = 1ll * rand() * rand() % Manager->count + 1;
	UserData *manager = (UserData *)List_ShowTheEarliest(Manager, index);
	FILE* managerfile = NULL;
	if(!InputType){
		fprintf(STDOUT, "管理员 %s (%lld) 已受理。管理员请输入密码：\n", manager->name, manager->PhoneNumber);
		managerfile = UserOutput(manager->PhoneNumber);
		fprintf(managerfile, "受理入库信息。请输入密码：\n");
	}else{
		fprintf(STDOUT, "管理员 %s (%lld) 已受理。管理员请输入密码：\n", "Admin", 10000000000ll);
	}

	char password[23];
	while(1)
	{
		fscanf(STDIN,"%20s%*[^\n]", password);
		if(InputType){
			if(strncmp("114514", password, 21) == 0){
				fprintf(STDOUT,"密码验证成功!\n");
				break;
			}else{
				fprintf(STDOUT,"密码验证错误,请重新输入:\n");
			}
		}
		if(strncmp(manager->password, password, 21) == 0)
		{
			fprintf(STDOUT,"密码验证成功!\n");
			fprintf(managerfile,"密码验证成功!\n");
			break;
		} 
		else if(strncmp(manager->password, password, 21) != 0)
		{
			fprintf(STDOUT,"密码验证错误,请重新输入:\n");
			fprintf(managerfile,"密码验证错误,请重新输入:\n");
		}
	}

	if(managerfile != NULL) fclose(managerfile);

	/* 找到包裹并删除 */
	for(ListNode *now = WarePosition->head; now != NULL; now = now->next){
		WarePostionData *WarePos = (WarePostionData *)now->data;
		if(memcmp(&WarePos->package, &package, sizeof(PackageData) ) == 0){
			WarePos->empty = 1;
			break;
		}
	}
	List_Delete(WarePackage, &package, sizeof(PackageData) );
	return 0;
}
