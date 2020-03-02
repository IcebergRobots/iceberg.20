#include "Bluetooth.h"

void Bluetooth::init()
{
    if (getEn())
    {
        LogBluetooth("enabled");
        if (!BT_SERIAL)
            Serial.println("BT_SERIAL couldnt Open");
        BT_SERIAL.begin(115200);
        LogBluetooth("Initialized");
    } else
        LogBluetooth("disabled");
}

void Bluetooth::update()
{
    if(getEn())
    {
        send();
        receive();
    }
}

void Bluetooth::setMessage(byte *sendMsg)
{
    for(int i = 0; i < BT_MSG_SIZE; i++)
    {
        _sendMsg[i] = sendMsg[i];
    }
}

byte Bluetooth::getMessage(byte index)
{
    return _receivedMsg[index];
}

void Bluetooth::send()
{
    if(getEn())
    {
        BT_SERIAL.write(START_MARKER);
        for(int i = 0; i < BT_MSG_SIZE; i++)
        {
          BT_SERIAL.write(constrain(_sendMsg[i], 0, 253));
        }
        BT_SERIAL.write(END_MARKER);
    }
}

void Bluetooth::receive()
{
    if(getEn())
    {
        if(BT_SERIAL.available() && _waitingForMsg)
    {
        _received = BT_SERIAL.read();
        if(_received == START_MARKER)
        {
            _waitingForMsg = false;
        }
    }
    if(BT_SERIAL.available() >= BT_MSG_SIZE + 1 && !_waitingForMsg)
    {
            for(int i = 0; i < BT_MSG_SIZE; i++)
            {
                _tmp[i] = BT_SERIAL.read();
            }
            _received = BT_SERIAL.read();
            if(_received == END_MARKER)
            {
                LogBluetooth("Received Succesfully");
                for(int i = 0; i < BT_MSG_SIZE; i++)
                {
                _receivedMsg[i] = _tmp[i];
                }
            }else {
                LogBluetooth("Message could be uncomnplete");
            }
            _waitingForMsg = true;
    }
    }
}