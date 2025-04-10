// 汤嘉敏
#include"PackageData.h"
#include"FileManage.h"
#include"Trie.h"
#include"UserData.h"
#include"restart.h"
#include<string.h>
#include "MyString.h"
extern Trie UserManager;
void reputout(UserData *courier)
{
	if (!InputType) system("cls");//清屏
	FILE* user = UserOutput(courier->PhoneNumber);
	long long PhoneNumber;
	char phonenumber[15];
	char name[25];
	char Distance[20];
	char Volume[20];
	char Weight[20];
	double distance;
	double volume;
	double weight;
	char PlaceFrom[45], PlaceTo[45];
	int status = 0;
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
	while (1)
	{
		fscanf(STDIN, "%18s%*[^\n]", Volume);
		int Vocheck = strlen(Volume);
		if (Vocheck > 10)
		{
			fprintf(STDOUT, "您的输入的包裹过大，请重新输入\n");
			fprintf(user, "您的输入的包裹过大，请重新输入\n");
		}
		else
		{
			int bool = 1, tep = 0;
			for (int i = 0; i < Vocheck; i++)
			{
				if (Volume[i] == '.')
				{
					tep++;
				}
				else if (Volume[i] < '0' || Volume[i]>'9')
				{
					bool = 0;
				}

			}
			if (bool == 0 || tep > 1 || Volume[0] == '.')
			{
				fprintf(STDOUT, "您的输入格式错误，请重新输入\n");
				fprintf(user, "您的输入格式错误，请重新输入\n");
			}
			else
			{
				volume = atof(Volume);
				if (volume<=0||volume>120000)
				{
					if (volume > 120000)
					{
						fprintf(STDOUT, "您的输入的包裹过大，请重新输入\n");
						fprintf(user, "您的输入的包裹过大，请重新输入\n");
					}
					if (volume <= 0)
					{
						fprintf(STDOUT, "您的输入的包裹过小，请重新输入\n");
						fprintf(user, "您的输入的包裹过小，请重新输入\n");
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	fprintf(STDOUT, "请输入货物运输距离\n");
	fprintf(user, "请输入货物运输距离\n");
	while (1)
	{
		fscanf(STDIN, "%18s%*[^\n]", Distance);
		int Dicheck = strlen(Distance);
		if (Dicheck > 10)
		{
			fprintf(STDOUT, "您的输入的距离过远，请重新输入\n");
			fprintf(user, "您的输入的距离过远，请重新输入\n");
		}
		else
		{
			int bool = 1, tep = 0;
			for (int i = 0; i < Dicheck; i++)
			{
				if (Distance[i] == '.')
				{
					tep++;
				}
				else
					if (Distance[i] < '0' || Distance[i]>'9')
					{
						bool = 0;
					}
			}
			if (bool == 0 || tep > 1 || Distance[0] == '.')
			{
				fprintf(STDOUT, "您的输入格式错误，请重新输入\n");
				fprintf(user, "您的输入格式错误，请重新输入\n");
			}
			else
			{
				distance = atof(Distance);
				if (distance<=0||distance>10000)
				{
					if (distance > 10000)
					{
						fprintf(STDOUT, "您的输入的距离过远，请重新输入\n");
						fprintf(user, "您的输入的距离过远，请重新输入\n");
					}
					if (distance <= 0)
					{
						fprintf(STDOUT, "您的输入的距离过近，请重新输入\n");
						fprintf(user, "您的输入的距离过近，请重新输入\n");
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	fprintf(STDOUT, "请输入货物重量\n");
	fprintf(user, "请输入货物重量\n");
	while (1)
	{
		fscanf(STDIN, "%10s%*[^\n]", Weight);
		int Wecheck = strlen(Weight);
		if (Wecheck > 7)
		{
			fprintf(STDOUT, "您的输入的重量过重，请重新输入\n");
			fprintf(user, "您的输入的重量过重，请重新输入\n");
		}
		else
		{
			int bool = 1, tep = 0;
			for (int i = 0; i < Wecheck; i++)
			{
				if (Weight[i] == '.')
				{
					tep++;
				}
				else
					if (Weight[i] < '0' || Weight[i]>'9')
					{
						bool = 0;
					}

			}
			if (bool == 0 || tep > 1 || Weight[0] == '.')
			{
				fprintf(STDOUT, "您的输入格式错误，请重新输入\n");
				fprintf(user, "您的输入格式错误，请重新输入\n");
			}
			else
			{
				weight = atof(Weight);
				if (weight<=0||weight>200)
				{
					if (weight > 200)
					{
						fprintf(STDOUT, "您的输入的重量过重，请重新输入\n");
						fprintf(user, "您的输入的重量过重，请重新输入\n");
					}
					if (weight <= 0)
					{
						fprintf(STDOUT, "您的输入的重量过轻，请重新输入\n");
						fprintf(user, "您的输入的重量过轻，请重新输入\n");
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	fprintf(STDOUT, "请输入货物发货地\n");
	fprintf(user, "请输入货物发货地\n");
	while (1)
	{
		fscanf(STDIN, "%41s%*[^\n]", PlaceFrom);
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
			if (count > 20)
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
		fscanf(STDIN, "%41s%*[^\n]", PlaceTo);
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
			if (Count > 20)
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
	char g[5];
	while (1)
	{
		fscanf(STDIN, "%2s%*[^\n]", &g);
		int len = strlen(g);
		if (len > 1)
		{
			fprintf(STDOUT, "输入错误，请重新输入0或1\n");
			fprintf(user, "输入错误，请重新输入0或1\n");
		}
		else
		{
			if (g[0] == '0' || g[0] == '1')
			{
				break;
			}
			else
			{
				fprintf(STDOUT, "输入错误，请重新输入0或1\n");
				fprintf(user, "输入错误，请重新输入0或1\n");
			}
		}
	}
	fprintf(STDOUT, "请输入货物是否需要保鲜\n");
	fprintf(user, "请输入货物是否需要保鲜\n");
	fprintf(STDOUT, "0.不需保鲜\n");
	fprintf(user, "0.不需保鲜\n");
	fprintf(STDOUT, "1.保鲜\n");
	fprintf(user, "1.保鲜\n");
	char b[5];
	while (1)
	{
		fscanf(STDIN, "%2s%*[^\n]", &b);
		int len = strlen(b);
		if (len > 1)
		{
			fprintf(STDOUT, "输入错误，请重新输入0或1\n");
			fprintf(user, "输入错误，请重新输入0或1\n");
		}
		else
		{
			if (b[0] == '0' || b[0] == '1')
			{
				break;
			}
			else
			{
				fprintf(STDOUT, "输入错误，请重新输入0或1\n");
				fprintf(user, "输入错误，请重新输入0或1\n");
			}
		}
	}
	fprintf(STDOUT, "请输入货物是否需要急运\n");
	fprintf(user, "请输入货物是否需要急运\n");
	fprintf(STDOUT, "0.不需急运\n");
	fprintf(user, "0.不需急运\n");
	fprintf(STDOUT, "1.急运\n");
	fprintf(user, "1.急运\n");
	char j[5];//5
	while (1)
	{
		fscanf(STDIN, "%2s%*[^\n]", &j);
		int len = strlen(j);
		if (len > 1)
		{
			fprintf(STDOUT, "输入错误，请重新输入0或1\n");
			fprintf(user, "输入错误，请重新输入0或1\n");
		}
		else
		{
			if (j[0] == '0' || j[0] == '1')
			{
				break;
			}
			else
			{
				fprintf(STDOUT, "输入错误，请重新输入0或1\n");
				fprintf(user, "输入错误，请重新输入0或1\n");
			}
		}
	}

	if (g[0] == '1') status += 1;
	if (b[0]=='1') status += 2;
	if (j[0]=='1') status += 4;
	PackageData pack = CreatePackage(PhoneNumber, name,
		(int)distance * 100, (int)volume * 100, (int)weight * 100, PlaceFrom, PlaceTo, status);
	UserData *puser = (UserData*)Trie_Find(&UserManager, pack.PhoneNumber);
	int t;
	t = List_Find_Package(&courier->vehicle, &pack, sizeof(PackageData) );
	if (t == 0)
	{
		fprintf(STDOUT, "输入的包裹信息有误，请重新输入\n");
		fprintf(user, "输入的包裹信息有误，请重新输入\n");
	}
	if (t == 1)
	{
		int damage = 5;
		if (status & 1)
		{
			damage = 20;
		}
		if (!InputType) system("cls");
		FILE* user1 = UserOutput(PhoneNumber);
		fprintf(STDOUT, "重新发货并支付赔偿金 %d 元\n", damage);
		fprintf(user, "重新发货并支付赔偿金 %d 元\n", damage);
		char msg[200];
		sprintf(msg, "很抱歉在运输过程中损坏了您的货物，已赔偿您%d元并重新运输", damage);
		fprintf(user1, "很抱歉在运输过程中损坏了您的货物，已赔偿您%d元并重新运输", damage);
		List_Insert(&puser->message, msg, sizeof(msg));
		if (puser->message.count > 10)List_DeleteTheEarliest(&puser->message);
		fclose(user);
		fclose(user1);
	}
}
