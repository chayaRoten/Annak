#include "Vehicle.h"
#include "ReadJson.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


Vehicle::Vehicle(string Type, int x, int y)
{
	type = Type;
	location = { x, y };
    setCurrentLoacstion(Point(x,y));
}

void Vehicle::setType(string Type)
{
	type = Type;
}

void Vehicle::takeResources(map<string, int>& estateResources)
{
	for (auto& res : estateResources) {
		int index = ReadJson::getIndexResource(res.first);
		if (res.second > 0)
		{
			auto f = ReadJson::getCapacities()[type][index];
			if (resources[res.first] >= ReadJson::getCapacities()[type][index])
				return;
			if (resources[res.first]+ res.second >=ReadJson::getCapacities()[type][index]) {
				resources[res.first] = ReadJson::getCapacities()[type][index];
				res.second -= ReadJson::getCapacities()[type][index];
			}
			else {
				resources[res.first] += res.second;
				res.second-=res.second;
			}
		}
	}
}

void Vehicle::addResource(string resourceType, int amount)
{
	resources[resourceType] += amount;
	int index = ReadJson::getIndexResource(resourceType);
	if (resources[resourceType] >= ReadJson::getCapacities()[type][index])
		resources[resourceType] = ReadJson::getCapacities()[type][index];
}

void Vehicle::resourceMany(vector<string> args)
{
	for (int i = 0; i < ReadJson::getResources().size(); i++)
		this->resources[ReadJson::getResources()[i]] = stoi(args[i]);
}
