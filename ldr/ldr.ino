
#define LDR 0 // the LDR will be connected to AIO1, i.e. analog 0

void setup () {
  Serial.begin(9600);
  pinMode(14+LDR, INPUT_PULLUP);
}
  
void loop () {
  // measure analog value and convert the 0..1023 result to 255..0
  byte value = 255 - analogRead(LDR) / 4;

    Serial.println(1024-analogRead(LDR));

    delay(1000);
}

