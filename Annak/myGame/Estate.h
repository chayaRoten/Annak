#pragma once
#include <string>
#include "ReadJson.h"
using namespace std;

class Estate
{
private:
	string type;
	bool isComplate=false;
	map< string, int> resources;
public:
	Estate(string);
	string getType();
	void setType(string Type);
	bool getIsComplate() { return isComplate; }
	void setIsComplate(int wait);
	void makeEmpty();
	void addResource(string type, int amount);
	map< string, int>& getResources() { return resources; }
	void setResources(map< string, int> res) { resources = res; }
	bool canManufacture(string type);
	void resourceMany(vector<string> args);
	void pay(string type);
	void deposit(map< string, int>&);
};

