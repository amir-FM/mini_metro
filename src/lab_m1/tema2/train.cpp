#include "train.h"

Train::Train (Rail *rail, float speed) : rail(rail), progress(0), speed(speed), noMove(false), stationDone(false), stationWait(false) {
    start = position = rail->getStart();
    end = rail->getEnd();
    square = circle = triangle = 0;
    dim = 0;
    cap = 6;
    timer = 0;
}

glm::vec3 Train::getPosition() {
        return position;
}

void Train::makeProgress(double delta) {
    if(stationWait) {
        timer += 0.08f;
        if(timer > 1) {
            timer = 0;
            stationWait = false;
        } else return;
    }

    if(noMove) return;

    progressCarriages(delta);

    progress += delta * speed;

    if(progress >= 1) {
        progress = 1;
        if(!stationDone) {
            stopTrain();
            return;
        }
        stationDone = false;
        startTrain();
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

void Train::addCarriage() {
    cap += 3;

    carriages.push_back(new Carriage(rail, speed));
    initCarriagePositions();
}

void Train::delCarriage() {
    cap -= 3;

    carriages.pop_back();
}

void Train::initCarriagePositions() {
    float offset = 0.23f;
    float carriageOffset = 0.25f;
    float start = progress - offset;

    for(auto& it : carriages) {
        it->changeRail(rail, start);
        start -= carriageOffset;
    }
}

void Train::progressCarriages(double delta) {
    for(auto& it : carriages) {
        it->makeProgress(delta);
    }
}

void Train::stopTrain() {
    for(auto& it : carriages) {
        it->noMove = true;
    }
}

void Train::startTrain() {
    for(auto& it : carriages) {
        it->noMove = false;
    }
}
