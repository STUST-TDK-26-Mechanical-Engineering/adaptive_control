// This example use SPI.

#include "LIS3DHTR.h"
#include "SPI.h"
LIS3DHTR<SPIClass> LIS; //SPI

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  LIS.begin(10); //SPI SS/CS
  LIS.openTemp();//If ADC3 is used, the temperature detection needs to be turned off.
  //  LIS.closeTemp();//default
  delay(100);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_4G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_8G);
  //  LIS.setFullScaleRange(LIS3DHTR_RANGE_16G);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_1HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_10HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_100HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_200HZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_1_6KHZ);
  //  LIS.setOutputDataRate(LIS3DHTR_DATARATE_5KHZ);
}
void loop()
{
  if (!LIS)
  {
    Serial.println("LIS3DHTR didn't connect.");
    while(1);
    return;
  }
  //3 Axis
//  Serial.print("x:");Serial.print(LIS.getAccelerationX());Serial.print("  ");
//  Serial.print("y:");Serial.print(LIS.getAccelerationY());Serial.print("  ");
//  Serial.print("z:");Serial.println(LIS.getAccelerationZ());
  //ADC
//    Serial.print("adc1:"); Serial.println(LIS.readbitADC1());
//    Serial.print("adc2:"); Serial.println(LIS.readbitADC2());
//    Serial.print("adc3:"); Serial.println(LIS.readbitADC3());
  //temperature
  Serial.print("temp:"); Serial.println(LIS.getTemperature());
  delay(500);
}
