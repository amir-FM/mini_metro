#include "station.h"

Station::Station () : cap(10), dim(0) {
    srand(time(nullptr));

    position.first = glm::round((rand() % 13 - 6) / 2) * 2;
    position.second = glm::round((rand() % 13 - 6) / 2) * 2;
    globalPos = glm::vec3(position.first, 0, position.second);

    switch(rand() % 3) {
    case 0:
        type = SPHERE;
        type_s = "sphere";
        break;
    case 1:
        type = CUBE;
        type_s = "cube";
        break;
    case 2:
        type = PYRAMID;
        type_s = "pyramid";
        break;
    }
}

void Station::generatePassenger() {
    int no = rand();
    if(no % 10000 < 20) {
        switch(no % 3) {
        case 0:
            if(type == SPHERE) break;
            passengers.push_back(new Passenger(SPHERE, "sphere"));
            break;
        case 1:
            if(type == CUBE) break;
            passengers.push_back(new Passenger(CUBE, "cube"));
            break;
        case 2:
            if(type == PYRAMID) break;
            passengers.push_back(new Passenger(PYRAMID, "pyramid"));
            break;
        }

        dim++;
    }
}

void Station::unload(Train *tr) {
    int to_empty;
    switch(type) {
    case SPHERE:
        to_empty = tr->circle;
        tr->circle = 0;
        break;
    case CUBE:
        to_empty = tr->square;
        tr->square = 0;
        break;
    case PYRAMID:
        to_empty = tr->triangle;
        tr->triangle = 0;
        break;
    }

    tr->dim -= to_empty;
}

void Station::load(Train *tr) {
    while(tr->dim < tr->cap && passengers.size() != 0) {
        switch(passengers.back()->destination) {
        case SPHERE:
            tr->circle++;
            break;
        case CUBE:
            tr->square++;
            break;
        case PYRAMID:
            tr->triangle++;
            break;
        }

        passengers.pop_back();

        tr->dim++;
        dim = passengers.size();
        cout << "[load] " << dim << endl;
    }
}
