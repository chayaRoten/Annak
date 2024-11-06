#include "World.h"
#include "algorithm"
using namespace std;

vector<int> World::resource = { 0,0,0,0 };

World::World(const vector<vector<string>>& data)
{
    points = 0;
    rainWool = 0;
    rainWood = 0;
	fill_grid(data);
}

void World::fill_grid(const vector<vector<string>>& data)
{
        vector<int> tilesSize = ReadJson::getSizes()["Tile"];
        for (size_t i = 0; i < data.size() ; i++)
        {
            tiles.push_back(vector<Tile>());
            for (size_t j = 0; j < data[i].size(); j++) {
                tiles[i].push_back(Tile(stoi(data[i ][j])));
            }
        }

        for (size_t i = 0; i < data.size() * tilesSize[1]; i++)
        {
            grid.push_back(vector<Coordination>());
            for (size_t j = 0; j < data[i / tilesSize[0]].size() * tilesSize[0]; j++) {
                grid[i].push_back(Coordination(& tiles[i / tilesSize[1]][j / tilesSize[0]]));
            }
        }
}

void World::printAllResource()
{
    for (size_t i = 0; i < tiles.size(); i++)
    {
        for (size_t j = 0; j < tiles[i].size(); j++) {
            cout << tiles[i][j].getType()<< ' ';
        }
    }
}

void World::raining(int rain)
{
    map<string, int> rains = readJSON.getRains();
    rainWood += rain;
    rainWool += rain;
    for (size_t i = 0; i < tiles.size(); i++)
    {
        for (size_t j = 0; j < tiles[i].size(); j++) {
            if (tiles[i][j].getResourceType() == "Wood") {
                if (rainWood >= rains["Wood"]) {
                    tiles[i][j].addResourceAmount(rainWood/ rains["Wood"]);
                }
            }
            else if (tiles[i][j].getResourceType() == "Wool") {
                if (rainWool >= rains["Wool"]) {
                    tiles[i][j].addResourceAmount(rainWool/ rains["Wool"]);
                }
            }
        } 
    }
    
    rainWood %= rains["Wood"];
    rainWool %= rains["Wool"];
}

void World::SelectedResource(int x, int y) {
    if (grid[x][y].getVehicle() != nullptr) {
        cout << "SelectedResource " << grid[x][y].getVehicle()->getResources()[ReadJson::getResources()[0]] << ' '
            << grid[x][y].getVehicle()->getResources()[ReadJson::getResources()[1]] << ' '
            << grid[x][y].getVehicle()->getResources()[ReadJson::getResources()[2]] << ' '
            << grid[x][y].getVehicle()->getResources()[ReadJson::getResources()[3]] << ' ';
    }
    else if (grid[x][y].getEstate() != nullptr) {
        cout << "SelectedResource " << grid[x][y].getEstate()->getResources()[ReadJson::getResources()[0]] << ' '
            << grid[x][y].getEstate()->getResources()[ReadJson::getResources()[1]] << ' '
            << grid[x][y].getEstate()->getResources()[ReadJson::getResources()[2]] << ' '
            << grid[x][y].getEstate()->getResources()[ReadJson::getResources()[3]] << ' ';
    }
    else {
        cout << "SelectedResource " << (grid[x][y].getTile()->getResourceType() == ReadJson::getResources()[0] ? grid[x][y].getTile()->getResourceAmount() : 0) << ' '
            << (grid[x][y].getTile()->getResourceType() == ReadJson::getResources()[1] ? grid[x][y].getTile()->getResourceAmount() : 0) << ' '
            << (grid[x][y].getTile()->getResourceType() == ReadJson::getResources()[2] ? grid[x][y].getTile()->getResourceAmount() : 0) << ' '
            << (grid[x][y].getTile()->getResourceType() == ReadJson::getResources()[3] ? grid[x][y].getTile()->getResourceAmount() : 0);
    }

}

void World::build(string type, int x, int y)
{
    estates_count[type]++;
    Estate* estate = new Estate(type);
    for (size_t i = x; i < x + ReadJson::getSizes()[type][0]; i++)
    {
        for (int j = y; j <y+ ReadJson::getSizes()[type][1]; j++)
        {
            grid[i][j].setEstate(estate);
        }
    }
    if (type == "Village") {
        points = min(points+1, 100);
    }
    else if (type == "City")
        points = min(points + 2, 100);
}

