//////////////////////////
// Hardware Definitions //
//////////////////////////
#include "HX711.h"

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

// 5, 6, 7, 8 in clock-data-clock-data
#define DOUT1  6
#define CLK1  5
#define DOUT2  8
#define CLK2  7
// 9, 10, 11, 12 in clock-data-clock-data
#define DOUT3  10
#define CLK3  9
#define DOUT4  12
#define CLK4  11


HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

#define PIR_DOUT_FIRST 2   // FIRST PIR digital output on D2
#define PIR_DOUT_SECOND 3   // SECOND PIR digital output on D3
#define PIR_DOUT_THIRD 4   // THIRD PIR digital output on D4

#define PRINT_TIME 500 // Rate of serial printouts
unsigned long lastPrint = 0; // Keep track of last serial out

void setup() 
{
  Serial.begin(115200);  // Serial is used to view Analog out
  // Analog and digital pins should both be set as inputs:
  pinMode(PIR_DOUT_FIRST, INPUT);
  pinMode(PIR_DOUT_SECOND, INPUT);
  pinMode(PIR_DOUT_THIRD, INPUT);

  scale1.begin(DOUT1, CLK1);
  scale1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale1.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale2.begin(DOUT2, CLK2);
  scale2.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale2.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale3.begin(DOUT3, CLK3);
  scale3.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale3.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale4.begin(DOUT4, CLK4);
  scale4.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale4.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
}

void loop() 
{
  // Read OUT pin, and set onboard LED to mirror output
  readDigitalValue();
}

void readDigitalValue()
{
  if ( (lastPrint + PRINT_TIME) < millis() )
  {
    lastPrint = millis();
    // The OpenPIR's digital output is active high
    int motionStatusFirst = digitalRead(PIR_DOUT_FIRST);
    int motionStatusSecond = digitalRead(PIR_DOUT_SECOND);
    int motionStatusThird = digitalRead(PIR_DOUT_THIRD);
    float weight1 = scale1.get_units();
    float weight2 = scale2.get_units();
    float weight3 = scale3.get_units();
    float weight4 = scale4.get_units();
    int firstStatus = 0;
    int secondStatus = 0;
    int thirdStatus = 0;
  
    // If motion is detected, turn the onboard LED on:
    if (motionStatusFirst == HIGH){
      firstStatus = 1;
    }
    if (motionStatusSecond == HIGH) {
      secondStatus = 1;
    }
    if (motionStatusThird == HIGH) {
      thirdStatus = 1;
    }
  
    Serial.print(firstStatus);
    Serial.print(",");
    Serial.print(secondStatus);
    Serial.print(",");
    Serial.print(thirdStatus);  
    Serial.print(",");
    Serial.print(weight1, 1);
    Serial.print(",");
    Serial.print(weight2, 1);
    Serial.print(",");
    Serial.print(weight3, 1);
    Serial.print(",");
    Serial.print(weight4, 1);
    Serial.println();
  }
}
