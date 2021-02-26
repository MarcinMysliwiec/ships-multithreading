//
// Created by psiw on 11.02.2021.
//

#include "Port.h"

Port::Port(int nDocks, int nTugs) // initialize a Port object with parameters
{
    this->nDocks = nDocks;
    this->nTugs = nTugs;

    pthread_mutex_init(&mutex1, NULL);

    dock = new Dock[nDocks];
    for (int i = 0; i < nDocks; i++) {
        dock[i].id = i;
        pthread_cond_init(&dock[i].dockCond, NULL);
    }
}

int Port::randInt(int min, int max) {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

void Port::idleDock(int dockId) {
    pthread_mutex_lock(&mutex1);

    if (getDock(dockId)->myShipId == -1) { // id statku | jezeli -1 to w doku nie ma statku
        printf("Dock %i is waiting for ship.\n", dockId);
        sleepingDocks.push(dockId);
        while (getDock(dockId)->myShipId == -1) {
            pthread_cond_wait(&(getDock(dockId)->dockCond), &mutex1);
        }
    }

    while (dockedShips[getDock(dockId)->myShipId].state != DOCKED) //synchronization with customer thread
    {
        pthread_cond_wait(&(getDock(dockId)->dockCond), &mutex1);
    }

    printf("Dock %i has Welcomed ship %i.\n", dockId, getDock(dockId)->myShipId);

    pthread_mutex_unlock(&mutex1);
}


int Port::dockShip(int shipId, int neededTugs) // return a non-negative number only when a customer got a service
{
    pthread_mutex_lock(&mutex1);

    if (sleepingDocks.empty()) {
        printf("Ship %i leaving port, because of no available docks.\n", shipId);
        pthread_mutex_unlock(&mutex1);
        return -1;
    }
    if (neededTugs > nTugs) {
        printf("Ship %i leaving port, because of no tugs available.\n", shipId);
        pthread_mutex_unlock(&mutex1);
        return -1;
    }

    nTugs -= neededTugs;

    dockedShips[shipId] = Ship();
    dockedShips[shipId].id = shipId;
    dockedShips[shipId].neededTugs = neededTugs;

    pthread_cond_init(&dockedShips[shipId].shipCond, NULL);
    int dockId;

    dockId = sleepingDocks.front();
    sleepingDocks.pop();
    dockedShips[shipId].myDockId = dockId;
    getDock(dockId)->myShipId = shipId;

    printf("Ship %i moves to a dock %i with help of %i tugs\n", shipId, dockId, neededTugs);
    dockedShips[shipId].state = DOCKED;
    pthread_cond_signal(&(getDock(dockId)->dockCond));
    pthread_mutex_unlock(&mutex1);
    return dockId;
}

void Port::leaveDock(int shipId, int dockId) {
    pthread_mutex_lock(&mutex1);
    printf("Ship %i is waiting to be allowed to go from %i\n", shipId, dockId);

    while (dockedShips[shipId].myDockId != -1) {
        pthread_cond_wait(&dockedShips[shipId].shipCond, &mutex1);
    }

    nTugs += dockedShips[shipId].neededTugs;
    dockedShips[shipId].state = LEAVING;

    printf("Ship %i is sailing away from %i!\n", shipId, dockId);

    pthread_cond_signal(&(getDock(dockId)->dockCond));

    pthread_mutex_unlock(&mutex1);
}

void Port::farewellShip(int dockId) {
    pthread_mutex_lock(&mutex1);

    printf("Dock %i : allows ship %i leaving\n", dockId, getDock(dockId)->myShipId);

    dockedShips[getDock(dockId)->myShipId].myDockId = -1;

    pthread_cond_signal(&dockedShips[getDock(dockId)->myShipId].shipCond);

    while (dockedShips[getDock(dockId)->myShipId].state == LEAVING) //synchronization with customer thread
    {
        pthread_cond_wait(&(getDock(dockId)->dockCond), &mutex1);
    }
    getDock(dockId)->myShipId = -1;

    pthread_mutex_unlock(&mutex1);
}

Port::Dock *Port::getDock(int dockId) {
    for (int i = 0; i < nDocks; i++) {
        if (dock[i].id == dockId) {
            return &dock[i];
        }
    }
    return NULL;
}