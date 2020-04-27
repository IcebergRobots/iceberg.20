#pragma once

struct Shared {
    unsigned long headstartTimer;
    bool enHeadstart;

    enum State {
            standby = 0, offense = 1, defense = 2 
        };

    State currentState;
};