#include "railroad.h"

void Railroad::addRail(Rail *rail) {
    pair<int, int> start = {rail->start.x, rail->start.z};
    railroad[start] = rail;
}

void Railroad::delRail(Rail *rail) {
    pair<int, int> start = {rail->start.x, rail->start.z};
    auto it = railroad.find(start);
    if(it == railroad.end()) {
        return;
    }
    railroad.erase(it);
    canRide = false;
}

bool Railroad::checkLoop() {
    if(railroad.size() == 0)
        return false;

    set<pair<int, int>> seen;

    pair<int, int> start = railroad.begin()->first;
    pair<int, int> cursor = start;
    pair<int, int> last;

    cout << "[checkLoop] start\n";

    while(true) {
        cout << "[checkLoop] " << cursor.first << "," << cursor.second << endl;
        seen.insert(cursor);
        last = cursor;
        cursor = {railroad[cursor]->end.x, railroad[cursor]->end.z};


        if(railroad.find(cursor) == railroad.end()) {
            canRide = false;
            return false;
        }

        railroad[last]->next = railroad[cursor];

        if(seen.find(cursor) != seen.end()) {
            canRide = true;
            return true;
        }
    }

    return false;

}

Rail* Railroad::getStart() {
    if(railroad.size() == 0)
        return nullptr;

    return railroad.begin()->second;
}

void Railroad::printRails() {
    for(auto& it : railroad) {
        cout << it.second->start.x << " " << it.second->start.z << endl;
    }
}

bool Railroad::railExists(glm::vec2 start) {
    pair<int, int> elem = {start.x, start.y};

    if(railroad.find(elem) != railroad.end()) {
        return true;
    }

    return false;

}
