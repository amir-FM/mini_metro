#pragma once

#include <iostream>
#include <cmath>
#include "components/transform.h"
#include "utils/math_utils.h"

enum RailType {LAND, BRIDGE, TUNNEL};
enum RailOrientation {VERTICAL, HORIZONTAL};

class Rail {
public:

    Rail *next;
    glm::vec3 start, end;
    std::pair<int, int> end_pair;
    RailType type;
    glm::mat4 modelMatrix;
    glm::mat4 translateMatrix;
    glm::mat4 bridgeMatrix1;
    glm::mat4 bridgeMatrix2;
    glm::mat4 tunnelMatrix;
    bool working;
    RailOrientation orientation;
    float railWidth;
    float railHeight;
    float rotation;

    Rail () = default;
    Rail (glm::vec3 start, glm::vec3 end) : Rail(start, end, LAND) {}
    Rail (glm::vec3 start, glm::vec3 end, RailType type) : start(start), end(end), type(type), next(nullptr), working(false), railWidth(0.2f), railHeight(0.2f) {makeMatrix();}
    Rail (glm::vec3 start, glm::vec3 end, Rail* next) : Rail(start, end, LAND) {this->next = next;}

    glm::vec3 getStart();
    glm::vec3 getEnd();
    void setNext(Rail *next);
    Rail* getNext();
    void makeMatrix();
    bool checkAndChange(glm::vec3 mouse);
};
