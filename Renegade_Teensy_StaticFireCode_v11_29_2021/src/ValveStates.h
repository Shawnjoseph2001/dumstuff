#ifndef VALVESTATES_H
#define VALVESTATES_H

// defines the possible valve states accross all valves


enum class ValveState
{
    Closed,             // 0
    Open,               // 1
    FireCommanded,      // 2
    OpenCommanded,      // 3
    CloseCommanded,     // 4
    OpenProcess,        // 5
    CloseProcess,       // 6
    ValveState_SIZE,    // 7
};

enum class ValveEnableState
{
    Off,                    // 0
    On,                     // 1
    ValveEnableState_Size,  // 2
};

#endif