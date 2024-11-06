#include "ReadJson.h"
#include "algorithm"

json ReadJson::config = NULL;

ReadJson::ReadJson()
{
		ifstream f("configuration.json");

		if (!f) {
			cerr << "Failed to open configuration.json" << endl;
		}
		try {
			f >> config;
		}
		catch (const json::parse_error& e) {
			cerr << "Error parsing JSON: " << e.what() << endl;
		}
}

 unordered_map<int, string> ReadJson::getTiles()
{
	{
		unordered_map<int, string> tiles;
		if (config.contains("Tiles")) {
			for (const auto& item : config["Tiles"].items()) {
				tiles[item.value().get<int>()] = item.key();
			}
		}
		return tiles;
	}
}

 string ReadJson::getTypeTile(int type)
 {
	 unordered_map<int, string> tiles;
	 if (config.contains("Tiles")) {
		 for (const auto& item : config["Tiles"].items()) {
			 tiles[item.value().get<int>()] = item.key();
			 if (type == item.value().get<int>())
				 return item.key();
		 }
	 }
	 return "";
 }

 unordered_map<string, vector<int>> ReadJson::getSizes()
{
	int* tilesSize = new int[2];
	unordered_map<string, vector<int>> sizes;
	if (config.contains("Sizes")) {
		for (const auto& item : config["Sizes"].items()) {
			sizes[item.key()].push_back(item.value()[0].get<int>());
			sizes[item.key()].push_back(item.value()[1].get<int>());
		}
	}
	return sizes;
}

 map<string, int> ReadJson::getRains()
{
	map<string, int> rains;
	if (config.contains("Rains")) {
		for (const auto& item : config["Rains"].items()) {
			rains[item.key()]=item.value().get<int>();
		}
	}
	return rains;
}

 vector<string> ReadJson::getResources()
{
	{
		vector<string> resources;
		if (config.contains("ResourceTypes")) {
			for (const auto& item : config["ResourceTypes"].items()) {
				resources.push_back(item.value().get<string>());
			}
		}
		return resources;
	}
}

 unordered_map<string, int> ReadJson::StartingResources()
 {
	 unordered_map<string, int> startingResources;
	 if (config.contains("StartingResources")) {
		 for (const auto& item : config["StartingResources"].items()) {
			 startingResources[item.key()] = item.value().get<int>();
		 }
	 }
	 return startingResources;
 }

 unordered_map<string, vector<int>> ReadJson::getCapacities()
 {
	 static unordered_map<string, vector<int>> capacities;
	 if (config.contains("Capacities")) {
		 for (const auto item : config["Capacities"].items()) {
			 capacities[item.key()] = item.value().get<vector<int>>();
		 }
	 }
	 return capacities;
 }

 int ReadJson::getIndexResource(string resourceType)
 {
	 map<string, int> res;
		 int i = 0;
	 if (config.contains("ResourceTypes")) {
		 for (const auto& item : config["ResourceTypes"].items()) {
			 res[item.key()] = i++;
		 }
	 }
	 return res[resourceType];
 }

 string ReadJson::getTypeResource(int index)
 {
	 map<string, int> res;
	 int i = 0;
	 if (config.contains("ResourceTypes")) {
		 for (const auto& item : config["ResourceTypes"].items()) {
			 if (i == index)
				 return item.value();
			 res[item.key()] = i++;
		 }
	 }
	 return 0;
 }

 unordered_map<string, vector<int>> ReadJson::getCosts()
 {
	 unordered_map<string, vector<int>> costs;
	 if (config.contains("Costs")) {
		 for (const auto& item : config["Costs"].items()) {
			 for (size_t i = 0; i < getResources().size(); i++)
			 {
				 costs[item.key()].push_back(item.value()[i].get<int>());
			 }
		 }
	 }
	 return costs;
 }
