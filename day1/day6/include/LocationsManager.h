#ifndef LOCATIONSMANAGER_H_INCLUDED
#define LOCATIONSMANAGER_H_INCLUDED
#include <algorithm>

#include "Location.h"


class LocationsManager {
public:
    LocationsManager(){};
    void addLocation(x, y) {
        mainLocations.emplace_back(make_unique(id++, {x, y}));
    }
    void eraseLocation(Location& loc) {
        getSpecificLocation()
        auto it = find(begin(mainLocations), end(mainLocations), loc);
        mainLocations.erase(it);
    }
private:
    list<unique_ptr<Location>> mainLocations;
    unsigned gridWidth;
    unsigned gridHeight;
};


#endif // LOCATIONSMANAGER_H_INCLUDED
