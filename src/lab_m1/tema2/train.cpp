#include "train.h"

Train::Train (Rail *rail, float speed) : rail(rail), progress(0), speed(speed) {
    start = position = rail->getStart();
    end = rail->getEnd();
}

glm::vec3 Train::getPosition() {
        return position;
}

void Train::makeProgress(double delta) {
    progress += delta * speed;

    if(progress >= 1) {
        progress = 1;
        initNewRail();
    }

    calculateNextPosition();
}


void Train::calculateNextPosition() {
    position.x = lerp(start.x, end.x, progress);
    position.y = lerp(start.y, end.y, progress);
    position.z = lerp(start.z, end.z, progress);
}

void Train::initNewRail() {
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
