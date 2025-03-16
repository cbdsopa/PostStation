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

	int NameLen = strlen(name) + 1;
	package.name = (char *)malloc(sizeof(char) * NameLen);
	strcpy(package.name, name);
	int FromLen = strlen(PlaceFrom) + 1;
	package.PlaceFrom = (char *)malloc(sizeof(char) * FromLen);
	strcpy(package.PlaceFrom, PlaceFrom);
	int ToLen = strlen(PlaceTo) + 1;
	package.PlaceTo = (char *)malloc(sizeof(char) * ToLen);
	strcpy(package.PlaceTo, PlaceTo);
}
int DeletePackage(PackageData *package){
	if(package == NULL) return -1;
	if(package->name != NULL) free(package->name);
	if(package->PlaceFrom != NULL) free(package->PlaceFrom);
	if(package->PlaceTo != NULL) free(package->PlaceTo);
	memset(package, 0, sizeof(package) );
	return 0;
}
