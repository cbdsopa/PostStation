#include "UserData.h"
#include "user.h"
#include "FileManage.h"
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Trie.h"
#include "PackageData.h"
//用户注册
UserData *user_register()
{
	if(!InputType) system("cls");
	long long phone;
	char name[32],pass[21];
	int us, ts, tsize;
	char phonenumber[15];
	fprintf(STDOUT,"请输入11位手机号:");
	while(1)
	{
		fscanf(STDIN,"%11s", phonenumber);
		int bool=1;
		for(int i=0;i<11;i++)
		{
			if(phonenumber[i]<'0'||phonenumber[i]>'9') bool=0;
		}
		if(bool==0) fprintf(STDOUT,"手机号格式错误,请重新输入:");
		else
		{
			phone=atoll(phonenumber);
			break;
		}
	}
	fprintf(STDOUT,"请输入用户名:");
	fscanf(STDIN,"%s", name);
	fprintf(STDOUT,"请输入密码:");
	fscanf(STDIN,"%s", pass);
	int bbs=0,us=0;
	fprintf(STDOUT,"下面请选择对应的用户类型:\n");
	fprintf(STDOUT,"请问你是学生吗?(1:是,2:否):");
	int yui=1;
	while(1)
	{
		fscanf(STDIN,"%1d",&bbs);
		if(bbs==1) 
		{
			us|=1;
			break;
		}
		else if(bbs==2) 
		{
			us|=0;
			yui=0;
			break;
		}
		else 
		{
			fprintf(STDOUT,"请输入1或2:");
		}
	}
	if(yui==0)
	{
		fprintf(STDOUT,"请问你是老人吗?(1:是,2:否):");
		while(1)
		{
			fscanf(STDIN,"%1d",&bbs);
			if(bbs==1) 
			{
				us|=2;
				break;
			}
			else if(bbs==2) 
			{
				us|=0;
				break;
			}
			else
			{
				fprintf(STDOUT,"请输入1或2:");		
			}
		}
		fprintf(STDOUT,"请问你是退役军人吗?(1:是,2:否):");
		while(1)
		{
			fscanf(STDIN,"%1d",&bbs);
			if(bbs==1)
			{
				us|=4;
				break;
			}
			else if(bbs==2)
			{
				us|=0;
				break;
			}
			else
			{
				fprintf(STDOUT,"请输入1或2:");
			}
		}
	}
	fprintf(STDOUT,"请问你是会员吗?(1:是,2:否):");
	while(1)
	{
		fscanf(STDIN,"%1d",&bbs);
		if(bbs==1)
		{
			us|=8;
			break;
		}
		else if(bbs==2)	
		{
			us|=0;
			break;
		}
		else
		{
			fprintf(STDOUT,"请输入1或2:");
		}
	}
	fprintf(STDOUT,"请问你是管理员吗?(1:是,2:否):");
	while(1)
	{
		fscanf(STDIN,"%1d",&bbs);
		if(bbs==1)
		{
			us|=16;
			break;
		}
		else if(bbs==2)
		{
			us|=0;
			break;
		}
		else
		{
			fprintf(STDOUT,"请输入1或2:");
		}
	}
	fprintf(STDOUT,"请问你是快递员吗?(1:是,2:否):");
	while(1)
	{
		fscanf(STDIN,"%1d",&bbs);
		if(bbs==1)
		{
			us|=32;
			break;
		}
		else if(bbs==2)
		{
			us|=0;
			break;
		}
		else
		{
			fprintf(STDOUT,"请输入1或2:");	
		}
	}
	int transport=0;
	int tsize=0;
	if(bbs==1) 
	{
		us|=32;
		fprintf(STDOUT,"请输入你的运输方式(1.冷藏,2.飞机):");
		while(1)
		{
			fscanf(STDIN,"%1d",&transport);
			if(transport!=1 || transport!=2)	fprintf(STDOUT,"请输入1或2:");
			else break;
		}
		fprintf(STDOUT,"请输入车辆大小(1-500):");
		while(1)
		{
			fscanf(STDIN,"%3d",&tsize);
			if(tsize<1 || tsize>500) fprintf(STDOUT,"请输入1-500:");
			else break;
		}
	}
	UserData reguser=CreateUser(phone, name, pass, us, ts, tsize);
	Trie_Insert(&UserManager, phone, &reguser, sizeof(UserData));
	return (UserData *)Trie_Find(&UserManager, phone);
}
//用户注销
void user_logout()
{
	if(!InputType) system("cls");
	long long numb;
	char phonenumber[15];
	fprintf(STDOUT,"请输入11位手机号:");
	while(1)
	{
		fscanf(STDIN,"%11s", phonenumber);
		int bool=1;
		for(int i=0;i<11;i++)
		{
			if(phonenumber[i]<'0'||phonenumber[i]>'9') bool=0;
		}
		if(bool==0) fprintf(STDOUT,"手机号格式错误,请重新输入:");
		else
		{
			numb=atoll(phonenumber);
			break;
		}
	}
	FILE* user = UserOutput(numb);
	if (Trie_Find(&UserManager, numb) == NULL)
	{
		fprintf(STDOUT,"未查询到该用户信息,请重新录入.\n");
		fprintf(user,"未查询到该用户信息,请重新录入.\n");
		return;
	}
	char passw[21];
	UserData *User = Trie_Find(&UserManager, numb);
	fprintf(STDOUT,"请输入密码验证");
	fprintf(user,"请输入密码验证");
	int count=0; //计数器
	while(1)
	{
		fscanf(STDIN,"%21s", passw);
		if(strcmp(User->password,passw) == 0)
		{
			fprintf(STDOUT,"密码验证成功!\n");
			fprintf(user,"密码验证成功!\n");
			break;
		} 
		else if(User->password!=passw && count<3)
		{
			++count;
			fprintf(STDOUT,"密码验证错误,请重新输入:");
			fprintf(user,"密码验证错误,请重新输入:");
		}
		else if(strcmp(User->password,passw)!=0 && count==3)
		{
			fprintf(STDOUT,"密码验证错误,已达到最大验证次数,请重新操作\n");
			fprintf(user,"密码验证错误,已达到最大验证次数,请重新操作\n");
			return;
		}
	}
	char* sd = User->name;
	if (User->PackageCount > 0)
	{
		fprintf(STDOUT,"您还有%d个待取包裹,请全部取走后再注销!\n", User->PackageCount);
		fprintf(user,"您还有%d个待取包裹,请全部取走后再注销!\n", User->PackageCount);
		return;
	}
	fprintf(STDOUT,"您在本驿站已没有未取包裹,可以注销!\n");
	fprintf(user,"您在本驿站已没有未取包裹,可以注销!\n");
	fclose(user);
	int poi = Trie_Insert(&UserManager, numb, NULL, 0);
	fprintf(STDOUT,"用户%s注销成功!", sd);
	return;
}
//用户登录
UserData* user_login()
{
	if(!InputType) system("cls");
	long long numb;
	char phonenumber[15];
	fprintf(STDOUT,"请输入11位手机号:");
	while(1)
	{
		fscanf(STDIN,"%11s", phonenumber);
		int bools=1;
		for(int i=0;i<11;i++)
		{
			if(phonenumber[i]<'0'||phonenumber[i]>'9') bools=0;
		}
		if(bools==0) fprintf(STDOUT,"手机号格式错误,请重新输入:");
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
	return user;
}
//待取包裹查询
void user_check(UserData* user)
{
	if(!InputType) system("cls");
	long long number=user->PhoneNumber;
	FILE* User = UserOutput(number);
	fprintf(STDOUT,"您好用户%s,您还有%d个待取包裹\n", user->name,user->PackageCount);
	fprintf(user,"您好用户%s,您还有%d个待取包裹\n", user->name,user->PackageCount );
	fprintf(STDOUT,"下面是待取的取件码:\n");
	fprintf(user,"下面是待取的取件码:\n");
	ListNode* current = user->package.head;
	int index = 1;
	while (current!= NULL)
	{
		PackageData* package = (PackageData*)current->data;
		fprintf(STDOUT,"第%d个待取包裹的取件码: %s\n", index, package->PackageCode);
		fprintf(User,"第%d个待取包裹的取件码: %s\n", index, package->PackageCode);
		current = current->next;
		index++;
	}
	fclose(User);
}
