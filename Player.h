#pragma once

#include "Display.h"
#include "Ultrasonic.h"
#include "Compass.h"
#include "Utility.h"
#include "Pui.h"
#include "Camera.h"
#include "Chassis.h"
#include "BallTouch.h"
#include "Kick.h"

class Player
{
public:
    virtual ~Player(){};

    virtual Player *update() = 0;
    virtual void play() = 0;

    virtual void updPos(); //Kompass ausrichten

    virtual void rate() = 0;          //Position bewerten (individuell bestimmen)
    virtual void communication() = 0; // Daten zwischen Robotern austauschen (individuell welche daten)
};