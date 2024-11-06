#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Command.h"
#include "ReadJson.h"
#include "Tile.h"
#include "Coordination.h"

using namespace std;


class World
{
private:
    vector<vector<Coordination>>grid;
    vector<vector<Tile>>tiles;
    map<string, int> estates_count;
    map<string, int> vehicle_count;
    map<string, int> countAll;
    int points;
    int rainWool;
    int rainWood;

    static World* instance;

    World(const vector< vector<string> >& data);

public:
    static vector<int> resource;
    ReadJson readJSON;
    ~World() {}
    static World* getInstance(const vector< vector<string> >& data);
    void fill_grid(const vector< vector<string> >& data);
    void setGrid(vector<vector<Coordination>>data) { grid = data; };
    vector<vector<Coordination>>& getGrid() { return grid; };
    vector<vector<Tile>>& getTiles() { return tiles; };
    void printAllResource();
    int getRainWool() { return rainWool; }
    int getRainWooD() { return rainWood; }
    void setRainWool(int RainWool) { rainWool = RainWool; }
    void setRainWooD(int RainWood) { rainWood = RainWood; }
    void raining(int rain);
    void SelectedResource(int x , int y);
    void build(string type, int x, int y);
    map<string, int> getEstates() { return estates_count; }
    void printCountEstate(string assert, string type);
    bool canBuild(string type ,int x, int y);
    void manufacture(string type, int x, int y);
    map<string, int> getVehicleCount() { return vehicle_count; }
    void printCountVehicle(string assert, string type);
    void move(int xOld, int yOld, int xNew, int yNew);
    void setPoints(int p) { points = p; }
    int getPoints() { return points; }
    void destroy(string type, int x, int y);
};