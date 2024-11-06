#include "Game.h"
#include "World.h"
#include "Input.h"
#include "openCv.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "Images.h"

using namespace std;
using namespace cv;


int main()
{
    ifstream infile("input.txt");
    Input myInput(infile);
	unordered_map<int, string> tails = ReadJson::getTiles();
	myInput.parse_and_store();
    World* world = World::getInstance(myInput.world->data);

    Images::drawWorld(world);

    Game game;
    game.start(myInput, world);
    game.steps(myInput, world);

    Images::moveEntities(world);
    Images::show(world);

    game.asserts(myInput, world);


	//for (shared_ptr<Command> start : myInput.start) {
	//	if (start->name == Command::RESOURCE) {
	//		if (myWorld.getGrid()[stoi(start->arguments[3]) - 1][stoi(start->arguments[2]) - 1].getEstate() != nullptr)
	//			myWorld.getGrid()[stoi(start->arguments[3]) - 1][stoi(start->arguments[2]) - 1].getEstate()->addResource(start->arguments[1], stoi(start->arguments[0]));
	//		else if (myWorld.getGrid()[stoi(start->arguments[3]) - 1][stoi(start->arguments[2]) - 1].getVehicle() != nullptr)
	//			myWorld.getGrid()[stoi(start->arguments[3]) - 1][stoi(start->arguments[2]) - 1].getVehicle()->addResource(start->arguments[1], stoi(start->arguments[0]));
	//		myWorld.getGrid()[stoi(start->arguments[3]) - 1][stoi(start->arguments[2]) - 1].getTile()->setResourceAmount(stoi(start->arguments[0]));
	//	}
	//	if (start->name == Command::RESOURCES) {
	//		if (myWorld.getGrid()[stoi(start->arguments[5]) - 1][stoi(start->arguments[4]) - 1].getEstate() != NULL) {
	//			myWorld.getGrid()[stoi(start->arguments[5]) - 1][stoi(start->arguments[4]) - 1].getEstate()->resourceMany(start->arguments);
	//		}
	//		if (myWorld.getGrid()[stoi(start->arguments[5]) - 1][stoi(start->arguments[4]) - 1].getVehicle() != NULL) {
	//			myWorld.getGrid()[stoi(start->arguments[5]) - 1][stoi(start->arguments[4]) - 1].getVehicle()->resourceMany(start->arguments);
	//		}
	//	}
	//	if (start->name == Command::PEOPLE) {
	//		if (myWorld.getGrid()[stoi(start->arguments[2]) - 1][stoi(start->arguments[1]) - 1].getEstate() != nullptr) {
	//			myWorld.getGrid()[stoi(start->arguments[2]) - 1][stoi(start->arguments[1]) - 1].getEstate()->addResource(start->name, stoi(start->arguments[0]));
 //               Images::getVehicles().push_back(Vehicle(start->arguments[0], stoi(start->arguments[1]) - 1, stoi(start->arguments[2]) - 1));
 //           }
	//		else
	//			myWorld.manufacture(start->name, stoi(start->arguments[2]) - 1, stoi(start->arguments[1]) - 1);
 //           Images::build(start->arguments[0], stoi(start->arguments[1]) - 1, stoi(start->arguments[2]) - 1, Images::getMapImage());
	//	}
	//	if (start->name == Command::BUILD) {
	//		myWorld.build(start->arguments[0], stoi(start->arguments[2]) - 1, stoi(start->arguments[1]) - 1);
 //           Images::build(start->arguments[0], stoi(start->arguments[1]) - 1, stoi(start->arguments[2]) - 1, Images::getMapImage());
	//	}
	//	if (start->name == Command::MANUFACTURE) {
	//		myWorld.manufacture(start->arguments[0], stoi(start->arguments[2]) - 1, stoi(start->arguments[1]) - 1);
 //           //Images::build(start->arguments[0], stoi(start->arguments[1]) - 1, stoi(start->arguments[2]) - 1,Images::getMapImage());
 //           Images::setVehicles(Vehicle(start->arguments[0], stoi(start->arguments[1]) - 1, stoi(start->arguments[2]) - 1));
	//	}
	//	if(start->name == Command::MAKE_EMPTY) {
	//		myWorld.getGrid()[stoi(start->arguments[1]) - 1][stoi(start->arguments[0]) - 1].getEstate()->makeEmpty();
	//	}
	//	if (start->name == Command::SETPOINTS) {
	//		myWorld.setPoints(stoi(start->arguments[0]));
	//	}
	//}
    
	//while (wait < max_wait) {
	//	for (shared_ptr<Command> step : myInput.steps) {
	//		if (step->name == Command::SELECT) {
	//			select1 = stoi(step->arguments[0]);
	//			select2 = stoi(step->arguments[1]);
	//			if (myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle() != nullptr)
	//				selectedVehicle = myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle();
	//		}
	//		if (step->name == Command::WORK) {
	//			if (wait == 0) {
	//				if (myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle() != NULL && (myWorld.getGrid()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].getVehicle() == NULL)) {
	//					myWorld.move(select2 - 1, select1 - 1, stoi(step->arguments[1]) - 1, stoi(step->arguments[0]) - 1);
	//					myWorld.getGrid()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].getVehicle()->addResource(myWorld.getGrid()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].getTile()->getResourceType(), 1);
	//					myWorld.getGrid()[stoi(step->arguments.at(1)) - 1][stoi(step->arguments.at(0)) - 1].getTile()->lesResourceAmount(1);
	//				}
	//			}
	//		}
	//		if (step->name == Command::RAIN) {
	//			if(stoi(step->arguments[0])>0)
	//				myWorld.raining(1);
	//				step->arguments[0] = to_string(stoi(step->arguments[0]) + 1);
	//		}
	//		if (step->name == Command::WAIT) {
	//			if (wait == 0)
	//				max_wait = stoi(step->arguments[0]);
	//			wait++;
	//		}
	//		if (step->name == Command::BUILD) {
	//			if (wait == 0) 
	//				if (myWorld.canBuild(step->arguments[0], stoi(step->arguments[2]) - 1, stoi(step->arguments[1]) - 1))
	//					myWorld.build(step->arguments[0], stoi(step->arguments[2]) - 1, stoi(step->arguments[1]) - 1);
	//				if (myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].getEstate()!=nullptr)
	//					myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].getEstate()->setIsComplate(wait);
	//			
	//		}
	//		if (step->name == Command::PEOPLE) {
	//			//myWorld.manufacture(step->name, stoi(step->arguments[2]) - 1, stoi(step->arguments[1]) - 1);
	//			//myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].setPeople(true);
	//			if (myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].getEstate() != nullptr) {
	//				myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].getEstate()->addResource(step->name, stoi(step->arguments[0]));
	//			}
	//			else
	//				myWorld.manufacture(step->name, stoi(step->arguments[2]) - 1, stoi(step->arguments[1]) - 1);
	//		}
	//		if (step->name == Command::TAKE_RESOURCES) {
	//			if (wait == 0) {
	//				if (myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle() != nullptr)
	//					myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle()->takeResources(
	//						myWorld.getGrid()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].getEstate()->getResources());
	//			}
	//		}
	//		if (step->name == Command::MANUFACTURE) {
	//			if(myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].getEstate()!=NULL)
	//				if (myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].getEstate()->canManufacture(step->arguments[0])) {
	//					myWorld.manufacture(step->arguments[0], stoi(step->arguments[2]) - 1, stoi(step->arguments[1]) - 1);
	//					myWorld.getGrid()[stoi(step->arguments[2]) - 1][stoi(step->arguments[1]) - 1].getEstate()->pay(step->arguments[0]);
	//				}
	//		}
	//		if (step->name == Command::MOVE) {
	//			if (wait == 0) {
	//				if (myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle() != NULL &&
	//					((myWorld.getGrid()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].getVehicle() == NULL))
	//					|| (myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle()->getType() == "Helicopter"))
	//				myWorld.move(select2 - 1, select1 - 1, stoi(step->arguments[1]) - 1, stoi(step->arguments[0]) - 1);
	//			}
	//		}
	//		if (step->name == Command::DEPOSIT) {
	//			if (wait == 0) {
	//				if (myWorld.getGrid()[select2-1][select1-1].getVehicle() != nullptr)
	//					myWorld.getGrid()[stoi(step->arguments[1])][stoi(step->arguments[0])].getEstate()->deposit(
	//						myWorld.getGrid()[select2-1][select1-1].getVehicle()->getResources());
	//			}
	//		}
	//	}
	//	if (max_wait == INT_MAX)
	//		max_wait = 0;
	//}
	    
   /* for (string assert : myInput.asserts) {
		if (assert == "SelectedCategory") {
			string category;
			if(myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle()!=NULL)
				category = myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle()->getType();
			else
			{
				if (myWorld.getGrid()[select2 - 1][select1 - 1].getEstate() != NULL)
					category = myWorld.getGrid()[select2 - 1][select1 - 1].getEstate()->getType();
				else
					category = myWorld.getGrid()[select2 - 1][select1 - 1].getTile()->getTypeTile();
			}
			cout << "SelectedCategory " << category<< endl;
		}
		if (assert == "SelectedResource") {
			myWorld.SelectedResource(select2 - 1, select1 - 1);
		}
		if (assert == "CityCount") {
			myWorld.printCountEstate(assert, "City");
		}
		if (assert == "RoadCount") {
			myWorld.printCountEstate(assert, "Road");
		}
		if (assert == "VillageCount") {
			myWorld.printCountEstate(assert, "Village");
		}
		if (assert == "SelectedComplete") {
			myWorld.getGrid()[select2 - 1][select1 - 1].getEstate()->getIsComplate() ? (cout << "SelectedComplete True" << endl) : (cout << "SelectedComplete False" << endl);
		}
		if (assert == "SelectedPeople") {
			if (myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle())
				myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle()->getType() == Command::PEOPLE ? cout << "SelectedPeople 1 \n" : cout << "SelectedPeople 0\n";
			else if (myWorld.getGrid()[select2 - 1][select1 - 1].getEstate() != nullptr)
				cout << "SelectedPeople " << myWorld.getGrid()[select2 - 1][select1 - 1].getEstate()->getResources()["People"];
		}
		if (assert == "SelectedCar") {
			(myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle() != nullptr) && myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle()->getType() == "Car" ? cout << "SelectedCar 1" : cout << "SelectedCar 0";
		}
		if (assert == "SelectedTruck") {
			(myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle() != nullptr) && myWorld.getGrid()[select2 - 1][select1 - 1].getVehicle()->getType() == "Truck" ? cout << "SelectedTruck 1" : cout << "SelectedTruck 0";

		}
		if (assert == "CarCount") {
			myWorld.printCountVehicle(assert, "Car");
		}
		if (assert == "TruckCount") {
			myWorld.printCountVehicle(assert, "Truck");
		}
		if (assert == "HelicopterCount") {
			myWorld.printCountVehicle(assert, "Helicopter");
		}
		if (assert == "SelectedCoordinates") {
			selectedVehicle != nullptr ? cout << "SelectedCoordinates " << selectedVehicle->getLocation().second / 5 << " " << selectedVehicle->getLocation().first / 5 << " " : cout << "SelectedCoordinates 0 0";
		}
		if (assert == "Points") {
			cout << "Points " << myWorld.getPoints();
		}
	}*/

    return 0;


}












//במקום לשאול כל פעם האם זה... אלא לבדוק האם נגמר בcount 
//else if (hasEnding(assert, "Count"))
//myWorld.printCount(assert);

//bool hasEnding(std::string const& fullString, std::string const& ending) {
//	if (fullString.length() >= ending.length()) {
//		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
//	}
//	else {
//		return false;
//	}
//}


