#include"Transport.h"
#include"FileManage.h"
#include"UserData.h"
#include "Packagedata.h"
#include"List.h"
#include"Cost.h"
#include<stdio.h>

PackageData goodtrans(UserData user) {
	long long PhoneNumber;
	char name[21], PlaceFrom[41], PlaceTo[41], PackageCode[21] = "/0";
	int value, conveyance, status;
	double distance, weight, volume;
	if (!InputType) system("cls");
	FILE* userself = UserOutput(user.PhoneNumber);
	if (user.TransSize == 500) {
		fprintf(STDOUT, "您的快递数量已达上限，无法继续发出快递\n");
		fprintf(userself, "您的快递数量已达上限，无法继续发出快递\n");
		fclose(userself);
		return (PackageData){};
	}
	fprintf(STDOUT, "请输入收件人姓名");
	fprintf(userself, "请输入收件人姓名");
	fscanf(STDIN, "%s", name);
	fprintf(STDOUT, "请输入收件人电话号码");
	fprintf(userself, "请输入收件人电话号码");
	fscanf(STDIN, "%lld", &PhoneNumber);
	fprintf(STDOUT,"请输入货物体积：");
	fprintf(userself, "请输入货物体积：");
	fscanf(STDIN,"%lf", &volume);
	while (volume > 120000 || volume <= 0) {
		fprintf(STDOUT, "货物体积不符合要求，请重新输入：");
		fprintf(userself, "货物体积不符合要求，请重新输入：");
		fscanf(STDIN, "%lf", &volume);
	}
	if (volume <= 36000) {
		fprintf(STDOUT, "货物为小型货物\n");
		fprintf(userself, "货物为小型货物\n");
	}
	else if (volume <= 60000) {
		fprintf(STDOUT, "货物为中型货物\n");
		fprintf(userself, "货物为中型货物\n");
	}
	else {
		fprintf(STDOUT, "货物为大型货物\n");
		fprintf(userself, "货物为大型货物\n");
	}
	fprintf(STDOUT, "请输入货物重量：");
	fscanf(STDIN, "%lf", &weight);
	while (weight > 200 || weight <= 0) {
		fprintf(STDOUT, "货物重量不符合要求，请重新输入：");
		fprintf(userself, "货物重量不符合要求，请重新输入：");
		fscanf(STDIN, "%lf", &weight);
	}
	fprintf(STDOUT, "请输入货物起始地：");
	fprintf(userself, "请输入货物起始地：");
	fscanf(STDIN, "%s", PlaceFrom);
	fprintf(STDOUT, "请输入货物目的地：");
	fprintf(userself, "请输入货物目的地：");
	fscanf(STDIN, "%s", PlaceTo);
	fprintf(STDOUT, "请输入货物距离：");
	fprintf(userself, "请输入货物距离：");
	fscanf(STDIN, "%lf", &distance);
	while (distance > 10000 || distance <= 0) {
		fprintf(STDOUT, "货物距离不符合要求，请重新输入：");
		fprintf(userself, "货物距离不符合要求，请重新输入：");
		fscanf(STDIN, "%lf", &distance);
	}
	fprintf(STDOUT, "请输入货物状态：\n 1-贵重 2-需要保鲜 4-紧急");
	fprintf(userself, "请输入货物状态：\n 1-贵重 2-需要保鲜 4-紧急");
	fscanf(STDIN, "%d", &status);
	while (status != 1 && status != 2 && status != 4) {
		fprintf(STDOUT, "货物状态不符合要求，请重新输入：");
		fprintf(userself, "货物状态不符合要求，请重新输入：");
		fscanf(STDIN, "%d", &status);
	}
	fclose(userself);
	return CreatePackage(PhoneNumber, name, distance, volume, weight, PlaceFrom, PlaceTo, status);
}

void messagecost(UserData addresser, UserData receiver, PackageData package) {
	double cost = expense(addresser, package);
	char message1[] = "您的快递已经发出，快递费用为：%lf", message2[] = "您有一件快递已经发出，请关注运输动态";
	List_Insert(&addresser.message, message1,sizeof(message1));
	List_Insert(&receiver.message, message2, sizeof(message2));
}
