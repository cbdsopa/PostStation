#include "UserData.h"
#include <stdlib.h>
#include <string.h>
#include "List.h"

UserData CreateUser(long long PhoneNumber, char *name, char *password, int UserStatus, int TransStatus, int TransSize){
	UserData user;

	strcpy(user.name, name);
	strcpy(user.password, password);

	user.PhoneNumber = PhoneNumber;
	user.UserStatus = UserStatus;
	user.TransStatus = TransStatus;
	user.TransSize = TransSize;
	
	user.level = 1;
	user.PackageCount = 0;

	user.package = List_Init();
	user.vehicle = List_Init();
	return user;
}
