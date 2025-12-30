#pragma once

#include <iostream>
#include <cmath>
#include "components/transform.h"
#include "utils/math_utils.h"

enum RailType {LAND, BRIDGE, TUNNEL};

class Rail {
public:

    Rail *next;
    glm::vec3 start, end;
    RailType type;
    glm::mat4 modelMatrix;

    Rail () = default;
    Rail (glm::vec3 start, glm::vec3 end) : Rail(start, end, LAND) {}
    Rail (glm::vec3 start, glm::vec3 end, RailType type) : start(start), end(end), type(type), next(nullptr) {makeMatrix();}
    Rail (glm::vec3 start, glm::vec3 end, Rail* next) : Rail(start, end, LAND) {this->next = next;}

    glm::vec3 getStart();
    glm::vec3 getEnd();
    void setNext(Rail *next);
    Rail* getNext();
    void makeMatrix();
};
