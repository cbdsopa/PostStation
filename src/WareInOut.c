#include "WareInOut.h"
#include "WarePositionData.h"
#include "Trie.h"
#include "FileManage.h"
#include "UserData.h"
#include "string.h"

const double eps = 1e-9;

PackageData WareIn(List *Manager, PackageData package, List *WarePosition, List *WarePackage){
	if(!InputType) system("cls");
	int index = rand() * rand() % Manager->count + 1;
	UserData *manager = (UserData *)List_ShowTheEarliest(Manager, index);
	
	fprintf(STDOUT, "管理员 %s 已受理。\n", manager->name);
	FILE* managerfile = UserOutput(manager->PhoneNumber);
	fprintf(managerfile, "受理出库信息。\n");
	fclose(managerfile);
	
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
			if(WarePos->SizeType == 0 && package.volume - 36000 <= eps){
				WarePos->empty = 0;
				package.posID = WarePos->ID;
				WarePos->package = package;
				return package;
			}
			if(WarePos->SizeType == 1 && package.volume - 36000 > eps && package.volume - 60000 <= eps){
				WarePos->empty = 0;
				package.posID = WarePos->ID;
				WarePos->package = package;
				return package;
			}
			if(WarePos->SizeType == 2 && package.volume - 60000 > eps){
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
			if(package.volume - 36000 <= eps && package_now->volume - 36000 <= eps){
				package_delete = package_now;
			}
			if(
				package.volume - 36000 > eps && package.volume - 60000 <= eps &&
				package_now->volume - 36000 > eps && package_now->volume - 60000 <= eps
			){
				package_delete = package_now;
			}
			if(package.volume - 60000 > eps && package_now->volume - 60000 > eps){
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
	if(!InputType) system("cls");
	int index = rand() * rand() % Manager->count + 1;
	UserData *manager = (UserData *)List_ShowTheEarliest(Manager, index);
	
	fprintf(STDOUT, "管理员 %s 已受理。\n", manager->name);
	FILE* managerfile = UserOutput(manager->PhoneNumber);
	fprintf(managerfile, "受理出库信息。\n");
	fclose(managerfile);

	/* 找到包裹并删除 */
	for(ListNode *now = WarePosition->head; now != NULL; now = now->next){
		WarePostionData *WarePos = (WarePostionData *)now->data;
		if(memcmp(&WarePos->package, &package, sizeof(PackageData) ) == 0){
			WarePos->empty = 1;
		}
	}
	List_Delete(WarePackage, &package, sizeof(PackageData) );
	return 0;
}
