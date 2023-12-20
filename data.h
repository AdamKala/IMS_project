//////////////////////////////////////////////////////////////////
//         @@ SHO Model sluzeb v oblasti sport @@               //
//                                                              //
//         author:  Michal Wagner (xwagne12)                    //
//         author:  Adam Kala (xkalaa00)                        //
//                                                              //
//                                                              //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef DATA_H
#define DATA_H


typedef struct {
    int simulationTime;
    double peopleComeIn;
    double hasTicketSpeed;
    double noTicketSpeedStart;
    double noTicketSpeedEnd;
    double poolStart;
    double poolEnd;
    double saunaStart;
    double saunaEnd;

    double toboganTakesTime;
    double restaurantTakesTime;
    double cafeteriaTakesTime;
    double barTakesTime;
    double saunaTakesTime;
    double poolTakesTime;
    double cashDeskTakesTime;
    int queueLenght;

    double leaveTime;
} Data;


extern Data peakSeason;
extern Data classicSeason;
extern Data openingHours;
extern Data closingHours;
extern Data weekend;
extern Data data;

#endif
