//////////////////////////////////////////////////////////////////
//         @@ SHO Model sluzeb v oblasti sport @@               //
//                                                              //
//         author:  Michal Wagner (xwagne12)                    //
//         author:  Adam Kala (xkalaa00)                        //
//                                                              //
//                                                              //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "data.h"

Data peakSeason = {
        .simulationTime = 60 * 11 * 7,
        .peopleComeIn = 0.18,
        .hasTicketSpeed = 0.5,
        .noTicketSpeedStart = 2.0,
        .noTicketSpeedEnd = 3.0,
        .poolStart = 0.0,
        .poolEnd = 120.0,
        .saunaStart = 2.0,
        .saunaEnd = 20.0,
        .toboganTakesTime = 0.16,
        .restaurantTakesTime = 0.29,
        .cafeteriaTakesTime = 0.18,
        .queueLenght = 100,
        .leaveTime = 300.0, // Prumerne v letni sezone navstevnik stravi 5h v aquaparku
};


Data weekend = {
        .simulationTime = 60 * 11,
        .peopleComeIn = 0.26,
        .hasTicketSpeed = 0.5,
        .noTicketSpeedStart = 1.0,
        .noTicketSpeedEnd = 2.0,
        .poolStart = 0.0,
        .poolEnd = 120.0,
        .saunaStart = 2.0,
        .saunaEnd = 20.0,
        .toboganTakesTime = 0.52,
        .restaurantTakesTime = 0.87,
        .cafeteriaTakesTime = 0.47,
        .queueLenght = 50,
        .leaveTime = 300.0, // Prumerne v letni sezone navstevnik stravi 3h v aquaparku
};

Data classicSeason = {
        .simulationTime = 60 * 11,
        .peopleComeIn = 0.38,
        .hasTicketSpeed = 0.5,
        .noTicketSpeedStart = 0.5,
        .noTicketSpeedEnd = 2.0,
        .poolStart = 0.0,
        .poolEnd = 120.0,
        .saunaStart = 2.0,
        .saunaEnd = 20.0,
        .toboganTakesTime = 0.40,
        .restaurantTakesTime = 0.7,
        .cafeteriaTakesTime = 0.3,
        .queueLenght = 30,
        .leaveTime = 180.0,
};

Data openingHours = {
        // Prvni dve hodiny, ktere se pocitaji do oteviracky (10:00-12:00)
        .simulationTime = 60 * 2,
        .peopleComeIn = 0.23,
        .hasTicketSpeed = 0.5,
        .noTicketSpeedStart = 0.5,
        .noTicketSpeedEnd = 2.0,
        .poolStart = 0.0,
        .poolEnd = 120.0,
        .saunaStart = 2.0,
        .saunaEnd = 20.0,
        .toboganTakesTime = 0.3,
        .restaurantTakesTime = 0.7,
        .cafeteriaTakesTime = 0.3,
        .queueLenght = 50,
        .leaveTime = 180.0,
};

Data closingHours = {
        // Poslednich 90 minut z oteviraci doby
        .simulationTime = 90,

        // Aby nikdo neprisel po 19:30
        .peopleComeIn = 100000.0,
        .hasTicketSpeed = 4.0,
        .noTicketSpeedStart = 1.0,
        .noTicketSpeedEnd = 1.2,
        .poolStart = 0.0,
        .poolEnd = 120.0,
        .saunaStart = 2.0,
        .saunaEnd = 20.0,
        .toboganTakesTime = 0.3,
        .restaurantTakesTime = 0.7,
        .cafeteriaTakesTime = 0.4,
        .queueLenght = 10,
        .leaveTime = 0.0,
};

Data data = classicSeason;