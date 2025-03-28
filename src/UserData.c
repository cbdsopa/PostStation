#include "UserData.h"
#include <stdlib.h>
#include <string.h>
#include "List.h"

UserData CreateUser(long long PhoneNumber, char *name, char *password, int UserStatus, int TransStatus, int TransSize){
	UserData user;

	strncpy(user.name, name, 31);
	strncpy(user.password, password, 21);

	user.PhoneNumber = PhoneNumber;
	user.UserStatus = UserStatus;
	user.TransStatus = TransStatus;
	user.TransSize = TransSize;
	
	user.level = 1;
	user.PackageCount = 0;

	user.package = List_Create();
	user.vehicle = List_Create();
	user.message = List_Create();
	return user;
}
