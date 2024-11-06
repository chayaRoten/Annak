#include "Tile.h"
#include "ReadJson.h"
#include "World.h"

Tile::Tile(int Type)
{
	resourceAmount = 0;
	type = Type;
	typeTile = ReadJson::getTypeTile(Type);
	unordered_map<string, int> startingResources = ReadJson::StartingResources();
	vector<string> resources = ReadJson::getResources();
	if (Type >= 3) {
		resourceType = resources[Type - 3];
		resourceAmount = startingResources[resourceType];
	}
	else
		resourceType = "";
	
}

Tile::~Tile(){}

void Tile::setResourceAmount(int ResourceAmount)
{
	resourceAmount = ResourceAmount;
}

void Tile::addResourceAmount(int ResourceAmount)
{
	resourceAmount += ResourceAmount;
}

void Tile::lesResourceAmount(int ResourceAmount)
{
	resourceAmount -= ResourceAmount;
	if (resourceAmount < 0)
		resourceAmount = 0;
}
