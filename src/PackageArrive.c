// 齐荣骁
#include"UserData.h"
#include"List.h"
#include "PackageArrive.h"
#include "WarePositionData.h"
#include "FileManage.h"
#include "PackageData.h"
#include "WareInOut.h"
#include <stdio.h>
#include <string.h>
#include "Trie.h"

void PackageArrive(UserData *user) {
	FILE* userself = UserOutput(user->PhoneNumber);
	// FILE* PositionSave = WarePostionSave();
	// FILE* PackageSave = WarePackageSave();
	if (!InputType) system("cls");
	PackageData package;
	ListNode* temp = user->vehicle.head;
	while (temp != NULL) {
		package = *(PackageData*)temp->data;
		package = WareIn(&ManagerAvailable, package, &WarePosition, &WarePackage);
		UserData *receiver = Trie_Find(&UserManager, package.PhoneNumber);
		List_Insert(&receiver->package, &package, sizeof(package) );
		List_Insert(&WarePackage, &package, sizeof(PackageData));
		if (package.status & 1) {
			fprintf(STDOUT, "贵重物品，已存入贵重物品区");
			fprintf(userself, "贵重物品，已存入贵重物品区");
		}
		else {
			if (package.volume <= 3600000) {
				fprintf(STDOUT, "小型物品，已存入小型货架");
				fprintf(userself, "小型物品，已存入小型货架");
			}
			else if (package.volume <= 6000000) {
				fprintf(STDOUT, "中型物品，已存入中型货架");
				fprintf(userself, "中型物品，已存入中型货架");
			}
			else {
				fprintf(STDOUT, "大型物品，已存入大型货架");
				fprintf(userself, "大型物品，已存入大型货架");
			}
		}
		/*
		fprintf(PackageSave, '%lld', package.PhoneNumber);
		fprintf(PackageSave, '%s', package.name);
		fprintf(PackageSave, '%d', package.distance);
		fprintf(PackageSave, '%d', package.volume);
		fprintf(PackageSave, '%d', package.weight);
		fprintf(PackageSave, '%s', package.PlaceFrom);
		fprintf(PackageSave, '%s', package.PlaceTo);
		fprintf(PackageSave, '%d', package.status);
		fprintf(PackageSave, '%d', package.posID);
		fprintf(PackageSave, '%s', package.PackageCode);
		fprintf(PackageSave, '\n');
		*/
		temp = temp->next;
	}
	List_Destroy(&user->vehicle);
	fprintf(STDOUT, "您的所有货物已经入库");
	fprintf(userself, "您的所有货物已经入库");
	/*
	for (ListNode* p = WarePosition.head; p; p = p->next) {
		WarePostionData* data = (WarePostionData*)p->data;
		fprintf(PositionSave, "%d ", data->ID);
		fprintf(PositionSave, "%d ", data->SizeType);
		fprintf(PositionSave, "%d ", data->empty);
		fprintf(PositionSave, "%lld ", data->package.PhoneNumber);
		fprintf(PositionSave, "%s", data->package.PackageCode);
		fprintf(PositionSave, "\n");
	}
	fprintf(STDOUT, "货架信息已保存");
	fprintf(userself, "货架信息已保存");
	*/
	// fclose(PositionSave);
	// fclose(PackageSave);
	fclose(userself);
	return;
}

//for (ListNode* p = user->vehicle.head; p; p = p->next)
//{
//	PackageData* package = (PackageData*)p->data;
//	fprintf(vehicle, "%lld ", package->PhoneNumber);
//	fprintf(vehicle, "%s ", package->name);
//	fprintf(vehicle, "%d ", package->distance);
//	fprintf(vehicle, "%d ", package->volume);
//	fprintf(vehicle, "%d ", package->weight);
//	fprintf(vehicle, "%s ", package->PlaceFrom);
//	fprintf(vehicle, "%s ", package->PlaceTo);
//	fprintf(vehicle, "%d ", package->status);
//	fprintf(vehicle, "%d ", package->posID);
//	fprintf(vehicle, "%s", package->PackageCode);
//	fprintf(vehicle, "\n");
//}


void PackageSave() {
	WarePackageClear();
	FILE* PackageSave = WarePackageSave();
	for (ListNode* temp = WarePackage.head; temp; temp = temp->next) {
		PackageData* package = (PackageData*)temp->data;
		fprintf(PackageSave, "%lld ", package->PhoneNumber);
		fprintf(PackageSave, "%s ", package->name);
		fprintf(PackageSave, "%d ", package->distance);
		fprintf(PackageSave, "%d ", package->volume);
		fprintf(PackageSave, "%d ", package->weight);
		fprintf(PackageSave, "%s ", package->PlaceFrom);
		fprintf(PackageSave, "%s ", package->PlaceTo);
		fprintf(PackageSave, "%d ", package->status);
		fprintf(PackageSave, "%d ", package->posID);
		fprintf(PackageSave, "%s ", package->PackageCode);
		fprintf(PackageSave, "\n");
	}
	fclose(PackageSave);
	return;
}
void PositionSave() {
	WarePositionClear();
	FILE* PositionSave = WarePostionSave();
	for (ListNode* temp = WarePosition.head; temp; temp = temp->next) {
		WarePostionData* data = (WarePostionData*)temp->data;
		fprintf(PositionSave, "%d ", data->ID);
		fprintf(PositionSave, "%d ", data->SizeType);
		fprintf(PositionSave, "%d ", data->empty);
		if(data->empty){
			fprintf(PositionSave, "\n");
			continue;
		}
		fprintf(PositionSave, "%lld ", data->package.PhoneNumber);
		fprintf(PositionSave, "%s ", data->package.name);
		fprintf(PositionSave, "%d ", data->package.distance);
		fprintf(PositionSave, "%d ", data->package.volume);
		fprintf(PositionSave, "%d ", data->package.weight);
		fprintf(PositionSave, "%s ", data->package.PlaceFrom);
		fprintf(PositionSave, "%s ", data->package.PlaceTo);
		fprintf(PositionSave, "%d ", data->package.status);
		fprintf(PositionSave, "%d ", data->package.posID);
		fprintf(PositionSave, "%s ", data->package.PackageCode);
		fprintf(PositionSave, "\n");
	}
	fclose(PositionSave);
	return;
}
