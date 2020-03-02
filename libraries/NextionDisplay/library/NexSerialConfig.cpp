#include "NexSerialConfig.h"

// Initialisierung der Klassenvariable meinSerial der Klasse StaticSoftwareSerial
// mit einer Instanz (Objekt) der Klasse SoftwareSerial.
// Wie gesagt: Man hätte anstatt der ganzen Objektorientierung hier auch einfach
// "extern SoftwareSerial meinSerial = SoftwareSerial(2, 3);" schreiben können,
// aber mir hat die Compiler-Warnung nicht gefallen.
// Wichtig ist, dass Instanziierungen IMMER in cpp-Dateien statt finden und nicht
// in h-Dateien, sonst kommt dieser "Multiple Definition" Fehler!
SoftwareSerial StaticSoftwareSerial::meinSerial = SoftwareSerial(RX, TX); // RX, TX
