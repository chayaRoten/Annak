# Strategic Board Game - Catan Inspired

## Overview

This project is a strategic board game inspired by the classic **Catan** game, developed in **C++** with an interactive **Graphical User Interface (GUI)** utilizing **OpenCV**. The game allows players to interact with a simulated world, gather resources, build estates, vehicles, and manage their growth.

Key features of the game include:
- Grid-based world with various types of tiles (e.g., resources, cities, roads)
- Vehicle management for resource collection and movement
- Construction and manufacturing of buildings
- Command-based gameplay where players input actions in the form of commands
- Automated game steps for simulation
- Assertions and checks for game state

## Features

- **World Simulation**: The game world is represented as a grid where each tile can contain various elements, such as estates (cities, roads), vehicles (trucks, cars, helicopters), and resource tiles.
- **Resource Management**: Players collect and deposit resources (e.g., wood, stone, etc.) in order to build and grow their world.
- **Vehicle Interaction**: Vehicles can be used to transport resources across the grid, and players can move them around the world to gather or deliver resources.
- **Building & Manufacturing**: The game allows for the construction of new buildings, such as cities and roads, and the manufacturing of goods.
- **Command System**: Players can define steps and actions through a command file. These commands include actions like moving, building, manufacturing, and waiting.
- **Interactive GUI**: OpenCV is used to render the world visually and show real-time updates on the game state.

## Design Patterns Used

3. **Command Pattern**: Commands (e.g., `MOVE`, `BUILD`, `SELECT`) are parsed from a file and executed as actions, promoting loose coupling between command input and game logic.
5. **Singleton Pattern**: Global instances like the game world or the image rendering class can be made singletons to ensure there is only one instance throughout the game's lifecycle.

## Requirements

- **C++** (C++11 or higher recommended)
- **OpenCV** (for GUI rendering)
- A C++ compiler (e.g., GCC, Clang, MSVC)
- A text editor or IDE for editing the code

### Optional Dependencies:
- **JSON Library**: For reading configuration files (such as tile information).
  
## How to Run

1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd <project_directory>
   ```

2. Compile the project using a C++ compiler. If you're using **g++**:
   ```bash
   g++ -std=c++11 -o game main.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
   ```

3. Run the game:
   ```bash
   ./game
   ```

4. The game will automatically load an input configuration file (`input.txt`) containing the commands for starting and running the game. You can modify this file to experiment with different scenarios.

## Game Rules

- **Start**: The game starts by reading the input file, which contains a list of commands to initialize the game world, build estates, and spawn vehicles.
- **Turns**: After starting, the game proceeds by processing steps from the input file. Each step can involve selecting tiles, building structures, moving vehicles, or gathering resources.
- **Waiting**: Some commands, such as `WAIT`, will pause the game for a given number of turns.
- **Resource Management**: Players must manage their resources efficiently to build new structures or vehicles and expand their influence on the grid.
  
## Commands

The game uses a command-based system to drive the gameplay. The available commands include:

- **SELECT x y**: Select a tile on the grid.
- **BUILD type x y**: Build a structure of the specified type (e.g., City, Road) at coordinates (x, y).
- **MOVE x y**: Move a vehicle from one tile to another.
- **MANUFACTURE type x y**: Manufacture a product at a given location.
- **WAIT turns**: Wait for a specific number of turns.
- **RAIN turns**: Simulate rain, which may affect resources.

Commands are read from a text file (e.g., `input.txt`) and executed step-by-step.

## Game World

The game world consists of a grid where each tile can contain:
- **Empty Space**
- **Estate**: Can be a city, village, or road.
- **Vehicle**: Can be a car, truck, or helicopter.
- **Resource Tile**: Contains resources like wood, stone, etc.

Each entity can interact with others, like vehicles collecting resources or buildings being constructed.

## Example Commands (`input.txt`)

```txt
START
SELECT 1 1
BUILD City 2 2
MANUFACTURE People 3 3
WAIT 2
MOVE 2 2 3 3
TAKE_RESOURCES
ASSERTS SelectedCategory
```

## Contributions

Contributions are welcome! Feel free to fork the repository, submit issues, and open pull requests.

## Contact

If you have any questions or suggestions, feel free to open an issue or contact the project maintainers.
