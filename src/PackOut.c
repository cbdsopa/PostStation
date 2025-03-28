#include"PackOut.h"
#include"FileManage.h"
#include"UserData.h"
#include"PackageData.h"
#include<string.h>
#include"Transport.h"
#include"Trie.h"
#include "MyString.h"
#include "cost.h"
void OutPut(UserData *User)
{
	
	FILE* user = UserOutput(User->PhoneNumber);
	long long PhoneNumber;
	char phonenumber[15];
	char name[21];
	double distance;
	double volume;
	double weight;
	char PlaceFrom[41], PlaceTo[41];
	int status=0;
	fprintf(STDOUT, "请输入收货者11位号码\n");
	fprintf(user, "请输入收货者11位号码\n");
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
			fprintf(user, "手机号格式错误,请重新输入\n");
		}
		else
		{
			PhoneNumber = atoll(phonenumber);
			break;
		}
	}
	fprintf(STDOUT, "请输入用户名(10字以内)\n");
	fprintf(user, "请输入用户名(10字以内)\n");
	while (1)
	{
		fscanf(STDIN, "%32s%*[^\n]", name);
		int namecheck = strlen(name);
		if (namecheck > 30)
		{
			fprintf(STDOUT, "名字输入长度超出限制,请重新输入\n");
			fprintf(user, "名字输入长度超出限制,请重新输入\n");
			continue;
		}
		else
		{
			int namecount = realen(name);//把汉字算作一个字符
			if (namecount > 10)
			{
				fprintf(STDOUT, "名字输入长度超出限制,请重新输入\n");
				fprintf(user, "名字输入长度超出限制,请重新输入\n");
			}
			else break;
		}

	}
	fprintf(STDOUT, "请输入货物体积\n");
	fprintf(user, "请输入货物体积\n");
	fscanf(STDIN, "%lf", &volume);
	while (volume > 120000)
	{
		fprintf(STDOUT, "您的输入的包裹过大，请重新输入\n");
		fprintf(user, "您的输入的包裹过大，请重新输入\n");
		fscanf(STDIN, "%lf", &volume);
	}
	fprintf(STDOUT, "请输入货物运输距离\n");
	fprintf(user, "请输入货物运输距离\n");
	fscanf(STDIN, "%lf", &distance);
	while (distance > 10000)
	{
		fprintf(STDOUT, "您的输入的距离过远，请重新输入\n");
		fprintf(user, "您的输入的距离过远，请重新输入\n");
		fscanf(STDIN, "%lf", &distance);
	}
	fprintf(STDOUT, "请输入货物重量\n");
	fprintf(user, "请输入货物重量\n");
	fscanf(STDIN, "%lf", &weight);
	while (weight > 200)
	{
		fprintf(STDOUT, "您的输入的重量过重，请重新输入\n");
		fprintf(user, "您的输入的重量过重，请重新输入\n");
		fscanf(STDIN, "%lf", &weight);
	}
	fprintf(STDOUT, "请输入货物发货地\n");
	fprintf(user, "请输入货物发货地\n");
	while (1)
	{
		fscanf(STDIN, "%40s%*[^\n]", PlaceFrom);
		int check = strlen(PlaceFrom);
		if (check > 40)
		{
			fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
			fprintf(user, "地名输入长度超出限制,请重新输入\n");
			continue;
		}
		else
		{
			int count = realen(PlaceFrom);//把汉字算作一个字符
			if (count > 13)
			{
				fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
				fprintf(user, "地名输入长度超出限制,请重新输入\n");
			}
			else break;
		}
	}
	fprintf(STDOUT, "请输入货物收货地\n");
	fprintf(user, "请输入货物收货地\n");
	while (1)
	{
		fscanf(STDIN, "%40s%*[^\n]", PlaceTo);
		int Check = strlen(PlaceTo);
		if (Check > 40)
		{
			fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
			fprintf(user, "地名输入长度超出限制,请重新输入\n");
			continue;
		}
		else
		{
			int Count = realen(PlaceTo);//把汉字算作一个字符
			if (Count > 13)
			{
				fprintf(STDOUT, "地名输入长度超出限制,请重新输入\n");
				fprintf(user, "地名输入长度超出限制,请重新输入\n");
			}
			else break;
		}
	}
	fprintf(STDOUT, "请输入货物是否贵重\n");
	fprintf(user, "请输入货物是否贵重\n");
	fprintf(STDOUT, "0.不是贵重\n");
	fprintf(user, "0.不是贵重\n");
	fprintf(STDOUT, "1.贵重\n");
	fprintf(user, "1.贵重\n");
	int g;
	while (1)
	{
		fscanf(STDIN, "%2d%*[^\n]", &g);
		if (g==0||g==1)
		{
			break;
		}
		else
		{
			fprintf(STDOUT, "输入错误，请重新输入0或1\n");
			fprintf(user, "输入错误，请重新输入0或1\n");
		}
	}
	fprintf(STDOUT, "请输入货物是否需要保鲜\n");
	fprintf(user, "请输入货物是否需要保鲜\n");
	fprintf(STDOUT, "0.不需保鲜\n");
	fprintf(user, "0.不需保鲜\n");
	fprintf(STDOUT, "1.保鲜\n");
	fprintf(user, "1.保鲜\n");
	int b;
	while (1)
	{
		fscanf(STDIN, "%2d%*[^\n]", &b);
		if (b == 0 || b == 1)
		{
			break;
		}
		else
		{
			fprintf(STDOUT, "输入错误，请重新输入0或1\n");
			fprintf(user, "输入错误，请重新输入0或1\n");
		}
	}
	fprintf(STDOUT, "请输入货物是否需要急运\n");
	fprintf(user, "请输入货物是否需要急运\n");
	fprintf(STDOUT, "0.不需急运\n");
	fprintf(user, "0.不需急运\n");
	fprintf(STDOUT, "1.急运\n");
	fprintf(user, "1.急运\n");
	int j;//5
	while (1)
	{
		fscanf(STDIN, "%2d%*[^\n]", &j);
		if (j == 0 || j == 1)
		{
			break;
		}
		else
		{
			fprintf(STDOUT, "输入错误，请重新输入0或1\n");
			fprintf(user, "输入错误，请重新输入0或1\n");
		}
	}
	fprintf(STDOUT, "您已发货成功！\n");
	fprintf(user, "您已发货成功！\n");
	if (g) status += 1;
	if (b) status += 2;
	if (j) status += 4;
	PackageData pack = CreatePackage(PhoneNumber, name, distance, volume, weight, PlaceFrom, PlaceTo, status);
	// 传用户数据和包裹
	double cost = expense(*User, pack);
	char msg[60];
	sprintf(msg, "请您支付运输费用 %lf 元\n", cost);
	fprintf(user, "请您支付运输费用 %lf 元\n", cost);
	List_Insert(&User->message, msg, sizeof(msg));
	if (User->message.count > 10) List_DeleteTheEarliest(&User->message);
	fclose(user);
}
