//////////////////////////////////////////////////////////////////
//         @@ SHO Model sluzeb v oblasti sport @@               //
//                                                              //
//         author:  Michal Wagner (xwagne12)                    //
//         author:  Adam Kala (xkalaa00)                        //
//                                                              //
//                                                              //
//                                                              //
//////////////////////////////////////////////////////////////////

#include <simlib.h>
#include "generator.h"

extern Data data_season;
extern bool isPeak;
extern bool isWeekend;
double ArrivalTime;

Generator::Generator(Data *data) {
    Activate();
    dataGen = data;
}

void Generator::Behavior() {
    // Jakou sezonu zrovna testujeme
    if (isPeak) {
        data = peakSeason;
    } else if (isWeekend) {
        data = weekend;
    } else {
        if (Time < 120) {
            data = openingHours;
        } else if (Time >= 120 && Time < 570) {
            data = classicSeason;
        } else {
            data = closingHours;
        }
    }

    // Vytvorime noveho navstevnika
    (new Visitor)->Activate();

    // Cas jeho prichodu
    ArrivalTime = Time;

    // Aktivace navstevnika
    Activate(Time + Exponential(data.peopleComeIn));
}