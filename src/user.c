// 吉庆喆
#include "UserData.h"
#include "user.h"
#include "FileManage.h"
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Trie.h"
#include "PackageData.h"
#include "WarePositionData.h"
#include "WareInOut.h"
#include "MyString.h"
//用户注册
UserData *user_register()
{
	if(!InputType) system("cls");
	long long phone;
	char name[35],pass[30],checkpass[21];
	int  ts=0;
	char phonenumber[15];
	fprintf(STDOUT,"请输入11位手机号:\n");
	while(1)
	{
		fscanf(STDIN,"%12s%*[^\n]", phonenumber);
		int bool=1;
		int numlenth=strlen(phonenumber);
		if(numlenth!=11) bool=0;
		else 
		{
			for(int i=0;i<11;i++)
			{
				if(phonenumber[i]<'0'||phonenumber[i]>'9') bool=0;
			}
		}
		if(bool==0  || phonenumber[0]!='1') fprintf(STDOUT,"手机号格式错误,请重新输入:\n");
		else
		{
			phone=atoll(phonenumber);
			break;
		}
	}
	if (Trie_Find(&UserManager, phone) != NULL)
	{
		fprintf(STDOUT,"该手机号已注册。\n");
		return NULL;
	}
	fprintf(STDOUT,"请输入用户名(不超过10字):\n");
	while(1)
	{
		fscanf(STDIN,"%32s%*[^\n]", name);
		int namecheck=strlen(name);
		if(namecheck>30) 
		{
			fprintf(STDOUT,"名字输入长度超出限制,请重新输入:\n");
			continue;
		}
		else 
		{
			int namecount=realen(name);
			if(namecount>10)
			{
				fprintf(STDOUT,"名字输入长度超出限制,请重新输入:\n");
			}
			else break;
		}
		
	}
	fprintf(STDOUT,"请输入密码(20位以内):\n");
	while(1)
	{
		fscanf(STDIN,"%25s%*[^\n]", pass);
		if(strlen(pass)!=realen(pass))
		{
			fprintf(STDOUT,"密码请不要输入中文!\n请重新设置密码:");
			continue;
		}
		if(strlen(pass)>20)
		{
			fprintf(STDOUT,"请输入20位以内的密码!\n");
		}
		else
		{
			fprintf(STDOUT,"请再次输入密码以确认:\n");
			fscanf(STDIN,"%25s%*[^\n]",checkpass);
			if(strncmp(pass,checkpass,20)==0) break;
			else
			{
				fprintf(STDOUT,"两次密码输入不一致!\n请重新设置密码:\n");
			}
		}
		
	}
	int us=0;
	char bs[5];
	fprintf(STDOUT,"下面请选择对应的用户类型:\n");
	fprintf(STDOUT,"请问你是学生吗?(1:是,2:否):\n");
	int yui=1;
	while(1)
	{
		fscanf(STDIN,"%2s%*[^\n]",bs);
		if(strlen(bs)>1) 
		{
			fprintf(STDOUT,"请输入1或2:\n");
		}
		else 
		{
			if(bs[0]=='1')
			{
				us|=1;
				break;
			}
			else if(bs[0]=='2')
			{
				us|=0;
				yui=0;
				break;
			}
			else 
			{
				fprintf(STDOUT,"请输入1或2:\n");
			}
		}
	}
	char cs[5];
	if(yui==0)
	{
		fprintf(STDOUT,"请问你是老人吗?(1:是,2:否):\n");
		while(1)
		{
			fscanf(STDIN,"%2s%*[^\n]",cs);
			if(strlen(cs)> 1) 
			{
				fprintf(STDOUT,"请输入1或2:\n");
			}
			else
			{
				if(cs[0]=='1')
				{
					us|=2;
					break;
				}
				else if(cs[0]=='2')
				{
					us|=0;
					break;
				}
				else 
				{
					fprintf(STDOUT,"请输入1或2:\n");	
				}
			}
		}
		char dsi[5];
		fprintf(STDOUT,"请问你是退役军人吗?(1:是,2:否):\n");
		while(1)
		{
			fscanf(STDIN,"%2s%*[^\n]",dsi);
			if(strlen(dsi)>1)
			{
				fprintf(STDOUT,"请输入1或2:\n");
			} 
			else
			{
				if(dsi[0]=='1')
				{
					us|=4;
					break;
				}
				else if(dsi[0]=='2')
				{
					us|=0;
					break;
				}
				else 
				{
					fprintf(STDOUT,"请输入1或2:\n");
				}
			}
		}
	}
	char ti[5];
	fprintf(STDOUT,"请问你是会员吗?(1:是,2:否):\n");
	while(1)
	{
		fscanf(STDIN,"%2s%*[^\n]",ti);
		if(strlen(ti)>1) 
		{
			fprintf(STDOUT,"请输入1或2:\n");
		}
		else 
		{
			if(ti[0]=='1')
			{
				us|=8;
				break;
			}
			else if(ti[0]=='2')
			{
				us|=0;
				break;
			}
			else
			{
				fprintf(STDOUT,"请输入1或2:\n");
			}
		}
	}
	int bool_register=0;
	char ko[5];
	fprintf(STDOUT,"请问你是管理员吗?(1:是,2:否):\n");
	while(1)
	{
		fscanf(STDIN,"%2s%*[^\n]",ko);
		if(strlen(ko)>1) 
		{
			fprintf(STDOUT,"请输入1或2:\n");
		}
		else 
		{
			if(ko[0]=='1')
			{
				us|=16;
				bool_register=1;
				break;
			}
			else if(ko[0]=='2')
			{
				us|=0;
				break;
			}
			else
			{
				fprintf(STDOUT,"请输入1或2:\n");
			}

		}
	}
	char zbh[5];
	fprintf(STDOUT,"请问你是快递员吗?(1:是,2:否):\n");
	while(1)
	{
		fscanf(STDIN,"%2s%*[^\n]",zbh);
		if(strlen(zbh)>1)
		{
			fprintf(STDOUT,"请输入1或2:\n");
		}
		else 
		{
			if(zbh[0]=='1')
			{
				us|=32;
				break;
			}
			else if(zbh[0]=='2')
			{
				us|=0;
				break;
			}
			else 
			{
				fprintf(STDOUT,"请输入1或2:\n");	
			}
		}	
	}
	int transport=0;
	int tsize=0;
	if(zbh[0]=='1') 
	{
		char gxa[5];
		fprintf(STDOUT,"运输方式是冷藏吗?(1:是,2:否):\n");
		while(1)
		{
			fscanf(STDIN,"%2s%*[^\n]",gxa);
			if(strlen(gxa)>1) 
			{
				fprintf(STDOUT,"请输入1或2:\n");
			}
			else 
			{
				if(gxa[0]=='1')
				{
					ts|=1;
					break;
				}
				else if(gxa[0]=='2')
				{
					ts|=0;
					break;
				}
				else 
				{
					fprintf(STDOUT,"请输入1或2:\n");
				}
			}
		}
		fprintf(STDOUT,"运输方式是飞机吗?(1:是,2:否):\n");
		char wt[5];
		while(1)
		{
			fscanf(STDIN,"%2s%*[^\n]",wt);
			if(strlen(wt)>1)
			{
				fprintf(STDOUT,"请输入1或2:\n");
			}
			else 
			{
				if(wt[0]=='1')
				{
					ts|=2;
					break;
				}
				else if(wt[0]=='2')
				{
					ts|=0;
					break;
				}
				else
				{
					fprintf(STDOUT,"请输入1或2:\n");
				}
			}
		}
		fprintf(STDOUT,"请输入车辆大小(1-500):\n");
		char tts[10];
		while(1)
		{
			fscanf(STDIN,"%5s%*[^\n]",tts);
			if(strlen(tts)>3) 
			{
				fprintf(STDOUT,"请输入1-500:\n");
			} 
			else 
			{
				int yuhg=1;
				for(int i=0;i<strlen(tts);i++)
				{
					if(tts[i]<'0' || tts[i]>'9') yuhg=0;
				}
				if(yuhg)
                {
                    tsize=atoi(tts);
                    if(tsize>500 || tsize<0) fprintf(STDOUT,"请输入1-500:\n");
                    else break;
                }
				else 
				{
					fprintf(STDOUT,"请输入1-500:\n");
				}
			}
		}
	}
	fprintf(STDOUT, "注册成功！\n");
	UserData reguser=CreateUser(phone, name, pass, us, ts, tsize);
	Trie_Insert(&UserManager, phone, &reguser, sizeof(UserData));
	if(bool_register) List_Insert(&ManagerAvailable, &reguser,sizeof(UserData));
	return (UserData *)Trie_Find(&UserManager, phone);
}
//用户注销
void user_logout(UserData* User)
{
	if(!InputType) system("cls");
	FILE* user = UserOutput(User->PhoneNumber);
	char passw[21];
	//UserData *User = Trie_Find(&UserManager, numb);
	fprintf(STDOUT,"请输入密码验证:\n");
	fprintf(user,"请输入密码验证:\n");
	int count=0; //计数器
	while(1)
	{
		fscanf(STDIN,"%20s%*[^\n]", passw);
		if(strncmp(User->password, passw, 21) == 0)
		{
			fprintf(STDOUT,"密码验证成功!\n");
			fprintf(user,"密码验证成功!\n");
			break;
		} 
		else if(strncmp(User->password, passw, 21) != 0 && count<3)
		{
			++count;
			fprintf(STDOUT,"密码验证错误,请重新输入:\n");
			fprintf(user,"密码验证错误,请重新输入:\n");
		}
		else if(strncmp(User->password, passw, 21) != 0 && count==3)
		{
			fprintf(STDOUT,"密码验证错误,已达到最大验证次数,请重新操作\n");
			fprintf(user,"密码验证错误,已达到最大验证次数,请重新操作\n");
			fclose(user);
			return;
		}
	}
	char* sd = User->name;
	if (User->package.count!=0 && User->vehicle.count!=0)
	{
		fprintf(STDOUT,"您还有待取包裹和正在运输的包裹,请全部取走后再注销!\n");
		fprintf(user,"您还有待取包裹和正在运输的包裹,请全部取走后再注销!\n");
		fclose(user);
		return;
	}
	else if(User->package.count==0 && User->vehicle.count!=0)
	{
		fprintf(STDOUT,"您还有待取包裹,请全部取走后再注销!\n");
		fprintf(user,"您还有待取包裹,请全部取走后再注销!\n");
		fclose(user);
		return;
	}
	else if(User->package.count!=0 && User->vehicle.count==0)
	{
		fprintf(STDOUT,"您还有正在运输的包裹,请全部取走后再注销!\n");
		fprintf(user,"您还有正在运输的包裹,请全部取走后再注销!\n");
		fclose(user);
		return;
	}
	fprintf(STDOUT,"您在本驿站已没有未取包裹,可以注销!\n");
	fprintf(user,"您在本驿站已没有未取包裹,可以注销!\n");
	int poi = Trie_Insert(&UserManager, User->PhoneNumber, NULL, sizeof(UserData) );
	fprintf(STDOUT,"用户%s注销成功!", sd);
	fprintf(user,"用户%s注销成功!", sd);
	fclose(user);
	return;
}
//用户登录
UserData* user_login()
{
	if(!InputType) system("cls");
	long long numb;
	char phonenumber[15];
	fprintf(STDOUT,"请输入11位手机号:\n");
	while(1)
	{
		fscanf(STDIN,"%12s%*[^\n]", phonenumber);
		int bools=1;
		int numlenth=strlen(phonenumber);
		if(numlenth!=11) bools=0;
		else
		{
			for(int i=0;i<11;i++)
			{
				if(phonenumber[i]<'0'||phonenumber[i]>'9') bools=0;
			}
		}
		if(bools==0  || phonenumber[0]!='1') fprintf(STDOUT,"手机号格式错误,请重新输入:\n");
		else
		{
			numb=atoll(phonenumber);
			break;
		}
	}
	if (Trie_Find(&UserManager, numb) == NULL)
	{
		fprintf(STDOUT,"未查询到该用户信息,请先注册用户.\n");
		return NULL;
	}
	UserData* user = Trie_Find(&UserManager, numb);
	fprintf(STDOUT,"请输入密码验证:\n");
	char passw[21];
	int count=0; //计数器
	while(1)
	{
		fscanf(STDIN,"%21s%*[^\n]", passw);
		if(strncmp(user->password, passw, 20) == 0)
		{
			fprintf(STDOUT,"密码验证成功!\n");
			break;
		} 
		else if(strncmp(user->password, passw, 20) != 0 && count<3)
		{
			++count;
			fprintf(STDOUT,"密码验证错误,请重新输入:");
		}
		else if(strncmp(user->password, passw, 20) != 0 && count==3)
		{
			fprintf(STDOUT,"密码验证错误,已达到最大验证次数,请重新操作\n");
			return NULL;
		}
	}
	return user;
}
//待取包裹查询
void user_check(UserData* user)
{
	if(!InputType) system("cls");
	long long number=user->PhoneNumber;
	FILE* User = UserOutput(number);
	fprintf(STDOUT,"您好用户%s,您还有%d个待取包裹\n", user->name,user->package.count);
	fprintf(User,"您好用户%s,您还有%d个待取包裹\n", user->name,user->package.count);
	fprintf(STDOUT,"下面是待取的取件码:\n");
	fprintf(User,"下面是待取的取件码:\n");
	ListNode* current = user->package.head;
	int index = 1;
	while (current!= NULL)
	{
		PackageData* package = (PackageData*)current->data;
		fprintf(STDOUT,"第%d个待取包裹，货架位置：%d 取件码: %s\n", index,package->posID, package->PackageCode);
		fprintf(User,"第%d个待取包裹，货架位置：%d 取件码: %s\n", index,package->posID, package->PackageCode);
		current = current->next;
		index++;
	}
	fclose(User);
}
//用户取货
void user_packageout(UserData* user)
{
	
	if(!InputType) system("cls");
	long long number=user->PhoneNumber;
	FILE* User = UserOutput(number);
	fprintf(STDOUT,"请输入货架位置");
	fprintf(User,"请输入货架位置");
	int posid;
	fscanf(STDIN,"%6d%*[^\n]",&posid);
	for(ListNode *now = WarePosition.head; now != NULL; now = now->next)
	{
		WarePostionData *WarePos = (WarePostionData *)now->data;
		if(posid==WarePos->ID) 
		{
			char nowpick[23];
			strcpy(nowpick, WarePos->package.PackageCode);
			char checkpick[23];
			fprintf(STDOUT,"请输入取件码验证:\n");
			fprintf(User,"请输入取件码验证:\n");
			fscanf(STDIN,"%22s%*[^\n]",checkpick);
			int pol=0;
			if(WarePos->package.PhoneNumber==user->PhoneNumber) pol=1;
			if((strncmp(checkpick,nowpick, 8) ==0 || InputType) && pol==1) 
			{
				fprintf(STDOUT,"取货成功!\n");
				fprintf(User,"取货成功!");
				fprintf(STDOUT,"当前取出的货物信息:\n");
				fprintf(User,"当前取出的货物信息:\n");
				fprintf(STDOUT,"收货人名字:%s\n",WarePos->package.name);
				fprintf(User,"收货人名字:%s\n",WarePos->package.name);
				fprintf(STDOUT,"发货地%s距离收货地%s:%.2lf公里\n",WarePos->package.PlaceFrom,WarePos->package.PlaceTo,WarePos->package.distance / 100.0);
				fprintf(User,"发货地%s距离收货地%s:%.2lf公里\n",WarePos->package.PlaceFrom,WarePos->package.PlaceTo,WarePos->package.distance / 100.0);
				fprintf(STDOUT,"货物重量:%.2lfkg\n",WarePos->package.weight / 100.0);
				fprintf(User,"货物重量:%.2lfkg\n",WarePos->package.weight / 100.0);
				user->PackageCount++;
				int pcc=user->PackageCount;
				if(pcc < 10) user->level = 1;
				else if(pcc>=10 && pcc<20) user->level=2;
				else if(pcc>=20) user->level=3;
				List_Delete(&user->package,&WarePos->package,sizeof(PackageData));
				WareOut(&ManagerAvailable,WarePos->package, &WarePosition,&WarePackage);
				fclose(User);
				return;
			}
			else if((strncmp(checkpick,nowpick, 8) ==0 || InputType) && pol==0)
			{
				fprintf(STDOUT,"当前货物非本人快递,请问是否帮用户%s代取?(1是2否)",WarePos->package.name);
				fprintf(User,"当前货物非本人快递,请问是否帮用户%s代取?(1是2否)",WarePos->package.name);
				int we;
				while(1)
				{
					fscanf(STDIN,"%2d%*[^\n]",we);
					if(we==1)
					{
						fprintf(STDOUT,"用户%s帮用户%s代取成功!",user->name,WarePos->package.name);
						fprintf(User,"用户%s帮用户%s代取成功!",user->name,WarePos->package.name);
						fprintf(STDOUT,"收货人名字:%s\n",WarePos->package.name);
						fprintf(User,"收货人名字:%s\n",WarePos->package.name);
						fprintf(STDOUT,"发货地%s距离收货地%s:%.2lf公里\n",WarePos->package.PlaceFrom,WarePos->package.PlaceTo,WarePos->package.distance / 100.0);
						fprintf(User,"发货地%s距离收货地%s:%.2lf公里\n",WarePos->package.PlaceFrom,WarePos->package.PlaceTo,WarePos->package.distance / 100.0);
						fprintf(STDOUT,"货物重量:%.2lfkg\n",WarePos->package.weight / 100.0);
						fprintf(User,"货物重量:%.2lfkg\n",WarePos->package.weight / 100.0);
						UserData *replace=Trie_Find(&UserManager,WarePos->package.PhoneNumber);
						List_Delete(&replace->package,&WarePos->package,sizeof(PackageData));
						WareOut(&ManagerAvailable,WarePos->package, &WarePosition,&WarePackage);
						replace->PackageCount++;
						int vcc=replace->PackageCount;
						if(vcc < 10) replace->level=1;
						else if(vcc>=10 && vcc<20) replace->level=2;
						else if(vcc>=20) replace->level=3;
						fclose(User);
						return ;
					}
					else if(we==2)
					{
						fprintf(STDOUT,"用户%s的货物未代取!",WarePos->package.name);
						fprintf(User,"用户%s的货物未代取!",WarePos->package.name);
					}
					else{
						fprintf(STDOUT,"请输入1或2:\n");
						fprintf(User,"请输入1或2:\n");
					}
				}
			}
			else
			{
				fprintf(STDOUT,"取货码验证错误,请核对后输入!\n");
				fprintf(User,"取货码验证错误,请核对后输入!\n");

				fclose(User);
				return;
			}
		}
	}
	fprintf(STDOUT,"未找到货架\n");
	fprintf(User,"未找到货架\n");
	fclose(User);
}

 //未读消息查询
void user_message(UserData* user)
{
	
	if(!InputType) system("cls");
    FILE *User=UserOutput(user->PhoneNumber);
    for(ListNode* p=user->message.head;p;p=p->next)
    {
        char *str=(char*)p->data;
        fprintf(STDOUT,"%s\n",str);
        fprintf(User,"%s\n",str);
    }
    List_Destroy(&user->message);
	fclose(User);
}
