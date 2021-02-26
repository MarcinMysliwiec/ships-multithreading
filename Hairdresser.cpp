//
// Created by psiw on 11.02.2021.
//

#include "Hairdresser.h"

Hairdresser::Hairdresser(int nBarbers, int nChairs,
                         int priceForHaircut) // initialize a Hairdresser object with parameters
{
    this->nBarbers = nBarbers;
    this->nChairs = nChairs;
    this->priceForHaircut = priceForHaircut;

    pthread_mutex_init(&mutex1, NULL);

    barbers = new Barber[nBarbers];
    for (int i = 0; i < nBarbers; i++) {
        barbers[i].id = i;
        pthread_cond_init(&barbers[i].barberCond, NULL);
    }
}

int Hairdresser::randInt(int min, int max) {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

int Hairdresser::visitShop(int customerId) // return a non-negative number only when a customer got a service
{
    pthread_mutex_lock(&mutex1);
    if (customers[customerId].cash.getSum() < priceForHaircut) {
        printf("customer |%i| : leaves the shop because has not enough money. \n", customerId);
        pthread_mutex_unlock(&mutex1);
        return -1;
    }
    if (((int) waitingCustomers.size() == nChairs) && (sleepingBarbers.empty())) {
        printf("customer |%i| : leaves the shop because of no available waiting chairs. \n", customerId);
        pthread_mutex_unlock(&mutex1);
        return -1;
    }

    customers[customerId] = Customer();
    customers[customerId].id = customerId;
    pthread_cond_init(&customers[customerId].customerCond, NULL);
    int barberId;

    if (sleepingBarbers.empty()) {
        waitingCustomers.push(customerId);
        customers[customerId].state = WAIT;

        printf("customer |%i| : takes a waiting chair. # waiting seats available = %i \n",
               customerId, (int) (nChairs - waitingCustomers.size()));

        while (customers[customerId].myBarber == -1) {
            pthread_cond_wait(&customers[customerId].customerCond, &mutex1);
        }
        barberId = customers[customerId].myBarber;
    } else {    //there are sleeping barbers in a queue
        barberId = sleepingBarbers.front();
        sleepingBarbers.pop();
        customers[customerId].myBarber = barberId;
        getBarber(barberId)->myCustomer = customerId;
    }

    printf("customer |%i| : moves to a service chair[%i], # waiting seats available = %i \n",
           customerId, barberId, (int) (nChairs - waitingCustomers.size()));

    customers[customerId].state = CHAIR;
    pthread_cond_signal(&(getBarber(barberId)->barberCond));
    pthread_mutex_unlock(&mutex1);
    payForVisit(customerId);
    return barberId;
}

void Hairdresser::leaveShop(int customerId, int barberId) {
    pthread_mutex_lock(&mutex1);
    printf("customer |%i| : wait for barber|%i| to be done with hair-cut.\n", customerId, barberId);

    while (customers[customerId].myBarber != -1) {
        pthread_cond_wait(&customers[customerId].customerCond, &mutex1);
    }

    customers[customerId].state = LEAVING;
    giveChange(customerId);
    printf("customer |%i| : says good-bye to barber|%i|\n", customerId, barberId);
    pthread_cond_signal(&(getBarber(barberId)->barberCond));

    pthread_mutex_unlock(&mutex1);
}

void Hairdresser::helloCustomer(int barberId) {
    pthread_mutex_lock(&mutex1);

    if (getBarber(barberId)->myCustomer == -1) {
        printf("barber   |%i| : sleeps because of no customers.\n", barberId);
        sleepingBarbers.push(barberId);
        while (getBarber(barberId)->myCustomer == -1) {
            pthread_cond_wait(&(getBarber(barberId)->barberCond), &mutex1);
        }
    }

    while (customers[getBarber(barberId)->myCustomer].state != CHAIR) //synchronization with customer thread
    {
        pthread_cond_wait(&(getBarber(barberId)->barberCond), &mutex1);
    }

    printf("barber   |%i| : starts a hair-cut service for customer|%i|\n", barberId, getBarber(barberId)->myCustomer);

    pthread_mutex_unlock(&mutex1);
}

void Hairdresser::byeCustomer(int barberId) {
    pthread_mutex_lock(&mutex1);
    printf("barber   |%i| : says he's done with a hair-cut service for customer|%i|\n", barberId,
           getBarber(barberId)->myCustomer);

    customers[getBarber(barberId)->myCustomer].myBarber = -1;

    pthread_cond_signal(&customers[getBarber(barberId)->myCustomer].customerCond);

    while (customers[getBarber(barberId)->myCustomer].state == CHAIR) //synchronization with customer thread
    {
        pthread_cond_wait(&(getBarber(barberId)->barberCond), &mutex1);
    }

    getBarber(barberId)->myCustomer = -1;

    printf("barber   |%i| : calls in another customer.\n", barberId);
    if (!waitingCustomers.empty()) {
        int customerId = waitingCustomers.front();
        waitingCustomers.pop();
        getBarber(barberId)->myCustomer = customerId;
        customers[customerId].myBarber = barberId; //?
        pthread_cond_signal(&customers[customerId].customerCond);
    }

    pthread_mutex_unlock(&mutex1);
}

Hairdresser::Barber *Hairdresser::getBarber(int barberId) {
    for (int i = 0; i < nBarbers; i++) {
        if (barbers[i].id == barberId) {
            return &barbers[i];
        }
    }
    return NULL;
}

void Hairdresser::goToWork(int customerId) {
    pthread_mutex_lock(&mutex1);
    customers[customerId].state = WORK;
    printf("customer |%i| : went to work.\n", customerId);
    pthread_mutex_unlock(&mutex1);
}


void Hairdresser::leaveWork(int customerId) {
    pthread_mutex_lock(&mutex1);

    customers[customerId].cash.fives = randInt(1, 2);
    customers[customerId].cash.twos = randInt(1, 2);
    customers[customerId].cash.ones = randInt(1, 3);

    printf("customer |%i| : left work with 5$:%i, 2$:%i, 1$:%i\n", customerId,
           customers[customerId].cash.fives, customers[customerId].cash.twos, customers[customerId].cash.ones);

    customers[customerId].state = IDLE;
    pthread_mutex_unlock(&mutex1);
}


void Hairdresser::payForVisit(int customerId) {
    pthread_mutex_lock(&mutex1);
    Cash customerCash = customers[customerId].cash;
    Cash *collectedCash = new Cash();

    while (collectedCash->getSum() < priceForHaircut) {
        int randIndex = randInt(1, 3);
        switch (randIndex) {
            case 1:
                if (customerCash.ones > collectedCash->ones) {
                    collectedCash->ones++;
                    break;
                }
            case 2:
                if (customerCash.twos > collectedCash->twos) {
                    collectedCash->twos++;
                    break;
                }
            case 3:
                if (customerCash.fives > collectedCash->fives) {
                    collectedCash->fives++;
                    break;
                }
        }
    }
    customers[customerId].change = collectedCash->getSum() - priceForHaircut;

    customerCash.ones -= collectedCash->ones;
    customerCash.twos -= collectedCash->twos;
    customerCash.fives -= collectedCash->fives;
    customers[customerId].cash = customerCash;

    cash.ones += collectedCash->ones;
    cash.twos += collectedCash->twos;
    cash.fives += collectedCash->fives;

    printf("customer |%i| : paid: %i$ with 5$:%i, 2$:%i, 1$:%i (will need change - %i$)\n", customerId,
           collectedCash->getSum(), collectedCash->fives, collectedCash->twos, collectedCash->ones,
           customers[customerId].change);
    pthread_mutex_unlock(&mutex1);
}

void Hairdresser::giveChange(int customerId) {
    int change = customers[customerId].change;
    Cash *collectedCash = new Cash();

    collectedCash->fives = change / 5;
    change -= collectedCash->fives * 5;
    collectedCash->twos = change / 2;
    change -= collectedCash->twos * 2;
    collectedCash->ones = change;


    while (collectedCash->fives > cash.fives && collectedCash->twos > cash.twos && collectedCash->ones > cash.ones) {
        pthread_cond_wait(&cashCond, &mutex1);
    }

    cash.ones -= collectedCash->ones;
    cash.twos -= collectedCash->twos;
    cash.fives -= collectedCash->fives;

    customers[customerId].cash.ones += collectedCash->ones;
    customers[customerId].cash.twos += collectedCash->twos;
    customers[customerId].cash.fives += collectedCash->fives;

    printf("customer |%i| : is given change: %i$ with 5$:%i, 2$:%i, 1$:%i\n", customerId, customers[customerId].change,
           collectedCash->fives,
           collectedCash->twos, collectedCash->ones);

    customers[customerId].change = 0;
}
