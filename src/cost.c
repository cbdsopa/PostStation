// 汤嘉敏
#include"cost.h"
#include<stdio.h>
#include<math.h>

double expense(UserData user,PackageData pack)
{
	double base = 0, extra = 0, discount = 1, vip = 1, grade = 1, total = 0, Total;
	if (pack.distance<=5000)
	{
		base = pack.distance / 100.0 * 3;
	}
	else
	{
		base = (pack.distance - 5000) / 100.0 * 1.5 + 150;
	}
	if (pack.volume>3600000&&pack.volume<=6000000)
	{
		extra += 0.1;
	}
	if (pack.volume>6000000)
	{
		extra += 0.15;
	}
	if (pack.status&1)
	{
		extra += 0.1;
	}
	if (pack.status & 2)
	{
		extra += 0.15;
	}
	if (pack.status & 4)
	{
		extra += 0.2;
	}
	if (pack.weight>100)
	{
		extra += 0.2;
	}
	if (user.UserStatus&1)
	{
		discount = 0.9;
	}
	if (user.UserStatus & 2)
	{
		discount = 0.85;
	}
	if (user.UserStatus & 4)
	{
		discount = 0.6;
	}
	if (user.UserStatus & 8)
	{
		vip = 0.9;
	}
	switch (user.level)
	{
	case 1:grade = 1;
		break;
	case 2:grade = 0.95;
		break;
	case 4:grade = 0.9;
		break;
	}
	total = base * (1 + extra) * discount * vip * grade;
	Total = round(total * 100) / (100);
	return Total;
}
