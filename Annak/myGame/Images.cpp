#include "Images.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <random>


using namespace std;
using namespace cv;


Mat Images::mapImage;
vector<Vehicle> Images::vehicles;
bool Images::isRunning = true;
Mat img;
Mat tempImg;
bool drawing = false;
int ix = -1, iy = -1;

vector<vector<int>> Images::readMapFromFile(const string& filename)
{
    ifstream infile(filename);
    string line;
    getline(infile, line);
    if (line != "+World") {
        cerr << "Invalid file format: Missing +World" << endl;
        return {};
    }

    vector<vector<int>> matrix;
    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        vector<int> row;
        stringstream ss(line);
        int value;
        while (ss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    infile.close();

    if (matrix.empty()) {
        cerr << "Input file is empty or invalid format" << endl;
        return {};
    }
    return matrix;
}

map<int, Mat> Images::loadImages(const string& folderPath)
{
    std::map<int, cv::Mat> images;

    for (int i = 1; i <= 6; ++i) {
        std::string imagePath = folderPath + "\\tile" + std::to_string(i) + ".png";

        cv::Mat image = cv::imread(imagePath);
        if (!image.empty()) {
            images[i] = image.clone();
        }
        else {
            std::cerr << "Unable to load image: " << imagePath << std::endl;
        }
    }

    return images;
}

void Images::drawGrid(Mat& image, int cellSize, int gridDivisions)
{
    int rows = image.rows / cellSize;
    int cols = image.cols / cellSize;

    for (int i = 0; i <= rows; ++i) {
        cv::line(image, cv::Point(0, i * cellSize), cv::Point(image.cols, i * cellSize), cv::Scalar(200, 200, 200), 2);
    }
    for (int j = 0; j <= cols; ++j) {
        cv::line(image, cv::Point(j * cellSize, 0), cv::Point(j * cellSize, image.rows), cv::Scalar(200, 200, 200), 2);
    }

    int expandedCellSize = cellSize * gridDivisions;
    int smallCellSize = cellSize / gridDivisions;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 1; k < gridDivisions; ++k) {
                cv::line(image, cv::Point(j * cellSize + k * smallCellSize, i * cellSize),
                    cv::Point(j * cellSize + k * smallCellSize, (i + 1) * cellSize), cv::Scalar(200, 200, 200), 1);
                cv::line(image, cv::Point(j * cellSize, i * cellSize + k * smallCellSize),
                    cv::Point((j + 1) * cellSize, i * cellSize + k * smallCellSize), cv::Scalar(200, 200, 200), 1);
            }
        }
    }
}

Mat Images::initializeMapImage(int mapHeight, int mapWidth, const map<int, Mat>& images) {
    return Mat(mapHeight * images.at(1).rows, mapWidth * images.at(1).cols, CV_8UC3, Scalar(255, 255, 255));
}

void Images::initialize(int mapHeight, int mapWidth, const map<int, Mat>& images) {
    mapImage = initializeMapImage(mapHeight, mapWidth, images);
}

void Images::CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN) {
        isRunning = !isRunning;
        drawing = true;
        ix = x;
        iy = y;
        tempImg = mapImage.clone();
    }
    else if (event == EVENT_LBUTTONUP) {
        drawing = false;
        img = tempImg.clone();
        imshow("World Map", img);
    }
    else if (event == EVENT_MOUSEMOVE && drawing) {
        img = tempImg.clone();
        rectangle(img, Point(ix, iy), Point(x, y), Scalar(255, 0, 0), 2);
        imshow("World Map", img);
    }
}

void Images::show(World* world)
{
    img = Mat::zeros(512, 700, CV_8UC3);
    namedWindow("World Map", WINDOW_AUTOSIZE);
    setMouseCallback("World Map", CallBackFunc, NULL);
    Mat copied;
    while (true) {
        if (isRunning) {
            moveEntities(world);
        }
        copied = mapImage.clone();
        
        for (auto& vehicle : vehicles) {
            build(vehicle.getType(), vehicle.getCurrentLoacstion().x, vehicle.getCurrentLoacstion().y, copied);
        }
        imshow("World Map", copied);
        if (waitKey(1) >= 0) break;
        this_thread::sleep_for(chrono::milliseconds(30));
    }

    imshow("World Map", copied);
    waitKey(0);
}

Point generateRandomTarget(int x, int y, int maxX, int maxY)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, maxX - 1);
    std::uniform_int_distribution<> disY(0, maxY - 1);
    int X = disX(gen);
    int Y = disY(gen);
    return Point(X, Y);
}

