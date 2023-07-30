#include"Pressure_XGZP6847D.h"
#include <Wire.h>


XGZP6847D::XGZP6847D(uint16_t _K)
{
  K = _K;
  I2C_device_address = _I2C_device_address;
}
bool XGZP6847D::begin()
{
#ifdef debug
  Serial.begin(9600);
#endif
  Wire.begin(I2C_device_address);
  Wire.beginTransmission(I2C_device_address);
  if (Wire.endTransmission() == 0)
  {
    return true;
  }
  return false;
}
uint32_t XGZP6847D::getRawPressure()
{
  uint8_t cmd_reg;
  uint8_t P_MSB_reg;
  uint8_t P_CSB_reg;
  uint8_t P_LSB_reg;
  uint32_t Pressure_ADC;
  Wire.beginTransmission(I2C_device_address);
  Wire.write(0x30);
  Wire.write(0x0A);
  Wire.endTransmission();
  do {
    Wire.beginTransmission(I2C_device_address);
    Wire.write(0x30);
    Wire.endTransmission();
    Wire.requestFrom(I2C_device_address, byte(1));
    cmd_reg = Wire.read();

  } while ((cmd_reg & 0x08) == 1);

  Wire.beginTransmission(I2C_device_address);
  Wire.write(0x06);
  Wire.endTransmission();
  Wire.requestFrom(I2C_device_address, byte(3));
  P_MSB_reg = Wire.read();
  P_CSB_reg = Wire.read();
  P_LSB_reg = Wire.read();
  Pressure_ADC = (P_MSB_reg << 8) + P_CSB_reg ;
  Pressure_ADC = (Pressure_ADC << 8) + P_LSB_reg  ;

#ifdef debug
  Serial.print("P_MSB_reg :");
  Serial.println(P_MSB_reg);
  Serial.print("P_CSB_reg :");
  Serial.println(P_CSB_reg);
  Serial.print("P_LSB_reg :");
  Serial.println(P_LSB_reg);
#endif
  Pressure_ADC = ((Pressure_ADC << 8) >> 8);

                 return Pressure_ADC;


}
uint32_t XGZP6847D::getRawTempature()
{
  uint8_t cmd_reg;
  uint8_t T_MSB_reg;
  uint8_t T_LSB_reg;
  uint16_t Tempature_ADC;
  Wire.beginTransmission(I2C_device_address);
  Wire.write(0x30);
  Wire.write(0x0A);
  Wire.endTransmission();
  do {
    Wire.beginTransmission(I2C_device_address);
    Wire.write(0x30);
    Wire.endTransmission();
    Wire.requestFrom(I2C_device_address, byte(1));
    cmd_reg = Wire.read();

  } while ((cmd_reg & 0x08) == 1);

  Wire.beginTransmission(I2C_device_address);
  Wire.write(0x09);
  Wire.endTransmission();
  Wire.requestFrom(I2C_device_address, byte(2));
  T_MSB_reg = Wire.read();
  T_LSB_reg = Wire.read();
  Tempature_ADC = (T_MSB_reg << 8) + T_LSB_reg;
#ifdef debug
  Serial.print("T_MSB_reg :");
  Serial.println(T_MSB_reg);
  Serial.print("T_LSB_reg :");
  Serial.println(T_LSB_reg);
#endif
  return Tempature_ADC;
}
float XGZP6847D::getPressure()
{

  if ((  getRawPressure() & 0x800000 ) == 0 )
    return float(getRawPressure()) / K;
  else
    return (float(getRawPressure()) - pow(2, 24)) / K;
}

float XGZP6847D::getTempature()
{
  return float(getRawTempature()) / 256;
}
