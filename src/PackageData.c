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

	strcpy(package.name, name);
	strcpy(package.PlaceFrom, PlaceFrom);
	strcpy(package.PlaceTo, PlaceTo);
	
	
	return package;
}
