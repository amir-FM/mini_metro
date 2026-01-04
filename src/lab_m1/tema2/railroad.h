#pragma once

#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include "components/transform.h"
#include "utils/math_utils.h"
#include "rail.h"

using namespace std;

class Railroad {
public:

    map<pair<int, int>, Rail*> railroad;
    bool canRide;

    void addRail(Rail *rail);
    void delRail(Rail *rail);
    bool checkLoop();
    Rail* getStart();
    void printRails();
    bool railExists(glm::vec2 start);

};