void Images::moveEntities(World* world)
{
    //for (auto& vehicle : vehicles) {
    //    if (vehicle.getCurrentLoacstion() == vehicle.getTarget()) {
    //        int maxX = mapImage.rows;
    //        int maxY = mapImage.cols;
    //        Point newTarget;
    //        do {
    //            newTarget = generateRandomTarget(vehicle.getCurrentLoacstion().x, vehicle.getCurrentLoacstion().y, maxX / 9.6, maxY / 9.6);
    //        } while (newTarget == vehicle.getCurrentLoacstion());
    //        vehicle.setTarget(newTarget);

    //        Point currentLocation = vehicle.getCurrentLoacstion();
    //        Point target = vehicle.getTarget();
    //        Point direction = target - currentLocation;
    //        double distance = norm(direction);
    //    }

    //    Point currentLocation = vehicle.getCurrentLoacstion();
    //    Point target = vehicle.getTarget();
    //    Point direction = target - currentLocation;
    //    double distance = norm(direction);

    //    if (distance > 1.0) {
    //    direction *= 1.0 / distance;
    //    Point newPosition = currentLocation + direction;

    //    int newX = newPosition.x;
    //    int newY = newPosition.y;
    //    int attempts = 0;
    //    const int maxAttempts = 10; // מספר מקסימלי של ניסיונות למצוא מקום פנוי
    //   /* if ((world.getGrid()[newX/9.6][newY/9.6].getEstate() != nullptr) || (world.getGrid()[newX/9.6][newY/9.6].getVehicle() != nullptr)) {
    //        return;
    //    }*/
    //    
    //        while (((world.getGrid()[newX][newY].getEstate() != nullptr) || (world.getGrid()[newX][newY].getVehicle() != nullptr)) && attempts < maxAttempts) {
    //            // חישוב כיוון חלופי רנדומלי
    //            double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
    //            Point alternativeDirection = Point(cos(angle), sin(angle));
    //            Point alternativePosition = currentLocation + alternativeDirection;

    //            newX = (alternativePosition.x / 9.6);
    //            newY = (alternativePosition.y / 9.6);

    //            attempts++;
    //        }

    //        // אם נמצא מקום פנוי לאחר הניסיונות, עדכון המיקום
    //        if (world.getGrid()[newX][newY].getEstate() == nullptr && world.getGrid()[newX][newY].getVehicle() == nullptr) {
    //            newPosition = Point(newX * 9.6, newY * 9.6);
    //        }
    //        else {
    //            // במקרה ולא נמצא מקום פנוי לאחר מספר הניסיונות, נשארים במקום הנוכחי
    //            newPosition = currentLocation;
    //        }
    //        newPosition.x = max(0, min(newPosition.x, mapImage.cols - 1));
    //        newPosition.y = max(0, min(newPosition.y, mapImage.rows - 1));
    //        
    //        vehicle.setCurrentLoacstion(newPosition);
    //        pair<int, int> p;
    //        p.first = newPosition.x;
    //        p.second = newPosition.y;
    //        vehicle.setLocation(p);
    //    
    //    }
    //}


    for (auto& vehicle : vehicles) {
        if (vehicle.getCurrentLoacstion() == vehicle.getTarget()) {
            int maxX = mapImage.rows;
            int maxY = mapImage.cols;
            Point newTarget;
            do {
                newTarget = generateRandomTarget(vehicle.getCurrentLoacstion().x, vehicle.getCurrentLoacstion().y, maxX / 9.6, maxY / 9.6);
            } while (newTarget == vehicle.getCurrentLoacstion());
            vehicle.setTarget(newTarget);
        }
        Point currentLocation = vehicle.getCurrentLoacstion();
        world->destroy(vehicle.getType(), vehicle.getLocation().first, vehicle.getLocation().second);
        Point target = vehicle.getTarget();
        Point direction = target - currentLocation;
        double distance = norm(direction);
        //if (distance > 1.0) {

        direction *= 1.0 / distance;
        double moveStep = 1.0;

        Point newPosition = currentLocation + direction * moveStep;

        //Point newPosition = currentLocation + direction;
        // 
        // Make sure the new position is within the canvas bounds
        newPosition.x = std::max(0, std::min(newPosition.x, mapImage.cols - 1));
        newPosition.y = std::max(0, std::min(newPosition.y, mapImage.rows - 1));
        vehicle.setCurrentLoacstion(newPosition);
        pair<int, int> p;
        p.first = newPosition.x/9.6;
        p.second = newPosition.y / 9.6;
        vehicle.setLocation(p);
        world->manufacture(vehicle.getType(), p.first, p.second);

        //}
    }
}

void Images::drawWorld(World* worldMap)
{
    //vector<vector<int>> worldMap = readMapFromFile("input.txt");

    map<int, Mat> images = loadImages("C:\\האחסון שלי\\תכנות\\תשפד\\mobileye embedded\\Annak\\images\\TILES\\TILES");

    int mapWidth = worldMap->getTiles()[0].size();
    int mapHeight = worldMap->getTiles().size();
    initialize(mapHeight, mapWidth, images);
    int cellSize = images[1].rows;
    int gridDivisions = 5;
    //int gridDivisions = ReadJson::getSizes()["Tile"][1];

    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            int tileType = worldMap->getTiles()[i][j].getType();
            Mat tile = images[tileType];
            Rect roi(j * tile.cols, i * tile.rows, tile.cols, tile.rows);
            tile.copyTo(mapImage(roi));
        }
    }

    drawGrid(mapImage, cellSize, gridDivisions);

    
}

void Images::build(string name, int x, int y, Mat& mapWorld)
{
    string imagePath = "C:\\האחסון שלי\\תכנות\\תשפד\\mobileye embedded\\Annak\\images\\Build\\" + name + ".png";

    Mat estate = imread(imagePath, IMREAD_COLOR);

    if (estate.empty()) {
        cerr << "Error: Could not load image " << imagePath << endl;
        return;
    }

    double width = ReadJson::getSizes()[name][0]*9.6;
    double height = ReadJson::getSizes()[name][1]*9.6;


    Mat resizedTile;
    resize(estate, resizedTile, Size(width, height));



    Rect roi(x * 9.6, y * 9.6, width, height);

    if (roi.x + roi.width > mapWorld.cols || roi.y + roi.height > mapWorld.rows) {
        cerr << "Error: ROI exceeds the bounds of mapImage" << endl;
        return;
    }

    resizedTile.copyTo(mapWorld(roi));

}



