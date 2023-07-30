#ifndef PRESSURE_XGZP6847D_H
#define PRESSURE_XGZP6847D_H

#include <Arduino.h>

#define _I2C_device_address 0x6D

class XGZP6847D {

    public:
    XGZP6847D(uint16_t _K);
    bool begin();
    float getPressure();
    float getTempature();

    uint32_t getRawPressure();
    uint32_t getRawTempature();
    
    private:
    uint8_t I2C_device_address;
    uint16_t K;
};










#endif
