//////////////////////////////////////////////////////////////////
//         @@ SHO Model sluzeb v oblasti sport @@               //
//                                                              //
//         author:  Michal Wagner (xwagne12)                    //
//         author:  Adam Kala (xkalaa00)                        //
//                                                              //
//                                                              //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef GEN_H
#define GEN_H

#include <vector>
#include <simlib.h>
#include "visitor.h"
#include "data.h"

// Generator navstevniku
class Generator : public Event {
    std::vector<Visitor *> visitors;
    Data *dataGen;
public:
    Generator(Data *data);

    void Behavior();
};

#endif