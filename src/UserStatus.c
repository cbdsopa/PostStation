// 汤嘉敏
#include"UserStatus.h"
#include"FileManage.h"
#include"Trie.h"
extern Trie UserManager;
extern List ManagerAvailable;
void ChangeStatus(UserData *user)
{
	if (!InputType) system("cls");//清屏
	int status,t;
	UserData* puser;
	FILE* User = UserOutput(user->PhoneNumber);
	fprintf(STDOUT, "请选择你需要改变的状态\n");
	fprintf(User, "请选择你需要改变的状态\n");
	fprintf(STDOUT, "1.设置忙碌\n");
	fprintf(User, "1.设置忙碌\n");
	fprintf(STDOUT, "2.取消忙碌\n");
	fprintf(User, "2.取消忙碌\n");
	fscanf(STDIN, "%d", &t);
	puser = (UserData*)Trie_Find(&UserManager, user->PhoneNumber);
	if (t==2)
	{
		
		if (puser->UserStatus & 64) {
			puser->UserStatus -= 64;
			fprintf(STDOUT, "您已取消忙碌状态\n");
			fprintf(User, "您已取消忙碌状态\n");
			if (puser->UserStatus & 16) 
			{
				int k;
				k = List_Insert(&ManagerAvailable, &user, sizeof(user));
			}
		}
	}
	if (t==1)
	{
		puser->UserStatus |= 64;
		if (puser->UserStatus&16)
		{
			int s;
			s=List_Delete(&ManagerAvailable,&user,sizeof(user) );
				if (s==0)
				{
					fprintf(STDOUT, "您已设置好忙碌状态\n");
					fprintf(User, "您已设置好忙碌状态\n");
				}
				else
				{
					fprintf(STDOUT, "请您核对信息是否输入错误\n");
					fprintf(User, "请您核对信息是否输入错误\n");
				}
		}
		else
		{
			fprintf(STDOUT, "您已设置好忙碌状态\n");
			fprintf(User, "您已设置好忙碌状态\n");
		}
	}
	fclose(User);
}