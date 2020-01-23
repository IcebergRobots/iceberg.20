#include "Camera.h"

void Camera::init()
{
    if (getEn())
    {
        SPI.begin();
        Pixy::init();
    }
}

void Camera::update()
{
    if (millis() - _timer > 50 && getEn())
    {
        _ballArea = 0;
        _ballPos = 0;
        _goalArea = 0;
        _goalPos = 0;
        _blockCount = getBlocks();
        if (_blockCount != 0)
        {
            for (int i = 0; i < _blockCount; i++)
            {
                int signature = blocks[i].signature;
                int position = blocks[i].x;
                int height = blocks[i].height;
                int width = blocks[i].width;
                int area = height * width;
                switch (signature)
                {
                case SIG_BALL:
                    if (area > _ballArea)
                    {
                        _ballArea = area;
                        _ballPos = position;
                        _ballCount++;
                    }
                case SIG_GOAL:
                    if (area > _goalArea)
                    {
                        _goalArea = area;
                        _goalPos = position;
                        _goalCount++;
                    }
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