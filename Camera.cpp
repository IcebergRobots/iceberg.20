#include "Camera.h"

void Camera::init()
{
    if (getEn())
    {
        LogCam("enabled");
        // SPI.begin(); wird automatisch in pixy init gemacht
        Pixy::init();
        LogCam("Calibrated");
    } else
        LogCam("disabled");
}

void Camera::update()
{
    if (millis() - _timer > 50 && getEn())
    {
        _ballArea = 0;
        _ballPos = 0;
        _ballHeight = 0;
        _ballWidth = 0;
        _goalArea = 0;
        _goalPos = 0;
        _goalWidth = 0;
        _goalHeight = 0;
        _blockCount = getBlocks();
        Serial.println(_blockCount);
        if (_blockCount)
        {
            for (int i = 0; i < _blockCount; i++)
            {
                int signature = blocks[i].signature;
                switch (signature)
                {
                case SIG_BALL:
                    // if (blocks[i].height * blocks[i].width > _ballArea)
                    // {
                        _ballHeight = blocks[i].height;
                        _ballPos = blocks[i].x;
                        _ballWidth = blocks[i].width;
                        _ballArea = _ballHeight * _ballWidth;
                        _ballCount++;
                    // }
                case SIG_GOAL:
                    // if (blocks[i].height * blocks[i].width > _goalArea)
                    // {
                        _goalHeight = blocks[i].height;
                        _goalPos = blocks[i].x;
                        _goalWidth = blocks[i].width;
                        _goalArea = _goalHeight * _goalWidth;
                        _goalCount++;
                    // }
                }
            }
        }
        _timer = millis();
    }
}

int Camera::getBArea()
{
    return _ballArea;
}

int Camera::getBPos()
{
    return _ballPos;
}

int Camera::getGArea()
{
    return _goalArea;
}

int Camera::getGWidth()
{
    return _goalWidth;
}