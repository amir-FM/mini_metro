#include "carriage.h"

Carriage::Carriage (Rail *rail, float speed) : rail(rail), progress(0), speed(speed), noMove(false), stationDone(false) {
    start = position = rail->getStart();
    end = rail->getEnd();
}

glm::vec3 Carriage::getPosition() {
        return position;
}

void Carriage::makeProgress(double delta) {
    if(noMove) return;

    progress += delta * speed;

    if(progress >= 1) {
        progress = 1;
        initNewRail();
    }

    calculateNextPosition();
}


void Carriage::calculateNextPosition() {

    position.x = lerp(start.x, end.x, progress);
    position.y = lerp(start.y, end.y, progress);
    position.z = lerp(start.z, end.z, progress);
}

void Carriage::initNewRail() {

    try { 
        if(rail->getNext() == nullptr) return;

        rail = rail->getNext();
        progress = 0;
        start = position = rail->getStart();
        end = rail->getEnd();
    } catch(...) {
        return;
    }
}

void Carriage::changeRail(Rail *rail, float progress) {
    this->rail = rail;
    this->progress = progress;
    start = position = rail->getStart();
    end = rail->getEnd();
}
