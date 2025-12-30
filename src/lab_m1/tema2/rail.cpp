#include "rail.h"

glm::vec3 Rail::getStart() {
    return start;
}

glm::vec3 Rail::getEnd() {
    return end;
}

void Rail::setNext(Rail *next) {
    this->next = next;
}

Rail* Rail::getNext() {
    if(next == nullptr) {
    }

    return next;
}

//void Rail::makeMatrix() {
//    double xDist = (end.x - start.x) / 4;
//    double zDist = (end.z - start.z) / 4;
//
//    modelMatrix = glm::mat4(1);
//    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1 * start.x + xDist, 0, -1 * start.z + zDist));
//    modelMatrix = glm::rotate(modelMatrix, RADIANS(0.0f), glm::vec3(0, 1, 0));
//    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.2, 0.2));
//}

void Rail::makeMatrix() {
    modelMatrix = glm::mat4(1.0f);

    float railWidth = 0.2f;  // Thickness of the rail
    float railHeight = 0.3f; // Height of the rail

    float lengthX = end.x - start.x;
    float lengthZ = end.z - start.z;

    // 1. Find the midpoint of the track segment
    glm::vec3 midpoint = (start + end) * 0.5f;

    if (std::abs(lengthZ) > std::abs(lengthX)) {
        // --- ORIENTATION: PARALLEL TO Z-AXIS (Vertical) ---
        // Offset the midpoint horizontally (X) by the gauge
        modelMatrix = glm::translate(modelMatrix, midpoint);
        // Scale: X=Width, Y=Height, Z=Total Length
        modelMatrix = glm::scale(modelMatrix, glm::vec3(railWidth, railHeight, std::abs(lengthZ)));
    } 
    else {
        // --- ORIENTATION: PARALLEL TO X-AXIS (Horizontal) ---
        // Offset the midpoint vertically (Z) by the gauge
        modelMatrix = glm::translate(modelMatrix, midpoint);
        // Scale: X=Total Length, Y=Height, Z=Width
        modelMatrix = glm::scale(modelMatrix, glm::vec3(std::abs(lengthX), railHeight, railWidth));
    }
}
