#pragma once

#include "Config.h"
#include "Hardware.h"

class Bluetooth : public Hardware
{
  public:
    Bluetooth(const bool& enabled = false)
        {
            _enabled = enabled;
        };

    void init() override;
    void update() override;

    void send();
    void receive();

    char b;
  private:

};