#pragma once

#include <iostream>
#include "utils/math_utils.h"
#include "components/transform.h"
#include "rail.h"

using namespace std;

class Train {
public:
    Rail *rail;
    float progress;
    float speed;
    glm::vec3 position, start, end;
    bool noMove;

    Train () = default;
    Train (Rail *rail, float speed);
    Train (Rail *rail) : Train(rail, 2.0f) {}

    glm::vec3 getPosition();
    void makeProgress(double delta);
    void calculateNextPosition();
    void initNewRail();
};
