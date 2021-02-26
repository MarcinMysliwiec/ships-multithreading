#ifndef SLEEPING_BARBER_PROBLEM_PORT_H
#define SLEEPING_BARBER_PROBLEM_PORT_H

#include <pthread.h>
#include <queue>
#include <map>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

class Port {
public:
    enum SHIP_STATE {
        INCOMING,
        DOCKED,
        LEAVING
    };

    Port(int nDocks);

    int randInt(int min, int max); // return a number between min and max

    void idleDock(int dockId);

    int dockShip(int shipId); // return dock's id for docked ship   | (-1) is leaving port

    void leaveDock(int shipId, int dockId);

    void farewellShip(int dockId);
private:
    int nDocks;

    struct Dock {
        int id;
        int myShipId = -1;       // no ships by default (-1)
        pthread_cond_t dockCond;
    };

    struct Ship {
        int id;
        int myDockId = -1;      // no dock by default (-1)
        SHIP_STATE state = INCOMING; // incoming state by default
        pthread_cond_t shipCond;
    };

    Dock *dock; // array of dock objects
    map<int, Ship> dockedShips;

    queue<int> sleepingDocks;

    pthread_mutex_t mutex1;

    Dock *getDock(int dockId);
};

#endif