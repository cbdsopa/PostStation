#pragma once

#include <stdlib.h>
#include "UserData.h"

UserData *user_register(); //用户注册
UserData *user_login();  //用户登录
void user_logout(); //用户注销
void user_check(UserData *user); //未取包裹查询

