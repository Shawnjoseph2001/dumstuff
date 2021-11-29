#ifndef VALVEDEFINITIONS_H
#define VALVEDEFINITIONS_H

#include "ValveClass.h"
#include <array>

// Define number of valves here
#define NUM_VALVES 10

// Declare all Valve Objects here using ValveClass, and add them to the valveArray
// On Engine Node
Valve HiPress{16, 2, NormalClosed, 2, 25000};
Valve HiPressVent{17, 2, NormalClosed, 5, 25000};
Valve FuelMV{26, 2, NormalClosed, 6, 25000, 12000000};
Valve LoxMV{27, 2, NormalClosed, 7, 25000, 12000000};
// On Prop Node
Valve FuelVent{21, 3, NormalClosed, 2, 25000};
Valve LoxDomeReg{19, 3, NormalClosed, 5, 25000};
Valve LoxDomeRegVent{20, 3, NormalClosed, 6, 25000};
Valve FuelDomeReg{22, 3, NormalClosed, 7, 25000};
Valve FuelDomeRegVent{23, 3, NormalClosed, 8, 25000};
Valve LoxVent{18, 3, NormalOpen, 2, 500000, 9, 166};


// ADD VALVES TO THIS VALVE ARRAY IN THE FORM: &VALVE

std::array<Valve*, NUM_VALVES> valveArray{&HiPress, &HiPressVent, &LoxVent, &LoxDomeReg, &LoxDomeRegVent, &FuelVent, &FuelDomeReg, &FuelDomeRegVent, &FuelMV, &LoxMV};






#endif