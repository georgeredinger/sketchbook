#include <math.h>
void setup() { 
  Serial.begin(9600); 
}
  float i=0.0;
  void loop() { 
     Serial.println(sin(i));
     i += 0.1;
     delay(1000);
} 
