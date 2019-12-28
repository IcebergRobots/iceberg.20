#pragma once

class Hardware {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
};