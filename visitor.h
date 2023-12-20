//////////////////////////////////////////////////////////////////
//         @@ SHO Model sluzeb v oblasti sport @@               //
//                                                              //
//         author:  Michal Wagner (xwagne12)                    //
//         author:  Adam Kala (xkalaa00)                        //
//                                                              //
//                                                              //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef VISITOR_H
#define VISITOR_H

#include <simlib.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "data.h"

extern Facility toboganyFacility[5];
extern Facility deskFacility[10];
extern Facility restaurantFacility[3];
extern Facility cafeFacility[2];

extern Store pool;
extern Store sauna;

class Visitor : public Process {
private:
    int age;
    double restaurantProbability;
    double cafeProbability;
    double toboganProbability;
    double poolProbability;
    double saunaProbability;
    bool wasInRestaurant;
    bool wasInCafeteria;
public:
    Visitor();

    void Behavior();

    void WaitTime(Facility &facility, double time);

    void StandInQueueCashDesk();

    // Nastevnik dojde do prostoru aquaparku a rozhoduje se, co bude delat dal
    void MainHall();

    void InPool();

    void IsInSauna();

    void ToboganQueue();

    void StandInQueueRestaurant();

    void StandInQueueCafeteria();

    void LeaveEnvironment();
};

#endif