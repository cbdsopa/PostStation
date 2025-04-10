// 汤嘉敏
#include"VehicleSave.h"
#include"FileManage.h"
#include"PackageData.h"
#include"Trie.h"
void foreach(UserData *user)
{
	UserVehicleInfoClear(user->PhoneNumber);
	FILE* vehicle=UserVehicleInfoSave(user->PhoneNumber);
	for (ListNode* p = user->vehicle.head; p ; p = p->next)
	{
		PackageData *package = (PackageData *)p->data;
		fprintf(vehicle, "%lld ", package->PhoneNumber);
		fprintf(vehicle, "%s ", package->name);
		fprintf(vehicle, "%d ", package->distance);
		fprintf(vehicle, "%d ", package->volume);
		fprintf(vehicle, "%d ", package->weight);
		fprintf(vehicle, "%s ", package->PlaceFrom);
		fprintf(vehicle, "%s ", package->PlaceTo);
		fprintf(vehicle, "%d ", package->status);
		fprintf(vehicle, "%d ", package->posID);
		fprintf(vehicle, "%s", package->PackageCode);
		fprintf(vehicle, "\n");
	}
	fclose(vehicle);
}
void foreachpro(int t, TrieNode *p)
{
	if(p == NULL){
		return;
	}
	if (t == -1) {
		if(p->data != NULL) foreach((UserData*)p->data);
		return;
	}
	if(p->child[0] != NULL) foreachpro(t - 1, p->child[0]);
	if (p->child[1]!=NULL) foreachpro(t - 1, p->child[1]);
}