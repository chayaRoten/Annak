#include "Estate.h"

#include <string>
using namespace std;

Estate::Estate(string Type)
{
	type = Type;
	isComplate = false;
}

string Estate::getType()
{
	return type;
}

void Estate::setType(string Type)
{
	type = Type;
}

void Estate::setIsComplate(int wait)
{
	if (wait == ReadJson::getSizes()[type][0] * ReadJson::getSizes()[type][1])
		isComplate == true;
}

void Estate::makeEmpty()
{
	for (auto res : resources) {
		res.second = 0;
	}
}

void Estate::addResource(string resourceType, int amount)
{
	resources[resourceType] += amount;
	int index=ReadJson::getIndexResource(resourceType);
	if (resources[resourceType] >= ReadJson::getCapacities()[type][index])
		resources[resourceType] = ReadJson::getCapacities()[type][index];
}

bool Estate::canManufacture(string type)
{
	vector<int> costArr = ReadJson::getCosts()[type];
	for (int i = 0; i < costArr.size(); i++)
	{
		string f = ReadJson::getTypeResource(i);
		if ( resources[f] < costArr[i])
			return false;
	}
	return true;
}

void Estate::resourceMany(vector<string> args)
{
	for (int i = 0; i < ReadJson::getResources().size(); i++)
		this->resources[ReadJson::getResources()[i]] = stoi(args[i]);
}

void Estate::pay(string type)
{
	vector<int>costs = ReadJson::config["Costs"][type];
	for (int i = 0; i < ReadJson::getResources().size(); i++)
		this->resources[ReadJson::getResources()[i]] -= costs[i];
}

void Estate::deposit(map<string, int>& vehicleResources)
{
	for (auto& res : vehicleResources) {
		int index = ReadJson::getIndexResource(res.first);
		if (res.second > 0)
		{
			auto f = ReadJson::getCapacities()[type][index];
			if (resources[res.first] >= ReadJson::getCapacities()[type][index])
				return;
			if (resources[res.first] + res.second >= ReadJson::getCapacities()[type][index]) {
				resources[res.first] = ReadJson::getCapacities()[type][index];
				res.second -= ReadJson::getCapacities()[type][index];
			}
			else {
				resources[res.first] += res.second;
				res.second -= res.second;
			}
		}
	}
}
