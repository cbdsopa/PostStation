#include "UserData.h"
#include <stdlib.h>
#include <string.h>

UserData CreateUser(long long PhoneNumber, char *name, char *password, int UserStatus, int TransStatus, int TransSize){
	UserData user;

	int NameLen = strlen(name) + 1;
	user.name = (char *)malloc(sizeof(char) * NameLen);
	strcpy(user.name, name);
	int PasswordLen = strlen(password) + 1;
	user.password = (char *)malloc(sizeof(char) * PasswordLen);
	strcpy(user.password, password);

	user.PhoneNumber = PhoneNumber;
	user.UserStatus = UserStatus;
	user.TransStatus = TransStatus;
	user.TransSize = TransSize;
	
	user.level = 1;
	user.PackageCount = 0;
}

int DeleteUser(UserData *user){
	if(user == NULL) return -1;
	if(user->name != NULL) free(user->name);
	if(user->password != NULL) free(user->password);
	memset(user, 0, sizeof(user) );
	return 0;
}
