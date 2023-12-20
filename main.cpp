//////////////////////////////////////////////////////////////////
//         @@ SHO Model sluzeb v oblasti sport @@               //
//                                                              //
//         author:  Michal Wagner (xwagne12)                    //
//         author:  Adam Kala (xkalaa00)                        //
//                                                              //
//                                                              //
//                                                              //
//////////////////////////////////////////////////////////////////

#include <iostream>
#include <simlib.h>
#include "data.h"
#include "visitor.h"
#include "generator.h"

extern int N;
bool isPeak = false;
bool isWeekend = false;

// Pouziti aplikace
int printHelp() {
    std::cout << "Description: Aqualand Moravia simulation" << std::endl;
    std::cout << "Usage: ./ims [-h] [-p] [-c] [-o] [-e]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h       Show this help message" << std::endl;
    std::cout << "  -p       Peak season simulation" << std::endl;
    std::cout << "  -c       Classic season simulation" << std::endl;
    std::cout << "  -o       Opening hours simulation" << std::endl;
    std::cout << "  -e       Closing hours simulation" << std::endl;
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    int opt;
    bool optionProvided = false;
    bool invalidOption = false;
    bool isClassic = false;

    // Pro testovani, podle toho jaky argument zadame, takova se bude simulovat situace
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            printHelp();
            return EXIT_SUCCESS;
        } else if (arg.length() == 2 && arg[0] == '-' && !optionProvided) {
            switch (arg[1]) {
                case 'p':
                    data = peakSeason;
                    isPeak = true;
                    optionProvided = true;
                    break;
                case 'c':
                    data = classicSeason;
                    isClassic = true;
                    optionProvided = true;
                    break;
                case 'o':
                    data = openingHours;
                    optionProvided = true;
                    break;
                case 'e':
                    data = closingHours;
                    optionProvided = true;
                    break;
                case 'w':
                    data = weekend;
                    isWeekend = true;
                    optionProvided = true;
                    break;
                default:
                    invalidOption = true;
                    break;
            }
        } else {
            invalidOption = true;
        }
    }

    // Pokud byl argument spatne zadany
    if (!optionProvided || invalidOption) {
        std::cerr << "Please provide a single valid option using '-p', '-c', '-o', or '-e'." << std::endl;
        printHelp();
        return 1;
    }

    // Output pro simulaci
    SetOutput("aqualand_simulation.txt");

    // Aby se pokazde vytovrila jina simuulace
    long seedValue = time(nullptr);
    RandomSeed(seedValue);

    // data.simulationTime se bude odvijet od toho, kolik lidi ma dojit
    Init(0, data.simulationTime);

    Generator *generator = new Generator(&data);
    Run();


    // Vypis vsech pokladen
    for (int a = 0; a < N; a++) {
        deskFacility[a].Output();
    }

    // Vypis toboganu
    for (int y = 0; y < 5; y++) {
        toboganyFacility[y].Output();
    }

    // Vypis pokladen v restauraci
    for (int x = 0; x < 3; x++) {
        restaurantFacility[x].Output();
    }

    // Vypis pokladen v kafeterii
    for (int p = 0; p < 2; p++) {
        cafeFacility[p].Output();
    }

    // Vypis bazenu (bereme jako celek)
    pool.Output();

    // Vypis sauny (bereme jako celek)
    sauna.Output();

    SIMLIB_statistics.Output();

    return 0;
}
