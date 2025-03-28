#include "PackageData.h"
#include <stdlib.h>
#include <string.h>

PackageData CreatePackage(long long PhoneNumber, char *name, double distance, double volume, double weight,
	char *PlaceFrom, char *PlaceTo, int status){
	PackageData package;

	package.PhoneNumber = PhoneNumber;
	package.distance = distance;
	package.volume = volume;
	package.weight = weight;
	package.status = status;

	strncpy(package.name, name, 31);
	strncpy(package.PlaceFrom, PlaceFrom, 61);
	strncpy(package.PlaceTo, PlaceTo, 61);
	
	package.posID = 0;

	for(int i = 0; i < 8; ++i){
		int num = rand();
		num %= 62;
		if(num < 10){
			package.PackageCode[i] = '0' + num;
		}else{
			num -= 10;
			if(num < 26) 
				package.PackageCode[i] = 'a' + num;
			else 
				package.PackageCode[i] = 'A' + num - 26;
		}
	}
	package.PackageCode[8] = '\0';
	return package;
}