void World::printCountEstate(string assert, string type)
{
    cout << assert<< " " << estates_count[type] << endl;
}

void World::printCountVehicle(string assert, string type)
{
    cout << assert << " " << vehicle_count[type] << endl;
}

void World::move(int xOld, int yOld, int xNew, int yNew)
{
    if (grid[xNew][yNew].getTile()->getTypeTile() != "Water") {
        Vehicle* vehicle = grid[xOld][yOld].getVehicle();
        for (size_t i = 0; i < ReadJson::getSizes()[vehicle->getType()][0]; i++) {
            for (size_t j = 0; j < ReadJson::getSizes()[vehicle->getType()][1]; j++) {
                grid[xNew + i][yNew + j].setVehicle(vehicle);
                grid[vehicle->getLocation().first + i][vehicle->getLocation().second + j].setVehicle(nullptr);
            }
        }
        vehicle->setLocation({ xNew,yNew });
    }
}

void World::destroy(string type, int x, int y)
{
    vehicle_count[type]--;
    for (int i = x; i < x + ReadJson::getSizes()[type][0] && i < grid.size(); i++)
        for (int j = y; j < y + ReadJson::getSizes()[type][1] && j < grid[0].size(); j++)
            grid[i][j].setVehicle(nullptr);
}

bool World::canBuild(string type, int x, int y)
{
    if (type == "Road") {
        for (size_t i = x; i < ReadJson::getSizes()[type][0] + x; i++)
        {
            if (y > 0 && grid[i][y - 1].getEstate() != nullptr && grid[i][y - 1].getEstate()!= nullptr ||
                (y + ReadJson::getSizes()[type][1] < grid.size() && grid[i][y + ReadJson::getSizes()[type][1] + 1].getEstate() != nullptr && grid[i][y + ReadJson::getSizes()[type][1] + 1].getEstate()!= nullptr))
                return true;
        }
        for (size_t i = y; i < ReadJson::getSizes()[type][1] + y; i++)
        {
            if (x > 0 && grid[x - 1][i].getEstate() != nullptr && grid[x][i].getEstate()->getType() == "Road" ||
                x + ReadJson::getSizes()[type][0] < grid.size() && grid[x + ReadJson::getSizes()[type][0] + 1][i].getEstate() != nullptr && grid[x + ReadJson::getSizes()[type][0] + 1][i].getEstate()->getType() == "Road")
                return true;
        }
    }
    else {
        for (size_t i = x; i < ReadJson::getSizes()[type][0] + x; i++)
        {
            if (y > 0 && grid[i][y - 1].getEstate() != nullptr && grid[i][y - 1].getEstate()->getType() == "Road" ||
                (y + ReadJson::getSizes()[type][1] < grid.size() && grid[i][y + ReadJson::getSizes()[type][1] + 1].getEstate() != nullptr && grid[i][y + ReadJson::getSizes()[type][1] + 1].getEstate()->getType() == "Road"))
                return true;
        }
        for (size_t i = y; i < ReadJson::getSizes()[type][1] + y; i++)
        {
            if (x > 0 && grid[x - 1][i].getEstate() != nullptr && grid[x][i].getEstate()->getType() == "Road" || 
                x + ReadJson::getSizes()[type][0] < grid.size() && grid[x + ReadJson::getSizes()[type][0] + 1][i].getEstate() != nullptr && grid[x + ReadJson::getSizes()[type][0] + 1][i].getEstate()->getType() == "Road")
                return true;
        }
    }
    return false;
}

void World::manufacture(string type, int x, int y)
{
    vehicle_count[type]++;
    Vehicle* vehicle = new Vehicle(type, x,y);
    for (size_t i = x; i < x + ReadJson::getSizes()[type][0]; i++)
    {
        for (int j = y; j < y + ReadJson::getSizes()[type][1]; j++)
        {
            grid[i][j].setVehicle(vehicle);
        }
    }
}

