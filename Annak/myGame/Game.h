#pragma once

#include "World.h"
#include "Input.h"

class Game {
public:
    void start(Input& myInput, World& myWorld);
    void steps(Input& myInput, World& myWorld);
    void asserts(Input& myInput, World& myWorld);
};

