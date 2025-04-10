// 齐荣骁（用户输入） & 欧阳承风（货架删除处理）
#include "UserData.h"
#include "FileManage.h"
#include "StorageRack.h"
#include "List.h"
#include "WarePositionData.h"
#include <stdio.h>
#include<string.h>
#include <math.h>

extern List ManagerAvailable, WarePackage, WarePosition;
extern FILE* STDIN, * STDOUT;
void IncreaseRack(UserData *user) {
	char modeStr[10], sizeStr[10], changeStr[10];
	int mode, size;
	int change; 
	FILE* userself = UserOutput(user->PhoneNumber);
	//change >= 0
	fprintf(STDOUT,"请选择货架类型 0-小 1-中 2-大 3-贵重：");
	fprintf(userself, "请选择货架类型 0-小 1-中 2-大 3-贵重：");
	while (1) {
		fscanf(STDIN, "%2s%*[^\n]", sizeStr);
		if (strlen(sizeStr) != 1) {
			fprintf(STDOUT, "输入不符合要求，请重新输入：");
			fprintf(userself, "输入不符合要求，请重新输入：");
		}
		else {
			if (sizeStr[0] == '0' || sizeStr[0] == '1' || sizeStr[0] == '2' || sizeStr[0] == '3') {
				break;
			}
			else {
				fprintf(STDOUT, "输入不符合要求，请重新输入：");
				fprintf(userself, "输入不符合要求，请重新输入：");
			}
		}
	}
	size = sizeStr[0] - '0';
	fprintf(STDOUT,"输入 1-增加货架 2-减少货架：");
	fprintf(userself, "输入 1-增加货架 2-减少货架：");
	while (1) {
		fscanf(STDIN, "%2s%*[^\n]", modeStr);
		if (strlen(modeStr) != 1) {
			fprintf(STDOUT, "输入不符合要求，请重新输入：");
			fprintf(userself, "输入不符合要求，请重新输入：");
		}
		else {
			if (modeStr[0] == '1' || modeStr[0] == '2') {
				break;
			}
			else {
				fprintf(STDOUT, "输入不符合要求，请重新输入：");
				fprintf(userself, "输入不符合要求，请重新输入：");
			}
		}
	}
	mode = modeStr[0] - '0';
	if (mode == 1) {
		fprintf(STDOUT, "请输入增加的货架数量（不超过9999）：");
		fprintf(userself, "请输入增加的货架数量（不超过9999）：");
		while(1)
		{
			fscanf(STDIN, "%6s%*[^\n]", changeStr);
			int pol=1;
			int len = strlen(changeStr);
			if(len > 4) pol = 0;
			for (int i = 0;i < len;i++) if (changeStr[i] < '0' || changeStr[i]>'9') pol=0;
			if(pol) break;
			else 
			{
				fprintf(STDOUT, "输入不符合要求，请重新输入：");
				fprintf(userself, "输入不符合要求，请重新输入：");
			}
		}
		change = atoi(changeStr);
		for (int i = 0; i < change; i++) {
			WarePostionData Ware = WarePositionCreate(WarePosition.count + 1, size, 1, (PackageData) { 0 });
			List_Insert(&WarePosition, &Ware, sizeof(WarePostionData));
		}
		
		fprintf(STDOUT, "货架添加完毕。");
		fprintf(userself, "货架添加完毕。");
	}
	if (mode == 2) {
		fprintf(STDOUT, "请输入减少的货架数量：");
		fprintf(userself, "请输入减少的货架数量：");
		while (1) 
		{
			int flag=1;
			fscanf(STDIN, "%6s%*[^\n]", changeStr);
			int len = strlen(changeStr);
			if(len > 4) flag = 0;
			for (int i = 0; i < len; i++) if (changeStr[i] < '0' || changeStr[i]>'9') flag=0;
			if(flag) 
			{
				change = atoi(changeStr);
				break;
			}
			else 
			{
				fprintf(STDOUT, "输入不符合要求，请重新输入：");
				fprintf(userself, "输入不符合要求，请重新输入：");
			}
		}
		int count = 0;
		for(ListNode *now = WarePosition.head; now != NULL; now = now->next){
			WarePostionData *ware = now->data;
			if(ware->SizeType == size){
				++count;
			}
		}
		if(change > count - 1){
			fprintf(STDOUT, "货架数量不足。");
			fprintf(userself, "货架数量不足。");
			fclose(userself);
			return;
		}
		int cnt = 0;
		ListNode *now = WarePosition.head, *last = NULL;
		while(now != NULL && change){
			WarePostionData *ware = now->data;
			if(ware->SizeType == size && ware->empty){
				--change;
				++cnt;
				if(last == NULL){
					--WarePosition.count;
					WarePosition.head = now->next;
					free(now);
					now = WarePosition.head;
				}else{
					last->next = now->next;
					free(now);
					now = last->next;
				}
			}else{
				last = now;
				now = now->next;
			}
		}
		fprintf(STDOUT, "货架删除 %d 个，完毕。", cnt);
		fprintf(userself, "货架删除 %d 个，完毕。", cnt);
	}
	fclose(userself);
	return;
}
