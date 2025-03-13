#include "UserData.h"
#include <stdlib.h>
#include <string.h>

UserData CreateUser(long long PhoneNumber, char *name, char *password, int UserStatus, int TransStatus, int TransSize){
	UserData user;

	int NameLen = strlen(name) + 1;
	user.name = (char *)malloc(sizeof(char) * NameLen);
	strcpy(user.name, name);

	int PassWordLen = strlen(password);
	user.password = (char *)malloc(sizeof(char) * PassWordLen);
	strcpy(user.password, password);

	user.PhoneNumber = PhoneNumber;
	user.UserStatus = UserStatus;
	user.TransStatus = TransStatus;
	user.TransSize = TransSize;
	
	user.level = 1;
	user.PackageCount = 0;
}

void DeleteUser(UserData *user){
	free(user->name);
	free(user->password);
	memset(user, 0, sizeof(user) );
}
