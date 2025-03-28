#include"VehicleSave.h"
#include"FileManage.h"
#include"PackageData.h"
#include"Trie.h"
void foreach(UserData *user)
{
	if (!InputType) system("cls");
	FILE* vehicle=UserVehicleInfoSave(user->PhoneNumber);
	for (ListNode* p = user->vehicle.head; p ; p = p->next)
	{
		PackageData *package = (PackageData *)p->data;
		fprintf(vehicle, "%ld ", package->PhoneNumber);
		fprintf(vehicle, "%s ", package->name);
		fprintf(vehicle, "%ld ", package->distance);
		fprintf(vehicle, "%ld ", package->volume);
		fprintf(vehicle, "%ld ", package->weight);
		fprintf(vehicle, "%s ", package->PlaceFrom);
		fprintf(vehicle, "%s ", package->PlaceTo);
		fprintf(vehicle, "%d ", package->status);
		fprintf(vehicle, "%d ", package->posID);
		fprintf(vehicle, "%s", package->PackageCode);
		fprintf(vehicle, "\n");
	}
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