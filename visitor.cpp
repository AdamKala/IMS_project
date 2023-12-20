//////////////////////////////////////////////////////////////////
//         @@ SHO Model sluzeb v oblasti sport @@               //
//                                                              //
//         author:  Michal Wagner (xwagne12)                    //
//         author:  Adam Kala (xkalaa00)                        //
//                                                              //
//                                                              //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "visitor.h"

// Inicializace zarizeni
Facility deskFacility[10];
Facility toboganyFacility[5];
Facility restaurantFacility[3];
Facility cafeFacility[2];

// Inicializace "skladu"
Store sauna("Sauna", 200);
Store pool("Bazen", 2000);

// Cas, kdy zakaznik prisel
extern double ArrivalTime;
int N = 1;
double lastHour = 30.0;


Visitor::Visitor() {
    // Od 10 let pro nejlepsi simulaci, protoze na tobogan se muze chodit od 10
    age = static_cast<int>((Random() * 55) + 10);
    wasInRestaurant = false;
    if (age < 18) {
        cafeProbability = 5.0;
        toboganProbability = 60.0;
        poolProbability = 15.0;
        saunaProbability = 5.0;
        restaurantProbability = 10.0;
    } else if (age >= 18 && age < 40) {
        cafeProbability = 10.0;
        toboganProbability = 55.0;
        poolProbability = 15.0;
        saunaProbability = 5.0;
        restaurantProbability = 10.0;
    } else if (age >= 40 && age < 50) {
        cafeProbability = 15.0;
        toboganProbability = 5.0;
        poolProbability = 40.0;
        saunaProbability = 20.0;
        restaurantProbability = 15.0;
    } else if (age >= 50) {
        cafeProbability = 20.0;
        toboganProbability = 5.0;
        poolProbability = 35.0;
        saunaProbability = 22.0;
        restaurantProbability = 12.0;
    }
    Activate();
}

void Visitor::Behavior() {
    // Navstevnik prijde do fronty na zakoupeni listku
    StandInQueueCashDesk();
}

// Pomocna funkce, aby se neopakoval kod
void Visitor::WaitTime(Facility &facility, double time) {
    facility.Seize(this);
    Wait(Exponential(time));
    facility.Release(this);
}

void Visitor::StandInQueueCashDesk() {
    // Nastaveni jmena pro prvni pokladnu
    deskFacility[0].SetName("Pokladna " + std::to_string(1));
    // Pocatecni pocet pokladen (1)
    int idx = 0;
    for (int a = 0; a < N; a++) {
        if (deskFacility[a].QueueLen() < deskFacility[idx].QueueLen()) {
            idx = a;
        }

        // Pokud pokladna dosahne maximalni delky, otevre se dalsi
        if (deskFacility[a].QueueLen() > data.queueLenght) {
            // Maximalne pocet pokladen v Aqualandu Moravia (10)
            for (int b = 0; b < N; b++) {
                if (deskFacility[b].QueueLen() < deskFacility[idx].QueueLen()) {
                    idx = b;
                }
            }

            // Otevreni nove pokladny
            if (N < 10) {
                deskFacility[N].SetName("Pokladna " + std::to_string(N + 1));
                N += 1;
            }
        }


        if (deskFacility[a].QueueLen() == 0 && N > 1) {
            // Uzavreni pokladny
            N -= 1;
        }
    }


    double hasTicket = Random() * 100;

    // Pokud si zakoupil listek online, jeho cekani je vyrazne nizsi
    if (hasTicket <= 40) {
        Seize(deskFacility[idx]);
        Wait(Exponential(data.hasTicketSpeed));
        Release(deskFacility[idx]);
    } else {
        Seize(deskFacility[idx]);
        Wait(Exponential(Uniform(data.noTicketSpeedStart, data.noTicketSpeedEnd)));
        Release(deskFacility[idx]);
    }

    MainHall();
}

void Visitor::MainHall() {
    // Rozhodnuti, co bude navstevnik v arealu delat
    double decision = Random() * 100;

    // Pokud je jeho straveny cas v aquaparku vyssi nez prumerna doba v aquaparku
    if (Time > (ArrivalTime + data.leaveTime)) {
        LeaveEnvironment();
    }

    // Pokud je cas vetsi nez 30 minut pred zavirackou, muze se clovek rozhodnout co bude jeste delat
    if (Time < data.simulationTime - 30) {
        if (decision < poolProbability) {
            InPool();
        } else if (decision < (poolProbability + toboganProbability)) {
            ToboganQueue();
        } else if (decision < (poolProbability + toboganProbability + cafeProbability)) {
            // Pote co uz jednou byl v kavarne, jeho sance na to ji znovu navstivit se snizi
            if (wasInCafeteria) {
                cafeProbability -= 2;
                toboganProbability += 2;
            }
            StandInQueueCafeteria();
        } else if (decision < (poolProbability + toboganProbability + cafeProbability + restaurantProbability)) {
            // Pote co uz jednou byl v restauraci, jeho sance na to ji znovu navstivit se snizi
            if (wasInRestaurant) {
                restaurantProbability -= 2;
                toboganProbability += 2;
            }
            StandInQueueRestaurant();
        } else if (decision < (poolProbability + toboganProbability + cafeProbability + restaurantProbability +
                               saunaProbability)) {
            IsInSauna();
        } else {
            LeaveEnvironment();
        }
    } else {
        LeaveEnvironment();
    }


    this->Passivate();
}

