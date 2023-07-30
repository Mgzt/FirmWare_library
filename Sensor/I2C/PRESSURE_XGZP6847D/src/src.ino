#include"Pressure_XGZP6847D.h"

XGZP6847D sensor(64);
void setup()
{
  Serial.begin(9600);
  if ( sensor.begin())Serial.print("sucsses connected");
  else {
    Serial.print("fail connected");
    for (;;) {}
  };
  delay(1000);
}

void loop()
{
  float pressure = sensor.getPressure();
  float Temp = sensor.getTempature();
  Serial.print("pressure :"  );
  Serial.print(pressure); Serial.println("PA" );
  Serial.print("pressure kpa:"  );
  Serial.print(pressure/1000); Serial.println("kPA" );
  Serial.print("Temp : " );
  Serial.println(Temp);
  delay(200);
}
