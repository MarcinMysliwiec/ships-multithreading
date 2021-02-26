#include <iostream>    // cout
#include <sys/time.h> // gettimeofday
#include <unistd.h> //usleep
#include "Hairdresser.h"

using namespace std;

#define ONE_SECOND_US 1000000   // the default number of barbers

// prototypes
void *barber(void *);           // the barber thread function
void *customer(void *);         // the customer thread function

// set of parameters to be passed to each thread
class ThreadParam {
public:
    ThreadParam(Hairdresser *hairdresser, int id, int minServiceTime, int maxServiceTime) :
            pHairdresser(hairdresser), id(id), minServiceTime(minServiceTime),
            maxServiceTime(maxServiceTime) {};

    Hairdresser *pHairdresser;  // a pointer to the Hairdresser object
    int id;                     // a thread identifier
    int minServiceTime;         // min service time (us)
    int maxServiceTime;         // max service time (us)
};

int main() {
    int nBarbers = 1;           // Workers
    int nChairs = 1;            // Queue size
    int priceForHaircut = 13;   // Price for having haircut
    int nCustomers = 3;         // Customers
    int minServiceTime = 2;     // Barber's service time in seconds
    int maxServiceTime = 5;

    pthread_t barber_thread[nBarbers];
    pthread_t customer_threads[nCustomers + 1];
    Hairdresser hairdresser(nBarbers, nChairs, priceForHaircut);    // instantiate a hairdresser

    for (int i = 0; i < nBarbers; i++) {    // instantiate barbers
        ThreadParam *param = new ThreadParam(&hairdresser, i, minServiceTime, maxServiceTime);
        pthread_create(&barber_thread[i], NULL, barber, (void *) param);
    }
    for (int i = 0; i < nCustomers; i++) {  // instantiate customers
        usleep(hairdresser.randInt(500, 1000));
        ThreadParam *param = new ThreadParam(&hairdresser, i, minServiceTime, maxServiceTime);
        pthread_create(&customer_threads[i], NULL, customer, (void *) param);
    }

    for (int i = 0; i <= nCustomers; i++)    // wait until all the customers are served
        pthread_join(customer_threads[i], NULL);

    for (int i = 0; i < nBarbers; i++)      // terminate all the barbers
        pthread_cancel(barber_thread[i]);

    return 0;
}

// the barber thread function
void *barber(void *arg) {

    // extract parameters
    ThreadParam &thread = *(ThreadParam *) arg;
    Hairdresser &hairdresser = *(thread.pHairdresser);
    int id = thread.id;
    int minServiceTime = thread.minServiceTime;
    int maxServiceTime = thread.maxServiceTime;
    delete &thread;

    int random;
    // keep working until being terminated by the main
    while (true) {
        hairdresser.helloCustomer(id);      // pick up a new customer
        random = hairdresser.randInt(minServiceTime, maxServiceTime);
        printf("barber   |%i| : is working %is\n", id, random);
        usleep(random * ONE_SECOND_US); // spend a service time
        hairdresser.byeCustomer(id);        // release the customer
    }

    return NULL;
}

// the customer thread function
void *customer(void *arg) {
    // extract parameters
    ThreadParam &thread = *(ThreadParam *) arg;
    Hairdresser &hairdresser = *(thread.pHairdresser);
    int id = thread.id;
    int minServiceTime = thread.minServiceTime;
    int maxServiceTime = thread.maxServiceTime;
    delete &thread;

    int random;
    while (true) { // Initiate customer's routine
        int barber = -1;
        if ((barber = hairdresser.visitShop(id)) != -1) {               // If customer was assigned to barber
            hairdresser.leaveShop(id, barber);
        }
        hairdresser.goToWork(id);               // After visiting hairdresser go to work
        random = hairdresser.randInt(minServiceTime, maxServiceTime);
        printf("customer |%i| : is working %is\n", id, random);
        usleep(random * ONE_SECOND_US); // Spend some time at hairdresse's
        hairdresser.leaveWork(id);              // Leave work
    }

    return NULL;
}