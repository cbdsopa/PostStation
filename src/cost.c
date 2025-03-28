#include"cost.h"
#include<stdio.h>
#include<math.h>

double expense(UserData user,PackageData pack)
{
	double base = 0, extra = 0, discount = 1, vip = 1, grade = 1, total = 0, Total;
	if (pack.distance<=50)
	{
		base = pack.distance * 3;
	}
	else
	{
		base = (pack.distance - 50) * 1.5 + 150;
	}
	if (pack.volume>36000&&pack.volume<=60000)
	{
		extra += 0.1;
	}
	if (pack.volume>60000)
	{
		extra += 0.15;
	}
	switch (pack.status)
	{
	case 1:extra += 0.1;
		break;
	case 2:extra += 0.15;
		break;
	case 4:extra += 0.2;
		break;	
	}
	if (pack.weight>100)
	{
		extra += 0.2;
	}
	switch (user.UserStatus)
	{
	case 1: discount = 0.9;
		break;
	case 2:discount = 0.85;
		break;
	case 4:discount = 0.6;
		break;
	case 8:vip = 0.9;
		break;
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
