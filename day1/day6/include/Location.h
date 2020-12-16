#ifndef LOCATION_H
#define LOCATION_H

#include <memory>
#include <list>

struct Coord {
    unsigned x;
    unsigned y;
};

class Location {
public:
    Location() = delete;
    Location(unsigned id, Coord coords) mlocationId(id), mCoordinates(coords) {}
    void addSideLocation()

private:
    unsigned mlocationId;
    Coord mCoordinates;
    list<unique_ptr<Location>> mClosestLocationsPtr;
};

#endif // LOCATION_H
