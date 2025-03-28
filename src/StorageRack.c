#include "UserData.h"
#include "FileManage.h"
#include "StorageRack.h"
#include "List.h"
#include "WarePositionData.h"
#include <stdio.h>

void IncreaseRack(UserData user) {
	int mode;
	int change; 
	FILE* userself = UserOutput(user.PhoneNumber);
	//change >= 0
	fprintf(STDOUT,"输入 1-增加货架 2-减少货架");
	fprintf(userself, "输入 1-增加货架 2-减少货架");
	fscanf(STDIN, "%d", mode);
	while (mode != 1 && mode != 2) {
		fprintf(STDOUT, "输入不符合要求，请重新输入");
		fprintf(userself, "输入不符合要求，请重新输入");
		fscanf(STDIN, "%d", mode);
	}
	if (mode == 1) {
		fprintf(STDOUT, "输入增加的货架数量");
		fprintf(userself, "输入增加的货架数量");
		fscanf(STDIN, "%d", change);
		while (change < 0) {
			fprintf(STDOUT, "输入不符合要求，请重新输入");
			fprintf(userself, "输入不符合要求，请重新输入");
			fscanf(STDIN, "%d", change);
		}
		WarePosition.count += change;
	}
	if (mode == 2) {
		fprintf(STDOUT, "输入减少的货架数量");
		fprintf(userself, "输入减少的货架数量");
		fscanf(STDIN, "%d", change);
		while (change < 0 || change > WarePosition.count) {
			fprintf(STDOUT, "输入不符合要求，请重新输入");
			fprintf(userself, "输入不符合要求，请重新输入");
			fscanf(STDIN, "%d", change);
		}
		WarePosition.count -= change;
	}
	fclose(userself);
	return;
}
