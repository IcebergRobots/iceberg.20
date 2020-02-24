#pragma once

#include "Config.h"
#include "Hardware.h"

#define START_MARKER 254
#define END_MARKER  255
#define BT_SERIAL Serial2

class Bluetooth : public Hardware
{
  public:
    Bluetooth(const bool& enabled = false)
        {
            _enabled = enabled;
        };

    void init() override;
    void update() override;

    void setMessage(byte *sendMsg);

    byte getMessage(byte index);

  private:
    bool _waitingForMsg = true;
    byte _received;
    byte _tmp[BT_MSG_SIZE];
    byte _receivedMsg[BT_MSG_SIZE];

    byte _sendMsg[BT_MSG_SIZE];

    void send();
    void receive();
};