#pragma once
#include "Images.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "World.h"

using namespace std;
using namespace cv;

class Images
{
private:
    static Mat mapImage;
    static vector<Vehicle> vehicles;
public:
    static bool isRunning;
    static Mat& getMapImage() { return mapImage; }
    static vector<vector<int>> readMapFromFile(const string& filename);
    static map<int, Mat> loadImages(const string& folderPath);
    static void drawGrid(Mat& image, int cellSize, int gridDivisions);
    static void drawWorld(World world);
    static void build(string name, int x, int y, Mat& mapWorld);
    static Mat initializeMapImage(int mapHeight, int mapWidth, const map<int, Mat>& images);
    static void initialize(int mapHeight, int mapWidth, const map<int, Mat>& images);
    static void show(World world);
    static void moveEntities(World world);
    static void setVehicles(Vehicle v) { vehicles.push_back(v); }
    static vector<Vehicle> getVehicles() { return vehicles; }
    static void CallBackFunc(int event, int x, int y, int flags, void* userdata);
};

