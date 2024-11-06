#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Tile
{
private:
	int type;
	string resourceType;
	int resourceAmount;
	string typeTile;
public:
	Tile(int Type);
	~Tile();
	int getType() const { return this->type; }
	string getTypeTile() { return typeTile; }
	string getResourceType() { return this->resourceType; }
	void setResourceType(int rs) { this->resourceType=rs; }
	int getResourceAmount() { return this->resourceAmount; }
	void setResourceAmount(int ResourceAmount);
	void addResourceAmount(int ResourceAmount);
	void lesResourceAmount(int ResourceAmount);
};
