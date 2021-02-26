#include <iostream>
#include <unistd.h>
#include "Port.h"

using namespace std;

#define ONE_SECOND_US 1000000   // the default number of dock

// prototypes
void *dock(void *);
void *ships(void *);

// set of parameters to be passed to each thread
class ThreadParam {
public:
    ThreadParam(Port *port, int id, int minServiceTime, int maxServiceTime) :
            port(port), id(id), minServiceTime(minServiceTime),
            maxServiceTime(maxServiceTime) {};

    Port *port;
    int id;                     // a thread identifier
    int minServiceTime;         // min service time (us)
    int maxServiceTime;         // max service time (us)
};

int main() {
    int nDocks = 4;
    int nShips = 10;

    int minServiceTime = 2;
    int maxServiceTime = 5;

    pthread_t dock_threads[nDocks];
    pthread_t ship_threads[nShips];

    Port port(nDocks);

    for (int i = 0; i < nDocks; i++) {
        usleep(port.randInt(500, 1000));
        ThreadParam *param = new ThreadParam(&port, i, minServiceTime, maxServiceTime);
        pthread_create(&dock_threads[i], NULL, dock, (void *) param);
    }

    for (int i = 0; i < nShips; i++) {
        usleep(port.randInt(500, 1000));
        ThreadParam *param = new ThreadParam(&port, i, 0, 0);
        pthread_create(&ship_threads[i], NULL, ships, (void *) param);
    }

    for (int i = 0; i <= nShips; i++)
        pthread_join(ship_threads[i], NULL);

    for (int i = 0; i < nDocks; i++)
        pthread_cancel(dock_threads[i]);

    return 0;
}

// the dock thread function
void *dock(void *arg) {
    // extract parameters
    ThreadParam &thread = *(ThreadParam *) arg;
    Port &port = *(thread.port);
    int id = thread.id;
    int minServiceTime = thread.minServiceTime;
    int maxServiceTime = thread.maxServiceTime;
    delete &thread;

    int random;
    // keep working until being terminated by the main
    while (true) {
        port.idleDock(id);      // pick up a new ships
        random = port.randInt(minServiceTime, maxServiceTime);
        printf("Dock %i is holding ship for %s.\n", id, random);
        usleep(random * ONE_SECOND_US); // spend a service time
        port.farewellShip(id);        // release the ships
    }

    return NULL;
}

// the ships thread function
void *ships(void *arg) {
    // extract parameters
    ThreadParam &thread = *(ThreadParam *) arg;
    Port &port = *(thread.port);
    int id = thread.id;
    delete &thread;

    int dockId = -1;
    if ((dockId = port.dockShip(id)) != -1) {               // If ships was assigned to dock
        port.leaveDock(id, dockId);
    }

    return NULL;
}