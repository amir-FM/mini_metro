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

void Rail::makeMatrix() {
    modelMatrix = glm::mat4(1.0f);

    float lengthX = end.x - start.x;
    float lengthZ = end.z - start.z;

    glm::vec3 midpoint = (start + end) * 0.5f;

    if (std::abs(lengthZ) > std::abs(lengthX)) {
        orientation = VERTICAL;
        modelMatrix = glm::translate(modelMatrix, midpoint);

        if(lengthZ > 0)
            rotation = 270;
        else
            rotation = 90;

        if(type == BRIDGE) {
            bridgeMatrix1 = bridgeMatrix2 = modelMatrix;
            float height = railHeight / 4 - 0.1f;
            float width = railWidth / 4;
            float heightOffset = railHeight / 4 + 0.07f;
            float spacing = 0.05f;

            bridgeMatrix1 = glm::translate(bridgeMatrix1, glm::vec3(spacing, heightOffset, 0));
            bridgeMatrix1 = glm::scale(bridgeMatrix1, glm::vec3(width, height, std::abs(lengthZ)));

            bridgeMatrix2 = glm::translate(bridgeMatrix2, glm::vec3(-spacing, heightOffset, 0));
            bridgeMatrix2 = glm::scale(bridgeMatrix2, glm::vec3(width, height, std::abs(lengthZ)));
        } else if(type == TUNNEL) {
            float height = railHeight / 4 - 0.1f;
            float width = railWidth / 1.3;
            float heightOffset = railHeight / 4 + 0.07f;

            tunnelMatrix = modelMatrix;
            tunnelMatrix = glm::translate(tunnelMatrix, glm::vec3(0, heightOffset, 0));
            tunnelMatrix = glm::scale(tunnelMatrix, glm::vec3(width, height, std::abs(lengthZ)));
        }

        modelMatrix = glm::scale(modelMatrix, glm::vec3(railWidth, railHeight, std::abs(lengthZ)));
    } 
    else {
        orientation = HORIZONTAL;
        modelMatrix = glm::translate(modelMatrix, midpoint);

        if(lengthX > 0)
            rotation = 0;
        else
            rotation = 180;

        if(type == BRIDGE) {
            bridgeMatrix1 = bridgeMatrix2 = modelMatrix;
            float height = railHeight / 4 - 0.1f;
            float width = railWidth / 4;
            float heightOffset = railHeight / 4 + 0.07f;
            float spacing = 0.05f;

            bridgeMatrix1 = glm::translate(bridgeMatrix1, glm::vec3(0, heightOffset, spacing));
            bridgeMatrix1 = glm::scale(bridgeMatrix1, glm::vec3(std::abs(lengthX), height, width));

            bridgeMatrix2 = glm::translate(bridgeMatrix2, glm::vec3(0, heightOffset, -spacing));
            bridgeMatrix2 = glm::scale(bridgeMatrix2, glm::vec3(std::abs(lengthX), height, width));
        } else if(type == TUNNEL) {
            float height = railHeight / 4 - 0.1f;
            float width = railWidth / 1.3;
            float heightOffset = railHeight / 4 + 0.07f;

            tunnelMatrix = modelMatrix;
            tunnelMatrix = glm::translate(tunnelMatrix, glm::vec3(0, heightOffset, 0));
            tunnelMatrix = glm::scale(tunnelMatrix, glm::vec3(std::abs(lengthX), height, width));
        }

        modelMatrix = glm::scale(modelMatrix, glm::vec3(std::abs(lengthX), railHeight, railWidth));
    }
}

bool Rail::checkAndChange(glm::vec3 mouse) {
    if(orientation == HORIZONTAL &&
        ((mouse.x >= start.x && mouse.x <= end.x || mouse.x >= end.x && mouse.x <= start.x)) &&
        abs(mouse.z - start.z) <= railWidth) {
        working = !working;
        return true;
    }

    if(orientation == VERTICAL &&
        ((mouse.z >= start.z && mouse.z <= end.z || mouse.z >= end.z && mouse.z <= start.z)) &&
        abs(mouse.x - start.x) <= railWidth) {
        working = !working;
        return true;
    }

    return false;
}
