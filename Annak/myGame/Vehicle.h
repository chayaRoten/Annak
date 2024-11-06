#pragma once
#include <string>
#include <map>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class Vehicle
{
private:
	string type;
	map< string, int> resources;
	vector<int> capacities;
	double speed;
	pair<int,int> location;
    Point target;
    Point currentLoacstion;
public:
	Vehicle(string, int ,int);
	string getType() { return type; }
	void setType(string Type);
	map< string, int>& getResources() { return resources; }
	void takeResources(map< string, int>& resources);
	void addResource(string type, int amount);
	double getSpeed() { return speed; }
	void setSpeed(double s) { speed=s; }
	pair<int, int> getLocation() { return location; }
	void setLocation(pair<int, int> p) { location = p; }
	void resourceMany(vector<string> args);
    Point getTarget() { return target; }
    Point getCurrentLoacstion() { return currentLoacstion; }
    void setTarget(Point t) {  target=t; }
    void setCurrentLoacstion(Point s) { currentLoacstion=s; }
};

