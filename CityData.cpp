#include "CityData.h"

CityData::CityData()	//constructor
{
	LocationId = 0;		//allocate citydata memory
	name = new char[50];
	country = new char[50];
}

CityData::~CityData()	//destructor
{
}

int CityData::GetLocationId()	//location id
{
	return this->LocationId;
}

char * CityData::Getname()	//city name
{
	return this->name;
}

char * CityData::Getcountry()	//city country
{
	return this->country;
}

void CityData::SetLocationId(int LocationId)	//set location id
{
	this->LocationId = LocationId;
}

void CityData::Setname(char * name)	//set city name
{
	strcpy(this->name, name);
}

void CityData::Setcountry(char * country)	//set country
{
	strcpy(this->country, country);
}
