#pragma once

#include <iostream>
#include "utils/math_utils.h"
#include "components/transform.h"
#include <vector>
#include "rail.h"

using namespace std;

class Carriage {
public:
    Rail *rail;
    float progress;
    float speed;
    glm::vec3 position, start, end;
    bool noMove;
    bool stationDone;

    Carriage () = default;
    Carriage (Rail *rail, float speed);
    Carriage (Rail *rail) : Carriage(rail, 2.0f) {}

    glm::vec3 getPosition();
    void makeProgress(double delta);
    void calculateNextPosition();
    void initNewRail();
    void changeRail(Rail *rail, float progress);
};
