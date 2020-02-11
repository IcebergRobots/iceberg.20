#include "Bluetooth.h"

/*****************************************************
  übertrage Daten an den Patner
  @param data: Datenarray
  @param numberOfElements: Länge des Arrays
*****************************************************/
void Bluetooth::send(byte *data, byte numberOfElements)
{
    if (BLUETOOTH)
    {
        BLUETOOTH_SERIAL.write(START_MARKER);
        for (byte i = 0; i < numberOfElements; i++)
        {
            BLUETOOTH_SERIAL.write(constrain(data[i], 0, 253));
        }
        BLUETOOTH_SERIAL.write(END_MARKER);
    }
}

/*****************************************************
  empfange Daten an des Patners
  - speichere diese im Cache
*****************************************************/
byte Bluetooth::fetch()
{
    // returns length of incomming message
    if (BLUETOOTH)
    {
        while (BLUETOOTH_SERIAL.available())
        {
            byte b = BLUETOOTH_SERIAL.read();
            if (cacheIndex != 255)
            { // aktives Zuhören?
                if (b == START_MARKER)
                {
                    cacheIndex = 0; // aktiviere Zuhören
                    for (byte i = 0; i < CACHE_SIZE; i++)
                    {
                        cache[i] = 255; // überschreibe den Cache
                    }
                }
                else if (b == END_MARKER)
                {
                    byte messageLength = cacheIndex;
                    cacheIndex = 255;     // deaktiviere Zuhören
                    return messageLength; // Befehl empfangen!
                }
                else
                {
                    if (cacheIndex >= CACHE_SIZE)
                    {
                        cacheIndex = 255; // deaktiviere Zuhören
                    }
                    else
                    {
                        cache[cacheIndex] = b; // speichere in Cache
                        cacheIndex++;       // speichere index
                    }
                }
            }
            else
            {
                if (b == START_MARKER)
                {
                    cacheIndex = 0; // aktiviere Zuhören
                    for (byte i = 0; i < CACHE_SIZE; i++)
                    {
                        cache[i] = 255; // überschreibe den Cache
                    }
                }
            }
        }
    }
    return 0;
}

/*****************************************************
  lese Nachrichten aus dem Cache aus
*****************************************************/
byte Bluetooth::receive()
{
    byte messageLength = fetch(); // aktualisiere den Cache
    if (messageLength == 3 && cache[0] == 'h')
    {
        /*****************************************************
      Sende einen Herzschlag mit Statusinformationen an den Partner

      Byte    Information   mögliche Zustände
      -----------------------------------------------------
      0       Pakettyps     Heartbeat(104)
      1       Status+Rolle  Aus(0+Status) / Torwart(1+Status) / Stürmer(2+Status)
      2       Score         Blind(0) / Bewertung(...)
    *****************************************************/
        role = cache[1] / 10;
        state = cache[1] % 10;
        score = cache[2];
        responseTimer = millis();
    }
    if (messageLength > 0)
    {
        return cache[0];
    }
    else
    {
        return 255;
    }
}

unsigned long Bluetooth::timeout()
{
    if (millis() - responseTimer < 500)
        return 0;
    else
        return millis() - responseTimer;
}
