#include "Hardware.h"

void Hardware::setEn(const bool& enabled)
{
    _enabled = enabled;
}

const bool Hardware::getEn()
{
    return _enabled;
}