void Visitor::InPool() {
    double timeInPool;
    Enter(pool, 1);
    if (Time <= data.simulationTime - 140) {
        timeInPool = Uniform(data.poolStart, data.poolEnd); // Nahodna hodnota toho, jak dlouho stravi v bazenu
    } else {
        timeInPool = Uniform(data.poolStart, data.simulationTime - Time - 20);
    }
    Wait(Exponential(timeInPool));
    Leave(pool, 1);

    MainHall();
}

void Visitor::IsInSauna() {
    // Jelikoz je sauna Store, pouzijeme Enter a Leave, misto nasi funkce WaitTime, ktera pouziva Seize a Release
    if (Time < data.simulationTime - 20) {
        Enter(sauna, 1);
        Wait(Exponential(Uniform(data.saunaStart, data.saunaEnd)));
        Leave(sauna, 1);
    } else {
        LeaveEnvironment();
    }
    MainHall();
}

void Visitor::ToboganQueue() {
    // Vyber toboganu podle toho, kde je nejmensi fronta
    double tob1 = toboganyFacility[0].QueueLen();
    double tob2 = toboganyFacility[1].QueueLen();
    double tob3 = toboganyFacility[2].QueueLen();
    double tob4 = toboganyFacility[3].QueueLen();
    double tob5 = toboganyFacility[4].QueueLen();

    double minQueueLen = tob1;

    if (tob2 < minQueueLen) {
        minQueueLen = tob2;
    }

    if (tob3 < minQueueLen) {
        minQueueLen = tob3;
    }

    if (tob4 < minQueueLen) {
        minQueueLen = tob4;
    }

    if (tob5 < minQueueLen) {
        minQueueLen = tob5;
    }

    if (minQueueLen == tob1) {
        toboganyFacility[0].SetName("Tobogan 1");
        if (Time < data.simulationTime - 30) {
            WaitTime(toboganyFacility[0], data.toboganTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
    } else if (minQueueLen == tob2) {
        toboganyFacility[1].SetName("Tobogan 2");
        if (Time < data.simulationTime - 30) {
            WaitTime(toboganyFacility[1], data.toboganTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
    } else if (minQueueLen == tob3) {
        toboganyFacility[2].SetName("Tobogan 3");
        if (Time < data.simulationTime - 30) {
            WaitTime(toboganyFacility[2], data.toboganTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
    } else if (minQueueLen == tob4) {
        toboganyFacility[3].SetName("Tobogan 4");
        if (Time < data.simulationTime - 30) {
            WaitTime(toboganyFacility[3], data.toboganTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
    } else {
        toboganyFacility[4].SetName("Tobogan 5");
        if (Time < data.simulationTime - 30) {
            WaitTime(toboganyFacility[4], data.toboganTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
    }
}

void Visitor::StandInQueueRestaurant() {
    // Vyber pokladny v restauraci podle toho, kde je nejmensi fronta
    double res1 = restaurantFacility[0].QueueLen();
    double res2 = restaurantFacility[1].QueueLen();
    double res3 = restaurantFacility[2].QueueLen();

    double minQueueLen = res1;

    if (res2 < minQueueLen) {
        minQueueLen = res2;
    }

    if (res3 < minQueueLen) {
        minQueueLen = res3;
    }

    if (minQueueLen == res1) {
        restaurantFacility[0].SetName("Restaurace, pokladna 1");
        if (Time < data.simulationTime - 30) {
            WaitTime(restaurantFacility[0], data.restaurantTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
        wasInRestaurant = true;
        MainHall();
    } else if (minQueueLen == res2) {
        restaurantFacility[1].SetName("Restaurace, pokladna 2");
        if (Time < data.simulationTime - 30) {
            WaitTime(restaurantFacility[1], data.restaurantTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
        wasInRestaurant = true;
        MainHall();
    } else {
        restaurantFacility[2].SetName("Restaurace, pokladna 3");
        if (Time < data.simulationTime - 30) {
            WaitTime(restaurantFacility[2], data.restaurantTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
        wasInRestaurant = true;
        MainHall();
    }
}

void Visitor::StandInQueueCafeteria() {
    // Vyber pokladny v kavarne podle toho, kde je nejmensi fronta
    double caf1 = cafeFacility[0].QueueLen();
    double caf2 = cafeFacility[1].QueueLen();

    double minQueueLen = caf1;

    if (caf2 < minQueueLen) {
        minQueueLen = caf2;
    }

    if (minQueueLen == caf1) {
        cafeFacility[0].SetName("Kafeterie, pokladna 1");
        if (Time < data.simulationTime - 30) {
            WaitTime(cafeFacility[0], data.cafeteriaTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
        wasInCafeteria = true;
        MainHall();
    } else {
        cafeFacility[1].SetName("Kafeterie, pokladna 2");
        if (Time < data.simulationTime - 30) {
            WaitTime(cafeFacility[1], data.cafeteriaTakesTime);
            MainHall();
        } else {
            LeaveEnvironment();
        }
        wasInCafeteria = true;
        MainHall();
    }
}

void Visitor::LeaveEnvironment() {
//    wholeTime(Time - arrival);

    // Navstevnik odchazi z aquaparku
    this->Cancel();
}