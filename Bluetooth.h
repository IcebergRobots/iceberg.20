#pragma once

#include "Config.h"

#define CACHE_SIZE 10               // Länge des Input Byte Buffers
#define BLUETOOTH_SERIAL Serial2    // Serial des Bluetooth-Moduls
#define START_MARKER 254            // Startzeichen einer Bluetooth-Nachricht
#define END_MARKER 255              // Endzeichen einer Bluetooth-Nachricht

class Bluetooth
{
 public:
    byte receive();
    unsigned long timeout();
    void send(byte * data, byte numberOfElements = 1);
    
  private:
    byte fetch();

    byte role = 0;
    byte state = 0;
    byte score = 0;
    
    byte cache[CACHE_SIZE]; // Zwischenspeicher für eingehende Bluetooth Nachrichten
    byte cacheIndex = 255;  // aktuelle Schreibposition im Zwischenspeicher
    
    unsigned long responseTimer = 0;
};