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
        //std::cerr << "next ptr not defined\n";
    }

    return next;
}
