#include "Wire.h"
#define TMP102_I2C_ADDRESS 72 /* This is the I2C address for our chip.
This value is correct if you tie the ADD0 pin to ground. See the datasheet for some other values. */


void setup() {
  Wire.begin(); // start the I2C library
  Serial.begin(9600); //Start serial communication at 9600 baud
}


void getTemp102(){
  byte firstbyte, secondbyte; //these are the bytes we read from the TMP102 temperature registers
  int val; /* an int is capable of storing two bytes, this is where we "chuck" the two bytes together. */ 
  float temp; 
  // The sensor overreads (?) 


  /* Reset the register pointer (by default it is ready to read temperatures)
You can alter it to a writeable register and alter some of the configuration - 
the sensor is capable of alerting you if the temperature is above or below a specified threshold. */

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor. 
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
  Wire.endTransmission();


  firstbyte      = (Wire.read()); 
  secondbyte     = (Wire.read()); 
    val = ((firstbyte) << 4);  
    val |= (secondbyte >> 4);    
    temp = val*0.0625*1.8+32.0;

  Serial.println(temp);
}

void loop() {
  getTemp102();
  delay(1000); //wait 5 seconds before printing our next set of readings. 
}

