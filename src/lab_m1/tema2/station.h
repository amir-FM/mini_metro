#pragma once

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdlib>
#include "components/transform.h"
#include "utils/math_utils.h"
#include "train.h"

using namespace std;

enum StationType {SPHERE, CUBE, PYRAMID};

class Passenger {
public:
    Passenger(StationType dest, string dest_s) : destination(dest), dest_s(dest_s) {}

    StationType destination;
    string dest_s;
};

class Station {
public:

    vector<Passenger*> passengers;
    StationType type;
    string type_s;
    pair<int, int> position;
    glm::vec3 globalPos;
    int dim;
    int cap;

    Station ();

    void load(Train *tr);
    void unload(Train *tr);
    void generatePassenger();

};
