#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
class ReadJson
{
public:
	static json config;
	ReadJson();
	static unordered_map<int, string> getTiles();
	static string getTypeTile(int);
	static unordered_map<string,vector<int>> getSizes();
	static map<string, int> getRains();
	static vector<string> getResources();
	static unordered_map<string, int> StartingResources();
	static unordered_map<string, vector<int>> getCapacities();
	static int getIndexResource(string);
	static string getTypeResource(int);
	static unordered_map<string, vector<int>> getCosts();
};
