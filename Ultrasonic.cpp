 #include "Ultrasonic.h"

 Ultrasonic::Ultrasonic()
 {
    //  warum initialisiert man nicht hier direkt, sondern erst durch einen extra Methodenaufruf
 }

 void Ultrasonic::init()
 {
     for (int i = 0; i < NUM_OF_US; i++)
     {
         Wire.beginTransmission(addresses[i]);
         Wire.write(byte(0x02)); //Set Maximum Analogue Gain to 100, aber warum 100 was bedeutet das genau (wenn es cm sind dann ist es ein bisschen wenig oder?)
         Wire.write(byte(70)); //warum 70? sehe im datenblatt nichts
         Wire.endTransmission();
     }
 }

 void Ultrasonic::fetch()
 {
     for(int i = 0; i < 5; i++) {
     Wire.beginTransmission(addresses[i]);
     Wire.write(byte(0x02));
     Wire.endTransmission();
     Wire.requestFrom((int) addresses[i], (int) 2);

     if (2 <= Wire.available()) { 
         distance[i] = Wire.read() << 8;    
         distance[i] |= Wire.read(); 
     }
   }
 }

 void Ultrasonic::update() {
     if (millis() - lastMeasurement > 25 && !fetched)
     {
         fetch();
         fetched = true;
     }
     if (millis() - lastMeasurement > 65)
     {
         Wire.beginTransmission(0);// auf Adresse 0 hören alle Ultraschallsensor zu. Alternativ können die Befehle an alle Sonsoren einzeln gesendet werden.
         Wire.write(byte(0x00));
         Wire.write(byte(0x51));
         Wire.endTransmission();

         lastMeasurement = millis();
         fetched = false;
     }
 }

     int Ultrasonic::frontLeft() { return distance[0]; }
     int Ultrasonic::left() { return distance[1]; }
     int Ultrasonic::back() {distance[2] = 100; return distance[2]; }
     int Ultrasonic::right() { return distance[3]; }
     int Ultrasonic::frontRight() { return distance[4]; }
     int Ultrasonic::front() { return min(frontLeft(), frontRight()); }
