#ifndef __NEXSERIALCONFIG_H__
#define __NEXSERIALCONFIG_H__

#include <SoftwareSerial.h>

/**
 * Umhüllt die SoftwareSerial, sodass weltweit nur eine einzige Instanz existiert
 * die statisch referenziert werden kann. Normalerweise würde man hierfür das
 * Singleton-Entwurfsmodell verwenden, aber ich war faul.
 * 
 * Anstatt die Referenz auf meinSerial in dieser statischen Klasse zu verstecken
 * (objektorientierte Variante), könnte man sie in der cpp-Datei auch als "extern"
 * markieren. Dann existiert sie überall. Das hat aber eine Warnung erzeugt und ich
 * kann es nicht ausprobieren, also bleiben wir lieber bei der objektorientierten
 * Variante.
 */

#define RX 66
#define TX 41
class StaticSoftwareSerial {
    public:
        // Klassenvariable (statisch): Referenz auf ein Objekt der Klasse SoftwareSerial
        static SoftwareSerial meinSerial;
};

#endif /* #ifndef __NEXSERIALCONFIG_H__ */
