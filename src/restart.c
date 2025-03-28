#include"PackageData.h"
#include"FileManage.h"
#include"Trie.h"
#include"UserData.h"
#include"restart.h"
#include<string.h>
#include "MyString.h"
extern Trie UserManager;
void reputout(UserData courier)
{
	if (!InputType) system("cls");//清屏
	long long PhoneNumber;
	char phonenumber[15];
	char name[21];
	double distance;
	double volume;
	double weight;
	char PlaceFrom[41], PlaceTo[41];
	int status;
	UserData* puser;
	FILE* Courier = UserOutput(courier.PhoneNumber);
	fprintf(STDOUT, "请输入收货者11位码\n");
	fprintf(Courier, "请输入收货者11位号码\n");
	while (1)
	{
		fscanf(STDIN, "%12s%*[^\n]", phonenumber);
		int bool = 1;
		int numlenth = strlen(phonenumber);
		if (numlenth != 11) bool = 0;
		else
		{
			for (int i = 0; i < 11; i++)
			{
				if (phonenumber[i] < '0' || phonenumber[i]>'9') bool = 0;
			}
		}
		if (bool == 0)
		{
			fprintf(STDOUT, "手机号格式错误,请重新输入\n");
			fprintf(Courier, "手机号格式错误,请重新输入\n");
		}
		else
		{
			PhoneNumber = atoll(phonenumber);
			break;
		}
	}
	fprintf(STDOUT, "请输入收货者姓名\n");
	fprintf(Courier, "请输入收货者姓名\n");
	while (1)
	{
		fscanf(STDIN, "%32s%*[^\n]", name);
		int namecheck = strlen(name);
		if (namecheck > 30)
		{
			fprintf(STDOUT, "名字输入长度超出限制,请重新输入\n");
			fprintf(Courier, "名字输入长度超出限制,请重新输入\n");
			continue;
		}
		else
		{
			int namecount = realen(name);//把汉字算作一个字符
			if (namecount > 10)
			{
				fprintf(STDOUT, "名字输入长度超出限制,请重新输入\n");
				fprintf(Courier, "名字输入长度超出限制,请重新输入\n");
			}
			else break;
		}

	}
	fprintf(STDOUT, "请输入货物体积\n");
	fprintf(Courier, "请输入货物体积\n");
	fscanf(STDIN, "%lf", &volume);
	while (volume>120000)
	{
		fprintf(STDOUT, "您的输入的包裹过大，请重新输入\n");
		fprintf(Courier, "您的输入的包裹过大，请重新输入\n");
		fscanf(STDIN, "%lf", &volume);
	}
	fprintf(STDOUT, "请输入货物运输距离\n");
	fprintf(Courier, "请输入货物运输距离\n");
	fscanf(STDIN, "%lf", &distance);
	while (distance>10000)
	{
		fprintf(STDOUT, "您的输入的距离过远，请重新输入\n");
		fprintf(Courier, "您的输入的距离过远，请重新输入\n");
		fscanf(STDIN, "%lf", &distance);
	}
	fprintf(STDOUT, "请输入货物重量\n");
	fprintf(Courier, "请输入货物重量\n");
	fscanf(STDIN, "%lf", &weight);

	while (weight>200)
	{
		fprintf(STDOUT, "您的输入的重量过重，请重新输入\n");
		fprintf(Courier, "您的输入的重量过重，请重新输入\n");
		fscanf(STDIN, "%lf", &weight);
	}
	fprintf(STDOUT, "请输入货物发货地\n");
	fprintf(Courier, "请输入货物发货地\n");
	while (1)
	{
		fscanf(STDIN, "%40s%*[^\n]", PlaceFrom);
		int check = strlen(PlaceFrom);
		if (check > 40)
		{
			fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
			fprintf(Courier, "地名输入长度超出限制,请重新输入\n");
			continue;
		}
		else
		{
			int count = realen(PlaceFrom);//把汉字算作一个字符
			if (count > 13)
			{
				fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
				fprintf(Courier, "地名输入长度超出限制,请重新输入\n");
			}
			else break;
		}
	}
	fprintf(STDOUT, "请输入货物收货地\n");
	fprintf(Courier, "请输入货物收货地\n");
	while (1)
	{
		fscanf(STDIN, "%40s%*[^\n]", PlaceTo);
		int Check = strlen(PlaceTo);
		if (Check > 40)
		{
			fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
			fprintf(Courier, "地名输入长度超出限制,请重新输入\n");
			continue;
		}
		else
		{
			int Count = realen(PlaceTo);//把汉字算作一个字符
			if (Count > 13)
			{
				fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
				fprintf(Courier, "地名输入长度超出限制,请重新输入\n");
			}
			else break;
		}
	}
	fprintf(STDOUT, "请输入货物是否贵重\n");
	fprintf(Courier, "请输入货物是否贵重\n");
	fprintf(STDOUT, "0.不是贵重\n");
	fprintf(Courier, "0.不是贵重\n");
	fprintf(STDOUT, "1.贵重\n");
	fprintf(Courier, "1.贵重\n");
	int g;
	while (1)
	{
		fscanf(STDIN, "%2d%*[^\n]", &g);
		if (g == 0 || g == 1)
		{
			break;
		}
		else
		{
			fprintf(STDOUT, "输入错误，请重新输入0或1\n");
			fprintf(Courier, "输入错误，请重新输入0或1\n");
		}
	}
	status = g;
	if (!InputType) system("cls");
	PackageData pack=CreatePackage(PhoneNumber, name, distance, volume, weight, PlaceFrom, PlaceTo, status);
	puser=(UserData *)Trie_Find(&UserManager,pack.PhoneNumber);
	int t;
	t = List_Find(&puser->vehicle, &pack, sizeof(pack) - sizeof(char[21]));
	if (t==0)
	{
		fprintf(STDOUT, "输入的包裹信息有误，请重新输入\n");
		fprintf(Courier, "输入的包裹信息有误，请重新输入\n");
	}
	if (t==1)
	{
		int damage=5;
		if (status==1)
		{
			damage = 20;
		}
		if (!InputType) system("cls");
		FILE* user = UserOutput(PhoneNumber);
		fprintf(STDOUT, "请重新发货并支付赔偿金 %d 元\n",damage);
		fprintf(Courier, "请重新发货并支付赔偿金 %d 元\n", damage);
		char msg[100];
		sprintf(msg, "很抱歉在运输过程中损坏了您的货物，已赔偿您 %d 元并重新运输\n", damage);
		fprintf(user, "很抱歉在运输过程中损坏了您的货物，已赔偿您 %d 元并重新运输\n", damage);
		List_Insert(&puser->message, msg, sizeof(msg));
		if (puser->message.count > 10)List_DeleteTheEarliest(&puser->message);
		fclose(Courier);
		fclose(user);
	}
}