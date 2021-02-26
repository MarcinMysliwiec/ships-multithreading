#ifndef SLEEPING_BARBER_PROBLEM_HAIRDRESSER_H
#define SLEEPING_BARBER_PROBLEM_HAIRDRESSER_H

#include <pthread.h>
#include <queue>
#include <map>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

class Hairdresser {
public:
    enum CUSTOMER_STATE {
        IDLE,
        WORK,
        WAIT,
        CHAIR,
        LEAVING
    };

    Hairdresser(int nBarbers, int nChairs, int priceForHaircut);

    Hairdresser();

    int randInt(int min, int max); // return a number between min and max

    int visitShop(int customerId); // return a non-negative number only when a customer got a service

    void leaveShop(int customerId, int barberId);

    void helloCustomer(int barberId);

    void byeCustomer(int barberId);

    void goToWork(int customerId);

    void leaveWork(int customerId);

    void payForVisit(int customerId);

    void giveChange(int customerId);

private:
    int nBarbers;
    int nChairs;
    int priceForHaircut;
    pthread_cond_t cashCond;

    struct Cash {
        int ones;
        int twos;
        int fives;

        Cash() : ones(0), twos(0), fives(0) {}

        Cash(int ones, int twos, int fives) : ones(ones), twos(twos), fives(fives) {}

        int getSum() {
            return (1 * ones) + (2 * twos) + (5 * fives);
        }
    };

    struct Barber {
        int id;
        int myCustomer = -1; // no customer by default
        pthread_cond_t barberCond;
    };

    struct Customer {
        int id;
        int myBarber = -1; // no barber by default
        int change = 0;
        CUSTOMER_STATE state = IDLE; // waiting state by default
        Cash cash = *new Cash(3, 3, 2);
        pthread_cond_t customerCond;
    };

    Cash cash;
    Barber *barbers; // array of barber objects
    map<int, Customer> customers; // container for customer objects

    queue<int> waitingCustomers;
    queue<int> sleepingBarbers;

    pthread_mutex_t mutex1;

    Barber *getBarber(int barberId);
};

#endif