// 吉庆喆
#include "userfile.h"
void save_user_info(UserData* user)
{
    UserInfoClean(user->PhoneNumber);
    FILE* asd=UserInfoSave(user->PhoneNumber);
    fprintf(asd,"%lld\n",user->PhoneNumber);
    fprintf(asd,"%s\n",user->name);
    fprintf(asd,"%s\n",user->password);
    fprintf(asd,"%d\n",user->UserStatus);
    fprintf(asd,"%d\n",user->TransStatus);
    fprintf(asd,"%d\n",user->TransSize);
    fprintf(asd,"%d\n",user->PackageCount);
    fprintf(asd,"%d\n",user->level);
	fclose(asd);
}
void save_user_package(UserData* user)
{
    UserPackageInfoClear(user->PhoneNumber);
	FILE* asd=UserPackageInfoSave(user->PhoneNumber);
	for (ListNode* p = user->package.head; p ; p = p->next)
	{
		PackageData *package = (PackageData *)p->data;
		fprintf(asd, "%lld ", package->PhoneNumber);
		fprintf(asd, "%s ", package->name);
		fprintf(asd, "%d ", package->distance);
		fprintf(asd, "%d ", package->volume);
		fprintf(asd, "%d ", package->weight);
		fprintf(asd, "%s ", package->PlaceFrom);
		fprintf(asd, "%s ", package->PlaceTo);
		fprintf(asd, "%d ", package->status);
		fprintf(asd, "%d ", package->posID);
		fprintf(asd, "%s\n", package->PackageCode);
	}
	fclose(asd);
}
void save_user_message(UserData* user)
{
    UserMessageInfoClear(user->PhoneNumber);
	FILE* asd=UserMessageInfoSave(user->PhoneNumber);
	for (ListNode* p = user->message.head; p ; p = p->next)
	{
		char *str = (char *)p->data;
		fprintf(asd, "%s\n", str);
	}
	fclose(asd);
}
void file_user_save(int t, TrieNode *p)
{
	if(p == NULL){
		return;
	}
	if (t == -1) {
		if(p->data != NULL) 
        {
			FILE *userlist = fopen("../data/user/userlist.txt", "a");
			fprintf(userlist, "%lld\n", ((UserData *)p->data)->PhoneNumber);
			fclose(userlist);
            save_user_info((UserData*)p->data);
            save_user_package((UserData*)p->data);
            save_user_message((UserData*)p->data);
        }
		return;
	}
	if(p->child[0] != NULL) file_user_save(t - 1, p->child[0]);
	if (p->child[1]!=NULL) file_user_save(t - 1, p->child[1]);
}